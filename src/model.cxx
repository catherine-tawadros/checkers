#include <iostream>
#include "model.hxx"
#include "space.hxx"


Model::Model()
{
    board = Board();
    turn = -1;
    other_player = 1;
    game_over_ = false;
    spot_selected = false;
    must_jump = false;
}

void
Model::move(Space s, Position p)
{
    bool king = board.is_kinged(board.at_pos(s.spot));
    bool jumped = false;
    //if the move that's about to happen is a jump, hold a boolean saying so
    for (Board::move m : board.possible_captures(turn)) {
        if (Board::move(s.spot, p) == m) {
            jumped = true;
        }
    }
    //if the player must jump (meaning the last move was a jump and there's
    // another one available
    if (!must_jump) {
        //make a direction vector
        std::vector<int> v = {(p.x - s.spot.x), (p.y - s.spot.y)};
        //update direction vector if the player is moving two spaces
        if (abs(v.at(0)) == 2) {
            v.at(0) = v.at(0) / 2;
            v.at(1) = v.at(1) / 2;
            //empty the jumped position
            board.set(Position(s.spot.x + v.at(0), s.spot.y + v.at(1)), 0);
            board.set_kinged(Position(s.spot.x + v.at(0), s.spot.y + v.at(1))
                             , false);
        }
        //update the new position
        board.set(p, turn);
        if (king) {board.set_kinged(p, true);;}
        //empty the current position
        board.set(s.spot, 0);
        board.set_kinged(s.spot, false);
    }
    //else if the player has to jump
    else {
        for (Board::move m : board.possible_captures(turn)) {
            //only move if the move is a jump
            if (Board::move(s.spot, p) == m) {
                //make direction vector
                std::vector<int> v = {(p.x - s.spot.x), (p.y - s.spot.y)};
                //update captured
                board.set(Position(s.spot.x + v.at(0)/2, s.spot.y + v.at(1)/2),
                          0);
                board.set_kinged(Position(s.spot.x + v.at(0)/2, s.spot.y + v.at
                                                                                    (1)/2), false);
                //update new position
                board.set(p, turn);
                if (king) {board.set_kinged(p, true);;}
                //update current
                board.set(s.spot, 0);
                board.set_kinged(s.spot, false);
            }
        }
    }

    //if the dark player gets to the other side then king it
    if (turn == -1 && p.y == 0) {
        board.set_kinged(p, true);
    }

    //if the light player gets to the other side then king it
    if (turn == 1 && p.y == 7) {
        board.set_kinged(p, true);
    }

    //figure out if the player has another jump available and if so,
    //indicate that they must jump on their next turn, set their selected spot
    //to the current one so they have to start there, and return so they can
    // move again
    if (jumped && !board.possible_captures_for_spot(p, turn).empty()) {
        must_jump = true;
        selected_spot = p;
        return;
    }

    //actually advance the turn, since the player has moved and has no more
    // jumps left
    advance_turn();
}

void
Model::advance_turn()
{
    //make sure the game isn't over
    if (board.player_total(other_player) == 0) {
        set_game_over();
    }

    spot_selected = false;
    must_jump = false;
    selected_spot = Position(-1, -1);
    turn = turn*-1;
    other_player = other_player*-1;
}

void
Model::set_game_over()
{
    game_over_ = true;
    for (Space s : board.spaces) {
        board.set(s.spot, turn);
        board.set_kinged(s.spot, false);
    }
}
