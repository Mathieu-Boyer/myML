#include "Dense.hpp"


Dense::Dense(size_t inputSize, size_t outputSize) : _inputSize(inputSize), _outputSize(outputSize){
    initWeights();
}


Tensor Dense::forward(const Tensor &input) {
    _input = input;

    return input.matmul(_weights) + _biases.reshape({1, _biases.shape()[0]});
}


Tensor Dense::backward(const Tensor &outGrad) {
    computeGradients(outGrad);
    return outGrad.matmul(_weights.transpose());
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

void Dense::computeGradients(const Tensor &outGrad) {
    _WGradients = _input.transpose().matmul(outGrad);
    _BGradients = outGrad.sum(0);
}

std::vector<Tensor*> Dense::getGradients(){
    return {&_WGradients, &_BGradients};
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