//
//  Movable.hpp
//  D3
//
//  Created by Srđan Rašić on 10/9/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_Movable_hpp
#define D3_Movable_hpp

namespace d3 {
    //! Represents movable object
    class Movable {
    public:
        //! Default constructor
        Movable(SceneNode & mover);
        
        //! Virtual destructor
        virtual ~Movable() {}
        
        //! Sets mover node
        void setMover(SceneNode & mover);
        
        //! @return Mover node
        SceneNode & getMover() const;
        
    protected:
        SceneNode * mover;
    };
}

#endif
