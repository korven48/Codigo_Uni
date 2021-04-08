#include <iostream>
#include <fstream>
#include <Coordinates.h>

using namespace std;

const int DIM_MAX = 64;

typedef unsigned char tImageRow[DIM_MAX];
typedef tImageRow tImage[DIM_MAX];

struct tMatrixChar{
    int width;
    int height;
    tImage image;
};

bool load (tMatrixChar &mat, istream &in);
bool operator == (tMatrixChar const &mat1, tMatrixChar const& mat2);
bool swap(tMatrixChar &mat, tCoor pos1, tCoor pos2);
bool swapR(tMatrixChar &mat, int r1, int r2);
bool swapC(tMatrixChar &mat, int c1, int c2);
bool swapD(tMatrixChar &mat, int d);
bool flipR(tMatrixChar &mat, int r); 
bool flipID(tMatrixChar & mat);