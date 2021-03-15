//
//  InsertCharacterCommand.hpp
//  
//
//  Created by Erik M. Buck on 2/25/21.
//

#ifndef InsertCharacterCommand_hpp
#define InsertCharacterCommand_hpp

#include "Command.hpp"
#include "StoredString.hpp"
#include <memory>
#include <cstdint>

namespace WSU {
namespace Model {

/// \imp \ref R1_3 The mechanism for inserting a character at an index in the stored string is to run() and instance of this class.
class InsertCharacterAtIndexCommand : public StoredString::Command {
public:
    //typedef typename WSU::Model::Command::p_t p_t;
    
private:
    char m_characterToInsert;
    size_t m_storedStringIndex;
    
public:
    static constexpr const char* name { "insertCharacterAtIndex" };
    
    /// \param[in] c \imp \ref R1_3 the character to insert
    /// \param[in] storedStringIndex \imp \ref R1_3
    InsertCharacterAtIndexCommand(StoredString::p_t s, char c, size_t storedStringIndex);
    
    virtual void run();
    virtual p_t makeReciprocalCommand();
    virtual std::string getStringRepresentation();
};

} // namespace Model
} // namespace WSU

#endif /* InsertCharacterCommand_hpp */
