//
//  Occurable.cpp
//  D3
//
//  Created by Srđan Rašić on 10/8/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Occurable.hpp"

namespace d3 {
    //! Adds new node of origin (where object is to be rendered)
    void Occurable::addPointOfOrigin(SceneNode & node_of_origin)
    {
        origin_list.push_back(&node_of_origin);
    }
    
    //! Removes origin
    void Occurable::removePointOfOrigin(SceneNode & node_of_origin)
    {
        origin_list.remove(&node_of_origin);
    }
    
    //! @return Reference to orign list
    Occurable::OriginList & Occurable::getOriginList()
    {
        return origin_list;
    }
    
    //! @return Number of occurrences
    unsigned Occurable::getNumberOfOccurrences() const
    {
        return (unsigned)origin_list.size();
    }
}