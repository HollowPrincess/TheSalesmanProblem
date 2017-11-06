#include <vector>
#include <algorithm>
#include <map>
#include <iostream> //temporary
using namespace std;

class graph {
public:
	int nodesNum = 0;
	vector<vector<int>> adjacencyList;
	vector <int> priceHeap;
	graph() {};
	graph(graph * example) { 	//graph for Prims algorithm
		nodesNum = 2;
		adjacencyList.resize(1);
		int edgeCounter = -1;
		//add the cheapest edge
		while (adjacencyList.back().empty()) {
			edgeCounter++;
			if (example->adjacencyList[edgeCounter][2] == example->priceHeap.front()) {//if the cheapest
				for (int j = 0; j < 3; j++) {
					adjacencyList.back().push_back(example->adjacencyList[edgeCounter][j]);//add in new graph					
				};
			};
		};

	};
	graph() {
		//example graph
			//A=0,B=1,C=2,D=3,E=4,F=5,G=6
		nodesNum = 7;
		adjacencyList = {
		{0,1,7},{0,3,5},
		{1,2,8},{1,3,9},{1,4,7},
		{2,4,5},
		{3,4,15},{3,5,6},
		{4,5,8},{4,6,9},
		{5,6,11}
		};//{node1,node2,price of edge}		

		//temporary:
		for (int i = 0; i < adjacencyList.size(); i++) {
			priceHeap.push_back(adjacencyList[i][2]);
		};
		make_heap(priceHeap.begin(), priceHeap.end());
		sort_heap(priceHeap.begin(), priceHeap.end());//first - min; last - max;		
	}
	~graph() {}
};
void PrimsAlgorithm() {
	graph* example = new graph();
	graph* spanningTree = new graph(example);//now it has only the cheapest edge
	map <int, int> priorityQueueMap;//Map <node,the cheapest edge between this edge and tree>
	typedef pair <int, int> queuePair;
	for (int i = 0; i < example->nodesNum; i++) {
		priorityQueueMap.insert(queuePair(i, 0));//now nodes aren't in map
	};
	//deleting tree nodes from Queue:
	priorityQueueMap.erase(priorityQueueMap.find(spanningTree->adjacencyList[0][0]));//erase 0
	priorityQueueMap.erase(priorityQueueMap.find(spanningTree->adjacencyList[0][1]));//erase 3
	//adding adjoing graph nodes Queue:
	
	for (int edgesCounter = 0; edgesCounter < example->adjacencyList.size(); edgesCounter++) {
		if (priorityQueueMap.count(example->adjacencyList[edgesCounter][1]) || priorityQueueMap.count(example->adjacencyList[edgesCounter][0])){
			//if it isn't added edge
			if ((example->adjacencyList[edgesCounter][0] == spanningTree->adjacencyList[0][0]) || (example->adjacencyList[edgesCounter][0] == spanningTree->adjacencyList[0][1])) {
				//if it is an edge with one of added nodes (node1)
				//if (new edge cheaper OR nodes' price isn't in map) than add price to map 			
				if (priorityQueueMap.at(example->adjacencyList[edgesCounter][1]) == 0 || priorityQueueMap.at(example->adjacencyList[edgesCounter][1])>example->adjacencyList[edgesCounter][2]) {
					priorityQueueMap.at(example->adjacencyList[edgesCounter][1]) = example->adjacencyList[edgesCounter][2];
				};
			}
			else if ((example->adjacencyList[edgesCounter][1] == spanningTree->adjacencyList[0][0]) || (example->adjacencyList[edgesCounter][1] == spanningTree->adjacencyList[0][1])) {
				//if it is an edge with one of added nodes (node2)
				if (priorityQueueMap.at(example->adjacencyList[edgesCounter][0]) == 0
					|| priorityQueueMap.at(example->adjacencyList[edgesCounter][0]
						) > example->adjacencyList[edgesCounter][2]) {
					priorityQueueMap.at(example->adjacencyList[edgesCounter][0]) = example->adjacencyList[edgesCounter][2];
				};
			};
		};
	};
	while (!priorityQueueMap.empty()) {

	};
};

int main() {
	//PrimsAlgorithm();

	return 0;
}