#include "Dense.hpp"


// Dense::Dense(size_t inputSize, size_t outputSize) : _inputSize(inputSize), _outputSize(outputSize){

// }

// Tensor Dense::forward(const Tensor &input) {

// }

// void Dense::initWeights(const std::string &init = "xavier"){
//     if (init == "xavier"){
//         float limit = (6 / (_inputSize + _outputSize));
//         _biases = Tensor::random_uniform({_inputSize, _outputSize}, -limit, limit);
//         _biases = Tensor::zeros({_outputSize});
//     }else{
//         throw std::logic_error("Init required is not implemented yet.");
//     }
// }

// std::vector<Tensor*> Dense::getParameters(){

// }

// Tensor &Dense::getWeights(){

// }
// Tensor &Dense::getBiases(){

// }

// const Tensor &Dense::getWeights() const{

// }
// const Tensor &Dense::getBiases() const{

// }