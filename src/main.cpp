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
    Tensor test({2, 2, 3, 3}, {    1, 2, 3, 4, 5, 6, 7, 8, 9,
    1, 2, 3, 4, 5, 6, 7, 8, 9,
    1, 2, 3, 4, 5, 6, 7, 8, 9,
    1, 2, 3, 4, 5, 6, 7, 8, 9});
    test.print();
    (test + test).print();
    (test - test).print();
    (test * test).print();
    (test / test).print();


    (test + 1).print();
    (test - 1).print();
    (test * 2).print();
    (test / 2).print();
    return 0;
}
