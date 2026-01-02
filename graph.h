#include <string>
#include <stdexcept>
#include <map>
#include <iostream>
#include <limits>

using namespace std;

class GraphExcept: public runtime_error
{
        public:
                GraphExcept(const string& msg): runtime_error(msg) {};
};

/*
 * graph is represented as an adjacency matrix
 * the matrix is represented as the map 
 * 
 */


class Graph
{
	public:
		Graph();
		~Graph();

	typedef map<string, map<string, int>> AdjMatrix;
	typedef AdjMatrix::iterator r_iter; // iterator for adjacency matrix rows
	typedef map<string, int>::iterator c_iter; // iterator for adjacency matrix columns

		void addVertex(const string name);
		void removeVertex(const string name);

	void addEdge(const string v1, const string v2, const int weight);
	void removeEdge(const string v1, const string v2);
	bool edgeExist(const string v1, const string v2);
	int getWeight(const string v1, const string v2);
	void setWeight(const string v1, const string v2, const int weight);

		int countVertices() const;
		int countEdges() const;

		void print() const;
	private:
		constexpr static const int INF = numeric_limits<int>::max();
		int edges;
		AdjMatrix adjMatrix;
};

Graph::Graph()
{
	edges = 0;
}

Graph::~Graph()
{
	for (r_iter row = adjMatrix.begin(); row != adjMatrix.end(); ++row)
	{
		row->second.clear();
	}
	adjMatrix.clear();
}


void Graph::addVertex(const string name)
{
	if( adjMatrix.find(name) != adjMatrix.end())
	{
		throw GraphExcept("The vertex already exists!");
	}
	
	adjMatrix[name][name] = 0;

	if(adjMatrix.size() != 1)
	{
		for(r_iter row = adjMatrix.begin(); row != adjMatrix.end(); ++row)
		{
			if (row->first != name)
			{
				row->second[name] = INF;
				adjMatrix[name][row->first] = INF;
			}
		}
	}
}

void Graph::removeVertex(const string name)
{
	if( adjMatrix.find(name) == adjMatrix.end())
        {
                throw GraphExcept("The vertex does not exist");
        }

	for (r_iter it = adjMatrix.begin(); it != adjMatrix.end(); ++it)
	{
		it->second.erase(name);
	}
	adjMatrix.erase(name);
}

int Graph::countVertices() const
{
	return adjMatrix.size();
}

int Graph::countEdges() const
{
	return edges;
}

void Graph::addEdge(const string v1, const string v2, const int weight)
{
	if(v1 == v2)
        {
                throw GraphExcept("You can't add an edge between the same vertex");
        }

	if(adjMatrix[v1][v2] != INF)
	{
		throw GraphExcept("The edge already exists");
	}

	adjMatrix[v1][v2] = weight;
	edges++;
}

void Graph::removeEdge(const string v1, const string v2)
{
	if(v1 == v2)
        {
                throw GraphExcept("You can't remove an edge between the same vertex");
        }

	if (adjMatrix[v1][v2] == INF)
	{
		throw GraphExcept("The edge does not exist");
	}

	adjMatrix[v1][v2] = INF;
	edges--;
}

bool Graph::edgeExist(const string v1, const string v2)
{
	if (v1 == v2) return false;
	
	return adjMatrix[v1][v2] != INF;
}

int Graph::getWeight(const string v1, const string v2)
{
	return adjMatrix[v1][v2];
}

void Graph::setWeight(const string v1, const string v2, const int weight)
{
	if (v1 == v2) throw GraphExcept("The vertex can't have an edge with itself");
	adjMatrix[v1][v2] = weight;
}
