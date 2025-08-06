#pragma once
#include "ActivationFunction.hpp"
#include <memory>

class Sigmoid : public ActivationFunction
{
public:
    Sigmoid() = default;
    ~Sigmoid() = default;
    Tensor forward(const Tensor& input);
    std::unique_ptr<ActivationFunction> clone() const;
    std::string getName() const;
};
