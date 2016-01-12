//
// Created by gilovi on 1/12/16.
//

#ifndef CPP3_NONSQUAREMATRIXEXCEPTION_HPP
#define CPP3_NONSQUAREMATRIXEXCEPTION_HPP
#include "MatrixException.hpp"
#include <iostream>
using namespace std;

class NonSquareMatrixException: public MatrixException
{
public:

    /**
    * constructor.
    * builds the error message for a given operator
    */
    NonSquareMatrixException(string operatr)
    {
        this->_msg = "cannot preform operation \"" + operatr + "\" because matrix is not square";
    }

};


#endif //CPP3_NONSQUAREMATRIXEXCEPTION_HPP
