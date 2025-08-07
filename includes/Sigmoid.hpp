#pragma once
#include "ActivationFunction.hpp"
#include <memory>

class Sigmoid : public ActivationFunction
{
    private: 
        Tensor sigmoidOutput;
    public:
        Sigmoid() = default;
        ~Sigmoid() = default;
        Tensor forward(const Tensor& input);
        Tensor backward(const Tensor &outGrad);
        std::unique_ptr<ActivationFunction> clone() const;
        std::string getName() const;
};
