#ifndef _YAGO_HXX
#define _YAGO_HXX

#include <cmath>
#include <functional>
#include <limits>
#include <utility>

namespace yago
{

typedef double time;
constexpr float twopi = 6.28318531f;

}

#include <yago/sigelem.hxx>

#include <yago/functional.hxx>

#include <yago/envelop.hxx>
#include <yago/oscillator.hxx>

namespace yago
{

template <typename Range>
class Distortion : SignalElement<Range>
{
private:
    float _gain;
    float _limit;
public:
    Distortion(float gain, float limit) : _gain(gain), _limit(limit) {}
    void signal(const yago::time t, const float sample_rate, Range& buffer)
    {
        for (float& sample : buffer)
        {
            sample *= _gain;
            if (sample > _limit) sample = _limit;
            else if (sample < -_limit) sample = -_limit;
        }
    }
};

template <typename Range>
class OverDrive : SignalElement<Range>
{
private:
    float _gain;
    float _limit;
public:
    OverDrive(float gain, float limit) : _gain(gain), _limit(limit) {}
    void signal(const yago::time t, const float sample_rate, Range& buffer)
    {
        float rlimit = 1.0f / _limit;
        for (float& sample : buffer)
        {
            if (sample > 0.0f)
                sample = _limit * tanh(rlimit * _gain * sample);
            else
                sample = _gain * sample;
        }
    }
};

}

/* namespace yago */

#endif

