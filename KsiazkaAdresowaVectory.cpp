
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

struct Uzytkownik
{
	int idUzytkownika;
	string nazwa, haslo;
};
struct DaneOsobowe
{
	string imie, nazwisko, telefon, email, adres;
	int idAdresata, idUser;
};
string wczytajLinie()
{
	string input;
	getline(cin, input);
	return input;
}
int wczytajLiczbe() {
	string linia;
	int liczba;

	while (true)
	{
		getline(cin, linia);
		try
		{
			liczba = stoi(linia);
			break;
		}
		catch (invalid_argument const&)
		{
			cout << "To nie jest poprawna liczba. Sprobuj ponownie: ";
		}
	}
	return liczba;
}

void odczytanieUzytkownikowZPiku(vector <Uzytkownik>& uzytkownicy)
{
	Uzytkownik user;
	string linia = "";
	int pozycja = 1;

	fstream plik;
	plik.open("Uzytkownicy.txt", ios::in);
	if (plik.good() == false)
	{
		cout << "plik nie moze byc otwarty";
	}
	while (getline(plik, linia))
	{
		stringstream ss(linia);
		string pole;
		pozycja = 1;

		while (getline(ss, pole, '|'))
		{
			switch (pozycja) {
			case 1: user.idUzytkownika = stoi(pole); break;
			case 2: user.nazwa = pole; break;
			case 3: user.haslo = pole; break;
			}
			pozycja++;
		}
		uzytkownicy.push_back(user);
	}
	plik.close();
}
void zapisUzytkownikowDoPliku(vector <Uzytkownik>& uzytkownicy)
{
	fstream plik;
	plik.open("Uzytkownicy.txt", ios::out);
	if (plik.good() == false)
	{
		cout << "plik nie może być otwarty";
	}
	else
	{
		for (int i = 0; i < uzytkownicy.size(); i++)
		{
			plik << uzytkownicy[i].idUzytkownika << "|" << uzytkownicy[i].nazwa << "|" << uzytkownicy[i].haslo << "|" << endl;
		}
	}
	plik.close();
}

string odczytajOstatniaLinie()
{
	fstream plik;
	plik.open("KsiazkaAdresowa.txt", ios::in);
	if (plik.good() == false)
	{
		cout << "plik nie może być otwarty";
	}
	string linia, ostatniaLinia;
	while (getline(plik, linia))
	{
		ostatniaLinia = linia;
	}
	plik.close();
	return ostatniaLinia;
}

void rejestracja(vector <Uzytkownik> &uzytkownicy)
{
	Uzytkownik user;
	fstream plik;
	plik.open("Uzytkownicy.txt", ios::app);
	if (plik.good() == false)
	{
		cout << "plik nie moze byc otwarty";
		return;
	}

	if (uzytkownicy.empty()) user.idUzytkownika = 1;
	else user.idUzytkownika = uzytkownicy.back().idUzytkownika + 1;
	
	cout << "Podaj nazwe uzytkownika: ";
	user.nazwa = wczytajLinie();
	int i = 0;
	while (i < uzytkownicy.size())
	{
		if (uzytkownicy[i].nazwa == user.nazwa)
		{
			cout << "Taki uzytkownik istnieje. Napisz inna nazwe uzytkownika" << endl;
			user.nazwa = wczytajLinie();
			i = 0;
		}
		else
		{
			i++;
		}
	}
	cout << "Podaj haslo: ";
	user.haslo = wczytajLinie();
	uzytkownicy.push_back(user);
	plik << user.idUzytkownika << "|" << user.nazwa << "|" << user.haslo << "|" << endl;
	cout << "Konto zalozone " << endl;
	plik.close();
	Sleep(1000);
}
int logowanie(vector <Uzytkownik> &uzytkownicy)
{
	string user, pass;
	cout << "Podaj login uzytkownika: ";
	user = wczytajLinie();
	int i = 0;
	while (i < uzytkownicy.size())
	{
		if (uzytkownicy[i].nazwa == user)
		{
			for (int proby = 0; proby < 3; proby++)
			{
				cout << "Podaj haslo. Pozostalo prob: " << 3 - proby << endl;
				pass = wczytajLinie();
				if (uzytkownicy[i].haslo == pass)
				{
					cout << "Zalogowano" << endl;
					Sleep(1000);
					return uzytkownicy[i].idUzytkownika;
				}
			}
			cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy";
			Sleep(3000);
			return 0;
		}
		i++;
	}
	cout << "Nie ma uzytkownika z takim loginem" << endl;
	Sleep(1500);
	return 0;
}
void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idOsobyZalogowanej)
{
	cout << "Podaj nowe haslo: ";
	uzytkownicy[idOsobyZalogowanej-1].haslo = wczytajLinie();
	zapisUzytkownikowDoPliku(uzytkownicy);
	cout << "Haslo zostalo zmienione" << endl;
	Sleep(1500);
}

