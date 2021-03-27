//
//  UndoManager.hpp
//  demo
//
//  Created by Erik M. Buck on 3/16/21.
//  Copyright © 2021 Erik M. Buck. All rights reserved.
//

#ifndef UndoManager_hpp
#define UndoManager_hpp

#include "StoredString.hpp"
#include <vector>

namespace WSU {
namespace Controller {

/// \ref R2_0 This class provides a mechanism for undo of previously performed commands
/// \ref R2_2 This class provides a mechanism for redo of previously undone commands
class UndoManager {
private:
    /// \ref R2_1 Use a vector as a stack of commands
    std::vector<Model::StoredString::Command::p_t> m_undoStack;
    
    /// \ref R3_1 Use a vector as a stack of commands
    std::vector<Model::StoredString::Command::p_t> m_redoStack;
    
    /// \ref R2_2 Variable is used to detect when a command is run as result of an undo so a reciprocal command is pushed onto the redo stack.
    bool m_isUndoing {false};

public:
    /// \ref 2_0
    void undo();
    
    /// \ref 3_0
    void redo();
    
    /// \ref R2_4 \ref R2_3 \ref R2_2 This function pushes a reciprocal of cmd_p onto an undo or redo stack based on whether the function is called in the midst of an undo operation or not.
    void runCommand(Model::StoredString::Command::p_t cmd_p);
};

} // namespace Controller
} // namespace WSU

#endif /* UndoManager_hpp */
