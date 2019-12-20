#include "Network.h"
#include <math.h>
#include <algorithm>
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
	errors = 0;
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
		/**using cross entropy cost function much better than quadratic
		C=y*ln(a)+(1-y)*ln(1-a)
		where y is target output and a is activated value.
		dC/dw=(dC/da)(da/dz)(dz/dw)
		dC/da=a-y/a*(1-a)	;	da/dz= o'(z)=o(z)(1-o(z)) where o(z)=a		dz/dw=a^(l-1)-activated neuron of the previous layer
		dC/dw=(a-y)*a^(l-1)
		**/ 
		double a = layers.at(layers.size() - 1).GetNeurons().at(i).GetActivatedVals();
		double y = target.at(i);
		double e = (a - y);
		error.emplace_back(e);
		errors += -(y * log(a) + (1 - y) * log(1 - a));
	}
}

void Network::BackPropagation()
{
	//get gradient in the output layer.
	//g=(dC/da)*f'(x); where f'(x) is the derived activation function (sigmoid).
	//[gO1 gO2 gO3]=[y1'*e1	y2'*e2		y3'*e3];
	Matrix OutputGradient = Matrix(1, error.size(), false);
	std::vector <Matrix> w = weightconnections;
	for (int i = 0; i < error.size(); i++)
	{
		OutputGradient.SetValue(0, i, error.at(i));
		//OutputGradient.SetValue(0, i, layers.at(layers.size() - 1).GetNeurons().at(i).GetDerivedActivatedVals() * error.at(i));
	}
	Matrix deltaweights;
	Matrix FirstHiddenLayer = layers.at(layers.size() - 2).ActivatedVals();
	deltaweights = (OutputGradient.transpose() * FirstHiddenLayer).transpose();
	Matrix stepsize = deltaweights * learningrate;
	//[gO1				[w7	w8
	//gO2	*	[z1 z2]=w9	w10
	//gO3]				w11	w12]	then transpose so that we can subtract it from the original weightconnection
	weightconnections.at(layers.size() - 2) -= stepsize;
	std::cout << "Weight COnn at out" << std::endl;
	weightconnections.at(layers.size() - 2).Print();
	//[w7	w9		w11		-[w7'	w8'	T
	//w8	w10		w12]	  w9'	w10'		=
	//						  w11'	w12']
	OutputGradient.Print();
	//computing for the gradient in the hidden layer
	std::vector<Matrix> HiddenGradient;
	for (int i = layers.size() - 2; i > 0; i--)
	{
		//get the gradient of the 1st hidden layer
		Matrix currWeightConnections = w.at(i);
		Matrix derivedLayer = layers.at(i).DerivedActivatedVals();
		Matrix gradient = i == layers.size() - 2 ? OutputGradient.transpose() : HiddenGradient.back().transpose();	//if it is the 1st hidden layer 
																													// use gradient of the ouput otherwise
																													//use the current HiddenGradient
		
		Matrix activatedLayer = (i - 1) == 0 ? layers.at(0).Value() : layers.at(i - 1).ActivatedVals();				//if it is at the input layer use the 
																													//input values otherwise use the activated
		//computing for the gradient
		//[w7	w9		w11		*	[g1			
		// w8	w10		w12]		 g2		=	[gh1 gh2]
		//							 g3]
		/**Matrix m = (currWeightConnections * gradient).transpose();		//transposing it
		HiddenGradient.emplace_back(Matrix::Hadamard(m, derivedLayer));
		deltaweights = (HiddenGradient.back().transpose() * activatedLayer).transpose();**/	// deltaweights is just dC/dw...Refer to Gradient Descent Kuno program 
		Matrix m = (currWeightConnections * gradient).transpose();
		HiddenGradient.emplace_back(m);
		deltaweights = (HiddenGradient.back().transpose() * activatedLayer).transpose();
		Matrix stepsize = deltaweights * learningrate;										//stepsize=dC/dw* learningrate;
		weightconnections.at(i - 1) -= stepsize;													//newweightconnection=oldweightconnection-stepsize
	}
	error.clear();
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
	for (int i = 0; i < error.size(); i++)
	{
		std::cout << "error: "<<error.at(i) << "\t \t";
	}
	std::cout << std::endl;
	std::cout << "The total error :" << errors << std::endl;
	
}

double Network::GetTotalError()
{
	return errors;
}
