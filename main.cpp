#include "graph.h"
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

        const double testWeightAB = 1.0;
        const double testWeightBA = 2.0;

        graph.addEdge("A", "B", testWeightAB);
        graph.addEdge("B", "A", testWeightBA);
	
	assert(graph.countVertices() == 2);
        assert(graph.countEdges() == 2);
        assert(graph.edgeExist("A", "B"));
        assert(graph.getWeight("A", "B") == testWeightAB);
        assert(graph.getWeight("B", "A") == testWeightBA);

        graph.removeEdge("B", "A");
        assert(graph.edgeExist("B", "A") == false);
        assert(graph.countEdges() == 1);

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
