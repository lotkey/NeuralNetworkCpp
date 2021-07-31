#include <iostream>
#include "Activation.h"
#include "DataReader.h"
#include "Loss.h"
#include "Matrix.h"
#include "NeuralNetwork.h"

int main() {
    
    srand(time(NULL));
    DataReader dr = DataReader();
    dr.read("dataset.data", ",", false, false);
    dr.shuffle();
    DataTuple testingData = dr.spliceBack(0.2, true, true);
    DataTuple trainingData = dr.spliceFront(0.8, true, true);

    NeuralNetwork net = NeuralNetwork(3, testingData.inputSize(), 16, testingData.outputSize());
    std::cout << "Test loss: " << net.testDiscrete(testingData.getFeatures(), testingData.getLabels()) * 100 << "%\n";
    net.train(trainingData.getFeatures(), trainingData.getLabels(), 0.1, 500, 10);
    std::cout << "Test loss: " << net.testDiscrete(testingData.getFeatures(), testingData.getLabels()) * 100 << "%\n";
    std::cout << "Training loss: " << net.testDiscrete(trainingData.getFeatures(), trainingData.getLabels()) * 100 << "%\n";

}