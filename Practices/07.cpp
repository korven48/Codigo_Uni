#include <iostream>
#include <fstream>

using namespace std;

const int Length = 20;
typedef int tSequence[Length];
typedef bool tBooleanSeq[Length];

bool isTriangular(int n);
void display_seq(const tSequence seq);
void triangulars(const tSequence seq);
bool isGrowing(const tBooleanSeq seq);

int main()
{
    ifstream inputFile("sequence.txt");
    ifstream triangular;
    tSequence numbers;
    tBooleanSeq higher;

    if (inputFile.is_open())
    {
        int i = 0, temp;
        inputFile >> temp;
        while (temp >= 0 && i < Length)
        {
            numbers[i] = temp;
            i++;
            inputFile >> temp;
        }
        if (i < (Length - 1))
            cout << "Less than 20 numbers in the file! Exiting..." << endl;
        else
        {
            display_seq(numbers);
            triangulars(numbers);
            triangular.open("triangular.txt");
            if (triangular.is_open())
            {
                cout << "Triangular numbers: ";
                triangular >> temp;
                while (temp != -1)
                {
                    cout << temp << " ";
                    triangular >> temp;
                }
                cout << endl;
            }
            triangular.close();

            for (int i = Length - 1; i > 0; i--)
            {
                if (numbers[i] >= numbers[i - 1])
                    higher[i] = true;
                else
                    higher[i] = false;
                // cout << higher[i] << endl;
            }

            if (isGrowing(higher))
                cout << "The sequence is a growing sequence of numbers" << endl;
            else
                cout << "The sequence is NOT a growing sequence of numbers" << endl;
        }
    }
    else
        cout << "File not found! Exiting..." << endl;

    inputFile.close();
    return 0;
}

void display_seq(const tSequence seq)
{
    for (int i = 0; i < Length; i++)
    {
        cout << seq[i];
        if ((i + 1) < Length)
            cout << " ";
        else
            cout << endl;
    }
}

bool isTriangular(int n)
{
    int i = 1, total = 0;
    while (total < n)
    {
        total += i;
        i++;
    }
    if (total == n)
        return true;
    else
        return false;
}

void triangulars(const tSequence seq)
{
    ofstream outputFile("triangular.txt");
    if (outputFile.is_open())
    {
        for (int i = 0; i < Length; i++)
        {
            if (isTriangular(seq[i]))
                outputFile << seq[i] << " ";
        }
        outputFile << -1;
    }
    outputFile.close();
}

bool isGrowing(const tBooleanSeq seq)
{
    bool grow = true;
    for (int i = 0; i < Length; i++)
    {
        if (!seq[i])
            grow = false;
    }
    return grow;
}