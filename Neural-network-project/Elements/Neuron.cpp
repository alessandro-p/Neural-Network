//
//  Neuron.cpp
//  Neural-network-project
//

#include "Neuron.hpp"

/* ------------ CONSTANT VALUES --------------------- */
double Neuron :: eta = 0.15;
double Neuron :: alpha = 0.5;


/* Constructor
   It receives
        - The number of neurons in the next layer
        - The index of the neuron itself in order to be identified
 
    The neuron will have a connection for each neurons in the next layer, 
    where a connection has a weight and a delta_weight and is initilized 
    with random values
 */
Neuron :: Neuron(unsigned int num_outputs, unsigned int my_index)
{
    for (unsigned int c = 0; c < num_outputs; ++c)
    {
        _output_weights.push_back(Connection());
    }
    _my_index = my_index;
}

/* Given the previous layer, it works out the output_value for the neuron */
void Neuron :: feed_forward(const Layer &prev_layer)
{
    double sum = 0.0;
    
    /*
     * Sum the previous layer's outputs (which are our inputs, so our x_k)
     * Include the Bias node from the previous layer
     * _my_index is necessary because I have to know which weights are referred
     * to the neuron I am working out the result
     */
    for(unsigned int n = 0; n < prev_layer.size(); n++)
    {
        Connection tmp_conn = prev_layer[n]._output_weights[_my_index];
        double connection_weight = tmp_conn.get_connection_weight();
        
        double output_value = prev_layer[n].get_output_value();
        
        sum += output_value * connection_weight;
    }
    
    _output_value = Neuron :: transfer_function(sum);
}

// Given the target value, it computes the
void Neuron :: calc_output_gradients(double target_val)
{
    double delta = target_val - _output_value;
    _gradient = delta * Neuron :: transfer_function_derivative(_output_value);
}


// Sum of the derivatives of the weight of a layer
double Neuron :: sumDOW(const Layer &next_layer) const
{
    double sum = 0.0;
    
    // Sum contribution of error at the node we feed
    for (unsigned int n = 0; n < next_layer.size()-1; n++)
    {
        Connection tmp_conn = _output_weights[n];
        sum += tmp_conn.get_connection_weight() * next_layer[n]._gradient;
    }
    return sum;
}

// here we don't have a target value which we can compare with
// So we have to look for the sum of the derivatives of the weights of the next layer
void Neuron :: calc_hidden_gradients(const Layer &next_layer)
{
    double dow = sumDOW(next_layer);
    _gradient = dow * Neuron :: transfer_function_derivative(_output_value);
}

void Neuron :: update_input_weights(Layer &prev_layer)
{
    // The weights to be updated are in the connection container in the neurons of the previous layer (backpropagation algorithm)
    for(unsigned int n=0; n < prev_layer.size(); n++)
    {
        Neuron &neuron = prev_layer[n];
        Connection tmp_connection = neuron._output_weights[_my_index];
        
        double old_delta_weight = tmp_connection.get_connection_delta_weight();
       
        // eta is the learning rate, alpha is the momentum: a fraction of the previous delta weight
        double new_delta_weight = eta * neuron.get_output_value() * _gradient
                                    + alpha * old_delta_weight;
        
        tmp_connection.set_connection_delta_weight(new_delta_weight);
       
        
        neuron._output_weights[_my_index]._weight += new_delta_weight;
        
        //tmp_connection.set_connection_weight(tmp_connection.get_connection_weight() + new_delta_weight);
        
    }
    
}

/* --------  GETTERS AND SETTERS --------  */

double Neuron :: get_output_value(void) const
{
    return _output_value;
}

void Neuron :: set_output_value(double val)
{
    _output_value = val;
}

std :: vector<Connection>&  Neuron :: output_weights()
{
    return _output_weights;
}

/*  ---------- ACTIVATION FUNCTIONS AND THEIR DERIVATIVES ------------- */

/* It can be somewhat function, I'll use sigmoid function */
double Neuron :: transfer_function(double x)
{
    return 1.0 / (1.0 + exp(-x));
    
    //return tanh(x);
}

double Neuron :: transfer_function_derivative(double x)
{
    /* Use this when the transfer function is the sigmoid */
    return transfer_function(x) * (1 - transfer_function(x));
    
    /*
     Choose between one of the following when the transfer function is the tangent
     */
    
    // return 1 - tanh(x) * tanh(x);
    //return 1 -x*x;
}














