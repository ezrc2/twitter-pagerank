#pragma once

#include <map>
#include <stack>
#include <vector>
#include <iostream>

using std::map;
using std::stack;
using std::vector;

/**
 * DFS traversal class
 */
class DFS {
  public:
    /**
     * Traverses the matrix using DFS traversal
     * 
     * @param v The user ID to start the traversal at
     * @param adj The matrix to traverse
     * @param output_file The file to output the DFS traversal to
     * @return The vector that contains the order of the nodes visited
     */
    vector<int> Traverse(int v, map<unsigned long, unsigned int> &adj, const string& output_file);

};

#include "../src/DFS.cpp"
