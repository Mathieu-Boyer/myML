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
    Matrix(size_t rows, size_t columns, const std::vector<float> &data);
    Matrix(const Matrix &toCopy) = default;
    ~Matrix() = default;

    float &operator()(size_t rows, size_t columns);
    float operator()(size_t rows, size_t columns) const;

    Matrix operator+(const Matrix &rhs) const;
    Matrix operator-(const Matrix &rhs) const;
    Matrix operator*(const float &rhs) const;
    Matrix operator/(const float &rhs) const;

    Matrix operator*(const Matrix &rhs) const;

    void print();
};

