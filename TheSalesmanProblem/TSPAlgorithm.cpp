#include <vector>
#include <algorithm>
#include <functional> //greater
#include <queue> //priority_queue
#include <map> //priorityQueueMap
#include <iostream> //temporary
using namespace std;

multimap <int, vector<int>> priorityQueueMap;
multimap <int, vector<int>>::iterator mapIter, buffMapIter;
typedef pair <int, vector<int>> queuePair;

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
			{ 0,1,7 },{ 0,3,5 },
			{ 1,2,8 },{ 1,3,9 },{ 1,4,7 },
			{ 2,4,5 },
			{ 3,4,15 },{ 3,5,6 },
			{ 4,5,8 },{ 4,6,9 },
			{ 5,6,11 }
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
void addingEdgeInQueue(graph *example, int &edgesCounter, vector<int> &tmp, int numOfNode) {
	for (mapIter = priorityQueueMap.begin(); mapIter != priorityQueueMap.end(); mapIter++) {
		//if we find node in map
		if (mapIter->second[0] == example->adjacencyList[edgesCounter][numOfNode]) {
			//if new edge has lower price OR map hasn't edge with this node
			if ((mapIter->first > example->adjacencyList[edgesCounter][2])) {
				//than add new edge
				tmp[0] = mapIter->second[0];
				if (mapIter->second[0] != example->adjacencyList[edgesCounter][0]) {
					tmp[1] = example->adjacencyList[edgesCounter][0];
				}
				else {
					tmp[1] = example->adjacencyList[edgesCounter][1];
				};
				priorityQueueMap.insert(queuePair(example->adjacencyList[edgesCounter][2], tmp));
				priorityQueueMap.erase(mapIter);
			};
			break;
		};
	};
};

void PrimsAlgorithm() {
	graph* example = new graph();
	graph* spanningTree = new graph(example);//now it has only the cheapest edge
	vector<int> tmp = { 0,0 };
	vector<int> nodesWhichHasNotEdges;

	for (int i = 0; i < example->nodesNum; i++) {
		tmp[0] = i;
		priorityQueueMap.insert(queuePair(1000, tmp));//now nodes are in map without prices and edges
	};
	//deleting tree nodes from Queue:
	bool erasePrev = false;
	for (mapIter = priorityQueueMap.begin(); mapIter != priorityQueueMap.end(); mapIter++) {
		if (erasePrev) {
			priorityQueueMap.erase(buffMapIter);
			erasePrev = false;
		};
		if ((mapIter->second[0] == spanningTree->adjacencyList[0][0]) || (mapIter->second[0] == spanningTree->adjacencyList[0][1])) {
			buffMapIter = mapIter;
			erasePrev = true;
			nodesWhichHasNotEdges.push_back(mapIter->second[0]);
		};
	};
	if (erasePrev) {
		priorityQueueMap.erase(buffMapIter);
		erasePrev = false;
	};
	//adding adjoing graph nodes in Queue:
	for (int nodesCounter = 0; nodesCounter < nodesWhichHasNotEdges.size(); nodesCounter++) {
		for (int edgesCounter = 0; edgesCounter < example->adjacencyList.size(); edgesCounter++) {
			//if it isn't edge added in graph 
			if (!(((example->adjacencyList[edgesCounter][0] == nodesWhichHasNotEdges[0]) || (example->adjacencyList[edgesCounter][0] == nodesWhichHasNotEdges[1]))
				&& ((example->adjacencyList[edgesCounter][1] == nodesWhichHasNotEdges[0]) || (example->adjacencyList[edgesCounter][1] == nodesWhichHasNotEdges[1])))) {
				//if first node is added than find second in mapQueue 
				if ((example->adjacencyList[edgesCounter][0] == nodesWhichHasNotEdges[0]) || (example->adjacencyList[edgesCounter][0] == nodesWhichHasNotEdges[1])) {
					addingEdgeInQueue(example, edgesCounter, tmp, 1);
				}
				//if second
				else if ((example->adjacencyList[edgesCounter][1] == nodesWhichHasNotEdges[0]) || (example->adjacencyList[edgesCounter][1] == nodesWhichHasNotEdges[1])) {
					addingEdgeInQueue(example, edgesCounter, tmp, 0);
				};
			};
		};
	};
	nodesWhichHasNotEdges.clear();
	int newNodeInGraph;
	while (!priorityQueueMap.empty()) {

	};
};

int main() {
	PrimsAlgorithm();

	return 0;
}