//
//  Training_data.cpp
//  Neural-network-project
//
//  Created by Alessandro Petraro on 28/02/16.
//  Copyright © 2016 Alessandro Petraro. All rights reserved.
//

#include "Training_data.hpp"



Training_data :: Training_data(const std :: string file_name)
{
    _training_data_file.open(file_name.c_str());
    
    if(!_training_data_file.is_open())
    {
        std :: cout << "Error opening the file..." << std :: endl;
    }

}

bool Training_data :: isEOF(void)
{
    return _training_data_file.eof();
}

void Training_data :: get_topology(std :: vector<unsigned int> &topology)
{
    std :: string line;
    std :: string label;
    
    
    std :: getline(_training_data_file, line);
    std :: stringstream ss(line);
    
    ss >> label;
    if(this->isEOF() || label.compare("topology:") != 0 )
    {
        abort();
    }
    
    while(!ss.eof())
    {
        unsigned int n;
        ss >> n;
        topology.push_back(n);
    }
    return;
    
}

unsigned int Training_data :: get_next_inputs(std :: vector<double> &input_vals)
{
    input_vals.clear();
    
    std :: string line;
    getline(_training_data_file, line);
    std :: stringstream ss(line);
    
    std :: string label;
    ss >> label;
    
    if(label.compare("in:") == 0)
    {
        double one_value;
        while(ss >> one_value)
        {
            input_vals.push_back(one_value);
        }
    }
    
    return (unsigned int) input_vals.size();
    
    
    
}

unsigned int Training_data :: get_target_outputs(std :: vector<double> &target_output_vals)
{
    target_output_vals.clear();
    
    std :: string line;
    getline(_training_data_file, line);
    std :: stringstream ss(line);
    
    std :: string label;
    ss >> label;
    
    if(label.compare("out:") == 0)
    {
        double one_value;
        while(ss >> one_value)
        {
            target_output_vals.push_back(one_value);
        }
    }

    return (unsigned int) target_output_vals.size();
}