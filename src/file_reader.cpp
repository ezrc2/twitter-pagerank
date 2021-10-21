#include "../include/file_reader.h"
//To view the comments they are avaliable at include/file_reader.h

map<unsigned long, unsigned int> FileReader::GetMatrixData(const string& input_file, const string& output_file) {
  // Matrix width: 500,000
  string interaction;
  int id1, id2, time;
  unsigned long index;

  std::ifstream input_stream(input_file);
  std::ofstream output_stream(output_file);

  map<unsigned long, unsigned int> m;

  while (!input_stream.eof()) {
    input_stream >> id1 >> id2 >> time >> interaction;

    if (interaction != "RE") {
      unsigned long u1 = id1;
      unsigned long u2 = id2;
      index = (u2 * 500000) + u1;

      m[index] += 1;
    }
  }

  for (auto itr = m.begin(); itr != m.end(); ++itr) {
    output_stream << itr->first << " " << itr->second << std::endl;
  }

  input_stream.close();
  output_stream.close();

  return m;
}

multimap<int, int> FileReader::GetPageRankData(const string& input_file, const string& output_file) {
  string interaction;
  int id1, id2, time;

  std::ifstream input_stream(input_file);
  std::ofstream output_stream(output_file);

  multimap<int, int> m;
  set<pair<int, int>> s;

  while (!input_stream.eof()) {
    input_stream >> id1 >> id2 >> time >> interaction;

    if (interaction != "RE") {
      s.insert(pair<int, int>(id1, id2));
    }
  }

  for (const auto& elem : s) {
    m.insert(elem);
  }

  for (const auto& edge : m) {
    output_stream << edge.first << " " << edge.second << std::endl;
  }

  input_stream.close();
  output_stream.close();

  return m;
}

vector<pair<int, double>> FileReader::ReadTopUsers(const string& input_file, int num_users) {
  int user;
  double weight;
  vector<pair<int, double>> pageusers;

  std::ifstream input_stream;
  input_stream.open(input_file, std::ios::in);

  for (int i = 0; i < num_users; i++) {
    input_stream >> user >> weight;

    pageusers.push_back(pair<int, double>(user, weight));
  }

  input_stream.close();

  return pageusers;
}

map<unsigned long, unsigned int> FileReader::ReadMatrixData(const string& input_file) {
  unsigned long index;
  unsigned int ixn_count;
  map<unsigned long, unsigned int> temp;

  std::ifstream input_stream;
  input_stream.open(input_file, std::ios::in);

  while (!input_stream.eof()) {
    input_stream >> index >> ixn_count;

    temp[index] = ixn_count;
  }

  input_stream.close();

  return temp;
}
