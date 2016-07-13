#include "CardComparison.h"

namespace ulti {

compare_figure::compare_figure(const eOrderDir& dir)
: _dir(dir)
{}

int compare_figure::compare_figure operator()(const Card& lhs, const Card& rhs) {
    if(lhs.GetFigure() == rhs.GetFigure()) {
        return 0;
    }

    switch(_dir) {
        case eOrderDir::ASC:
            return lhs.GetFigure() < rhs.GetFigure() ? 1 : -1;
        case eOrderDir::DESC:
            return lhs.GetFigure() > rhs.GetFigure() ? 1 : -1;
        case eOrderDir::COLORLESS_ASC:
            if(lhs.GetFigure() == eFigures::X) {
                return rhs.GetFigure() >= eFigures::LOW ? 1 : -1;
            }
            else if(rhs.GetFigure() == eFigures::X) {
                return lhs.GetFigure() <= eFigures::IX ? 1 : -1;
            }
            else {
                return lhs.GetFigure() > rhs.GetFigure() ? 1 : -1;
            }
        case eOrderDir::COLORLESS_DESC:
            if(lhs.GetFigure() == eFigures::X) {
                return rhs.GetFigure() <= eFigures::IX ? 1 : -1;
            }
            else if(rhs.GetFigure() == eFigures::X) {
                return lhs.GetFigure() >= eFigures::LOW ? 1 : -1;
            }
            else {
                return lhs.GetFigure() < rhs.GetFigure() ? 1 : -1;
            }
    }
    return 0;
}

int compare_color::operator()(const Card& lhs, const Card& rhs) {
    if(lhs.GetFigure() == rhs.GetFigure()) {
        return 0;
    }

    switch(_dir) {
        case eOrderDir::COLORLESS_ASC:
        case eOrderDir::ASC:
            return lhs.GetColor() < rhs.GetColor() ? 1 : -1;
        case eOrderDir::COLORLESS_DESC:
        case eOrderDir::DESC:
            return lhs.GetColor() > rhs.GetColor() ? 1 : -1;
    }
    return 0;
}

} //ns ulti
