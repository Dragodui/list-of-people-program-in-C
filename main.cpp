#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

typedef struct osoba
{
	string imie;
	string nazwisko;
	int wiek;
	string plec;
	string pesel;
	struct osoba* pPrev, * pNext;
} Osoba;

typedef struct osobaList {
	Osoba* head,
		* tail; 
} OsobaList;

Osoba* getOsoba()
{
	Osoba* p = new Osoba;
	cout << "Wprowadz imie: ";
	cin >> p->imie;
	cout << "Wprowadz nazwisko: ";
	cin >> p->nazwisko;
	cout << "Wprowadz wiek: ";
	cin >> p->wiek;
	cout << "Wprowadz plec: ";
	cin >> p->plec;
	cout << "Wprowadz pesel: ";
	cin >> p->pesel;
	cout << "\n";
	p->pPrev = p->pNext = NULL;
	return p;
}

void addOsoba(OsobaList* lst, Osoba* p)
{
	if (lst->head == NULL) {
		lst->head = lst->tail = p;
	}
	else {
		p->pPrev = lst->tail;
		lst->tail->pNext = p;
		lst->tail = p;
	}
}

void getListOsoba(OsobaList* lst)
{
	addOsoba(lst, getOsoba());
}

void printOsoba(Osoba* p)
{
	cout << p->imie << ' '
		<< p->nazwisko << ' '
		<< p->wiek << ' '
		<< p->plec << ' '
		<< p->pesel
		<< '\n';
}

void printListAuto(OsobaList* lst)
{
	for (Osoba* p = lst->head; p; p = p->pNext) {
		printOsoba(p);
	}
	cout << "\n";
}

void printListReverse(OsobaList* lst)
{
	for (Osoba* p = lst->tail; p; p = p->pPrev) {
		printOsoba(p);
	}
	cout << "\n";
}

void findOsoba(const OsobaList* lst) {
	int choice;
	cout << "Czy szukac po imieniu(1) czy po nazwisku(2)?: ";
	cin >> choice;
	string k;
	cout << "wprowadz: ";
	cin >> k;
	for (Osoba* current = lst->head; current; current = current->pNext)
	{
		switch (choice)
		{
		case 1:
			if (current->imie == k)
			{
				printOsoba(current);
			}
			break;
		case 2:
			if (current->nazwisko == k)
			{
				printOsoba(current);
			}
			break;
		}
	}
}

void writeToFile(OsobaList* lst)
{
	FILE* file;
	file = fopen("file2.txt", "w");
	for (Osoba* p = lst->head; p; p = p->pNext) {
		Osoba* cur = p;
		fprintf(file, "%s %s %d %s %s\n", cur->imie.c_str(), cur->nazwisko.c_str(), cur->wiek, cur->plec.c_str(), cur->pesel.c_str());
	}
	fclose(file);
}
void freeListAuto(OsobaList *lst)
{
	for (Osoba* p = lst->head; p;) {
		Osoba* cur = p;
		p = p->pNext;
		delete cur;   
	}

	lst->head = lst->tail = 0;
}
OsobaList* getFromFile() {
	OsobaList* list = new OsobaList();

	FILE* file;
	fopen_s(&file, "file.txt","r");
	while (!feof(file)) {
		Osoba* newOsoba = new Osoba();
		
		char* buf = new char[255];
		fscanf(file, "%s", buf);
		newOsoba->imie.assign(buf);
		fscanf(file, "%s", buf);
		newOsoba->nazwisko.assign(buf);
		fscanf(file, "%d", &newOsoba->wiek);
		fscanf(file, "%s", buf);
		newOsoba->plec.assign(buf);
		fscanf(file, "%s", buf);
		newOsoba->pesel.assign(buf);
		addOsoba(list, newOsoba);
	}
	fclose(file);

	return list;
}
void deleteOsoba(OsobaList* lst) {
	string k;
	cout << "wprowadz nazwisko: ";
	cin >> k;
	Osoba* current = lst->head;
	while (current != NULL)
	{	
		Osoba* next = current->pNext;
		if (current->nazwisko == k)
		{	
			if (current->pPrev == NULL) {
				if (current->pNext == NULL)
				{
					lst->head = NULL;
				}
				else
				{
					lst->head = current->pNext;
					current->pNext->pPrev = NULL;
				}
			}
			else if (current->pNext == NULL) {
				lst->tail = current->pPrev;
				current->pPrev->pNext = NULL;
			}
			else {
				Osoba* cur_next = current->pNext;
				Osoba* cur_prev = current->pPrev;
				cur_next->pPrev = cur_prev;
				cur_prev->pNext = cur_next;
			}
			free(current);
		}
		current = next;
	}
}

bool prwnc(string s0, string s1)
{
	int l0 = s0.length(), l1 = s1.length();
	int l = min(l0, l1);
	for (int i = 0; i < l; ++i)
	{
		char c0 = tolower(s0[i]), c1 = tolower(s1[i]);
		if (c0 > c1) return true;
		else if (c0 < c1) return false;
	}
	return l0 > l1;
}

void sort(OsobaList* list)
{
	int swapped;
	Osoba* current;
	Osoba* next = NULL;

	if (list->head == NULL)	return;

	do
	{
		swapped = 0;
		current = list->head;

		while (current->pNext != next)
		{
			if (prwnc(current->nazwisko, current->pNext->nazwisko))
			{
				swap(current->imie, current->pNext->imie);
				swap(current->nazwisko, current->pNext->nazwisko);
				swap(current->wiek, current->pNext->wiek);
				swap(current->pesel, current->pNext->pesel);
				swap(current->plec, current->pNext->plec);
				swapped = 1;
			}
			current = current->pNext;
		}
		next = current;
	} while (swapped);
	printListAuto(list);

}

int main(void)
{
	OsobaList* lst = new OsobaList;
	lst->head = lst->tail = NULL;
	while (1) {
		int choice;
		cout << "Wybierz: " << endl;
		cout << "0. Wyscie z programu" << endl;
		cout << "1. Dodaj uzytkownika" << endl;
		cout << "2. wyszukiwanie osoby(po nazwisku)" << endl;
		cout << "3. Kasowanie osoby" << endl;
		cout << "4. Wyswietlic liste" << endl;
		cout << "5. Wyswietlic liste(odwrotnie)" << endl;
		cout << "6. Odczytac liste z pliku" << endl;
		cout << "7. Zapisac liste do pliku" << endl;
		cout << "8. Sortowac liste po nazwisku" << endl;
		cout << "Wybor: ";
		cin >> choice;
		cout << endl;
		switch (choice) {
		case 0:
			freeListAuto(lst);
			return 0;
		case 1:
			getListOsoba(lst);
			break;
		case 2:
			findOsoba(lst);
			break;
		case 3:
			deleteOsoba(lst);
			break;
		case 4:
			printListAuto(lst);
			break;
		case 5:
			printListReverse(lst);
			break;
		case 6:
			freeListAuto(lst);
			lst = getFromFile();
			break;
		case 7:
			writeToFile(lst);
			break;
		case 8:
			sort(lst);
			break;
		default:
			cout << "Wybierz inne" << endl << endl;
			continue;
			break;
		}

	}
}
