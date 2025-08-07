#pragma once
#include "Layer.hpp"
#include "Tensor.hpp"
#include <string>
#include <vector>

class Dense : public Layer
{
    private:
        Tensor _input;

        Tensor _weights;
        Tensor _biases;

        Tensor _WGradients;
        Tensor _BGradients;

        size_t _inputSize;
        size_t _outputSize;
    public:
        Dense(size_t inputSize, size_t outputSize);
        ~Dense() = default;

        Tensor forward(const Tensor &input) override;
        Tensor backward(const Tensor &outGrad) override;
        void initWeights(const std::string &init = "xavier");

        std::vector<Tensor*> getParameters() override;
        std::vector<Tensor*> getGradients() override;

        void computeGradients(const Tensor &outGrad) override;
        Tensor &getWeights();
        Tensor &getBiases();
        const Tensor &getWeights() const;
        const Tensor &getBiases() const;
};

