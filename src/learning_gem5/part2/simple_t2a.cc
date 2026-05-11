#include "learning_gem5/part2/simple_t2a.hh"

#include "base/trace.hh"
#include "debug/SimpleT2A.hh"

namespace gem5
{

SimpleT2A::SimpleT2A(const SimpleT2AParams &params) :
    SimObject(params),
    cpuPort(params.name + ".cpu_side", this),
    memPort(params.name + ".mem_side", this)
{
}

Port &
SimpleT2A::getPort(const std::string &if_name, PortID idx)
{
    panic_if(idx != InvalidPortID, "This object doesn't support vector ports");

    // This is the name from the Python SimObject declaration (SimpleT2A.py)
    if (if_name == "mem_side") {
        return memPort;
    } else if (if_name == "cpu_side") {
        return cpuPort;
    } else {
        // pass it along to our super class
        return SimObject::getPort(if_name, idx);
    }
}

bool
SimpleT2A::MemSidePort::recvTimingResp(PacketPtr pkt)
{
  panic("unimpl.");
}

void
SimpleT2A::MemSidePort::recvReqRetry()
{
  panic("unimpl.");
}

void
SimpleT2A::MemSidePort::recvRangeChange()
{
    owner->sendRangeChange();
}

Tick
SimpleT2A::handleAtomic(PacketPtr pkt)
{
    return memPort.sendAtomic(pkt);
}

void
SimpleT2A::handleFunctional(PacketPtr pkt)
{
    // Just pass this on to the memory side to handle for now.
    memPort.sendFunctional(pkt);
}

AddrRangeList
SimpleT2A::getAddrRanges() const
{
    DPRINTF(SimpleT2A, "Sending new ranges\n");
    // Just use the same ranges as whatever is on the memory side.
    return memPort.getAddrRanges();
}

void
SimpleT2A::sendRangeChange()
{
    cpuPort.sendRangeChange();
}

} // namespace gem5
