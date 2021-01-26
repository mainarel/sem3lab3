#pragma once
#include "ListSequence.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <queue>

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
	const int INF = INT_MAX;

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
		for (int i = 0; i < size; i++) {
			if (id == this->vertices->Get(i)->getID()) {
				return true;
			}
		}
		return false;
	}

	bool HasArc(ID first, ID second) {
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
		if (!(HasVertex(id))) {
			Vertex<ID>* new_vertex = new Vertex<ID>(id);
			vertices->Prepend(new_vertex);
		}
		else {
			throw exception("Vertex  is already exists");
		}
	}

	void addArc(ID first, ID second, int weight) {
		if (!(HasArc(first, second))) {
			Arc<ID>* new_arc = new Arc<ID>(first, second, weight);
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
			throw exception("Arc  is already exists");
		}
	}

	void removeArc(ID first, ID second) {
		if (HasArc(first, second)) {
			this->arcs->RemoveAt(whereArc(first,second)); 
		}
		else {
			throw exception("This arc was not found in the graph");
			
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
			
			throw exception ("This vertex was not found in the graph");
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
				matrix[i][j] = INF;
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

	vector<vector<pair<ID, int>>> toAdjList() {
		int n = getVerticesCount();
		vector<vector<pair<ID, int>>> g(n);
		vector<vector<int>> AdjMatrix = getAdjMatrix();
		for (int i = 0; i < getVerticesCount(); i++) {
			g.push_back(vector<pair<ID, int>>(n));
			for (int j = 0; j < getVerticesCount(); j++) {
				if (AdjMatrix[i][j] != INF) {
					g[i].push_back(pair<ID, int>(vertices->Get(j)->getID(), AdjMatrix[i][j]));
					cout << vertices->Get(j)->getID() << "  " << AdjMatrix[i][j];
				}
			}
		}
		return g;
	}

	//void dijkstra(int start) {
	//	vector<vector<pair<ID, int>>> g = toAdjList();
	//	int n = getVerticesCount();
	//	int s = start; // стартовая вершина

	//	//массивы предков и расстояний
	//	vector<int> d(n, INF), p(n);
	//	d[s] = 0;
	//	priority_queue <pair<int, int>> q;
	//	q.push(make_pair(0, s));
	//	while (!q.empty()) {
	//		int v = q.top().second, cur_d = -q.top().first;
	//		q.pop();
	//		if (cur_d > d[v])  continue;

	//		for (size_t j = 0; j < g[v].size(); ++j) {
	//			int to = g[v][j].first,
	//				len = g[v][j].second;
	//			if (d[v] + len < d[to]) {
	//				d[to] = d[v] + len;
	//				p[to] = v;
	//				q.push(make_pair(-d[to], to));
	//			}
	//		}
	//	}
	//}



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
				if (vect[i][j] != INF) {
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