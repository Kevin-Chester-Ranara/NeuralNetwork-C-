#include "Network.h"

Network::Network(std::vector<int> topology)
	:
	topology(topology)
{
	for (int i = 0; i < topology.size(); i++)
	{
		layers.emplace_back(topology.at(i));
	}
	for (int i = 0; i < topology.size() - 1; i++)
	{
		weightconnections.emplace_back(topology.at(i), topology.at(i + 1), true);
	}
}

void Network::Initialize(std::vector<double> values)
{
	layers.at(0).Initialize(values);
}

void Network::FeedForward()
{
	for (int i = 0; i < topology.size()-1; i++)
	{
		if (i == 0)
		{
			//from input layer to 1st hidden layer
			int x = i + 1;
			Matrix z = layers.at(i).Value() * weightconnections.at(i);
			layers.at(x).Initialize(z.Vectorize());
		}
		else
		{
			int x = i + 1;
			Matrix z = layers.at(i).ActivatedVals() * weightconnections.at(i);
			layers.at(x).Initialize(z.Vectorize());
		}
	}
}

void Network::SetTarget(std::vector<double> Target)
{
	target = Target;
}

void Network::SetErrors()
{
	assert(topology.at(layers.size()-1)==target.size());
	int outputneurons = layers.at(layers.size() - 1).GetNeurons().size();
	for (int i = 0; i < outputneurons; i++)
	{
		//using quadratic cost function; C=1/2*(y-a)^2;
		//where y is target output and a is activated value.
		//dC/da=(a-y)
		double e = layers.at(layers.size() - 1).GetNeurons().at(i).GetActivatedVals() - target.at(i);
		error.emplace_back(e);
		errors += e;
	}
}

void Network::BackPropagation()
{
	//get gradient in the output layer.
	//g=(dC/da)*f'(x); where f'(x) is the derived activation function (sigmoid).
	//[g1 g2 g3]=[y1'*e1	y2'*e2		y3'*e3];
	Matrix OutputGradient = Matrix(1, error.size(), false);
	std::vector <Matrix> w = weightconnections;
	for (int i = 0; i < error.size(); i++)
	{
		OutputGradient.SetValue(0, i, layers.at(layers.size() - 1).GetNeurons().at(i).GetDerivedActivatedVals() * error.at(i));
	}
	Matrix deltaweights;
	Matrix FirstHiddenLayer = layers.at(layers.size() - 2).ActivatedVals();
	deltaweights = OutputGradient.transpose() * FirstHiddenLayer;
	//[gO1				[w7	w8
	//gO2	*	[z1 z2]=w9	w10
	//gO3]				w11	w12]	then transpose so that we can subtract it from the original weightconnection
	Matrix dw = deltaweights.transpose();
	weightconnections.at(layers.size() - 2) -= dw;
	std::cout << "Weight COnn at out" << std::endl;
	weightconnections.at(layers.size() - 2).Print();
	//[w7	w8	w9		-[w7'	w8'	T
	//w10	w11	w12]	  w9'	w10'		=
	//					  w11'	w12']
	OutputGradient.Print();
	//computing for the gradient in the hidden layer
	std::vector<Matrix> HiddenGradient;
	for (int i = layers.size() - 2; i > 0; i--)
	{
		//get the gradient of the 1st hidden layer
		Matrix currWeightConnections = w.at(i);
		Matrix derivedLayer = layers.at(i).DerivedActivatedVals();
		Matrix gradient = i == layers.size() - 2 ? OutputGradient.transpose() : HiddenGradient.back().transpose();
		Matrix activatedLayer = (i - 1) == 0 ? layers.at(0).Value() : layers.at(i - 1).ActivatedVals();
		//computing for the gradient
		Matrix m = (currWeightConnections * gradient).transpose();
		HiddenGradient.emplace_back(Matrix::Hadamard(m, derivedLayer));
		Matrix dw = (HiddenGradient.back().transpose() * activatedLayer).transpose();
		weightconnections.at(i - 1) -= dw;
	}
}

void Network::Print()
{
	for (int i = 0; i < layers.size() - 1; i++)
	{
		if (i == 0)
		{
			layers.at(i).Value().Print();
		}
		weightconnections.at(i).Print();
		layers.at(i + 1).ActivatedVals().Print();
	}
	std::cout << "The errors are:" << std::endl;
	for (int i = 0; i < error.size(); i++)
	{
		std::cout << error.at(i) << "\t \t";
	}
}