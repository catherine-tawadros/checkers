#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
    using Dimensions = ge211::geometry::Dims<int>;

public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;
    Dimensions initial_window_dimensions() const override;

private:
    Model model_;
    View view_;
    ge211::Posn<int> position_;

    void on_mouse_move(ge211::Posn<int> pos) override;

    void on_mouse_down(ge211::Mouse_button, Position pos) override;
};
