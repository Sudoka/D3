//
//  Device.hpp
//  D3
//
//  Created by Srđan Rašić on 10/5/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_Device_hpp
#define D3_Device_hpp

namespace d3 {
    class Device {
    protected:
        
    public:
        //! Virtual destructor
        virtual ~Device() {}
        
        //! @return Currently bound program
        virtual Program * getCurrentProgram() =0;
    };
}

#endif
