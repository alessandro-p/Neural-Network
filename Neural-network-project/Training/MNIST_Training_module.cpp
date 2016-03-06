//
//  MNIST_Training_module.cpp
//  Neural-network-project
//


#include "MNIST_Training_module.hpp"

MNIST_Training_module :: MNIST_Training_module()
{
    populate_input_vals(default_input_vals_training_file);
    populate_target_vals(default_targets_vals_training_file);
}

MNIST_Training_module :: MNIST_Training_module(std :: string input_vals_file, std :: string target_vals_file)
{
    populate_input_vals(input_vals_file);
    populate_target_vals(target_vals_file);
}

void MNIST_Training_module :: populate_input_vals(std :: string file_name)
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
        n_cols = Utility :: reverse_int (n_cols);
        
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


void MNIST_Training_module :: populate_target_vals(std :: string file_name)
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

std :: vector<double> MNIST_Training_module ::  get_target_vals(std :: vector<double> target_vals, int index)
{
    std :: vector<double> v(10,0);
    int new_index = target_vals[index];
    
    v[new_index] = 1;
    return v;
}

void MNIST_Training_module :: training_network(Network& net, std :: vector<unsigned int> topology, int epoch)
{
    int training_vals_size = (int) _input_vals.size();
    
    std :: vector<double> input_vals;
    std :: vector<double> target_vals;
    std :: vector<double> result_vals;
    
    int training_iteration = 0;
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
        
        // train the net what the outputs should have been
        target_vals = get_target_vals(_target_vals, i);
        
        std :: cout << "Targets: " << _target_vals[i] << std :: endl;
        assert(target_vals.size() == topology.back());
        
        net.back_propagation(target_vals);
        
        double avg_error = net.get_recent_average_error();
        std :: cout << "Network recent average error: " << avg_error << std :: endl;
    }
    
    std :: stringstream sstream;
    sstream << "./Weights_file/MNIST_weights_file/weights_file_" << topology[1] << "_neurons_ep_" << epoch << ".txt";
    std :: string weights_file_name = sstream.str();
    
    net.save_weights_to_file(net, topology, weights_file_name);
}



