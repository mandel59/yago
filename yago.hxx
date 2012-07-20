#ifndef YAGO_H
#define YAGO_H

#include <cmath>
#include <functional>
#include <list>
#include <vector>
#include <utility>

namespace yago
{

typedef double time;

constexpr float twopi = 6.28318531f;

template <typename T>
class SignalElement
{
public:
    virtual ~SignalElement() {}
    virtual void signal(const yago::time t, const int sample_rate, std::vector<T>& buffer) {}
};

class Oscillator : SignalElement<float>
{
    typedef std::function<float (float)> wave_func;
    typedef std::function<float (yago::time)> freq_func;
private:
    float _frequency;
    freq_func _freq_f;
    float _phase;
    wave_func _wave;
public:
    static float sine_wave(float phase)
    {
        return sin(twopi * phase);
    }
    Oscillator(const float frequency, const float phase = 0.0f, const wave_func wave = sine_wave) : _frequency(frequency), _freq_f(nullptr), _phase(phase - (int) phase), _wave(wave) {}
    Oscillator(const freq_func frequency, const float phase = 0.0f, const wave_func wave = sine_wave) : _frequency(0.0), _freq_f(frequency), _phase(phase - (int) phase), _wave(wave) {}
    void signal(const yago::time t, const int sample_rate, std::vector<float>& buffer);
    void set_frequency(const float frequency)
    {
        _frequency = frequency;
        _freq_f = nullptr;
    }
    void set_frequency(const freq_func frequency)
    {
        _freq_f = frequency;
    }
};

class Amplifier : SignalElement<float>
{
private:
    float _rate;
    float _limit;
public:
    Amplifier(const float rate, const float limit) : _rate(rate), _limit(limit) {}
    void signal(const yago::time t, const int sample_rate, std::vector<float>& buffer);
};

}
/* namespace yago */

#endif

