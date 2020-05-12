/**
* @file   Activation.cpp
* @brief a program that implements Activation.h. represents and creates an activation object,
 *       that has functions to perform on matrices
* @section DESCRIPTION a program that implements Activation.h.
*/

// -------------------------------------- includes ------------------------------------------------

#include "Activation.h"
#include "MlpNetwork.h"
#include <math.h>
#define WRONG_SIZE_ERR "Error: Wrong matrix size for softmax"

// ------------------------------------------- function declaration -------------------------------

/**
 * @brief constructor for activation object
 * @param actType - activation type
 */
Activation::Activation(ActivationType actType):_actType(actType)
{
}

/**
 * @brief returns the activation type
 * @return activation type
 */
ActivationType& Activation::getActivationType()
{
    return _actType;
}

/**
 * @brief performs relu function on a matrix
 * @param mat - the matrix
 * @return - the matrix after relu function
 */
Matrix& Activation::reluFunction(Matrix& mat)
{
    // Goes over the array of float and changes it if needed
    for (int i = 0; i < mat.getCols() * mat.getRows(); i++)
    {
        // Checks if the value in the current cell is smaller then zero
        if (mat[i] < 0)
        {
            mat[i] = 0;
        }
    }
    return mat;
}

/**
 * @brief performs softmax function on a matrix
 * @param mat - the matrix
 * @return - the matrix after softmax function
 */
Matrix& Activation::softMaxFunction(Matrix& mat)
{
    if ((mat.getRows() != biasDims[MLP_SIZE - 1].rows) ||
        (mat.getCols() != biasDims[MLP_SIZE - 1].cols))
    {
        std::cerr << WRONG_SIZE_ERR << std::endl;
    }

    Matrix e(mat.getRows(), mat.getCols()); // should be 10 * 1
    int sizeOfE = e.getRows() * e.getCols();

    for (int i = 0; i < sizeOfE; i++)
    {
        e[i] = std::exp(mat[i]); // e[i] = e^zi
    }
    float sum = 0;
    for (int i = 0; i < sizeOfE; i++)
    {
        sum += e[i];
    }

    float division = 1 / sum;

    mat = division * e;
    return mat;
}

/**
 * @brief performs a function on the input matrix, according to the dense's activation type
 *        does not change the input matrix
 * @param input - the matrix to perform the function on
 * @return - a matrix after the function
 */
Matrix Activation::operator()(Matrix& input)
{
    Matrix result = input;

    if (getActivationType() == Relu)
    {
       result = reluFunction(result);
    }
    else if (getActivationType() == Softmax)
    {
        result = softMaxFunction(result);
    }
    return result;
}