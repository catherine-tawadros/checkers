#pragma once

#include <ge211.hxx>
#include "space.hxx"
#include "board.hxx"

class Model
{
    public:

        Model();

        Board board;
        int turn;
        int other_player;
        bool spot_selected;
        Position selected_spot = Position(-1, -1);
        bool must_jump;

        void set_selected_spot(Position p) {
            selected_spot = p; spot_selected = true;
        };

        void advance_turn();

    void move(Space s, Position p);
private:

        bool game_over_;

        void set_game_over();

};
