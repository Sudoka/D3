//
//  Image.h
//  
//
//  Created by Srđan Rašić on 8/30/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef ____Image__
#define ____Image__

#include "Types.hpp"
#include <assert.h>

namespace d3 {
    //! Image class.
    class Image {
    protected:
        // Basic image info
        Size width_;
        Size height_;
        PixelFormat pixel_format_;
        
        // Memory stuff
        Size num_of_channels_;
        Size depth_;
        
        // Image data
        unsigned char *data_;
        
    public:
#pragma mark Constructors        
        /*! Constructs Image from raw data.
         *  'data' must be of size (bytes): bytesPerRow * height * channel_count * depth
         */
        Image(unsigned char *data,            //!< Image data
                 Size depth,                  //!< Depth in bytes
                 Size width,                  //!< Width
                 Size height,                 //!< Height
                 PixelFormat pixel_format     //!< Pixel format
                 );
        
        //! Loads image from file.
        Image(const char* filename      //!> Image full path
                 );
        
        //! Destructor.
        ~Image();
        
#pragma mark Base methods
        //! @return Image width in pixels.
        Size getWidth() const;
        
        //! @return Image height in pixels.
        Size getHeight() const;
        
        //! @return Pixel format.
        PixelFormat getPixelFormat() const;
        
        //! @return Number od channels.
        Size getNumberOfChannels() const;
        
        //! @return Size of pixel's component in bytes.
        Size getDepth() const;
        
        //! @return Size of row in bytes.
        Size getBytesPerRow() const;
        
        //! @return Raw image data.
        unsigned char* getData();
        
        //! @return Pointer to specified pixel in 2D
        unsigned char* getPixel(Size x, Size y);
        
#pragma mark File manipulation methods
        //! Save image to disk.
        void saveToFile(const char* filename) const;
    };
    
#pragma mark Inline methods implementation
    inline Size Image::getWidth() const {
        return width_;
    }
    
    inline Size Image::getHeight() const {
        return height_;
    }
    
    inline PixelFormat Image::getPixelFormat() const {
        return pixel_format_;
    }
    
    inline Size Image::getNumberOfChannels() const {
        return num_of_channels_;
    }
    
    inline Size Image::getDepth() const {
        return depth_;
    }
    
    inline Size Image::getBytesPerRow() const {
        return getWidth() * getNumberOfChannels() * getDepth() * sizeof(unsigned char);
    }
    
    inline unsigned char* Image::getData() {
        return data_;
    }
    
    inline unsigned char* Image::getPixel(Size x, Size y) {
        assert(x < width_ && y < height_);
        return getData() + y * getBytesPerRow() + x * getNumberOfChannels() * getDepth();
    }
}
#endif
