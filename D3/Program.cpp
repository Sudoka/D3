//
//  Program.cpp
//  D3
//
//  Created by Srđan Rašić on 10/10/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Program.hpp"

namespace d3 {
    //! Default constructor
    Program::Program(String name) : name(name)
    {}
    
    //! @return program name
    String Program::getName() const
    {
        return name;
    }
}