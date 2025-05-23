//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Pracownik.cpp
//  @ Date : 05.05.2025
//  @ Author : 
//
//

#define STRZALKI -32
#define GORA 72
#define DOL 80
#define LEWO 75
#define PRAWO 77
#define ESC 27
#define ENTER 13
#define BACKSPACE 8


#include "Pracownik.h"

Pracownik::Pracownik()
{
    this->katalog = KatalogDlaPracownikow::pobierzInstancjePracownik();
}

void Pracownik::przegladaj_katalog() 
{
    int a;
    system("cls");
    do
    {
        std::cout << "1. Przegladaj pokoje.\n2. Przegladaj uslugi.\n3. Wroc do menu.\n";
        std::cin >> a;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        if (a == 1) {
            przegladaj_pokoje();
        }
        if (a == 2) {
            przegladaj_uslugi();
        }
        if (a == 3) {
            return;
        }
    } while (true);
}

void Pracownik::przegladaj_pokoje()
{
    system("cls");
    std::shared_ptr<Data> data_przyjazdu = std::make_shared<Data>(Data::dzis() + 1);
    std::shared_ptr<Data> data_wymeldowania = std::make_shared<Data>(Data::dzis() + 2);

    bool rysuj = true;
    int wybor = 0;
    int start = 0;
    int ilosc = 10;
    int stop = min(start + ilosc, katalog->get_ilosc_pokoi());
    std::vector<short> indeksy = zastosuj_filtry(*data_przyjazdu, *data_wymeldowania, 0, 1000, 1, "all");
    while (true)
    {
        if (rysuj)
        {
            std::cout << "\033[" << 0 << ";" << 0 << "H";
            std::cout << "ESC - wyjscie z katalogu\n";
            std::cout << "F - wybierz filtry\n";
            std::cout << "D - dodaj nowy pokoj\n";
            std::cout << "E - edytuj aktualnie wybrany pokoj\n";
            std::cout << "BACKSPACE - usun aktualnie wybrany pokoj\n";
            std::cout << "Wyswietlam wyniki dla planowanej daty pobytu: " << data_przyjazdu->string() << " - " << data_wymeldowania->string() << "\n\n";
            if (indeksy.size() == 0)
            {
                std::cout << "Brak wynikow :(\n";
            }
            for (int i = start; i < stop; i++)
            {
                std::cout << i << ". " << (wybor == i ? "\033[38;5;0;48;5;15m" : "") << katalog->get_opis(indeksy[i]) << "\x1b[0m          \n";
            }
            rysuj = false;
            //std::cout << start << " " << wybor << " " << stop <<" "<< indeksy.size()<< "        \n";
        }
        switch (Ekran::klawisz())
        {
        case STRZALKI:
        {
            rysuj = true;
            switch (Ekran::klawisz())
            {
            case GORA:
            {
                if (wybor)
                {
                    wybor--;
                    if (wybor - start < 1)
                    {
                        if (start > 0)
                        {
                            start--;
                            stop--;
                        }
                    }
                }
                break;
            }
            case DOL:
            {
                if (wybor < indeksy.size() - 1)
                {
                    wybor++;
                    if (stop - wybor < 2)
                    {
                        if (stop < indeksy.size())
                        {
                            start++;
                            stop++;
                        }
                    }
                }
                break;
            }
            default:
                break;
            }
            break;
        }
        case ESC:
        {
            system("cls");
            return;
        }
        case 'f':
        case 'F':
        {
            indeksy = filtruj(data_przyjazdu, data_wymeldowania);
            start = 0;
            wybor = 0;
            stop = min(start + ilosc, indeksy.size());
            rysuj = true;
            system("cls");
            break;
        }
        case 'd':
        case 'D':
        {
            katalog->dodaj_pokoj(dodaj_pokoj());
            indeksy = zastosuj_filtry(*data_przyjazdu, *data_wymeldowania, 0, 1000, 1, "all");
            system("cls");
            rysuj = true;
            break;
        }
        case 'e':
        case 'E':
        {
            katalog->edytuj_pokoj(indeksy[wybor], edytuj_pokoj(indeksy[wybor]));
            indeksy = zastosuj_filtry(*data_przyjazdu, *data_wymeldowania, 0, 1000, 1, "all");
            system("cls");
            rysuj = true;
            break;
        }
        case BACKSPACE:
        {
            katalog->usun_pokoj(indeksy[wybor]);
            indeksy = zastosuj_filtry(*data_przyjazdu, *data_wymeldowania, 0, 1000, 1, "all");
            if (start)
            {
                start--;
            }
            if (stop)
            {
                stop--;
            }
            if (wybor)
            {
                wybor--;
            }
            system("cls");
            rysuj = true;
            break;
        }
        default:
            break;
        }
    }
}

