#include "Loss.hpp"

class MSE : public Loss
{
    public:
        ~MSE() = default;
        const std::string getName() const override;
        float compute(const Tensor &prediction, const Tensor &target) const override;
        Tensor gradient(const Tensor &prediction, const Tensor &target) const override;
};

