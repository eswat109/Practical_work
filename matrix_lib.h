#ifndef MATRIX_LIB_H_INCLUDED
#define MATRIX_LIB_H_INCLUDED

#include <vector>
using namespace std;

typedef vector<vector<float>> DVECTOR;

struct TMatrix{
    int Height, Width;
    DVECTOR Matrix;
    TMatrix(int _H, int _W, DVECTOR Temp);
};

extern void PrintTMatrix(TMatrix Matr);

extern TMatrix SumTMatrix(TMatrix Matr_1, TMatrix Matr_2);

extern TMatrix MulTMatrix(TMatrix Matr_1, TMatrix Matr_2);

extern TMatrix MulTMatrixConst(TMatrix Matr, float Const);

extern float DetTMatrix(TMatrix Matr);

extern TMatrix InversTMatrix(TMatrix Matr);

#endif // MATRIX_LIB_H_INCLUDED
