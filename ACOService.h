#include "graph.h"
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

class ACOService
{
	public:
		ACOService(const map<string, map<string, int>>& adjacencyMatrix);
		~ACOService();

		// Getters
		vector<string> getVertices() const;
		int getWeight(const string v1, const string v2);
		int getPheromone(const string v1, const string v2);
		
		// ACO methods
		void iterate();
		
		// Get iterations made
		int getIterationsMade() const;

	private:
		Graph graph;
		int iterationsMade;
};

ACOService::ACOService(const map<string, map<string, int>>& adjacencyMatrix)
	: iterationsMade(0)
{
	// Extract all unique vertices from the adjacency matrix
	set<string> uniqueVertices;
	for (const auto& row : adjacencyMatrix)
	{
		uniqueVertices.insert(row.first);
		for (const auto& col : row.second)
		{
			uniqueVertices.insert(col.first);
		}
	}
	
	// Add all vertices to the graph
	for (const string& vertex : uniqueVertices)
	{
		graph.addVertex(vertex);
	}
	
	// Add all edges from the adjacency matrix
	for (const auto& row : adjacencyMatrix)
	{
		const string& v1 = row.first;
		for (const auto& col : row.second)
		{
			const string& v2 = col.first;
			int weight = col.second;
			
			// Skip self-loops (diagonal entries with value 0)
			if (v1 == v2 && weight == 0)
			{
				continue;
			}
			
			// Add edge if it doesn't already exist
			if (!graph.edgeExist(v1, v2) && !graph.edgeExist(v2, v1))
			{
				graph.addEdge(v1, v2, weight);
			}
		}
	}
}

ACOService::~ACOService()
{
}

vector<string> ACOService::getVertices() const
{
	return graph.getVertices();
}

int ACOService::getWeight(const string v1, const string v2)
{
	return graph.getWeight(v1, v2);
}

int ACOService::getPheromone(const string v1, const string v2)
{
	return graph.getPheromone(v1, v2);
}

void ACOService::iterate()
{
	// TODO: Implement ACO iteration
	// This will contain the ant colony optimization algorithm logic
	iterationsMade++;
}

int ACOService::getIterationsMade() const
{
	return iterationsMade;
}
