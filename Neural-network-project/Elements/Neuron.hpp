//
//  Neuron.hpp
//  Neural-network-project
//


#ifndef Neuron_hpp
#define Neuron_hpp

#include <stdio.h>
#include <vector>
#include "Connection.hpp"

/* This class models the neuron concept */

class Neuron
{
    typedef std :: vector <Neuron> Layer;
    
public:
    Neuron(unsigned int num_outputs, unsigned int _my_index);
    void feed_forward(const Layer &prev_layer);
    void set_output_value(double val);
    double get_output_value(void) const;
    void calc_output_gradients(double target_val);
    void calc_hidden_gradients(const Layer &next_layer);
    void update_input_weights(Layer &prev_layer);
    
    std :: vector<Connection>&  output_weights();
    
    
    
private:
    static double eta; // [0...1]
    static double alpha; //[0...N]
    static double transfer_function(double x);
    static double transfer_function_derivative(double x);
    double sumDOW(const Layer &next_layer) const;
    double _output_value;
    unsigned int _my_index;
    double _gradient;
    std :: vector<Connection> _output_weights;
    
    
    
};

#endif /* Neuron_hpp */
