//
//  WSURemoveCharacterAtIndexCommandTest.cpp
//
//  Created by Erik M. Buck on 3/12/21.
//

#include <gtest/gtest.h>
#include "RemoveCharacterAtIndexCommand.hpp"

/// \ref 1_4  A Command is a echanism for removing a character at an index
/// \ref 3_1_1 The string representation of a Command is human readable
TEST(RemoveCharacterAtIndexCommand, getStringRepresentation) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    storedString_p->appendCharacter('$');
    storedString_p->appendCharacter('#');
    storedString_p->appendCharacter('!');
    EXPECT_EQ("$#!", storedString_p->getString());
    
    WSU::Model::RemoveCharacterAtIndexCommand cmd0 {storedString_p, 0 };
    EXPECT_EQ("{\"command\": \"removeCharacterAtIndex\", \"index\": 0}", cmd0.getStringRepresentation());
    cmd0.run();
    EXPECT_EQ("#!", storedString_p->getString());
    cmd0.run();
    EXPECT_EQ("!", storedString_p->getString());
}

/// \ref 1_4  A Command is a mechanism for removing a character at an index
/// \ref 3_1_1 Command names are human readable
TEST(RemoveCharacterAtIndexCommand, makeCommandWithName) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    storedString_p->appendCharacter('$');
    storedString_p->appendCharacter('#');
    storedString_p->appendCharacter('!');
    EXPECT_EQ("$#!", storedString_p->getString());

    const json11::Json obj = json11::Json::object({
        { "command", std::string {WSU::Model::RemoveCharacterAtIndexCommand::name} },
        { "index", 0 } });
    
    auto cmd_p = WSU::Model::StoredString::makeCommandWithName(WSU::Model::RemoveCharacterAtIndexCommand::name, storedString_p, obj.dump());
    if(nullptr != cmd_p) {
        cmd_p->run();
    }
    EXPECT_EQ("#!", storedString_p->getString());
}

/// \ref R2_0 In order undo a command, a reciprocal command is needed
TEST(RemoveCharacterAtIndexCommand, reciprocal0) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    storedString_p->appendCharacter('$');
    storedString_p->appendCharacter('#');
    storedString_p->appendCharacter('!');
    EXPECT_EQ("$#!", storedString_p->getString());

    const json11::Json obj = json11::Json::object({
        { "command", std::string {WSU::Model::RemoveCharacterAtIndexCommand::name} },
        { "index", 0 } });
    
    auto cmd_p = WSU::Model::StoredString::makeCommandWithName(WSU::Model::RemoveCharacterAtIndexCommand::name, storedString_p, obj.dump());
    auto reciprocalCmd_p = cmd_p->makeReciprocalCommand();
    ASSERT_TRUE(nullptr !=  cmd_p);
    cmd_p->run();
    
    EXPECT_EQ("#!", storedString_p->getString());

    ASSERT_TRUE(nullptr != reciprocalCmd_p);
    reciprocalCmd_p->run();
    EXPECT_EQ("$#!", storedString_p->getString());
}

/// \ref R2_0 In order undo a command, a reciprocal command is needed
TEST(RemoveCharacterAtIndexCommand, reciprocal1) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    storedString_p->appendCharacter('$');
    storedString_p->appendCharacter('#');
    storedString_p->appendCharacter('!');
    EXPECT_EQ("$#!", storedString_p->getString());

    const json11::Json obj = json11::Json::object({
        { "command", std::string {WSU::Model::RemoveCharacterAtIndexCommand::name} },
        { "index", 1 } });
    
    auto cmd_p = WSU::Model::StoredString::makeCommandWithName(WSU::Model::RemoveCharacterAtIndexCommand::name, storedString_p, obj.dump());
    auto reciprocalCmd_p = cmd_p->makeReciprocalCommand();
    ASSERT_TRUE(nullptr !=  cmd_p);
    cmd_p->run();
    
    EXPECT_EQ("$!", storedString_p->getString());

    ASSERT_TRUE(nullptr != reciprocalCmd_p);
    reciprocalCmd_p->run();
    EXPECT_EQ("$#!", storedString_p->getString());
}

/// \ref R2_0 In order undo a command, a reciprocal command is needed
TEST(RemoveCharacterAtIndexCommand, reciprocal2) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    storedString_p->appendCharacter('$');
    storedString_p->appendCharacter('#');
    storedString_p->appendCharacter('!');
    EXPECT_EQ("$#!", storedString_p->getString());

    const json11::Json obj = json11::Json::object({
        { "command", std::string {WSU::Model::RemoveCharacterAtIndexCommand::name} },
        { "index", 2 } });
    
    auto cmd_p = WSU::Model::StoredString::makeCommandWithName(WSU::Model::RemoveCharacterAtIndexCommand::name, storedString_p, obj.dump());
    auto reciprocalCmd_p = cmd_p->makeReciprocalCommand();
    ASSERT_TRUE(nullptr !=  cmd_p);
    cmd_p->run();
    
    EXPECT_EQ("$#", storedString_p->getString());

    ASSERT_TRUE(nullptr != reciprocalCmd_p);
    reciprocalCmd_p->run();
    EXPECT_EQ("$#!", storedString_p->getString());
}
