#include "Layer.hpp"

void Layer::setTraining(bool training) {
    _training = training;
};

bool Layer::getTraining() {
    return _training;
};

std::vector<Tensor*> Layer::getParameters() {
    return {};
}

std::vector<Tensor*> Layer::getGradients() {
    return {};
}