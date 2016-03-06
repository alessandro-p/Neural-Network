# Neural-Network

## Main modules for training and testing

This is a simple implementation af a neural network. There are two main training modules: 
- EXOR_Training_module: A simple "toy-module" that train the network to behave like an EXOR
- MNIST_Training_module: A module that uses MNIST Data in order to train the network to recognize hand-written digits

In order to test the network, you can then use the respective testing modules: 
- EXOR_Testing_module
- MNIST_Testing_Module

In this implementation I have not kept into account the epochs, but you can simply extend the network in order to make it able to do it. 
After each training, I made the network save the weights in a file stored in the Weights_file folder, so that it is also possible to skip 
the training phase using the Network method set_initial_weights_from_file. 

## Folders: Data and Weights_file 

In the data folder are stored the MNIST and the EXOR data. 

The weights_file folder is used to store the weights of the network in a .txt file after each training. 

## The transfer function 

The class Neuron has two important methods called Transfer function and Transfer function derivative. 
Changing between different transfer functions will influence the network performance.

I suggest using the sigmoid function for the MNIST data, while the tangent function for the EXOR data.


