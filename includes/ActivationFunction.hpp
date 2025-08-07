#pragma once
#include "Tensor.hpp"
#include <string>

class ActivationFunction
{
    protected: 
        Tensor _input;
    public:
        virtual ~ActivationFunction() = default;
        virtual Tensor forward(const Tensor& input) = 0;
        virtual Tensor backward(const Tensor &outGrad) = 0;
        virtual std::unique_ptr<ActivationFunction> clone() const = 0;
        virtual std::string getName() const = 0;
};