#include "ReLU.hpp"

Tensor ReLU::forward(const Tensor& input){
    return input.relu();
}
std::unique_ptr<ActivationFunction> ReLU::clone() const{
    return std::make_unique<ReLU>(*this);
}
std::string ReLU::getName() const{
    return "ReLU";
}