std::shared_ptr<Pokoj> Pracownik::edytuj_pokoj(int indeks)
{
    auto p = katalog->get_pokoj(indeks);
    return dodaj_pokoj(p->getNumer(), p->getMaksymalnaLiczbaOsob(), p->getCenaZaNoc(), p->getStandardPokoju());
}

std::shared_ptr<Pokoj> Pracownik::dodaj_pokoj(int n, int lo, int cn, std::string s)
{
    system("cls");
    int numer = n;
    int liczba_osob = lo;
    int cena_noc = cn;
    std::vector<std::string> standard = { "family", "basic", "komfort", "apartament", "deluxe" };
    bool rysuj = true;
    int wybor = 0, wybor_standard = 0;
    for (int i=0; i< standard.size(); i++)
    {
        if (s == standard[i])
        {
            wybor_standard = i;
        }
    }
    while (true)
    {
        if (rysuj)
        {
            std::cout << "\033[" << 0 << ";" << 0 << "H";
            std::cout << "ENTER - zatwierdz pokoj\n\n\n";
            std::cout << "Numer pokoju: " << (wybor == 0 ? "\033[38;5;0;48;5;15m" : "") << numer << "\x1b[0m          \n";
            std::cout << "Makasymalna liczba osob: " << (wybor == 1 ? "\033[38;5;0;48;5;15m" : "") << liczba_osob << "\x1b[0m          \n";
            std::cout << "Cena za noc: " << (wybor == 2 ? "\033[38;5;0;48;5;15m" : "") << cena_noc << "\x1b[0m          \n";
            std::cout << "Standard: " << (wybor == 3 ? "\033[38;5;0;48;5;15m" : "") << standard[wybor_standard] << "\x1b[0m          \n";
            rysuj = false;
        }
        switch (Ekran::klawisz())
        {
        case STRZALKI:
        {
            rysuj = true;
            switch (Ekran::klawisz())
            {
            case GORA:
            {
                if (wybor)
                    wybor--;
                break;
            }
            case DOL:
            {
                if (wybor < 3)
                    wybor++;
                break;
            }
            case LEWO:
            {
                switch (wybor)
                {
                case 0:
                {
                    if (numer > 101)
                        numer--;
                    break;
                }
                case 1:
                {
                    if (liczba_osob>1)
                    {
                        liczba_osob--;
                    }

                    break;
                }
                case 2:
                {
                    if (cena_noc>50)
                    {
                        cena_noc-=10;
                    }
                    break;
                }
                case 3:
                {
                    if (wybor_standard)
                        wybor_standard--;
                    break;
                }
                default:
                    break;
                }
                break;
            }
            case PRAWO:
            {
                switch (wybor)
                {
                case 0:
                {
                    if (numer < 199)
                        numer++;
                    break;
                }
                case 1:
                {
                    if (liczba_osob < 8)
                        liczba_osob++;
                    break;
                }
                case 2:
                {
                    if (cena_noc < 1000)
                        cena_noc += 10;
                    break;
                }
                case 3:
                {
                    if (wybor_standard < standard.size() - 1)
                        wybor_standard++;
                    break;
                }
                default:
                    break;
                }
                break;
            }
            default:
                break;
            }
            break;
        }
        case ENTER:
        {
            return std::make_shared<Pokoj>(numer, liczba_osob, cena_noc, standard[wybor_standard]);
            system("cls");
        }
        default:
            break;
        }
    }
}

