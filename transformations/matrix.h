#ifndef MATRIX_H
#define MATRIX_H
#include "exceptions.h"

class Matrix
{
    int m;
    int n;
    double **tab;
public:
    Matrix(int m, int n);
    Matrix(double *t, int m, int n);
    Matrix(const Matrix &mat);
    Matrix operator+(const Matrix &mat);
    Matrix operator-(const Matrix &mat);
    Matrix operator*(const Matrix &mat);
    Matrix operator*(double scalar);
    Matrix operator/(double scalar);
    double determinant();
    Matrix transposition();
    bool operator==(const Matrix &mat);
    bool operator!=(const Matrix &mat);
    Matrix& operator=(const Matrix &mat);
    double get_el(int _m, int _n);
    void set_el(int _m, int _n, double val);
    ~Matrix();
    friend void print_matrix(const Matrix& m);
};

void print_matrix(const Matrix& m);

#endif
