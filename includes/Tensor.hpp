#pragma once

#include <vector>
#include <iostream>

class Tensor
{
private:
    std::vector<float> _data;
    std::vector<size_t> _shape;
    std::vector<size_t> _strides;
    void computeStrides();
    void resizeData();

    size_t shapeProduct() const;
    size_t stridesProduct() const;


    void print(size_t nest, size_t index) const;
    bool indicesOutOfBound(const std::vector<size_t> &indices) const;

public:
    Tensor();
    Tensor(std::vector<size_t> shape);
    Tensor(std::vector<size_t> shape, float value);
    Tensor(std::vector<size_t> shape, const std::vector<float> &data);
    Tensor(const Tensor &toCopy) = default;
    ~Tensor() = default;



    // ------------ Operators -------------- //
    float &operator()(const size_t index);
    float operator()(const size_t index) const;
    float &operator()(size_t rows, size_t columns);
    float operator()(size_t rows, size_t columns) const;
    float &operator()(std::vector<size_t> indices);
    float operator()(std::vector<size_t> indices) const;

    Tensor operator+(const Tensor &rhs) const;
    Tensor operator-(const Tensor &rhs) const;
    Tensor operator*(const Tensor &rhs) const;
    Tensor operator/(const Tensor &rhs) const;


    Tensor operator+(const float &rhs) const;
    Tensor operator-(const float &rhs) const;
    Tensor operator*(const float &rhs) const;
    Tensor operator/(const float &rhs) const;


    // ------------ Memberfunctions -------- //

    void fill(float value);
    void print() const;
    size_t ndim() const;
    bool isVector() const;
    bool isMatrix() const;

    // ------------ Statics ---------------- //
    static Tensor vector(size_t size, float fill = 0.0f);
    static Tensor matrix(size_t rows, size_t cols, float fill = 0.0f);
    static Tensor zeros(const std::vector<size_t>& shape);
    static Tensor ones(const std::vector<size_t>& shape);
    static Tensor identity(size_t size);
};

