#pragma once

#include <cstddef>
#include <initializer_list>
#include <vector>

namespace linalg {

class Matrix {
private: 
    std::vector<std::vector<double>> mat; 
public: 
    Matrix(std::size_t rows, std::size_t cols);     
    
    Matrix(std::initializer_list<std::initializer_list<double>> rows); 
    
    std::size_t rows() const; 
    
    std::size_t cols() const; 
    
    double& at(std::size_t row, std::size_t col); 

    double at(std::size_t row, std::size_t col) const; 
    
    Matrix& operator+=(const Matrix& B); 

    Matrix& operator-=(const Matrix& B);

    Matrix& operator*=(double t); 
};

bool operator==(const Matrix& A, const Matrix& B); 

Matrix operator+(const Matrix& A, const Matrix& B); 

Matrix operator-(const Matrix& A, const Matrix& B); 

Matrix operator*(const Matrix& M, double t); 

Matrix operator*(double t, const Matrix& M);

Matrix operator*(const Matrix& A, const Matrix& B); 

Matrix transpose(const Matrix& M); 
}
