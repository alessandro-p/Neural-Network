//
//  Network.cpp
//  Neural-network-project
//

#include "Network.hpp"

/* Constructor */
Network :: Network(const std :: vector<unsigned int> &topology)
{
    unsigned int num_layers = (unsigned int) topology.size();
    
    for(unsigned int layer_num = 0; layer_num < num_layers; ++layer_num)
    {
        _layers.push_back(Layer());
        
        //num_outputs represents the number of neurons in the next layer (0 for the output layer)
        unsigned int num_outputs = (layer_num == num_layers -1)  ? 0 : topology[layer_num + 1];
        
        // less than equal is used to add the Bias neuron as well
        for(unsigned int neuron_num = 0; neuron_num <= topology[layer_num]; ++neuron_num)
        {
            _layers.back().push_back(Neuron(num_outputs,neuron_num));
            std :: cout << "new Neuron made!" << std::endl;
        }
        
        // Force the bias node's output to be 1.0 -- The last neuron created above
        _layers.back().back().set_output_value(1.0);
    }
}

void Network :: feed_forward(const std :: vector<double> &input_vals)
{
    // To make the feedforward possible the number of inputs must be the same as
    // the number of neurons in the first level (excluded the bias)
    assert(input_vals.size() == _layers[0].size() -1);
    
    
    // For the input layer: output = input (they are like latches)
    for(unsigned int i = 0; i<input_vals.size(); i++)
    {
        _layers[0][i].set_output_value(input_vals[i]);
    }
    
    // For the hidden and output layers, the output is given by the activation function of
    // the sum of W*X + Bias.
    // The feedforward is delegated to each neuron and needs to know the previous layer
    for(unsigned int layer_num = 1; layer_num < _layers.size(); layer_num++)
    {
        Layer &prev_layer = _layers[layer_num-1];
        for(unsigned int n = 0; n < _layers[layer_num].size() -1; n++) // -1 is bias
        {
            _layers[layer_num][n].feed_forward(prev_layer);
        }
    }
}

/* 
 * Given the target values (our desired outputs) it calculates the error and try to
 * calibrate the weights according to that
 */
void Network :: back_propagation(const std :: vector<double> &target_vals)
{
    // Calculate the overall net error (RMSE: Root Mean Square Error)
    // This is the quantity we'll want to minimize
    Layer &output_layer = _layers.back();
    _error = 0.0;
    
    // I am excluding the Bias (-1)
    for (unsigned int n = 0; n < output_layer.size()-1; n++)
    {
        double delta = target_vals[n] - output_layer[n].get_output_value();
        _error += delta*delta;
    }
    
    _error /= output_layer.size() -1;  // get the average error squared
    _error = sqrt(_error);  // RMS
    
    // recent average measure
    _recent_average_error = (_recent_average_error * _recent_average_smoothing_factor + _error)
                                / (_recent_average_smoothing_factor + 1.0);
    
    // Calculate gradients on output layer  (not including the bias)
    for(unsigned int n = 0; n < output_layer.size()-1; n++)
    {
        output_layer[n].calc_output_gradients(target_vals[n]);
    }
    
    // Calculate gradients on hidden layers
    for(unsigned int layer_num = (unsigned int) _layers.size()-2; layer_num > 0; --layer_num)
    {
        Layer &hidden_layer = _layers[layer_num];
        Layer &next_layer = _layers[layer_num+1];
        
        for(unsigned int n = 0; n < hidden_layer.size(); n++)
        {
            hidden_layer[n].calc_hidden_gradients(next_layer);
        }

    }
    
    // For all layers from outputs to first hidden layer, update connection weights
    // This is why is called backpropagation algortithm, I update the connection weights
    // From the last layer to the first hidden layer
    for(unsigned int layer_num = (unsigned int) _layers.size()-1; layer_num >0; --layer_num)
    {
        Layer layer = _layers[layer_num];
        Layer &prev_layer = _layers[layer_num-1];
        
        for(unsigned int n = 0; n < layer.size()-1; n++)
        {
            layer[n].update_input_weights(prev_layer);
        }
    }
}

void Network :: get_results(std :: vector<double> &result_vals) const
{
    result_vals.clear();
    for(unsigned n=0; n < _layers.back().size()-1; ++n )
    {
        result_vals.push_back(_layers.back()[n].get_output_value());
    }
}

/* 
 * UTILITY METHODS -> Load networks weight from file, Save networks weights to file
 */
void Network :: set_initial_weights_from_file(Network& net, std :: vector<unsigned int> topology, std :: string file_name)
{
    
    std :: ifstream weight_file;
    weight_file.open(file_name);
    if (! weight_file.is_open())
    {
        std :: cout << "Error opening weight file...";
    }
    
    std :: string line;
    for(int l = 0; l < topology.size(); l++)
    {
        std :: vector<Layer> layers = net.layers();
        for(int n = 0; n < layers[l].size(); n++)
        {
            std :: vector<Connection> connections = net.layers()[l][n].output_weights();
            
            for(int c = 0; c < connections.size(); c++)
            {
                double weight;
                
                getline(weight_file, line);
                std :: stringstream ss(line);
                
                ss >> weight;
                
                net.layers()[l][n].output_weights()[c].set_connection_weight(weight);
            }
        }
    }
    weight_file.close();
}

void Network :: save_weights_to_file(Network& net, std :: vector<unsigned int> topology, std :: string file_name)
{
    std :: ofstream weight_file;
    weight_file.open (file_name);
    
    for(int l = 0; l < topology.size(); l++)
    {
        //weight_file << "Layers: " << l << std :: endl;
        
        std :: vector<Layer> layers = net.layers();
        for(int n = 0; n < layers[l].size(); n++)
        {
            //weight_file << "     Neuron: " << n << std :: endl;
            std :: vector<Connection> connections = net.layers()[l][n].output_weights();
            
            for(int c = 0; c < connections.size(); c++)
            {
                //weight_file << "             Connection: " << c << " Value: " << connections[c]._weight << std :: endl;
                weight_file << connections[c]._weight << std :: endl;
            }
            
        }
    }
    weight_file.close();
    return;
}

/* GETTERS */
double Network :: get_recent_average_error(void)
{
    return _recent_average_error; 
}

std :: vector<Layer>& Network  :: layers()
{
    return _layers;
}

