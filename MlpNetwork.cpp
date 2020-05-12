/**
* @file   MlpNetwork.cpp
* @brief a program that implements MlpNetwork.h. represents and creates a mlpnetwork
* @section DESCRIPTION a program that implements MlpNetwork.h.
*/

// -------------------------------------- includes ------------------------------------------------
#include "MlpNetwork.h"

#define ERROR_WRONG_SIZE_WEIGHTS "Error: different sizes weights matrix"
#define ERROR_WRONG_SIZE_BIASES  "Error: different sizes biases matrix"

// ------------------------------------------- function declaration -------------------------------

/**
 * @brief constructor for mlpnetwork
 * @param weights an array of weights matrices
 * @param biases an array of biases matrices
 */
MlpNetwork::MlpNetwork(Matrix weights[], Matrix biases[]):_denseArr
                  {
                       Dense(weights[0], biases[0], Relu),
                       Dense(weights[1], biases[1], Relu),
                       Dense(weights[2], biases[2], Relu),
                       Dense(weights[3], biases[3], Softmax)
                  }
{
    if (!(_checkSizeOfWeightsMatrix(weights)))
    {
        std::cerr << ERROR_WRONG_SIZE_WEIGHTS << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!(_checkSizeOfBiasMatrix(biases)))
    {
        std::cerr << ERROR_WRONG_SIZE_BIASES << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool MlpNetwork::_checkSizeOfWeightsMatrix(Matrix weights[])
{
    // Checks for each matrix in the weights array if her size matches the needed size according
    // to the number of the dense
    for (int index = 0; index < MLP_SIZE; index++)
    {
        Matrix weightsByIndex = weights[index];
        MatrixDims matDims = weightsDims[index];

        if ((weightsByIndex.getRows() != matDims.rows) || (weightsByIndex.getCols() != matDims.cols))
        {
            return false;
        }
    }
    return true;
}

bool MlpNetwork::_checkSizeOfBiasMatrix(Matrix biases[])
{
    // Checks for each matrix in the weights array if her size matches the needed size according
    // to the number of the dense
    for (int index = 0; index < MLP_SIZE; index++)
    {
        Matrix biasByIndex = biases[index];
        MatrixDims matDims = biasDims[index];

        if ((biasByIndex.getRows() != matDims.rows) || (biasByIndex.getCols() != matDims.cols))
        {
            return false;
        }
    }
    return true;
}


/**
 * @brief Gets a vector representing an image
 *        performs the mlpnetwork's functions on the input vector
 *        returns a digit struct with the number on the picture
 * @param inputVector - the input vector, at size 784*1.
 * @return digit struct with the probability and index of the number in the picture
 */
Digit MlpNetwork::operator()(Matrix inputVector)
{
    // check the size of input

    Matrix inputForNextDense = inputVector; // the input vector

    // Goes over the denses in the network, for each dense performs activation function
    for (Dense& i : _denseArr)
    {
        inputForNextDense = i(inputForNextDense);
    }

    float maxProbability = 0;
    unsigned int maxIndex = 0;

    // Goes over the matrix and saves the index with the highest probability
    // the index represents the number that is on the input picture
    for (int i = 0; i < inputForNextDense.getRows() * inputForNextDense.getCols(); i++)
    {
        if (inputForNextDense[i] > maxProbability)
        {
            maxProbability = inputForNextDense[i];
            maxIndex = i;
        }
    }

    Digit newDigit;
    newDigit.probability = maxProbability; // the probability
    newDigit.value = maxIndex; // the number in the array represents the picture received

    return newDigit;
}
