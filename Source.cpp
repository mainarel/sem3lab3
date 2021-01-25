#include <iostream>
#include "Graph.h"
#include <string>
//using namespace std;

int main()
{
	//cout <<"mew";
	Graph<string>* graph = new Graph<string>();
	graph->addVertex("first");
	graph->addVertex("second");
	
	graph->addArc("A","B",1);
	graph->addArc("first", "second", 1);
	graph->addArc("first", "second", 2);
//	graph->removeArc("A","B");
}