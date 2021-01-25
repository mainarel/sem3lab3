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
		int size = getArcsCount();
		for (int i = 0; i < this->getArcsCount(); ++i) {
			if (this->arcs->Get(i)->getArc().first->getID() == first && this->arcs->Get(i)->getArc().second->getID() == second) {
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
				if (this->arcs->Get(i)->getArc().first->getID() == vertices->Get(j)->getID()) { frst = j; }
				if (this->arcs->Get(i)->getArc().second->getID() == vertices->Get(j)->getID()) { scnd = j; }
			}
			if (matrix[frst][scnd] > this->arcs->Get(i)->getWeight()) {
				matrix[frst][scnd] = this->arcs->Get(i)->getWeight();
			}
		}

		

		return matrix;
	}

};