//
//  CommandController.hpp
//  demo
//
//  Created by Erik M. Buck on 3/16/21.
//  Copyright © 2021 Erik M. Buck. All rights reserved.
//

#ifndef CommandController_hpp
#define CommandController_hpp

#include "StoredString.hpp"
#include <string>

namespace WSU {
namespace Model {

class CommandController {
private:
    StoredString::p_t m_storedString_p;
    
public:
    CommandController();
    
    void runScript(std::string script);
    std::string getCurrentStoredStringValue();
};

} // namespace Model
} // namespace WSU

#endif /* CommandController_hpp */
