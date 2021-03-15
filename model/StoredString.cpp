//
//  StoredString.cpp
//  
//
//  Created by Erik M. Buck on 2/23/21.
//

#include "StoredString.hpp"
#include <cassert>

namespace WSU {
namespace Model {

void StoredString::appendCharacter(char c) {
    m_string = m_string + c;
}

void StoredString::insertCharacterAtIndex(char c, size_t index) {
    m_string.insert(index, 1, c);
}

void StoredString::removeCharacterAtIndex(size_t index) {
    m_string.erase(index, 1);
}

void StoredString::insertStringAtIndex(std::string s, size_t index)
{
    m_string.insert(index, s);
}

std::string StoredString::getString() const {
    return m_string;
}

StoredString::Command::Command(StoredString::p_t storedString_p) {
    assert(nullptr != storedString_p);
    m_storedString_p = storedString_p;
}

StoredString::p_t StoredString::Command::getStoredString() const {
    return m_storedString_p;
}

StoredString::factoryMap_t& StoredString::getNameToFactoryMap() {
    static StoredString::factoryMap_t nameToFactoryMap;
    
    return nameToFactoryMap;
}


void StoredString::registerCommandFactoryWithName(commandFactory_t factory,
                                                  std::string name) {
    getNameToFactoryMap().insert( {name, factory} );
    assert(getNameToFactoryMap().end() != getNameToFactoryMap().find(name));
}

/// \imp \ref R3_1 This is a Factory Method that must be overridden in subclasses
StoredString::command_p_t StoredString::makeCommandWithName(std::string name,
                                               p_t storedString_p,
                                               std::string args) {
    StoredString::command_p_t result { nullptr };
    auto factoryIt = getNameToFactoryMap().find(name);
    if(getNameToFactoryMap().end() != factoryIt) {
        auto factory = factoryIt->second;
        if(nullptr != factory) {
            result = factory(storedString_p, args);
        }
    }
    return result;
}

} // namespace Model
} // namespace WSU
