//
// Created by ctawa on 3/9/2022.
//

#ifndef CONTROLLER_CXX_BOARD_HXX
#define CONTROLLER_CXX_BOARD_HXX

#include <ge211.hxx>
#include "space.hxx"

class Board
{
    public:

        using Rectangle = ge211::Rect<int>;
        using Position = ge211::Posn<int>;
        using Dimensions = ge211::Dims<int>;
        using pos_set = std::vector<Position>;
        using move = std::pair<Position, Position>;
        using move_set = std::vector<std::pair<Position, Position>>;

        Board();

        std::vector<Space> spaces;

        bool good_position(Position pos) const;

        pos_set player_spaces(int p) const;
        int player_total(int p);

        Space at_pos(Position p) const;

        void set(Position p, int player);

        move_set possible_moves(int player) const;

        pos_set moves_for_spot(Position p, int player) const;

        move_set possible_captures(int p) const;

        pos_set possible_captures_for_spot(Position pos, int p) const;

        bool is_kinged(Space s) const
        {return s.kinged;};

        void set_kinged(Position p, bool k);
        void king(Position p) {at_pos(p).king();};

    private:

        Dimensions dims_;

};


#endif //CONTROLLER_CXX_BOARD_HXX
