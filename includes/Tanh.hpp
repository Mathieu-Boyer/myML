#pragma once
#include "ActivationFunction.hpp"
#include <memory>

class Tanh : public ActivationFunction
{
    private : 
        Tensor tanhOutput;
    public:
        Tanh() = default;
        ~Tanh() = default;
        Tensor forward(const Tensor& input);
        Tensor backward(const Tensor &outGrad);
        std::unique_ptr<ActivationFunction> clone() const;
        std::string getName() const;
};
