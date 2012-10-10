//
//  FileIO.hpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _FileIO_hpp
#define _FileIO_hpp

#include "Types.hpp"

namespace d3 {
    class FileIO {
    public:
        //! Loads whole file content as string
        static String loadString(String path);
    };
}

#endif
