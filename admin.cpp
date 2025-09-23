//
// Created by Hana on 9/2/2025.
//
#include "admin.h"

#include <fstream>
#include <sstream>

#include "driver.h"
#include "user.h"
using namespace std;


// I need to increment the numLocation in the location's contructor 
int admin::numLocations = 0;
int admin :: numdrivers =0 ;
int admin :: numusers = 0;

// increment it then add it to the unordered map

admin::admin()
{
    numLocations = 0;
}

// helper Functions
bool admin ::location_is_found(int loctID)
{
    return (loctID != -1);
}
bool admin ::road_is_found(int outerIndex, int innerIndex)
{


    auto &neighbors = adj[outerIndex]; 

    auto it = std::find_if(neighbors.begin(), neighbors.end(),
                           [innerIndex](const std::pair<int,float> &p) {
                               return p.first == innerIndex; // match by node ID
                           });

    if (it != neighbors.end())
    {
        neighbors.erase(it);
        return true;
    }

    return false;                       




//    auto it = find(adj[outerIndex].begin(), adj[outerIndex].end(), innerIndex);
//     if (it != adj[outerIndex].end())
//     {
//         adj[outerIndex].erase(it);
//         return true;
//     }

//     return false;

}


int admin::findLocationByName(const string &locationName)
{
    // loop on unordered map(locationByid)
    for (const auto & pair : locationById)
    {
        if (pair.second.name == locationName)
        {
            return pair.first;
        }
    }
    return -1; // Not found
}


bool admin::edge_exists(int u, int v) {
    auto &neighbors = adj[u];
    return std::any_of(neighbors.begin(), neighbors.end(),
                       [v](const std::pair<int,float>& p) {
                           return p.first == v;
                       });
}

// update Functions(add , delete)

// add location , road
void admin :: addGraph(){
    // to be implemented 
    // inserting multiple roads and locations 
    // updating the adj list and I need their id's 
    // updating the locationbyId => id , location with the new locations  
}
void admin::add_location() {
    pair<float, float> coordinates;
    string name;

    cout << "Enter location name: ";
    cin >> name;
    cout << "Enter location coordinates: ";
    cin >> coordinates.first >> coordinates.second;

    int id = numLocations++; // use current numLocations as ID, then increment

    location locat(coordinates, name);
    locationById[id] = locat;

    // Initialize adjacency list for this location
    adj[id] = {};

    cout << "Location added successfully with ID = " << id << "\n";
}

void admin::add_road(){

    string name1, name2;
    cout << "Enter first location name: ";
    cin >> name1;
    cout << "Enter second location name: ";
    cin >> name2;
    int firstId = findLocationByName(name1);
    int secondId = findLocationByName(name2);
    // used the bool function change it  if you don't like it
    if (!(location_is_found(firstId) && location_is_found(secondId)))
    {
        cout << "One or both locations not found!" << endl;
        return;
    }



    // check for existing edge => implement edge_exist 
if (edge_exists(firstId, secondId)) {
    cout << "Road already exists!" << endl;
    return;
}




    // Add bidirectional road
    float weight = lengthBetNodes(firstId , secondId);
    adj[firstId].push_back({secondId , weight});
    adj[secondId].push_back({firstId , weight});

    cout << "Road added successfully!" << endl;
}

// delete location , road
void admin ::delete_location()
{

    string loctName;
    cout << "Enter the location name you want to delete : " << l;
    cin >> loctName;

    int loctID = findLocationByName(loctName);

    if (!location_is_found(loctID))
    {
        cout << "The location is not found" << l;
        return;
    }
    string confirmation;
    cout << "Are you sure you want to delete  Y/N" << loctName << l;
    cin >> confirmation;

    if (confirmation == "N")
    {
        cout << "deleting location  process is canceled" << l;
        return;
    }

auto it = adj.find(loctID);
if (it != adj.end()) {
    // for each neighbor of loctID, remove the reverse edge
    for (const auto &p : it->second) {
        int child = p.first;

        // remove (child -> loctID) directly here
        auto &neighbors = adj[child];
        neighbors.erase(
            std::remove_if(neighbors.begin(), neighbors.end(),
                           [loctID](const std::pair<int,float> &pr) {
                               return pr.first == loctID;
                           }),
            neighbors.end()
        );
    }
    // finally remove adjacency list for loctID
    adj.erase(it);
}

    // for (const auto [child , wieight ]: adj[loctID])
    // {

    //     adj[child].erase(
    //         remove(adj[child].begin(), adj[child].end(), loctID),
    //         adj[child].end());

    //     // vec[outerIndex].erase(vec[outerIndex].begin() + innerIndex);
    // }

    // adj.erase(loctID);
    locationById.erase(loctID);

    cout << "location is deleted successfully";
}
void admin ::delete_road()
{

    string city1, city2;
    cout << "Enter the the two locations names the road exist between" << l;
    cin >> city1 >> city2;
    int first_id = findLocationByName(city1);
    int second_id = findLocationByName(city2);

    string confirmation;
    cout << "Are you sure you want to delete road between  " << city1 << ' ' << city2 << "Y/N" << l;
    cin >> confirmation;

    if (confirmation == "N")
    {
        cout << "deleting road process is canceled" << l;
        return;
    }

    if (!(location_is_found(first_id) && location_is_found(second_id)))
    {
        cout << "One or both locations not found!" << endl;
        return;
    }



 // undirected graph → must delete both sides
    bool removedA = road_is_found(first_id, second_id);
    bool removedB = road_is_found(second_id, first_id);

    if (removedA && removedB)
    {
        cout << "Road is deleted successfully" << l;
    }
    else
    {
        cout << "Road is not found between the two locations " << l;
    }
}

