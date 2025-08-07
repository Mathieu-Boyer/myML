#include "BCE.hpp"

const std::string BCE::getName() const{
    return "BCE";
}

float BCE::compute(const Tensor &prediction, const Tensor &target) const{


    Tensor ones = Tensor::ones(prediction.shape());

    Tensor positive_term = (target * prediction.log());
    Tensor negative_term = (ones - target) * ((ones - prediction).log());

    return ((positive_term + negative_term).meanFloat() * -1);
}

Tensor BCE::gradient(const Tensor &prediction, const Tensor &target) const{
    Tensor ones = Tensor::ones(prediction.shape());
    return (((prediction - target) / (prediction * (ones - prediction))) * (1.f/prediction.size()));
}