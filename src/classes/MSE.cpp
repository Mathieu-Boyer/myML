#include "MSE.hpp"

const std::string MSE::getName() const{
    return "MSE";
}

float MSE::compute(const Tensor &prediction, const Tensor &target) const{
    return ((target - prediction).square().meanFloat());
}

Tensor MSE::gradient(const Tensor &prediction, const Tensor &target) const{
    return ((prediction - target) * (2.f / prediction.size()));
}