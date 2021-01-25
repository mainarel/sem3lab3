#pragma once
#include "ListSequence.hpp"
#include <vector>
#include <utility>
#include <string>
using namespace std;

template <class ID>
class Graph {
public:
	template <class ID>
	//вершина
	class Vertex {
	private:
		ID id;
	public:
		Vertex(ID id) {
			this->id = id;
		}

		ID getID() {
			return this->id;
		}
	};
		//дуга
	template <class ID>
		class Arc {
		private:
			int weight;
			Vertex<ID>* from;
			Vertex<ID>* to;
		public:
			Arc(ID first, ID second, int weight) {
				this->weight = weight;
				this->from = new Vertex<ID>(first);
				this->to = new Vertex<ID>(second);
			}

			int getWeight() {
				return this->weight;
			}
			pair<Vertex<ID>*, Vertex<ID>*> getArc() {
				return make_pair(from, to);
			}
		};

private:
	ListSequence<Vertex<ID>*>* vertices;
	ListSequence<Arc<ID>*>* arcs;

public:
	Graph() {
		this->arcs = new ListSequence<Arc<ID>*>();
		this->vertices = new ListSequence<Vertex<ID>*>();
		}

	int getArcsCount() {
		return this->arcs->GetLength();
	}
	int getVerticesCount() {
		return this->vertices->GetLength();
	}
	bool HasVertex(ID id) {

		int size = getVerticesCount();
		for (int i = 0; i < size; i++) {
			if (id == this->vertices->Get(i)->getID()) {
				return true;
			}
		}
		return false;
	}

	bool HasArc(ID first, ID second) {
		int size = getArcsCount();
		for (int i = 0; i < this->getArcsCount(); ++i) {
			if (this->arcs->Get(i)->getArc().first->getID() == first && this->arcs->Get(i)->getArc().second->getID() == second) {
				return true;
			}
		}
		return false;
	}

	int whereArc(ID first, ID second) {
		for (int i = 0; i < this->getArcsCount(); ++i) {
			if (this->arcs->Get(i)->getArc().first->getID() == first && this->arcs->Get(i)->getArc().second->getID() == second) {
				return i;
			}
		}
		return -1;
	}

	int whereVertex(ID id) {
		for (int i = 0; i < this->getVerticesCount(); ++i) {
			if (id == this->vertices->Get(i)->getID()) {
				return i;
			}
		}
		return -1;
	}

	void addVertex(ID id) {
		Vertex<ID>* new_vertex = new Vertex<ID>(id);
		if (!(HasVertex(id))) {
			vertices->Prepend(new_vertex);
		}
		else {
			cout << "Vertex <"<<  id  <<"> is already exists" << endl;
		}
	}

	void addArc(ID first, ID second, int weight) {
		Arc<ID>* new_arc = new Arc<ID>(first, second, weight);
		if (!(HasArc(first, second))) {
			this->arcs->Prepend(new_arc);

			Vertex<ID>* firstVertex = new Vertex<ID>(first);
			Vertex<ID>* secondVertex = new Vertex<ID>(second);

			if (!(HasVertex(first))) {
				vertices->Prepend(firstVertex);
			}
			if (!(HasVertex(second))) {
				vertices->Prepend(secondVertex);
			}
		}
		else {
			cout << "Arc <" << first <<", "<< second << "> is already exists" << endl;
		}
	}

	void removeArc(ID first, ID second) {
		if (HasArc(first, second)) {
			this->arcs->RemoveAt(whereArc(first,second)); 
		}
		else {
			cout << "This arc was not found in the graph" << endl;
		}
	}

	void removeVertex(ID id) {
		if (HasVertex(id)) {
			for (int i = 0; i < this->getArcsCount(); ++i) {
				if (this->arcs->Get(i)->getArc().first->getID() == id) {
					removeArc(this->arcs->Get(i)->getArc().first->getID(), this->arcs->Get(i)->getArc().second->getID());
				}
				if (this->arcs->Get(i)->getArc().second->getID() == id) {
					removeArc(this->arcs->Get(i)->getArc().second->getID(), this->arcs->Get(i)->getArc().first->getID());
				}
			}
			this->vertices->RemoveAt(this->whereVertex(id));
		}
		else {
			cout << "This vertex was not found in the graph"<<endl;
		}
	}

