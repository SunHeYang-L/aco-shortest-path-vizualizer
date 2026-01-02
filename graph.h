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

	if(edgeExist(v1, v2) || edgeExist(v2, v1))
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

	if (!edgeExist(v1, v2))
	{
		throw GraphExcept("The edge does not exist");
	}

	adjMatrix[v1][v2] = INF;
	edges--;
}

bool Graph::edgeExist(const string v1, const string v2)
{
	if (v1 == v2) return false;
	
	// Check if v1 exists in the adjacency matrix
	r_iter row = adjMatrix.find(v1);
	if (row == adjMatrix.end()) return false;
	
	// Check if v2 exists in v1's row
	c_iter col = row->second.find(v2);
	if (col == row->second.end()) return false;
	
	// Check if the edge exists (not INF)
	return col->second != INF;
}

int Graph::getWeight(const string v1, const string v2)
{
	if (!edgeExist(v1, v2))
	{
		throw GraphExcept("The edge does not exist");
	}
	
	r_iter row = adjMatrix.find(v1);
	c_iter col = row->second.find(v2);
	return col->second;
}

void Graph::setWeight(const string v1, const string v2, const int weight)
{
	if (v1 == v2) throw GraphExcept("The vertex can't have an edge with itself");
	
	r_iter row = adjMatrix.find(v1);
	if (row == adjMatrix.end())
	{
		throw GraphExcept("The edge does not exist");
	}
	
	c_iter col = row->second.find(v2);
	if (col == row->second.end() || col->second == INF)
	{
		throw GraphExcept("The edge does not exist");
	}
	
	col->second = weight;
}
