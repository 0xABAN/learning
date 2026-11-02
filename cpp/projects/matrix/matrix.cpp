#include "matrix.h"
#include <stdexcept>

using std::size_t;
using std::vector;

namespace linalg {

Matrix::Matrix(size_t rows, size_t cols) {
    if(rows <= 0 || cols <= 0) throw std::invalid_argument("bruh"); 

    m_ = rows; 
    n_ = cols; 
    size_ = m_ * n_; 
    
    mat = vector<double>(rows * cols, 0); 
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> rows) {
    if(rows.size() == 0) throw std::invalid_argument("matrices are undefined for size 0x0"); 
    
    m_ = rows.size(); 
    n_ = rows.begin()->size(); 
    size_ = m_ * n_; 
    
    for(const auto& row : rows) {
        if(row.size() != n_ || row.size() == 0) {
            throw std::invalid_argument("initializer list size not constant across rows");
        }
            
        for(double num : row) {
            mat.push_back(num);
        } 
    }
}

size_t Matrix::rows() const {
    return m_; 
}

size_t Matrix::cols() const {
    return n_; 
}

size_t Matrix::size() const {
    return size_;
}

double* Matrix::operator[](size_t row) {
    return &mat[row * n_]; 
}

const double* Matrix::operator[](size_t row) const {
    return &mat[row * n_];
}

bool operator==(const Matrix& A, const Matrix& B) {
    if(A.rows() != B.rows() || A.cols() != B.cols()) return false; 
    
    for(size_t i = 0; i < A.size(); i++) {
        // M[row] returns the first item in row, so A[0] lets us access the first item of the matrix. 
        if(A[0][i] != B[0][i]) return false; 
    }    
    return true;
}

Matrix& Matrix::operator+=(const Matrix& B) {    
    if(m_ != B.rows() || n_ != B.cols()) {
        throw std::invalid_argument("matrices need to be same size");
    }
    
    for(size_t i = 0; i < size_; i++) {
        mat[i] += B.mat[i]; 
    }

    return *this; 
}

Matrix operator+(const Matrix& A, const Matrix& B) {
    Matrix res = A; 
    return res += B; 
}

Matrix& Matrix::operator-=(const Matrix& B) {
    if(m_ != B.rows() || n_ != B.cols()) {
        throw std::invalid_argument("matrices need to be same size"); 
    }

    for(size_t i = 0; i < size_; i++) {
        mat[i] -= B.mat[i];     
    }
    
    return *this; 
}

Matrix operator-(const Matrix& A, const Matrix& B) {
    Matrix res = A; 
    return res -= B; 
}

Matrix& Matrix::operator*=(double t) {
    for(size_t i = 0; i < size_; i++) {
        mat[i] *= t; 
    } 
    return *this; 
}

Matrix operator*(const Matrix& M, double t) {
    Matrix res = M; 
    return res *= t; 
}

Matrix operator*(double t, const Matrix& M) {
    Matrix res = M; 
    return res *= t; 
}

Matrix operator*(const Matrix& A, const Matrix& B) {
    if(A.cols() != B.rows()) {
        throw std::invalid_argument("bruh"); 
    }

    size_t m = A.rows(); 
    size_t n = B.cols(); 
    size_t t = B.rows(); 
    
    Matrix res(m, n); 
    for(size_t i = 0; i < m; i++) {
        for(size_t k = 0; k < t; k++) { 
            for(size_t j = 0; j < n; j++) { 
               res[i][j] += A[i][k] * B[k][j];  
            }
        } 
    }
    
    return res; 
}

Matrix transpose(const Matrix& M) {
    size_t m = M.rows();
    size_t n = M.cols(); 
    Matrix res(n, m); 

    for(size_t r = 0; r < m; r++) {
        for(size_t c = 0; c < n; c++) {
            res[c][r] = M[r][c];
        }
    }

    return res; 
}

}

