

// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
    int rows, cols;
} MatrixDims;

/**
 * @brief class that represents a matrix
 */
class Matrix
{
public:
    /**
     * @brief constructs a matrix with one cell
     */
    Matrix();

    /**
     * @brief constructor for Matrix - creates a matrix object
     * @param rows - the number of rows of the matrix to create
     * @param cols - the number of cols of the matrix to create
     */
    Matrix(int rows, int cols);

    /**
     * @brief copy constructor for matrix
     * @param mat - the other matrix to copy from
     */
    Matrix(const Matrix &m);

    /**
     * @brief destructor for Matrix
     */
    ~Matrix();

    /**
     * @brief multiples two matrices
     * @param other - the matrix to multiply with the current matrix
     * @return - a matrix with the result of multiplication
     */
    Matrix operator*(const Matrix &other) const;

    /**
     * @brief adds two matrices
     * @param other - the other matrix
     * @return a matrix after the addition
     */
    Matrix operator+(const Matrix &other) const;

    /**
     * @brief multiples the matrix by scalar
     * @param scalar the scalar
     * @return a matrix after multiplication by scalar
     */
    Matrix operator*(const float &scalar) const;

    /**
     * @brief assigns and adds the other matrix to the current matrix
     * @param other - the other matrix
     * @return - the current matrix after the add and assignment
     */
    Matrix &operator+=(const Matrix &other);

    /**
     * @brief returns the element in the i row, j column
     * @param i - the row
     * @param j - the column
     * @return  - the element in the matrix
     */
    float &operator()(const int i, const int j);

    /**
     * @brief returns the element in the i row, j column
     * @param i - the row
     * @param j - the column
     * @return  - the element in the matrix (const)
     */
    const float &operator()(const int i, const int j) const;

    /**
     * @brief returns the element in the array in the i index
     * @param i the index
     * @return the element (non const)
     */
    float &operator[](const int i);

    /**
     * @brief returns the element in the array in the i index
     * @param i the index
     * @return the element (const)
     */
    const float &operator[](const int i) const;

    /**
     * @brief assigns the information of other matrix into the current matrix
     * @param other - the other matrix
     * @return the current matrix
     */
    Matrix &operator=(const Matrix &other);

    /**
     * @brief returns the number of rows of the array
     * @return the number of rows
     */
    int &getRows();

    /**
     * @brief returns the number of cols of the array
     * @return the number of cols
     */
    int &getCols();

    /**
     * @brief returns the number of rows of the array
     * @return the number of rows
     */
    const int &getRows() const;

    /**
     * @brief returns the number of cols of the array
     * @return the number of cols
     */
    const int &getCols() const;

    /**
     * @brief prints the matrix array
     */
    void plainPrint() const;

    /**
     * @brief represents the matrix as a column vector
     * @return the current matrix represented as column vector
     */
    Matrix &vectorize();

    /**
     * @brief multiples scalar by matrix
     * @param scalar the scalar
     * @param m the matrix (const)
     * @return a matrix after the multiplication
     */
    friend Matrix operator*(const float &scalar, const Matrix &m);

    /**
     * @brief prints the matrix according to a condition
     * @param out - ostream object
     * @param mat - the matrix to print
     * @return - ostream object
     */
    friend std::ostream &operator<<(std::ostream &out, Matrix &mat);

    /**
     * @brief reads data into mat
     * @param is - ifstream object
     * @param mat - the matrix to save the data into
     */
    friend std::istream& operator>>(std::istream& is, Matrix& mat);

    /**
    * @brief multiples scalar by matrix
    * @param scalar the scalar
    * @param m the matrix (const)
    * @return a matrix after the multiplication
    */
    friend Matrix operator*(const float& scalar,  Matrix& m);

private:
    MatrixDims _dims;
    float *_2DArray;
    int _size;
};

#endif //MATRIX_H


