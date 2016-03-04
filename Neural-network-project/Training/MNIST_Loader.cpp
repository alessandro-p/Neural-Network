//
//  MNIST_Loader.cpp
//  Neural-network-project
//
//  Created by Alessandro Petraro on 29/02/16.
//  Copyright © 2016 Alessandro Petraro. All rights reserved.
//

#include "MNIST_Loader.hpp"


MNIST_Loader :: MNIST_Loader(bool train_network)
{
    if(!train_network)
    {
        populate_training_vals(file_name_training_vals);
        populate_target_vals(file_name_target_vals);
        return;
    }
    populate_training_vals(file_name_test_vals);
    populate_target_vals(file_name_target_vals_for_test);
    return;
}

/*
MNIST_Loader :: MNIST_Loader(std :: string file_name_training, std :: string file_name_targets)
{
    populate_training_vals(file_name_training);
    populate_target_vals(file_name_targets); 
}
 */


int MNIST_Loader :: reverseInt (int i)
{
    unsigned char c1, c2, c3, c4;
    
    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;
    
    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}


void MNIST_Loader :: populate_training_vals(std :: string file_name)
{
    std :: ifstream file (file_name, std:: ios :: binary);
    
    if(file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);
        
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        
        file.read((char*) &n_rows, sizeof(n_rows));
        n_rows = reverseInt(n_rows);
        
        file.read((char*) &n_cols, sizeof(n_cols));
        n_cols = reverseInt(n_cols);
        
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
            _training_vals.push_back(tp);
        }
    }

}

void MNIST_Loader :: populate_target_vals(std :: string file_name)
{
    std :: ifstream file (file_name, std :: ios :: binary);
    
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);
        
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        
        for(int i = 0; i < number_of_images; ++i)
        {
            unsigned char temp = 0;
            
            file.read((char*) &temp, sizeof(temp));
            _target_vals.push_back((double)temp); 
        }
    }
}



void MNIST_Loader :: test_net(Network& net, std :: vector<unsigned int> topology)
{
    //MNIST_Loader MNIST_Loader(file_name_test_vals, file_name_target_vals_for_test);
    
    // std :: vector<std :: vector<double>> test_vals = MNIST_Loader.training_vals();
    int training_vals_size = (int) _training_vals.size();
    
    //std :: vector<double> label_vals_for_test = MNIST_Loader.target_vals();
    
    std :: vector<double> result_vals;
    
    int training_iteration = 0;
    int correct = 0;
    for(int i = 0; i < training_vals_size; i++)
    {
        training_iteration++;
        std :: cout << std :: endl << "Iteration number: " << training_iteration << std :: endl;
        
        // get new input data and feed it forward
        if(_training_vals[i].size() != topology[0])
        {
            std :: cout << "Number of inputs differs from topology[0]" << std :: endl;
            break;
        }
        net.feed_forward(_training_vals[i]);
        
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


int MNIST_Loader :: evaluate(std :: vector<double> outputs, double target)
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

std :: vector<double> MNIST_Loader ::  get_target_vals(std :: vector<double> target_vals, int index)
{
    std :: vector<double> v(10,0);
    int new_index = target_vals[index];
    
    v[new_index] = 1;
    return v;
}

void MNIST_Loader :: training_network(Network& net, std :: vector<unsigned int> topology, int epoch)
{
    
    //MNIST_Loader MNIST_Loader(file_name_training_vals, file_name_target_vals);
    //std :: vector<std :: vector<double>> training_vals = MNIST_Loader.training_vals();
    int training_vals_size = (int) _training_vals.size();
    
    //std :: vector<double> label_vals = MNIST_Loader.target_vals();
    
    std :: vector<double> input_vals;
    std :: vector<double> target_vals;
    std :: vector<double> result_vals;
    
    
    int training_iteration = 0;
    for(int i = 0; i < training_vals_size; i++)
    {
        training_iteration++;
        std :: cout << std :: endl << "Iteration number: " << training_iteration << std :: endl;
        
        // get new input data and feed it forward
        if(_training_vals[i].size() != topology[0])
        {
            std :: cout << "Number of inputs differs from topology[0]" << std :: endl;
            break;
        }
        net.feed_forward(_training_vals[i]);
        
        // collect the net's actual results
        net.get_results(result_vals);
        Utility :: show_vector_vals(": Outputs: ", result_vals);
        
        // train the net what the outputs should have been
        target_vals = get_target_vals(_target_vals, i);
        
        std :: cout << "Targets: " << _target_vals[i] << std :: endl;
        assert(target_vals.size() == topology.back());
        
        net.back_propagation(target_vals);
        
        double avg_error = net.get_recent_average_error();
        std :: cout << "Network recent average error: " << avg_error << std :: endl;
    }
    
    std :: stringstream sstream;
    sstream << "weights_file_" << topology[1] << "_neurons_ep_" << epoch << ".txt";
    std :: string weights_file_name = sstream.str();
    
    
    net.save_weights_to_file(net, topology, weights_file_name);
    
}

/* ------- GETTER ------- */

std :: vector <std :: vector <double>> MNIST_Loader :: training_vals()
{
    return _training_vals;
}

std :: vector <double> MNIST_Loader ::target_vals()
{
    return _target_vals;
}
























