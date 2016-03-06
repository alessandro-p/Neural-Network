//
//  main.cpp
//  Neural-network-project
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
    /* ------ Network for MNIST DATA ------ */
    
    std :: vector<unsigned int> topology = {784, 30, 10};
    Network net(topology);
    
    MNIST_Training_module mtraining;
    MNIST_Testing_module mtest;
    
    /* 0 is the epoch */
    mtraining.training_network(net, topology, 0);
    mtest.test_net(net, topology);
    
     
    /* --- Network for EXOR DATA ---- */
    
    /*
    std :: vector<unsigned int> topology = {2, 5, 1};
    Network net(topology);
    
    EXOR_Training_module exor_training;
    exor_training.training_network(net, topology, 0);
    
    EXOR_Testing_module exor_testing;
    exor_testing.test_net(net, topology); 
     
     */
    
    std :: cout << std :: endl << "Done" << std :: endl;
    
    return 0;
}
