#pragma once
#include <iostream>
#include <vector>

typedef std::vector<Node> Layer;

struct Node {
    double value;
};

struct Connection {
    Node inNode;
    Node outNode;
    double weight;
    bool enabled;
};

class NeuralNetwork {
public:
    NeuralNetwork(int numInputs, int numOutputs, int hiddenLayers);
    std::vector<double> ComputeOutput(const std::vector<double>& input);
    void CreateNewNode();

    std::vector<Layer> neuronLayers;
    std::vector<Connection> connections;
    int neuronCount;
};
