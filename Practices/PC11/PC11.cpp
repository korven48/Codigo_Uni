#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cassert>
using namespace std;

const string FileName = "stock.txt";
const int DIM = 50;
const int NP = 20; // Number of purchases

struct tProduct
{
	string name;
	double price;
	int units;
	int code;
};
typedef tProduct tProdArray[DIM];

struct tItem
{
	int code;
	int units;
};

typedef tItem tItemArray[NP];

struct tCart
{
	tItemArray purchases;
	int count = 0;
};

struct tStock
{
	tProdArray products;
	int count = 0;
};

bool load(tStock &stock);
void save(const tStock &stock);
tProduct readProduct();
bool addProduct(tStock &stock);
void display(const tStock &stock);
int find(const tStock &stock, int code);
tItem readItem(const tStock &stock);
bool addToCart(tCart &cart, const tStock &stock);
void displayCart(const tCart cart, const tStock &stock);
void sellCart(tStock &stock, tCart &cart);

int menu();

int main()
{
	tStock stock;
	tCart cart;
	int option;

	if (!load(stock))
		cout << "File not found! Exiting..." << endl;
	else
	{
		option = menu();
		while (option != 0)
		{
			switch (option)
			{
			case 1:
				display(stock);
				// print();
				break;
			case 2:
				if (addProduct(stock))
					cout << "Product added!" << endl
						 << endl;
				else
					cout << "Too many porducts, not possible to add more." << endl;
				break;
			case 3:
				display(stock);
				if (!addToCart(cart, stock))
					cout << "Not enough units in stock!" << endl;
				break;
			case 4:
				displayCart(cart, stock);
				break;
			case 5:
				sellCart(stock, cart);
				cout << "Sold!" << endl;
				break;
			}
			cout << endl;
			option = menu();
		}
		save(stock);
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
		cout << "3 - Add order to cart" << endl;
		cout << "4 - Display cart" << endl;
		cout << "5 - Sell cart" << endl;
		cout << "0 - Exit" << endl;
		cout << "Your option: ";
		cin >> op;
		if ((op < 0) || (op > 6))
			cout << "Invalid option! Try again..." << endl;
	}
	cout << endl;
	return op;
}

bool load(tStock &stock)
{
	bool ok = false;
	ifstream file;
	string name;
	int code;

	file.open(FileName);
	stock.count = 0;
	if (file.is_open())
	{
		file >> code;
		while ((code != -1) && (stock.count < DIM))
		{
			stock.products[stock.count].code = code;
			file.get();
			getline(file, name);
			stock.products[stock.count].name = name;
			file >> stock.products[stock.count].price >> stock.products[stock.count].units;
			stock.count++;
			file >> code;
		}
		file.close();
		ok = true;
	}

	return ok;
}

void save(const tStock &stock)
{
	ofstream outputFile("stock.txt");
	if (outputFile.is_open())
	{
		for (int i = 0; i < stock.count; i++)
		{
			outputFile << stock.products[i].code << endl
					   << stock.products[i].name << endl
					   << stock.products[i].price << endl
					   << stock.products[i].units << endl;
		}
		outputFile << -1 << endl;
		outputFile.close();
	}
}

tProduct readProduct()
{
	tProduct product;
	cout << "Product code: ";
	cin >> product.code;
	cout << "Product name: ";
	cin >> product.name;
	cout << "Product price: ";
	cin >> product.price;
	cout << "Product units: ";
	cin >> product.units;

	return product;
}

bool addProduct(tStock &stock)
{
	bool added = false;
	tProduct product;
	product = readProduct();
	if (stock.count < DIM)
	{
		stock.products[stock.count] = product;
		added = true;
		stock.count++;
	}
	return added;
}

void display(const tStock &stock)
{
	// 1
	cout << " # " << setw(4) << left << "Code"
		 << setw(28 + 1) << left << "    Product"
		 << " Price"
		 << " Units" << endl;
	for (int i = 0; i < stock.count; i++)
	{
		cout << setw(2) << right << (i + 1) << ' ' << setw(7) << left << stock.products[i].code << ' '
			 << setw(25) << left << stock.products[i].name << ' '
			 << setprecision(2) << fixed << setw(8) << left << stock.products[i].price
			 << stock.products[i].units << endl;
	}
}

int find(const tStock &stock, int code)
{
	int index = -1;

	for (int i = 0; i < stock.count; i++)
	{
		if (stock.products[i].code == code)
			index = i;
	}

	return index;
}

tItem readItem(const tStock &stock)
{
	tItem item;
	int number, units;
	cout << "Please enter product's number: ";
	cin >> number;
	cout << "Please enter the units to buy: ";
	cin >> units;
	cout << endl;

	item.code = stock.products[number - 1].code;
	item.units = units;
	return item;
}

bool addToCart(tCart &cart, const tStock &stock)
{
	tItem item;
	int itemIndex;
	bool added = true;

	item = readItem(stock);
	itemIndex = find(stock, item.code);
	if (item.units > stock.products[itemIndex].units)
		added = false;
	else
	{
		cart.purchases[cart.count] = item;
		cart.count++;
	}
	return added;
}

void displayCart(const tCart cart, const tStock &stock)
{
	int itemIndex;
	double total = 0, unitsPrice;
	tItem item; // item
	tProduct product;
	for (int i = 0; i < cart.count; i++)
	{
		item = cart.purchases[i];
		itemIndex = find(stock, item.code);
		product = stock.products[itemIndex];

		unitsPrice = item.units * product.price;
		total += unitsPrice;

		cout << setw(26) << left << product.name
			 << right << product.price << " x"
			 << setw(5) << right << item.units << " ="
			 << setw(9) << right << fixed << setprecision(2) << unitsPrice << endl;
	}
	cout << setw(43) << left << "Total" << right << fixed << setprecision(2) << total << endl;
}

void sellCart(tStock &stock, tCart &cart)
{
	for (int i = 0; i < cart.count; i++)
	{
		int itemIndex;
		itemIndex = find(stock, cart.purchases[i].code);
		stock.products[itemIndex].units -= cart.purchases[i].units;
	}
	cart.count = 0;
}