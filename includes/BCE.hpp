#pragma once
#include "Loss.hpp"

class BCE : public Loss
{
    public:
        ~BCE() = default;
        const std::string getName() const override;
        float compute(const Tensor &prediction, const Tensor &target) const override;
        Tensor gradient(const Tensor &prediction, const Tensor &target) const override;
};

