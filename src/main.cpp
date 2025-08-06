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
    Tensor test1({1, 2, 3, 4}, { -1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 18,
    19, 20, 21, 22, 23, 24});

    Tensor::random_uniform({2,2,2,2}, -.5, .5).print();
    Tensor::random_normal({2,2,2,2}, -.5, .5).print();
    // test1.abs().print();

    // test1.print();
    // test1.mean().print();
    // .print();
    // std::cout << test1.mean() << "\n";

    // Tensor test2({2, 3, 3, 2}, { 1, 2, 3, 4, 5, 6, 7, 8, 9,
    // 10, 11, 12, 13, 14, 15, 16, 17, 18,
    // 19, 20, 21, 22, 23, 24, 25, 26, 27,
    // 28, 29, 30, 31, 32, 33, 34, 35, 36});

    // for (size_t i = 0; i < 100000;i ++)
    //     test1.matmul(test2);

    // (test + test).print();
    // (test - test).print();
    // (test * test).print();
    // (test / test).print();


    // (test + 1).print();
    // (test - 1).print();
    // (test * 2).print();
    // (test / 2).print();



    return 0;
}
