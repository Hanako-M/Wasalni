//
// Created by Hana on 9/2/2025.
//

#ifndef DRIVER_H
#define DRIVER_H
#include "admin.h"
#include<set>


class driver {



    public :
    string password;
    public :
    float progress ;
pair<int,int>street; // node1 , node2
bool available = true;
    std::vector<int> driverNodes; // NEW: track temp nodes for this driver


location curr_location=location({0,0}," ");

string name;
string email;
string telephone;



    driver() = default; // 👈 ADD THIS
driver(string name ,string email,string telephone,string pass);
void setdriverlocation(location curr_locat,pair<int,int>street);
void setavailability(bool available);


void update_progress (float delta  , admin & a);
void snapToEdge (int node  , admin & a);
void set_edge (pair <int , int > street  );

};




#endif //DRIVER_H
