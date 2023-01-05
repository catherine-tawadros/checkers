#include "controller.hxx"

using Dimensions = ge211::geometry::Dims<int>;

Controller::Controller()
        : view_(model_),
          position_(ge211::Posn<int>(0,0))
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set, position_);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return Dimensions(400, 400);
}

void
Controller::on_mouse_move(ge211::Posn<int> pos)
{
    position_ = pos;
}

void
Controller::on_mouse_down(ge211::Mouse_button, Position pos)
{
    view_.on_click(position_);
}
