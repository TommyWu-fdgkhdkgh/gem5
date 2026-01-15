#include "learning_gem5/tommy/port_example_object.hh"

#include <iostream>

#include "base/trace.hh"
#include "debug/PortExampleObject.hh"

namespace gem5
{

PortExampleObject::PortExampleObject(const PortExampleObjectParams &params)
    : SimObject(params),
      event([this] { processEvent(); }, name()),
      cpu_port(params.name + ".cpu_side", this),
      mem_port(params.name + ".mem_side", this),
      req(std::make_shared<Request>()),
      blocked(false),
      is_atomic(params.is_atomic),
      send_packet(params.send_packet),
      times_left(params.times_left),
      first_latency(params.first_latency),
      atomic_latency(params.atomic_latency)
{ DPRINTF(PortExampleObject, "Hello World! From a SimObject!\n"); }

void
PortExampleObject::processEvent()
{
    DPRINTF(PortExampleObject, "Fire an event!\n");

    const RequestPtr &const_req = req;
    Packet pkt(const_req, Packet::makeReadCmd(const_req));
    if (is_atomic) {
        sendAtomicPacket(&pkt);
    } else {
        sendTimingPacket(&pkt);
    }
}

void
PortExampleObject::startup()
{
    if (send_packet) {
        schedule(event, first_latency);
    }
}

Port &
PortExampleObject::getPort(const std::string &if_name, PortID idx)
{
    panic_if(idx != InvalidPortID, "This object doesn't support vector ports");

    // This is the name from the Python SimObject declaration (SimpleMemobj.py)
    if (if_name == "cpu_side") {
        return cpu_port;
    } else if (if_name == "mem_side") {
        return mem_port;
    } else {
        // pass it along to our super class
        return SimObject::getPort(if_name, idx);
    }
}

/*
 *  PortExampleObject
 *  atomic part
 */
void
PortExampleObject::sendAtomicPacket(PacketPtr pkt)
{
    times_left--;

    Tick latency = mem_port.sendAtomic(pkt);
    DPRINTF(PortExampleObject, "processEvent latency : %d\n", latency);

    if (times_left > 0) {
        schedule(event, curTick() + latency);
    }
}
Tick
PortExampleObject::handleAtomicRequest(PacketPtr pkt)
{ return atomic_latency; }

/*
 *  PortExampleObject
 *  timing part
 */
void
PortExampleObject::sendTimingPacket(PacketPtr pkt)
{ mem_port.sendTimingPacket(pkt); }
bool
PortExampleObject::handleTimingRequest(PacketPtr pkt)
{
    if (processing_packet) {
        return false;
    }

    processing_packet = true;
    // schedule an event to release
}
bool
PortExampleObject::handleTimingResponse(PacketPtr pkt)
{
    panic("Unsupported function!");
    return false;
}

/*
 *  PortExampleObject
 *  functional part
 */
void
PortExampleObject::handleFunctional(PacketPtr pkt)
{ panic("Unsupported function!"); }

/*
 *  PortExampleObject
 *  misc part
 */
AddrRangeList
PortExampleObject::getAddrRanges() const
{
    panic("Unsupported function!");
    return mem_port.getAddrRanges();
}

void
PortExampleObject::sendRangeChange()
{ panic("Unsupported function!"); }

/*
 *  PortExampleObject::CPUSidePort
 *  atomic part
 */
Tick
PortExampleObject::CPUSidePort::recvAtomic(PacketPtr pkt)
{
    DPRINTF(PortExampleObject, "recv an atomic packet!\n");
    return owner->handleAtomicRequest(pkt);
}

/*
 *  PortExampleObject::CPUSidePort
 *  timing part
 */
void
PortExampleObject::CPUSidePort::trySendRetry()
{ panic("Unsupported function!"); }
bool
PortExampleObject::CPUSidePort::recvTimingReq(PacketPtr pkt)
{
    if (!owner->handleTimingRequest(pkt)) {
        needRetry = true;
        return false;
    } else {
        return true;
    }
}
void
PortExampleObject::CPUSidePort::recvRespRetry()
{ panic("Unsupported function!"); }

/*
 *  PortExampleObject::CPUSidePort
 *  functional part
 */
void
PortExampleObject::CPUSidePort::recvFunctional(PacketPtr pkt)
{ panic("Unsupported function!"); }

/*
 *  PortExampleObject::CPUSidePort
 *  misc part
 */
void
PortExampleObject::CPUSidePort::sendPacket(PacketPtr pkt)
{ panic("Unsupported function!"); }

AddrRangeList
PortExampleObject::CPUSidePort::getAddrRanges() const
{
    panic("Unsupported function!");
    return owner->getAddrRanges();
}

/*
 *  PortExampleObject::MemSidePort
 *  atomic part
 */
/*
 *  PortExampleObject::MemSidePort
 *  timing part
 */
void
PortExampleObject::MemSidePort::sendTimingPacket(PacketPtr pkt)
{
    // Note: This flow control is very simple since the memobj is blocking.
    panic_if(blockedPacket != nullptr, "Should never try to send if blocked!");

    // If we can't send the packet across the port, store it for later.
    if (!sendTimingReq(pkt)) {
        blockedPacket = pkt;
    }
}

bool
PortExampleObject::MemSidePort::recvTimingResp(PacketPtr pkt)
{
    panic("Unsupported function!");
    return false;
}

void
PortExampleObject::MemSidePort::recvReqRetry()
{ panic("Unsupported function!"); }

/*
 *  PortExampleObject::MemSidePort
 *  functional part
 */

/*
 *  PortExampleObject::MemSidePort
 *  misc part
 */
void
PortExampleObject::MemSidePort::recvRangeChange()
{ panic("Unsupported function!"); }

} // namespace gem5