// Traversal functions
void admin ::dfs_caller(vector<bool> &visited)
{

    for (const auto [id, loc] : locationById)
    {
        if (!visited[id])
        {
            dfs(id, visited);
        }
    }
}
void admin ::dfs(int node, vector<bool> &visited){
    visited[node] = true;
    cout << locationById[node].name << ' ';

    auto it = adj.find(node);
    if (it == adj.end()) return;

    for (const auto &p : it->second) { // p.first = neighbor, p.second = weight
        int neighbor = p.first;
        if (!visited[neighbor])
            dfs(neighbor, visited);
    }

    // for (auto [neighbor , weight]: adj[node])
    // {
    //     if (!visited[neighbor])
    //         dfs(neighbor, visited);
    // }
}
void admin::bfs(queue<int> &Qlocat, vector<bool> &visited, int start){
    visited[start] = true;
    Qlocat.push(start); // Add starting node to queue

    while (!Qlocat.empty())
    {
        int curr = Qlocat.front();
        Qlocat.pop();
        cout << locationById.at(curr).name << endl;



        auto it = adj.find(curr);
        if (it == adj.end()) continue;

        for (const auto &p : it->second) {
            int neighbor = p.first;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                Qlocat.push(neighbor);
            }
        }

        // for (auto [neighbor , weight ] : adj[curr])
        // { // Use curr, not start
        //     if (visited[neighbor] == false)
        //     {
        //         visited[neighbor] = true;
        //         Qlocat.push(neighbor);
        //     }
        // }
    }
}
void admin :: displayData () {
    // to be implemented 
}


// id node 1 , id node 2 
float admin :: lengthBetNodes (int a , int b){



double xA , yA , xB , yB ;

xA =  locationById[a].coordinates.first ;
yA =  locationById[a].coordinates.second ;
xB=   locationById[b].coordinates.first ;
yB=   locationById[b].coordinates.second ;


double diffX = xA - xB  , diffY = yA - yB ;

double  dist = sqrt (diffX * diffX + diffY * diffY  );

return static_cast<float>(dist); // convert at the end



}


int admin::driverdijkstra(int userNode,vector<int>&driverNodes) {  //will return driver node id
    const int INF =10000000;
    vector<float> dist(numLocations, INF);
    priority_queue<pair<float,int>, vector<pair<int,int>>, greater<>> pq;
    unordered_map<int, int> parentDriver; // track which driver reached this node

    for (int i=0; i<driverNodes.size(); i++) {
        dist[driverNodes[i]]=0;
        pq.push({0, driverNodes[i]}); //push all drivers in the pq
        parentDriver[driverNodes[i]] = driverNodes[i]; // each driver is their own parent
    }
    while (pq.empty()==false) {
        pair curr = pq.top();
        pq.pop();
        if (curr.second == userNode) {
            cout << "Nearest driver is at node " << parentDriver[curr.second]
                 << " with distance " << curr.first << "\n";
            return parentDriver[curr.second];
        }
        // skip if this is an outdated distance
        if (curr.first > dist[curr.second]) continue;
        for (auto p : adj[curr.second]) { // p.first neighbor id p.second weight
            dist[p.first]=min(dist[p.first],curr.first+p.second);//update neighbors dist
            parentDriver[p.first] = parentDriver[curr.second]; //parent of the neighbor is the parent of the parent lol
            pq.push({dist[p.first] ,p.first});//push neighbor in the pq
        }
    }
    cout << "All drivers are busy!\n";
    return -1;
}


