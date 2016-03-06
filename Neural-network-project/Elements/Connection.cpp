//
//  Connection.cpp
//  Neural-network-project
//


#include "Connection.hpp"

Connection :: Connection()
{
    _weight = rand() / (double) (RAND_MAX);
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

