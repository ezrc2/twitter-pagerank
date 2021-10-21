#include "../cs225/catch/catch.hpp"

#include <map>
#include <set>
#include <string>
#include <vector>
#include <cmath>

using std::string;
using std::vector;
using std::map;
using std::multimap;

#include "../include/file_reader.h"
#include "../include/DFS.h"
#include "../include/pagerank.h"
#include "../include/diagram.h"

const string kInput = "tests/sample_data.txt";
const string kOutput = "tests/temp_output.txt"; // placeholder file, not used

TEST_CASE("Matrix Data", "[matrix]") {
  FileReader fr;
  map<unsigned long, unsigned int> matrix = fr.GetMatrixData(kInput, kOutput);

  REQUIRE(matrix.size() == 6);

  map<unsigned long, unsigned int> expected;
  expected.insert(std::make_pair(500000, 1));
	expected.insert(std::make_pair(1000000, 1));
	expected.insert(std::make_pair(1000001, 3));
  expected.insert(std::make_pair(1500002, 1));
	expected.insert(std::make_pair(2000001, 3));
	expected.insert(std::make_pair(2000003, 5));

  REQUIRE(matrix == expected);
}

TEST_CASE("Adjacency Matrix", "[matrix]") {
  FileReader fr;
  multimap<int, int> adjacency_matrix = fr.GetPageRankData(kInput, kOutput);
  
	REQUIRE(adjacency_matrix.size() == 6);

	multimap<int, int> expected;
	expected.insert(std::make_pair(0, 1));
	expected.insert(std::make_pair(0, 2));
	expected.insert(std::make_pair(1, 2));
  expected.insert(std::make_pair(1, 4));
	expected.insert(std::make_pair(2, 3));
	expected.insert(std::make_pair(3, 4));

	REQUIRE(adjacency_matrix == expected);
}

TEST_CASE("DFS Testing", "[dfs]") {
  FileReader fr;
  map<unsigned long, unsigned int> matrix = fr.GetMatrixData(kInput, kOutput);

  DFS dfs;
  vector<int> temp = dfs.Traverse(4, matrix, "tests/dfs_temp.txt");

  int array[5] = {4, 3, 2, 0, 1};

  for (int i = 0; i < 5; i++) {
    REQUIRE(array[i] == temp[i]);
  }
}

TEST_CASE("PageRank Test", "[pagerank]") {
  FileReader fr;
  multimap<int, int> adjacency_matrix = fr.GetPageRankData(kInput, kOutput);
  REQUIRE(adjacency_matrix.size() == 6);

  PageRank pr(adjacency_matrix, kOutput);
  vector<pair<int, double>> ranked_users = pr.GetRankedUsers();

  SECTION("Descending") {
    for (size_t i = 0; i < ranked_users.size() - 1; i++) {
      REQUIRE(ranked_users[i].second >= ranked_users[i + 1].second);
    }
  }

  SECTION("PageRank values") {
    vector<pair<int, double>> expected;
    expected.push_back(std::make_pair(4, 0.1176));
    expected.push_back(std::make_pair(3, 0.0817));
    expected.push_back(std::make_pair(2, 0.0609));
    expected.push_back(std::make_pair(1, 0.0427));
    expected.push_back(std::make_pair(0, 0.03));

    for (size_t i = 0; i < ranked_users.size(); i++) {
      REQUIRE(ranked_users[i].first == expected[i].first);
      REQUIRE(fabs(ranked_users[i].second == expected[i].second) < 1e-5);
    }

  }
}

TEST_CASE("ForceDirected Test", "[forcedirected]") {
  FileReader fr;
  vector<pair<int, double>> pageusers = fr.ReadTopUsers("tests/pagerank_test_data.txt", 3);
  map<unsigned long, unsigned int> newMap = fr.ReadMatrixData("tests/pagerank_adj_matrix.txt");
    
    srand(420);
    Diagram dr(pageusers, newMap, 20);
    dr.updateDistances(0);
    dr.drawDiagram("tests/diagramtemp.png");
    cs225::PNG key;
    key.readFromFile("tests/diagramkey.png");
    cs225::PNG tobetested;
    tobetested.readFromFile("tests/diagramtemp.png");
    REQUIRE(key == tobetested);


}