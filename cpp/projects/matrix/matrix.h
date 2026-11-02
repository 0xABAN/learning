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
    
    std::size_t rows(); 
    
    std::size_t cols(); 
    
    double& at(std::size_t row, std::size_t col); 
};

bool operator==(Matrix mat_a, Matrix mat_b); 

Matrix operator+(Matrix mat_a, Matrix mat_b); 

Matrix operator-(Matrix mat_a, Matrix mat_b); 
    
Matrix operator*(Matrix mat, double t); 

Matrix operator*(double m, Matrix mat);

Matrix operator*(Matrix mat_a, Matrix mat_b); 

Matrix transpose(Matrix mat); 
}