void Pracownik::przegladaj_uslugi()
{
    system("cls");
    bool rysuj = true;
    int wybor = 0;
    int start = 0;
    int ilosc = 10;
    int stop = min(start + ilosc, katalog->get_ilosc_uslug());

    int najdluzszy = 0;
    for (int i = 0; i < katalog->get_ilosc_uslug(); i++) {
        if (katalog->get_opis_uslugi(i).length() > najdluzszy) {
            najdluzszy = katalog->get_opis_uslugi(i).length();
        }
    }

    while (true)
    {
        if (rysuj)
        {
            std::cout << "\033[" << 0 << ";" << 0 << "H";
            std::cout << "ESC - wyjscie z katalogu\n";
            std::cout << "D - dodaj nowa usluge\n";
            std::cout << "E - edytuj aktualnie wybrana usluge\n";
            std::cout << "BACKSPACE - usun aktualnie wybrana usluge\n";
            for (int i = start; i < stop; i++)
            {
                std::cout << i << ". " << (wybor == i ? "\033[38;5;0;48;5;15m" : "") << katalog->get_opis_uslugi(i) << Ekran::spacje(najdluzszy - katalog->get_opis_uslugi(i).length() + 4) << "\x1b[0m                              \n";
            }
            rysuj = false;
        }
        switch (Ekran::klawisz())
        {
        case STRZALKI:
        {
            rysuj = true;
            switch (Ekran::klawisz())
            {
            case GORA:
            {
                if (wybor)
                {
                    wybor--;
                    if (wybor - start < 1)
                    {
                        if (start > 0)
                        {
                            start--;
                            stop--;
                        }
                    }
                }
                break;
            }
            case DOL:
            {
                if (wybor < katalog->get_ilosc_uslug() - 1)
                {
                    wybor++;
                    if (stop - wybor < 2)
                    {
                        if (stop < katalog->get_ilosc_uslug())
                        {
                            start++;
                            stop++;
                        }
                    }
                }
                break;
            }
            default:
                break;
            }
            break;
        }
        case ESC:
        {
            system("cls");
            return;
        }
        case 'd':
        case 'D':
        {
            katalog->dodaj_usluge(dodaj_usluge());
            system("cls");
            rysuj = true;
            break;
        }
        case 'e':
        case 'E':
        {
            katalog->edytuj_usluge(wybor, edytuj_usluge(wybor));
            system("cls");
            rysuj = true;
            break;
        }
        case BACKSPACE:
        {
            katalog->usun_usluge(wybor);
            if (start)
            {
                start--;
            }
            if (stop)
            {
                stop--;
            }
            if (wybor)
            {
                wybor--;
            }
            system("cls");
            rysuj = true;
            break;
        }

        default:
            break;
        }
    }
}

DodatkowaUsluga Pracownik::edytuj_usluge(int indeks)
{
    auto u = katalog->get_usluga(indeks);
    return dodaj_usluge(u.get_nazwa(), u.get_cena());
}

DodatkowaUsluga Pracownik::dodaj_usluge(std::string n, double c)
{
    system("cls");
    std::string nazwa = n;
    double cena = c;
    bool rysuj = true;
    int wybor = 0;
    auto policz_kropki = [](const std::string& s) {
        return std::count(s.begin(), s.end(), '.');
        };
    std::string cena_str = std::to_string(cena);

    while (true)
    {
        if (rysuj)
        {
            std::cout << "\033[" << 0 << ";" << 0 << "H";
            std::cout << "ENTER - zatwierdz usluge\n\n\n";
            std::cout << "Nazwa uslugi: " << (wybor == 0 ? "\033[38;5;0;48;5;15m" : "") << nazwa << "\x1b[0m          \n";
            std::cout << "cena: " << (wybor == 1 ? "\033[38;5;0;48;5;15m" : "") << cena_str << "\x1b[0m          \n";
            rysuj = false;
        }
        char klawisz = Ekran::klawisz();
        switch (klawisz)
        {
        case STRZALKI:
        {
            rysuj = true;
            switch (Ekran::klawisz())
            {
            case GORA:
            {
                if (wybor)
                    wybor--;
                break;
            }
            case DOL:
            {
                if (wybor < 1)
                    wybor++;
                break;
            }
            
            default:
                break;
            }
            break;
        }
        case ENTER:
        {
            return DodatkowaUsluga(nazwa, std::stod(cena_str));
            system("cls");
        }case BACKSPACE:
        {
            rysuj = true;
            if (wybor == 0)
            {
                if (nazwa.length()>0)
                    nazwa.pop_back();
            }
            if (wybor == 1)
            {
                if(cena_str.length()>0)
                    cena_str.pop_back();
            }
        }
        default:
        {
            
            if (wybor == 0 && ((klawisz>= 'a' && klawisz<= 'z') || (klawisz >= 'A' && klawisz <= 'Z') || klawisz == ' '))
            {
                nazwa += klawisz;
                rysuj = true;
            }
            if (wybor == 1 && ((klawisz >= '0' && klawisz <= '9') || (klawisz == '.' && cena_str.length()>0 && policz_kropki(cena_str)<1)))
            {
                cena_str += klawisz;
                rysuj = true;
            }
        }
            break;
        }
    }
}

