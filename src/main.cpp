#include "Vector.hpp"
#include "Matrix.hpp"

#include "tests.hpp"

int main()
{
    // -------- vectors ----------
    // vectorConstructions();
    // vectorIndexAcess();
    // vectorSizes();
    // vectorOperators();

    // dot();
    // norm();
    // normalize();

    // -------- matrices ----------
    // matrixConstruction();
    // MatrixAcess();
    // MatrixOperations();
    // MatrixScalarOperations();
    // MatMul();

    // -------- tensors ----------
    // tensorConstructions();
    // tensorStatics();

    // Tensor::identity(2).print();
    Tensor test({1,2,3}, {1,2,3,4,5,6});
    test.print();
    std::cout << (test({0,0,0})) << "\n";
    return 0;
}
