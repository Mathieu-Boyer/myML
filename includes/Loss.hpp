#include "Tensor.hpp"
#include <string>

class Loss
{
    public:
        virtual ~Loss() = default;
        virtual const std::string getName() const = 0;
        virtual float compute(const Tensor &prediction, const Tensor &target) const = 0;
        virtual Tensor gradient(const Tensor &prediction, const Tensor &target) const = 0;
};

