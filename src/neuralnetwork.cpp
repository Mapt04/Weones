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
    // Feed input
    for (int i = 0; i < neuronLayers[0].size(); i++) {
        neuronLayers[0][i].value = input[i];
    }

    // Calculate Values
    for (int layerIndex = 1; layerIndex < neuronLayers.size(); layerIndex++) {
        for (Node& node : neuronLayers[layerIndex]) {
            node.value = 0; // Reset value
            for (Connection& connection : connections) {
                if (connection.enabled && connection.outNode.id == node.id) {
                    node.value += connection.inNode.value * connection.weight;
                }
            }
            node.value = ActivationFunction(node.value); // Apply activation function
        }
    }

    // Output vector
    std::vector<double> outputs;
    for (Node& outputNode : neuronLayers[neuronLayers.size() - 1]) {
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
}

void NeuralNetwork::CreateNewConnection() {
    if (neuronLayers.empty()) {
        std::cout << "No layers in the network." << std::endl;
        return;
    }

    bool connectionExists;
    int inLayerIndex, outLayerIndex;
    int inNodeIndex, outNodeIndex;
    Node inNode, outNode;

    do {
        inLayerIndex = rand() % (neuronLayers.size() - 1);
        outLayerIndex = inLayerIndex + 1 + rand() % (neuronLayers.size() - inLayerIndex - 1);

        // Check if layers are empty
        if (neuronLayers[inLayerIndex].empty() || neuronLayers[outLayerIndex].empty()) {
            continue;
        }

        inNodeIndex = rand() % neuronLayers[inLayerIndex].size();
        outNodeIndex = rand() % neuronLayers[outLayerIndex].size();

        inNode = neuronLayers[inLayerIndex][inNodeIndex];
        outNode = neuronLayers[outLayerIndex][outNodeIndex];

        // Check if connection already exists
        connectionExists = false;
        for (const auto& connection : connections) {
            if (connection.inNode.id == inNode.id && connection.outNode.id == outNode.id) {
                connectionExists = true;
                break;
            }
        }

    } while (neuronLayers[inLayerIndex].empty() || neuronLayers[outLayerIndex].empty() || connectionExists);

    // Create new connection if it doesn't exist
    if (!connectionExists) {
        Connection newConnection;
        newConnection.inNode = inNode;
        newConnection.outNode = outNode;
        connections.push_back(newConnection);
    }
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

float NeuralNetwork::ActivationFunction(float x) {
    if(x >= 0) return 1.0;
    else return 0.0;
}