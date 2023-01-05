#pragma once

#include "model.hxx"

class View
{

public:
    using Dimensions = ge211::geometry::Dims<int>;

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set, ge211::Posn<int> pos);

    void on_click(Position pos);

private:
    Model model_;
    ge211::Rectangle_sprite const light_tile_sprite;
    ge211::Rectangle_sprite const dark_tile_sprite;
    ge211::Rectangle_sprite const red_tile_sprite;
    ge211::Rectangle_sprite const redder_tile_sprite;
    ge211::Circle_sprite const light_sprite;
    ge211::Circle_sprite const dark_sprite;
    ge211::Circle_sprite const small_dark_sprite;
    ge211::Circle_sprite const small_light_sprite;

    Position screen_to_board(Position p);
};
