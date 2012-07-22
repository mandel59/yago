#ifndef _YAGO_FUNCTIONAL_HXX
#define _YAGO_FUNCTIONAL_HXX

namespace yago
{

template <typename Range>
class FunctionalElement : SignalElement<Range>
{
    typedef std::function<float (yago::time, float)> signal_func;
private:
    signal_func _func;
public:
    FunctionalElement(const signal_func f) : _func(f) {}
    void signal(yago::time t, float sample_rate, Range& buffer)
    {
        double delta_t = 1.0 / sample_rate;
        for (float& sample : buffer)
        {
            sample = _func(t, sample);
            t += delta_t;
        }
    }
};

}
/* namespace yago */

#endif

