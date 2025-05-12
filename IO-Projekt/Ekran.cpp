#include "Ekran.h"

char Ekran::klawisz() {
	if (_kbhit()) {
		return _getch();
	}
}
