//
// Created by Hana on 9/2/2025.
//



#ifndef USER_H
#define USER_H
#include "admin.h"


class user {


public :
    string name;
    string email;
    string telephone;
    string password ;

location curr_location = location({0,0}," ");
location destination =location({0,0}," ");
    user() = default; // 👈 ADD THIS
user (string , string , string , string);

location getCurrLocation ();
location getDestination();


// how will the user enter his current location and destination 
// setters are for admin/manager  not user frindly
void setCurrLocation (int , int , string );
void setDestination (int , int , string);


void requestRide (admin&Admin);



};



#endif //USER_H
