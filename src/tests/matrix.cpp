#include "tests.hpp"
    void matrixConstruction(){
        Matrix().print();
        Matrix(2, 3).print();
        Matrix(2,3,9).print();
    }


void MatrixAcess(){

    Matrix willChange(2, 3, 9);
    Matrix willNotChange(2, 3);

    // std::cout << willChange(1,2) << "\n";
    willChange(1,2) = 18;


    std::cout << willChange(1,2) << "\n";
    std::cout << willNotChange(1,2) << "\n";

    willChange.print();
}



void MatrixOperations(){

    (Matrix(2,4, 1) - Matrix(2,4, 1)).print();
    (Matrix(2,4, 1) - Matrix(2,4, .5)).print();

    (Matrix(2,4, 1) + Matrix(2,4, 1)).print();
    (Matrix(2,4, 1) + Matrix(2,4, .5)).print();
}

void MatrixScalarOperations(){
    ((Matrix(2,4, 3) * 3) / 3).print();
}

void MatMul(){
    Matrix A(2,4, {1,2,3,4,5,6,8,9});
    Matrix B(3,2, {7,8,9,10,11,12});


    A.print();
    B.print();

    std::cout << "------------\n" ;
    (B * A).print();
}