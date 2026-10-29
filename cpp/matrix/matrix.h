#include <vector> 

using std::vector; 

namespace linalg {

class Matrix {
private: 
    vector<vector<double>> mat; 
public: 
    Matrix(std::size_t rows, std::size_t cols);     
    
    Matrix(std::initializer_list<std::initializer_list<double>> rows); 
    
    size_t rows(); 
    
    size_t cols(); 
    
    double& at(std::size_t row, std::size_t col); 
};

bool operator==(Matrix mat_a, Matrix mat_b); 

Matrix operator+(Matrix mat_a, Matrix mat_b); 

Matrix operator-(Matrix mat_a, Matrix mat_b); 
    
Matrix operator*(Matrix mat, double t); 

Matrix operator*(double m, Matrix mat);

Matrix identity(std::size_t n);

Matrix transpose(Matrix mat); 

double trace(Matrix mat); 
}
