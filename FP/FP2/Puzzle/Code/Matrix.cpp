/*
   SUBMITTED BY:  Lucas Vukotic and Iván Gallego
   DATE:          April 4, 2021
*/

#include <iostream>
#include <fstream>
#include "UtilitiesSYS.h"
#include "Matrix.h"

using namespace std;

bool load (tMatrixChar &mat, istream &in){
    bool ok = true;
    int height, width;
    in >> height >> width;
    mat.height = height;
    mat.width = width;
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

bool inWidth(tMatrixChar& mat, int x) {
    return (x < mat.width && x >= 0);
}
bool inHeight(tMatrixChar& mat, int y) {
    return (y < mat.height && y >= 0);
}

bool swap(tMatrixChar& mat, tCoor pos1, tCoor pos2) {
    bool correct = inWidth(mat, pos1.x) && inHeight(mat, pos1.y) && inWidth(mat, pos2.x) && inHeight(mat, pos2.y);
    unsigned char pixel;
    if (correct) {
        pixel = mat.image[pos1.y][pos1.x];
        mat.image[pos1.y][pos1.x] = mat.image[pos2.y][pos2.x];
        mat.image[pos2.y][pos2.x] = pixel;
    }
    return correct;
}
bool swapR(tMatrixChar& mat, int r1, int r2) {
    bool correct = inHeight(mat, r1) && inHeight(mat, r2);
    tCoor pos1, pos2;
    if (correct) {
        pos1.y = r1;
        pos2.y = r2;
        for (int x = 0; x < mat.width; x++) {
            pos1.x = pos2.x = x;
            swap(mat, pos1, pos2);
        }
    }
    return correct;
}
bool swapC(tMatrixChar& mat, int c1, int c2) {
    bool correct = inWidth(mat, c1) && inWidth(mat, c2);
    tCoor pos1, pos2;
    if (correct) {
        pos1.x = c1;
        pos2.x = c2;
        for (int y = 0; y < mat.height; y++) {
            pos1.y = pos2.y = y;
            swap(mat, pos1, pos2);
        }
    }
    return correct;
}
bool swapD(tMatrixChar& mat, int d) {
    bool correct = (mat.height == mat.width) && inWidth(mat, d);
    tCoor pos1, pos2, downRight;
    pos1.x = 0;
    pos1.y = d;
    pos2.x = d;
    pos2.y = 0;
    downRight.x = 1;
    downRight.y = 1;
    if (correct) {
        for (int x = 0; x < mat.height - d; x++) {
            swap(mat, pos1, pos2);
            pos1 = pos1 + downRight;
            pos2 = pos2 + downRight;
        }
    }
    return correct;
}
bool flipR(tMatrixChar& mat, int r) {
    bool correct = inHeight(mat, r);
    tCoor pos1, pos2;
    pos1.y = r;
    pos2.y = r;
    for (int x = 0; x < mat.width / 2; x++) {
        pos1.x = x;
        pos2.x = mat.width - x - 1;
        swap(mat, pos1, pos2);
    }
    return correct;
}
bool flipC(tMatrixChar& mat, int c) {
    bool correct = inWidth(mat, c);
    tCoor pos1, pos2;
    pos1.x = c;
    pos2.x = c;
    for (int y = 0; y < mat.height / 2; y++) {
        pos1.y = y;
        pos2.y = mat.height - y - 1;
        swap(mat, pos1, pos2);
    }
    return correct;
}
bool flipD(tMatrixChar& mat, int d) {
    bool correct = (mat.height == mat.width) && inWidth(mat, d);
    int length = mat.height - 1;
    tCoor pos1, pos2, downRight;
    pos1.x = d;
    pos1.y = 0;
    pos2.x = length - pos1.y;
    pos2.y = length - pos1.x;
    downRight.x = 1;
    downRight.y = 1;
    for (int i = 0; i < (mat.height / 2 - d); i++) {
        swap(mat, pos1, pos2);
        pos1 = pos1 + downRight;
        pos2.x = length - pos1.y;
        pos2.y = length - pos1.x;
    }
    return correct;
}
void flipV(tMatrixChar& mat) {

}
void flipH(tMatrixChar& mat) {

}
void rotateR(tMatrixChar& mat) {

}
bool swapAdj(tMatrixChar& mat, tCoor pos1, tCoor pos2) {
    bool correct = false;

    return correct;
}
bool flipID(tMatrixChar& mat) {
    bool correct = false;

    return correct;
}
