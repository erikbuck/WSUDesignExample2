//
//  RemoveCharacterAtIndexCommand.cpp
//
//  Created by Erik M. Buck on 3/12/21.
//

#include "RemoveCharacterAtIndexCommand.hpp"
#include "InsertCharacterAtIndexCommand.hpp"

namespace WSU {
namespace Model {

/// This class exists to install a Factory for RemoveCharacterAtIndexCommand commands. See WSU::Model::Command::FactoryInstaller for related design information.
struct _RemoveCharacterAtIndexCommandFactoryInstaller : public WSU::Model::Command::FactoryInstaller {
    
    /// This is the actual Factory Method that produces new instances of RemoveCharacterAtIndexCommand
    static StoredString::command_p_t factory(StoredString::p_t storedString_p,
                                             std::string args) {
        auto parsedArgs = parse(args);
        StoredString::command_p_t result {nullptr};
        std::string err;
        if(!parsedArgs.has_shape({
            { "command", json11::Json::STRING },
            { "index", json11::Json::NUMBER },
        }, err)) {
        } else {
            assert(parsedArgs["command"].string_value() == RemoveCharacterAtIndexCommand::name);
            const size_t index = (size_t)parsedArgs["index"].int_value();
            
            result = StoredString::command_p_t(new RemoveCharacterAtIndexCommand(storedString_p, index));
        }
        return result;
    }
    
    /// This constructor registers factory with StoredString's collection of named factories. See WSU::Model::Command::FactoryInstaller for related design information.
    _RemoveCharacterAtIndexCommandFactoryInstaller() {
        StoredString::registerCommandFactoryWithName(factory,
                                                     RemoveCharacterAtIndexCommand::name);
    }
};

// Force registration of factory: C++ calls constructor before main()
_RemoveCharacterAtIndexCommandFactoryInstaller removeCharacterAtIndexCommandInstaller;


RemoveCharacterAtIndexCommand::RemoveCharacterAtIndexCommand(StoredString::p_t s,
                                                             size_t storedStringIndex) :
StoredString::Command(s), m_storedStringIndex(storedStringIndex) {
    // Intentionally empty
}

void RemoveCharacterAtIndexCommand::run() {
    getStoredString()->removeCharacterAtIndex(m_storedStringIndex);
}

Command::p_t RemoveCharacterAtIndexCommand::makeReciprocalCommand()
{
    const json11::Json obj = json11::Json::object({
        { "command", std::string {WSU::Model::InsertCharacterAtIndexCommand::name} },
        { "character", std::string {getStoredString()->getString()[m_storedStringIndex]} },
        { "index", (int)m_storedStringIndex } });
    
    auto reciprocalCmd_p = WSU::Model::StoredString::makeCommandWithName(WSU::Model::InsertCharacterAtIndexCommand::name, getStoredString(), obj.dump());
    return reciprocalCmd_p;
}

std::string RemoveCharacterAtIndexCommand::getStringRepresentation()
{
    const json11::Json obj = json11::Json::object({
        { "command", std::string {RemoveCharacterAtIndexCommand::name} },
        { "index", (int)m_storedStringIndex } });
    return obj.dump();
}

} // namespace Model
} // namespace WSU
