#include "Vector.hpp"
#include "Matrix.hpp"
#include "Dense.hpp"
#include "ReLU.hpp"
#include "Sigmoid.hpp"
#include "Tanh.hpp"
#include "Activation.hpp"
#include "tests.hpp"
#include "MSE.hpp"

int main()
{
    // Tensor input({2, 4}, {
    //     1.0f, -2.0f, 3.0f, -4.0f,
    //     0.5f,  1.0f, -1.5f, 2.0f
    // });

    // Dense dense(4, 3);
    // dense.initWeights("xavier");

    // Tensor output = dense.forward(input);
    // std::cout << "Dense output:" << std::endl;
    // output.print();

    // std::vector<std::unique_ptr<Layer>> activations;
    // activations.push_back(Activation::relu());
    // activations.push_back(Activation::sigmoid());
    // activations.push_back(Activation::tanh());

    // for (auto &activation : activations)
    //     activation->forward(output).print();


}
