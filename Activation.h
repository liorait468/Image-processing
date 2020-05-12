
//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};

/**
 * @brief class that represents an activation
 */
class Activation
{
public:

    /**
     * @brief constructor for activation object
     * @param actType - activation type
     */
    explicit Activation(ActivationType actType);

    /**
     * @brief returns the activation typew
     * @return activation type
     */
    ActivationType& getActivationType();

    /**
     * @brief performs relu function on a matrix
     * @param mat - the matrix
     * @return - the matrix after relu function
     */
    Matrix& reluFunction(Matrix& mat);

    /**
     * @brief performs softmax function on a matrix
     * @param mat - the matrix
     * @return - the matrix after softmax function
     */
    Matrix& softMaxFunction(Matrix& mat);

    /**
     * @brief performs a function on the input matrix, according to the dense's activation type
     *        does not change the input matrix
     * @param input - the matrix to perform the function on
     * @return - a matrix after the function
     */
    Matrix operator()(Matrix& input);
private:
    ActivationType _actType;
};

#endif //ACTIVATION_H
