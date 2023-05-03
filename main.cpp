#include <iostream>
#include <climits>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <utility>

#define CITIES 12
#define INF INT_MAX
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
        shortest[i] = INF;
        included[i] = false;
    }

    parents[source] = -1;
    shortest[source] = 0;

    for (int i = 1; i < CITIES; i++)
    {
        int nearestAirport = -1;
        int shortestDistance = INF;
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

    std::cout << std::endl << "----------------" << std::endl;
    std::cout << " Preferred path " << std::endl;
    std::cout << "----------------" << std::endl;
    for (int i = 0; i < path.size(); i++)
    {
        std::cout << path[i].second;
        if (i != path.size() - 1)
            std::cout << " -> ";
    }

    int result = shortest[destination];
    int difference = distance[source][destination] - result;

    std::cout << std::endl;
    std::cout << std:: endl << "Direct distance from source to destination: " << distance[source][destination] << " kms" << std::endl;
    std::cout << "Shortest distance using given path: " << result << " kms" << std::endl;
    std::cout << "Distance saved: " << difference << " kms" << std::endl;
}

void minimumCost(int source, int destination) {
    std::vector<int> parents(CITIES);
    std::vector<int> shortest(CITIES);
    std::vector<bool> included(CITIES);

    for (int i = 0; i < CITIES; i++)
    {
        shortest[i] = INF;
        included[i] = false;
    }

    parents[source] = -1;
    shortest[source] = 0;

    for (int i = 1; i < CITIES; i++)
    {
        int nearestAirport = -1;
        int shortestDistance = INF;
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
            int edgeDistance = price[nearestAirport][j];
            if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < shortest[j]))
            {
                parents[j] = nearestAirport;
                shortest[j] = shortestDistance + edgeDistance;
            }
        }
    }

    std::vector<std::pair<std::string, std::string>> path;
    getPath(destination, parents, path);

    std::cout << std::endl << "----------------" << std::endl;
    std::cout << " Preferred path " << std::endl;
    std::cout << "----------------" << std::endl;
    for (int i = 0; i < path.size(); i++)
    {
        std::cout << path[i].second;
        if (i != path.size() - 1)
            std::cout << " -> ";
    }

    int result = shortest[destination];
    int difference = price[source][destination] - result;

    std::cout << std::endl;
    std::cout << std:: endl << "Direct flight cost from source to destination: Rs " << price[source][destination] << std::endl;
    std::cout << "Minimum flight cost using given path: Rs " << result << std::endl;
    std::cout << "Amount saved: Rs " << difference << std::endl;
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

// Edmond Karp (Network Flow)
void numberOfFlights(int source, int destination)
{
    std::vector<int> p(CITIES, -1);

    int mn = INF;
    int ans = 0;

    while (isPath(source, destination, p, &mn))
    {
        int temp = p[destination];

        ans += mn;
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

        mn = INF;
    }

    std::cout << "Numbers of flights available from source to destination are: " << ans << std::endl;
}

// Floyd Warshall And DFS
void computeLPSArray(std::string &pat, int M, std::vector<int> &lps);

// Prints occurrences of txt[] in pat[]
bool KMPSearch(std::string &pat, std::string &txt)
{
    int M = pat.length();
    int N = txt.length();

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    std::vector<int> lps(M);

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while ((N - i) >= (M - j))
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            return 1;
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return 0;
}

// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(std::string &pat, int M, std::vector<int> &lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0;
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {

            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

std::string str = "";
std::vector<std::vector<int>> min_price;

void dfs(int src, int money, std::vector<int> &vis, std::vector<int> &p)
{
    std::map<std::string, int> m;
    bool flag = 0;
    for (int j = 0; j < CITIES; j++)
    {
        if (vis[j] == -1 && flights[src][j] == 1 && money >= min_price[src][j])
        {
            p.push_back(j);
            money -= min_price[src][j];
            vis[j] = 1;
            flag = 1;
            dfs(j, money, vis, p);
            vis[j] = -1;
            money += min_price[src][j];
            p.pop_back();
            flag = 0;
        }
    }
    if (money == 0 || flag == 0)
    {
        if (p.size() != 1)
        {
            std::string pat = "";
            if (str == "")
            {
                for (int i = 0; i < p.size(); i++)
                {

                    str += p[i];
                }
            }
            else
            {
                for (int i = 0; i < p.size(); i++)
                {

                    pat += p[i];
                }
                bool r = KMPSearch(pat, str);
                if (r == 0)
                {
                    str += pat;
                    for (int i = 0; i < p.size(); i++)
                    {
                        std::string s = airports[p[i]].second;
                        std::cout << s;
                        if (i != p.size() - 1)
                        {
                            std::cout << " -> ";
                        }
                    }
                    std::cout << std::endl;
                    std::cout << "Money Left: Rs " << money << std::endl;
                }
            }
        }
        return;
    }
}

void max_dist(int source, int money)
{
    // std::vector<std::vector<int>> min_price;
    for (int k = 0; k < CITIES; k++)
    {
        for (int i = 0; i < CITIES; i++)
        {
            std::vector<int> v;
            for (int j = 0; j < CITIES; j++)
            {
                int temp = price[i][k] + price[k][j];
                if (temp < price[i][j])
                {
                    v.push_back(temp);
                }
                else
                {
                    v.push_back(price[i][j]);
                }
            }
            min_price.push_back(v);
        }
    }

    std::vector<int> p, vis(CITIES, -1);
    int i = source;
    int temp;
    int j;
    p.push_back(i);
    vis[i] = 1;
    dfs(source, money, vis, p);
}

std::string art = R"(  ______ _ _       _     _     __  __                                                   _   )" "\n"
R"( |  ____| (_)     | |   | |   |  \/  |                                                 | |  )" "\n"
R"( | |__  | |_  __ _| |__ | |_  | \  / | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_ )" "\n"
R"( |  __| | | |/ _` | '_ \| __| | |\/| |/ _` | '_ \ / _` |/ _` |/ _ \ '_ ` _ \ / _ \ '_ \| __|)" "\n"
R"( | |    | | | (_| | | | | |_  | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_ )" "\n"
R"( |_|    |_|_|\__, |_| |_|\__| |_|  |_|\__,_|_| |_|\__,_|\__, |\___|_| |_| |_|\___|_| |_|\__|)" "\n"
R"(              __/ |                                      __/ |                              )" "\n"
R"(             |___/                                      |___/                               )" "\n";

std::string menu = R"(======)" "\n"
R"( MENU )" "\n"
R"(======)" "\n\n"
R"(1. Show available airports)" "\n"
R"(2. Shortest path between source and destination)" "\n"
R"(3. Minimum cost flight between source and destination)" "\n"
R"(4. Number of flights available between source and destination)" "\n"
R"(5. Destinations available from one source according to a budget)" "\n"
R"(6. Exit)" "\n";

int main()
{
    std::cout << art << std::endl;
    std::cout << menu;

    while (true) {
        int option;
        std::cout << std::endl << "fms> Enter option: ";
        std::cin >> option;

        switch (option) {
            case 1: {
                std::cout << "===\t====\t=======" << std::endl;
                std::cout << "NUM\tCODE\tAIRPORT" << std::endl;
                std::cout << "===\t====\t=======" << std::endl;

                int n = airports.size();
                for (int i = 0; i < n; i++) {
                    std::cout << i << "\t" << airports[i].first << "\t" << airports[i].second << std::endl;
                }
                break;
            }

            case 2: {
                int source, destination;

                std::cout << "fms> Enter source airport number: ";
                std::cin >> source;
                if (airports.find(source) == airports.end()) {
                    std::cout << "[-] Invalid airport number, use option 1 to check valid numbers.";
                }

                std::cout << "fms> Enter destination airport number: ";
                std::cin >> destination;
                if (airports.find(destination) == airports.end()) {
                    std::cout << "[-] Invalid airport number, use option 1 to check valid numbers.";
                }

                std::cout << std::endl << "Source: " << airports[source].second << " ( " << airports[source].first << " )" << std::endl;
                std::cout << "Destination: " << airports[destination].second << " ( " << airports[destination].first << " )" << std::endl;
                shortestPath(source, destination);
                break;
            }

            case 3: {
                int source, destination;

                std::cout << "fms> Enter source airport number: ";
                std::cin >> source;
                if (airports.find(source) == airports.end()) {
                    std::cout << "[-] Invalid airport number, use option 1 to check valid numbers.";
                }

                std::cout << "fms> Enter destination airport number: ";
                std::cin >> destination;
                if (airports.find(destination) == airports.end()) {
                    std::cout << "[-] Invalid airport number, use option 1 to check valid numbers.";
                }

                std::cout << std::endl << "Source: " << airports[source].second << " ( " << airports[source].first << " )" << std::endl;
                std::cout << "Destination: " << airports[destination].second << " ( " << airports[destination].first << " )" << std::endl;
                minimumCost(source, destination);
                break;
            }

            case 4: {
                int source, destination;

                std::cout << "fms> Enter source airport number: ";
                std::cin >> source;
                if (airports.find(source) == airports.end()) {
                    std::cout << "[-] Invalid airport number, use option 1 to check valid numbers.";
                }

                std::cout << "fms> Enter destination airport number: ";
                std::cin >> destination;
                if (airports.find(destination) == airports.end()) {
                    std::cout << "[-] Invalid airport number, use option 1 to check valid numbers.";
                }

                std::cout << std::endl << "Source: " << airports[source].second << " ( " << airports[source].first << " )" << std::endl;
                std::cout << "Destination: " << airports[destination].second << " ( " << airports[destination].first << " )" << std::endl;
                numberOfFlights(source, destination);
                break;
            }

            case 5: {
                int source, budget;

                std::cout << "fms> Enter source airport number: ";
                std::cin >> source;
                if (airports.find(source) == airports.end()) {
                    std::cout << "[-] Invalid airport number, use option 1 to check valid numbers.";
                }

                std::cout << "fms> Enter budget amount: ";
                std::cin >> budget;
                max_dist(source, budget);
                break;
            }

            case 6: {
                std::cout << "[-] Terminating program." << std::endl;
                exit(0);
            }

            default: {
                std::cout << "[-] Choose a correct option from the menu." << std::endl;
                break;
            }
        }
    }
    return 0;
}
