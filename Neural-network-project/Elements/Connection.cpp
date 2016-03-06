//
//  Connection.cpp
//  Neural-network-project
//


#include "Connection.hpp"

Connection :: Connection()
{
    /* construct a trivial random generator engine from a time-based seed:
    unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    
    std::normal_distribution<double> distribution (0.0,1.0);
     
    
    _weight = distribution(generator);
    */
    
    _weight = rand() / (double) (RAND_MAX); 
    ;
}

double Connection :: get_connection_weight(void)
{
    return _weight;
}

void Connection :: set_connection_weight(double x)
{
    _weight = x; 
}

double Connection :: get_connection_delta_weight(void)
{
    return _delta_weight;
}

void Connection :: set_connection_delta_weight(double x)
{
    _delta_weight = x; 
}

