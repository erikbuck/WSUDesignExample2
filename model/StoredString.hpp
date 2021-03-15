//
//  StoredString.hpp
//  
//
//  Created by Erik M. Buck on 2/23/21.
//

#ifndef WSUWord_hpp
#define WSUWord_hpp

#include "Command.hpp"
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <cstdint>

/// This entire project is part of a demonstration for Wright State University (WSU) CSE-4110 "Intro. Software Eng." Spring 2021.
namespace WSU {

/// Model Model Subsystem
///
/// This Module contains components that are part of the @ref Model within the overall @ref ModelViewPresenter Design.
namespace Model {

/// \imp \ref R1_0 This class implements the core of the Model subsystem with methods to manipulate a stored string.
class StoredString {
private:
    /// \imp \ref R1_0
    /// \imp \ref R1_1
    std::string m_string;
    
public:
    typedef std::shared_ptr<StoredString> p_t;
    
    /// \imp \ref R1_2
    void appendCharacter(char c);
    
    /// \imp \ref R1_3
    /// \imp \ref R1_3_1 The character, c, is inserted into the stored string at index.
    /// \imp \ref R1_3_2  All characters already in the at index and beyond are moved to the next index to make room for c.
    void insertCharacterAtIndex(char c, size_t index);
    
    /// \imp \ref R1_4
    /// \imp \ref R1_4_1
    /// \imp \ref R1_4_2
    void removeCharacterAtIndex(size_t index);
    
    /// \imp \ref R1_5
    /// \imp \ref R1_5_1
    /// \imp \ref R1_5_2
    void insertStringAtIndex(std::string s, size_t index);
    
    std::string getString() const;
    
    /// This is an abstract base class for Commands that operate upon Stored String instances.
    class Command : public WSU::Model::Command {
    private:
        StoredString::p_t m_storedString_p;
        
    public:
        typedef typename WSU::Model::Command::p_t p_t;

        Command(StoredString::p_t storedString_p);
        
        StoredString::p_t getStoredString() const;
    };
    
    typedef typename WSU::Model::Command::p_t command_p_t;
    
    /// Type for Factory Methods. Having a standard type simplifies use of [Factory Methods](https://en.wikipedia.org/wiki/Factory_method_pattern) because the caller need not know any details (like special arguments) about the object(s) created by the Factory Method.
    typedef std::function<command_p_t (p_t storedString_p,
                                       std::string args)> commandFactory_t;
    
private:
    typedef std::unordered_map<std::string, StoredString::commandFactory_t> factoryMap_t;
    
    /// \imp \ref R3_1 In order to recognize commands by their names in a script, it is necessary to be able to lookup commands by name. This function returns a map from name to a Factory that creates instances of the command with that name. See [Factory Design Pattern](https://www.oodesign.com/factory-pattern.html)
    static factoryMap_t& getNameToFactoryMap();
    
public:
    /// \imp \ref R3_1 In order to recognize commands by their names in a script, it is necessary to be able to lookup commands by name. This method provides a mechanism to associate a command Factory with the name of the command. A command Factory Method is an implantation of the [Factory Method Design Pattern](https://en.wikipedia.org/wiki/Factory_method_pattern).
    static void registerCommandFactoryWithName(commandFactory_t, std::string name);
    
    /// \imp \ref R3_1 Create a Command instance using the named Factory, stored string, and arguments. The name is a human readable identifier that may be used in scripts. The arguments are [JSON](https://www.json.org/json-en.html) formatted key/value pairs where each key is a string argument name and each value is a JSON value type.
    /// \ref R3_1_1 As an implementation detail, JSON is chosen as a human readable format .
    static command_p_t makeCommandWithName(std::string name,
                                           p_t storedString_p,
                                           std::string args);
};


} // namespace Model
} // namespace WSU

#endif /* WSUWord_hpp */
