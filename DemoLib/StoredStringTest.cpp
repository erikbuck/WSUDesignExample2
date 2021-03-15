#include <gtest/gtest.h>
#include "StoredString.hpp"

TEST(StoredString, getString) {
    WSU::Model::StoredString model;
    EXPECT_EQ("", model.getString());
    model.appendCharacter('$');
    EXPECT_EQ("$", model.getString());
}

// \ref R1_2
TEST(StoredString, appendCharacter) {
    WSU::Model::StoredString model;
    model.appendCharacter('$');
    EXPECT_EQ("$", model.getString());
    model.appendCharacter('#');
    model.appendCharacter('!');
    EXPECT_EQ("$#!", model.getString());
}

// \ref R1_3
TEST(StoredString, insertCharacterAtIndex) {
    WSU::Model::StoredString model;
    model.appendCharacter('$');
    model.appendCharacter('#');
    model.appendCharacter('!');
    EXPECT_EQ("$#!", model.getString());
    model.insertCharacterAtIndex('a', 0);
    EXPECT_EQ("a$#!", model.getString());   /// \ref R1_3_1 \ref R1_3_2
    model.insertCharacterAtIndex('c', 4);
    EXPECT_EQ("a$#!c", model.getString());  // Boundry "insert" after last char
    model.insertCharacterAtIndex('d', 4);
    EXPECT_EQ("a$#!dc", model.getString()); // Boundry "insert" not at either end
}

// \ref R1_4
TEST(StoredString, removeCharacterAtIndex) {
    WSU::Model::StoredString model;
    model.appendCharacter('$');
    model.appendCharacter('#');
    model.appendCharacter('!');
    model.appendCharacter('a');
    model.appendCharacter('b');
    EXPECT_EQ("$#!ab", model.getString());
    model.removeCharacterAtIndex(0);
    EXPECT_EQ("#!ab", model.getString());           /// \ref R1_4_1 \ref R1_4_2 // Boundry at beginning
    model.removeCharacterAtIndex(3);
    EXPECT_EQ("#!a", model.getString());            // Boundry at end
    model.removeCharacterAtIndex(1);
    EXPECT_EQ("#a", model.getString());             // Boundry not at either end
}

// \ref R1_5
TEST(StoredString, insertStringAtIndex) {
    WSU::Model::StoredString model;
    model.appendCharacter('$');
    model.appendCharacter('#');
    model.appendCharacter('!');
    EXPECT_EQ("$#!", model.getString());
    model.insertStringAtIndex("ABC", 0);
    EXPECT_EQ("ABC$#!", model.getString());         // \ref R1_5_1 \ref R1_5_2 // Boundry at beginning
    model.insertStringAtIndex("DEF", 6);
    EXPECT_EQ("ABC$#!DEF", model.getString());      // Boundry at end
    model.insertStringAtIndex("GH", 6);
    EXPECT_EQ("ABC$#!GHDEF", model.getString());    // Boundry not at either end
}
