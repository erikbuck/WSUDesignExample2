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
    
    std::string getCurrentStoredStringValue();
    UndoManager& getUndoManager();
    
    /// \imp \ref R2_0 \ref R2_2
    void runCommandWithUndoRedoSupport(command_p_t);
    
    /// \imp \ref R3_0
    void runScript(std::string script);
    
    
    /// \imp \ref R3_1 This function is a Factory Method used to return Command isntances that are preinitialized to operate upon the stored string encapsulated by the WSUWordController
    command_p_t makeCommandWithName(std::string name, std::string args);
};

} // namespace Controller
} // namespace WSU

#endif /* CommandController_hpp */
