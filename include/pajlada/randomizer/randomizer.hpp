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
        : rng(std::random_device{}())
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
    getString(unsigned length = 10)
    {
        static const char charset[] = "0123456789"
                                      "abcdefghijklmnopqrstuvwxyz"
                                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static constexpr size_t maxCharsetIndex = sizeof(charset) - 1;
        static std::uniform_int_distribution<> strIntDist(0, maxCharsetIndex);
        static auto getCharacter = [=](std::default_random_engine &r) -> char {
            return charset[strIntDist(r)];  //
            // return 'a';  //
        };

        std::string ret(length, 0);
        std::generate_n(ret.begin(), length,
                        std::bind(getCharacter, this->rng));

        return ret;
    }

private:
    std::default_random_engine rng;

    std::uniform_int_distribution<int> iDist;
    std::uniform_real_distribution<float> fDist;
    std::uniform_real_distribution<double> dDist;
    std::bernoulli_distribution bDist;
};

}  // namespace randomizer
}  // namespace pajlada
