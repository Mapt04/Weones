#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(int numInputs, int numOutputs, int hiddenLayers) {
    Layer inputLayer;
    Layer outputLayer;
    neuronCount = 0;
    for (int i = 0; i < numInputs; i++) {
        inputLayer.push_back(Node{neuronCount, 0.0});
        neuronCount++;
    }

    neuronLayers.push_back(inputLayer);

    for (int i = 0; i < hiddenLayers; i++) {
        Layer layer;
        neuronLayers.push_back(layer);
    }

    for(int i = 0; i < numOutputs; i++) {
        outputLayer.push_back(Node{neuronCount, 0.0});
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
    for(Node outputNode: neuronLayers[neuronLayers.size() - 1]) {
        outputs.push_back(outputNode.value);
    }
    return outputs;
}

void NeuralNetwork::CreateNewNode() {
    int layerIndex = rand() % (neuronLayers.size() - 2) + 1;
    Node newNode;
    newNode.value = 0.0;
    newNode.id = neuronCount;
    neuronCount++;

    neuronLayers[layerIndex].push_back(newNode);
    neuronCount++;
}

void NeuralNetwork::CreateNewConnection() {

    Connection newConnection;
    int inLayerIndex, outLayerIndex;
    int inNodeIndex, outNodeIndex;
    Node inNode, outNode;
    bool connectionExists = true;
    
    while (connectionExists) {
        inLayerIndex = rand() % (neuronLayers.size() - 1);
        outLayerIndex = rand() % (neuronLayers.size() - (inNodeIndex + 1)) + (inNodeIndex + 1);

        inNodeIndex = rand() % (neuronLayers[inLayerIndex].size() - 1);
        outNodeIndex = rand() % (neuronLayers[outLayerIndex].size() - 1);

        inNode = neuronLayers[inLayerIndex][inNodeIndex];
        outNode = neuronLayers[outLayerIndex][outNodeIndex];

        connectionExists = false;

        for (Connection connection: connections) {
            if(connection.inNode.id == inNode.id && connection.outNode.id == outNode.id) {
                connectionExists = true;
                break;
            }
        }
    }

    newConnection.inNode = inNode;
    newConnection.outNode = outNode;

    std::uniform_real_distribution<double> unif(-1,1);
    std::default_random_engine re;
    newConnection.weight = unif(re);
    newConnection.enabled = true;

    connections.push_back(newConnection);
}

void NeuralNetwork::Display() {
    for(int i = 0; i < neuronLayers.size(); i++) {
        if(neuronLayers[i].size() == 0) continue;
        std::cout << i << " | " ;
        for(int j = 0; j < neuronLayers[i].size(); j++) {
            std::cout << "• ";
        }
        std::cout << std::endl;
    }

    for(Connection connection: connections) {
        std::cout << connection.inNode.id << " --- " << connection.outNode.id << std::endl;
    }
}