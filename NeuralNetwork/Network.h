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
	double GetTotalError();
private:
	std::vector<int>	topology;
	std::vector<Layer>	layers;
	std::vector<Matrix> weightconnections;
	std::vector<double> error;
	std::vector<double> target;
	double	errors = 0.00;
	double learningrate = 0.01; //change the learning rate it is crappy
};