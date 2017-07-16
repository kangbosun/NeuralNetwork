
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
		static std::uniform_real_distribution<double> random(0, 1);

		return random(rnd);
	}

//===================================================================================

	Neuron::Neuron(double _value/* = 0.0*/) :
		Id(0),
		Value(_value)
	{
	}

	void Neuron::CreateConnections(size_t _connectionCount)
	{
		Connections.clear();
		Connections.resize(_connectionCount);
	}

	double Neuron::GetWeightedValue(size_t index)
	{
		verify(index < Connections.size());
		return Connections[index].Weight * Value;
	}

//===================================================================================

	NeuronLayer::NeuronLayer(const NeuronLayerCreateInfo & _createInfo) : Bias(1.0)
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

		Bias.CreateConnections(next_layer_nueron_count);
	}

	void NeuronLayer::ForwardPropagation(NeuronLayer& _prevLayer, const DataSetInfo & _dataSetInfo)
	{
		for (size_t i = 0; i < Neurons.size(); ++i)
		{
			double sum = 0;
			for (size_t n = 0; n < _prevLayer.NeuronCount(); ++n)
			{
				sum += _prevLayer[n].GetWeightedValue(i);
			}
			Neurons[i].Value = sum;
		}
	}

	Neuron & NeuronLayer::operator[](size_t _index)
	{
		verify(Neurons.size() > _index);
		return Neurons[_index];
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
		ActivationFunction = _createInfo.ActivationFunction;

		InputDataSetInfo = _createInfo.InputDataSetInfo;

		CreateLayers(_createInfo);

		ConnectNeurons();
	}


	NeuralNetwork::~NeuralNetwork()
	{
	}

	void NeuralNetwork::ForwardPropagation(const std::vector<double> _inputValues)
	{
		verify(_inputValues.size() == GetInputLayer().NeuronCount());

		SetState(State::ForwardPropagationing);

		// Setting Inputlayer
		NeuronLayer& input_layer = GetInputLayer();
		for (size_t i = 0; i < input_layer.NeuronCount(); ++i)
		{
			input_layer[i].Value = ActivationFunction->Normalize(_inputValues[i], InputDataSetInfo);
		}

		// hidden layers and output layer
		for (size_t i = 1; i < Layers.size(); ++i)
		{
			NeuronLayer& prev_layer = Layers[i - 1];
			NeuronLayer& curr_layer = Layers[i];

			curr_layer.ForwardPropagation(prev_layer, InputDataSetInfo);
		}

		SetState(State::ForwardPropagationFinished);
	}

//===================================================================================

	double Sigmoid::Get(double x)
	{
		return 1.0 / (1.0 + exp(-x));
	}

	double Sigmoid::GetDerivative(double x)
	{
		return 0.0;
	}

	double Sigmoid::Normalize(double x, DataSetInfo& _dataSetInfo)
	{
		return 0.0;
	}

	double Sigmoid::Denormalize(double x, DataSetInfo& _dataSetInfo)
	{
		return 0.0;
	}

//===================================================================================

	double Tanh::Get(double x)
	{
		return tanh(x);
	}

	double Tanh::GetDerivative(double x)
	{
		return 1 - (x * x);
	}

	double Tanh::Normalize(double x, DataSetInfo& _dataSetInfo)
	{
		return (x - _dataSetInfo.Min) / (_dataSetInfo.Max - _dataSetInfo.Min);
	}

	double Tanh::Denormalize(double x, DataSetInfo& _dataSetInfo)
	{
		return ( x * (_dataSetInfo.Max - _dataSetInfo.Min)) + _dataSetInfo.Min;
	}
	//===================================================================================
}