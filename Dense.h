
//Dense.h

#ifndef CPP_EX1_DENSE_H
#define CPP_EX1_DENSE_H

#include "Activation.h"

/**
 * @brief class that represents a dense
 */
class Dense
{
public:
    /**
     * @brief constructor for dense
     * @param w - array of 4 matrices
     * @param bias - array of 4 matrices
     * @param actType - activation type
     */
    Dense(Matrix& w, Matrix& bias, ActivationType actType);

    /**
     * @brief return the weights matrix of the dense
     * @return - the weights matrix
     */
    const Matrix& getWeights() const;

    /**
     * @brief return the bias matrix of the dense
     * @return - the bias matrix
     */
    const Matrix& getBias() const;

    /**
     * @brief returns the activation
     * @return - the activation object
     */
    Activation getActivation() const;

    /**
     * @brief performs the activation function on the input
     * @param matVector - the input matrix
     * @return - the matrix after the activation function
     */
    Matrix operator()(const Matrix& matVector) const;
private:
    Matrix _w;           // the matrix of weights
    Matrix _bias;        // the matrix of bias
    Activation _act;     // the activation of the dense
};

#endif //CPP_EX1_DENSE_H
