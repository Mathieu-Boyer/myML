#pragma once

#include "Tensor.hpp"

class Layer
{
    protected:
        bool _training = true;

    public:
        virtual ~Layer() = default;
        virtual Tensor forward(const Tensor &input) = 0;
        virtual void setTraining(bool training);
        virtual bool getTraining();

        virtual std::vector<Tensor*> getParameters();
        virtual std::vector<Tensor*> getGradients();
};

