#ifndef _YAGO_SIGELEM_HXX
#define _YAGO_SIGELEM_HXX

namespace yago
{

template <typename Range>
class SignalElement
{
protected:
    virtual ~SignalElement() {}
public:
    virtual void signal(yago::time t, float sample_rate, Range& buffer) {}
};

}
/* namespace yago */

#endif

