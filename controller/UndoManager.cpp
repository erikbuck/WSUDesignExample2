//
//  UndoManager.cpp
//  demo
//
//  Created by Erik M. Buck on 3/16/21.
//  Copyright © 2021 Erik M. Buck. All rights reserved.
//

#include "UndoManager.hpp"

namespace WSU {
namespace Controller {

void UndoManager::undo() {
    m_isUndoing = true;
    auto cmd_p = m_undoStack.back();
    m_undoStack.pop_back();
    runCommand(cmd_p);
    m_isUndoing = false;
}

void UndoManager::redo() {
    auto cmd_p = m_redoStack.back();
    m_redoStack.pop_back();
    runCommand(cmd_p);
}

void UndoManager::runCommand(Model::StoredString::Command::p_t cmd_p) {
    if(!m_isUndoing) {
        m_undoStack.push_back(cmd_p->makeReciprocalCommand());
    } else {
        m_redoStack.push_back(cmd_p->makeReciprocalCommand());
    }
    cmd_p->run();
}

} // namespace Controller
} // namespace WSU
