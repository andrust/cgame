#include "Card.h"

namespace ulti {

Card::Card(const eColors& c, const eFigures& f)
: _color(c)
, _figure(f)
{}

Card::CardCard(const Card& other)
: _color(other.GetColor())
, _figure(other.GetFigure())_
{}

Card& Card::Card operator= (const Card& c) {
    _color = c.GetColor();
    _figure = c.GetFigure();
}

} //ns ulti
