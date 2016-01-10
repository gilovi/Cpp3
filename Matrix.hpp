//
// Created by gilovi on 1/10/16.
//

#ifndef CPP3_MATRIX_HPP
#define CPP3_MATRIX_HPP

#include <vector>
#include <iterator>
#include "Complex.h"


/**
* Generic matrix class.
*/
template<class T>
class Matrix
{
public:
    typedef typename std::vector<T>::const_iterator const_iterator;
    /**
    * Default constructor.
    */
    Matrix<T>() : _rows(1), _cols(1)
    {

    }

    /**
    * Dimensional constructor.
    * @param rows number of rows
    * @param cols number of columns
    */
    Matrix<T>(unsigned int rows, unsigned int cols) : _rows(rows), _cols(cols)
    {

    }

    /**
    * Copy constructor.
    * @param matrixToCopy source matrix
    */
    Matrix<T>(const Matrix<T>& matrixToCopy)
    {
        *this = matrixToCopy;
    }

    /**
    * Move constructor.
    * @param matrixToMove source matrix
    */
    Matrix<T>(const Matrix<T> && matrixToMove) :
            _matrix(std::move(matrixToMove._matrix)),
            _rows(std::move(matrixToMove._rows)),
            _cols(std::move(matrixToMove._cols)){}

    /**
    * Content constructor.
    * @param rows number of rows in matrix
    * @param cols number of columns in matrix
    * @param cells set of values to instert into matrix
    */
    Matrix<T>(unsigned int rows, unsigned int cols, const std::vector<T>& cells) : _rows(rows), _cols(cols)
    {

    }

    /**
    * Destructor.
    */
    ~Matrix<T>()
    {
        this->_matrix.clear();
    }

    /**
    * Setter () operator.
    * @param row row index
    * @param col column index
    * @return the relevant value in matrix
    * @throw OutOfMatrixLimitsException if input indexes are out of matrix size
    */
    T& operator()(unsigned int row, unsigned int col)
    {

    }

    /**
    * Getter () operator.
    * @param row row index
    * @param col column index
    * @return the relevant value in matrix
    * @throw OutOfMatrixLimitsException if input indexes are out of matrix size
    */
    const T& operator()(unsigned int row, unsigned int col) const
    {

    }

    /**
    * Equality operator.
    * @param rhs second matrix in the operation
    */
    bool operator==(const Matrix<T>& rhs) const
    {

    }

    /**
    * Non-Equality operator.
    * @param rhs second matrix in the operation
    */
    bool operator!=(const Matrix<T>& rhs) const
    {
        return not(*this == rhs);
    }

    /**
    * Assignment operator.
    * @param rhs matrix to assign
    */
    Matrix<T>& operator=(Matrix<T> rhs)
    {

    }

    /**
    * Addition operator.
    * @param rhs matrix to add
    * @throw NotCompatibleDimensionsException if matrices' sizes are different
    */
    const Matrix<T> operator+(const Matrix<T>& rhs) const
    {

    }

    /**
    * Subtraction operator.
    * @param rhs matrix to sub (?!)
    * @throw NotCompatibleDimensionsException if matrices' sizes are different
    */
    const Matrix<T> operator-(const Matrix<T>& rhs) const
    {

    }

    /**
    * Multiplication operator.
    * @param rhs matrix to multiply with
    * @throw NotCompatibleDimensionsException if lhs' cols != rhs' rows
    */
    const Matrix<T> operator*(const Matrix<T>& rhs) const
    {

    }

    /**
    * Matrix transpose creator.
    * @return transposed matrix
    */
    const Matrix<T> trans() const
    {

    }

    /**
    * Matrix trace calculator.
    */
    T trace() const
    {

    }

    /**
    * @return begining of iterator
    */
    const const_iterator begin()
    {
        return this->_matrix.begin();
    }

    /**
    * @return ending of iterator
    */
    const const_iterator end()
    {
        return this->_matrix.end();
    }

    /**
    * Rows getter.
    * @return number of rows in matrix
    */
    unsigned int rows() const
    {
        return this->_rows;
    }

    /**
    * Columns getter.
    * @return number of columns in matrix
    */
    unsigned int cols() const
    {
        return this->_cols;
    }

    /**
    * Size getter.
    * @return matrix's size (rows * cols)
    */
    unsigned int size() const
    {

    }

    /**
    * This function goal is to turn on/off the parallel programming option.
    * @param mode mode to set
    */
    static void setParallel(bool mode)
    {

    }

private:
    std::vector<T> _matrix;
    unsigned int _rows;
    unsigned int _cols;


    /**
    * A Function that check if matrix is square or not.
    * @return true if square matrix.
    */
    bool isSquare()
    {
        return this->_rows == this->_cols;
    }





};

/**
* Matrix printing operator.
* @param matrix right-side matrix
* @return output stream
*/
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
{

}

/**
* Conjugate matrix creator. Works on complex matrices only.
* @return conjugate matrix
*/
template<>
const Matrix<Complex> Matrix<Complex>::trans() const
{

}



#endif //CPP3_MATRIX_HPP
