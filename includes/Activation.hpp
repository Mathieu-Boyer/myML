#pragma once
#include "ActivationFunction.hpp"
#include "Layer.hpp"
#include <string>
#include <memory>

#include "ReLU.hpp"
#include "Tanh.hpp"
#include "Sigmoid.hpp"


class Activation : public Layer
{
private:
    std::unique_ptr<ActivationFunction> _activation;
    
public:
    Activation(std::unique_ptr<ActivationFunction> activation);
    Activation(const Activation& other);
    Activation& operator=(const Activation& other);

    Tensor forward(const Tensor& input) override;
    std::string getName() const;

    static  std::unique_ptr<Activation>relu();
    static  std::unique_ptr<Activation>sigmoid();
    static  std::unique_ptr<Activation>tanh();
};