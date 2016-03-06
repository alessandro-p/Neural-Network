//
//  EXOR_Training_module.cpp
//  Neural-network-project
//

#include "EXOR_Training_module.hpp"

EXOR_Training_module :: EXOR_Training_module()
{
    populate_input_vals(default_exor_input_vals_training_file);
    populate_target_vals(default_exor_targets_vals_training_file);
}

EXOR_Training_module :: EXOR_Training_module(std :: string input_vals_file, std :: string target_vals_file)
{
    populate_input_vals(input_vals_file);
    populate_target_vals(target_vals_file);
}

void EXOR_Training_module :: populate_input_vals(std :: string file_name)
{
    std :: ifstream input_vals_file(file_name);
    if (! input_vals_file.is_open())
    {
        std :: cout << "Error openinig input vals file...";
        return;
    }
    
    std :: string line;
    std :: vector <double> inputs;
    
    double n1;
    double n2;
    
    while(! input_vals_file.eof())
    {
        inputs.clear(); 
        std :: getline(input_vals_file, line);
        std :: stringstream ss(line);
        
        ss >> n1;
        ss >> n2;
        
        inputs.push_back(n1);
        inputs.push_back(n2);
        
        _input_vals.push_back(inputs);
    }
}

void EXOR_Training_module :: populate_target_vals(std :: string file_name)
{
    std :: ifstream target_vals_file(file_name);
    if (! target_vals_file.is_open())
    {
        std :: cout << "Error openinig input vals file...";
        return;
    }
    
    std :: string line;
    double res;
    
    while(! target_vals_file.eof())
    {
        std :: getline(target_vals_file, line);
        std :: stringstream ss(line);
        
        ss >> res;
        
        _target_vals.push_back(res);
    }
}


void EXOR_Training_module :: training_network(Network& net, std :: vector<unsigned int> topology, int epoch)
{
    
    int training_iteration = 0;
    int input_vals_size = (int) _input_vals.size();
    
    std :: vector<double> result_vals;
    std :: vector<double> target_vals;
    
    for (int i = 0; i< input_vals_size; i++)
    {
        target_vals.clear();
        
        training_iteration++;
        std :: cout << std :: endl << "Iteration number: " << training_iteration << std :: endl;
        
        if(_input_vals[i].size() != topology[0])
        {
            std :: cout << "Number of inputs differs from topology[0]" << std :: endl;
            break;
        }
        
        Utility :: show_vector_vals("Inputs: ", _input_vals[i]);
        net.feed_forward(_input_vals[i]);
        
        net.get_results(result_vals);
        Utility :: show_vector_vals("Outputs: ", result_vals);
        
        // train the net what the outputs should have been
        target_vals.push_back(_target_vals[i]);
        Utility :: show_vector_vals("Outputs: ", target_vals);

        assert (target_vals.size() == topology.back());
        net.back_propagation(target_vals);
        
        double avg_error = net.get_recent_average_error();
        std :: cout << "Network recent average error: " << avg_error << std :: endl;
    }
    
    std :: stringstream sstream;
    sstream << "./Weights_file/EXOR_weights-file/exor_weights_file_" << topology[1] << "_neurons_ep_" << epoch << ".txt";
    std :: string weights_file_name = sstream.str();
    
    net.save_weights_to_file(net, topology, weights_file_name);
}

