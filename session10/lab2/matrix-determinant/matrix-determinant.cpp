// matrix-determinant.cpp

#include "stdafx.h"

using namespace std;

typedef vector<double> matrix1D;
typedef vector<matrix1D> matrix2D;

matrix2D CreateRandomMatrix(size_t rows, size_t cols)
{
    seed_seq seed{ 2016 };
    default_random_engine generator{ seed };
    uniform_int_distribution<> distribution(-10, 10);

    matrix2D A;
    A.resize(rows, matrix1D(cols));

    for (size_t row{}; row < rows; row++)
        for (size_t col{}; col < cols; col++)
            A.at(row).at(col) = distribution(generator);

    return move(A);
}

void DisplayMatrix(const matrix2D& A)
{
    size_t rowsA = A.size();
    size_t colsA = A[0].size();

    for (size_t row{}; row < rowsA; row++)
    {
        for (size_t col{}; col < colsA; col++)
            cout << setw(5) << A.at(row).at(col);
        cout << endl;
    }
    cout << endl;
}

matrix2D CreateReducedMatrix(const matrix2D& A, size_t skipRow, size_t skipCol)
{
    size_t rowsA = A.size();
    size_t colsA = A.at(0).size();

    matrix2D B(rowsA - 1, matrix1D(colsA - 1, 0));

    size_t rowB{};
    for (size_t rowA{}; rowA < rowsA; rowA++)
    {
        if (rowA == skipRow)
            continue;
        size_t colB{};
        for (size_t colA{}; colA < colsA; colA++)
        {
            if (colA == skipCol)
                continue;
            B[rowB][colB] = A[rowA][colA];
            colB++;
        }
        rowB++;
    }

    return move(B);
}

void CalcDeterminant(const matrix2D& A, double& det, double f = 1)
{
    size_t rowsA = A.size();
    size_t colsA = A[0].size();

    if (rowsA == 2 && colsA == 2)
        det += f * (A[0][0] * A[1][1] - A[0][1] * A[1][0]);
    else
    {
        for (size_t rowA{}; rowA < rowsA; rowA++)
        {
            matrix2D B = CreateReducedMatrix(A, rowA, 0);

            double f2 = A[rowA][0];
            if (rowA % 2 == 1) f2 *= -1;

            CalcDeterminant(B, det, f * f2);
        }
    }
}


int main()
{
    matrix2D A = CreateRandomMatrix(10,10);
    DisplayMatrix(A);

    double det{};
    CalcDeterminant(A, det);

    cout.imbue(std::locale(""));
    cout << fixed << setprecision(4);
    cout << "det = " << det << endl;

    return 0;
}
