//
//  Connection.hpp
//  Neural-network-project
//
//  Created by Alessandro Petraro on 23/02/16.
//  Copyright © 2016 Alessandro Petraro. All rights reserved.
//

#ifndef Connection_hpp
#define Connection_hpp

#include <stdio.h>
#include <chrono>
#include <random> 


class Connection
{
public:
    Connection();
    double get_connection_weight(void);
    double get_connection_delta_weight(void);
    void set_connection_delta_weight(double x);
    void set_connection_weight(double x);
    

    double _weight;
    double _delta_weight;
    
    
    
};

#endif /* Connection_hpp */