void Pracownik::wirtualna_recepcja()
{
    system("cls");
    auto wr = WirtualnaRecepcja::pobierzInstancje();
    int a;
    do {
        auto para = Wiadomosc::odczytaj_wiadomosci(this->login);
        this->wyslane_wiadomosci = para.first;
        this->odebrane_wiadomosci = para.second;
        std::cout << "1. Zamelduj\n2. Wymelduj\n3. Zobacz wszystkie rezerwacje\n4. Zobacz status wszystkich pokoi\n5. Wroc do menu\n";
        std::cin >> a;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        if (a == 1) {
            wr->zamelduj();
        }
        if (a == 2) {
            wr->wymelduj();
        }
        if (a == 3) {
            wr->przegladaj_rezerwacje();
        }
        if (a == 4) {
            wr->przegladaj_pokoje();
        }
        if (a == 5) {
            return;
        }
    } while (true);
}


void Pracownik::gui() {
	system("cls");
    int a;
    do {
        auto para = Wiadomosc::odczytaj_wiadomosci(this->login);
        this->wyslane_wiadomosci = para.first;
        this->odebrane_wiadomosci = para.second;
        std::cout << "1. Pokaz katalog.\n2. Wejdz do wirtualnej recepcji.\n3. Wyslij wiadomosc.\n4. Zobacz wyslane wiadomosci.\n5. Zobacz odebrane wiadomosci.\n6. Wyloguj sie.\n";
        std::cin >> a;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        if (a == 1) {
            przegladaj_katalog();
        }
        if (a == 2) {
            wirtualna_recepcja();
        }
        if (a == 3) {
            wyslij_wiadomosc();
        }
        if (a == 4) {
            przegladaj_wyslane_wiadomosci();
        }
        if (a == 5) {
            przegladaj_odebrane_wiadomosci();
        }
        if (a == 6) {
            wyloguj();
            break;
        }
    } while (true);
}








//
// METODY skopiowane z gosc.cpp
//


