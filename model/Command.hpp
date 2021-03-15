//
//  Command.hpp
//  
//
//  Created by Erik M. Buck on 2/24/21.
//

#ifndef Command_hpp
#define Command_hpp

#include "json11.hpp"
#include <memory>
#include <functional>

namespace WSU {
namespace Model {

/// This class is an "interface" for Commands within the [Command Design Pattern](https://en.wikipedia.org/wiki/Command_pattern) "In object-oriented programming, the command pattern is a behavioral design pattern in which an object is used to encapsulate all information needed to perform an action or trigger an event at a later time. This information includes the method name, the object that owns the method and values for the method parameters." -wikipedia
/// \imp \ref R2_0 In order to undo an operation (a.k.a. action), it is necessary to execute the reciprocal of the undoable operation at a later time when the user chooses to undo.
class Command {
public:
    typedef std::shared_ptr<Command> p_t;
    
protected:
    
    /// \anchor DR_1_0 \dreq Derived 2.0:  In C++, all classes that have one or more virtual method are required to have a virtual destructor.
    virtual ~Command() { /* Intentionally Empty */ }
    
public:
    /// This class exists to install a Command factories associated with names so that Command instances may be created by looking up named factories and using the factories to create the Command instances. See [Factory Design Pattern](https://www.oodesign.com/factory-pattern.html).
    /// \ref R3_1_1 Scripts contain human readable command names. The names may be used to lookup installed factories, and then the factories may be used to create instances of the named Commands.
    class FactoryInstaller {
    protected:
        /// \ref R3_1_1 As an implementation detail, [JavaScript Object Notation (JSON)](https://www.json.org/json-en.html)  is chosen as a human readable format .
        typedef json11::Json arguments_t;
        /// Commands encapsulate the information needed to run the command at a later time. This method  must be implemented in all subclasses of those class to encapsulate (that is store) needed information.
        /// \param args \imp \ref R3_1_1 A script needs to be human readable. That implies the arguments to a command are human readable too. The args parameter is intended to contain a human readable string of command arguments such as the argument that may be present in a script.
        /// \return true iff args are successful parsed and encapsulated. Return false otherwise.
        static arguments_t parse(const std::string& args);
    };
    
    /// \imp \ref R2_0 To do, undo, or redo and operation, it is necessary to "run" the operation.
    virtual void run() = 0;
    
    /// C++ has a well established idiom know as [Functors](https://www.geeksforgeeks.org/functors-in-cpp). Functors are a C++ language level implementation of the Command Design Pattern particularly when combined with C++11 std::bind and std::function. Providing this operator makes it seamless to use this class as a Functor along with std::bind and std::function.
    /// \anchor DR_1_0 \dreq Derived 1.0: Any implementation of a Design Pattern should incorporate related language idioms as a matter of courtesy for other practitioners of the language.
    void operator() () { run(); }
    
    /// \imp \ref R2_0 In order to be able to undo a command, the reciprocal of the command is needed.
    /// \imp \ref R2_2 In order to redo an undo command, the reciprocal of the command executed as part of undo is needed.
    virtual p_t makeReciprocalCommand() = 0;
    
    /// \imp \ref R3_0 In order to create a script of commands, it is necessary to have string representations of the commands
    /// \imp \ref R3_1 A script will consist of a sequence of commands identified by their string representations
    /// \imp \ref R3_1_1 String representations are human readable
    virtual std::string getStringRepresentation() = 0;
};

} // namespace Model
} // namespace WSU

#endif /* Command_hpp */
