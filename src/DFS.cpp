#include "../include/DFS.h"
//To view the comments they are avaliable at include/DFS.h

vector<int> DFS::Traverse(int v, map<unsigned long, unsigned int> &adj, const string& output_file){  
  map<int, bool> visit;
  stack<int> tempStack;
  vector<int> dataPoints;
  unsigned long u1, u2;
  std::ofstream output_stream(output_file);

  tempStack.push(v);
  output_stream << v << std::endl;
  visit[v] = true;

  int curr;
  int counter = 1;

  while ((!tempStack.empty()) && (counter < 50000)) {
  	curr = tempStack.top();
    tempStack.pop();
    dataPoints.push_back(curr);

    for (int i = 0; i < 500000; i++) {
      u2 = curr;
      u1 = i;
      if (adj.count(u2 * 500000 + u1)) {
        if (visit[i] == false) {
          tempStack.push(i);
          output_stream << i << std::endl;
          visit[i] = true;
          ++counter;
          if (counter >= 50000) {
            break;
          }
        }
      }
    }
  }

  output_stream.close();
  return dataPoints;
}
