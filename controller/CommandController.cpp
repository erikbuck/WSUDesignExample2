//
//  CommandController.cpp
//  demo
//
//  Created by Erik M. Buck on 3/16/21.
//  Copyright © 2021 Erik M. Buck. All rights reserved.
//

#include "CommandController.hpp"

namespace WSU {
namespace Model {

CommandController::CommandController() {
    m_storedString_p = StoredString::p_t(new StoredString);
}

void CommandController::runScript(std::string script) {
    std::string::size_type parser_stop_pos {0};
    std::string err;
    auto commandsJSON = json11::Json::parse_multi(script, parser_stop_pos, err);
    for(auto singleCommandJSON : commandsJSON) {
        auto commandName = singleCommandJSON["command"];
        auto command = StoredString::makeCommandWithName(commandName.string_value(),
                                          m_storedString_p, singleCommandJSON.dump());
        command->run();
    }
}

std::string CommandController::getCurrentStoredStringValue() {
    return m_storedString_p->getString();
}

} // namespace Model
} // namespace WSU
