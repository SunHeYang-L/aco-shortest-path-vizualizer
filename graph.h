#include <string>
#include <stdexcept>
#include <map>
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

class GraphExcept: public runtime_error
{
        public:
                GraphExcept(const string& msg): runtime_error(msg) {};
};

class EdgeNotExist: public runtime_error
{
        public:
                EdgeNotExist(const string& msg): runtime_error(msg) {};
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

	typedef map<string, map<string, int>> PheromoneMatrix;
	typedef PheromoneMatrix::iterator p_r_iter; // iterator for pheromone matrix rows
	typedef map<string, int>::iterator p_c_iter; // iterator for pheromone matrix columns

		void addVertex(const string name);
		void removeVertex(const string name);

	void addEdge(const string v1, const string v2, const int weight);
	void removeEdge(const string v1, const string v2);
	bool edgeExist(const string v1, const string v2);
	int getWeight(const string v1, const string v2);
	void setWeight(const string v1, const string v2, const int weight);
	int getPheromone(const string v1, const string v2);
	void setPheromone(const string v1, const string v2, const int pheromone);

		int countVertices() const;
		int countEdges() const;
		vector<string> getVertices() const;

		void print() const;
	private:
		int edges;
		AdjMatrix adjMatrix;
		PheromoneMatrix pheromoneMatrix;
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
	
	for (p_r_iter row = pheromoneMatrix.begin(); row != pheromoneMatrix.end(); ++row)
	{
		row->second.clear();
	}
	pheromoneMatrix.clear();
}


void Graph::addVertex(const string name)
{
	if( adjMatrix.find(name) != adjMatrix.end())
	{
		throw GraphExcept("The vertex already exists!");
	}
	
	adjMatrix[name][name] = 0;
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
	
	// Remove from pheromone matrix
	for (p_r_iter it = pheromoneMatrix.begin(); it != pheromoneMatrix.end(); ++it)
	{
		it->second.erase(name);
	}
	pheromoneMatrix.erase(name);
}

int Graph::countVertices() const
{
	return adjMatrix.size();
}

vector<string> Graph::getVertices() const
{
	vector<string> vertices;
	for (const auto& row : adjMatrix)
	{
		vertices.push_back(row.first);
	}
	return vertices;
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
	pheromoneMatrix[v1][v2] = 0;
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
		throw EdgeNotExist("The edge does not exist");
	}

	adjMatrix[v1].erase(v2);
	pheromoneMatrix[v1].erase(v2);
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
	
	// Entry exists, so edge exists (self-loops are already filtered out by v1 == v2 check)
	return true;
}

int Graph::getWeight(const string v1, const string v2)
{
	if (!edgeExist(v1, v2))
	{
		throw EdgeNotExist("The edge does not exist");
	}
	
	return adjMatrix[v1][v2];
}

void Graph::setWeight(const string v1, const string v2, const int weight)
{
	if (v1 == v2) throw GraphExcept("The vertex can't have an edge with itself");
	
	if (!edgeExist(v1, v2))
	{
		throw EdgeNotExist("The edge does not exist");
	}
	
	adjMatrix[v1][v2] = weight;
}

int Graph::getPheromone(const string v1, const string v2)
{
	if (!edgeExist(v1, v2))
	{
		throw EdgeNotExist("The edge does not exist");
	}
	
	return pheromoneMatrix[v1][v2];
}

void Graph::setPheromone(const string v1, const string v2, const int pheromone)
{
	if (v1 == v2) throw GraphExcept("The vertex can't have pheromone with itself");
	
	if (!edgeExist(v1, v2))
	{
		throw EdgeNotExist("The edge does not exist");
	}
	
	pheromoneMatrix[v1][v2] = pheromone;
}
