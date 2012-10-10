//
//  Movable.cpp
//  D3
//
//  Created by Srđan Rašić on 10/9/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Movable.hpp"

namespace d3 {
    //! Default constructor
    Movable::Movable(SceneNode & mover) : mover(&mover)
    {
    }
    
    //! Sets mover node
    void Movable::setMover(SceneNode & mover)
    {
        this->mover = &mover;
    }
    
    //! @return Mover node
    SceneNode & Movable::getMover() const
    {
        return * mover;
    }
}