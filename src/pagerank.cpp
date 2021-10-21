#include "../include/pagerank.h"
//To view the comments they are avaliable at include/pagerank.h

PageRank::PageRank(const multimap<int, int>& adjacency_matrix, const string& output_file) {
    adjacency_matrix_ = adjacency_matrix;
    output_file_ = output_file;

    set<int> users;
    for (const auto& edge : adjacency_matrix) {
        flipped_matrix_.insert(pair<int, int>(edge.second, edge.first));
        users.insert(edge.first);
        users.insert(edge.second);
    }
    N = static_cast<double>(users.size());

    for (const auto& id : users) {
        pageranks_[id] = 1 / N; // initial values
    }
}

vector<pair<int, double>> PageRank::GetRankedUsers() {
    for (int i = 0; i < kRepetitions; i++) { // need values to converge
        for (const auto& it : pageranks_) {
            pageranks_[it.first] = CalculatePageRank(it.first);
        }
    }

    vector<pair<int, double>> sorted_pairs = SortPageRanks();

    std::ofstream output_stream(output_file_);

    for (const pair<int, double>& it : sorted_pairs) {
        output_stream << it.first << " " << it.second << std::endl;
    }

    return sorted_pairs;
}

double PageRank::CalculatePageRank(int user) {
    double sum = 0;

    // get all users that point to this user
    auto incoming = flipped_matrix_.equal_range(user); 

    for (auto it = incoming.first; it != incoming.second; ++it) {
        sum += pageranks_[it->second] / adjacency_matrix_.count(it->second);
    }

    return (1 - kDampingFactor) / N + kDampingFactor * sum;
}

vector<pair<int, double>> PageRank::SortPageRanks() {
    vector<pair<int, double>> temp;

    for (const auto& it : pageranks_) {
        temp.push_back(pair<int, double>(it.first, it.second));
    }
    std::sort(temp.begin(), temp.end(), Compare);

    return temp;
}

bool PageRank::Compare(const pair<int, double>& a, const pair<int, double>& b) {
    return a.second > b.second;
}
