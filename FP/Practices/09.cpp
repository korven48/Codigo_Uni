/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          Dicember 2, 2020
*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX = 20;

typedef string tName[MAX];
typedef int tCuantity[MAX];

bool load(string filename, tName names, tCuantity grams, tCuantity calories, int &counter);
double totalCalories(const tCuantity grams, const tCuantity calories, int counter);
void display(string name, tName names, tCuantity grams, tCuantity calories, int counter);
int findMax(const tCuantity grams, const tCuantity calories, int counter);
void save(string filename, const tName names, const tCuantity grams, const tCuantity calories, int counter);

void addIngredient(int calOfMax, int indexOfMax, tName names, tCuantity grams, tCuantity calories);


int main()
{
    string filename, name;
    int counter = 0, indexOfMax;
    double calOfMax;
    tName names;
    tCuantity grams;
    tCuantity calories;

    cout << "File to load: ";
    cin >> filename;
    cout << "Recipe's name: ";
    cin >> name;

    load(filename, names, grams, calories, counter);
    display(name, names, grams, calories, counter);
    indexOfMax = findMax(grams, calories, counter);
    calOfMax = grams[indexOfMax] / 100. * calories[indexOfMax];
    cout << "Substituting ingredient: " << names[indexOfMax] << " (total calories = " << calOfMax << ")" << endl;
    addIngredient(calOfMax, indexOfMax, names, grams, calories);
    display(name, names, grams, calories, counter);
    save(filename, names, grams, calories, counter);
    return 0;
}

bool load(string filename, tName names, tCuantity grams, tCuantity calories, int &counter){
    bool opened = true;
    int temp;
    ifstream inputFile(filename);
    if (!inputFile.is_open())
        opened = false;
    else
    {
        inputFile >> temp;
        while (temp != 0 && counter != MAX)
        {
            grams[counter] = temp;
            inputFile >> calories[counter];
            inputFile.get();
            getline(inputFile, names[counter]);
            counter++;
            inputFile >> temp;
        }
    }
    inputFile.close();
    return opened;
}

void display(string name, tName names, tCuantity grams, tCuantity calories, int counter){
    double cal;
    cout << "Recipe: " << name << endl;
    cout << " # Ingredient" << setw(15) << right << "Grams" << "  " << "Cal/100gr" << "  " << "Total cal" << endl;
    for (int i = 0; i < counter; i++){
        cal = grams[i] / 100. * calories[i];
        cout << " " << (i + 1) << " " << setw(21) << left << names[i] << setw(3) << right << grams[i]
             << setw(9) << right << calories[i] << setw(12) << right << fixed << setprecision(2) << cal << endl;
    }
    cout << "Total calories:" << setw(33) << right << totalCalories(grams, calories, counter) << endl << endl;
}

double totalCalories(const tCuantity grams, const tCuantity calories, int counter){
    double total = 0;
    for (int i = 0; i < counter; i++){
        total += grams[i] / 100. * calories[i];
    }
    return total;
}

int findMax(const tCuantity grams, const tCuantity calories, int counter){
    double maximum = -1, temp, index = -1;
    for (int i = 0; i < counter; i++){
        temp = grams[i] / 100. * calories[i];
        if (temp > maximum){
            maximum = temp;
            index = i;
        }
    }
    return index;
}

void save(string filename, const tName names, const tCuantity grams, const tCuantity calories, int counter){
    ofstream outputFile(filename);
    for(int i = 0; i < counter; i++){
        outputFile << grams[i] << ' ' << calories[i] << ' ' << names[i] << endl;
    }
    outputFile << 0 << endl;
    outputFile.close();
}

void addIngredient(int calOfMax, int indexOfMax, tName names, tCuantity grams, tCuantity calories){
    string newName;
    int newGrams, newCal;
    int cals = 999999999;
    while (cals > calOfMax){
        cout << endl;
        cout << "Please enter the name of the new ingredient: ";
        cin >> newName;
        cout << "Please enter the grams of the new ingredient: ";
        cin >> newGrams;
        cout << "Please enter the calories/100gr of the new ingredient: ";
        cin >> newCal;
        cout << endl;
        cals = newGrams / 100. * newCal;
        if (cals > calOfMax)
        {
            cout << "The new ingredient is not healthier! Try again..." << endl;
        } 
    }
    names[indexOfMax] = newName;
    grams[indexOfMax] = newGrams;
    calories[indexOfMax] = newCal;
}