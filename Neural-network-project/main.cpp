//
//  main.cpp
//  Neural-network-project
//
//  Created by Alessandro Petraro on 23/02/16.
//  Copyright © 2016 Alessandro Petraro. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string> 
#include <fstream> 

#include "Network/Network.cpp"
#include "Elements/Neuron.cpp"
#include "Elements/Connection.cpp"
#include "Network/Utility/Utility.cpp"

#include "Training/MNIST_Training_module.cpp"
#include "Testing/MNIST_Testing_module.cpp"

#include "Training/EXOR_Training_module.cpp"
#include "Testing/EXOR_Testing_module.cpp"

/* We have 3 distinct phases
 
 1. Feedforward phase: At first we have to do the feedforward for the network. For the input layer it will be the simple propagation of the input values becuase the are like latches. For the hidden and the output layers it will be the activation function (sigmoid, tg, ...) of the sum of W*X + Bias.
 
 It has as parameters the input values
 
 
 2. Backpropagation phase: Secondly we have to calibrate the weights in order to train the network. So, we give the network the target values or in other words the values we know are correct so that the network can work out the error and change the weights according to that.
 
 It has as parameters the target values.
 
 We'll repeate phase 1 and phase 2 in order to train the network in a loop.
 
 In order to test the network, we'll have to repeat only phase 1 and phase 3
 */


int main(int argc, const char * argv[])
{
    
    std :: vector<unsigned int> topology = {784, 120, 10};
    Network net(topology);
    
    MNIST_Training_module mtraining;
    MNIST_Testing_module mtest;
    
    //net.set_initial_weights_from_file(net, topology, "./Weights_file/MNIST_weights_file/weights_file_30_neurons_ep_0.txt");
    
    mtraining.training_network(net, topology, 0);
    mtest.test_net(net, topology);
    
     
    
    
    /*
    std :: vector<unsigned int> topology = {2, 5, 1};
    Network net(topology);
    
    net.set_initial_weights_from_file(net, topology, "./Weights_file/EXOR_weights-file/exor_weights_file_5_neurons_ep_0.txt");
    //EXOR_Training_module exor_training;
    //exor_training.training_network(net, topology, 0);
    
    EXOR_Testing_module exor_testing;
    exor_testing.test_net(net, topology); 
     
     */
    

    
    /*
    Training_data training_data("/Users/Alessandro/Desktop/Neural-network-project/Neural-network-project/tmp/training_data.txt");
    
    // We define the topology of the network //
    std :: vector<unsigned int> topology;
    training_data.get_topology(topology);
    
    //std :: shared_ptr<Network> ptr_ntwk = std :: shared_ptr<Network>(new Network(topology));
    
    Network net(topology);
    
    net.set_initial_weights_from_file(net, topology, "./exor_weight.txt");

    std :: vector<double> input_vals;
    std :: vector<double> target_vals;
    std :: vector<double> result_vals;

    int training_iteration = 0;
    
    std :: ofstream myfile;
    myfile.open ("./error_file.txt");
    
    while(!training_data.isEOF())
    {
        training_iteration++;
        std :: cout << std :: endl << "Iteration number: " << training_iteration << std :: endl;
        
        // get new input data and feed it forward
        if(training_data.get_next_inputs(input_vals) != topology[0])
        {
            std :: cout << "Number of inputs differs from topology[0]" << std :: endl;
            break;
        }
        
        show_vector_vals(": Inputs: ", input_vals);
        net.feed_forward(input_vals);
        
        // collect the net's actual results
        net.get_results(result_vals);
        show_vector_vals(": Outputs: ", result_vals);
        
        // train the net what the outputs should have been
        training_data.get_target_outputs(target_vals);
        show_vector_vals("Targets: ", target_vals);
        assert(target_vals.size() == topology.back());
        
        //net.back_propagation(target_vals);
        
        double avg_error = net.get_recent_average_error();
        std :: cout << "Network recent average error: " << avg_error << std :: endl;
        
        if(net.get_recent_average_error() > 0.3 && training_iteration > 9000)
        {
            myfile << "Iteration n: " << training_iteration << " ";
            myfile << "avg error: " << avg_error << std :: endl;
        }
        
    }
    myfile.close();
    */
    //save_weights_to_file(net, topology, "./exor_weight.txt");
    std :: cout << std :: endl << "Done" << std :: endl;
    
    return 0;
}
