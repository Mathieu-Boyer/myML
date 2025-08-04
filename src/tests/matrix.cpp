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