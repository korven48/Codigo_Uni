/*
   SUBMITTED BY:  Lucas Vukotic and Iván Gallego
   DATE:          April 4, 2021
*/

#include <iostream>
#include <fstream>
// #include <UtilitiesSYS>

using namespace std;

const int DIM_MAX = 64;

typedef unsigned char tImageRow[DIM_MAX];
typedef tImageRow tImage[DIM_MAX];

struct tMatrixChar{
    int width;
    int height;

};


int menu();
bool load (tMatrixChar &mat, istream &in);
bool operator == (tMatrixChar const& mat1, tMatrixChar const& mat2);
bool swap(tMatrixChar &mat, tCoor pos1, tCoor pos2);
bool swapR(tMatrixChar &mat, int r1, int r2);
bool swapC(tMatrixChar &mat, int c1, int c2);
bool swapD(tMatrixChar &mat, intd);
bool flipR(tMatrixChar &mat, int r); 
bool flipID(tMatrixChar & mat);

int main()
{
    int version;
    string name;
    version = menu();
    cout << "Name of the file without the extension" << endl;
    cout << "Name: ";
    cin >> name;
    load(version, name);
    switch (version)
    {
    case 1:
        break;
    case 2:
        break;
    }


    return 0;
}

