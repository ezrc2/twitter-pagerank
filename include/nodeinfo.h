/**Node class changed to nodeinfo.h
Contains user id number, weight, list of connections, position, and velocity
**/
#pragma once

#include <utility>
#include <list>
using std::pair;
using std::list;

class nodeinfo {
    public: 
        int user;
        double weight;
        list<int> connections;

        pair<double, double> position;
        pair<double, double> velocity;
};
