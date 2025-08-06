#include "Dense.hpp"


Dense::Dense(size_t inputSize, size_t outputSize) : _inputSize(inputSize), _outputSize(outputSize){

}

Tensor Dense::forward(const Tensor &input) {
    return input.matmul(_weights) + _biases.reshape({1, _biases.shape()[0]});
}

void Dense::initWeights(const std::string &init){
    if (init == "xavier"){
        float limit = std::sqrt((6.f / (_inputSize + _outputSize)));
        _weights = Tensor::random_uniform({_inputSize, _outputSize}, -limit, limit);
        _biases = Tensor::zeros({_outputSize});
    }else{
        throw std::logic_error("Init required is not implemented yet.");
    }
}

std::vector<Tensor*> Dense::getParameters(){
    return {&_weights, &_biases};
}

Tensor &Dense::getWeights(){
    return _weights;
}
Tensor &Dense::getBiases(){
    return _biases;
}

const Tensor &Dense::getWeights() const{
    return _weights;
}
const Tensor &Dense::getBiases() const{
    return _biases;
}