#include "matrix.h"
#include <stdexcept>

using std::size_t;
using std::vector;

namespace linalg {

Matrix::Matrix(size_t rows, size_t cols) {
    if(rows <= 0 || cols <= 0) throw std::invalid_argument("bruh"); 
    mat = vector<vector<double>>(rows, vector<double>(cols, 0)); 
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> rows) {
    if(rows.size() == 0) throw std::invalid_argument("bruh"); 
    
    for(const auto& row : rows) {
        if((!mat.empty() && row.size() != mat.back().size()) || row.size() == 0) {
           throw std::invalid_argument("cols gotta be same, u know that maine"); 
        } 
        
        mat.push_back({}); 
        for(double col : row) {
           mat.back().push_back(col);  
        }
    } 
}

size_t Matrix::rows() const {
    return mat.size(); 
}

size_t Matrix::cols() const {
    if (mat.empty()) return 0; 
    return mat[0].size();
}

double& Matrix::at(size_t row, size_t col) {
    if(row < 0 || col < 0 || rows() <= row || cols() <= col) {
        throw std::out_of_range("do that shit again"); 
    }
    return mat[row][col]; 
}

double Matrix::at(size_t row, size_t col) const {
    if(row < 0 || col < 0 || rows() <= row || cols() <= col) {
        throw std::out_of_range("do that shit again"); 
    }
    return mat[row][col]; 
}

bool operator==(const Matrix& A, const Matrix& B) {
    size_t m = A.rows(); 
    size_t n = A.cols(); 

    if(m != B.rows() || n != B.cols()) return false; 

    for(size_t r = 0; r < m; r++) {
        for(size_t c = 0; c < n; c++) {
            if(A.at(r, c) != B.at(r, c))  {
               return false; 
            }
        }
    }

    return true;
}

Matrix operator+(const Matrix& A, const Matrix& B) {
    size_t m = A.rows(); 
    size_t n = A.cols(); 
    
    if(m != B.rows() || n != B.cols()) {
        throw std::invalid_argument("bruh");
    }
    
    Matrix res(m, n); 
    for(size_t r = 0; r < m; r++) {
        for(size_t c = 0; c < n; c++) {
            res.at(r, c) = A.at(r, c) + B.at(r, c);
        }
    }
    return res; 
}

Matrix operator-(const Matrix& A, const Matrix& B) {
    size_t m = A.rows(); 
    size_t n = A.cols(); 
    
    if(m != B.rows() || n != B.cols()) {
        throw std::invalid_argument("bruh");
    }
    
    Matrix res(m, n); 
    for(size_t r = 0; r < m; r++) {
        for(size_t c = 0; c < n; c++) {
            res.at(r, c) = A.at(r, c) - B.at(r, c);
        }
    }
    return res; 
}

Matrix operator*(const Matrix& M, double t) {
    size_t m = M.rows();
    size_t n = M.cols(); 
    
    Matrix res(m, n); 
    for(size_t r = 0; r < m; r++) {
        for(size_t c = 0; c < n; c++) {
            res.at(r, c) = M.at(r, c) * t;  
        }
    }
    return res; 
}

Matrix operator*(double t, const Matrix& M) {
    size_t m = M.rows();
    size_t n = M.cols(); 
    
    Matrix res(m, n); 
    for(size_t r = 0; r < m; r++) {
        for(size_t c = 0; c < n; c++) {
            res.at(r, c) = M.at(r, c) * t;  
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
            res.at(c, r) = M.at(r, c);
        }
    }

    return res; 
}

Matrix operator*(const Matrix& A, const Matrix& B) {
    if(A.cols() != B.rows()) {
        throw std::invalid_argument("bruh"); 
    }

    size_t v = A.cols(); 
    size_t m = A.rows(); 
    size_t n = B.cols(); 
    
    Matrix res(m, n); 

    for(size_t i = 0; i < m; i++) {
        for(size_t j = 0; j < n; j++) {
            for(size_t k = 0; k < v; k++) {
               res.at(i, j) += A.at(i, k) * B.at(k, j);  
            }
        } 
    }

    return res; 
}

}
