#pragma once

#include "Layer.hpp"
#include "Loss.hpp"
#include "MSE.hpp"
#include <memory>
#include <vector>


class NeuralNetwork
{
private:
    std::vector<std::unique_ptr<Layer>> _layers;
    std::unique_ptr<Loss> _loss = std::make_unique<MSE>();
public:
    NeuralNetwork() = default;
    ~NeuralNetwork() = default;

    void addLayer(std::unique_ptr<Layer> layer);

    template<typename LayerType, typename... Args> // i'll move it in a tpp file later.
    void emplaceLayer(Args&&... args){
        _layers.push_back(std::make_unique<LayerType>(std::forward<Args>(args)...));
    }

    Tensor forward(const Tensor &input);
    float computeLoss(const Tensor &predictions, const Tensor &target);

    void setLoss(std::unique_ptr<Loss> loss);

    std::vector<Tensor*> getAllParameters();
    std::vector<Tensor*> getAllGradients();

    void print();
};