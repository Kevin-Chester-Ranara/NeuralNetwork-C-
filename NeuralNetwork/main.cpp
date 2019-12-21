#include "Network.h"
#include <algorithm>
#include <windows.data.json.h>
int main()
{
	std::vector<int> topology = { 3,2,3 };
	std::vector<int> topo1 = { 7,5,4,4,7 };
	std::vector<double> Input = { 1,0,1 };
	std::vector<double> Input1 = { 1,0,0,1,1,1,1 };
	Network ann = Network(topo1);
	ann.Initialize(Input1);
	ann.SetTarget(Input1);
	ann.FeedForward();
	ann.SetErrors();
	ann.BackPropagation();
	while (ann.GetTotalError() > 0.1)
	{
		ann.FeedForward();
		ann.SetErrors();
		ann.Print();
		ann.BackPropagation();
		//ann.FeedForward();
		//ann.SetErrors();
		//ann.Print();
	}
	
	return 0;
}