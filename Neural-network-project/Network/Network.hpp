//
//  Network.hpp
//  Neural-network-project
//


#ifndef Network_hpp
#define Network_hpp

#include <stdio.h>
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include "Neuron.hpp"

typedef std :: vector<Neuron> Layer;

class Network
{
public:
    Network(const std :: vector<unsigned int> &topology);
    void feed_forward(const std :: vector<double> &input_vals);
    void back_propagation(const std :: vector<double> &target_vals);
    void get_results(std :: vector<double> &result_vals) const;
    double get_recent_average_error(void);
    
    
    void set_initial_weights_from_file(Network& net, std :: vector<unsigned int> topology, std :: string file_name);
    
    void save_weights_to_file(Network& net, std :: vector<unsigned int> topology, std :: string file_name);
    
    std :: vector<Layer>& layers();
    
    
private:
    double _error;
    std :: vector<Layer> _layers;
    double _recent_average_error;
    double _recent_average_smoothing_factor;
    
};


#endif /* Network_hpp */
