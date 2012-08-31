//
//  d3Image.h
//  D3
//
//  Created by Srđan Rašić on 8/30/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__d3Image__
#define __D3__d3Image__

#include "d3Types.hpp"
#include <assert.h>

namespace d3 {
    //! Image class.
    class d3Image {
    protected:
        // Basic image info
        d3Size width_;
        d3Size height_;
        d3PixelFormat pixel_format_;
        
        // Memory stuff
        d3Size num_of_channels_;
        d3Size depth_;
        
        // Image data
        unsigned char *data_;
        
    public:
#pragma mark Constructors        
        /*! Constructs d3Image from raw data.
         *  'data' must be of size (bytes): bytesPerRow * height * channel_count * depth
         */
        d3Image(unsigned char *data,            //!< Image data
                 d3Size depth,                  //!< Depth in bytes
                 d3Size width,                  //!< Width
                 d3Size height,                 //!< Height
                 d3PixelFormat pixel_format     //!< Pixel format
                 );
        
        //! Loads image from file.
        d3Image(const char* filename      //!> Image full path
                 );
        
        //! Destructor.
        ~d3Image();
        
#pragma mark Base methods
        //! @return Image width in pixels.
        d3Size getWidth() const;
        
        //! @return Image height in pixels.
        d3Size getHeight() const;
        
        //! @return Pixel format.
        d3PixelFormat getPixelFormat() const;
        
        //! @return Number od channels.
        d3Size getNumberOfChannels() const;
        
        //! @return Size of pixel's component in bytes.
        d3Size getDepth() const;
        
        //! @return Size of row in bytes.
        d3Size getBytesPerRow() const;
        
        //! @return Raw image data.
        unsigned char* getData();
        
        //! @return Pointer to specified pixel in 2D
        unsigned char* getPixel(d3Size x, d3Size y);
        
#pragma mark File manipulation methods
        //! Save image to disk.
        void saveToFile(const char* filename) const;
    };
    
#pragma mark Inline methods implementation
    inline d3Size d3Image::getWidth() const {
        return width_;
    }
    
    inline d3Size d3Image::getHeight() const {
        return height_;
    }
    
    inline d3PixelFormat d3Image::getPixelFormat() const {
        return pixel_format_;
    }
    
    inline d3Size d3Image::getNumberOfChannels() const {
        return num_of_channels_;
    }
    
    inline d3Size d3Image::getDepth() const {
        return depth_;
    }
    
    inline d3Size d3Image::getBytesPerRow() const {
        return getWidth() * getNumberOfChannels() * getDepth() * sizeof(unsigned char);
    }
    
    inline unsigned char* d3Image::getData() {
        return data_;
    }
    
    inline unsigned char* d3Image::getPixel(d3Size x, d3Size y) {
        assert(x < width_ && y < height_);
        return getData() + y * getBytesPerRow() + x * getNumberOfChannels() * getDepth();
    }
}
#endif
