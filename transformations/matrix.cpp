#include <string.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "matrix.h"

const double epsilon = 0.000001;

using std::setw;
using std::cout;
using std::endl;

Matrix::Matrix(int m, int n)
{
    this->m = m;
    this->n = n;
    tab = new double *[m];
    for(int i=0; i<m; ++i)
    {
        tab[i] = new double [n];
        for(int j=0; j<n; ++j)
        {
            tab[i][j]=0;
        }
    }
}

Matrix::Matrix(double *t, int m, int n)
{
    this->m = m;
    this->n = n;
    tab = new double *[m];
    for(int i=0; i<m; ++i)
    {
        tab[i] = new double [n];
        for(int j=0; j<n; ++j)
        {
            tab[i][j]=t[i*this->n+j];
        }
    }
}

Matrix::Matrix(const Matrix &mat)
{
    m = mat.m;
    n = mat.n;
    tab = new double *[m];
    for(int i=0; i<m; ++i)
    {
        tab[i] = new double [n];
        memcpy(tab[i], mat.tab[i], n*sizeof(double));
    }
}

void print_matrix(const Matrix &m)
{
    for(int i=0; i<m.m; ++i)
    {
        cout<<"| ";
        for(int j=0; j<m.n; ++j)
        {
            if(m.tab[i][j]>0) cout<<" ";
            if(j<m.n-1) cout<<setw(5)<<m.tab[i][j]<<"\t";
            else cout<<setw(5)<<m.tab[i][j];
        }
        cout<<" |"<<endl;
    }
}

Matrix Matrix::operator+(const Matrix &mat)
{
    if(this->m != mat.m  || this->n != mat.n)
        throw Exception_add();
    else
    {
        double tab1[this->m*this->n];
        for(int i=0; i<this->m; ++i)
        {
            for(int j=0; j<this->n; ++j)
            {
                tab1[i*this->n+j]=this->tab[i][j]+mat.tab[i][j];
            }
        }
        Matrix new_matrix(tab1, this->m, this->n);
        return new_matrix;
    }
}

Matrix Matrix::operator-(const Matrix &mat)
{
    if(this->m != mat.m  || this->n != mat.n)
        throw Exception_subtract();
    else
    {
        double tab[this->m*this->n];
        for(int i=0; i<this->m; ++i)
        {
            for(int j=0; j<this->n; ++j)
            {
                tab[i*this->n+j]=(this->tab[i][j])-mat.tab[i][j];
            }
        }
        Matrix new_matrix(tab, this->m, this->n);

        return new_matrix;
    }
}

Matrix Matrix::operator*(const Matrix &mat)
{
    if(this->n!=mat.m)
        throw Exception_multiply();
    else
    {
        double tab[this->m*mat.n];
        double s;
        for(int i=0; i<this->m; i++)
        {
            for(int j=0; j<mat.n; j++)
            {
                s = 0;
                for(int k=0; k<this->n; k++)
                    s+=this->tab[i][k] * mat.tab[k][j];
                tab[i*mat.n+j]=s;
            }
        }

        Matrix new_matrix(tab, this->m, mat.n);
        return new_matrix;
    }
}

Matrix Matrix::operator*(double scalar)
{
    double tab[this->m*this->n];
    for(int i=0; i<this->m; ++i)
    {
        for(int j=0; j<this->n; ++j)
        {
            tab[i*this->n+j]=(this->tab[i][j])*scalar;
        }
    }

    Matrix new_matrix(tab, this->m, this->n);

    return new_matrix;
}

Matrix Matrix::operator/(double scalar)
{
    if(scalar == 0)
        throw Exception_subtract();
    else
    {
        return (*this)*(1/scalar);
    }
}

bool Matrix::operator==(const Matrix &mat)
{
    if(m!=mat.m || n!=mat.n)
        return false;
    else
    {
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(tab[i][j]!=mat.tab[i][j]) return false;
            }
        }
        return true;
    }
}

bool Matrix::operator!=(const Matrix &mat)
{
    return !((*this)==mat);
}

Matrix& Matrix::operator=(const Matrix &mat)
{
    for(int i=0; i<m; ++i)
    {
        delete [] tab[i];
    }
    delete [] tab;

    m = mat.m;
    n = mat.n;
    tab = new double *[m];
    for(int i=0; i<m; ++i)
    {
        tab[i] = new double [n];
        memcpy(tab[i], mat.tab[i], sizeof(double)*n);
    }
    return *this;
}

double Matrix::determinant()
{
    if(this->n!=this->m)
        throw -1;
    else
    {
        Matrix temp(*this);
        double scalar;
        for(int k=0; k<n-1; ++k)
        {
            for(int i=k+1; i<n; ++i)
            {
                if(fabs(temp.tab[i][k]/temp.tab[k][k])<epsilon)
                    continue;
                scalar=temp.tab[i][k]/temp.tab[k][k];
                for(int j=k; j<m; ++j)
                {
                    temp.tab[i][j]=temp.tab[i][j]-temp.tab[k][j]*scalar;
                }
            }
        }
        double det=1;
        for(int i=0; i<n; ++i)
            det*=temp.tab[i][i];

        return det;
    }
}

Matrix Matrix::transposition()
{
    double tab1[m*n];
    for(int i=0; i<m; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            tab1[i*m+j]=tab[j][i];
        }
    }

    Matrix new_matrix(tab1, m, n);

    return new_matrix;
}

double Matrix::get_el(int _m, int _n)
{
    if(_m-1>m || _n-1>n || _m<1 || _n<1)
        throw Exception_getset();
    else
        return tab[_m-1][_n-1];
}

void Matrix::set_el(int _m, int _n, double val)
{
    if(_m-1>m || _n-1>n || _m<1 || _n<1)
        throw Exception_getset();
    else
        tab[_m-1][_n-1]=val;
}

Matrix::~Matrix()
{
    for(int i=0; i<m; ++i)
    {
        delete [] tab[i];
    }
    delete [] tab;
}
