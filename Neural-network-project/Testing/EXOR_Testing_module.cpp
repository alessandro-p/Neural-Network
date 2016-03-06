//
//  EXOR_Testing_module.cpp
//  Neural-network-project
//

#include "EXOR_Testing_module.hpp"

EXOR_Testing_module :: EXOR_Testing_module()
{
    populate_input_vals(default_exor_input_vals_testing_file);
    populate_target_vals(default_exor_targets_vals_testing_file);
}

EXOR_Testing_module :: EXOR_Testing_module(std :: string input_vals_file, std :: string target_vals_file)
{
    populate_input_vals(input_vals_file);
    populate_target_vals(target_vals_file);
}

void EXOR_Testing_module :: populate_input_vals(std :: string file_name)
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

void EXOR_Testing_module :: populate_target_vals(std :: string file_name)
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

int EXOR_Testing_module :: evaluate(std :: vector<double> outputs, double target)
{
    int output = (outputs[0] >= 0.5) ? 1 : 0;
    return output == (int )target;
}

void EXOR_Testing_module :: test_net(Network& net, std :: vector<unsigned int> topology)
{
    int input_vals_size = (int) _input_vals.size();
    
    std :: vector<double> result_vals;
    
    int training_iteration = 0;
    int correct = 0;
    for(int i = 0; i < input_vals_size; i++)
    {
        training_iteration++;
        std :: cout << std :: endl << "Iteration number: " << training_iteration << std :: endl;
        
        // get new input data and feed it forward
        if(_input_vals[i].size() != topology[0])
        {
            std :: cout << "Number of inputs differs from topology[0]" << std :: endl;
            break;
        }
        net.feed_forward(_input_vals[i]);
        
        // collect the net's actual results
        net.get_results(result_vals);
        Utility :: show_vector_vals(": Outputs: ", result_vals);
        
        correct += evaluate(result_vals, _target_vals[i]);
        
        double avg_error = net.get_recent_average_error();
        std :: cout << "Network recent average error: " << avg_error << std :: endl;
    }
    std :: cout << "_________________________________________________" << std :: endl << std :: endl;
    
    std :: cout << "Correct: " << correct << " Out of: " << input_vals_size << std :: endl;
}