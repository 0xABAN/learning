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

size_t Matrix::rows() {
    return mat.size(); 
}

size_t Matrix::cols() {
    if (mat.empty()) return 0; 
    return mat[0].size();
}

double& Matrix::at(size_t row, size_t col) {
    if(row < 0 || col < 0 || rows() <= row || cols() <= col) {
        throw std::out_of_range("do that shit again"); 
    }
    return mat[row][col]; 
}

bool operator==(Matrix mat_a, Matrix mat_b) {
    size_t m = mat_a.rows(); 
    size_t n = mat_a.cols(); 

    if(m != mat_b.rows() || n != mat_b.cols()) return false; 

    for(size_t r = 0; r < m; r++) {
        for(size_t c = 0; c < n; c++) {
            if(mat_a.at(r, c) != mat_b.at(r, c))  {
               return false; 
            }
        }
    }

    return true;
}

Matrix operator+(Matrix mat_a, Matrix mat_b) {
    size_t m = mat_a.rows(); 
    size_t n = mat_a.cols(); 
    
    if(m != mat_b.rows() || n != mat_b.cols()) {
        throw std::invalid_argument("bruh");
    }
    
    Matrix res(m, n); 
    for(size_t r = 0; r < m; r++) {
        for(size_t c = 0; c < n; c++) {
            res.at(r, c) = mat_a.at(r, c) + mat_b.at(r, c);
        }
    }
    return res; 
}

Matrix operator-(Matrix mat_a, Matrix mat_b) {
    size_t m = mat_a.rows(); 
    size_t n = mat_a.cols(); 
    
    if(m != mat_b.rows() || n != mat_b.cols()) {
        throw std::invalid_argument("bruh");
    }
    
    Matrix res(m, n); 
    for(size_t r = 0; r < m; r++) {
        for(size_t c = 0; c < n; c++) {
            res.at(r, c) = mat_a.at(r, c) - mat_b.at(r, c);
        }
    }
    return res; 
}

Matrix operator*(Matrix mat_a, double t) {
    size_t m = mat_a.rows();
    size_t n = mat_a.cols(); 
    
    Matrix res(m, n); 
    for(size_t r = 0; r < m; r++) {
        for(size_t c = 0; c < n; c++) {
            res.at(r, c) = mat_a.at(r, c) * t;  
        }
    }
    return res; 
}

Matrix operator*(double t, Matrix mat_a) {
    size_t m = mat_a.rows();
    size_t n = mat_a.cols(); 
    
    Matrix res(m, n); 
    for(size_t r = 0; r < m; r++) {
        for(size_t c = 0; c < n; c++) {
            res.at(r, c) = mat_a.at(r, c) * t;  
        }
    }
    return res; 
}

Matrix transpose(Matrix mat) {
    size_t m = mat.rows();
    size_t n = mat.cols(); 
    Matrix res(n, m); 

    for(size_t r = 0; r < m; r++) {
        for(size_t c = 0; c < n; c++) {
            res.at(c, r) = mat.at(r, c);
        }
    }

    return res; 
}

Matrix operator*(Matrix mat_a, Matrix mat_b) {
    if(mat_a.cols() != mat_b.rows()) {
        throw std::invalid_argument("bruh"); 
    }

    size_t v = mat_a.cols(); 
    size_t m = mat_a.rows(); 
    size_t n = mat_b.cols(); 
    
    Matrix res(m, n); 

    for(size_t i = 0; i < m; i++) {
        for(size_t j = 0; j < n; j++) {
            for(size_t k = 0; k < v; k++) {
               res.at(i, j) += mat_a.at(i, k) * mat_b.at(k, j);  
            }
        } 
    }

    return res; 
}

}
