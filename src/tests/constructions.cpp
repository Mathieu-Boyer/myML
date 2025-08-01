#include "tests.hpp"

void vectorConstructions(){
    Vector emptyVector;
    Vector zeroVector(10);
    Vector twoVector(10, 2);
    Vector twoVectorCpy(twoVector);
    Vector vectorContentCpy({1,2,3,4,5});

    emptyVector.print();
    zeroVector.print();
    twoVector.print();
    twoVectorCpy.print();
    vectorContentCpy.print();
}