/**
 * Code based on Brad Smith's algorithm: https://www.brad-smith.info/blog/archives/129
 */

#pragma once

#include "nodeinfo.h"
#include "../cs225/PNG.h"

#include <map>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <cfloat>
#include <string>
#include <list>
using std::map;
using std::cout;
using std::endl;
using std::string;
using cs225::PNG;
using cs225::HSLAPixel;
using std::list;

class Diagram {

    public: 
		/**
		 * Constructs a Diagram object
		 * 
		 * @param nodes The vector that holds the top users sorted according to PageRank weight
		 * @param adjmatrix The adjacency matrix that contains interaction data
		 * @param max_children The max number of children for each "top user" to have in the visualization
		 */
		Diagram(vector<pair<int, double>> nodes, map<unsigned long, unsigned int> adjmatrix, int max_children);

		/**
		 * Calls attractions() and repulsions() MAX_ITERATIONS times.
		 * 
		 * @param min_totaldisp The minimum value for the total displacemnent to stop iterating
		 */
		void updateDistances(double min_totaldisp);

		/**
		 * Draws the diagram to a PNG file.
		 * 
		 * @param filepath The filepath to write the PNG file to
		 */
		void drawDiagram(string filepath);

	private: 
		/**
		 * Updates the velocity of the nodes on the diagram using Hooke's Law
		 */
		void attractions();

		/**
		 * Updates the velocity of the nodes on the diagram using Coulomb's Law
		 */
		void repulsions();

		/**
		 * Updates the position of the nodes on the diagram with the new velocity after attractions/repulsions
		 * 
		 * @return A value indicating the total displacement of the nodes after the position update.
		 */
		double iterate();

		/**
		 * Draws nodes (users) onto the diagram.
		 * 
		 * @param img A reference to a pointer of a PNG
		 * @param x The x-coord of the center of the circle
		 * @param y The y-coord of the center of the circle
		 * @param radsqr The radius squared value
		 */
		void drawNode(PNG *& img, double x, double y, double radsqr);

		/**
		 * Draws lines (interactions) onto the diagram. Starts from the current node and draws lines to each of its connections.
		 * 
		 * @param img A reference to a pointer to a PNG
		 * @param x The x-coord of the center of the current node
		 * @param y The y-coord of the center of the current node
		 * @param others The list of connections of the current node
		 * @param linerad The line "radius"
		 */
		void drawLines(PNG *& img, double x, double y, list<int> & others, double linerad);

		const double ATTRACTION_CONSTANT = 1;		// spring constant
		const double REPULSION_CONSTANT = 0.4;	// charge constant
		const double DAMPING = 0.5;
		const int SPRING_LENGTH = 100;
		const int MAX_ITERATIONS = 500;

		double lowest_weight, highest_weight;

		map<int, nodeinfo> mNodes;
};

#include "../src/diagram.cpp"