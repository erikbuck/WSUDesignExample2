//
//  CommandController.cpp
//  demo
//
//  Created by Erik M. Buck on 3/16/21.
//  Copyright © 2021 Erik M. Buck. All rights reserved.
//

#include "WSUWordController.hpp"

namespace WSU {
namespace Controller {

WSUWordController::WSUWordController() {
    m_storedString_p = Model::StoredString::p_t(new Model::StoredString);
}

UndoManager& WSUWordController::getUndoManager() {
    return m_undoManager;
}

void WSUWordController::runCommandWithUndoRedoSupport(command_p_t cmd_p) {
    getUndoManager().runCommand(cmd_p);
}

void WSUWordController::runScript(std::string script) {
    std::string::size_type parser_stop_pos {0};
    std::string err;
    auto commandsJSON = json11::Json::parse_multi(script, parser_stop_pos, err);
    for(auto singleCommandJSON : commandsJSON) {
        auto commandName = singleCommandJSON["command"];
        auto command = makeCommandWithName(commandName.string_value(), singleCommandJSON.dump());
        command->run();
    }
}

std::string WSUWordController::getCurrentStoredStringValue() {
    return m_storedString_p->getString();
}

WSUWordController::command_p_t WSUWordController::makeCommandWithName(std::string name,
                                                                        std::string args) {
    return WSU::Model::StoredString::makeCommandWithName(name,
                                                         m_storedString_p, args);
    
}

} // namespace Controller
} // namespace WSU
