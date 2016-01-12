//
// Created by gilovi on 1/10/16.
//

#ifndef CPP3_MATRIX_HPP
#define CPP3_MATRIX_HPP

#include <vector>
#include <iterator>
#include <stdexcept>
#include <iostream>
#include <mutex>
#include <thread>
#include "Complex.h"
#include "DimensionsMismatchException.hpp"
#include "NonSquareMatrixException.hpp"



#define DEFAULT_SIZE 1
#define OUT_OF_RANGE_MSG "index is outside the matrix's range"
#define PARALEL_MSG "Generic Matrix mode changed to parallel mode."
#define NON_PARALEL_MSG "Generic Matrix mode changed to non-parallel mode."


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
    Matrix<T>(unsigned int rows, unsigned int cols) : _rows(rows), _cols(cols), _matrix(rows*cols ,T(0))
    {}

    /**
    * Default constructor.
    */
    Matrix<T>() : Matrix(DEFAULT_SIZE, DEFAULT_SIZE)
    {}


    /**
    * Copy constructor.
    * @param toCopy the matrix to copy
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
    * @param rows the number of rows in the matrix
    * @param cols the number of columns in the matrix
    * @param cells the values to insert into the matrix
    * @throw
    */
    Matrix<T>(unsigned int rows, unsigned int cols, const std::vector<T>& cells) : _rows(rows), _cols(cols), _matrix(cells.begin(), cells.end())
    {
        if (rows * cols != cells.size())
        {
            throw DimensionsMismatchException("values constructor");
        }
    }

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
    * @param rhs the matrix to add
    * @throw DimensionsMismatchException if the matrices sizes mismatch
    */
    const Matrix<T> operator+(const Matrix<T>& rhs) const
    {
        if (this->_rows != rhs._rows || this->_cols != rhs._cols)
        {
            throw DimensionsMismatchException("+");
        }
        Matrix<T> result(this->_rows , this->_cols);
        if(s_isParalelMode)
        {
            //each row will run in it's own thread
            std::vector<std::thread> threads(this->_rows-1);
            for (unsigned int i = 0 ; i < this->_rows; i++ )
            {
                threads[i] = std::thread(paralelAddition, std::ref(*this), std::ref(rhs), i, std::ref(result));
            }
            for (int i = 0; i < threads.size(); i++)
            {
                threads[i].join();
            }


        }
        else
        {
            for (int i = 0 ; i < this->size() ; i++)
            {
                result._matrix[i] = this->_matrix[i] + rhs._matrix[i];
            }
        }
        return result;
    }

    /**
    * Subtraction operator.
    * @param rhs the matrix to sub
    * @throw DimensionsMismatchException if the matrices sizes mismatch
    */
    const Matrix<T> operator-(const Matrix<T>& rhs) const
    {
        if (this->_rows != rhs._rows || this->_cols != rhs._cols)
        {
            throw DimensionsMismatchException("-");
        }
        Matrix<T> result(this->_rows , this->_cols);

        {
            for (int i = 0 ; i < this->size() ; i++)
            {
                result._matrix[i] = this->_matrix[i] - rhs._matrix[i];
            }
        }
        return result;
    }

    /**
    * Multiplication operator.
    * @param rhs the matrix to multiply with
    * @throw DimensionsMismatchException if the columns in lhs != rows in rhs'
    */
    const Matrix<T> operator*(const Matrix<T>& rhs) const
    {
        if (this->_cols != rhs._rows)
        {
            throw DimensionsMismatchException("*");
        }
        Matrix<T> resultMat(this->_rows, rhs._cols);
        if (!s_isParalelMode)
        {
            for (unsigned int i = 0; i < resultMat._rows; i++)
            {
                for (unsigned int j = 0; j < resultMat._cols; j++)
                {
                    T currSum = T(0);
                    for (unsigned int k = 0; k < this->_cols; k++)
                    {
                        currSum += (*this)(i,k) * (rhs)(k,j);
                    }
                    resultMat(i,j) = currSum;
                }
            }
        }
        else
        {
            //TODO paralel mode
        }
        return resultMat;
    }

    /**
    * Equality operator.
    * @param rhs the matrix to compare to
    */
    bool operator==(const Matrix<T>& rhs) const
    {
        if (this->_rows == rhs._rows && this->_cols == rhs._cols)
        {
            for (int i = 0 ; i < this->size() ; i++)
            {
                if (this->_matrix[i] != rhs._matrix[i])
                {
                    return false;
                }
            }
            return true;
        }

        return false;
    }

    /**
    * Non-Equality operator.
    * @param rhs the matrix to compare to
    */
    bool operator!=(const Matrix<T>& rhs) const
    {
        return not(*this == rhs);
    }

    /**
    * Matrix transpose.
    * @return the transposed matrix
    */
    const Matrix<T> trans() const
    {
        Matrix<T> resultMat(this->_cols , this->_rows) ;
        for (unsigned int i = 0 ; i < this->_rows ; i++)
        {
            for (unsigned int j = 0 ; j < this->_cols ; j++)
            {
                resultMat(j,i) = ((*this)(i,j));
            }

        }
        return resultMat;
    }

    /**
    * Matrix trace .
    * @return the matrix's trace
    * @throw NonSquareMatrixException
    */

    T trace() const
    {
        if (not(isSquare()))
        {
            throw NonSquareMatrixException("trace");
        }

        T result = T(0) ;
        for (unsigned int i = 0 ; i < this->_cols ; i++)
        {
            result += (*this)(i,i);
        }
        return result;
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
        if (row >= this->_rows || col >= this->_cols)
        {
            throw std::out_of_range (OUT_OF_RANGE_MSG);
        }
        return this->_matrix[getIndex(this->_cols, row, col)];
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
        if (row >= this->_rows || col >= this->_cols)
        {
            throw std::out_of_range (OUT_OF_RANGE_MSG);
        }
        return this->_matrix[getIndex(this->_cols, row, col)];
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
        return this->_rows * this->_cols;
    }

    /**
    * sets paralel computationn of several operators
    * @param mode the mode to change to
    */
    static void setParallel(bool mode)
    {
        if (s_isParalelMode != mode)
        {
            std::string toPrint = mode? PARALEL_MSG : NON_PARALEL_MSG ;
            std::cout << toPrint <<std::endl;
            s_isParalelMode = mode;
        }

    }