std::vector<short> Pracownik::filtruj(std::shared_ptr<Data> data_przyjazdu, std::shared_ptr<Data> data_wymeldowania)
{
    system("cls");

    int min_liczba_osob = 1;

    int min_cena_noc = 0;
    int max_cena_noc = 1000;
    std::vector<std::string> standard = { "all", "family", "basic", "komfort", "apartament", "deluxe" };
    bool rysuj = true;
    int wybor = 0, wybor_standard = 0;
    while (true)
    {
        if (rysuj)
        {
            std::cout << "\033[" << 0 << ";" << 0 << "H";
            std::cout << "R - resetuj wszystkie filtry\n";
            std::cout << "ENTER - zatwierdz filtry\n\n\n";
            std::cout << "Minimalna liczba osob: " << (wybor == 0 ? "\033[38;5;0;48;5;15m" : "") << min_liczba_osob << "\x1b[0m          \n";
            std::cout << "Data przyjazdu: " << (wybor == 1 ? "\033[38;5;0;48;5;15m" : "") << data_przyjazdu->string() << "\x1b[0m          \n";
            std::cout << "Data wymeldowania: " << (wybor == 2 ? "\033[38;5;0;48;5;15m" : "") << data_wymeldowania->string() << "\x1b[0m          \n";
            std::cout << "Minimalna cena za noc: " << (wybor == 3 ? "\033[38;5;0;48;5;15m" : "") << min_cena_noc << "\x1b[0m          \n";
            std::cout << "Maksymalna cena za noc: " << (wybor == 4 ? "\033[38;5;0;48;5;15m" : "") << max_cena_noc << "\x1b[0m          \n";
            std::cout << "Standard: " << (wybor == 5 ? "\033[38;5;0;48;5;15m" : "") << standard[wybor_standard] << "\x1b[0m          \n";
            rysuj = false;
        }
        switch (Ekran::klawisz())
        {
        case STRZALKI:
        {
            rysuj = true;
            switch (Ekran::klawisz())
            {
            case GORA:
            {
                if (wybor)
                    wybor--;
                break;
            }
            case DOL:
            {
                if (wybor < 5)
                    wybor++;
                break;
            }
            case LEWO:
            {
                switch (wybor)
                {
                case 0:
                {
                    if (min_liczba_osob > 1)
                        min_liczba_osob--;
                    break;
                }
                case 1:
                {
                    if (*data_przyjazdu > Data::dzis())
                    {
                        (*data_przyjazdu)--;
                    }

                    break;
                }
                case 2:
                {
                    if (*data_wymeldowania > *data_przyjazdu + 1)
                    {
                        (*data_wymeldowania)--;
                    }
                    break;
                }
                case 3:
                {
                    if (min_cena_noc > 50)
                        min_cena_noc -= 50;
                    break;
                }
                case 4:
                {
                    if (max_cena_noc > 200 && max_cena_noc > min_cena_noc + 50)
                        max_cena_noc -= 50;
                    break;
                }
                case 5:
                {
                    if (wybor_standard)
                        wybor_standard--;
                }
                default:
                    break;
                }
                break;
            }
            case PRAWO:
            {
                switch (wybor)
                {
                case 0:
                {
                    if (min_liczba_osob < 6)
                        min_liczba_osob++;
                    break;
                }
                case 1:
                {
                    if (*data_przyjazdu + 1 < *data_wymeldowania)
                        *data_przyjazdu = *data_przyjazdu + 1;
                    break;
                }
                case 2:
                {
                    (*data_wymeldowania)++;
                    break;
                }
                case 3:
                {
                    if (min_cena_noc < 1000 && min_cena_noc + 50 < max_cena_noc)
                        min_cena_noc += 50;
                    break;
                }
                case 4:
                {
                    if (max_cena_noc < 1000)
                        max_cena_noc += 50;
                    break;
                }
                case 5:
                {
                    if (wybor_standard < standard.size() - 1)
                        wybor_standard++;
                }
                default:
                    break;
                }
                break;
            }
            default:
                break;
            }
            break;
        }
        case ENTER:
        {
            system("cls");
            return zastosuj_filtry(*data_przyjazdu, *data_wymeldowania, min_cena_noc, max_cena_noc, min_liczba_osob, standard[wybor_standard]);
        }
        case 'r':
        case 'R':
        {
            data_przyjazdu = std::make_shared<Data>(Data::dzis() + 1);
            data_wymeldowania = std::make_shared<Data>(Data::dzis() + 2);
            return zastosuj_filtry(*data_przyjazdu, *data_wymeldowania, 0, 1000, 1, "all");
        }
        default:
            break;
        }
    }

}

std::vector<short> Pracownik::zastosuj_filtry(Data data_przyjazdu, Data data_wymeldowania, int min_cena_noc, int max_cena_noc, int min_liczba_osob, std::string standard)
{
    std::vector<short> wyniki;
    auto v1 = katalog->filtruj_wg_ceny(min_cena_noc, max_cena_noc);
    auto v2 = katalog->filtruj_wg_ilosci_osob(min_liczba_osob);
    auto v3 = katalog->filtruj_wg_standardu(standard);
    wyniki = polacz_wyniki_filtrow(v1, v2);
    wyniki = polacz_wyniki_filtrow(wyniki, v3);
    for (Data d = data_przyjazdu; d <= data_wymeldowania; d++)
    {
        auto v4 = katalog->filtruj_wg_daty(d);
        wyniki = polacz_wyniki_filtrow(wyniki, v4);
    }
    return wyniki;
}
