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
#include "Training/Training_data.cpp"
#include "Training/MNIST_Loader.cpp"
#include "Network/Utility/Utility.cpp"

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
    std :: vector<unsigned int> topology = {784, 30, 10};
    Network net(topology);
    
    net.set_initial_weights_from_file(net, topology, "./weights_file_30_neurons_ep_1.txt");
    
    //MNIST_Loader mn_train(true);
    //mn_train.training_network(net, topology, 2);
    
    //MNIST_Loader mn_train(true);
    //for (int epoch = 0; epoch < 2; epoch++)
    //   mn_train.training_network(net, topology, epoch);
    
    
    MNIST_Loader mn_test(false);
    mn_test.test_net(net, topology);
    
    
    
    
    
    
    
    //set_initial_weights_from_file(net,topology, weights_file_name);
    //test_net(net, topology);
    
    /*
    Training_data training_data("/Users/Alessandro/Desktop/Neural-network-project/Neural-network-project/tmp/training_data.txt");
    
    // We define the topology of the network //
    std :: vector<unsigned int> topology;
    training_data.get_topology(topology);
    
    //std :: shared_ptr<Network> ptr_ntwk = std :: shared_ptr<Network>(new Network(topology));
    
    Network net(topology);
    
    net = set_initial_weights_from_file(net, topology, "./exor_weight.txt");

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
