
#include "Vector.hpp"

Vector::Vector(size_t size){
    data.resize(size);
}

Vector::Vector(size_t size, float value){
    data.resize(size);
    for (auto &component : data){
        component = value;
    }
}

Vector::Vector(const std::vector<float> &toCopy){
    data = toCopy;
}

float &Vector::operator[](size_t index){
    if (index >= data.size())
        throw std::logic_error("The provided index is too high.");
    return data[index];
}

float Vector::operator[](size_t index) const{
    if (index >= data.size())
        throw std::logic_error("The provided index is too high.");
    return data[index];
}

size_t Vector::size() const{
    return data.size();
}


Vector Vector::operator+(const Vector& rhs){
    if (this->size() != rhs.size())
        throw std::logic_error("Vector sizes do not match.");

    Vector newVector(*this);
    for (size_t i = 0; i < this->size(); ++i){
        newVector[i] += rhs[i];
    }
    return newVector;
}
Vector Vector::operator-(const Vector& rhs){
    if (this->size() != rhs.size())
        throw std::logic_error("Vector sizes do not match.");

    Vector newVector(*this);
    for (size_t i = 0; i < this->size(); ++i){
        newVector[i] -= rhs[i];
    }
    return newVector;
}

Vector Vector::operator*(const float rhs){
    Vector newVector(*this);
    for (size_t i = 0; i < this->size(); ++i){
        newVector[i] *= rhs;
    }
    return newVector;
}

Vector Vector::operator/(const float rhs){
    Vector newVector(*this);
    for (size_t i = 0; i < this->size(); ++i){
        newVector[i] /= rhs;
    }
    return newVector;
}



void Vector::print(){
    std::cout << "[ " ;
    for (auto &component : data){
        std::cout << component << " ";
    }
    std::cout << "]\n";
}