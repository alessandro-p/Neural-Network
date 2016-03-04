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