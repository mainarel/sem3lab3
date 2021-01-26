#include <iostream>
#include "Graph.h"
#include <string>
using namespace std;

int main() {
	Graph<string>* graph = new Graph<string>();
	string ID, fID, sID;
	int weight;
	while (true) {
		cout << "\n1. Add vertex\n2. Add arc\n3. Remove vertex (not work)\n4. Remove arc\n5. Print adjacency matrix\n6.Dijkstra algorithm \n7. Exit\n8. Example" << endl;
		int choice; cin >> choice;
		switch (choice) {
		case 1: {
			cout << "Enter vertex ID" << endl;
			cin >> ID;
			graph->addVertex(ID);
			break;
		}
		case 2: {
			cout << "Enter first vertex ID" << endl;
			cin >> fID;
			cout << "Enter second vertex ID" << endl;
			cin >> sID;
			cout << "Enter weight of arc" << endl;
			cin >> weight;
			graph->addArc(fID, sID, weight);
			break;
		}
		case 3: {
			cout << "Enter vertex ID to remove" << endl;
			cin >> ID;
			graph->removeVertex(ID);
			break;
		}
		case 4: {
			cout << "Enter first vertex ID of arc to remove" << endl;
			cin >> fID;
			cout << "Enter second vertex ID of arc to remove" << endl;
			cin >> sID;
			graph->removeArc(fID, sID);
			break;
		}
		case 5: {
			graph->PrintAdjMatrix();
			break;
		}
		case 6: {
			cout << "Enter first vertex ID" << endl;
			cin >> fID;
			cout << "Enter second vertex ID" << endl;
			cin >> sID;
			graph->dijkstra(fID,sID);
			break;
		}
		case 7: {
			exit(7);
		}
		case 8: {
			graph->addArc("A", "B", 2);
			graph->addArc("B", "C", 10);
			graph->addArc("A", "D", 2);
			graph->addArc("E", "C", 3);
			graph->addArc("A", "F", 1);
			graph->addArc("E", "F", 8);
			graph->addArc("A", "C", 20);
			graph->PrintAdjMatrix();
			graph->dijkstra("A", "C");

			break;
		}
		}
	}
	
}