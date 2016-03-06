//
//  EXOR_Testing_module.hpp
//  Neural-network-project
//
//  Created by Alessandro Petraro on 05/03/16.
//  Copyright © 2016 Alessandro Petraro. All rights reserved.
//

#ifndef EXOR_Testing_module_hpp
#define EXOR_Testing_module_hpp

#include <stdio.h>

#include <stdio.h>

#include <stdio.h>
#include <fstream>
#include <sstream>
#include "Utility.hpp"

#define default_exor_input_vals_testing_file "./Data/data_EXOR/testing/exor_file_input_vals_testing.txt"
#define default_exor_targets_vals_testing_file "./Data/data_EXOR/testing/exor_file_target_vals_testing.txt"

class EXOR_Testing_module
{
public:
    EXOR_Testing_module();
    EXOR_Testing_module(const std :: string input_vals_file, const std :: string target_vals_file);
    
    void test_net(Network& net, std :: vector<unsigned int> topology);

private:
    void populate_input_vals(std :: string file_name);
    void populate_target_vals(std :: string file_name);
    std :: vector <std :: vector<double>> _input_vals;
    std :: vector <double> _target_vals;
    int evaluate(std :: vector<double> outputs, double target);
    
};


#endif /* EXOR_Testing_module_hpp */
