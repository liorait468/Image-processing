/**
* @file   Dense.cpp
* @brief a program that implements Dense.h. represents and creates a dense in mlpnetwork
* @section DESCRIPTION a program that implements Dense.h.
*/

// -------------------------------------- includes ------------------------------------------------

#include "Dense.h"
#include "Activation.h"

// ------------------------------------------- function declaration -------------------------------

/**
 * @brief constructor for dense
 * @param w - array of 4 matrices
 * @param bias - array of 4 matrices
 * @param actType - activation type
 */
Dense::Dense(Matrix& w, Matrix& bias, ActivationType actType):_w(w), _bias(bias), _act(actType)
{
}

/**
 * @brief return the weights matrix of the dense
 * @return - the weights matrix
 */
const Matrix& Dense::getWeights() const
{
    return _w;
}

/**
 * @brief return the bias matrix of the dense
 * @return - the bias matrix
 */
const Matrix& Dense::getBias() const
{
    return _bias;
}

/**
 * @brief the activation type
 * @return
 */
Activation Dense::getActivation() const
{
   return _act;
}

/**
* @brief performs the activation function on the input
* @param matVector - the input matrix
* @return - the matrix after the activation function
*/
Matrix Dense::operator()(const Matrix& matVector) const
{
    Matrix outputMat(matVector.getRows(), matVector.getCols());
    Matrix mat = (getWeights() * matVector);

    mat += getBias();
    outputMat = getActivation()(mat);
    return outputMat;
}




