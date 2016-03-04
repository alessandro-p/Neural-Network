//
//  MNIST_Loader.hpp
//  Neural-network-project
//
//  Created by Alessandro Petraro on 29/02/16.
//  Copyright © 2016 Alessandro Petraro. All rights reserved.
//

#ifndef MNIST_Loader_hpp
#define MNIST_Loader_hpp

#include <stdio.h>
#include <string>
#include "Utility.hpp"


#define file_name_training_vals "./train-images-idx3-ubyte"
#define file_name_target_vals "./train-labels-idx1-ubyte"

#define file_name_test_vals "./t10k-images-idx3-ubyte"
#define file_name_target_vals_for_test "./t10k-labels-idx1-ubyte"


class MNIST_Loader
{
public:
    MNIST_Loader(bool train_network);
    //MNIST_Loader(std :: string file_name_training, std :: string file_name_targets);
    
    void test_net(Network& net, std :: vector<unsigned int> topology);
    
    void training_network(Network& net, std :: vector<unsigned int> topology, int epoch);
    
    std :: vector <std :: vector <double>> training_vals();
    std :: vector <double> target_vals();
    
private:
    
    int reverseInt (int i);
    void populate_target_vals(std :: string file_name);
    void populate_training_vals(std :: string file_name);
    int evaluate(std :: vector<double> outputs, double target);
    std :: vector<double> get_target_vals(std :: vector<double> target_vals, int index);
    

    
    std :: vector <std :: vector<double>> _training_vals;
    std :: vector <double> _target_vals;
};




#endif /* MNIST_Loader_hpp */
