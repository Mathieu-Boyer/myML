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

void vectorIndexAcess(){
    Vector emptyVector;
    Vector zeroVector1(1);
    const Vector zeroVector2(1);
    std::vector<Vector> vectorsToTest = {emptyVector, zeroVector1, zeroVector2};

    for (auto &vect : vectorsToTest){
        try {
            std::cout << vect[0] << "\n";
        }catch (std::exception &err){
            std::cerr << err.what() << "\n" ;
        }
    }
}

void vectorSizes(){
    Vector emptyVector;
    Vector zeroVector1(1);
    
    std::cout << emptyVector.size() << ", " << zeroVector1.size() << "\n";
}

void vectorOperators(){
    Vector vec1(9, 1);
    Vector vec2({1,2,3,4,5,6,7,8,9});

    vec1.print();
    vec2.print();
    std::cout << "------------------------------------------------------------------------------------\n";

    (vec1 + vec2).print();
    (vec1 - vec2).print();
    (vec1 * 3).print();
    (vec1 / 3).print();
}

void dot(){
    Vector vec1(9, 1);
    Vector vec2({1,2,3,4,5,6,7,8,9});

    std::cout << (vec1 * vec2) << "\n";
}


void norm(){
    Vector vec({0, 0, 7});
    Vector vec2({3, 4});

    std::cout << vec.norm() << "\n";
    std::cout << vec2.norm() << "\n";
}