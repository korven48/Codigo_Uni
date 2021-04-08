/*
   SUBMITTED BY:  Lucas Vukotic and Iván Gallego
   DATE:          April 4, 2021
*/

#include <iostream>
#include <fstream>
#include <UtilitiesSYS.h>
#include <Matrix.h>

using namespace std;


int main()
{


    return 0;
}

bool load (tMatrixChar &mat, istream &in){
    bool ok = true;
    int height, width;
    in >> height >> width;
    for (int i=0; i < height; i++)
        for (int j=0; j < width; j ++)
            in >> mat.image[i][j];
    return ok;
}

bool operator == (tMatrixChar const &mat1, tMatrixChar const& mat2){
    bool equal = true;
    if (mat1.width != mat2.width || mat1.height != mat2.height)
        equal = false;
    else{
        for (int i=0; i < mat1.height; i++)
            for (int j=0; j < mat1.width; j ++)
                if (mat1.image[i][j] != mat2.image[i][j])
                    equal = false;
    }
    return equal;
}

bool swap(tMatrixChar &mat, tCoor pos1, tCoor pos2);
bool swapR(tMatrixChar &mat, int r1, int r2);
bool swapC(tMatrixChar &mat, int c1, int c2);
bool swapD(tMatrixChar &mat, int d);
bool flipR(tMatrixChar &mat, int r); 
bool flipID(tMatrixChar & mat);