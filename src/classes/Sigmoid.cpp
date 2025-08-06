#include "Sigmoid.hpp"

Tensor Sigmoid::forward(const Tensor& input){
    return input.sigmoid();
}
std::unique_ptr<ActivationFunction> Sigmoid::clone() const{
    return std::make_unique<Sigmoid>(*this);
}
std::string Sigmoid::getName() const{
    return "Sigmoid";
}