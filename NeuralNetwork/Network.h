#pragma once
#include "Layer.h"
#include <assert.h>

class Network
{
public:
	Network(std::vector<int> topology);
	void Initialize(std::vector<double> values);
	void FeedForward();
	void SetTarget(std::vector<double> Target);
	void SetErrors();
	void BackPropagation();
	void Print();
private:
	std::vector<int>	topology;
	std::vector<Layer>	layers;
	std::vector<Matrix> weightconnections;
	std::vector<double> error;
	std::vector<double> target;
	double				errors = 0.00;

};