#pragma once

#include <exception>
#include <string>
#include <set>
#include <ostream>

#include "CardProperties.h"
namespace ulti {

enum class eBids {
    PARTY = 0,
    P40_100,
    P4ACE,
    ULTI,
    BETLI,
    REBETLI,
    TBETLI,
    DURCHMARS,
    REDURCHMARS,
    TDURCHMARS,
    P20_100,
    NONE
};

using Bid = std::set<eBids>;

std::string to_string(eBids b) {
    switch(b) {
        case eBids::PARTY :       return "parti";
        case eBids::P40_100 :     return "40-100";
        case eBids::P4ACE :       return "4 ász";
        case eBids::ULTI :        return "ulti";
        case eBids::BETLI :       return "betli";
        case eBids::REBETLI :     return "rebetli";
        case eBids::TBETLI :      return "terített betli";
        case eBids::DURCHMARS :   return "durchmars";
        case eBids::TDURCHMARS :  return "terített durchmars";
        case eBids::REDURCHMARS : return "redurchmars";
        case eBids::P20_100 :     return "20-100";
        default: return "";
    }
    return "";
}

bool isValidBid(eSuits suit, const Bid& bid) {
    // suit mathches bid type
    if(suit == eSuits::NONE) {
        if(bid.size() == 1) { // colorless bids cannot be compound
            eBids b = *bid.begin();
            switch(b) { //betli and ducrchmars variant are allowed with no color
                case eBids::BETLI:
                case eBids::REBETLI:
                case eBids::TBETLI:
                case eBids::DURCHMARS:
                case eBids::TDURCHMARS:
                case eBids::REDURCHMARS: return true;
                default: return false;
            }
        }
        return false;
    }

    for(auto b : bid) {
        switch(b) {
            case eBids::PARTY: if(bid.count(eBids::P40_100) || bid.count(eBids::P20_100)) return false; else break;
            case eBids::P40_100: if(bid.count(eBids::PARTY) || bid.count(eBids::P20_100)) return false; else break;
            case eBids::P20_100: if(bid.count(eBids::PARTY) || bid.count(eBids::P40_100)) return false; else break;

            case eBids::P4ACE: if(bid.count(eBids::DURCHMARS) || bid.count(eBids::TDURCHMARS) || (!bid.count(eBids::PARTY) && !bid.count(eBids::P20_100))) return false; else break;

            case eBids::DURCHMARS:
            case eBids::TDURCHMARS: if(bid.count(eBids::P4ACE)) return false; else break;

            case eBids::ULTI: if(!bid.count(eBids::PARTY) && !bid.count(eBids::P20_100) && !bid.count(eBids::P40_100)) return false; else break;

            case eBids::BETLI:
            case eBids::REBETLI:
            case eBids::TBETLI:
            case eBids::REDURCHMARS:
            case eBids::NONE: return false;
        }
    }
    return true;
}

int getPrice(eSuits suit, eBids bid) {
    switch(bid) {
        case eBids::PARTY :       return eSuits::RED == suit ? 2 : 1;
        case eBids::P40_100 :
        case eBids::ULTI :
        case eBids::P4ACE :       return eSuits::RED == suit ? 8 : 4;
        case eBids::BETLI :       return 5;
        case eBids::REBETLI :     return 10;
        case eBids::TBETLI :      return 20;
        case eBids::DURCHMARS :   return eSuits::RED == suit ? 12 : 6;
        case eBids::TDURCHMARS :  return (eSuits::RED == suit || eSuits::NONE == suit) ? 24 : 12;
        case eBids::REDURCHMARS : return 12;
        case eBids::P20_100 :     return eSuits::RED == suit ? 16 : 8;
        case eBids::NONE:         return 0;
    }
    throw std::invalid_argument{"unhandled bid"};
}

int getPrice(eSuits suit, const Bid& bid) {
    int ret = 0;
    for(auto b : bid) {
        ret += getPrice(suit, b);
    }
    return ret;
}

bool isBiggerThan(eSuits suitL, const Bid& bidL, eSuits suitR, const Bid& bidR) {
    auto priceL = getPrice(suitL, bidL);
    auto priceR = getPrice(suitR, bidR);

    if(priceL == priceR) {
        return bidL.size() < bidR.size();
    }
    return priceL > priceR;
}

std::ostream& operator<<(std::ostream& os, const eBids& bid) {
    os << to_string(bid);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Bid& bid) {
    for(const auto& b : bid) {
        os << b << ' ';
    }
    return os;
}

} // ns ulti
