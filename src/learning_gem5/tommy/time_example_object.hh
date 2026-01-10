#ifndef __TIME_EXAMPLE_OBJECT_HH__
#define __TIME_EXAMPLE_OBJECT_HH__

#include "params/TimeExampleObject.hh"
#include "sim/sim_object.hh"

namespace gem5
{

class TimeExampleObject : public SimObject
{
  private:
    void processEvent();
    EventFunctionWrapper event;
    const Tick latency;
    int timesLeft;

  public:
    TimeExampleObject(const TimeExampleObjectParams &p);
    void startup() override;
};

} // namespace gem5

#endif // __TIME_EXAMPLE_OBJECT_HH__
