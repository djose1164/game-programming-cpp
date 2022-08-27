#include "utils/random.h"

void Random::init()
{
    std::random_device rd;
    Random::seed(rd());
}

void Random::seed(unsigned seed)
{
    generator_.seed(seed);
}

float Random::get_float()
{
    get_float_range(0.f, 1.f);
}

float Random::get_float_range(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(generator_);
}

int Random::get_int_range(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(generator_);
}

Vector2 Random::get_vector(const Vector2 &min, const Vector2 &max)
{
    auto r = Vector2(get_float(), get_float());
    return min + (max - min) * r;
}

Vector3 Random::get_vector(const Vector3 &min, const Vector3 &max)
{
    auto r = Vector3(get_float(), get_float(), get_float());
    return min + (max - min) * r;
}

std::mt19937 Random::generator_;
