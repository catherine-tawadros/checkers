//
// Created by ctawa on 3/8/2022.
//

#ifndef CONTROLLER_CXX_SPACE_HXX
#define CONTROLLER_CXX_SPACE_HXX

#include <ge211.hxx>
using Position = ge211::Posn<int>;

class Space
{
    public:

    Position spot;
    int player;
    bool kinged;

    Space(Position d, int p);
    Space(Position d);

    void set(int p);
    void set_kinged(bool k) {kinged = k;};
    void king() {kinged = true;};

    Position up_left() {return Position(spot.x-1, spot.y-1);};
    Position up_right() {return Position(spot.x+1, spot.y-1);};
    Position down_right() {return Position(spot.x-1, spot.y+1);};
    Position down_left() {return Position(spot.x+1, spot.y+1);};

    Position double_up_left() {return Position(spot.x-2, spot.y-2);};
    Position double_up_right() {return Position(spot.x+2, spot.y-2);};
    Position double_down_right() {return Position(spot.x-2, spot.y+2);};
    Position double_down_left() {return Position(spot.x+2, spot.y+2);};
};


#endif //CONTROLLER_CXX_SPACE_HXX