private:
    unsigned int _rows;
    unsigned int _cols;
    std::vector<T> _matrix;
    static bool s_isParalelMode;
    std::mutex _mut;


    static int getIndex(unsigned int matCols , unsigned int row,  unsigned int col)
    {
        return (row * matCols) + col;
    }

    /**
    * A Function that check if matrix is square or not.
    * @return true if square matrix.
    */
    const bool isSquare() const
    {
        return this->_rows == this->_cols;
    }

    static void paralelAddition(const Matrix<T>& lhs, const Matrix<T>& rhs , int row , Matrix<T>& resMat )
    {
        for (int i = getIndex(lhs._cols, row, 0); i < getIndex(lhs._cols, row,resMat._cols); i++)
        {
            resMat(row,i) = lhs(row,i) + rhs(row,i);
        }
    }

    static void paralelMult(const Matrix<T>& lhs, const Matrix<T>& rhs , int row , Matrix<T>& resMat )
    {

        for (unsigned int j = 0; j < resMat._cols; j++) {
            T currSum = T(0);
            for (unsigned int k = 0; k < lhs._cols; k++) {
                currSum += lhs(row, k) * (rhs)(k, j);
            }
            resMat(row, j) = currSum;
        }



    }


};

template<class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
{
    for (unsigned int i = 0; i < matrix.rows(); i++)
    {
        for (unsigned int j = 0; j < matrix.cols(); j++)
        {
            os << matrix(i, j) << "\t";
        }
        os << std::endl;
    }
    return os;

}

template<class T>
bool Matrix<T>::s_isParalelMode = false;

template<>
const Matrix<Complex> Matrix<Complex>::trans() const
{
    Matrix<Complex> retMat(this->_cols, this->_rows);
    for (unsigned int i = 0; i < this->_rows; i++)
    {
        for (unsigned int j = 0; j < this->_cols; j++)
        {
            retMat(j, i) = ((*this)(i, j)).conj();
        }
    }
    return retMat;
}


#endif //CPP3_MATRIX_HPP
