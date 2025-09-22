//
// Created by Hana on 9/2/2025.
//

#include "driver.h"

driver::driver(string name ,string email,string telephone,string pass) {
    this->name = name;
    this->email = email;
    this->telephone = telephone;
    password=pass;
}
void driver::setdriverlocation(location curr_locat,pair<int,int>street) {
    this->curr_location=curr_locat;
    this->street=street;

}
void driver::setavailability(bool available) {
    this->available=available;
}



void driver :: update_progress (float delta , admin & a){
    progress += delta ;
   // if(! (progress % 1.0 ))


   if (progress >= 1.0 ){
      progress -= 1.0;
      snapToEdge(this->street.second , a);
      
   }

  

}


void driver :: snapToEdge (int node , admin & a){
int prevNode = this->street.first ;




auto it = a.adj.find(node);
    if (it == a.adj.end() || it->second.empty()) {
        // no neighbors: stay where you are
        this->street = {node, prevNode};
        return;
    }



    // build list of candidates excluding prevNode
    std::vector<int> candidates;
    for (const auto &p : it->second) {
        if (p.first != prevNode) candidates.push_back(p.first);
    }

    if (!candidates.empty()) {
        int randomIndex = rand() % candidates.size();
        this->street = {node, candidates[randomIndex]};
    } else {
        // no candidates except prevNode => bounce back
        this->street = {node, prevNode};
    }


//  vector <pair < int , float> > neighbors = a.adj[node];

// neighbors.erase(remove(neighbors.begin(),neighbors.end(),prevNode));

    
//     if(! neighbors.empty() ){
//         int randomIndex = rand() % neighbors.size();
//         this->street = {node , neighbors[randomIndex].first};
//     }else{
//         this->street = {node , prevNode};
//     }

    

    
   

    // there's a case I should handle -> bouncing forever between these to two nodes 



}



void driver :: set_edge(pair <int , int > street){
    this -> street = street ;
}