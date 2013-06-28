//
//  Image.cpp
//  
//
//  Created by Srđan Rašić on 8/30/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Image.hpp"
#include <png.h>
#include <stdio.h>
#include <assert.h>


namespace d3 {
    Image::Image(unsigned char *data,
                     Size depth,
                     Size width,
                     Size height,
                     PixelFormat pixel_format)
    : width_(width), height_(height), depth_(depth), pixel_format_(pixel_format)
    {
        // set number of channels
        switch (pixel_format) {
            case D3_GREY:
                num_of_channels_ = 1;
                break;
            case D3_RGB:
                num_of_channels_ = 3;
                break;
            case D3_RGBA:
                num_of_channels_ = 4;
                break;
            default:
                break;
        }
        
        // Set bytesPerRow
        
        data_ = data;
    }
    
    Image::~Image()
    {
        delete data_;
    }
    
    Image::Image(String filename) {
        // Loads only PNG for now
        png_byte color_type;
        png_byte bit_depth;
        
        png_structp png_ptr;
        png_infop info_ptr;
        int number_of_passes;
        
        char header[8];
        DEBUG_PRINT(filename)
        // Open file.
        FILE *fp = fopen(filename.c_str(), "rb");
        assert(fp);
        
        // Test if PNG.
        fread(header, 1, 8, fp);
        //assert(png_sig_cmp(header, 0, 8));
        
        // Initialization
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        assert(png_ptr);
        
        info_ptr = png_create_info_struct(png_ptr);
        assert(info_ptr);
        
        setjmp(png_jmpbuf(png_ptr));
        
        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);
        
        png_read_info(png_ptr, info_ptr);
        
        width_ = png_get_image_width(png_ptr, info_ptr);
        height_ = png_get_image_height(png_ptr, info_ptr);
        
        color_type = png_get_color_type(png_ptr, info_ptr);
        bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        
        switch (color_type) {
            case PNG_COLOR_TYPE_RGB:
                pixel_format_ = D3_RGB;
                num_of_channels_ = 3;
                break;
            case PNG_COLOR_TYPE_RGB_ALPHA:
                pixel_format_ = D3_RGBA;
                num_of_channels_ = 4;
                break;
            case PNG_COLOR_TYPE_GRAY:
                pixel_format_ = D3_GREY;
                num_of_channels_ = 1;
                break;
        }
        
        // Translate color type and bit depth
        depth_ = bit_depth / 8;
        
        number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);
        
        // Read file.
        setjmp(png_jmpbuf(png_ptr));
        
        data_ = new unsigned char[getBytesPerRow() * height_];
        
        png_bytep *row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height_);
        for (Size y = 0; y < height_; y++)
            row_pointers[y] = (data_ + y * getBytesPerRow());
        
        png_read_image(png_ptr, row_pointers);
        
        free(row_pointers);
        fclose(fp);
    }
    
    void Image::saveToFile(const char* filename) const {
        png_byte color_type;
        
        switch (getPixelFormat()) {
            case D3_GREY:
                color_type = PNG_COLOR_TYPE_GRAY;
                break;
            case D3_RGB:
                color_type = PNG_COLOR_TYPE_RGB;
                break;
            case D3_RGBA:
                color_type = PNG_COLOR_TYPE_RGB_ALPHA;
                break;
        }
        
        png_structp png_ptr;
        png_infop info_ptr;
        
        // Read
        FILE *fp = fopen(filename, "wb");
        assert(fp);
        
        // Initialize
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        assert(png_ptr);
        
        info_ptr = png_create_info_struct(png_ptr);
        assert(info_ptr);
        
        setjmp(png_jmpbuf(png_ptr));
        png_init_io(png_ptr, fp);
        
        // Write header
        setjmp(png_jmpbuf(png_ptr));
        
        png_set_IHDR(png_ptr, info_ptr, getWidth(), getHeight(),
                     getDepth() * 8, color_type, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
        
        png_write_info(png_ptr, info_ptr);
        
        
        // Write bytes
        setjmp(png_jmpbuf(png_ptr));
        
        png_bytep *row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height_);
        for (Size y = 0; y < height_; y++)
            row_pointers[y] = (data_ + y * getBytesPerRow());
        
        png_write_image(png_ptr, row_pointers);
        
        
        // End write
        setjmp(png_jmpbuf(png_ptr));
        png_write_end(png_ptr, NULL);
        
        free(row_pointers);
        
        fclose(fp);
    }
}
