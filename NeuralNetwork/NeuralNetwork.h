#pragma once

#include <vector>
#include <random>

namespace neural_network
{
//===================================================================================
	struct NeuronConnection
	{
		double Weight;

		NeuronConnection();

	private :
		static double GetRandomWeight();
	};

//===================================================================================
	struct Neuron
	{
		size_t Id;
		double Value;
		
		std::vector<NeuronConnection> Connections;

		Neuron();

		void CreateConnections(size_t _connectionCount);
	};
//===================================================================================
	struct NeuronLayerCreateInfo
	{
		uint32_t	NeuronCount;
	};
//===================================================================================
	struct NeuronLayer
	{
	public :
		NeuronLayer(const NeuronLayerCreateInfo& _createInfo);
		
		void ConnectNeurons(const NeuronLayer& _nextLayer);

	protected :
		std::vector<Neuron> Neurons;
	};
//===================================================================================
	struct IActivationFunction
	{
		virtual double Apply(double _in) = 0;
		virtual double Normalize(double _in) = 0;
	};

	struct Sigmoid : public IActivationFunction
	{
		// Inherited via IActivationFunction
		virtual double Apply(double _in) override;
		virtual double Normalize(double _in) override;
	};

//===================================================================================
	struct NeuralNetworkCreateInfo
	{
		std::vector<NeuronLayerCreateInfo> LayerInfos;

		IActivationFunction* ActivationFunction;
	};


//===================================================================================
	class NeuralNetwork
	{
	public :
		enum State
		{
			CreatingLayers,
			CreateLayersFinished,
			ConnectingNeurons,
			ConnectNeuronsFinished,
			Loading,
			LoadFinished,
			SaveFinished,
			ForwardPropagationing,
			ForwardPropagationFinished,
			BackPropagationing,
			BackPropagationFinished,
		};
	public:
		void CreateLayers(const neural_network::NeuralNetworkCreateInfo & _createInfo);

		NeuralNetwork(const NeuralNetworkCreateInfo& _createInfo);
		
		~NeuralNetwork();

		NeuronLayer& GetInputLayer();
		NeuronLayer& GetOutputLayer();

	protected:
		void ConnectNeurons();
		void SetState(State _state) { CurrentState = _state; }
		void CheckState(State _state);

		State CurrentState;		
		std::vector<NeuronLayer> Layers;
	};
//===================================================================================
}