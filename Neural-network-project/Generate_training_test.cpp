//
//  Generate_training_test.cpp
//  Neural-network-project
//


#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>


int main()
{
    // Random training set for XOR
    
    std :: ofstream input_vals_file;
    std :: ofstream target_vals_file;
    
    input_vals_file.open("./input_vals_exor_training.txt");
    target_vals_file.open("./target_exor_training.txt");
    
    std :: cout << "topology: 2 4 1" << std :: endl;
    for(int i = 10000; i >= 0; --i)
    {
        int n1 = (int)(2.0 * rand() / double(RAND_MAX));
        int n2 = (int)(2.0 * rand() / double(RAND_MAX));
        int t = n1 ^ n2; // logic bitwise xor
        
        
        input_vals_file << n1 << ".0 " << n2 << ".0 " << std :: endl;
        
        target_vals_file << t << ".0 " << std :: endl;
        
        //std :: cout << "in: " << n1 << ".0 " << n2 << ".0 " << std :: endl;
        //std :: cout << "out: " << t << ".0" << std :: endl;
    }
    
    input_vals_file.open("./input_vals_exor_test.txt");
    target_vals_file.open("./target_exor_test.txt");
    for(int i = 2000; i >= 0; --i)
    {
        int n1 = (int)(2.0 * rand() / double(RAND_MAX));
        int n2 = (int)(2.0 * rand() / double(RAND_MAX));
        int t = n1 ^ n2; // logic bitwise xor
        
        
        input_vals_file << n1 << ".0 " << n2 << ".0 " << std :: endl;
        
        target_vals_file << t << ".0 " << std :: endl;
        
        //std :: cout << "in: " << n1 << ".0 " << n2 << ".0 " << std :: endl;
        //std :: cout << "out: " << t << ".0" << std :: endl;
    }
}

