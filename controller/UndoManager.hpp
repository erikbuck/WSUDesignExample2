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

class UndoManager {
private:
    std::vector<Model::StoredString::Command::p_t> m_undoStack;
    std::vector<Model::StoredString::Command::p_t> m_redoStack;
    bool m_isUndoing {false};

public:
    void undo();
    void redo();
    void runCommand(Model::StoredString::Command::p_t);
};

} // namespace Controller
} // namespace WSU

#endif /* UndoManager_hpp */
