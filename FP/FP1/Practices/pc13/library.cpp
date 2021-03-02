/*
	SUBMITTED BY:  Lucas Vukotic
   	DATE:          January 20, 2020
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MaxBooks = 50;
const int MaxShelves = 15;
const int NAreas = 3;

typedef enum { Mathematics, Physics, Computers } tArea;

struct tBook {
	string title;
	tArea area = Mathematics;
	int pages = 0;
};

typedef tBook tBookArray[MaxBooks];

struct tBookList {
	tBookArray books;
	int counter = 0;
};

struct tShelf {
	tArea area;
	int num = 0;
	tBookList bookList;
	int capacity = 0; // pages
	int available = 0; // pages
};

typedef tShelf tShelfArray[MaxShelves];

struct tLibrary {
	tShelfArray shelves;
	int counter = 0;
};

string areaToStr(tArea area);
tArea strToArea(string str);
bool load(tLibrary& library);
bool load(tBookList& bookList);
void display(tBookList bookList);
void display(const tLibrary& library);
void delBook(tBookList& bookList, int idx);
tBook getBiggest(tBookList& bookList);
int findShelf(const tLibrary& library, tBook book);
void assign(tLibrary& library, tBookList& bookList);

int main() {
	tLibrary library;
	tBookList bookList;

	if (load(library) && load(bookList)) {
			assign(library, bookList);
			display(library);
			cout << "Books that couldn't be placed..." << endl;
			display(bookList);
	}
	else
		cout << "Sorry, file(s) not found!" << endl;

	return 0;
}

string areaToStr(tArea area) {
	string str;

	if (area == Mathematics)
		str = "Mathematics";
	else if (area == Physics)
		str = "Physics";
	else
		str = "Computers";

	return str;
}

tArea strToArea(string str) {
	tArea area;

	if (str == "Mat")
		area = Mathematics;
	else if (str == "Phy")
		area = Physics;
	else
		area = Computers;

	return area;
}

bool load(tLibrary& library) {
	bool ok = false;
	ifstream file;
	string str;
	tShelf shelf;
	int shelfNr[NAreas] = { 0 };

	file.open("shelves.txt");
	if (file.is_open()) {
		ok = true;
		file >> library.counter;
		for (int i = 0; i < library.counter; i++) {
			file >> str;
			shelf.area = strToArea(str);
			shelfNr[shelf.area]++;
			shelf.num = shelfNr[shelf.area];
			file >> shelf.capacity;
			shelf.available = shelf.capacity;
			library.shelves[i] = shelf;
		}
		file.close();
	}

	return ok;
}

bool load(tBookList& bookList) {
	bool ok = false;
	ifstream file;
	tBook book;
	string str;

	file.open("books.txt");
	if (file.is_open()) {
		ok = true;
		file >> str;
		while ((str != "XXX") && (bookList.counter < MaxBooks)) {
			book.area = strToArea(str);
			file >> book.pages;
			file.get(); // Skips space
			getline(file, book.title);
			bookList.books[bookList.counter] = book;
			bookList.counter++;
			file >> str;
		}
		file.close();
	}

	return ok;
}

void display(tBookList bookList) {
	for (int i = 0; i < bookList.counter; i++)
		cout << "     " << bookList.books[i].title
		<< " (" << bookList.books[i].pages << " pages)" << endl;
	cout << endl;
}

void display(const tLibrary& library) {
	tShelf shelf;

	for (tArea area = Mathematics; area <= Computers; area = tArea(int(area) + 1))
		for (int i = 0; i < library.counter; i++)
			if (library.shelves[i].area == area) {
				shelf = library.shelves[i];
				cout << areaToStr(area) << " - " << shelf.num << " (" << shelf.capacity - shelf.available
					<< "/" << shelf.capacity << ")" << endl;
				display(shelf.bookList);
			}
}

void delBook(tBookList& bookList, int idx) {
	for (int i = idx + 1; i < bookList.counter; i++) {
		bookList.books[i - 1] = bookList.books[i]; 
	}
	bookList.counter--;
}

tBook getBiggest(tBookList& bookList) {
	int maxPages = -1, index;
	tBook out;
	for (int i = 0; i < bookList.counter; i++){
		if (bookList.books[i].pages > maxPages){
			maxPages = bookList.books[i].pages;
			index = i;
		}
	}
	out = bookList.books[index];
	delBook(bookList, index);
	return out;
}

int findShelf(const tLibrary& library, tBook book) {
	int shelf = -1;
	int i = 0;
	bool found = false;
	while (i < library.counter && !found){
		if (library.shelves[i].area == book.area && book.pages <= library.shelves[i].available){
			shelf = i;
			found = true;
		}
		i++;
	}
	return shelf;
}

int find(tBookList& bookList, tBook book){
	int index = -1;
	bool found = false;
	int i = 0;
	while (i < bookList.counter && !found){
		if (bookList.books[i].title == book.title){
			index = i;
			found = true;
		}
		i++;
	}
	return index;
}

void copy(tBookList& bookList, tBookList& unvisited){
	unvisited.counter = bookList.counter;
	for (int i = 0; i < bookList.counter; i++){
		unvisited.books[i] = bookList.books[i];
	}
}

void assign(tLibrary& library, tBookList& bookList) {
	int shelfIdx, bookIdx;
	tBookList unvisited;
	copy(bookList, unvisited);
	tBook book;
	int n_books = bookList.counter;
	for (int i = 0; i < n_books; i++){
		book = getBiggest(unvisited);
		shelfIdx = findShelf(library, book);
		if (shelfIdx != -1){
			library.shelves[shelfIdx].bookList.books[library.shelves[shelfIdx].bookList.counter] = book;
			library.shelves[shelfIdx].available -= book.pages;
			library.shelves[shelfIdx].bookList.counter++;
			bookIdx = find(bookList, book);
			delBook(bookList, bookIdx);
		}
	}
}
