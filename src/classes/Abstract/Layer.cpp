#include "Layer.hpp"

void Layer::setTraining(bool training) {
    _training = training;
};

bool Layer::getTraining() {
    return _training;
};


void Layer::computeGradients(const Tensor &){
}

std::vector<Tensor*> Layer::getParameters() {
    return {};
}

std::vector<Tensor*> Layer::getGradients() {
    return {};
}