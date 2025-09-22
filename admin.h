//
// Created by Hana on 9/2/2025.
//
#include <string>
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
# include <cmath>


#define l endl;

using namespace std;
#ifndef ADMIN_H
#define ADMIN_H


class driver;
class user; 

struct location
{
  // should we add weight attribute ??
  pair<float, float> coordinates;
  string name;


      // default constructor
    location() : coordinates({0.0, 0.0}) , name("") {}

  // constructor
  location(pair<float, float> coordinates, string name)
  {
    this->coordinates = coordinates;
    this->name = name;
  }
};

class admin
{

public:
  static int numLocations;
  static int numdrivers ;
  static int numusers ;

  // why not adding bool vis array


  
   unordered_map<int , vector<pair<int,float> > > adj;        // adj list    {node id , weight }
  unordered_map<int, location> locationById; // assign id to every location to facilitate the searching
   //just for dijkstra for now till I understand what is going on!!!!!
  unordered_map <int ,driver> drivers ;
  unordered_map <int , user> users ;



  // functions
  admin();
  // Helper function to find location ID by name
  int findLocationByName(const string &locationName);
  bool location_is_found(int loctId);
  bool road_is_found(int, int);
bool  edge_exists(int , int );

  void addGraph();
  void add_location();
  void add_road();

  void delete_location();
  void delete_road();

  void dfs_caller(vector<bool> &visited);
  void dfs(int node, vector<bool> &visited);
  void bfs(queue<int> &Qlocat, vector<bool> &visited, int start);
  void displayData();
  queue<string> dijkstra(user& user,vector<int>&driverNodes);

  float lengthBetNodes (int a , int b );
  void loadData();
  void saveData();
};

#endif