void odczytywanieAdresatowZPliku(vector <DaneOsobowe>& osoby,int idOsobyZalogowanej)
{
	DaneOsobowe osoba;
	string linia = "";
	int pozycja = 1;

	fstream plik;
	plik.open("KsiazkaAdresowa.txt", ios::in);
	if (plik.good() == false)
	{
		cout << "plik nie moze byc otwarty";
	}
	while (getline(plik, linia))
	{
		stringstream ss(linia);
		string pole;
		pozycja = 1;

		while (getline(ss, pole, '|'))
		{
			switch (pozycja) {
			case 1: osoba.idAdresata = stoi(pole); break;
			case 2: osoba.idUser = stoi(pole); break;
			case 3: osoba.imie = pole; break;
			case 4: osoba.nazwisko = pole; break;
			case 5: osoba.telefon = pole; break;
			case 6: osoba.email = pole; break;
			case 7: osoba.adres = pole; break;
			}
			pozycja++;
		}
		if(idOsobyZalogowanej == osoba.idUser) osoby.push_back(osoba);
	}
	plik.close();
}
void zapisywanieAdresatowDoPliku(vector <DaneOsobowe>& osoby,int wybraneId)
{
	fstream plik1;
	plik1.open("KsiazkaAdresowa.txt", ios::in);
	if (plik1.good() == false)
	{
		cout << "plik nie może być otwarty";
		return;
	}
	fstream plik2;
	plik2.open("AdresaciTymczasowi.txt", ios::out);
	if (plik2.good() == false)
	{
		cout << "plik nie może być otwarty";
		return;
	}
	string linia;
	while (getline(plik1,linia))
	{
		if (stoi(linia) == wybraneId)
		{
			for (int i = 0; i < osoby.size(); i++)
			{
				if (osoby[i].idAdresata == wybraneId)
				{
					plik2 << osoby[i].idUser << "|" << osoby[i].idAdresata << "|" << osoby[i].imie << "|" << osoby[i].nazwisko << "|" << osoby[i].telefon << "|" << osoby[i].email << "|" << osoby[i].adres << "|" << endl;
				}
			}
		}
		else
		{
			plik2 << linia << endl;
		}
	}
	plik1.close();
	plik2.close();
	remove("KsiazkaAdresowa.txt");
	rename("AdresaciTymczasowi.txt","KsiazkaAdresowa.txt");
}

