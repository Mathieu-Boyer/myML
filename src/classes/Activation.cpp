#include "Activation.hpp"

std::unique_ptr<Activation> Activation::relu(){
    return  std::make_unique<Activation>(std::make_unique<ReLU>());
}

std::unique_ptr<Activation> Activation::sigmoid(){
    return  std::make_unique<Activation>(std::make_unique<Sigmoid>());
}

std::unique_ptr<Activation> Activation::tanh(){
    return  std::make_unique<Activation>(std::make_unique<Tanh>());
}

Activation::Activation(std::unique_ptr<ActivationFunction> activation) : _activation(std::move(activation)) {
}

Activation::Activation(const Activation& other) : _activation(other._activation->clone()) {}

Activation& Activation::operator=(const Activation& other) {
    if (&other != this)
        this->_activation = other._activation->clone();
    return *this;
}

Tensor Activation::forward(const Tensor& input) {
    return _activation->forward(input);
}
std::string Activation::getName() const {
    return _activation->getName();
}

