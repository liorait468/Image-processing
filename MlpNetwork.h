
//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Dense.h"
#include "Digit.h"

#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784},
                                  {64,  128},
                                  {20,  64},
                                  {10,  20}};
const MatrixDims biasDims[] = {{128, 1},
                               {64,  1},
                               {20,  1},
                               {10,  1}};

/**
 * @brief class that represents a mlpnetwork
 */
class MlpNetwork
{
public:

    /**
     * @brief constructor for mlpnetwork
     * @param weights an array of weights matrices
     * @param biases an array of biases matrices
     */
    MlpNetwork(Matrix weights[], Matrix biases[]);

    /**
     * @brief Gets a vector representing an image
     *        performs the mlpnetwork's functions on the input vector
     *        returns a digit struct with the number on the picture
     * @param inputVector - the input vector, at size 784*1.
     * @return digit struct with the probability and index of the number in the picture
     */
    Digit operator()(Matrix inputVector);
private:
    bool _checkSizeOfWeightsMatrix(Matrix weights[]);
    bool _checkSizeOfBiasMatrix(Matrix biases[]);
    Dense _denseArr[MLP_SIZE]; // the array of the four denses
};

#endif // MLPNETWORK_H
