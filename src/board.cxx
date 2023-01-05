//
// Created by ctawa on 3/9/2022.
//

#include <iostream>
#include "board.hxx"

Board::Board()
{
    for (int j=0; j<8; j++) {
        for (int i=0; i<8; i++) {
            spaces.push_back(Space(ge211::Posn<int>(i, j), 0));
        }
    }

    std::vector<int> numbers = {1,3,5,7,8,10,12,14,17,19,21,23};
    int k = 0;
    for (int i=0; i<24; i++) {
        if (i == numbers.at(k)) {
            spaces.at(63-i).player = -1;
            spaces.at(i).player = 1;
            k++;
        }
        if (k==12) {break;}
    }

    dims_ = {8, 8};
}

bool
Board::good_position(Position pos) const
{
    return (pos.x<8 && pos.y<8 && pos.x>=0 && pos.y>=0);
}

Board::pos_set
Board::player_spaces(int p) const
{
    pos_set set;
    for (Space s : spaces) {
        if (s.player == p) {
            set.push_back(s.spot);
        }
    }
    return set;
}

int
Board::player_total(int p)
{
    return player_spaces(p).size();
}

Space
Board::at_pos(Position p) const
{
    return spaces.at(p.x + (p.y*8));
}

void
Board::set(Position p, int player)
{
    Space* current_space = &spaces[p.x + (p.y*8)];
    current_space->player = player;
}

void
Board::set_kinged(Position p, bool k)
{
    Space* current_space = &spaces[p.x + (p.y*8)];
    current_space->kinged = k;
}

Board::move_set
Board::possible_moves(int p) const
{
    move_set ms;

    for (Board::move m : possible_captures(p)) {
        ms.push_back(m);
    }

    if (ms.empty()) {
        for (Space s: player_spaces(p)) {
            if (p == -1 || is_kinged(at_pos(s.spot))) {
                if (good_position(s.up_left()) && at_pos(s.up_left())
                                                          .player == 0) {
                    ms.push_back(move(s.spot, s.up_left()));
                }
                if (good_position(s.up_right()) &&
                    at_pos(s.up_right()).player ==
                    0) {
                    ms.push_back(move(s.spot, s.up_right()));
                }
            }
            if (p == 1 || is_kinged(at_pos(s.spot))) {
                if (good_position(s.down_left()) &&
                    at_pos(s.down_left()).player ==
                    0) {
                    ms.push_back(move(s.spot, s.down_left()));
                }
                if (good_position(s.down_right()) && at_pos(s.down_right())
                                                             .player == 0) {
                    ms.push_back(move(s.spot, s.down_right()));
                }
            }
        }
    }
    return ms;
}

Board::move_set
Board::possible_captures(int p) const
{
    move_set ms;

    for (Space s : player_spaces(p)) {
        if (p == -1 || is_kinged(at_pos(s.spot))) {
            if (good_position(s.double_up_left()) && at_pos(s.up_left())
            .player == -1 * p && at_pos(s.double_up_left()).player == 0
            && (is_kinged(at_pos(s.spot)) || !is_kinged(at_pos(s.up_left())))) {
                ms.push_back(move(s.spot, s.double_up_left()));
            }
            if (good_position(s.double_up_right()) && at_pos(s.up_right())
            .player == -1 * p && at_pos(s.double_up_right()).player== 0
            && (is_kinged(at_pos(s.spot)) || !is_kinged(at_pos(s.up_right())))) {
                ms.push_back(move(s.spot, s.double_up_right()));
            }
        }
        if (p == 1 || is_kinged(at_pos(s.spot))) {
            if (good_position(s.double_down_left()) && at_pos(s.down_left())
            .player == -1 * p&& at_pos(s.double_down_left()).player == 0 &&
            (is_kinged(at_pos(s.spot))|| !is_kinged(at_pos(s.down_left())))) {
                ms.push_back(move(s.spot, s.double_down_left()));
            }
            if (good_position(s.double_down_right()) && at_pos(s.down_right())
            .player == -1 * p && at_pos(s.double_down_right()).player == 0
            && (is_kinged(at_pos(s.spot)) || !is_kinged(at_pos(s.down_right())))) {
                ms.push_back(move(s.spot, s.double_down_right()));
            }
        }
    }
    return ms;
}

Board::pos_set
Board::moves_for_spot(Position p, int player) const
{
    pos_set poss;
    for (Board::move m : possible_moves(player)) {
        if (m.first == p) {
            poss.push_back(m.second);
        }
    }
    return poss;
}

Board::pos_set
Board::possible_captures_for_spot(Position pos, int p) const
{
    pos_set ps;
    for (move m : possible_captures(p)) {
        if (m.first == pos) {
            ps.push_back(m.second);
        }
    }
    return ps;
}
