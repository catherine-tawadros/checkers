//
// Created by ctawa on 3/8/2022.
//

#include "space.hxx"
#include <ge211.hxx>
using Position = ge211::Posn<int>;

Space::Space(Position d)
        : Space(d, 0)
{ }

Space::Space(Position d, int p)
        : spot(d),
          player(p),
          kinged(false)
{ }

void
Space::set(int p)
{
    player = p;
}
