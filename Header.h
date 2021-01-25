#pragma once
#include "ListSequence.hpp"
#include <vector>
#include <utility>
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

		ID getName() {
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

			pair<Vertex<ID>*, Vertex<ID>*> getVertex() {
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

	void addVertex(ID id) {
		bool containVertex = false;
		Vertex<ID>* toAdd = new Vertex<ID>(id);

		for (int i = 0; i < this->getVertexCount(); i++) {
			if (this->vertexList->Get(i)->getName() == name) {
				containVertex = true;
				break;
			}
		}

		if (!containVertex) {
			vertexList->Prepend(toAdd);
		}
		else {
			cout << "\n\tThis Vertex is already in Graph!";
		}
	}











};