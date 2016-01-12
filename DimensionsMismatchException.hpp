//
// Created by gilovi on 1/12/16.
//

#ifndef CPP3_DIMENSIONSMISMATCHEXCEPTION_HPP
#define CPP3_DIMENSIONSMISMATCHEXCEPTION_HPP
#include <exception>
#include "MatrixException.hpp"

#include <iostream>
#include "MatrixException.hpp"

using namespace std;

class DimensionsMismatchException : public MatrixException
{

public:
    /**
    * constructor.
    * builds the error message for a given operator
    */
    DimensionsMismatchException(string operatr)
    {
        this->_msg = "can't use \"" + operatr + "\" with given inputs. dimensions mismatch";
    }
};


#endif //CPP3_DIMENSIONSMISMATCHEXCEPTION_HPP
