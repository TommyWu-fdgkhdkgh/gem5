#ifndef __EXAMPLE_OBJECT_HH__
#define __EXAMPLE_OBJECT_HH__

#include "params/ExampleObject.hh"
#include "sim/sim_object.hh"

namespace gem5
{

class ExampleObject : public SimObject
{
  public:
    ExampleObject(const ExampleObjectParams &p);
};

} // namespace gem5

#endif // __EXAMPLE_OBJECT_HH__
