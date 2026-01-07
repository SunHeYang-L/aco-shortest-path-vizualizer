#include "graph.h"
#include "ACOService.h"
#include <cassert>
#include <fstream>
#include <sstream>

using namespace std;

void testGraphClass()
{
	// GRAPH CLASS TESTS
        Graph graph;

        // check that there is no vertices and edges in the graph
        assert(graph.countVertices() == 0);
        assert(graph.countEdges() == 0);

        // testing vertices manipulations
        graph.addVertex("A");
        assert(graph.countVertices() == 1);
        assert(graph.countEdges() == 0);

        try
        {
                graph.addVertex("A");
        }
        catch (GraphExcept)
        {
                cout << "TEST PASSED: can't add the same vertex twice." << endl;
        }

        graph.addVertex("B");

        assert(graph.countVertices() == 2);
        assert(graph.countEdges() == 0);

        // testing edges manipulations

        const int testWeightAB = 1;

        graph.addEdge("A", "B", testWeightAB);
	
	assert(graph.countVertices() == 2);
        assert(graph.countEdges() == 1);
        assert(graph.edgeExist("A", "B"));
        assert(graph.getWeight("A", "B") == testWeightAB);

        graph.removeEdge("A", "B");
        assert(graph.edgeExist("A", "B") == false);
        assert(graph.countEdges() == 0);

        graph.removeVertex("B");

        assert(graph.countVertices() == 1);

        try
        {
                graph.removeVertex("B");
        }
        catch (GraphExcept)
        {
                cout << "TEST PASSED: Can't remove the same vertex twice" << endl;
        }

        // test non-directed graph: can't add edge if it already exists in opposite direction
        graph.addVertex("B");
        graph.addVertex("C");
        graph.addEdge("B", "C", 5);
        
        try
        {
                graph.addEdge("C", "B", 10);
        }
        catch (GraphExcept)
        {
                cout << "TEST PASSED: Can't add edge if it already exists between the same vertices (non-directed graph)" << endl;
        }

        // testing pheromone matrix using ACOService
        graph.addVertex("D");
        graph.addEdge("B", "D", 3);
        
        // Create ACOService from the graph's adjacency matrix
        map<string, map<string, int>> adjacencyMatrix;
        vector<string> vertices = graph.getVertices();
        for (const string& v1 : vertices)
        {
                for (const string& v2 : vertices)
                {
                        if (graph.edgeExist(v1, v2))
                        {
                                adjacencyMatrix[v1][v2] = graph.getWeight(v1, v2);
                        }
                        else if (v1 == v2)
                        {
                                adjacencyMatrix[v1][v2] = 0;
                        }
                }
        }
        ACOService acoService(adjacencyMatrix);
        
        // Test that pheromone is initialized to 0 when edge is added
        assert(acoService.getPheromone("B", "D") == 0);
        
        // Test that setter sets a value and it can be retrieved by getter
        const int testPheromone = 42;
        acoService.setPheromone("B", "D", testPheromone);
        assert(acoService.getPheromone("B", "D") == testPheromone);
        
        // Test that exception is thrown when trying to get pheromone on non-existent edge
        try
        {
                acoService.getPheromone("A", "D");
        }
        catch (EdgeNotExist)
        {
                cout << "TEST PASSED: Exception thrown when getting pheromone on non-existent edge" << endl;
        }
        
        // Test that exception is thrown when trying to set pheromone on non-existent edge
        try
        {
                acoService.setPheromone("A", "D", 10);
        }
        catch (EdgeNotExist)
        {
                cout << "TEST PASSED: Exception thrown when setting pheromone on non-existent edge" << endl;
        }

}

// this function fills a graph adjacency matrix from a file
// file format: NxN matrix, filled with:
// * 0 for row=column;
// * INF if the edge does not exist
// * edge weight, if edge exists

void readFromFile(const string filename, Graph* graph)
{
	ifstream input(filename);


	string line;
	int r_count = 0;
	int c_count = 0;
	while(getline(input, line))
	{
		string v_name = to_string(r_count);
		stringstream ss(line);
	        while(ss.good())
        	{
                	string substr;
                	getline(ss, substr, ',');
                	graph->addVertex(substr);
        	}

	}
	stringstream ss(line);
	while(ss.good())
	{
		string substr;
		getline(ss, substr, ',');
		graph->addVertex(substr);
	}

	// get edges weights
		
}

int main()
{
	testGraphClass();
}
