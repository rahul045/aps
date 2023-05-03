#include <iostream>
#include <climits>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <utility>

#define CITIES 12
// using namespace std;

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

// Prices are in rupees
std::vector<std::vector<int>> price = {
/*  DEL     BOM     BLR     CCU     GOI     LKO     HYD     MAA     AMD     GAU     SXR     IDR */
    {0,     5297,   5176,   5880,   4788,   3407,   4788,   5283,   2625,   6109,   8709,   4016},  // DEL
    {5288,  0,      3346,   3220,   2795,   8485,   3225,   3220,   2606,   8474,   15731,  9614},  // BOM
    {5386,  2919,   0,      8809,   3612,   8641,   4037,   5963,   5339,   5867,   24360,  9974},  // BLR
    {6451,  7291,   9002,   0,      11527,  9534,   10341,  9444,   9721,   12555,  25451,  9480},  // CCU
    {5101,  3237,   2922,   11269,  0,      8476,   6371,   8478,   7684,   8089,   23782,  9216},  // GOI
    {2712,  7143,   7295,   8277,   7993,   0,      9342,   7242,   9574,   9164,   21917,  6093},  // LKO
    {6406,  3933,   4285,   10602,  9162,   9818,   0,      6946,   6363,   9402,   25589,  11819}, // HYD
    {5276,  3451,   6936,   9535,   8611,   7841,   6784,   0,      5613,   11610,  24293,  9908},  // MAA
    {4279,  2837,   5103,   7887,   7502,   5355,   5706,   5559,   0,      9991,   22780,  8394},  // AMD
    {6459,  8059,   6389,   12514,  10819,  9274,   9674,   11114,  11104,  0,      24079,  9754},  // GAU
    {9727,  16182,  20730,  21589,  20043,  18071,  21074,  20730,  22963,  19928,  0,      19094}, // SXR
    {4561,  9648,   9790,   9113,   9139,   6677,   10730,  9422,   12079,  9608,   23062,  0}      // IDR
};

std::vector<std::vector<int>> flights = {
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // DEL
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // BOM
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // BLR
    {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1}, // CCU
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1}, // GOI
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}, // LKO
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, // HYD
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}, // MAA
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1}, // AMD
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1}, // GAU
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1}, // SXR
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}  // IDR
};

void getPath(int current, std::vector<int> &parents, std::vector<std::pair<std::string, std::string>> &path)
{
    if (current == -1)
        return;
    getPath(parents[current], parents, path);
    path.push_back(airports[current]);
}

// Finding the shortest path between 2 airports using the
// Dijkstra's algorithm
void shortestPath(int source, int destination)
{
    std::vector<int> parents(CITIES);
    std::vector<int> shortest(CITIES);
    std::vector<bool> included(CITIES);

    for (int i = 0; i < CITIES; i++)
    {
        shortest[i] = INT_MAX;
        included[i] = false;
    }
    parents[source] = -1;
    shortest[source] = 0;

    for (int i = 1; i < CITIES; i++)
    {
        int nearestAirport = -1;
        int shortestDistance = INT_MAX;
        for (int j = 0; j < CITIES; j++)
        {
            if (included[j] == false && shortest[j] < shortestDistance)
            {
                nearestAirport = j;
                shortestDistance = shortest[j];
            }
        }

        included[nearestAirport] = true;
        for (int j = 0; j < CITIES; j++)
        {
            int edgeDistance = distance[nearestAirport][j];
            if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < shortest[j]))
            {
                parents[j] = nearestAirport;
                shortest[j] = shortestDistance + edgeDistance;
            }
        }
    }

    std::vector<std::pair<std::string, std::string>> path;
    getPath(destination, parents, path);
    for (int i = 0; i < path.size(); i++)
    {
        std::cout << path[i].second;
        if (i != path.size() - 1)
            std::cout << " -> ";
    }
    std::cout << std::endl;
    std::cout << "Direct Distance: " << distance[source][destination] << " kms" << std::endl;
    std::cout << "Shortest Distance: " << shortest[destination] << " kms" << std::endl;
}

bool isPath(int s, int d, std::vector<int> &p, int *mn)
{
    std::queue<int> q;
    bool flag = false;
    q.push(s);

    while (q.empty() == false)
    {
        int temp = q.front();
        q.pop();

        for (int i = 0; i < CITIES; i++)
        {
            if (flights[temp][i] > 0 && p[i] == -1)
            {
                p[i] = temp;
                q.push(i);
                *mn = std::min(*mn, flights[temp][i]);
                if (i == d)
                {
                    flag = true;
                    break;
                }
            }
        }
    }
    return flag;
}

void numberOfFlights(int source, int destination)
{
    std::vector<int> p(CITIES, -1);
    int mn = INT_MAX;
    int ans = 0;

    while (isPath(source, destination, p, &mn))
    {
        ans += mn;
        int temp = p[destination];
        flights[temp][destination] -= mn;
        flights[destination][temp] += mn;

        while (temp != source)
        {
            int c = temp;
            temp = p[temp];
            flights[temp][c] -= mn;
            flights[c][temp] += mn;
        }

        for (int i = 0; i < CITIES; i++)
            p[i] = -1;
        mn = INT_MAX;
    }
    std::cout << "Numbers of flights: " << ans << std::endl;
}

int main()
{
    shortestPath(2, 10);
    return 0;
}
