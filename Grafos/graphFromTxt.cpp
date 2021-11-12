#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Load graph from text file as adjacency list and adjacency matrix.
//Complexity: O(n)
void loadGraph(int n, int m,
                vector<vector<int>> &adjList, vector<vector<bool>> &adjMatrix,
                string fileName){
  vector<bool> nodes(n, false); //Boolean matrix set as false the size of n
  vector<int> edges;

  //For each vertex add a row
  for(int i = 0; i < n; i++){
    adjMatrix.push_back(nodes);
    adjList.push_back(edges);
  }

  //It is a DAG (directed graph), therefore:
  // FROM origin vertex TO destination vertex 
  int from, to;
  ifstream inFile(fileName);
  string line;

  //For each line on the text file...
  while(getline(inFile, line)){
    string strLine = line;

    //... take the first (0) and third (2) character, and...
    from  = line[0] - 48; //48 is ASCII for 0; "line[n]" returns ASCII if the content is a number
    to    = line[2] - 48;

    //... either set index on matrix as true or push destination vertex to list.
    adjMatrix[from][to] = true;
    adjList[from].push_back(to);
  }
}


/*Is tree (overloades): Detects cycles on destination vertices.
  Works really similar to next isTree(...) function but it also takes
  the index of destination of a directed edge and checks if it was
  visited in order to detect a cycle.
  For furthermore information refer to the next isTree(...) function
Complexity: O(n)*/
bool isTree(int target, vector<bool> visited, vector<vector<int>> adjList){
  if(visited[target] == true){
    return true;
  }

  visited[target] = true;
  bool wasVisited = false;
  for(int i = 0; i < adjList[target].size(); i++){
    wasVisited = isTree(adjList[target][i], visited, adjList);
    if(wasVisited){
      return true;
    }
  }
  return false;
}

/*Is tree: Returns false if there is a cycle detected.
  It uses both recursion and double iteration.
  Iteration is used to go trough the matrix and recursion
  to do the same algorithm with each destination vertex.
Complexity: O(n^2)*/
bool isTree(vector<vector<int>> adjList){
  //Bolean list of visited elements
  vector<bool> visited(adjList.size(), false);

  //Flag to indicate if element was visited
  bool wasVisited = false;

  /*For each element on the list, check the origin vertex as visited
    and refer to the destination vertices.*/
  for(int i = 0; i < adjList.size(); i++){
    //Mark element as visited
    visited[i] = true;
    
    //Refer to the desination vertices
    for(int j = 0; j < adjList[i].size(); j++){
      //Set flag to the result of checking cycles on destination vertices
      wasVisited = isTree(adjList[i][j], visited, adjList);
      //If flag is true, there is a cycle. Therefore it is not a tree (return false)
      if(wasVisited){
        return false;
      }
    }
    visited[i] = true;
  }
  return true;
}

//Displays with text if the graph is tree or not.
void checkIsTree(vector<vector<int>> &adjList){
  cout << endl << "Graph is ";
  if(!isTree(adjList)){
    cout << "not ";
  } 
  cout << "A TREE" << endl << endl;
}

/*Displays boolean matrix with rows and columns indexes.
  Works better for sizes under 10.
  Displays trues as "T" and falses as a blak spaces.
Complexity: O(n^2)*/
void showAdjMatrix(const vector<vector<bool>> &adjMatrix) {
  cout << endl << "Adjacency matrix:" << endl;
  cout << "  ";
  for(int node = 0; node < adjMatrix.size(); node++){
    cout << node << " ";
  }
  cout << endl;
  for (int node = 0; node < adjMatrix.size(); node++) {
    cout << node << " ";
    for (int arc = 0; arc < adjMatrix.size(); arc++) {
      cout << (adjMatrix[node][arc] ? "T|" : " |");
    }
    cout << endl;
  }
}

/*Displays a list of each origin vertex followed by the destination vertices
  Adjacency list is a list of lists, there fore it is displayed as a matrix.
Complexity: O(n^2)*/
void showAdjList(const vector<vector<int>> &adjList) {
  cout << endl << "Adjacency list:" << endl;
  for (int node = 0; node < adjList.size(); node++){
    cout << "Node " << node << " -> ";
    for (int arc = 0; arc < adjList[node].size(); arc++){
      cout << adjList[node][arc] << " ";
    }
    cout << endl;
  }
}



int main(){

  /*Test 1:
  Text file contains the connections that constitute an unbalanced tree:
       0
    1     2
   3 4   5 6
  7         8
  Image: https://github.com/CristianCazares/AlgoritmosEstructuras/blob/main/Grafos/Graph.png
  */
  cout << "===Test 1===";
  vector<vector<bool>> adjMatrix;
  vector<vector<int>> adjList;
  int n, m;

  n = 9, m = 8;
  loadGraph(n, m, adjList, adjMatrix, "graphs.txt");

  showAdjList(adjList);
  showAdjMatrix(adjMatrix);
  checkIsTree(adjList); //Uses isTree function.
  cout << "------------------------" << endl;
  

  /*Test 2:
  Text file contains a "circle" graph.
  Image: https://github.com/CristianCazares/AlgoritmosEstructuras/blob/main/Grafos/Graph2.png
  */
  cout << "===Test 2===";
  vector<vector<bool>> adjMatrix2;
  vector<vector<int>> adjList2;
  n = 8, m = 8;
  loadGraph(n, m, adjList2, adjMatrix2, "graphs2.txt");
  showAdjList(adjList2);
  showAdjMatrix(adjMatrix2);
  checkIsTree(adjList2);
  cout << "------------------------" << endl;
  

  /*Test 3:
  Text file contains a graph with two cycles.
  Image: https://github.com/CristianCazares/AlgoritmosEstructuras/blob/main/Grafos/Graph3.png
  */
  cout << "===Test 3===";
  vector<vector<bool>> adjMatrix3;
  vector<vector<int>> adjList3;
  n = 5, m = 7;
  loadGraph(n, m, adjList3, adjMatrix3, "graphs3.txt");
  showAdjList(adjList3);
  showAdjMatrix(adjMatrix3);
  checkIsTree(adjList3);
  cout << "------------------------" << endl;


  /*Test 4:
  Text file contains nodes two cycles and also connected with themselves.
  Image https://github.com/CristianCazares/AlgoritmosEstructuras/blob/main/Grafos/Graph4.png
  */
  cout << "===Test 4===";
  vector<vector<bool>> adjMatrix4;
  vector<vector<int>> adjList4;
  n = 5, m = 9;
  loadGraph(n, m, adjList4, adjMatrix4, "graphs4.txt");
  showAdjList(adjList4);
  showAdjMatrix(adjMatrix4);
  checkIsTree(adjList4);
  cout << "------------------------" << endl;

  return 0;
}