#include "NeuralNetwork.hpp"

void NeuralNetwork::addLayer(std::unique_ptr<Layer> layer){
    _layers.push_back(std::move(layer));
}

Tensor NeuralNetwork::forward(const Tensor &input){
    Tensor current = input;

    for (auto &layer : _layers)
        current = layer->forward(current);

    return current;
}

float NeuralNetwork::computeLoss(const Tensor &predictions, const Tensor &target){
    return _loss->compute(predictions, target);
}

void NeuralNetwork::setLoss(std::unique_ptr<Loss> loss){
    _loss = std::move(loss);
}

std::vector<Tensor*> NeuralNetwork::getAllParameters(){
    std::vector<Tensor*> paramsList;
    for (auto& layer : _layers){
        std::vector<Tensor*> layerParams = layer->getParameters();
        paramsList.insert(paramsList.end(), layerParams.begin(), layerParams.end());
    }

    return paramsList;
}
std::vector<Tensor*> NeuralNetwork::getAllGradients(){
    std::vector<Tensor*> gradList;
    for (auto& layer : _layers){
        std::vector<Tensor*> layerGrad = layer->getGradients();
        gradList.insert(gradList.end(), layerGrad.begin(), layerGrad.end());
    }

    return gradList;
}

void NeuralNetwork::print(){
    std::cout << "Number of layers : " << _layers.size() << "\n";
}