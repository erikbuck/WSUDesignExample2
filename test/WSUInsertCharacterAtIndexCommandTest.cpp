//
//  WSUInsertCharacterAtIndexCommandTest.cpp
//
//  Created by Erik M. Buck on 3/11/21.
//
#include <gtest/gtest.h>
#include "InsertCharacterAtIndexCommand.hpp"

/// \ref R1_3
/// \ref 3_1_1 The string representation of a Command is human readable
TEST(InsertCharacterAtIndexCommand, getStringRepresentation) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    EXPECT_EQ("", storedString_p->getString());
    WSU::Model::InsertCharacterAtIndexCommand cmd0 {storedString_p, '-', 0 };
    EXPECT_EQ("{\"character\": \"-\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}", cmd0.getStringRepresentation());
    cmd0.run();
    EXPECT_EQ("-", storedString_p->getString());
    cmd0.run();
    EXPECT_EQ("--", storedString_p->getString());
}

/// \ref 3_1 Multiple commands form a sequence of operations considered a "script".
TEST(InsertCharacterAtIndexCommand, multipleCommands0) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    EXPECT_EQ("", storedString_p->getString());
    
    std::vector<WSU::Model::InsertCharacterAtIndexCommand> commands {
        {storedString_p, 'A', 0 },
        {storedString_p, 'B', 0 },
        {storedString_p, 'C', 0 },
    };
    for(auto cmd : commands) {
        cmd.run();
    }
    EXPECT_EQ("CBA", storedString_p->getString());
}

/// \ref 3_1 Multiple commands form a sequence of operations considered a "script".
TEST(InsertCharacterAtIndexCommand, multipleCommands1) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    EXPECT_EQ("", storedString_p->getString());
    
    std::vector<WSU::Model::InsertCharacterAtIndexCommand> commands {
        {storedString_p, 'A', 0 },
        {storedString_p, 'B', 1 },
        {storedString_p, 'C', 2 },
    };
    for(auto cmd : commands) {
        cmd();  // Test functor operator as side effect
    }
    EXPECT_EQ("ABC", storedString_p->getString());
}

/// \ref 3_1 Multiple commands form a sequence of operations considered a "script".
TEST(InsertCharacterAtIndexCommand, multipleCommands2) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    EXPECT_EQ("", storedString_p->getString());
    
    std::vector<WSU::Model::InsertCharacterAtIndexCommand> commands {
        {storedString_p, 'A', 0 },
        {storedString_p, 'B', 1 },
        {storedString_p, 'C', 1 },
    };
    for(auto cmd : commands) {
        cmd.run();
    }
    EXPECT_EQ("ACB", storedString_p->getString());
}

/// \ref 1_4  A Command is a mechanism for inserting a character at an index
/// \ref 3_1_1 Command names are human readable
TEST(InsertCharacterAtIndexCommand, makeCommandWithName) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    EXPECT_EQ("", storedString_p->getString());
    
    const json11::Json obj = json11::Json::object({
        { "command", std::string {WSU::Model::InsertCharacterAtIndexCommand::name} },
        { "character", std::string {'z'} },
        { "index", 0 } });
    
    auto cmd_p = WSU::Model::StoredString::makeCommandWithName(WSU::Model::InsertCharacterAtIndexCommand::name, storedString_p, obj.dump());
    if(nullptr != cmd_p) {
        cmd_p->run();
    }
    EXPECT_EQ("z", storedString_p->getString());
}

/// \ref R2_0 In order undo a command, a reciprocal command is needed
TEST(InsertCharacterAtIndexCommand, reciprocal0) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    EXPECT_EQ("", storedString_p->getString());
    
    const json11::Json obj = json11::Json::object({
        { "command", std::string {WSU::Model::InsertCharacterAtIndexCommand::name} },
        { "character", std::string {'z'} },
        { "index", 0 } });
    
    auto cmd_p = WSU::Model::StoredString::makeCommandWithName(WSU::Model::InsertCharacterAtIndexCommand::name, storedString_p, obj.dump());
    ASSERT_TRUE(nullptr != cmd_p);
    cmd_p->run();
    EXPECT_EQ("z", storedString_p->getString());
    
    auto reciprocalCmd_p = cmd_p->makeReciprocalCommand();
    ASSERT_TRUE(nullptr != reciprocalCmd_p);
    reciprocalCmd_p->run();
    EXPECT_EQ("", storedString_p->getString());
}

/// \ref R2_0 In order undo a command, a reciprocal command is needed
TEST(InsertCharacterAtIndexCommand, reciprocal1) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    storedString_p->appendCharacter('$');
    storedString_p->appendCharacter('#');
    storedString_p->appendCharacter('!');
    EXPECT_EQ("$#!", storedString_p->getString());
    
    const json11::Json obj = json11::Json::object({
        { "command", std::string {WSU::Model::InsertCharacterAtIndexCommand::name} },
        { "character", std::string {'z'} },
        { "index", 1 } });
    
    auto cmd_p = WSU::Model::StoredString::makeCommandWithName(WSU::Model::InsertCharacterAtIndexCommand::name, storedString_p, obj.dump());
    ASSERT_TRUE(nullptr != cmd_p);
    cmd_p->run();
    EXPECT_EQ("$z#!", storedString_p->getString());
    
    auto reciprocalCmd_p = cmd_p->makeReciprocalCommand();
    ASSERT_TRUE(nullptr != reciprocalCmd_p);
    reciprocalCmd_p->run();
    EXPECT_EQ("$#!", storedString_p->getString());
}

/// \ref R2_0 In order undo a command, a reciprocal command is needed
TEST(InsertCharacterAtIndexCommand, reciprocal2) {
    std::shared_ptr<WSU::Model::StoredString> storedString_p { new WSU::Model::StoredString };
    storedString_p->appendCharacter('$');
    storedString_p->appendCharacter('#');
    storedString_p->appendCharacter('!');
    EXPECT_EQ("$#!", storedString_p->getString());
    
    const json11::Json obj = json11::Json::object({
        { "command", std::string {WSU::Model::InsertCharacterAtIndexCommand::name} },
        { "character", std::string {'z'} },
        { "index", 3 } });
    
    auto cmd_p = WSU::Model::StoredString::makeCommandWithName(WSU::Model::InsertCharacterAtIndexCommand::name, storedString_p, obj.dump());
    ASSERT_TRUE(nullptr != cmd_p);
    cmd_p->run();
    EXPECT_EQ("$#!z", storedString_p->getString());
    
    auto reciprocalCmd_p = cmd_p->makeReciprocalCommand();
    ASSERT_TRUE(nullptr != reciprocalCmd_p);
    reciprocalCmd_p->run();
    EXPECT_EQ("$#!", storedString_p->getString());
}
