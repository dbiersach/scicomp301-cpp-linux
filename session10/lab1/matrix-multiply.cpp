// matrix-multiply.cpp

#include "stdafx.h"

using namespace std;

typedef vector<vector<int>> matrix;

// Receiving matrix A by a constant reference assures
// the caller that no changes will be made to the matrix,
// while gaining the performance benefit of not causing
// the copy constructor to be called on the passed in matrix
void DisplayMatrix(const matrix& A)
{
    const size_t rowsA = A.size();
    const size_t colsA = A.at(0).size();

    for (size_t row{}; row < rowsA; row++)
    {
        for (size_t col{}; col < colsA; col++)
            cout << setw(5) << A.at(row).at(col);
        cout << endl;
    }
    cout << endl;
}

matrix MultiplyMatrices(const matrix& A, const matrix& B)
{
    const size_t rowsA = A.size();
    const size_t colsA = A.at(0).size();
    const size_t colsB = B.at(0).size();

    matrix c(rowsA, vector<int>(colsB, 0));

    for (size_t i{}; i < rowsA; ++i)
        for (size_t j{}; j < colsB; ++j)
            for (size_t k{}; k < colsA; ++k)
                c.at(i).at(j) += A.at(i).at(k) * B.at(k).at(j);

    // Normal C++ compiler copy elision would usually avoid an
    // uncessary copy constructor call when returning a local object.
    // Here however we must invoke explicit NRVO via move() as "matrix"
    // is a typedef for a vector of vectors, which will not auto elide
    return move(c);
}


int main()
{
    matrix A{{4,5,8},{1,9,7}};
    matrix B{{2,4},{6,1},{5,9}};
    matrix C = MultiplyMatrices(A, B);

    cout << "Matrix A = " << endl;
    DisplayMatrix(A);

    cout << "Matrix B = " << endl;
    DisplayMatrix(B);

    cout << "Matrix C = " << endl;
    DisplayMatrix(C);

    return 0;
}
