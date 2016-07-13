#pragma once

#include <type_traits>

#include "CardProperties.h"

namespace ulti {

class Card {
public:

public:
    inline eColors GetColor() const { return _color; }
    inline eFigures GetFigure() const {return _figure; }

    inline Card& SetColor(const eColors& c) { _color = c; return *this; }
    inline Card& SetFigure(const eFigures& f) { _figure = f; return *this; }

public:
    Card() = default;
    Card(const eColors& c, const eFigures& f);
    Card(const Card& other);

    Card& operator= (const Card& c);

private:
    eColors _color = eColors::GREEN;
    eFigures _figure = eFigures::VII;
};

} //ns ulti
