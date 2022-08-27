#ifndef RANDOM_H
#define RANDOM_H

#include "utils/Math.h"

#include <random>

class Random
{
public:
    static void init();

    static void seed(unsigned seed);

    static float get_float();
    static float get_float_range(float min, float max);

    static int get_int_range(int min, int max);

    static Vector2 get_vector(const Vector2 &min, const Vector2 &max);
    static Vector3 get_vector(const Vector3 &min, const Vector3 &max);

private:
    static std::mt19937 generator_;
};

#endif // RANDOM_H
