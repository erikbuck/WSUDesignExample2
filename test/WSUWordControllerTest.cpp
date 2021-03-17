//
//  CommandControllerTest.cpp
//  demo
//
//  Created by Erik M. Buck on 3/16/21.
//  Copyright © 2021 Erik M. Buck. All rights reserved.
//

#include <gtest/gtest.h>
#include "StoredString.hpp"
#include "WSUWordController.hpp"
#include "InsertCharacterAtIndexCommand.hpp"

TEST(WSUWordController, emptyModel) {
    WSU::Controller::WSUWordController commandController;
    EXPECT_EQ("", commandController.getCurrentStoredStringValue());
}

TEST(WSUWordController, runScript0) {
    WSU::Controller::WSUWordController commandController;
    commandController.runScript(
    "{\"character\": \"a\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}");
    EXPECT_EQ("a", commandController.getCurrentStoredStringValue());
}

TEST(WSUWordController, runScript1) {
    WSU::Controller::WSUWordController commandController;
    commandController.runScript(
    "{\"character\": \"a\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"character\": \"-\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}");
    EXPECT_EQ("-a", commandController.getCurrentStoredStringValue());
}

TEST(WSUWordController, runScript2) {
    WSU::Controller::WSUWordController commandController;
    commandController.runScript(
    "{\"character\": \"a\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"character\": \"-\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"character\": \"a\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"character\": \"!\", \"command\": \"insertCharacterAtIndex\", \"index\": 1}");
    EXPECT_EQ("a!-a", commandController.getCurrentStoredStringValue());
}

TEST(WSUWordController, runScript3) {
    WSU::Controller::WSUWordController commandController;
    commandController.runScript(
    "{\"character\": \"a\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"character\": \"-\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"character\": \"a\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}"
    "{\"command\": \"removeCharacterAtIndex\", \"index\": 1}");
    EXPECT_EQ("aa", commandController.getCurrentStoredStringValue());
}

TEST(WSUWordController, undo0) {
    WSU::Controller::WSUWordController commandController;
    auto cmd_p =  commandController.makeCommandWithName("insertCharacterAtIndex", "{\"character\": \"-\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}");
    EXPECT_EQ("", commandController.getCurrentStoredStringValue());

    commandController.runCommandWithUndoRedoSupport(cmd_p);
    EXPECT_EQ("-", commandController.getCurrentStoredStringValue());
    commandController.getUndoManager().undo();
    EXPECT_EQ("", commandController.getCurrentStoredStringValue());
}

TEST(WSUWordController, undo1) {
    WSU::Controller::WSUWordController commandController;
    auto cmd_p =  commandController.makeCommandWithName("insertCharacterAtIndex", "{\"character\": \"-\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}");
    EXPECT_EQ("", commandController.getCurrentStoredStringValue());

    commandController.runCommandWithUndoRedoSupport(cmd_p);
    commandController.runCommandWithUndoRedoSupport(cmd_p);
    commandController.runCommandWithUndoRedoSupport(cmd_p);
    commandController.runCommandWithUndoRedoSupport(cmd_p);
    EXPECT_EQ("----", commandController.getCurrentStoredStringValue());
    auto undoManager = commandController.getUndoManager();
    undoManager.undo();
    EXPECT_EQ("---", commandController.getCurrentStoredStringValue());
    undoManager.undo();
    undoManager.undo();
    undoManager.undo();
    EXPECT_EQ("", commandController.getCurrentStoredStringValue());
}

TEST(WSUWordController, redo0) {
    WSU::Controller::WSUWordController commandController;
    auto cmd_p =  commandController.makeCommandWithName("insertCharacterAtIndex", "{\"character\": \"-\", \"command\": \"insertCharacterAtIndex\", \"index\": 0}");
    EXPECT_EQ("", commandController.getCurrentStoredStringValue());

    commandController.runCommandWithUndoRedoSupport(cmd_p);
    commandController.runCommandWithUndoRedoSupport(cmd_p);
    commandController.runCommandWithUndoRedoSupport(cmd_p);
    commandController.runCommandWithUndoRedoSupport(cmd_p);
    auto undoManager = commandController.getUndoManager();
    EXPECT_EQ("----", commandController.getCurrentStoredStringValue());
    undoManager.undo();
    EXPECT_EQ("---", commandController.getCurrentStoredStringValue());
    undoManager.redo();
    EXPECT_EQ("----", commandController.getCurrentStoredStringValue());
    undoManager.undo();
    undoManager.undo();
    undoManager.undo();
    EXPECT_EQ("-", commandController.getCurrentStoredStringValue());
    undoManager.redo();
    undoManager.redo();
    EXPECT_EQ("---", commandController.getCurrentStoredStringValue());
}
