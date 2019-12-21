#pragma once
#include <math.h>
#include <algorithm>
#include <random>
class Neuron
{
public:
	Neuron(double val);
	void Activate();
	void DerivedActivated();
	void Initialize(double value);
	double GetValue();
	double GetActivatedVals();
	double GetDerivedActivatedVals();
	void Randomize();
private:
	double val = 0.00;
	double activatedval;
	double derived_activatedval;
};