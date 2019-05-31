#include "ADT_graph.h"  
#include <iostream>
#include <string>
// extra includes:
#include <stdexcept>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

/* class stored in PQ */
class Node {
public:
  ADT_Node<int>* node_ptr;
  Node(ADT_Node<int>* node_ptr) {
    this->node_ptr = node_ptr;
  }
};

class EdgeNode {
public:
  ADT_Edge<int>* edge_ptr;
  EdgeNode(ADT_Edge<int>* edge_ptr) {
    this->edge_ptr = edge_ptr;
  }
};

/* functions to be used */
void Dijkstra(string depart, string dest, ADT_Graph<int>* Graph, ofstream& outputstream);
bool nodeComp(Node* node1, Node* node2);
bool edgeComp(EdgeNode* edge1, EdgeNode* edge2);
bool sameSet(ADT_Node<int>* node1, ADT_Node<int>* node2);
void unionSet(set<string>* set1, set<string>* set2);

int main(int argc, char* argv[]) {
  /* "./task2_solver graph.txt shortest_path_task.txt
   * ans_SP.txt ans_MST.txt" */
  if (argc != 5) {
    cerr << "Wrong format of arguments given." << endl;
    return -1;
  }
  /* STEP 1: MAKE GRAPH */
  ADT_Graph<int>* graph = new ADT_Graph<int>("Final Project");
  string command, command2, name;
  string Node = "Node";
  string Edge = "Edge";
  int length;
  freopen(argv[1], "r", stdin);
  while (cin >> command) {
    if (command.compare(Node) == 0) {
      break;
    }
  }
  // add nodes
  while (cin >> command) {
    if (command.compare(Edge) == 0) {
      break;
    }
    graph->insertVertex(command, 0);
  }
  // add edges
  while (cin >> command) {
    cin >> command2 >> length;
    if (command > command2) {
      name = command2 + " ";
      name = name + command;
    }
    else {
      name = command + " ";
      name = name + command2;
    }
    graph->insertEdge(command, command2, name, length);
  }
  fclose(stdin);
  /* STEP 2: DIJKSTRA's ALGORITHM */
  ifstream dijkstra_r;
  ofstream dijkstra_w;
  dijkstra_r.open(argv[2], ifstream::in);
  dijkstra_w.open(argv[3]);
  while (dijkstra_r >> command) {
    dijkstra_r >> command2;
    Dijkstra(command, command2, graph, dijkstra_w);
  }
  dijkstra_r.close();
  dijkstra_w.close();
  /* STEP 3: MINIMAL SPANNING TREE (KRUSKAL's ALGORITHM) */
  ofstream kruskal;
  kruskal.open(argv[4]);
  //ADT_Graph<int>* kraph = new ADT_Graph<int>("MST");
  list<EdgeNode*> inefficientPQ;
  list<set<string>*> listOfSets;
  list<ADT_Node<int>*> NLT = graph->get_ADT_nodelist().get_node_list();
  typename list<ADT_Node<int>*>::iterator nodeIt;
  for (nodeIt = NLT.begin(); nodeIt != NLT.end(); nodeIt++) {
    string nodeName = (*nodeIt)->get_node_name();
    set<string>* newSet = new set<string>();
    newSet->insert(nodeName);
  }
  list<ADT_Edge<int>*> temp_list = graph->get_ADT_edgelist().get_edge_list();
  typename list<ADT_Edge<int>*>::iterator eit;
  for (eit = temp_list.begin(); eit != temp_list.end(); eit++) {
    EdgeNode* newEdge = new EdgeNode(*eit);
    inefficientPQ.push_back(newEdge);
  }
  inefficientPQ.sort(edgeComp); // make it a heap, but only need to do it this once
  while (!(inefficientPQ.empty())) {
    EdgeNode* temp = inefficientPQ.front();
    inefficientPQ.pop_front();
    list<ADT_Node<int>*> twoNodeList = temp->edge_ptr->endVertices();
    list<ADT_Node<int>*>::iterator tempIt = twoNodeList.begin();
    ADT_Node<int>* node1 = *tempIt;
    tempIt++;
    ADT_Node<int>* node2 = *tempIt;
    if (sameSet(node1, node2)) {
      // same set: do nothing
      continue;
    }
    else {
      // different sets: make a union
      set<string>* set1 = node1->get_set_ptr();
      set<string>* set2 = node2->get_set_ptr();
      unionSet(set1, set2);
    }
  }
  // now all edges have been checked.
  // check any of the sets
  set<string>* readySet = listOfSets.front();
  set<string>::iterator lastIt;
  int no = 1;
  for (lastIt = readySet->begin(); lastIt != readySet->end(); ++lastIt) {
    // elements already sorted
    string edge = *lastIt;
    kruskal << edge << " " << no << endl;
  }
  return 1;
}

