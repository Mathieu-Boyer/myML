#include "Matrix.hpp"

Matrix::Matrix() : data({}), _columns(0), _rows(0) {}
Matrix::Matrix(size_t rows, size_t columns) : _columns(columns), _rows(rows) {
    data.resize(_rows * _columns);
}

Matrix::Matrix(size_t rows, size_t columns, float value) : _columns(columns), _rows(rows) {
    data.resize(_rows * _columns);
    for (auto& element : data)
        element = value;
}

void Matrix::print(){
    for (size_t i = 0; i < _rows; i++){
        for (size_t j = 0; j < _columns; j++)
            std::cout << data[i * _rows + j] << " ";
        std::cout << "\n";
    }
}