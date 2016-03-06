//
//  MNIST_Training_module.hpp
//  Neural-network-project
//


#ifndef MNIST_Training_module_hpp
#define MNIST_Training_module_hpp

#include <stdio.h>

#define default_input_vals_training_file "./Data/data_MNIST/training/train-images-idx3-ubyte"
#define default_targets_vals_training_file "./Data/data_MNIST/training/train-labels-idx1-ubyte"

class MNIST_Training_module
{
public:
    MNIST_Training_module();
    MNIST_Training_module(std :: string input_vals_file, std :: string target_vals_file);
    
    void training_network(Network& net, std :: vector<unsigned int> topology, int epoch);
    
private:
    void populate_target_vals(std :: string file_name);
    void populate_input_vals(std :: string file_name);
    std :: vector<double> get_target_vals(std :: vector<double> target_vals, int index);
    
    std :: vector <std :: vector<double>> _input_vals;
    std :: vector <double> _target_vals;
};

#endif /* MNIST_Training_module_hpp */
