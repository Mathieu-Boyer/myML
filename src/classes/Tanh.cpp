#include "Tanh.hpp"

Tensor Tanh::forward(const Tensor& input){
    return input.tanh();
}
std::unique_ptr<ActivationFunction> Tanh::clone() const{
    return std::make_unique<Tanh>(*this);
}
std::string Tanh::getName() const{
    return "Tanh";
}