#pragma once
#include <vector>
#include <iostream>
class Vector
{
private:
    std::vector<float> data;
public:
    Vector() = default;
    Vector(size_t size);
    Vector(size_t size, float value);
    Vector(const Vector &toCopy) = default;
    Vector(const std::vector<float> &toCopy);
    ~Vector() = default;

    float &operator[](size_t index);
    float operator[](size_t index) const;

    void print();
};
