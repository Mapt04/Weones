#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(int numInputs, int numOutputs, int hiddenLayers) {
    Layer inputLayer;
    Layer outputLayer;
    neuronCount = 0;
    for (int i = 0; i < numInputs; i++) {
        inputLayer.push_back(Node{0.0});
        neuronCount++;
    }

    neuronLayers.push_back(inputLayer);

    for (int i = 0; i < hiddenLayers; i++) {
        Layer layer;
        neuronLayers.push_back(layer);
    }

    for(int i = 0; i < numOutputs; i++) {
        outputLayer.push_back(Node{0.0});
        neuronCount++;
    }

    neuronLayers.push_back(outputLayer);
}

std::vector<double> NeuralNetwork::ComputeOutput(const std::vector<double>& input) {

    //Reset neurons
    for (Layer layer: neuronLayers) {
        for(Node node: layer) {
            node.value = 0;
        }
    }

    //Feed input
    for (int i = 0; i < neuronLayers[0].size(); i++) {
        neuronLayers[0][i].value = input[i];
    }

    //Calculate Values
    for (Connection connection: connections) {
        if(connection.enabled) {
            connection.outNode.value += 
            connection.inNode.value * connection.weight;
        }
    }

    //Output vector
    std::vector<double> outputs;
    return neuronLayers[neuronLayers.size()-1];
}

void NeuralNetwork::CreateNewNode() {
    int layerIndex = rand() % (neuronLayers.size() - 2) + 1;
    Node newNode;
    newNode.value = 0.0;

    neuronLayers[layerIndex].push_back(newNode);
    neuronCount++;
}

void NeuralNetwork::CreateNewConnection() {

}