#pragma once
#include "ListSequence.hpp"
#include <vector>
#include <utility>
using namespace std;

template <class T>
class Graph {
public:
	template <class ID>
	//вершина
	class Vertex {
	private:
		ID name;
	public:
		Vertex(ID name) {
			this->name = name;
		}

		ID getName() {
			return this->name;
		}
	};
		//дуга
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
	
public:
	ListSequence<Vertex<ID>*>* vertices;
	ListSequence<Arc<ID>*>* arcs;
	Graph() {
		this->arcs = new ListSequence<Arc<ID>*>();
		this->vertices = new ListSequence<Vertex<ID>*>();
		}

	void addVertex(Name name) {
		bool containVertex = false;
		Vertex<Name>* toAdd = new Vertex<Name>(name);

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