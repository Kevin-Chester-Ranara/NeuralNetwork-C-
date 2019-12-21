#include "Neuron.h"

Neuron::Neuron(double val)
	:
	val(val)
{
	Activate();
	DerivedActivated();
}

void Neuron::Activate()
{
	//using sigmoid function
	//f(x)=1/(1+e^-z).	where z=w*x+b.
	activatedval = 1 / (1 + exp(-val));

}

void Neuron::DerivedActivated()
{
	//f(x)
	derived_activatedval = activatedval * (1 - activatedval);
}

void Neuron::Initialize(double value)
{
	val = value;
	Activate();
	DerivedActivated();
}

double Neuron::GetValue()
{
	return val;
}

double Neuron::GetActivatedVals()
{
	return activatedval;
}

double Neuron::GetDerivedActivatedVals()
{
	return derived_activatedval;
}

void Neuron::Randomize()
{
	std::random_device rd;
	std::mt19937 random(rd());
	std::uniform_real_distribution<double> Dist(0, 1);
	val = Dist(random);
}
