#include "Pathfinding.h"
using namespace sf;
using namespace std;

// This class is to utilize BFS (breadth-first) for our graph classes.
//Pathfinding::Pathfinding() {
//
//	//vector <int> visited;
//	//vector <int> queue;
//}

// FIX LATER

//vector <int> Pathfinding::BFS (int g, int source, int target) {
//
//	visited = vector <int>();
//	queue = vector <int>();
//
//	queue.push_back(source);
//
//	while (!visited.contains(target)) {
//		int here = queue.removeFirst();
//
//		if (!visited.contains(here)) {
//			visited.add(here);
//
//			for (Edge neighbour : g.neighbours(here)) {
//				if (!visited.contains(neighbour.to())) {
//					queue.add(neighbour.to());
//				}
//			}
//		}
//	}
//	return visited;
//}
