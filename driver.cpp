#include <iostream>
#include <vector>
#include "DataReader.h"
#include "NeuralNetwork.h"

int main() {
    srand(time(NULL));
    DataReader dr = DataReader();
    dr.read("dataset.data", ",", false, false);
    dr.shuffle();
    DataTuple testingData = dr.spliceBack(0.2, true, true);
    DataTuple trainingData = dr.spliceFront(0.8, true, true);

    std::vector<unsigned> topology{ testingData.inputSize(), 32, 16, testingData.outputSize() };
    NeuralNetwork net = NeuralNetwork(topology);
    std::cout << "Test loss: " << net.testDiscrete(testingData.getFeatures(), testingData.getLabels()) * 100 << "%\n";
    net.train(trainingData.getFeatures(), trainingData.getLabels(), 0.1, 500, 10);
    std::cout << "Test loss: " << net.testDiscrete(testingData.getFeatures(), testingData.getLabels()) * 100 << "%\n";
    std::cout << "Training loss: " << net.testDiscrete(trainingData.getFeatures(), trainingData.getLabels()) * 100 << "%\n";
}