	// Adjacency Matrix
	vector<vector<int>> getAdjMatrix() {
		vector<vector<int>> matrix(this->getVerticesCount(), vector<int>(this->getVerticesCount(), 0));
		//диагональ
		for (int i = 0; i < this->getVerticesCount(); ++i) {
			matrix[i][i] = 0;
		}

		for (int i = 0; i < this->getVerticesCount(); ++i) {
			for (int j = 0; j < this->getVerticesCount(); ++j) {
				matrix[i][j] = 9999;
			}
		}
		for (int i = 0; i < this->getArcsCount(); ++i) {
			int frst = 0;
			int scnd = 0;
			for (int j = 0; j < this->getVerticesCount(); ++j) {
				if (this->arcs->Get(i)->getArc().first->getID() == vertices->Get(j)->getID()) { 
					frst = j; 
				}
				if (this->arcs->Get(i)->getArc().second->getID() == vertices->Get(j)->getID()) {
					scnd = j; 
				}
			}
			if (matrix[frst][scnd] > this->arcs->Get(i)->getWeight()) {
				matrix[frst][scnd] = this->arcs->Get(i)->getWeight();
			}
		}
		return matrix;
	}

	void dijkstra(string StartVertex, string EndVertex) {
		int INF = 9999;
		int startnode;
		int endnode;
		for (int i = 0; i < this->getVerticesCount(); i++) {
			if (this->vertices->Get(i)->getID() == StartVertex) {
				startnode = i;
			}
			if (this->vertices->Get(i)->getID() == EndVertex) {
				endnode = i;
			}
		}
		vector<vector<int>> G = this->getAdjMatrix();
		vector<vector<int> > cost(this->getVerticesCount(), vector<int>(this->getVerticesCount(), 0));
		vector<int> distance(this->getVerticesCount()), pred(this->getVerticesCount());
		vector<int> visited(this->getVerticesCount());
		int count, mindistance, nextnode, i, j;
		for (i = 0; i < this->getVerticesCount(); i++)
			for (j = 0; j < this->getVerticesCount(); j++)
				if (G[i][j] == 0 || G[i][j] == INF)
					cost[i][j] = INF;
				else
					cost[i][j] = G[i][j];
		for (i = 0; i < this->getVerticesCount(); i++) {
			distance[i] = cost[startnode][i];
			pred[i] = startnode;
			visited[i] = 0;
		}
		distance[startnode] = 0;
		visited[startnode] = 1;
		count = 1;
		while (count < this->getVerticesCount() - 1) {
			mindistance = INF;
			for (i = 0; i < this->getVerticesCount(); i++)
				if (distance[i] < mindistance && !visited[i]) {
					mindistance = distance[i];
					nextnode = i;
				}
			visited[nextnode] = 1;
			for (i = 0; i < this->getVerticesCount(); i++)
				if (!visited[i])
					if (mindistance + cost[nextnode][i] < distance[i]) {
						distance[i] = mindistance + cost[nextnode][i];
						pred[i] = nextnode;
					}
			count++;
		}
		
		for (i = 0; i < this->getVerticesCount(); i++)
			if (i != startnode && i == endnode) {
				string graphAPI_V;
				if (distance[i] != INF) {
					cout << "\nDistance to Vertex <" << this->vertices->Get(i)->getID() << "> = " << distance[i];
					cout << "\nPath:" << this->vertices->Get(i)->getID();
					j = i;
					do {
						j = pred[j];
						cout << " <- " << this->vertices->Get(j)->getID();
					} while (j != startnode);
					
				}
				else {
					cout << "\n\tYou can't get to Vertex " << this->vertices->Get(endnode)->getID() << " from Vertex '" <<
						this->vertices->Get(startnode)->getID() << "'\n";
				}
			}
	}

	ListSequence<Vertex<ID>*>* getVetex() {
		return this->vertices;
	}

	void PrintAdjMatrix() {
		cout << "Adjacency Matrix:" << endl;
		vector<vector<int>> vect = getAdjMatrix();
		ListSequence<Graph<string>::Vertex<string>*>* Names = getVetex();

		cout << "      ";
		for (int i = 0; i < getVerticesCount(); i++) {
			cout << Names->Get(i)->getID() << "    ";
		}
		cout << endl;
		for (int i = 0; i < getVerticesCount(); i++) {
			cout << Names->Get(i)->getID() << " | ";
			for (int j = 0; j < getVerticesCount(); j++) {

				cout.width(3);
				//cout.setf(ios::left);

				if (vect[i][j] != 9999) {
					cout << vect[i][j] << "  ";
				}
				else {
					cout << "-" << "  ";
				}
			}
			cout << endl;
		}
	}
};