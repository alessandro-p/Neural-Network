//
//  Training_data.hpp
//  Neural-network-project
//
//  Created by Alessandro Petraro on 28/02/16.
//  Copyright © 2016 Alessandro Petraro. All rights reserved.
//

#ifndef Training_data_hpp
#define Training_data_hpp

#include <stdio.h>
#include <fstream>
#include <sstream>

class Training_data
{
public:
    Training_data(const std :: string file_name);
    bool isEOF(void);
    void get_topology(std :: vector<unsigned int> &topology);
    
    // returns the number of input values read from file 
    unsigned int get_next_inputs(std :: vector<double> &input_vals);
    unsigned int get_target_outputs(std :: vector<double> &target_output_vals);
    
    
private:
    std :: ifstream _training_data_file;
    
};




#endif /* Training_data_hpp */
