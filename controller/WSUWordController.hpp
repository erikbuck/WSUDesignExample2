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

/// This class is part of the "Supervising Controller" within an overall \ref ModelViewPresenter Design Pattern.
/// This class creates an instance of the Model and serves as a clearing house for operations upon the Model. For example, use runCommandWithUndoRedoSupport() to run commands that mutate the Model in such a way that those mutations may be undone or redone at a later time. Similarly, use runScript() to run an entire script of commands that mutate the Model.
class WSUWordController {
private:
    /// An instance of the Model
    Model::StoredString::p_t m_storedString_p;
    
    /// \ref R2_0 \ref R2_2
    UndoManager m_undoManager;
    
public:
    typedef Model::StoredString::command_p_t command_p_t;
    
    WSUWordController();
    
    std::string getCurrentStoredStringValue();
    UndoManager& getUndoManager();             /// \ref R2_0 \ref R2_2
    
    /// \imp \ref R2_0 \ref R2_2 Use this function to execute commands that mutate the Model associated with this "Supervising Controller" in such a way that the commands may be undone or redone in the future.
    void runCommandWithUndoRedoSupport(command_p_t);
    
    /// \imp \ref R3_0 Use this function to run all of the commands in a human readable script so that the commands mutate the Model associated with this "Supervising Controller". Scripts are formatted as JSON describing a sequence of commands and the operands for those commands. Example:
    /// <p> <i>{"command": "insertCharacterAtIndex", "character": "a", "index\": 0} <br> {"command": "insertCharacterAtIndex", "character": "-", "index": 0} <br> {"command": "insertCharacterAtIndex", "character": "a", "index": 0} <br>  {"command": "removeCharacterAtIndex", "index": 1} </i></p>
    void runScript(std::string script);
    
    
    /// \imp \ref R3_1 This function is a Factory Method used to return Command instances that are preinitialized to operate upon the Model associated with this "Supervising Controller". This function simplifies the implementation of scripts execution by providing a mechanism to convert human readable script commands into executable commands for mutating the Model.
    command_p_t makeCommandWithName(std::string name, std::string args);
};

} // namespace Controller
} // namespace WSU

#endif /* CommandController_hpp */