vector<int> admin::pathdijkstra(int start,int end,driver& driver) {  //return path
    const int INF =10000000;
    vector<float> dist(numLocations, INF);
    priority_queue<pair<float,int>, vector<pair<int,int>>, greater<>> pq;
    unordered_map<int, int> parent;//save parents nodes
    vector<int>q;
    dist[start]=0;
    pq.push({0, start});

    while (pq.empty()==false) {
        pair curr=pq.top();
        pq.pop();
        if (curr.second == end) {
            cout << "You have reached your destination! " <<endl;
            driver.available=true;
            driver.nodeId=end;
            //we should know the current location cooordinates !!!!!!!!!!!!!!!!!!!!!!!!
            //update user location or delete the user or whatever
           break;
        }

        if (curr.first > dist[curr.second]) {continue;}//if its outdated distance
        for (auto p : adj[curr.second]) { // p.first neighbor id p.second weight
            dist[p.first]=min(dist[p.first],curr.first+p.second);//update neighbors dist
            parent[p.first] = parent[curr.second]; //parent of the neighbor is the parent of the parent lol
            pq.push({dist[p.first] ,p.first});//push neighbor in the pq
        }
    }
    int node=end;
    while (node != -1) {
        q.push_back(node);
        node = parent[node];
    }
return q;
}
//yarab teshtaghal mn awel mara










///////////////////////////////////file logic///////////////////////////////////////////////////////////////////
void admin::saveData() {
    ofstream file("C:\\Users\\nonam\\CLionProjects\\Wasalni\\data.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open data.csv for writing!\n";
        return;
    }

    // Save counters at the top
    file << "COUNTERS," << numLocations << "," << numusers << "," << numdrivers << "\n";

    // Write locations
    file << "LOCATIONS\n";
    for (auto &[id, loc] : locationById) {
        file << id << "," << loc.name << ","
             << loc.coordinates.first << ","
             << loc.coordinates.second << "\n";
    }

    // Write adjacency list
    file << "ADJACENCY\n";
    for (auto &[node, neighbors] : adj) {
        for (auto &[nbr, weight] : neighbors) {
            file << node << "," << nbr << "," << weight << "\n";
        }
    }

    // Write users
    file << "USERS\n";
    for (auto &[id, u] : users) {
        file << id << "," << u.name << "," << u.email
             << "," << u.telephone << "," << u.password << "\n";
    }

    // Write drivers
    file << "DRIVERS\n";
    for (auto &[id, d] : drivers) {
        file << id << "," << d.name << "," << d.email
             << "," << d.telephone << "," << d.password << "\n";
    }

    file.close();
    cout << "Saved " << locationById.size() << " locations, "
         << adj.size() << " adjacency entries, "
         << users.size() << " users, and "
         << drivers.size() << " drivers to data.csv\n";
}

// Load users and drivers from CSV file
void admin::loadData() {
    ifstream file("C:\\Users\\nonam\\CLionProjects\\Wasalni\\data.csv");
    if (!file.is_open()) {
        cerr << "No existing data.csv found. Starting fresh.\n";
        return;
    }

    string line;
    enum Section { NONE, LOCATIONS, ADJ, USERS, DRIVERS };
    Section currentSection = NONE;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line == "LOCATIONS") { currentSection = LOCATIONS; continue; }
        if (line == "ADJACENCY") { currentSection = ADJ; continue; }
        if (line == "USERS") { currentSection = USERS; continue; }
        if (line == "DRIVERS") { currentSection = DRIVERS; continue; }

        stringstream ss(line);
        string part;
        vector<string> tokens;
        while (getline(ss, part, ',')) tokens.push_back(part);

        try {
            if (line.find("COUNTERS") == 0) {
                stringstream ss(line);
                string temp;
                getline(ss, temp, ','); // skip "COUNTERS"
                ss >> numLocations; ss.ignore(1, ',');
                ss >> numusers; ss.ignore(1, ',');
                ss >> numdrivers;
            }
           else if (currentSection == LOCATIONS && tokens.size() == 4) {
                int id = stoi(tokens[0]);
                string name = tokens[1];
                float x = stof(tokens[2]);
                float y = stof(tokens[3]);
                locationById[id] = location({x, y}, name);
            }
            else if (currentSection == ADJ && tokens.size() == 3) {
                int node = stoi(tokens[0]);
                int nbr = stoi(tokens[1]);
                float weight = stof(tokens[2]);
                adj[node].push_back({nbr, weight});
            }
            else if (currentSection == USERS && tokens.size() == 5) {
                int id = stoi(tokens[0]);
                users[id] = user(tokens[1], tokens[2], tokens[3], tokens[4]);
            }
            else if (currentSection == DRIVERS && tokens.size() == 5) {
                int id = stoi(tokens[0]);
                drivers[id] = driver(tokens[1], tokens[2], tokens[3], tokens[4]);
            }
        } catch (const std::invalid_argument &) {
            cerr << "Skipping invalid line: " << line << "\n";
        }
    }

    file.close();

    cout << "Loaded " << locationById.size() << " locations, "
         << adj.size() << " adjacency entries, "
         << users.size() << " users, and "
         << drivers.size() << " drivers from data.csv\n";
}
