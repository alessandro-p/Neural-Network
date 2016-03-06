//
//  MNIST_Testing_module.cpp
//  Neural-network-project
//

#include "MNIST_Testing_module.hpp"

MNIST_Testing_module :: MNIST_Testing_module()
{
    populate_input_vals(default_input_vals_test_file);
    populate_target_vals(default_targets_vals_test_file);
}

MNIST_Testing_module :: MNIST_Testing_module(std :: string input_vals_file, std :: string target_vals_file)
{
    populate_input_vals(input_vals_file);
    populate_target_vals(target_vals_file);
}

void MNIST_Testing_module :: populate_input_vals(std :: string file_name)
{
    std :: ifstream file (file_name, std:: ios :: binary);
    
    if(file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = Utility :: reverse_int(magic_number);
        
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = Utility :: reverse_int(number_of_images);
        
        file.read((char*) &n_rows, sizeof(n_rows));
        n_rows = Utility :: reverse_int(n_rows);
        
        file.read((char*) &n_cols, sizeof(n_cols));
        n_cols = Utility :: reverse_int(n_cols);
        
        for(int i = 0; i < number_of_images; ++i)
        {
            std :: vector<double> tp;
            for(int r = 0; r < n_rows; ++r)
            {
                for(int c = 0; c < n_cols; ++c)
                {
                    unsigned char temp = 0;
                    file.read((char*) &temp, sizeof(temp));
                    
                    tp.push_back((double)temp);
                }
            }
            _input_vals.push_back(tp);
        }
    }
}

void MNIST_Testing_module :: populate_target_vals(std :: string file_name)
{
    std :: ifstream file (file_name, std :: ios :: binary);
    
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = Utility :: reverse_int(magic_number);
        
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = Utility :: reverse_int(number_of_images);
        
        for(int i = 0; i < number_of_images; ++i)
        {
            unsigned char temp = 0;
            
            file.read((char*) &temp, sizeof(temp));
            _target_vals.push_back((double)temp);
        }
    }
}

std :: vector<double> MNIST_Testing_module ::  get_target_vals(std :: vector<double> target_vals, int index)
{
    std :: vector<double> v(10,0);
    int new_index = target_vals[index];
    
    v[new_index] = 1;
    return v;
}

void MNIST_Testing_module :: test_net(Network& net, std :: vector<unsigned int> topology)
{
    int training_vals_size = (int) _input_vals.size();
    
    std :: vector<double> result_vals;
    
    int training_iteration = 0;
    int correct = 0;
    for(int i = 0; i < training_vals_size; i++)
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
    
    std :: cout << "Correct: " << correct << " Out of: " << training_vals_size << std :: endl;
}

int MNIST_Testing_module :: evaluate(std :: vector<double> outputs, double target)
{
    double max = -99999;
    std :: vector<int> int_output = {0,1,2,3,4,5,6,7,8,9};
    
    int index;
    int max_index = 0;
    
    for (index = 0; index < outputs.size(); index++)
    {
        if(outputs[index] > max)
        {
            max = outputs[index];
            max_index = index;
        }
        
    }
    std :: cout << "Output: " << int_output[max_index] << "Target: " << target << std :: endl;
    if(int_output[max_index] == target)
    {
        return 1;
    }
    return 0;
}
