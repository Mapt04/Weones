#pragma once
#include <iostream>
#include <vector>
#include <random>

struct Node {
    int id;
    double value;
};

struct Connection {
    Node inNode;
    Node outNode;
    double weight;
    bool enabled;
};

typedef std::vector<Node> Layer;

class NeuralNetwork {
public:
    NeuralNetwork(int numInputs, int numOutputs, int hiddenLayers);
    std::vector<double> ComputeOutput(const std::vector<double>& input);
    void CreateNewNode();
    void CreateNewConnection();
    void Display();
    float ActivationFunction(float x);

    std::vector<Layer> neuronLayers;
    std::vector<Connection> connections;
    int neuronCount;
};
