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
    Vector(std::initializer_list<float> init);
    ~Vector() = default;

    float &operator[](size_t index);
    float operator[](size_t index) const;

    Vector operator+(const Vector& rhs) const;
    Vector operator-(const Vector& rhs)const;
    Vector operator*(const float rhs)const;
    Vector operator/(const float rhs)const;
    float operator*(const Vector& rhs)const;

    Vector normalize() const;
    float dot(const Vector& rhs) const;
    float norm() const;
    size_t size() const;
    void print();
};
