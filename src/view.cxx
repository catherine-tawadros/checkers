#include <iostream>
#include "view.hxx"

using Dimensions = ge211::geometry::Dims<int>;

View::View(Model const& model)
        : model_(model),
          light_tile_sprite({50, 50}, {210, 200, 200}),
          dark_tile_sprite({50, 50}, {60, 50, 50}),
          red_tile_sprite({50, 50}, {100, 50, 50}),
          redder_tile_sprite({50, 50}, {200, 50, 50}),
          light_sprite(21, {255, 255, 255}),
          dark_sprite(21, {0, 0, 0}),
          small_dark_sprite(10, {50, 50, 50}),
          small_light_sprite(10, {200, 200, 200})
{ }

Position
View::screen_to_board(Position p)
{
    return Position(p.x/50, p.y/50);
}

void
View::draw(ge211::Sprite_set& set, ge211::Posn<int> pos)
{
    int i = 0;
    for (Space s : model_.board.spaces) {

        if (i%2 == 0) {
            set.add_sprite(light_tile_sprite, {s.spot.x * 50, s.spot.y * 50});
        }
        else {
            set.add_sprite(dark_tile_sprite, {s.spot.x * 50, s.spot.y * 50});
        }
        i++;
        if (s.spot.x == 7) {i++;}

        if (s.player == -1) {
            set.add_sprite(dark_sprite, {s.spot.x*50+4, s.spot.y*50+4}, 1);
            if (s.kinged) {
                set.add_sprite(small_dark_sprite, {s.spot.x*50+15, s.spot
                .y*50+15}, 2);
            }
        }
        if (s.player == 1) {
            set.add_sprite(light_sprite, {s.spot.x*50+4, s.spot.y*50+4}, 1);
            if (s.kinged) {
                set.add_sprite(small_light_sprite, {s.spot.x * 50 + 15, s.spot
                                                                         .y *
                                                                        50 +
                                                                        15}, 2);
            }
        }

        if (!model_.spot_selected) {
            for (Board::move m : model_.board.possible_moves(model_.turn)) {
                if (m.first == screen_to_board(pos)) {
                    set.add_sprite(red_tile_sprite,
                                   Position(screen_to_board(pos)
                                                    .x * 50,
                                            screen_to_board(pos).y * 50));
                    set.add_sprite(red_tile_sprite, Position(m
                    .second.x *50,m.second.y * 50));
                }
            }
        }

        else if (model_.spot_selected) {
            set.add_sprite(redder_tile_sprite, Position(model_.selected_spot
            .x*50, model_.selected_spot.y*50));
            for (Position p : model_.board.moves_for_spot(model_.selected_spot,
                                                     model_.turn)) {
                set.add_sprite(red_tile_sprite, Position(p.x * 50,p.y * 50));
            }
        }
    }
}

void
View::on_click(Position pos) {
    Position board_pos = screen_to_board(pos);
    //if they haven't clicked their first spot yet
    if (!model_.spot_selected) {
        //only react if the clicked spot can move
        for (Board::move m : model_.board.possible_moves(model_.turn)) {
            if (m.first == board_pos) {
                model_.set_selected_spot(board_pos);
                return;
            }
        }
    }
    //otherwise, they have selected their first spot
    else {
        //only react if the spot they clicked can be moved to
        for (Position p : model_.board.moves_for_spot(model_.selected_spot, model_
        .turn)) {
            if (p == board_pos) {
                //actually move
                model_.move(model_.board.at_pos(model_.selected_spot), p);
            }
        }
    }
}