#pragma once

#include <functional>
#include <random>

// TODO: fix random being non-uniform or something
// or don't :)

namespace pajlada {
namespace randomizer {

struct Randomizer {
    Randomizer(std::pair<int, int> intRange = {0, 500},
               std::pair<float, float> floatRange = {0, 1.f},
               std::pair<double, double> doubleRange = {0.0, 1.0})
        : rng(this->rd())
        , iDist(intRange.first, intRange.second)
        , fDist(floatRange.first, floatRange.second)
        , dDist(doubleRange.first, doubleRange.second)
    {
    }

    bool
    getBool()
    {
        return this->bDist(this->rng);
    }

    float
    getFloat()
    {
        return this->fDist(this->rng);
    }

    double
    getDouble()
    {
        return this->dDist(this->rng);
    }

    int
    getInt()
    {
        return this->iDist(this->rng);
    }

    std::string
    getString(std::string::size_type length = 10)
    {
        static const char charset[] = "0123456789"
                                      "abcdefghijklmnopqrstuvwxyz"
                                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static std::uniform_int_distribution<> strIntDist(0,
                                                          sizeof(charset) - 2);
        static auto getCharacter = [=]() -> char {
            return charset[strIntDist(this->rng)];
        };

        std::string ret;
        ret.reserve(length);
        std::generate_n(std::back_inserter(ret), length, getCharacter);

        return ret;
    }

private:
    std::random_device rd;
    std::mt19937 rng;

    std::uniform_int_distribution<int> iDist;
    std::uniform_real_distribution<float> fDist;
    std::uniform_real_distribution<double> dDist;
    std::bernoulli_distribution bDist;
};

}  // namespace randomizer
}  // namespace pajlada
