#pragma once
#include "ActivationFunction.hpp"
#include <memory>

class ReLU : public ActivationFunction
{
public:
    ReLU() = default;
    ~ReLU() = default;
    Tensor forward(const Tensor& input);
    std::unique_ptr<ActivationFunction> clone() const;
    std::string getName() const;
};
