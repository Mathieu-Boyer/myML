#pragma once
#include <vector>
#include <iostream>

class Matrix
{
private:
    std::vector<float> data;
    size_t _columns;
    size_t _rows;
public:
    Matrix();
    Matrix(size_t rows, size_t columns);
    Matrix(size_t rows, size_t columns, float value);
    Matrix(const Matrix &toCopy) = default;
    ~Matrix() = default;

    float &operator()(size_t rows, size_t columns);
    float operator()(size_t rows, size_t columns) const;

    void print();
};

