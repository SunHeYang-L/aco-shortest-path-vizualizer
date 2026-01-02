#include "ACOService.h"
#include <iostream>

using namespace std;

int main()
{
	map<string, map<string, int>> adjacencyMatrix;
	
	adjacencyMatrix["A"]["A"] = 0;
	adjacencyMatrix["A"]["B"] = 5;
	adjacencyMatrix["A"]["C"] = 10;
	adjacencyMatrix["B"]["A"] = 5;
	adjacencyMatrix["B"]["B"] = 0;
	adjacencyMatrix["B"]["C"] = 3;
	adjacencyMatrix["C"]["A"] = 10;
	adjacencyMatrix["C"]["B"] = 3;
	adjacencyMatrix["C"]["C"] = 0;
	
	ACOService aco(adjacencyMatrix);
	
	cout << "Vertices: ";
	for (const string& v : aco.getVertices())
	{
		cout << v << " ";
	}
	cout << endl;
	
	cout << "Weight A->B: " << aco.getWeight("A", "B") << endl;
	cout << "Pheromone A->B: " << aco.getPheromone("A", "B") << endl;
	cout << "Iterations: " << aco.getIterationsMade() << endl;
	
	aco.iterate();
	cout << "Iterations after iterate(): " << aco.getIterationsMade() << endl;
	
	return 0;
}
