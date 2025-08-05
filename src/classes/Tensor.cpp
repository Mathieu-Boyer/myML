#include "Tensor.hpp"


Tensor Tensor::vector(size_t size, float fill){
    return Tensor({size}, fill);
}
Tensor Tensor::matrix(size_t rows, size_t columns, float fill){
    return Tensor({rows, columns}, fill);
}
Tensor Tensor::zeros(const std::vector<size_t>& shape){
    return Tensor(shape, 0);
}
Tensor Tensor::ones(const std::vector<size_t>& shape){
    return Tensor(shape, 1);
}
Tensor Tensor::identity(size_t size){
    Tensor identity({size, size}, 0);

    for (size_t i = 0; i < size; i++)
        identity(i,i) = 1;
    return identity;
} //i'll do this one when i will have element acessors.


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

    nest != _shape.size() - 1 ? (printSpaces(nest), std::cout << "],\n") : ( std::cout << "]");
}


size_t Tensor::ndim() const{
    return _shape.size();
}

void Tensor::print() const{
    std::cout << "Shape : [ ";
    for (auto &s : _shape)
        std::cout << s << " ";
    std::cout << "]\n";

    print(0,0);
}

bool Tensor::isVector() const{
    return _shape.size() == 1;
}

bool Tensor::isMatrix() const{
    return _shape.size() == 2;
}

float &Tensor::operator()(const size_t index){
    if (index >= _data.size())
        throw std::logic_error("Index provided is out of range.");
    return(_data[index]);
}
float Tensor::operator()(const size_t index) const{
    if (index >= _data.size())
        throw std::logic_error("Index provided is out of range.");
    return(_data[index]);
}

float &Tensor::operator()(size_t rows, size_t columns){
    if (!this->isMatrix())
        throw std::logic_error("Current tensor is not a matrix.");
    if (rows >= this->_shape[0])
        throw std::logic_error("Row provided is out of range.");
    if (columns >= this->_shape[0])
        throw std::logic_error("Column provided is out of range.");
    return(_data[rows * _strides[0] + columns]);
}
float Tensor::operator()(size_t rows, size_t columns) const{
    if (!this->isMatrix())
        throw std::logic_error("Current tensor is not a matrix.");
    if (rows >= this->_shape[0])
        throw std::logic_error("Row provided is out of range.");
    if (columns >= this->_shape[0])
        throw std::logic_error("Column provided is out of range.");
    return(_data[rows * _strides[0] + columns]);
}

bool Tensor::indicesOutOfBound(const std::vector<size_t> &indices) const{
    for (size_t i = 0; i < indices.size(); i++){
        if (indices[i] >= _shape[i]){
            return true;
        }

    }
    return false;
}

float &Tensor::operator()(std::vector<size_t> indices){

    if (indicesOutOfBound(indices))
        throw std::logic_error("provided is out of range.");

    size_t index = 0;
    for (size_t i = 0; i < indices.size(); i++)
        index += indices[i] * _strides[i];
    return(_data[index]);
}

float Tensor::operator()(std::vector<size_t> indices) const{

    if (indicesOutOfBound(indices))
        throw std::logic_error("provided is out of range.");

    size_t index = 0;
    for (size_t i = 0; i < indices.size(); i++)
        index += indices[i] * _strides[i];
    return(_data[index]);
}