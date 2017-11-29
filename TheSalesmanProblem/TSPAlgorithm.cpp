#include <vector>
#include <map> //priorityQueueMap
#include <unordered_set> //salesmans' tour
using namespace std;

multimap <int, vector<int>> priorityQueueMap;//price, node1, node2
multimap <int, vector<int>>::iterator mapIter;
typedef pair <int, vector<int>> queuePair;
struct TreeNode {
	int nodeNum;//nodes' number 
	TreeNode * parent;
	vector <TreeNode*> children;//nodes' children
	vector <int> childEdgePrice; //price of edges between 	
};
struct Tree {
	TreeNode* root;
	map <int, TreeNode*> listOfNodes;
	//typedef pair <int, TreeNode*> nodeListPair;
};
typedef pair <int, TreeNode*> nodeListPair;
typedef pair <vector<int>, int> adjacencyMapListPair;
void addingEdgesInGraph(map <vector<int>, int>* adjacencyMapList, vector<vector<int>> &adjacencyList) {
	vector<int> tmp;
	for (int edgeCounter = 0; edgeCounter < adjacencyList.size(); edgeCounter++) {
		tmp.clear();
		tmp.push_back(adjacencyList[edgeCounter][0]);
		tmp.push_back(adjacencyList[edgeCounter][1]);
		adjacencyMapList->insert(adjacencyMapListPair(tmp, adjacencyList[edgeCounter][2]));
	};
};
class graph {
public:
	int nodesNum = 0;
	vector<vector<int>> adjacencyList;
	map <vector<int>, int>* adjacencyMapList;
	int lowestPrice;
	graph() {
		//example graph
		//A=0,B=1,C=2,D=3,E=4
		nodesNum = 5;
		adjacencyList = {
			{ 0,1,3 },{ 0,2,5 },{ 0,3,6 },{ 0,4,4 },
			{ 1,2,3 },{ 1,3,6 },{ 1,4,4 },
			{ 2,3,4 },{ 2,4,2 },
			{ 3,4,3 }
		};//{node1,node2,price of edge}				
		adjacencyMapList = new map <vector<int>, int>;
		addingEdgesInGraph(adjacencyMapList, adjacencyList);
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

void treeTraversal(TreeNode * currentNode, unordered_set<int> * tour) {
	tour->insert(currentNode->nodeNum);
	if (!currentNode->children.empty()) {
		for (int i = 0; i < currentNode->children.size(); i++) {
			currentNode = currentNode->children[i];
			treeTraversal(currentNode, tour);
			currentNode = currentNode->parent;
		};
	};
	if (currentNode->parent) {
		currentNode = currentNode->parent;
	};
};
void addingToTheTree(int parentNum, int newNodeNum, int price, Tree * spanningTree) {
	TreeNode* newNode = new TreeNode;
	newNode->nodeNum = newNodeNum;
	newNode->parent = spanningTree->listOfNodes.at(parentNum);
	spanningTree->listOfNodes.insert(nodeListPair(newNodeNum, newNode));
	newNode->parent->children.push_back(newNode);
	newNode->parent->childEdgePrice.push_back(price);
};
void PrimsAlgorithm() {
	graph* example = new graph();
	Tree* spanningTree = new Tree;//now it is empty
	for (int edgeCounter = 0; edgeCounter < example->adjacencyList.size(); edgeCounter++) {
		if (example->adjacencyList[edgeCounter][2] == example->lowestPrice) {//if the cheapest
			TreeNode * root = new TreeNode;
			root->nodeNum = example->adjacencyList[edgeCounter][0];
			spanningTree->root = root;
			spanningTree->listOfNodes.insert(nodeListPair(root->nodeNum, root));
			break;
		};//now it has only the cheapest edge
	};

	vector<int> tmp = { 0,0 };
	int newNodeInGraph = spanningTree->root->nodeNum;
	for (int i = 0; i < example->nodesNum; i++) {
		if (i != newNodeInGraph) {
			tmp[0] = i;
			priorityQueueMap.insert(queuePair(1000, tmp));//now nodes are in map without prices and edges
		};
	};

	//adding adjoing graph nodes in Queue:
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
		addingToTheTree(priorityQueueMap.begin()->second[1], priorityQueueMap.begin()->second[0], priorityQueueMap.begin()->first, spanningTree);
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
	unordered_set<int> * salesmansTour = new unordered_set<int>;
	TreeNode* currentNode = spanningTree->root;
	treeTraversal(currentNode, salesmansTour);
	//tour cost:
	unordered_set <int>::iterator iter, buffForIter;
	int tourCost = 0;
	iter = salesmansTour->begin();
	tmp.clear();
	tmp.push_back(*iter);
	iter++;
	while (iter != salesmansTour->end()) {
		tmp.push_back(*iter);
		if (tmp[0] < tmp[1]) {
			tourCost += example->adjacencyMapList->at(tmp);
			tmp.erase(tmp.begin());
		}
		else {
			tmp[0] += tmp[1];
			tmp[1] = tmp[0] - tmp[1];
			tmp[0] -= tmp[1];
			tourCost += example->adjacencyMapList->at(tmp);
			tmp.pop_back();
		};
		iter++;
	};
	tmp.push_back(*salesmansTour->begin());
	tourCost += example->adjacencyMapList->at(tmp);
};

int main() {
	PrimsAlgorithm();

	return 0;
}