//
// Created by gilovi on 1/10/16.
//

#ifndef CPP3_MATRIX_HPP
#define CPP3_MATRIX_HPP

#include <vector>
#include <iterator>
#include "Complex.h"
#include <stdexcept>

#define DEFAULT_SIZE 1
#define OUT_OF_RANGE_MSG "index is outside the matrix's range"

/**
* Generic matrix class.
*/
template<class T>
class Matrix
{
public:
    typedef typename std::vector<T>::const_iterator const_iterator;

    /**
    * Dimension constructor.
    * @param rows the number of rows
    * @param cols the number of columns
    */
    Matrix<T>(unsigned int rows, unsigned int cols) : _rows(rows), _cols(cols),  _matrix(rows*cols ,T(0))
    {}

    /**
    * Default constructor.
    */
    Matrix<T>() : Matrix(DEFAULT_SIZE, DEFAULT_SIZE)
    {}


    /**
    * Copy constructor.
    * @param toCopy matrix to copy
    */
    Matrix<T>(const Matrix<T>& toCopy)
    {
        *this = toCopy;
    }

    /**
    * Move constructor.
    * @param toMove the matrix to move
    */
    Matrix<T>(const Matrix<T>&& toMove) :
            _rows(std::move(toMove._rows)),
            _cols(std::move(toMove._cols)),
            _matrix(std::move(toMove._matrix))
    {}

    /**
    * Values constructor.
    * @param rows number of rows in matrix
    * @param cols number of columns in matrix
    * @param cells values to insert into the matrix
    */
    Matrix<T>(unsigned int rows, unsigned int cols, const std::vector<T>& cells) : _rows(rows), _cols(cols), _matrix(cells.begin(), cells.end())
    {}

    /**
    * Destructor.
    */
    ~Matrix<T>()
    {
        this->_matrix.clear();
    }

    /**
    * Assignment operator.
    * @param rhs the matrix to assign
    */
    Matrix<T>& operator=(Matrix<T> rhs)
    {
        std::swap(this->_rows, rhs._rows);
        std::swap(this->_cols, rhs._cols);
        std::swap(this->_matrix, rhs._matrix);
        return *this;
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
    * Equality operator.
    * @param rhs second matrix in the operation
    */
    bool operator==(const Matrix<T>& rhs) const
    {
        if (this->_rows == rhs._rows && this->_cols == rhs._cols)
        {
            //TODO!!
        }

        return false;
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
    * Matrix printing operator.
    * @param matrix right-side matrix
    * @return output stream
    */
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
    {

    }

    /**
    * Index () operator.
    * @param row the row index
    * @param col the column index
    * @return the indexed value in the matrix
    * @throw out_of_range if input indexes are out of matrix size
    */
    T& operator()(unsigned int row, unsigned int col)
    {
        if (row > this->_rows || col > this->_cols)
        {
            throw std::out_of_range (OUT_OF_RANGE_MSG);
        }
        return this->_matrix[getIndex(row, col)];
    }

    /**
    * Const index () operator.
    * @param row the row index
    * @param col the column index
    * @return the indexed value in the matrix
    * @throw OutOfMatrixLimitsException if input indexes are out of matrix size
    */
    const T& operator()(unsigned int row, unsigned int col) const
    {
        return this->_matrix[getIndex(row, col)];
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
    * @return the number of rows in the matrix
    */
    unsigned int rows() const
    {
        return this->_rows;
    }

    /**
    * Columns getter.
    * @return the number of columns in the matrix
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
    unsigned int _rows;
    unsigned int _cols;
    std::vector<T> _matrix;


    int getIndex(unsigned int row,  unsigned int col) const
    {
        return (row * this->_cols) + col;
    }

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
* Conjugate matrix creator. Works on complex matrices only.
* @return conjugate matrix
*/
template<>
const Matrix<Complex> Matrix<Complex>::trans() const
{

}



#endif //CPP3_MATRIX_HPP
