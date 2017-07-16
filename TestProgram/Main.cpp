
#include "../NeuralNetwork/NeuralNetwork.h"

void main()
{
	using namespace neural_network;

	NeuralNetworkCreateInfo create_info;
	create_info.ActivationFunction = new Sigmoid();
	
	NeuralNetwork neuralNetwork(create_info);

	// Test Commmit

}

