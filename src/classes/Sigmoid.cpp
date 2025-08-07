#include "Sigmoid.hpp"

Tensor Sigmoid::forward(const Tensor& input){
    sigmoidOutput = input.sigmoid();
    return sigmoidOutput;
}

Tensor Sigmoid::backward(const Tensor& outGrad){
    return outGrad * (sigmoidOutput * (Tensor::ones(sigmoidOutput.shape()) - sigmoidOutput));
}
std::unique_ptr<ActivationFunction> Sigmoid::clone() const{
    return std::make_unique<Sigmoid>(*this);
}
std::string Sigmoid::getName() const{
    return "Sigmoid";
}