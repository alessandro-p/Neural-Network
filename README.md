# Neural-Network

This is a simple implementation af a neural network. There are two main training modules: 
- EXOR_Training_module: A simple "toy-module" that train the network to behave like an EXOR
- MNIST_Training_module: A module that uses MNIST Data in order to train the network to recognize hand-written digits

In order to test the network, you can then use the respective testing modules: 
- EXOR_Testing_module
- MNIST_Testing_Module

In this implementation I have not kept into account the epochs, but you can simply extend the network in order to make it able to do it. 

The class Neuron has two important methods called Transfer function and Transfer function derivative. 
Changing between different transfer functions will influence the network performance. 
