//
//  d3ArrayDescriptor.hpp
//  D3
//
//  Created by Srđan Rašić on 8/29/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3ArrayDescriptor_hpp
#define D3_d3ArrayDescriptor_hpp

namespace d3 {
    //! Encapsulate IVA array component
    template<class T>
    class d3ArrayDescriptor {
    protected:
        T * ptr_;
        int stride_;
        unsigned int size_;
        
    public:
        d3ArrayDescriptor(T *ptr, unsigned int size, int stride) : ptr_(ptr), size_(size), stride_(stride) {}
        
        //! Sets pointer to the first element
        void setPointer(T* data) { ptr_ = data; }
        
        //! @return Pointer to the first element
        T * getPointer() const { return ptr_; }
        
        //! Sets number of elements in array
        void setSize(unsigned int size) { size_ = size; }
        
        //! @return Number of elements
        unsigned int getSize() { return size_; }
        
        //! Sets stride
        void setStride(int stride) const { stride_ = stride; }
        
        //! @return Offset to each next element
        int getStride() const { return stride_; }
    };
}

#endif
