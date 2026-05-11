#ifndef __LEARNING_GEM5_PART2_SIMPLE_MEMOBJ_HH__
#define __LEARNING_GEM5_PART2_SIMPLE_MEMOBJ_HH__

#include "mem/tport.hh"
#include "mem/port.hh"
#include "params/SimpleT2A.hh"
#include "sim/sim_object.hh"

namespace gem5
{

class SimpleT2A : public SimObject
{
  private:
    class CPUSidePort : public SimpleTimingPort
    {
      protected:
        SimpleT2A *owner;
        Tick recvAtomic(PacketPtr pkt) override
        {
            return owner->handleAtomic(pkt);
        }	

	AddrRangeList
        getAddrRanges() const override
	{
            return owner->getAddrRanges();
	}
      public:
        CPUSidePort(const std::string& name, SimpleT2A *owner) :
            SimpleTimingPort(name, owner), owner(owner)
        { }
    };

    class MemSidePort : public RequestPort
    {
      private:
        SimpleT2A *owner;

      public:
        MemSidePort(const std::string& name, SimpleT2A *owner) :
            RequestPort(name), owner(owner) { }

      protected:
        bool recvTimingResp(PacketPtr pkt) override;
        void recvReqRetry() override;
        void recvRangeChange() override;
    };

    Tick handleAtomic(PacketPtr pkt);
    void handleFunctional(PacketPtr pkt);

    /**
     * Return the address ranges this memobj is responsible for. Just use the
     * same as the next upper level of the hierarchy.
     *
     * @return the address ranges this memobj is responsible for
     */
    AddrRangeList getAddrRanges() const;

    /**
     * Tell the CPU side to ask for our memory ranges.
     */
    void sendRangeChange();
    CPUSidePort cpuPort;
    MemSidePort memPort;
  public:
    SimpleT2A(const SimpleT2AParams &params);
    Port &getPort(const std::string &if_name,
                  PortID idx=InvalidPortID) override;
};

} // namespace gem5

#endif // __LEARNING_GEM5_PART2_SIMPLE_MEMOBJ_HH__
