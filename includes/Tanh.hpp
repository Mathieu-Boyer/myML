#pragma once
#include "ActivationFunction.hpp"
#include <memory>

class Tanh : public ActivationFunction
{
public:
    Tanh() = default;
    ~Tanh() = default;
    Tensor forward(const Tensor& input);
    std::unique_ptr<ActivationFunction> clone() const;
    std::string getName() const;
};
