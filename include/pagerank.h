#pragma once

#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

using std::multimap;
using std::map;
using std::set;
using std::pair;
using std::vector;

class PageRank {

	public:

		/**
		 * Constructs a PageRank object
		 *
		 * @param adjacency_matrix The adjacency matrix represented as a multimap
		 * @param output_file File path for PageRank output
		 */
		PageRank(const multimap<int, int>& adjacency_matrix, const string& output_file);

		/**
		 * Applies PageRank on the users and also outputs the Users and PageRanks to a file
		 *
		 * @return The IDs and Pagerank value of the users ranked by importance in decreasing order
		 */
		vector<pair<int, double>> GetRankedUsers();

	private:

		/**
		 * Calculates the PageRank value of a user
		 * 
		 * @param user The User ID
		 * @return The PageRank value
		 */
		double CalculatePageRank(int user);

		/**
		 * Sorts the map based on value
		 *
		 * @return a vector of User ID and PageRank value pairs
		 */
		vector<pair<int, double>> SortPageRanks();
		
		/**
		 * Comparator to sort by value
		 * @param a The first pair of values
		 * @param b The second pair of values
		 */
		static bool Compare(const pair<int, double>& a, const pair<int, double>& b);

		multimap<int, int> adjacency_matrix_;
		multimap<int, int> flipped_matrix_; // flipped adjacency matrix
		map<int, double> pageranks_;

		double N; // total number of users

		const double kDampingFactor = 0.85;
		const int kRepetitions = 100;

		string output_file_;
};

#include "../src/pagerank.cpp"