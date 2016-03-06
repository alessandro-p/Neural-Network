//
//  MNIST_Testing_module.hpp
//  Neural-network-project
//

#ifndef MNIST_Testing_module_hpp
#define MNIST_Testing_module_hpp

#include <stdio.h>

#define default_input_vals_test_file "./Data/data_MNIST/testing/t10k-images-idx3-ubyte"
#define default_targets_vals_test_file "./Data/data_MNIST/testing/t10k-labels-idx1-ubyte"

class MNIST_Testing_module
{
public:
    MNIST_Testing_module();
    MNIST_Testing_module(std :: string input_vals_file, std :: string target_vals_file);
    
    void test_net(Network& net, std :: vector<unsigned int> topology);
    
private:
    void populate_target_vals(std :: string file_name);
    void populate_input_vals(std :: string file_name);
    int evaluate(std :: vector<double> outputs, double target);
    std :: vector<double> get_target_vals(std :: vector<double> target_vals, int index);
    
    std :: vector <std :: vector<double>> _input_vals;
    std :: vector <double> _target_vals;
};

#endif /* MNIST_Testing_module_hpp */