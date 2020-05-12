/**
* @file   Matrix.cpp
* @brief a program that implements Matrix.h. represents and creates a matrix object that contains
 *       an array of float.
* @section DESCRIPTION a program that implements Matrix.h.
*/

// -------------------------------------- includes ------------------------------------------------
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <cstdio>

#define STR_INVALID_NUM_ROWS_OR_COLS "Error: number of rows or cols is invalid"
#define STR_ALLOCATION_ERR         "Error: memory allocation didn't work"
#define STR_WRONG_SIZES_MULT       "Error: different sizes for * "
#define STR_WRONG_SIZES_ADD        "Error: different sizes for + "
#define STR_WRONG_SIZES_ASSIGN_ADD "Error: different sizes for += "
#define STR_OUT_OF_BOUNDS_ERR      "Error: out of bounds"
#define STR_INVALID_ARGS_ERR       "Error: invalid args"
#define STR_DIFFERENT_SIZES_ERR    "Error: different sizes"
#define DEFAULT_SIZE 1

// ------------------------------------------- function declaration -------------------------------

/**
 * @brief destructor for Matrix
 */
Matrix::~Matrix()
{
    delete [] _2DArray;
}

/**
 * @brief constructor for Matrix - creates a matrix object
 * @param rows - the number of rows of the matrix to create
 * @param cols - the number of cols of the matrix to create
 */
Matrix::Matrix(int rows, int cols) : _dims{rows, cols}
{
    // Checks if the number of rows or cols is smaller or equal to zero
    if ((_dims.rows <= 0) || (_dims.cols <= 0))
    {
        std::cerr << STR_INVALID_NUM_ROWS_OR_COLS << std::endl;
        exit(EXIT_FAILURE);
    }

    _2DArray = new float[_dims.rows* _dims.cols];

    // Checks if the memory allocation worked
    if (_2DArray == nullptr)
    {
        std::cerr << STR_ALLOCATION_ERR << std::endl;
        exit(EXIT_FAILURE);
    }

    _size = _dims.rows * _dims.cols;

    // Goes over the array of float and initializes each cell with zero
    for (int i = 0; i < (_size); i++)
    {
        _2DArray[i] = 0;
    }
}

/**
 * @brief constructs a matrix with one cell
 */
