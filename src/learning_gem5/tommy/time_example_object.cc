#include "learning_gem5/tommy/time_example_object.hh"

#include <iostream>

#include "base/trace.hh"
#include "debug/TimeExampleObject.hh"

namespace gem5
{

TimeExampleObject::TimeExampleObject(const TimeExampleObjectParams &params)
    : SimObject(params),
      event([this] { processEvent(); }, name()),
      latency(params.latency),
      timesLeft(params.times_lelft)
{ DPRINTF(TimeExampleObject, "Hello World! From a SimObject!\n"); }

void
TimeExampleObject::processEvent()
{
    timesLeft--;
    DPRINTF(TimeExampleObject, "Processing the event! %d left\n", timesLeft);

    if (timesLeft <= 0) {
        DPRINTF(TimeExampleObject, "Last event !\n");
    } else {
        schedule(event, curTick() + latency);
    }
}

void
TimeExampleObject::startup()
{ schedule(event, 100); }

} // namespace gem5
