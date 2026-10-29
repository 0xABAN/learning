#include "matrix.h"
#include <stdexcept>

using std::vector; 

namespace linalg {

Matrix::Matrix(std::size_t rows, std::size_t cols) {
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

double& Matrix::at(std::size_t row, std::size_t col) {
    if(row < 0 || col < 0 || rows() <= row || cols() <= col) {
        throw std::out_of_range("do that shit again"); 
    }
    return mat[row][col]; 
}

bool operator==(Matrix mat_a, Matrix mat_b) {
    std::size_t m = mat_a.rows(); 
    std::size_t n = mat_a.cols(); 

    if(m != mat_b.rows() || n != mat_b.cols()) return false; 

    for(std::size_t r = 0; r < m; r++) {
        for(std::size_t c = 0; c < n; c++) {
            if(mat_a.at(r, c) != mat_b.at(r, c))  {
               return false; 
            }
        }
    }

    return true;
}

Matrix operator+(Matrix mat_a, Matrix mat_b) {
    std::size_t m = mat_a.rows(); 
    std::size_t n = mat_a.cols(); 
    
    if(m != mat_b.rows() || n != mat_b.cols()) {
        throw std::invalid_argument("bruh");
    }
    
    Matrix res(m, n); 
    for(std::size_t r = 0; r < m; r++) {
        for(std::size_t c = 0; c < n; c++) {
            res.at(r, c) = mat_a.at(r, c) + mat_b.at(r, c);
        }
    }
    return res; 
}

Matrix operator-(Matrix mat_a, Matrix mat_b) {
    std::size_t m = mat_a.rows(); 
    std::size_t n = mat_a.cols(); 
    
    if(m != mat_b.rows() || n != mat_b.cols()) {
        throw std::invalid_argument("bruh");
    }
    
    Matrix res(m, n); 
    for(std::size_t r = 0; r < m; r++) {
        for(std::size_t c = 0; c < n; c++) {
            res.at(r, c) = mat_a.at(r, c) - mat_b.at(r, c);
        }
    }
    return res; 
}

Matrix operator*(Matrix mat_a, double t) {
    std::size_t m = mat_a.rows();
    std::size_t n = mat_a.cols(); 
    
    Matrix res(m, n); 
    for(std::size_t r = 0; r < m; r++) {
        for(std::size_t c = 0; c < n; c++) {
            res.at(r, c) = mat_a.at(r, c) * t;  
        }
    }
    return res; 
}

Matrix operator*(double t, Matrix mat_a) {
    std::size_t m = mat_a.rows();
    std::size_t n = mat_a.cols(); 
    
    Matrix res(m, n); 
    for(std::size_t r = 0; r < m; r++) {
        for(std::size_t c = 0; c < n; c++) {
            res.at(r, c) = mat_a.at(r, c) * t;  
        }
    }
    return res; 
}

Matrix identity(std::size_t n) {
    Matrix mat(n, n); 
    
    for(std::size_t i = 0; i < n; i++) {
        mat.at(i, i) = 1;  
    }
    
    return mat; 
}

Matrix transpose(Matrix mat) {
    std::size_t m = mat.rows();
    std::size_t n = mat.cols(); 
    Matrix res(n, m); 

    for(std::size_t r = 0; r < m; r++) {
        for(std::size_t c = 0; c < n; c++) {
            res.at(c, r) = mat.at(r, c);
        }
    }

    return res; 
}

double trace(Matrix mat) {
    std::size_t n = mat.rows();
    if(n != mat.cols()) {
        throw std::invalid_argument("dont u know traces require square matrices??"); 
    }
    
    double ans = 0; 
    for(std::size_t i = 0; i < n; i++) {
        ans += mat.at(i, i);  
    } 
    return ans; 
}

}
