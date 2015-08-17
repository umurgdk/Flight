//
//  SimpleLevel.h
//  Flight
//
//  Created by Umur Gedik on 17/08/15.
//
//

#ifndef __Flight__SimpleLevel__
#define __Flight__SimpleLevel__

#include <string>
#include "entityx/entityx.h"

class SimpleLevel : public entityx::EntityX {
public:
    explicit SimpleLevel(std::string filename) {
    }
};

#endif /* defined(__Flight__SimpleLevel__) */
