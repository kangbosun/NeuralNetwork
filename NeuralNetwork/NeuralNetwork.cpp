
#include <iostream>
#include "NeuralNetwork.h"
#include "Utils.h"

namespace neural_network
{
//===================================================================================
	NeuronConnection::NeuronConnection() :
		Weight(GetRandomWeight())
	{
	}

	double NeuronConnection::GetRandomWeight()
	{
		static std::mt19937_64 rnd;
		std::uniform_real_distribution<double> random(0, 1);

		return random(rnd);
	}

//===================================================================================

	Neuron::Neuron() :
		Id(0),
		Value(0.0)
	{
	}

	void Neuron::CreateConnections(size_t _connectionCount)
	{
		Connections.clear();
		Connections.resize(_connectionCount);
	}

//===================================================================================

	NeuronLayer::NeuronLayer(const NeuronLayerCreateInfo & _createInfo)
	{
		check(_createInfo.NeuronCount);
		uint32_t neuron_count = _createInfo.NeuronCount;

		Neurons.resize(neuron_count);
	}


	NeuronLayer& NeuralNetwork::GetInputLayer()
	{
		check(Layers.size() > 2);

		return Layers[0];
	}

	NeuronLayer& NeuralNetwork::GetOutputLayer()
	{
		check(Layers.size() > 2);

		return Layers[Layers.size() - 1];
	}

	void NeuronLayer::ConnectNeurons(const NeuronLayer& _nextLayer)
	{
		size_t next_layer_nueron_count = _nextLayer.Neurons.size();

		for (Neuron& neuron : Neurons)
		{
			neuron.CreateConnections(next_layer_nueron_count);
		}
	}

//===================================================================================

	void NeuralNetwork::CheckState(State _state)
	{
		check(CurrentState == _state);
	}


	void NeuralNetwork::ConnectNeurons()
	{
		SetState(State::ConnectingNeurons);

		// no out connections for output layer
		for (size_t i = 0; i < Layers.size() - 1; ++i)
		{
			NeuronLayer& current_layer = Layers[i];
			NeuronLayer& next_layer = Layers[i + 1];

			current_layer.ConnectNeurons(next_layer);
		}

		SetState(State::ConnectNeuronsFinished);
	}
		
	void NeuralNetwork::CreateLayers(const neural_network::NeuralNetworkCreateInfo & _createInfo)
	{
		// 1 input layer, least 1 hidden layer, 1 out layer
		check(_createInfo.LayerInfos.size() > 2);

		SetState(State::CreatingLayers);

		size_t layer_count = _createInfo.LayerInfos.size();

		for (size_t i = 0; i < layer_count; ++i)
		{
			Layers.emplace_back(NeuronLayer(_createInfo.LayerInfos[i]));
		}

		SetState(State::CreateLayersFinished);

	}

	NeuralNetwork::NeuralNetwork(const NeuralNetworkCreateInfo& _createInfo)
	{
		check(_createInfo.ActivationFunction != nullptr);

		CreateLayers(_createInfo);

		ConnectNeurons();
	}


	NeuralNetwork::~NeuralNetwork()
	{
	}

//===================================================================================

	double Sigmoid::Apply(double _in)
	{
		return 0.0;
	}

	double Sigmoid::Normalize(double _in)
	{
		return 0.0;
	}

//===================================================================================

}