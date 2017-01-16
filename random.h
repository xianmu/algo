// Author: xianmu <atangengineer@gmail.com>
// Created: 01/16/17
// Description:

#ifndef RANDOM_H
#define RANDOM_H
#pragma once

class Random {};

class TrueRandom : public Random {
public:
    static uint32_t NextUInt32() { return 0;}

};

class PseudoRandom : public Random {
public:
    static uint32_t NextUInt32() { }

};

class CoinTossing {
public:
    /// Flip again
    static bool Flip() {
        return TrueRandom::NextUInt32() & 1;
    }

};

#endif // RANDOM_H
