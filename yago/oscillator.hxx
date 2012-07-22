#ifndef _YAGO_OSCILLATOR_HXX
#define _YAGO_OSCILLATOR_HXX

namespace yago
{

template <typename Range>
class Oscillator : SignalElement<Range>
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

    Oscillator(float frequency, float phase = 0.0f, const wave_func wave = sine_wave)
        : _frequency(frequency), _freq_f(nullptr), _phase(phase - (int) phase), _wave(wave) {}

    Oscillator(const freq_func frequency, float phase = 0.0f, const wave_func wave = sine_wave)
        : _frequency(0.0), _freq_f(frequency), _phase(phase - (int) phase), _wave(wave) {}

    void signal(yago::time t, float sample_rate, Range& buffer)
    {
        const double delta_t = 1.0 / sample_rate;
        const float delta_phase = _frequency * delta_t;

        float phase = _phase;

        for (float& sample : buffer)
        {
            sample = _wave(phase);
            if (_freq_f != nullptr)
            {
                phase += _freq_f(t) * (float) delta_t;
            }
            else
            {
                phase += delta_phase;
            }
            if (phase >= 1.0f) phase -= (int) phase;
            t += delta_t;
        }

        _phase = phase;
    }

    void set_frequency(float frequency)
    {
        _frequency = frequency;
        _freq_f = nullptr;
    }

    void set_frequency(const freq_func frequency)
    {
        _freq_f = frequency;
    }

};

}
/* namespace yago */

#endif

