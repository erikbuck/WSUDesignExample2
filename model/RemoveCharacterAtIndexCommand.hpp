//
//  RemoveCharacterAtIndexCommand.hpp
//
//  Created by Erik M. Buck on 3/12/21.
//

#ifndef RemoveCharacterAtIndexCommand_hpp
#define RemoveCharacterAtIndexCommand_hpp


#include "Command.hpp"
#include "StoredString.hpp"
#include <memory>
#include <cstdint>

namespace WSU {
namespace Model {

/// \imp \ref 1_4 The mechanism for removing a character at an index in the stored string is to run() and instance of this class.
class RemoveCharacterAtIndexCommand : public StoredString::Command {
public:
    //typedef typename WSU::Model::Command::p_t p_t;
    
private:
    size_t m_storedStringIndex;
    
public:
    static constexpr const char* name { "removeCharacterAtIndex" };
    
    /// \param[in] storedStringIndex \imp \ref R1_4
    RemoveCharacterAtIndexCommand(StoredString::p_t s, size_t storedStringIndex);
    
    virtual void run();
    virtual p_t makeReciprocalCommand();
    virtual std::string getStringRepresentation();
};

} // namespace Model
} // namespace WSU

#endif /* RemoveCharacterAtIndexCommand_hpp */
