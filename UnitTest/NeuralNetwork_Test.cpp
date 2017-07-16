
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../NeuralNetwork/NeuralNetwork.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NeuralNetworkTest
{
	using namespace neural_network;

	TEST_CLASS(NeuralNetwokUnitTest)
	{
	public :
		TEST_METHOD(InitNeuronHierarchyTest)
		{
			using namespace neural_network;

			NeuralNetworkCreateInfo create_info;
			create_info.ActivationFunction = new Tanh();
			create_info.InputDataSetInfo = { 0, 1 };
			create_info.LayerInfos.resize(3);
			create_info.LayerInfos[0].NeuronCount = 2;
			create_info.LayerInfos[1].NeuronCount = 4;
			create_info.LayerInfos[2].NeuronCount = 1;

			NeuralNetwork neuralNetwork(create_info);
			
			const auto& Layers = neuralNetwork.GetNeuronLayers();

			Assert::IsTrue(Layers.size() == create_info.LayerInfos.size());

			for (size_t i = 0; i < Layers.size(); ++i)
			{
				Assert::IsTrue(Layers[i].NeuronCount() == create_info.LayerInfos[i].NeuronCount);
			}
		}
	};
}