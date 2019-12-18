#pragma once
#include <vector>
#include "Neuron.h"
#include "Matrix.h"
class Layer
{
public:
	Layer(int num);
	void Initialize(std::vector<double> values);
	Matrix Value();
	Matrix ActivatedVals();
	Matrix DerivedActivatedVals();
	std::vector<Neuron> GetNeurons();
private:
	int num;
	std::vector <Neuron> neurons;
};