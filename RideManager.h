
#ifndef RIDEMANAGER_H
#define RIDEMANAGER_H
#include "admin.h"
#include "driver.h"
#include "user.h"


// when to  update  position driver 

class RideManager {


    private :
    admin & Admin;






    public :

    vector <int> toDeleteNodes ;
    RideManager (admin & a) : Admin(a) {} // constructor injection




    void detectOnEdgeDrivers ();
   void addTempNodes (driver & d);

   void deleteTempNodes();
     
};


#endif