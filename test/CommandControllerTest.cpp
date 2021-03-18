//
//  CommandControllerTest.cpp
//  demo
//
//  Created by Erik M. Buck on 3/16/21.
//  Copyright © 2021 Erik M. Buck. All rights reserved.
//

#include <stdio.h>

#include <gtest/gtest.h>
#include "StoredString.hpp"
#include "CommandController.hpp"

TEST(CommandController, emptyModel) {
    WSU::Model::CommandController commandController;
    EXPECT_EQ("", commandController.getCurrentStoredStringValue());
}

TEST(CommandController, runScript0) {
    WSU::Model::CommandController commandController;
    commandController.runScript(
    "{\"character\": \"a\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}");
    EXPECT_EQ("a", commandController.getCurrentStoredStringValue());
}

TEST(CommandController, runScript1) {
    WSU::Model::CommandController commandController;
    commandController.runScript(
    "{\"character\": \"a\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"character\": \"-\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}");
    EXPECT_EQ("-a", commandController.getCurrentStoredStringValue());
}

TEST(CommandController, runScript2) {
    WSU::Model::CommandController commandController;
    commandController.runScript(
    "{\"character\": \"a\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"character\": \"-\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"character\": \"a\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"character\": \"!\", \"command\": \"insertCharacterAtIndex\", \"index\": 1}");
    EXPECT_EQ("a!-a", commandController.getCurrentStoredStringValue());
}

TEST(CommandController, runScript3) {
    WSU::Model::CommandController commandController;
    commandController.runScript(
    "{\"character\": \"a\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"character\": \"-\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"character\": \"a\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"command\": \"removeCharacterAtIndex\", \"index\": 1}");
    EXPECT_EQ("aa", commandController.getCurrentStoredStringValue());
}
