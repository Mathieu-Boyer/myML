#include "Tensor.hpp"

Tensor::Tensor() : _data({}), _shape({}), _strides({}){}

Tensor::Tensor(std::vector<size_t> shape) : _shape(shape){
    resizeData();
    computeStrides();
}

Tensor::Tensor(std::vector<size_t> shape, float value) : _shape(shape){
    resizeData();
    computeStrides();
    fill(value);
}
Tensor::Tensor(std::vector<size_t> shape, const std::vector<float> &data) : _shape(shape){
    std::cout << _shape.size() << std::endl;
    if (shapeProduct() != data.size())
        throw std::logic_error("Inconsistant data for a tensor of this shape.");
    _data = data;
    computeStrides();
}

void Tensor::computeStrides(){
    _strides.resize(_shape.size());
    if (_shape.empty())
        return;

    _strides[_shape.size() - 1] = 1;

    for (int i = (int)_shape.size() - 2; i >= 0; --i) {
        _strides[i] = _strides[i + 1] * _shape[i + 1];
    }
}

void Tensor::resizeData(){
    _data.resize(shapeProduct());
}

void Tensor::fill(float value){
    for (auto &element : _data)
        element = value;
}

size_t Tensor::shapeProduct() const{
    size_t totalElements = 1;
    for (auto &s : _shape)
        totalElements *= s;
    std::cout << "sozecheiuch : " << totalElements << "\n";
    return totalElements;
}

size_t Tensor::stridesProduct() const{
    size_t totalElements = 1;
    for (auto &s : _strides)
        totalElements *= s;
    return totalElements;
}


void printSpaces(size_t num){
    for (size_t i = 0 ; i< num; i ++)
        std::cout << " ";
}

void Tensor::print(size_t nest, size_t index) const{
    if (nest == _shape.size()) {
        std::cout << _data[index] << " ";
        return;
    }

    if (nest != _shape.size() - 1){
        std::cout << "\n";
        printSpaces(nest);
    }
    std::cout << "[";
    for (size_t i = 0; i < _shape[nest]; ++i) {
        size_t new_index = index + i * _strides[nest];
        print(nest + 1, new_index);
    }
    std::cout << "]";
    nest != _shape.size() - 1 ? (printSpaces(nest), std::cout << "],\n") : ( std::cout << "]");
}

void Tensor::print() const{
    print(0,0);
}