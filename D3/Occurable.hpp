//
//  Occurable.hpp
//  D3
//
//  Created by Srđan Rašić on 10/8/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_Occurable_hpp
#define D3_Occurable_hpp

namespace d3 {    
    //! Occurable objects can apear on many
    //! places in scene, i.e. same instance is
    //! drawn multiple times
    class Occurable {
    public:
        typedef std::list<SceneNode *> OriginList;
        
    public:
        //! Virtual destructor
        virtual ~Occurable() {}
        
        //! Adds new node of origin (where object is to be rendered)
        virtual void addPointOfOrigin(SceneNode & node_of_origin);
        
        //! Removes origin
        virtual void removePointOfOrigin(SceneNode & node_of_origin);
        
        //! @return Reference to orign list
        virtual OriginList & getOriginList();
        
        //! @return Number of occurrences
        virtual unsigned getNumberOfOccurrences() const;
        
    protected:
        OriginList origin_list;
    };
}

#endif