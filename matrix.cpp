#include "matrix.h"
#include <iomanip>
#include <iostream>

Matrix::Matrix(unsigned int rows, unsigned int cols) : m(rows), n(cols){
    ar = new double * [m];
    for (int i = 0; i<m; i++){
        ar[i] = new double[n]();
    }
}
//we have an object matrix with unsigned(non negative) rows and cols. we take in m and n from the user.
//we allocate memory for m by doing line 6. then the for loop is to assign the number of colomns to each row.
//so that reads row 1 has that many columns, and they should all have the same number of columns, we're just looping
//so that all the rows has all of the same number of columns.

Matrix::Matrix(const Matrix& rhs) : Matrix(rhs.m, rhs.n){
    for (int i = 0; i<m;i++){
        for (int j =0; j< n; j++){
            ar[i][j] = rhs.ar[i][j];
        }
    }
}
//copy constructor

Matrix::~Matrix(){
    for(int i =0; i<m; i++){
        delete[] ar[i];
    }
    delete[] ar;
}
//destructor

int Matrix::getRows() const {return m;}
int Matrix::getCols() const {return n;}
//getters

double& Matrix::at(unsigned int row, unsigned int col){
    return ar[row][col];
}
//at

const double& Matrix::at(unsigned int row, unsigned int col) const{
    return ar[row][col];
}
//at const

Matrix& Matrix::operator=(const Matrix&rhs){
    if(this == &rhs) return *this;

    for(int i = 0; i<m; i++){
        delete[] ar[i];
    }
    delete[] ar;

    m = rhs.m;
    n=rhs.n;
    ar = new double*[m];
    for(int i =0; i<m; i++){
         ar[i] = new double[n];
         for (int j = 0; j<n; j++){
            ar[i][j] = rhs.ar[i][j];
         }
    }
    return * this;
}
//asignment operator

Matrix operator+(const Matrix& m1, const Matrix& m2){
    Matrix result(m1.getRows(), m2.getCols());
    for(int i= 0; i<m1.getRows(); i++){
        for(int j=0; j<m1.getCols(); j++){
            result.at(i, j) = m1.at(i, j)+m2.at(i,j);
        }
    }
    return result;
}
//addition

Matrix operator-(const Matrix& m1, const Matrix& m2){
    Matrix result(m1.getRows(), m2.getCols());
    for(int i= 0; i<m1.getRows(); i++){
        for(int j=0; j<m1.getCols(); j++){
            result.at(i, j) = m1.at(i, j)-m2.at(i,j);
        }
    }
    return result;
}
//subtraction

Matrix operator*(const Matrix& m1, const Matrix& m2){
    Matrix result(m1.getRows(), m2.getCols());
    for(int i= 0; i<m1.getRows(); i++){
        for(int j=0; j<m1.getCols(); j++){
            for(int k =0; k<m1.getCols(); k++){
                result.at(i, j) += m1.at(i, k)*m2.at(k,j);
            }
        }
    }
    return result;
}
//multiplication

Matrix operator*(double scalar, const Matrix& m){
    Matrix result(m.getRows(), m.getCols());
    for(int i = 0; i<m.getRows(); i++){
        for(int j = 0; j<m.getCols(); j++){
            result.at(i,j) = scalar * m.at(i,j);
        }
    }
    return result;
}
//scalar * matrix

Matrix operator*(const Matrix& m, double scalar){
    return scalar *m;
}
//matrix * scalar

std::ostream& operator<<(std::ostream & os, const Matrix& m){
    for (int i =0; i < m.getRows(); i++){
        for(int j = 0; j<m.getCols(); j++){
            os << std::setw(10) << m.at(i,j);
        }
        os << " " << std::endl;
    }
    return os;

}
//output

std::istream& operator >>(std::istream& is, Matrix& m){
    for (int i =0; i < m.getRows(); i++){
        for(int j = 0; j<m.getCols(); j++){
            is >> m.at(i,j);
        }
    }
    return is;
}
//input

