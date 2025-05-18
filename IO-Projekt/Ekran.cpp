#include "Ekran.h"

char Ekran::klawisz() {
	if (_kbhit()) {
		return _getch();
	}
}

std::string Ekran::spacje(int naj) {
    std::string s = "";
    for (int i = 0; i < naj; i++) {
        s += " ";
    }
    return s;
}
