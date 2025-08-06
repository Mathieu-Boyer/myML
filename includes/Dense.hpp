#pragma once
#include "Layer.hpp"
#include "Tensor.hpp"
#include <string>
#include <vector>

class Dense : public Layer
{
    private:
        // Tensor _weights;
        // Tensor _biases;
        // size_t _inputSize;
        // size_t _outputSize;

    // public:
    //     Dense(size_t inputSize, size_t outputSize);
    //     ~Dense() = default;

    //     Tensor forward(const Tensor &input) override;

    //     void initWeights(const std::string &init = "xavier");

    //     std::vector<Tensor*> getParameters();

    //     Tensor &getWeights();
    //     Tensor &getBiases();

    //     const Tensor &getWeights() const;
    //     const Tensor &getBiases() const;
};