void Dijkstra(string depart, string dest, ADT_Graph<int>* Graph, ofstream& outputstream) {
  list<Node*> inefficientPQ;
  int check = 1; // 0: unconnected, 1: connected
  list<ADT_Node<int>*> temp_list = Graph->get_ADT_nodelist().get_node_list();
  typename list<ADT_Node<int>*>::iterator it;
  for (it = temp_list.begin(); it != temp_list.end(); ++it) {
    if (depart.compare((*it)->get_node_name()) == 0) {
      // node to depart from
      (*it)->set_node_value(0);
    }
    else {
      (*it)->set_node_value(-1);
    }
    Node* newNode = new Node(*it);
    inefficientPQ.push_back(newNode);
  }
  int distance = -1;
  ADT_Node<int>* arrival;
  inefficientPQ.sort(nodeComp);
  while (!(inefficientPQ.empty())) {
    Node* temp = inefficientPQ.front();
    inefficientPQ.pop_front();
    if (temp->node_ptr->get_node_value() == -1) {
      std::cout << "Picked: " << temp->node_ptr->get_node_name() << std::endl;
      // the two nodes are not connected
      check = 0;
      break;
    }
    if (dest.compare(temp->node_ptr->get_node_name()) == 0) {
      arrival = temp->node_ptr;
      distance = temp->node_ptr->get_node_value();
      break;
    }
    typename list<ADT_Edge<int>*>::iterator incEdgeIt;
    list<ADT_Edge<int>*> incList = temp->node_ptr->incidentEdges();
    for (incEdgeIt = incList.begin(); incEdgeIt != incList.end(); ++incEdgeIt) {
      string z_name = (*incEdgeIt)->opposite(temp->node_ptr->get_node_name());
      ADT_Node<int>* z = Graph->get_ADT_nodelist().search_vertex(z_name);
      int distance_candidate = (temp->node_ptr->get_node_value()) + ((*incEdgeIt)->get_edge_value());
      if ((z->get_node_value() == -1) ||
	  (distance_candidate < z->get_node_value())) {
	z->set_node_value(distance_candidate);
	z->set_prev_node(temp->node_ptr);
	inefficientPQ.sort(nodeComp);
      }
    }
  }
  // check if connected
  if (check == 0) {
    outputstream << "The two nodes are not connected." << endl;
    return;
  }
  // 'arrival' has been initialized
  list<string> tempList;
  while (depart.compare(arrival->get_node_name()) != 0) {
    tempList.push_front(arrival->get_node_name());
    arrival = arrival->get_prev_node();
  }
  tempList.push_front(depart);
  for (list<string>::iterator tempListIt = tempList.begin();
       tempListIt != tempList.end(); ++tempListIt) {
    outputstream << *tempListIt << " ";
  }
  outputstream << distance << endl;
}

bool nodeComp(Node* node1, Node* node2) {
  int nv1 = node1->node_ptr->get_node_value();
  int nv2 = node2->node_ptr->get_node_value();
  if (nv1 == -1) {
    // -1 is 'infinity'
    return false;
  }
  else if (nv2 == -1) {
    // -1 is 'infinity'
    return true;
  }
  return (nv1 < nv2);
}

bool sameSet(ADT_Node<int>* node1, ADT_Node<int>* node2) {
  // all node names are different, and set is ordered -> check first element
  set<string>* set1 = node1->get_set_ptr();
  set<string>* set2 = node2->get_set_ptr();
  set<string>::iterator it1 = set1->begin();
  string elem1_in_set1 = *it1;
  set<string>::iterator it2 = set2->begin();
  string elem2_in_set2 = *it2;
  if (elem1_in_set1.compare(elem2_in_set2) == 0) {
    return true;
  }
  return false;
}

void unionSet(set<string>* set1, set<string>* set2) {
  set<string>::iterator it;
  for (it = set1->begin(); it != set1->end(); ++it) {
    string insert_string = *it;
    set2->insert(insert_string);
  }
  for (it = set2->begin(); it != set2->end(); ++it) {
    string insert_string = *it;
    set1->insert(insert_string);
  }
}

bool edgeComp(EdgeNode* edge1, EdgeNode* edge2) {
  int ev1 = edge1->edge_ptr->get_edge_value();
  int ev2 = edge2->edge_ptr->get_edge_value();
  return (ev1 < ev2);
}
