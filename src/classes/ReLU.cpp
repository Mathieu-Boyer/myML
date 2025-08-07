#include "ReLU.hpp"

Tensor ReLU::forward(const Tensor& input){
    _input = input;
    return input.relu();
}

Tensor ReLU::backward(const Tensor& outGrad){
    return outGrad * _input.d_relu();
}

std::unique_ptr<ActivationFunction> ReLU::clone() const{
    return std::make_unique<ReLU>(*this);
}
std::string ReLU::getName() const{
    return "ReLU";
}