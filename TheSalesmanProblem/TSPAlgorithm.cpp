#include <vector>
#include <map> //priorityQueueMap
using namespace std;

multimap <int, vector<int>> priorityQueueMap;
multimap <int, vector<int>>::iterator mapIter;
typedef pair <int, vector<int>> queuePair;

class graph {
public:
	int nodesNum = 0;
	vector<vector<int>> adjacencyList;
	int lowestPrice;
	int root;

	graph(graph * example) { 	//graph for Prims algorithm
		nodesNum = 2;
		int edgeCounter = -1;
		//add node with the cheapest edge
		while (!root) {
			edgeCounter++;
			if (example->adjacencyList[edgeCounter][2] == example->lowestPrice) {//if the cheapest
				root = example->adjacencyList[edgeCounter][0];
				break;
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

		lowestPrice = 1000;
		for (int i = 0; i < adjacencyList.size(); i++) {
			if (adjacencyList[i][2] < lowestPrice) {
				lowestPrice = adjacencyList[i][2];
			};
		};
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
	int newNodeInGraph = spanningTree->root;

	for (int i = 0; i < example->nodesNum; i++) {
		if (i != newNodeInGraph) {
			tmp[0] = i;
			priorityQueueMap.insert(queuePair(1000, tmp));//now nodes are in map without prices and edges
		};
	};

	//adding adjoing graph nodes in Queue:
	//for (int nodesCounter = 0; nodesCounter < nodesWhichHasNotEdges.size(); nodesCounter++) {
	for (int edgesCounter = 0; edgesCounter < example->adjacencyList.size(); edgesCounter++) {
		//if first node is added than find second in mapQueue 
		if (example->adjacencyList[edgesCounter][0] == newNodeInGraph) {
			addingEdgeInQueue(example, edgesCounter, tmp, 1);
		}
		//if second
		else if (example->adjacencyList[edgesCounter][1] == newNodeInGraph) {
			addingEdgeInQueue(example, edgesCounter, tmp, 0);
		};
	};
	while (!priorityQueueMap.empty()) {
		//adding new node in tree (extract min)
		spanningTree->adjacencyList.push_back({ priorityQueueMap.begin()->second[1] ,priorityQueueMap.begin()->second[0],priorityQueueMap.begin()->first });
		newNodeInGraph = priorityQueueMap.begin()->second[0];
		priorityQueueMap.erase(priorityQueueMap.begin());
		//adding adjoing graph nodes in Queue:
		for (int edgesCounter = 0; edgesCounter < example->adjacencyList.size(); edgesCounter++) {
			//if first node is added than find second in mapQueue 
			if ((example->adjacencyList[edgesCounter][0] == newNodeInGraph)) {
				addingEdgeInQueue(example, edgesCounter, tmp, 1);
			}
			//if second
			else if ((example->adjacencyList[edgesCounter][1] == newNodeInGraph)) {
				addingEdgeInQueue(example, edgesCounter, tmp, 0);
			};
		};

	};
};

int main() {
	PrimsAlgorithm();

	return 0;
}