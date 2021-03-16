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
#include "UndoManager.hpp"
#include <string>

namespace WSU {
namespace Controller {

class WSUWordController {
private:
    Model::StoredString::p_t m_storedString_p;
    UndoManager m_undoManager;
    
public:
    typedef Model::StoredString::command_p_t command_p_t;
    
    WSUWordController();
    
    UndoManager& getUndoManager();
    void runCommandWithUndoRedoSupport(command_p_t);
    
    void runScript(std::string script);
    std::string getCurrentStoredStringValue();
    
    command_p_t makeCommandWithName(std::string name,
                                           std::string args);
};

} // namespace Controller
} // namespace WSU

#endif /* CommandController_hpp */