Matrix::Matrix(): _dims{DEFAULT_SIZE, DEFAULT_SIZE}
{
    _2DArray = new float[_dims.rows * _dims.cols];

    // Checks if the memory allocation worked
    if (_2DArray == nullptr)
    {
        std::cerr << STR_ALLOCATION_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    _size = _dims.rows * _dims.cols;

    _2DArray[0] = 0;
}

/**
 * @brief copy constructor for matrix
 * @param mat - the other matrix to copy from
 */
Matrix::Matrix(const Matrix& mat): _dims{mat.getRows(), mat.getCols()}
{
    _2DArray = new float[_dims.rows * _dims.cols];

    // Checks if the memory allocation worked
    if (_2DArray == nullptr)
    {
        std::cerr << STR_ALLOCATION_ERR << std::endl;
        exit(EXIT_FAILURE);
    }

    _size = _dims.rows * _dims.cols;

    // Goes over the array of float and initializes each value with the according value in mat
    for (int i = 0; i < (_size); i++)
    {
        _2DArray[i] = mat[i];
    }
}

/**
 * @brief returns the number of rows of the array
 * @return the number of rows
 */
int& Matrix::getRows()
{
    return _dims.rows;
}

/**
 * @brief returns the number of cols of the array
 * @return the number of cols
 */
int& Matrix::getCols()
{
    return _dims.cols;
}

/**
 * @brief multiples two matrices
 * @param other - the matrix to multiply with the current matrix
 * @return - a matrix with the result of multiplication
 */
Matrix Matrix::operator*(const Matrix& other) const
{
    // checks if the number of cols is different from the number of rows
    if (_dims.cols != other.getRows())
    {
        std::cerr << STR_WRONG_SIZES_MULT << std::endl;
        exit(EXIT_FAILURE);
    }

    int otherCols = other.getCols();
    Matrix temp(_dims.rows, other.getCols());

    for (int i = 0; i < _dims.rows; i++)
    {
        for (int j = 0; j < otherCols; j++)
        {
            for (int k = 0; k < _dims.cols; k++)
            {
                (temp)(i, j) += ((*this)(i, k) * (other)(k, j));
            }
        }
    }
    return temp;
}

/**
 * @brief prints the matrix array
 */
void Matrix::plainPrint() const
{
    for (int i = 0; i < _dims.rows; i++)
    {
        for (int j = 0; j < _dims.cols; j++)
        {
            std::cout << _2DArray[i * _dims.cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief returns the element in the i row, j column
 * @param i - the row
 * @param j - the column
 * @return  - the element in the matrix
 */
float& Matrix::operator()(const int i, const int j)
{
    if ((i < 0) || (j < 0))
    {
        std::cerr << STR_INVALID_ARGS_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    if ((i >= _dims.rows) || (j >= _dims.cols))
    {
        std::cerr << STR_OUT_OF_BOUNDS_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    return _2DArray[i * _dims.cols + j];
}

const float& Matrix::operator()(const int i, const int j) const
{
    if ((i < 0) || (j < 0))
    {
        std::cerr << STR_INVALID_ARGS_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    if ((i >= _dims.rows) || (j >= _dims.cols))
    {
        std::cerr << STR_OUT_OF_BOUNDS_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    return _2DArray[i * _dims.cols + j];
}

/**
 * @brief adds two matrices
 * @param other - the other matrix
 * @return a matrix after the addition
 */
Matrix Matrix::operator+(const Matrix& other) const
{
    if ((_dims.rows != other.getRows()) || (_dims.cols != other.getCols()))
    {
        std::cerr << STR_WRONG_SIZES_ADD << std::endl;
        exit(EXIT_FAILURE);
    }

    Matrix temp(_dims.rows, _dims.cols);

    for (int i = 0; i < _dims.rows; i++)
    {
        for (int j = 0; j < _dims.cols; j++)
        {
            (temp)(i, j) = (other)(i, j) + (*this)(i, j);
        }
    }
    return temp;
}

const int& Matrix::getRows() const
{
    return _dims.rows;
}

const int& Matrix::getCols() const
{
    return _dims.cols;
}

/**
 * @brief assigns the information of other matrix into the current matrix
 * @param other - the other matrix
 * @return the current matrix
 */
Matrix& Matrix::operator=(const Matrix &other)
{
    if (this == &other)
    {
        return *this;
    }

    delete [] _2DArray;

    _dims.rows = other.getRows();
    _dims.cols = other.getCols();

    _2DArray = new float[_dims.rows * _dims.cols];

    // Checks if the memory allocation worked
    if (_2DArray == nullptr)
    {
        std::cerr << STR_ALLOCATION_ERR << std::endl;
        exit(EXIT_FAILURE);
    }

    _size = _dims.rows * _dims.cols;


    // Goes over the array of float and copies the data
    for (int i = 0; i < (_size); i++)
    {
        _2DArray[i] = other[i];
    }

    return *this;
}

/**
 * @brief represents the matrix as a column vector
 * @return the current matrix represented as column vector
 */
Matrix& Matrix::vectorize()
{
    _dims.rows = _dims.rows * _dims.cols;
    _dims.cols = 1;

    return *this;
}

/**
 * @brief multiples the matrix by scalar
 * @param scalar the scalar
 * @return a matrix after multiplication by scalar
 */
Matrix Matrix::operator*(const float& scalar) const
{
    Matrix temp(_dims.rows, _dims.cols);

    // Goes over the array and multiples each cell by the scalar
    for (int i = 0; i < _dims.rows; i++)
    {
        for (int j = 0; j < _dims.cols; j++)
        {
            (temp)(i, j) = (*this)(i, j) * scalar;
        }
    }
    return (temp);
}

/**
 * @brief multiples scalar by matrix
 * @param scalar the scalar
 * @param m the matrix (const)
 * @return a matrix after the multiplication
 */
Matrix operator*(const float& scalar,  const Matrix& m)
{
    Matrix temp(m.getRows(), m.getCols());

    // Goes over the array and multiples each cell by the scalar
    for (int i = 0; i < temp.getRows(); i++)
    {
        for (int j = 0; j < temp.getCols(); j++)
        {
            temp(i, j) = scalar * m(i , j);
        }
    }
    return temp;
}

/**
 * @brief multiples scalar by matrix
 * @param scalar the scalar
 * @param m the matrix
 * @return a matrix after the multiplication
 */
Matrix operator*(const float& scalar,  Matrix& m)
{
    Matrix temp(m.getRows(), m.getCols());

    // Goes over the array and multiples each cell by the scalar
    for (int i = 0; i < temp.getRows(); i++)
    {
        for (int j = 0; j < temp.getCols(); j++)
        {
            temp(i, j) = scalar * m(i , j);
        }
    }
    return temp;
}

/**
 * @brief assigns and adds the other matrix to the current matrix
 * @param other - the other matrix
 * @return - the current matrix after the add and assignment
 */
Matrix& Matrix::operator+=(const Matrix& other)
{
    if ((_dims.rows != other.getRows()) || (_dims.cols != other.getCols()))
    {
        std::cerr << STR_WRONG_SIZES_ASSIGN_ADD << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < _dims.rows; i++)
    {
        for (int j = 0; j < _dims.cols; j++)
        {
            (*this)(i, j) = (other)(i, j) + (*this)(i, j);
        }
    }
    return (*this);
}

/**
 * @brief returns the element in the array in the i index
 * @param i the index
 * @return the element (non const)
 */
float& Matrix::operator[](const int i)
{
    // Checks if i is a valid index
    if (i >= (_dims.rows * _dims.cols) || (i < 0))
    {
        std::cerr << STR_OUT_OF_BOUNDS_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    return _2DArray[i];
}

/**
 * @brief returns the element in the array in the i index
 * @param i the index
 * @return the element (const)
 */
const float& Matrix::operator[](const int i) const
{
    // Checks if i is a valid index
    if (i >= (_dims.rows * _dims.cols) || (i < 0))
    {
        std::cerr << STR_OUT_OF_BOUNDS_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    return _2DArray[i];
}

/**
 * @brief reads data into mat
 * @param is - ifstream object
 * @param mat - the matrix to save the data into
 */
std::istream& operator>>(std::istream& is, Matrix& mat)
{
    int i = 0;

    while (i < mat.getRows() * mat.getCols())
    {
        if (!is.good())
        {
            std::cerr << STR_DIFFERENT_SIZES_ERR << std::endl;
        }
        is.read((char*)&mat[i] , 4);
        i++;
    }
    return is;
}

/**
 * @brief prints the matrix according to a condition
 * @param out - ostream object
 * @param mat - the matrix to print
 * @return - ostream object
 */
std::ostream& operator<<(std::ostream& out, Matrix& mat)
{
    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            if (mat(i, j) <= 0.1f)
            {
                out << "  ";
            }
            else
            {
                out << "**";
            }
        }
        std::cout << std::endl;
    }
    return out;
}