void dodanieOsobyDoKsiazkiAdresowej(vector <DaneOsobowe>& osoby, int idOsobyZalogowanej)
{
	DaneOsobowe osoba;
	fstream plik;
	plik.open("KsiazkaAdresowa.txt", ios::app);
	if (plik.good() == false)
	{
		cout << "plik nie może być otwarty";
	}
	else
	{
		system("cls");
		osoba.idUser = idOsobyZalogowanej;
		cout << "Wczytywanie kolejnej osoby do Ksiazki Adresowej" << endl;
		cout << "Podaj imie: ";
		osoba.imie = wczytajLinie();
		cout << "Podaj nazwisko: ";
		osoba.nazwisko = wczytajLinie();
		cout << "Podaj numer telefonu: ";
		osoba.telefon = wczytajLinie();
		cout << "Podaj adres email: ";
		osoba.email = wczytajLinie();
		cout << "Podaj adres zamieszkania: ";
		osoba.adres = wczytajLinie();
		if (!osoby.empty()) {
			osoba.idAdresata = stoi(odczytajOstatniaLinie())+1;
		}
		else {
			osoba.idAdresata = 1;
		}
		osoby.push_back(osoba);

		plik << osoba.idAdresata << "|" << osoba.idUser << "|" << osoba.imie << "|" << osoba.nazwisko << "|" << osoba.telefon << "|" << osoba.email << "|" << osoba.adres << "|" << endl;
	}
	plik.close();
	cout << "Osoba zostala dodana" << endl;
	cout << "Aby kontynuowac wcisnij ENTER" << endl;
	cin.get();
}
void wyszukiwanieOsobyPoImieniu(vector <DaneOsobowe>& osoby)
{
	string wpisaneImie;
	system("cls");
	cout << "Podaj imie: ";
	wpisaneImie = wczytajLinie();
	cout << endl << "----- ZNALEZIONE OSOBY -----" << endl;
	for (int i = 0; i < osoby.size(); i++)
	{
		if (wpisaneImie == osoby[i].imie)
		{
			cout << "ID: " << osoby[i].idAdresata << endl;
			cout << "Imie: " << osoby[i].imie << endl;
			cout << "Nazwisko: " << osoby[i].nazwisko << endl;
			cout << "Numer telefonu: " << osoby[i].telefon << endl;
			cout << "Adres email: " << osoby[i].email << endl;
			cout << "Adres zamieszkania: " << osoby[i].adres << endl << endl;
		}
	}
	cout << "Aby kontynuowac wcisnij ENTER" << endl;
	cin.get();
}
void wyszukiwanieOsobyPoNazwisku(vector <DaneOsobowe>& osoby)
{
	string wpisaneNazwisko;
	system("cls");
	cout << "Podaj nazwisko: ";
	wpisaneNazwisko = wczytajLinie();
	cout << endl << "----- ZNALEZIONE OSOBY -----" << endl;
	for (int i = 0; i < osoby.size(); i++)
	{
		if (wpisaneNazwisko == osoby[i].nazwisko)
		{
			cout << "ID: " << osoby[i].idAdresata << endl;
			cout << "Imie: " << osoby[i].imie << endl;
			cout << "Nazwisko: " << osoby[i].nazwisko << endl;
			cout << "Numer telefonu: " << osoby[i].telefon << endl;
			cout << "Adres email: " << osoby[i].email << endl;
			cout << "Adres zamieszkania: " << osoby[i].adres << endl << endl;
		}
	}
	cout << "Aby kontynuowac wcisnij ENTER" << endl;
	cin.get();
}
void wypisanieCalejKsiazkiAdresowej(vector <DaneOsobowe>& osoby)
{
	system("cls");
	cout << endl << "----- WSZYSTKIE OSOBY -----" << endl;
	for (int i = 0; i < osoby.size(); i++)
	{
		cout << "ID: " << osoby[i].idAdresata << endl;
		cout << "Imie: " << osoby[i].imie << endl;
		cout << "Nazwisko: " << osoby[i].nazwisko << endl;
		cout << "Numer telefonu: " << osoby[i].telefon << endl;
		cout << "Adres email: " << osoby[i].email << endl;
		cout << "Adres zamieszkania: " << osoby[i].adres << endl << endl;
	}
	cout << "Aby kontynuowac wcisnij ENTER" << endl;
	cin.get();
}

