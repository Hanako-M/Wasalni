# include "RideManager.h"
#include "admin.h"


void RideManager :: detectOnEdgeDrivers (){
    for (auto [id , D] : Admin.drivers ){
 // Only if driver is really *between* nodes
        if (D.progress > 0.0 && D.progress < 1.0) {
            addTempNodes(D);
        }

    }
}

void RideManager :: addTempNodes (driver & d) {
    /*
    x = (1 - progress) * xA + progress * xB
    y = (1 - progress) * yA + progress * yB
    */


    int firstNode = d.street.first;
    int secondNode = d.street.second;

    float x = (1-d.progress ) * Admin.locationById[firstNode].coordinates.first + d.progress *  Admin.locationById[secondNode].coordinates.first ;
    float y = (1-d.progress ) * Admin.locationById[firstNode].coordinates.second + d.progress *  Admin.locationById[secondNode].coordinates.second ;
    string city1 = Admin.locationById[firstNode].name;
    string city2 = Admin.locationById[secondNode].name;

    d.curr_location = location( { x , y } , "between" + city1 + "and"  + city2 );


    int tempId = Admin.numLocations++ ;
    toDeleteNodes.push_back(tempId);
    d.driverNodes.push_back(tempId); // ✅ track this driver's temp node
    Admin.locationById[tempId] = d.curr_location ;



    float distA_temp = d.progress * Admin.lengthBetNodes(firstNode , secondNode) , distB_temp = (1-d.progress) * Admin.lengthBetNodes(firstNode , secondNode ) ;

    Admin.adj[firstNode].push_back({tempId, distA_temp});
    Admin.adj[tempId].push_back({firstNode,distA_temp});

    Admin.adj[secondNode].push_back({tempId, distB_temp});
    Admin.adj[tempId].push_back({secondNode,distB_temp});

    /*
    Connect it to A with distance = progress * length(A,B).
    Connect it to B with distance = (1 - progress) * length(A,B).
        */
}
    void RideManager::removeDriverNodes(driver &d) {
        for (int tempId : d.driverNodes) {
            Admin.locationById.erase(tempId);
            Admin.adj.erase(tempId);

            // Also remove references to tempId in other adjacency lists
            for (auto &[node, neighbors] : Admin.adj) {
                neighbors.erase(remove_if(neighbors.begin(), neighbors.end(),
                                          [tempId](auto &p){ return p.first == tempId; }),
                                neighbors.end());
            }
        }
        d.driverNodes.clear();
    }

void RideManager::updateDriver(driver &d, float delta) {
    d.update_progress(delta, Admin);

    removeDriverNodes(d);   // remove old temp nodes
    addTempNodes(d);        // add new temp node based on updated progress
}
