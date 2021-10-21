#include "../include/diagram.h"
//To view the comments they are avaliable at include/diagram.h

Diagram::Diagram(vector<pair<int, double>> nodes, map<unsigned long, unsigned int> adjmatrix, int max_children) {
    int max_c = max_children; // Max # of connections per user in mNodes
    lowest_weight = DBL_MAX;
    highest_weight = 0;
    map<int, nodeinfo> mHolder;

    //initialize map nodes, no connections yet
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++) {
        nodeinfo temp;
        temp.user = itr->first;
        temp.weight = itr->second;
        if (temp.weight < lowest_weight) {
            lowest_weight = temp.weight;
        }
        double posx = (rand() % 100) - 50;
        posx /= 100;
        double posy = (rand() % 100) - 50;
        posy /= 100;
        temp.position = pair<double, double>(posx, posy);
        temp.velocity = pair<double, double>(0, 0);


        mNodes[itr->first] = temp;
    }

    for (auto itr = mNodes.begin(); itr != mNodes.end(); itr++) {
        itr->second.weight = (itr->second.weight) / lowest_weight * 2.0;
        if (itr->second.weight > highest_weight) {
            highest_weight = itr->second.weight;
        }
    }

    mHolder = mNodes;

    for (auto itr = mHolder.begin(); itr != mHolder.end(); itr++) {
        int currid = itr->first;
        nodeinfo & currnode = mNodes[currid];
        int counter = 0;

        // Add nodes that may be in previous node connections to current node (if connection exists)
        for (auto itr2 = mNodes.begin(); itr2 != mNodes.end(); ++itr2) {
            for (auto itr3 = itr2->second.connections.begin(); itr3 != itr2->second.connections.end(); ++itr3) {
                if(((adjmatrix[currid * 500000 + *itr3] > 0) || (adjmatrix[(*itr3) * 500000 + currid] > 0))) {
                    nodeinfo temp;
                    temp.user = *itr3;
                    temp.weight = 1.0;
                    double posx = (rand() % 100) - 50;
                    posx /= 100;
                    double posy = (rand() % 100) - 50;
                    posy /= 100;
                    temp.position = pair<double, double>(posx, posy);
                    temp.velocity = pair<double, double>(0, 0);

                    mNodes[*itr3] = temp;

                    currnode.connections.push_back(*itr3);
                    ++counter;

                    if (counter >= max_c) {
                        break;
                    }
                }
            }
            if (counter >= max_c) {
                break;
            }
        }

        // If there is space for more connections, find more connections until full or none exist
        if (counter < max_c) {
            for (int i = 0; i < 500000; i++) {
                if(((adjmatrix[currid * 500000 + i] > 0) || (adjmatrix[i * 500000 + currid] > 0))) {
                    bool already = false;

                    for (auto itr2 = mNodes.begin(); itr2 != mNodes.end(); ++itr2) {
                        if (i == itr2->first) {
                            already = true;
                            break;
                        }
                    }

                    if (already) {
                        continue;
                    }
                    else {
                        nodeinfo temp;
                        temp.user = i;
                        temp.weight = 1.0;
                        double posx = (rand() % 100) - 50;
                        posx /= 100;
                        double posy = (rand() % 100) - 50;
                        posy /= 100;
                        temp.position = pair<double, double>(posx, posy);
                        temp.velocity = pair<double, double>(0, 0);

                        mNodes[i] = temp;

                        currnode.connections.push_back(i);
                        ++counter;
                        if (counter >= max_c) {
                            break;
                        }
                    }
                }
                if (counter >= max_c) {
                    break;
                }
            }
        }
    }
}

void Diagram::attractions(){
    for(auto itr = mNodes.begin(); itr != mNodes.end(); itr++){
        for(auto itr2 = itr->second.connections.begin(); itr2 != itr->second.connections.end(); itr2++){
            double dist = sqrt(((itr->second.position.first - mNodes[*itr2].position.first) * (itr->second.position.first - mNodes[*itr2].position.first)) + 
                                    ((itr->second.position.second - mNodes[*itr2].position.second) * (itr->second.position.second - mNodes[*itr2].position.second)));
            dist = dist < 1? 1 : dist;
            double springdist = fmax(dist - SPRING_LENGTH, 0);
            double force = ATTRACTION_CONSTANT *  springdist;
            double force_x = force * (mNodes[*itr2].position.first - itr->second.position.first) / dist;
            double force_y = force * (mNodes[*itr2].position.second - itr->second.position.second) / dist;
            itr->second.velocity = pair<double, double>(itr->second.velocity.first + force_x, itr->second.velocity.second + force_y);
        }
    }
}

