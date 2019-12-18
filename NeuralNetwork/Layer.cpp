#include "Layer.h"

Layer::Layer(int num)
	:
	num(num)
{
	double initial = 0.00;
	for (int i = 0; i < this->num; i++)
	{
		neurons.emplace_back(initial);
	}
}

void Layer::Initialize(std::vector<double> values)
{
	for (int i = 0; i < neurons.size(); i++)
	{
		neurons.at(i).Initialize(values.at(i));
	}
}

Matrix Layer::Value()
{
	Matrix c = Matrix(1, int(neurons.size()), false);
	for (int i = 0; i < int(c.GetColumn()); i++)
	{
		c.SetValue(0, i, neurons.at(i).GetValue());
	}
	return c;
}

Matrix Layer::ActivatedVals()
{
	Matrix c = Matrix(1, int(neurons.size()), false);
	for (int i = 0; i < c.GetColumn(); i++)
	{
		c.SetValue(0, i, neurons.at(i).GetActivatedVals());
	}
	return c;
}

Matrix Layer::DerivedActivatedVals()
{
	Matrix c = Matrix(1, int(neurons.size()), false);
	for (int i = 0; i < int(c.GetColumn()); i++)
	{
		c.SetValue(0, i, neurons.at(i).GetDerivedActivatedVals());
	}
	return c;
}

std::vector<Neuron> Layer::GetNeurons()
{
	return neurons;
}
