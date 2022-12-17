#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int orderMethod, menu, hour, mealPortion, table, somethingElse, editOrder, position, newPortion, houseNum;
int z = 0;
double mealPrice, totalPrice;
string mealName, userName, address;

class chart {
public:
    string name;
    double price{};
    int portion{};
    double portionPrice{};

    void getChart();

    void putChart() const;
};

void chart::getChart() {
    name = mealName;
    price = mealPrice;
    portion = mealPortion;
    portionPrice = price * portion;
};

void chart::putChart() const {
    cout << name << " liczba porcji: " << portion << " cena: " << portionPrice << " zl" << endl;
};

void glowna() {
    cout << "1.MENU" << endl << "2.ZLOZ ZAMOWIENIE" << endl << "3.INFORMACJE O RESTAURACJI" << endl << "4.ZAKONCZ"
         << endl;
    cin >> menu;
}

void plikTXTmenu() {
    ifstream file;
    file.open("project/menu.txt");

    string line;
    while (file.good()) {
        getline(file, line);

        cout << line << endl;
    }
    file.close();
    {
        /* code */
    }

}

void zlozZamowienie() {
    chart chart[10];

    cout << "PODAJ IMIE: " << endl;
    cin >> userName;
    cout << "WITAJ: \"" << userName << "\"" << endl;
    cout << "WYBIERZ RODZAJ ZAMOWIENIA" << endl << "1.DOSTAWA (KOSZT DOSTAWY 15 zl) || 2.NA MIEJSCU" << endl;
    cin >> orderMethod;

    // ZŁY RODZAJ DOSTAWY
    while (orderMethod < 0 || orderMethod > 2) {
        cout << "PODAJ POPRAWNY RODZAJ ZAMOWIENIA";
        cout << "1.DOSTAWA (KOSZT DOSTAWY 15 zl) || 2.NA MIEJSCU" << endl;
        cin >> orderMethod;
    }

    if (orderMethod == 1) {
        cout << "WYBRALES: DOSTAWA DO DOMU" << endl;
        totalPrice += 15;
        cout << "Podaj o, ktorej godzinie chcesz aby dowiezc twoje zamowienie" << endl;
        cin >> hour;

        while (hour < 8 || hour > 23) {
            cout << "RESTAURACJA W TYCH GODZINACH JEST ZAMKNIETA" << endl;
            cout << "PODAJ POPRAWNA GODZINE" << endl;
            cin >> hour;
        }

        cout << "PODAJ ADRES DOSTAWY" << endl;
        cout << " ulica: ";
        cin >> address;
        cout << "numer domu: ";
        cin >> houseNum;


    } else if (orderMethod == 2) {
        cout << "WYBRALES: NA MIEJSCU" << endl;
        cout << "PODAJ NR STOLIKA PRZY KTORYM SIEDISZ (1-12)" << endl;
        cin >> table;

        while (table < 1 || table > 12) {
            cout << "ZLY NUMER STOLIKA" << endl;
            cout << "PODAJ NR STOLIKA DO REZERWACJI OD 1 DO 12" << endl;
            cin >> table;
        }
    }

    do {
        plikTXTmenu();
        ifstream inputfile("project/cennik1.txt");

        if (!inputfile.is_open())
            cout << "Error opening file";

        string linemenu;
        int row = 28;
        int rowhalf = row / 2;
        int i, j, x, y = 0;

        std::string TABtxt[row];
        std::string TABname[rowhalf];
        double TABprice[rowhalf];

        for (int r = 0; r < row; r++) {

            std::getline(inputfile, linemenu);
            TABtxt[r] = linemenu;

        }

        for (i = 0, j = 0; j < row; i++, j += 2) {

            TABname[i] = TABtxt[j + 1];

            double num;
            stringstream ss;
            ss << TABtxt[j];
            ss >> num;
            TABprice[i] = num;
        }

        inputfile.close();


        cout << "WYBIERZ CO CHCESZ ZAMOWIC" << endl;
        cin >> x;
        cout << "Podaj ilosc porcji, ktora chcesz zamowic" << endl;
        cin >> y;
        mealName = TABname[x];
        mealPrice = TABprice[x];
        mealPortion = y;
        chart[z].getChart();
        cout << "Wybierz co chesz robic dalej:" << endl;
        cout << "1. Zamawiac dalej" << endl << "2. Przejsc do podsumowania" << endl;
        cin >> somethingElse;
        z++;

    } while (somethingElse < 2);

    cout << "-----PODSUMOWANIE-----" << endl;
    for (int a = 0; a < z; a++) {
        string noName = chart[a].name;
        double noPortion = chart[a].portion;
        double noPortionPrice = chart[a].portionPrice;
        if (noName.empty() || noPortion == 0 || noPortionPrice == 0) {
            cout << "";
        } else {
            chart[a].putChart();
        }
        totalPrice += chart[a].portionPrice;
    }
    cout << "Do zaplaty: " << totalPrice << endl;
    cout << "Godzina dostawy: " << hour << endl;

    cout << "Jesli chcesz zlozyc zamowienie kliknij 0" << endl;
    cout << "Jesli chcesz edytowac zamowienie kliknj 1" << endl;
    cin >> editOrder;

    while (editOrder < 0 || editOrder > 1) {
        cout << "Podales zly numer" << endl;
        cout << "Podaj ponownie numer" << endl;
        cout << "Jesli chcesz zlozyc zamowienie kliknij 0" << endl;
        cout << "Jesli chcesz edytowac zamowienie kliknj 1" << endl;
        cin >> editOrder;
    }

    if (editOrder == 1) {
        if (orderMethod == 1) {
            cout << "---ZAMOWIENIE---" << endl;
            for (int y = 0; y < z; y++) {
                string noName = chart[y].name;
                double noPortion = chart[y].portion;
                double noPortionPrice = chart[y].portionPrice;
                if (noName.empty() || noPortion == 0 || noPortionPrice == 0) {
                    cout << "";
                } else {
                    chart[y].putChart();
                }
            }
            cout << "\n Calkowita cena: " << totalPrice << " zl" << endl;
            cout << "Wybierz pozycje z koszyka, ktora chesz edytowac (lista zaczyna sie od  0)" << endl;
            cin >> position;
            cout << "Wpisz ile porcji odjac lub wpisz 0 aby usunac wszystkie porcje: " << endl;
            cin >> newPortion;

            if (newPortion == 0) {
                int c;
                int tot = 10;
                for (c = 0; c < z; c++) {
                    if (c == position) {
                        for (int d = c; d < (z - 1); d++) {
                            chart[d] = chart[d + 1];
                            c--;
                            z--;
                        }
                    }
                }
            } else {
                chart[position].portion -= newPortion;
                chart[position].portionPrice -= chart[position].price * newPortion;
                totalPrice = 0;
                for (int i = 0; i < 5; i++) {
                    totalPrice = totalPrice + chart[i].portionPrice;
                }
                totalPrice = totalPrice + 15;
            }

            cout << "---PODSUMOWANIE---" << endl;
            for (int y = 0; y < z; y++) {
                string noName = chart[y].name;
                double noPortion = chart[y].portion;
                double noPortionPrice = chart[y].portionPrice;
                if (noName.empty() || noPortion == 0 || noPortionPrice == 0) {
                    cout << "";
                } else {
                    chart[y].putChart();
                }
            }
            cout << "Calkowita cena: " << totalPrice << endl;
            cout << "Godzina dostawy: " << hour << endl;
        } else if (orderMethod == 2) {
            cout << "---ZAMOWIENIE---" << endl;
            for (int y = 0; y < z; y++) {
                string noName = chart[y].name;
                double noPortion = chart[y].portion;
                double noPortionPrice = chart[y].portionPrice;
                if (noName.empty() || noPortion == 0 || noPortionPrice == 0) {
                    cout << "";
                } else {
                    chart[y].putChart();
                }
            }
            cout << "\n Calkowita cena: " << totalPrice << " zl" << endl;
            cout << "Wybierz pozycje z koszyka, ktora chesz edytowac (lista zaczyna sie od  0)" << endl;
            cin >> position;
            cout << "Wpisz ile porcji odjac lub wpisz 0 aby usunac wszystkie porcje: " << endl;
            cin >> newPortion;

            if (newPortion == 0) {
                int c;
                int tot = 10;
                for (c = 0; c < z; c++) {
                    if (c == position) {
                        for (int d = c; d < (z - 1); d++) {
                            chart[d] = chart[d + 1];
                            c--;
                            z--;
                        }
                    }
                }
            } else {
                chart[position].portion -= newPortion;
                chart[position].portionPrice -= chart[position].price * newPortion;
                totalPrice = 0;
                for (int i = 0; i < 5; i++) {
                    totalPrice = totalPrice + chart[i].portionPrice;
                }
            }

            cout << "---PODSUMOWANIE---" << endl;
            for (int y = 0; y < z; y++) {
                string noName = chart[y].name;
                double noPortion = chart[y].portion;
                double noPortionPrice = chart[y].portionPrice;
                if (noName.empty() || noPortion == 0 || noPortionPrice == 0) {
                    cout << "";
                } else {
                    chart[y].putChart();
                }
            }
            cout << "Calkowita cena: " << totalPrice << endl;
        }
    }

    ofstream myFile("project/paragon.txt");
    if (orderMethod == 2) {
        if (myFile.is_open()) {
            myFile << "Adress: Wzgórze Apokalipsy 62-420 ul. Apokaliptyczna 16" << endl << "Własciciel: Jack Steel"
                   << endl << "Otwarte 8-23" << endl << "Imie:" << userName << endl << "Numer stolika: " << table
                   << endl
                   << "------PARAGON_FISKALNY------" << endl;
            for (int b = 0; b < z; b++) {
                string noName = chart[b].name;
                double noPortion = chart[b].portion;
                double noPortionPrice = chart[b].portionPrice;
                if (noName.empty() || noPortion == 0 || noPortionPrice == 0) {
                    myFile << endl;
                } else {
                    myFile << chart[b].name << "  " << chart[b].portion << "x" << chart[b].price << "  "
                           << chart[b].portionPrice << " zl" << endl;
                }
            }
            myFile << "Całkowita cena: " << totalPrice << " zl";
        }

    } else {
        if (myFile.is_open()) {
            myFile << "Adress: Wzgórze Apokalipsy 62-420 ul. Apokaliptyczna 168" << endl << "Własciciel: Jack Steel"
                   << endl << "Otwarte 8-23" << endl
                   << "Imie: " << userName << endl << "Adres dostawy: " << address << " " << houseNum << endl
                   << " Godzina dostarczenia: " << hour << endl
                   << "------PARAGON_FISKALNY------" << endl;
            for (int b = 0; b < z; b++) {
                string noName = chart[b].name;
                double noPortion = chart[b].portion;
                double noPortionPrice = chart[b].portionPrice;
                if (noName.empty() || noPortion == 0 || noPortionPrice == 0) {
                    myFile << endl;
                } else {
                    myFile << chart[b].name << "  " << chart[b].portion << "x" << chart[b].price << "  "
                           << chart[b].portionPrice << " zl" << endl;
                };
            }
            myFile << "Całkowita cena: " << totalPrice << " zl";
        };
    }
    myFile.close();
    std::cin.get();

    exit(0);
}

void informacje() {
    cout << "Wlasciciel: Jack Steel" << endl << "Adress: Wzgórze Apokalipsy 62-420 ul. Apokaliptyczna 16" << endl
         << "Otwarte: \n pn-sb: 8:00 - 23:00" << endl;
}

void zakonczenie() {
    cout << "DZIEKI ZA ODWIEDZINY" << endl;
}

int main() {
    cout << "WITAMY W BARZE Kuchnia Pustkowia" << endl;
    cout << endl;
    while (menu < 4) {
        glowna();

        switch (menu) {
            //MENUUU
            case 1:
                plikTXTmenu();
                break;
            case 2:
                zlozZamowienie();
                cout << endl;
                break;
            case 3:
                informacje();
                break;
            case 4:
                zakonczenie();
                cout << endl;
                return 0;
        }
    }
    return 0;
}