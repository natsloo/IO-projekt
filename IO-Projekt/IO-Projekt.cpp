#include <iostream>
#include "Gosc.h"
#include "Pracownik.h"
#include "Data.h"

int main()
{
    //while (true)
    //{
    //    char a = Ekran::klawisz();
    //    if (a != 0)
    //        std::cout << (int)a << std::endl;
    //}
       
    std::cout<<R"(
 .----------------.  .----------------.  .----------------.  .----------------.  .----------------. 
| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |
| |  ____  ____  | || |     ____     | || |  _________   | || |  _________   | || |   _____      | |
| | |_   ||   _| | || |   .'    `.   | || | |  _   _  |  | || | |_   ___  |  | || |  |_   _|     | |
| |   | |__| |   | || |  /  .--.  \  | || | |_/ | | \_|  | || |   | |_  \_|  | || |    | |       | |
| |   |  __  |   | || |  | |    | |  | || |     | |      | || |   |  _|  _   | || |    | |   _   | |
| |  _| |  | |_  | || |  \  `--'  /  | || |    _| |_     | || |  _| |___/ |  | || |   _| |__/ |  | |
| | |____||____| | || |   `.____.'   | || |   |_____|    | || | |_________|  | || |  |________|  | |
| |              | || |              | || |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |
 '----------------'  '----------------'  '----------------'  '----------------'  '----------------' 
)";

    std::cout << "\n\n\n";
    int a;
    do {
        std::cout << "Kim jestes?\n1. Gosc.\n2. Pracownik.\n";
        std::cin >> a;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        if (a == 1) {
            Gosc g;
            int b;
            do {
                std::cout << "\nChcesz:\n1. zalogowac sie.\n2. utworzyc nowe konto.\n3. wrocic do wyboru uzytkownika.\n";
                std::cin >> b;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                if (b == 1) {
                    if (g.zaloguj("dane/goscie.csv")) {
                        g.gui();
                        system("cls");
                        break;
                    }
                    else {
                        std::cout << "Niepoprawne dane lub nie ma takiego uzytkownika.\n";
                    }
                }
                if (b == 2) {
                    g.zarejestruj("dane/goscie.csv");
                }
                if (b == 3) {
                    break;
                }
            } while (true);
        }
        if (a == 2) {
            Pracownik p;
            int b;
            do {
                std::cout << "Chcesz:\n1. zalogowac sie.\n2. utworzyc nowe konto.\n3. wrocic do wyboru uzytkownika.\n";
                std::cin >> b;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                if (b == 1) {
                    if (p.zaloguj("dane/pracownicy.csv")) {
                        p.gui();
                        system("cls");
                        break;
                    }
                    else {
                        std::cout << "Niepoprawne dane lub nie ma takiego uzytkownika.\n";
                    }
                }
                if (b == 2) {
                    p.zarejestruj("dane/pracownicy.csv");
                }
                if (b == 3) {
                    break;
                }
            } while (true);
        }
    } while (true);
}
