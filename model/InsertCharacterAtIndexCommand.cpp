//
//  InsertCharacterCommand.cpp
//  
//
//  Created by Erik M. Buck on 2/25/21.
//

#include "InsertCharacterAtIndexCommand.hpp"
#include "RemoveCharacterAtIndexCommand.hpp"
#include "json11.hpp"
#include <functional>
#include <cassert>

namespace WSU {
namespace Model {

struct _InsertCharacterAtIndexCommandFactoryInstaller : public WSU::Model::Command::FactoryInstaller {
    static StoredString::command_p_t factory(StoredString::p_t storedString_p,
                                             std::string args) {
        auto parsedArgs = parse(args);
        StoredString::command_p_t result {nullptr};
        std::string err;
        if(!parsedArgs.has_shape({
            { "command", json11::Json::STRING },
            { "character", json11::Json::STRING },
            { "index", json11::Json::NUMBER },
        }, err)) {
        } else {
            assert(parsedArgs["command"].string_value() == InsertCharacterAtIndexCommand::name);
            assert(0 < parsedArgs["character"].string_value().size());
            const char c = parsedArgs["character"].string_value()[0];
            const size_t index = (size_t)parsedArgs["index"].int_value();
            
            result = StoredString::command_p_t(new InsertCharacterAtIndexCommand(storedString_p, c, index));
        }
        return result;
    }
    
    _InsertCharacterAtIndexCommandFactoryInstaller() {
        StoredString::registerCommandFactoryWithName(factory,
                                                     InsertCharacterAtIndexCommand::name);
    }
};

// Force registration of factory
_InsertCharacterAtIndexCommandFactoryInstaller insertCharacterAtIndexCommandInstaller;


InsertCharacterAtIndexCommand::InsertCharacterAtIndexCommand(StoredString::p_t s,
                                                             char c,
                                                             size_t storedStringIndex) :
StoredString::Command(s), m_characterToInsert(c), m_storedStringIndex(storedStringIndex) {
    // Intentionally empty
}

void InsertCharacterAtIndexCommand::run() {
    getStoredString()->insertCharacterAtIndex(m_characterToInsert, m_storedStringIndex);
}

Command::p_t InsertCharacterAtIndexCommand::makeReciprocalCommand()
{
    const json11::Json obj = json11::Json::object({
        { "command", std::string {WSU::Model::RemoveCharacterAtIndexCommand::name} },
        { "index", (int)m_storedStringIndex } });
    
    auto reciprocalCmd_p = WSU::Model::StoredString::makeCommandWithName(WSU::Model::RemoveCharacterAtIndexCommand::name, getStoredString(), obj.dump());
    return reciprocalCmd_p;
}

std::string InsertCharacterAtIndexCommand::getStringRepresentation()
{
    const json11::Json obj = json11::Json::object({
        { "command", std::string {InsertCharacterAtIndexCommand::name} },
        { "character", std::string {m_characterToInsert} },
        { "index", (int)m_storedStringIndex } });
    return obj.dump();
}

} // namespace Model
} // namespace WSU
