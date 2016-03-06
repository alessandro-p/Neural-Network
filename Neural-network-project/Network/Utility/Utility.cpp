//
//  Utility.cpp
//  Neural-network-project
//
//  Created by Alessandro Petraro on 04/03/16.
//  Copyright © 2016 Alessandro Petraro. All rights reserved.
//

#include "Utility.hpp"

void Utility :: show_vector_vals(std :: string label, std :: vector<double> &v)
{

    std :: cout << label << " ";
    for (unsigned int i = 0; i < v.size(); i++)
    {
        std :: cout << v[i] << " ";
    }
    std :: cout << std :: endl;
}

int Utility :: reverse_int (int i)
{
    unsigned char c1, c2, c3, c4;
    
    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;
    
    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}