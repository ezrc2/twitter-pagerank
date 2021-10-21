#pragma once

#include <map>
#include <set>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using std::map;
using std::multimap;
using std::set;
using std::pair;
using std::string;
using std::vector;

/**
 *
 */
class FileReader {

	public:
		
		/**
		 * Generates the matrix using the index calculation and keeps track of the number of directed interactions
		 *
		 * @param input_file The input file path to read the interactions from
		 * @param output_file The output file path to write the matrix to
		 * @return Returns a map containing the matrix data, with matrix indices as keys and number of interations as values
		 */
		map<unsigned long, unsigned int> GetMatrixData(const string& input_file, const string& output_file);
		
		/**
		 * Generates the map that holds pairs of user IDS to perform PageRank on
		 *
		 * @param input_file The input file path to read the IDs from
		 * @param output_file The output file path to write the map to
		 * @return Returns a multimap containing pairs of user IDs to represent the existence of interactions
		 */
		multimap<int, int> GetPageRankData(const string& input_file, const string& output_file);

		/**
		 * Reads the top num_users users from the specified PageRank input file
		 *
		 * @param input_file The input file that contains the PageRank algorithm output data
		 * @param num_users The number of users to read
		 * @return Returns a vector containing the top users and their weights in descending order
		 */
		vector<pair<int, double>> ReadTopUsers(const string& input_file, int num_users);

		/**
		 * Reads and formats matrix data
		 *
		 * @param input_file The input file to read the matrix data in from
		 * @return Returns a map with the matrix data
		 */
		map<unsigned long, unsigned int> ReadMatrixData(const string& input_file);

};

#include "../src/file_reader.cpp"