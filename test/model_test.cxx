#include "model.hxx"
#include <catch.hxx>

TEST_CASE("condition 1")
{
    // the pieces are set up on the board correctly at the beginning of the
    // game according to the traditional rules of checkers

    //this condition is easily checked by running the game and viewing the
    // tile setup

    // other setup tests:

    Model model;

    CHECK(model.turn == -1);
    CHECK(model.spot_selected == false);
    CHECK(model.other_player == -1);
    CHECK(model.must_jump == false);
}

TEST_CASE("condition 2")
{
    //a player can move by clicking on the piece they would like to move to
    // and the place they would like to move it to

    Model model;

    model.move(model.board.at_pos({0,5}), {1,4});
    CHECK(model.board.at_pos({0,5}).player == 0);
    CHECK(model.board.at_pos({1,4}).player == -1);
}
