#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "tictactoe.hpp"

// See: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md
// For documentation on how to write tests with Catch2

TEST_CASE("outOfBoundary"){
    REQUIRE(EvaluateBoard("O...X.X...") == Evaluation::InvalidInput);
}

TEST_CASE("missingEntry"){
    REQUIRE(EvaluateBoard("OO...X") == Evaluation::InvalidInput);
}

TEST_CASE("noEntry"){
    REQUIRE(EvaluateBoard("") == Evaluation::InvalidInput);
}

TEST_CASE("null"){
    REQUIRE(EvaluateBoard(nullptr) == Evaluation::InvalidInput);
}

TEST_CASE("allX"){
    REQUIRE(EvaluateBoard("XXXXXXXXX") == Evaluation::UnreachableState);
}

TEST_CASE("unequalTurns"){
    REQUIRE(EvaluateBoard("OOOOOOXX.") == Evaluation::UnreachableState);
}

TEST_CASE("duplicateRowWinner"){
    REQUIRE(EvaluateBoard("OOOXXX...") == Evaluation::UnreachableState);
}

TEST_CASE("duplicateColWinner"){
    REQUIRE(EvaluateBoard("OX.OX.OX.") == Evaluation::UnreachableState);
}

TEST_CASE("duplicateDiagonalWinner"){
    REQUIRE(EvaluateBoard("XOXOXOXOX") == Evaluation::UnreachableState);
}

TEST_CASE("duplicateCrossWinner"){
    REQUIRE(EvaluateBoard("XOXOOOXOX") == Evaluation::UnreachableState);
}

TEST_CASE("simpleNoWinnerBoard"){
    REQUIRE(EvaluateBoard("O...X.X..") == Evaluation::NoWinner);
}

TEST_CASE("emptyBoardWithOtherSymbols"){
    REQUIRE(EvaluateBoard("n2siEl!d-") == Evaluation::NoWinner);
}

TEST_CASE("noWinnerCaseInsensitive"){
    REQUIRE(EvaluateBoard("O9.i.Xx.o") == Evaluation::NoWinner);
}

TEST_CASE("noWinnerFullBoard"){
    REQUIRE(EvaluateBoard("OXOXXOXOX") == Evaluation::NoWinner);
}

TEST_CASE("XWinsCol"){
    REQUIRE(EvaluateBoard("XO.XXOXO.") == Evaluation::Xwins);
}

TEST_CASE("XWinsDiaLeft"){
    REQUIRE(EvaluateBoard("XO..XO.OX") == Evaluation::Xwins);
}

//EdgeCase
TEST_CASE("lastEntryAtCorner") {
    REQUIRE(EvaluateBoard("XOOXOOXXX") == Evaluation::Xwins);
}

TEST_CASE("OWinsRow"){
    REQUIRE(EvaluateBoard("X..OOOX..") == Evaluation::Owins);
}

TEST_CASE("OWinsDiaRight"){
    REQUIRE(EvaluateBoard(".XOXO.O..") == Evaluation::Owins);
}

TEST_CASE("OWinsCaseInsensitive"){
    REQUIRE(EvaluateBoard(".xOXo.O..") == Evaluation::Owins);
}

//EdgeCase
TEST_CASE("lastEntryAtMiddle"){
    REQUIRE(EvaluateBoard("OXOXOXOXO") == Evaluation::Owins);
}
