//
//  EXOR_Training_module.hpp
//  Neural-network-project
//
//  Created by Alessandro Petraro on 05/03/16.
//  Copyright © 2016 Alessandro Petraro. All rights reserved.
//

#ifndef EXOR_Training_module_hpp
#define EXOR_Training_module_hpp

#include <stdio.h>

#include <stdio.h>
#include <fstream>
#include <sstream>
#include "Utility.hpp"

#define default_exor_input_vals_training_file "./Data/data_EXOR/training/exor_file_input_vals_training.txt"
#define default_exor_targets_vals_training_file "./Data/data_EXOR/training/exor_file_target_vals_training.txt"

class EXOR_Training_module
{
public:
    EXOR_Training_module();
    EXOR_Training_module(const std :: string input_vals_file, const std :: string target_vals_file);
    
    void training_network(Network& net, std :: vector<unsigned int> topology, int epoch);
    
    
    
private:
    void populate_input_vals(std :: string file_name);
    void populate_target_vals(std :: string file_name);
    std :: vector <std :: vector<double>> _input_vals;
    std :: vector <double> _target_vals;
    
};

#endif /* EXOR_Training_module_hpp */
