#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "tictactoe.hpp"

// See: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md
// For documentation on how to write tests with Catch2

TicTacToe ticTacToe;


/**
 * O _ _
 * _ X _
 * X _ _ _
 */
TEST_CASE("outOfBoundary"){
    REQUIRE(ticTacToe.EvaluateBoard("O...X.X...") == Evaluation::InvalidInput);
}

/**
 * O O _
 * _ _ X
 *
 */
TEST_CASE("missingEntry"){
    REQUIRE(ticTacToe.EvaluateBoard("OO...X") == Evaluation::InvalidInput);
}

TEST_CASE("noEntry"){
    REQUIRE(ticTacToe.EvaluateBoard("") == Evaluation::InvalidInput);
}

TEST_CASE("null"){
    REQUIRE(ticTacToe.EvaluateBoard(nullptr) == Evaluation::InvalidInput);
}

/**
 * X X X
 * X X X
 * X X X
 */
TEST_CASE("allX"){
    REQUIRE(ticTacToe.EvaluateBoard("XXXXXXXXX") == Evaluation::UnreachableState);
}

/**
 * O O O
 * O O O
 * X X _
 */
TEST_CASE("unequalTurns"){
    REQUIRE(ticTacToe.EvaluateBoard("OOOOOOXX.") == Evaluation::UnreachableState);
}

/**
 * O O O
 * X X X
 * _ _ _
 */
TEST_CASE("duplicateRowWinner"){
    REQUIRE(ticTacToe.EvaluateBoard("OOOXXX...") == Evaluation::UnreachableState);
}

/**
 * O X _
 * O X _
 * O X _
 */
TEST_CASE("duplicateColWinner"){
    REQUIRE(ticTacToe.EvaluateBoard("OX.OX.OX.") == Evaluation::UnreachableState);
}

/**
 * O _ _
 * _ X _
 * X _ _
 */
TEST_CASE("simpleNoWinnerBoard"){
    REQUIRE(ticTacToe.EvaluateBoard("O...X.X..") == Evaluation::NoWinner);
}

/**
 * _ _ _
 * _ _ _
 * _ _ _
 */
TEST_CASE("emptyBoardWithOtherSymbols"){
    REQUIRE(ticTacToe.EvaluateBoard("n2siEl!d-") == Evaluation::NoWinner);
}

/**
 * _ _ _
 * _ _ _
 * _ _ _
 */
TEST_CASE("noWinnerCaseInsensitive"){
    REQUIRE(ticTacToe.EvaluateBoard("O9.i.Xx.o") == Evaluation::NoWinner);
}

/**
 * O X O
 * X X O
 * X O X
 */
TEST_CASE("noWinnerFullBoard"){
    REQUIRE(ticTacToe.EvaluateBoard("OXOXXOXOX") == Evaluation::NoWinner);
}

/**
 * X O _
 * X X O
 * X O _
 */
TEST_CASE("XWinsCol"){
    REQUIRE(ticTacToe.EvaluateBoard("XO.XXOXO.") == Evaluation::Xwins);
}

/**
 * X O _
 * _ X O
 * _ O X
 */
TEST_CASE("XWinsLeftDiagonal"){
    REQUIRE(ticTacToe.EvaluateBoard("XO..XO.OX") == Evaluation::Xwins);
}

/**
 * X O O
 * X O O
 * X X X
 */
//EdgeCase
TEST_CASE("lastEntryAtCorner") {
    REQUIRE(ticTacToe.EvaluateBoard("XOOXOOXXX") == Evaluation::Xwins);
}

/**
 * X O X
 * O X O
 * X O X
 */
 //EdgeCase
TEST_CASE("lastEntryAtMiddle"){
    REQUIRE(ticTacToe.EvaluateBoard("XOXOXOXOX") == Evaluation::Xwins);
}

/**
 * X _ _
 * O O O
 * X _ _
 */
TEST_CASE("OWinsRow"){
    REQUIRE(ticTacToe.EvaluateBoard("X..OOOX..") == Evaluation::Owins);
}

/**
 * _ X O
 * X O _
 * O _ _
 */
TEST_CASE("OWinsRightDiagonal"){
    REQUIRE(ticTacToe.EvaluateBoard(".XOXO.O..") == Evaluation::Owins);
}

/**
 * _ _ _
 * _ _ _
 * _ _ _
 */
TEST_CASE("OWinsCaseInsensitive"){
    REQUIRE(ticTacToe.EvaluateBoard(".xOXo.O..") == Evaluation::Owins);
}

/**
 * X O X
 * O O O
 * X O X
 */
TEST_CASE("lastEntryAtMiddle"){
    REQUIRE(ticTacToe.EvaluateBoard("XOXOOOXOX") == Evaluation::Owins);
}
