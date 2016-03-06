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
    std :: ofstream input_vals_file_training;
    std :: ofstream target_vals_file_training;
    
    input_vals_file_training.open("./exor_file_input_vals_training.txt");
    target_vals_file_training.open("./exor_file_target_vals_training.txt");
    
    for(int i = 10000; i >= 0; --i)
    {
        int n1 = (int)(2.0 * rand() / double(RAND_MAX));
        int n2 = (int)(2.0 * rand() / double(RAND_MAX));
        int t = n1 ^ n2; // logic bitwise xor
        
        input_vals_file_training << n1 << ".0 " << n2 << ".0 " << std :: endl;
        
        target_vals_file_training << t << ".0 " << std :: endl;
    }
    
    std :: ofstream input_vals_file_testing;
    std :: ofstream target_vals_file_testing;
    
    input_vals_file_testing.open("./exor_file_input_vals_testing.txt");
    target_vals_file_testing.open("./exor_file_target_vals_testing.txt");
    for(int i = 2000; i >= 0; --i)
    {
        int n1 = (int)(2.0 * rand() / double(RAND_MAX));
        int n2 = (int)(2.0 * rand() / double(RAND_MAX));
        int t = n1 ^ n2; // logic bitwise xor
        
        input_vals_file_testing << n1 << ".0 " << n2 << ".0 " << std :: endl;
        
        target_vals_file_testing << t << ".0 " << std :: endl;
    }
}