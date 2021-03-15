//
//  Command.cpp
//  
//
//  Created by Erik M. Buck on 2/24/21.
//

#include "Command.hpp"
#include <sstream>
#include <vector>

namespace WSU {
namespace Model {

Command::FactoryInstaller::arguments_t Command::FactoryInstaller::parse(const std::string& args) {
    Command::FactoryInstaller::arguments_t result;
    std::string err;
    result = json11::Json::parse(args, err);
    return result;
}

} // namespace Model
} // namespace WSU
