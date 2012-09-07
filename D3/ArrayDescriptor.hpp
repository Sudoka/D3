//
//  ArrayDescriptor.hpp
//  
//
//  Created by Srđan Rašić on 8/29/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _ArrayDescriptor_hpp
#define _ArrayDescriptor_hpp

namespace d3 {
    //! Encapsulate IVA array component
    template<class T>
    class ArrayDescriptor {
    protected:
        T * ptr_;
        int stride_;
        unsigned int size_;
        
    public:
        ArrayDescriptor(T *ptr, unsigned int size, int stride) : ptr_(ptr), size_(size), stride_(stride) {}
        
        SETGET(T *, ptr_, Pointer)
        SETGET(unsigned int, size_, Size)
        SETGET(int, stride_, Stride)
    };
}

#endif
