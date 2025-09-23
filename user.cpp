//
// Created by Hana on 9/2/2025.
//

#include "user.h"

#include "driver.h"

user :: user (string name , string email , string telephone , string password){
    this->name = name ;
    this->email = email;
    this->telephone = telephone ;
    this->password =  password ;
}

//getters
location user :: getCurrLocation(){
    return this->curr_location;
}

location user :: getDestination(){
    return this-> destination ;
}

//setters

void user :: setCurrLocation(int x , int y , string name){
    this -> curr_location = location({x,y},name);
}


void user :: setDestination(int x , int y , string name){
    this -> destination= location({x,y},name);
}


void user :: requestRide(admin & Admin ){
    string curr, dest ;
    cout << "Enter the pick up and drop off locations ' names :" << l ;
    cin >> curr >> dest ;
    int firstID = Admin.findLocationByName(curr);
    int secondID = Admin.findLocationByName(dest);
    if(!(Admin.location_is_found(firstID) && Admin.location_is_found(secondID))){
         cout << "One or both locations not found!" << endl;
        return;
    }
    location current = Admin.locationById[firstID];
    location destination = Admin.locationById[secondID];


    // here we should add function call
    int driverId=Admin.driverdijkstra(currNode,Admin.driverNodes);
    if (driverId == -1) {
        cout << "Try Again Later....." << endl;
    }
    Admin.drivers[driverId].available=false;
    currDriver = Admin.drivers[driverId];
    cout<<"your driver will be here soon"<<l;
    cout<<"Driver name :"<<currDriver.name<<endl;
    cout<<"Driver email :"<<currDriver.email<<endl;
    cout<<"Driver telephone :"<<currDriver.telephone<<endl;

    // after implementing dijkstra we should call it with current and destination being the parameters 
    vector<int>path=Admin.pathdijkstra(currNode,destination_node,currDriver);// we need to put this in the user class
    for (int i=0;i<path.size();i++) {
        cout<<Admin.locationById[path[i]].name<<" "<<" ";
    }
    cout<<"Thank you for riding Wasalni!"<<l;
}