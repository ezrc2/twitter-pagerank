#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>

#include "include/file_reader.h"
#include "include/DFS.h"
#include "include/pagerank.h"
#include "include/diagram.h"

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::multimap;
using std::string;

// Max user ID: 456,622
// user2 * 500,000 + user1 - matrix index calculation

int main(int argc, char *argv[]) { 
  FileReader fr;
  string action = argv[1];

  if (argc == 5 && action == "dfs") {

    DFS dfs;
    map<unsigned long, unsigned int> newMap = fr.GetMatrixData(argv[2], argv[3]);
    vector<int> dfsValues = dfs.Traverse(88,newMap, argv[4]);

  } if (argc == 5 && action == "pagerank"){

    multimap<int, int> adjacency_matrix = fr.GetPageRankData(argv[2], argv[3]);
    PageRank pr(adjacency_matrix, argv[4]);
    pr.GetRankedUsers();

  } if (argc == 5 && action == "diagram") {

    vector<pair<int, double>> pageusers = fr.ReadTopUsers(argv[2], 3);
    map<unsigned long, unsigned int> newMap = fr.ReadMatrixData(argv[3]);
    
    Diagram dr(pageusers, newMap, 20);
    dr.updateDistances(0);
    dr.drawDiagram(argv[4]);

  }
}