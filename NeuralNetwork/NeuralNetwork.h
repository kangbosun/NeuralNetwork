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
	
	struct DataSetInfo
	{
		double Min;
		double Max;
	};

//===================================================================================
	struct Neuron
	{
		size_t Id;
		double Value;
		
		std::vector<NeuronConnection> Connections;

		Neuron(double _value = 0.0);

		void CreateConnections(size_t _connectionCount);

		double GetWeightedValue(size_t index);
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

		void ForwardPropagation(NeuronLayer& _prevLayer, const DataSetInfo& _dataSetInfo);

		Neuron& operator[](size_t _index);

		size_t NeuronCount() const { return Neurons.size(); }

	protected :
		std::vector<Neuron> Neurons;
		Neuron Bias;
	};

//===================================================================================
	struct IActivationFunction
	{
		virtual double Get(double x) = 0;
		virtual double GetDerivative(double x) = 0;

		virtual double Normalize(double x, DataSetInfo& _dataSetInfo) = 0;
		virtual double Denormalize(double x, DataSetInfo& _dataSetInfo) = 0;
	};

	struct Sigmoid : public IActivationFunction
	{
		// Inherited via IActivationFunction
		virtual double Get(double _in) override;
		virtual double GetDerivative(double x) override;

		virtual double Normalize(double _in, DataSetInfo& _dataSetInfo) override;
		virtual double Denormalize(double x, DataSetInfo& _dataSetInfo) override;	
	};

	struct Tanh : public IActivationFunction
	{
		// Inherited via IActivationFunction
		virtual double Get(double x) override;
		virtual double GetDerivative(double x) override;

		virtual double Normalize(double x, DataSetInfo& _dataSetInfo) override;
		virtual double Denormalize(double x, DataSetInfo& _dataSetInfo) override;
	};

//===================================================================================
	struct NeuralNetworkCreateInfo
	{
		std::vector<NeuronLayerCreateInfo> LayerInfos;

		IActivationFunction* ActivationFunction;

		DataSetInfo InputDataSetInfo;
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

		const std::vector<NeuronLayer>& GetNeuronLayers() const { return Layers; }

		void ForwardPropagation(const std::vector<double> _inputValues);

	protected:
		void ConnectNeurons();
		void SetState(State _state) { CurrentState = _state; }
		void CheckState(State _state);

		State CurrentState;		
		std::vector<NeuronLayer> Layers;

		IActivationFunction* ActivationFunction;

		DataSetInfo InputDataSetInfo;
	};
//===================================================================================
}