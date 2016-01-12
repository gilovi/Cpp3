//
// Created by gilovi on 1/12/16.
//

#ifndef CPP3_MATRIXEXCEPTION_HPP
#define CPP3_MATRIXEXCEPTION_HPP

#include <exception>
#include <iostream>
using namespace std;

class MatrixException: public std::exception
{
public:

    /**
   * constructor.
   * builds the error message for a given operator
   */
//    MatrixException(string operatr) ;


    virtual const char* what() const throw()
    {
        return this->_msg.c_str();
    }

protected:
    string _msg;


};


#endif //CPP3_MATRIXEXCEPTION_HPP
