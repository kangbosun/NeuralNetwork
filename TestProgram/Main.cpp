
#include "../NeuralNetwork/NeuralNetwork.h"

void main()
{
	using namespace neural_network;

	NeuralNetworkCreateInfo create_info;
	create_info.ActivationFunction = new Tanh();
	create_info.InputDataSetInfo = { 0, 1 };
	create_info.LayerInfos.resize(3);
	create_info.LayerInfos[0].NeuronCount = 2;
	create_info.LayerInfos[1].NeuronCount = 4;
	create_info.LayerInfos[2].NeuronCount = 1;

	std::vector<double> inputValues = { 1, 0 };

	NeuralNetwork neuralNetwork(create_info);
	
	neuralNetwork.ForwardPropagation(inputValues);

	NeuronLayer& output_layer = neuralNetwork.GetOutputLayer();
}