void Diagram::repulsions(){
    for(auto itr = mNodes.begin(); itr != mNodes.end(); itr++){
        for(auto itr2 = mNodes.begin(); itr2 != mNodes.end(); itr2++){
            double distsquared = ((itr->second.position.first - itr2->second.position.first) * (itr->second.position.first - itr2->second.position.first)) + 
                                    ((itr->second.position.second - itr2->second.position.second) * (itr->second.position.second - itr2->second.position.second));
            distsquared = distsquared < 1? 1 : distsquared;
            double force = REPULSION_CONSTANT * (itr->second.weight * itr2->second.weight) / distsquared;
            double force_x = force * (itr->second.position.first - itr2->second.position.first) / sqrt(distsquared);
            double force_y = force * (itr->second.position.second - itr2->second.position.second) / sqrt(distsquared);
            itr->second.velocity = pair<double, double>(itr->second.velocity.first + force_x, itr->second.velocity.second + force_y);
        }
    }
}

double Diagram::iterate(){
    double totaldisp = 0;
    attractions();
    repulsions();
    for(auto itr = mNodes.begin(); itr != mNodes.end(); itr++){
        itr->second.velocity = pair<double, double>(itr->second.velocity.first * DAMPING, itr->second.velocity.second * DAMPING);
        totaldisp += sqrt((itr->second.velocity.first * itr->second.velocity.first) + (itr->second.velocity.second * itr->second.velocity.second));
        itr->second.position.first += itr->second.velocity.first;
        itr->second.position.second += itr->second.velocity.second;
    }
    return totaldisp;
}

void Diagram::updateDistances(double min_totaldisp){
    double totaldisp = DBL_MAX;
    int iterates = 0;
    while(totaldisp >= min_totaldisp && iterates < MAX_ITERATIONS){
        totaldisp = iterate();
        iterates++;
    }
}

void Diagram::drawNode(PNG *& img, double x, double y, double radsqr) {
    for (unsigned int h = 0; h < img->height(); h++) {
        for (unsigned int w = 0; w < img->width(); w++) {
            double height = h * 1.0;
            double width = w * 1.0;
            double xpos = x * 1.0;
            double ypos = y * 1.0;
            if ((xpos - width) * (xpos - width) + (ypos - height) * (ypos - height) <= radsqr) {
                HSLAPixel & temp = img->getPixel(w, h);
                if (radsqr > 1000.0) {
                    temp = HSLAPixel(360 - (radsqr * 360 / (highest_weight * 25000)), 1, 0.5);
                }
                else {
                    temp = HSLAPixel(180, 1, 0.5);
                }
            }
        }
    }
}

void Diagram::drawLines(PNG *& img, double x, double y, list<int> & others, double linerad) {
    double slope, intercept;

    for (auto itr = others.begin(); itr != others.end(); ++itr) {
        nodeinfo & temp = mNodes[*itr];
        if (((temp.position.first * 50 + 3000) - x) == 0) {
            continue;
        }
        slope = ((temp.position.second * 50 + 3000) - y) / ((temp.position.first * 50 + 3000) - x);
        intercept = y - (slope * x);

        for (unsigned int h = 0; h < img->height(); h++) {
            for (unsigned int w = 0; w < img->width(); w++) {
                double height = h * 1.0;
                double width = w * 1.0;
                double k = h - (slope * w) - intercept;

                if ((((k <= linerad) && (k >= 0 - linerad)) ) && (((w >= x) && (w <= temp.position.first * 50 + 3000)) || ((w <= x) && (w >= temp.position.first * 50 + 3000)))) {
                    HSLAPixel & temp = img->getPixel(w, h);
                    temp = HSLAPixel(0, 1, 0);
                }
            }
        }
    }
}

void Diagram::drawDiagram(string filepath) {
    PNG* img = new PNG(6000, 6000);
    double x, y;

    for (auto itr = mNodes.begin(); itr != mNodes.end(); itr++){
        x = (itr->second.position.first * 50) + 3000;
        y = (itr->second.position.second * 50) + 3000;

        drawLines(img, x, y, itr->second.connections, 5.0);
    }

    for (auto itr = mNodes.begin(); itr != mNodes.end(); itr++){
        x = (itr->second.position.first * 50) + 3000;
        y = (itr->second.position.second * 50) + 3000;

        double weight = itr->second.weight;
        double radsqr;

        if (weight > 1.0) {
            radsqr = weight * 25000;
        }
        else {
            radsqr = 1000.0;
        }
        drawNode(img, x, y, radsqr);
    }

    img->writeToFile(filepath);

    delete img;
}
