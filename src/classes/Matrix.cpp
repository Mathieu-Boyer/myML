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
            std::cout << data[i * _columns + j] << " ";
        std::cout << "\n";
    }
}


float &Matrix::operator()(size_t x, size_t y){
    if (x >= _rows)
        throw std::logic_error("Row index is out of range.");
    if (y >= _columns)
        throw std::logic_error("Column index is out of range.");

    return (data[x * _columns + y]);
}

float Matrix::operator()(size_t x, size_t y) const{
    if (x >= _rows)
        throw std::logic_error("Row index is out of range.");
    if (y >= _columns)
        throw std::logic_error("Column index is out of range.");

    return (data[x * _columns + y]);
}