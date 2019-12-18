#pragma once
#include <math.h>
#include <algorithm>
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
private:
	double val = 0.00;
	double activatedval;
	double derived_activatedval;
};