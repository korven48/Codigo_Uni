#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const string FileName = "stock.txt";
const int MAX = 50;

typedef string tProdName[MAX];
typedef double tProdPrice[MAX];
typedef int tProdUnits[MAX];

bool load(tProdName prodName, tProdPrice prodPrice, tProdUnits prodUnits, int &counter);
void save(const tProdName prodName, const tProdPrice prodPrice, const tProdUnits prodUnits,
		  int counter);
void initCart(tProdUnits cart);
void newProd(string &name, double &price, int &units);
bool insert(tProdName prodName, tProdPrice prodPrice, tProdUnits prodUnits, string name,
			double price, int units, int &counter);
void print(const tProdName prodName, const tProdPrice prodPrice, const tProdUnits prodUnits,
		   int counter);
void dispCart(const tProdUnits cart, int counter, const tProdName prodName,
			  const tProdPrice prodPrice);
void sell(tProdUnits prodUnits, tProdUnits cart);
int menu();

void addToCart(tProdUnits prodUnits, tProdUnits cart);

int main()
{
	tProdName prodName;
	tProdPrice prodPrice;
	tProdUnits prodUnits;
	tProdUnits shoppingCart;
	int counter = 0, cartCount = 0, option = -1;
	string name;
	double price;
	int units;

	if (!load(prodName, prodPrice, prodUnits, counter))
		cout << "File not found! Exiting..." << endl;
	else
	{
		while (option != 0)
		{
			option = menu();
			switch (option)
			{
			case 1:
				print(prodName, prodPrice, prodUnits, counter);
				break;
			case 2:
				newProd(name, price, units);
				if (insert(prodName, prodPrice, prodUnits, name, price, units, counter))
					cout << "Product added!" << endl
						 << endl;
				else
					cout << "Too many porducts, not possible to add more." << endl;
				break;
			case 3:
				initCart(shoppingCart);
				break;
			case 4:
				print(prodName, prodPrice, prodUnits, counter);
				addToCart(prodUnits, shoppingCart);
				break;
			case 5:
				dispCart(shoppingCart, counter, prodName, prodPrice);
				break;
			case 6:
				sell(prodUnits, shoppingCart);
				cout << "Sold!" << endl;
				break;
			}
			cout << endl;
		}
		save(prodName, prodPrice, prodUnits, counter);
	}

	return 0;
}

int menu()
{
	int op = -1;

	while ((op < 0) || (op > 6))
	{
		cout << "1 - Display stock" << endl;
		cout << "2 - New stock product" << endl;
		cout << "3 - Create cart" << endl;
		cout << "4 - Add order to cart" << endl;
		cout << "5 - Display cart" << endl;
		cout << "6 - Sell cart" << endl;
		cout << "0 - Exit" << endl;
		cout << "Your option: ";
		cin >> op;
		if ((op < 0) || (op > 6))
			cout << "Invalid option! Try again..." << endl;
	}
	cout << endl;
	return op;
}

bool load(tProdName prodName, tProdPrice prodPrice, tProdUnits prodUnits, int &counter)
{
	bool ok = false;
	ifstream file;
	string name;

	file.open(FileName);
	counter = 0;
	if (file.is_open())
	{
		file >> name;
		while ((name != "XXX") && (counter < MAX))
		{
			prodName[counter] = name;
			file >> prodPrice[counter] >> prodUnits[counter];
			counter++;
			file >> name;
		}
		file.close();
		ok = true;
	}

	return ok;
}

void save(const tProdName prodName, const tProdPrice prodPrice, const tProdUnits prodUnits,
		  int counter)
{
	ofstream outputFile("stock.txt");
	if (outputFile.is_open())
	{
		for (int i = 0; i < counter; i++)
		{
			outputFile << prodName[i] << " " << prodPrice[i] << " " << prodUnits[i] << endl;
		}
		outputFile << "XXX" << endl;
	}
}

void initCart(tProdUnits cart)
{
	// 3
	for (int i = 0; i < MAX; i++)
		cart[i] = 0;
}

void newProd(string &name, double &price, int &units)
{
	// 2
	cout << "Product name: ";
	cin >> name;
	cout << "Product price: ";
	cin >> price;
	cout << "Product units: ";
	cin >> units;
}

bool insert(tProdName prodName, tProdPrice prodPrice, tProdUnits prodUnits, string name,
			double price, int units, int &counter)
{
	bool ok = false;
	if (counter < MAX)
	{
		prodName[counter] = name;
		prodPrice[counter] = price;
		prodUnits[counter] = units;
		counter++;
		ok = true;
	}
	return ok;
}

void print(const tProdName prodName, const tProdPrice prodPrice, const tProdUnits prodUnits,
		   int counter)
{
	// 1
	cout << "# " << setw(25) << left << "Product"
		 << " Price" << ' ' << "Units" << endl;
	for (int i = 0; i < counter; i++)
	{
		cout << (i + 1) << ' ' << setw(25) << left << prodName[i] << setw(6) << right << prodPrice[i]
			 << setw(6) << right << prodUnits[i] << endl;
	}
}

void dispCart(const tProdUnits cart, int counter, const tProdName prodName,
			  const tProdPrice prodPrice)
{
	// 5
	double total = 0;
	for (int i = 0; i < counter; i++)
	{
		if (cart[i])
		{
			cout << setw(16) << left << prodName[i] << setw(10) << left << prodPrice[i] << right << "x" << setw(5) << right << cart[i]
				 << " =" << setw(10) << right << fixed << setprecision(2) << (prodPrice[i] * cart[i]) << endl;
			total += prodPrice[i] * cart[i];
		}
	}
	cout << "Total" << setw(39) << total << endl;
}

void sell(tProdUnits prodUnits, tProdUnits cart)
{
	for (int i = 0; i < MAX; i++)
	{
		prodUnits[i] -= cart[i];
		cart[i] = 0;
	}
}

void addToCart(tProdUnits prodUnits, tProdUnits cart)
{
	int num, units;
	cout << "Product Number: ";
	cin >> num;
	num--;
	cout << "Units to buy: ";
	cin >> units;
	while (units > prodUnits[num])
	{
		cout << "Units available: " << prodUnits[num] << " Try again!" << endl;
		cout << "Units to buy: ";
		cin >> units;
	}
	// prodUnits[num] -= units;
	cart[num] += units;
}