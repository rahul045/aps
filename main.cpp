#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <utility>

#define CITIES 12

// Order of airports
std::map<int, std::pair<std::string, std::string>> airports = {
    {0,     std::make_pair("DEL", "Delhi")},
    {1,     std::make_pair("BOM", "Mumbai")},
    {2,     std::make_pair("BLR", "Bangalore")},
    {3,     std::make_pair("CCU", "Kolkata")},
    {4,     std::make_pair("GOI", "Goa")},
    {5,     std::make_pair("LKO", "Lucknow")},
    {6,     std::make_pair("HYD", "Hyderabad")},
    {7,     std::make_pair("MAA", "Chennai")},
    {8,     std::make_pair("AMD", "Ahemdabad")},
    {9,     std::make_pair("GAU", "Guwahati")},
    {10,    std::make_pair("SXR", "Srinagar")},
    {11,    std::make_pair("IDR", "Indore")},
};

// Distances between airports is in km
std::vector<std::vector<int>> distance = {
/*  DEL     BOM     BLR     CCU     GOI     LKO     HYD     MAA     AMD     GAU     SXR     IDR */
    {0,     1137,   1740,   1305,   1515,   419,    1255,   1757,   775,    1457,   643,    670},   // DEL
    {1137,  0,      842,    1652,   435,    1190,   617,    1029,   441,    2079,   1674,   507},   // BOM
    {1740,  842,    0,      1560,   464,    1578,   455,    284,    1220,   2075,   2358,   1100},  // BLR
    {1305,  1652,   1560,   0,      1709,   886,    1180,   1366,   1617,   496,    1831,   1286},  // CCU
    {1515,  435,    464,    1709,   0,      1466,   530,    713,    871,    2192,   2083,   846},   // GOI
    {419,   1190,   1578,   886,    1466,   0,      1075,   1529,   942,    1074,   995,    681},   // LKO
    {1255,  617,    455,    1180,   530,    1075,   0,      521,    876,    1677,   2780,   652},   // HYD
    {1757,  1029,   284,    1366,   713,    1529,   521,    0,      1371,   1885,   2394,   1172},  // MAA
    {775,   441,    1220,   1617,   871,    942,    876,    1371,   0,      1961,   1395,   334},   // AMD
    {1457,  2079,   2075,   496,    2192,   1074,   1677,   1885,   1961,   0,      1846,   2114},  // GAU
    {643,   1674,   2358,   1831,   2083,   995,    2780,   2394,   1395,   1846,   0,      1261},  // SXR
    {670,   507,    1100,   1286,   846,    681,    652,    1172,   334,    2114,   1261,   0}      // IDR
};

void getPath(int current, std::vector<int> &parents, std::vector<std::pair<std::string, std::string>> &path) {
    if (current == -1)
        return;
    getPath(parents[current], parents, path);
    path.push_back(airports[current]);
}

// Finding the shortest path between 2 airports using the
// Dijkstra's algorithm
void shortestPath(int source, int destination) {
    std::vector<int> parents(CITIES);
    std::vector<int> shortest(CITIES);
    std::vector<bool> included(CITIES);

    for (int i = 0; i < CITIES; i++) {
        shortest[i] = INT_MAX;
        included[i] = false;
    }
    parents[source] = -1;
    shortest[source] = 0;

    for (int i = 1; i < CITIES; i++) {
        int nearestAirport = -1;
        int shortestDistance = INT_MAX;
        for (int j = 0; j < CITIES; j++) {
            if (included[j] == false && shortest[j] < shortestDistance) {
                nearestAirport = j;
                shortestDistance = shortest[j];
            }
        }

        included[nearestAirport] = true;
        for (int j = 0; j < CITIES; j++) {
            int edgeDistance = distance[nearestAirport][j];
            if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < shortest[j])) {
                parents[j] = nearestAirport;
                shortest[j] = shortestDistance + edgeDistance;
            }
        }
    }

    std::vector<std::pair<std::string, std::string>> path;
    getPath(destination, parents, path);
    for (int i = 0; i < path.size(); i++) {
        std::cout << path[i].second;
        if (i != path.size() - 1)
            std::cout << " -> ";
    }
    std::cout << std::endl;
    std::cout << "Direct Distance: " << distance[source][destination] << " kms" << std::endl;
    std::cout << "Shortest Distance: " << shortest[destination] << " kms" << std::endl;
}

int main() {
    shortestPath(2, 10);
    return 0;
}
