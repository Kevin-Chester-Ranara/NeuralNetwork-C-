#include "Network.h"
int main()
{
	std::vector<int> topology = { 3,2,3 };
	std::vector<int> topo1 = { 7,5,4,4,7 };
	std::vector<double> Input = { 1,1,1 };
	std::vector<double> Input1 = { 1,0,0,1,1,1,1 };
	Network ann = Network(topology);
	ann.Initialize(Input);
	ann.SetTarget(Input);
	ann.FeedForward();
	ann.SetErrors();
	//ann.Print();
	ann.BackPropagation();
	ann.FeedForward();
	ann.SetErrors();
	ann.Print();
	return 0;
}