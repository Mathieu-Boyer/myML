#include "Tanh.hpp"

Tensor Tanh::forward(const Tensor& input){
    tanhOutput = input.tanh();
    return tanhOutput;
}

Tensor Tanh::backward(const Tensor& outGrad) {
    return outGrad * (Tensor::ones(tanhOutput.shape()) - tanhOutput.square());
}
std::unique_ptr<ActivationFunction> Tanh::clone() const{
    return std::make_unique<Tanh>(*this);
}
std::string Tanh::getName() const{
    return "Tanh";
}