<<<<<<< HEAD
=======
{
	int wybraneId, wybranaPozycjaDoZmiany, wybor = 0;
	while (1)
	{
		system("cls");
		cout << "Prosze wybrac opcje wyszukiwania lub podac ID osoby do edycji" << endl;
		cout << "1. Wyszukiwanie osob po imieniu" << endl;
		cout << "2. Wyszukiwanie osob po nazwisku" << endl;
		cout << "3. Wyswietlenie calej ksiazki adresowej" << endl;
		cout << "4. Podanie numeru ID" << endl;
		cout << "9. Powrot do menu glownego" << endl;
		wybor = wczytajLiczbe();

		if (wybor == 1) wyszukiwanieOsobyPoImieniu(osoby);
		else if (wybor == 2) wyszukiwanieOsobyPoNazwisku(osoby);
		else if (wybor == 3) wypisanieCalejKsiazkiAdresowej(osoby);
		else if (wybor == 4) cout << endl;
		else if (wybor == 9) break;
		cout << "Prosze podac numer ID osoby znalezionej" << endl;
		cout << "Wybierz ID: ";
		wybraneId = wczytajLiczbe();
		for (int i = 0; i < osoby.size(); i++)
		{
			if (osoby[i].idAdresata == wybraneId)
			{
				while (1)
				{
					system("cls");
					cout << "1. Imie :" << osoby[i].imie << endl;
					cout << "2. Nazwisko :" << osoby[i].nazwisko << endl;
					cout << "3. Numer telefonu :" << osoby[i].telefon << endl;
					cout << "4. Adres email :" << osoby[i].email << endl;
					cout << "5. Adres zamieszkania :" << osoby[i].adres << endl;
					cout << "9. Wyjscie do poprzedniego menu" << endl;
					cout << "Wybierz pozycje do zmiany z powyzszej listy" << endl;

					wybranaPozycjaDoZmiany = wczytajLiczbe();
					if (wybranaPozycjaDoZmiany == 1)
					{
						cout << "Wpisz nowe imie: ";
						osoby[i].imie = wczytajLinie();
						cout << "Pozycja imie zostala zmieniona" << endl;
						Sleep(2000);
					}
					else if (wybranaPozycjaDoZmiany == 2)
					{
						cout << "Wpisz nowe nazwisko: ";
						osoby[i].nazwisko = wczytajLinie();
						cout << "Pozycja nazwisko zostala zmieniona" << endl;
						Sleep(2000);
					}
					else if (wybranaPozycjaDoZmiany == 3)
					{
						cout << "Wpisz nowy numer telefonu: ";
						osoby[i].telefon = wczytajLinie();
						cout << "Pozycja numer telefonu zostala zmieniona" << endl;
						Sleep(2000);
					}
					else if (wybranaPozycjaDoZmiany == 4)
					{
						cout << "Wpisz nowy adres email: ";
						osoby[i].email = wczytajLinie();
						cout << "Pozycja adres email zostala zmieniona" << endl;
						Sleep(2000);
					}
					else if (wybranaPozycjaDoZmiany == 5)
					{
						cout << "Wpisz nowy adres zamieszkania: ";
						osoby[i].adres = wczytajLinie();
						cout << "Pozycja adres zamieszkania zostala zmieniona" << endl;
						Sleep(2000);
					}
					else if (wybranaPozycjaDoZmiany == 9) break;
				}
			}
		}
		zapisywanieAdresatowDoPliku(osoby,wybraneId);
	}
}

>>>>>>> edit_person

int main()
{
	vector <Uzytkownik> uzytkownicy;
	vector <DaneOsobowe> osoby;
	int wybor = 0;
	int idOsobyZalogowanej = 0;
	odczytanieUzytkownikowZPiku(uzytkownicy);
	while (1)
	{
		if (idOsobyZalogowanej == 0)
		{
			system("cls");
			cout << "---------- KSIAZKA ADRESOWA ----------" << endl << endl;
			cout << "1. Rejestracja" << endl;
			cout << "2. Logowanie" << endl;
			cout << "9. Zakoncz Program" << endl;
			wybor = wczytajLiczbe();

			if (wybor == 1) rejestracja(uzytkownicy);
			else if (wybor == 2) idOsobyZalogowanej = logowanie(uzytkownicy);
			else if (wybor == 9) exit(0);
		}
		else
		{
			odczytywanieAdresatowZPliku(osoby, idOsobyZalogowanej);
			while (1)
			{
				system("cls");
				cout << "------------ KSIAZKA ADRESOWA ------------" << endl << endl;
				cout << "1. Dodanie osoby do ksiazki adresowej" << endl;
				cout << "2. Wyszukiwanie osob po imieniu" << endl;
				cout << "3. Wyszukiwanie osob po nazwisku" << endl;
				cout << "4. Wyswietlenie calej ksiazki adresowej" << endl;
				cout << "5. Edytowanie wybranej osoby po numerze ID" << endl;
				cout << "6. Usuniecie wybranej osoby po numerze ID" << endl;
				cout << endl << "---------------------------------------" << endl;
				cout << "7. Zmiana hasla" << endl;
				cout << "8. Wylogowanie" << endl;
				cout << "9. Zakonczenie programu" << endl;
				wybor = wczytajLiczbe();

				if (wybor == 1) dodanieOsobyDoKsiazkiAdresowej(osoby,idOsobyZalogowanej);
				else if (wybor == 2) wyszukiwanieOsobyPoImieniu(osoby);
				else if (wybor == 3) wyszukiwanieOsobyPoNazwisku(osoby);
				else if (wybor == 4) wypisanieCalejKsiazkiAdresowej(osoby);
				else if (wybor == 5) edycjaUtworzonegoWpisuPoId(osoby);
				else if (wybor == 6) usuwanieWpisu(osoby);
				else if (wybor == 7) {zmianaHasla(uzytkownicy, idOsobyZalogowanej); break;}
				else if (wybor == 8) { idOsobyZalogowanej = 0; osoby.clear(); break; }
				else if (wybor == 9) exit(0);
			}
		}
	}	
	return 0;
}


