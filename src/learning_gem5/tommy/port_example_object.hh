#ifndef __PORT_EXAMPLE_OBJECT_HH__
#define __PORT_EXAMPLE_OBJECT_HH__

#include "mem/packet.hh"
#include "mem/port.hh"
#include "params/PortExampleObject.hh"
#include "sim/sim_object.hh"

namespace gem5
{

class PortExampleObject : public SimObject
{
  private:
    void processEvent();
    EventFunctionWrapper event;

    // XXX
#if 0
    void process_request_done();
    EventFunctionWrapper process_request_event;

    void process_response_done();
    EventFunctionWrapper process_response_event;
#endif

    class CPUSidePort : public ResponsePort
    {
      private:
        PortExampleObject *owner;
        bool needRetry;
        PacketPtr blockedPacket;

      public:
        CPUSidePort(const std::string &name, PortExampleObject *owner)
            : ResponsePort(name),
              owner(owner),
              needRetry(false),
              blockedPacket(nullptr)
        {}
        void sendPacket(PacketPtr pkt);
        AddrRangeList getAddrRanges() const override;
        void trySendRetry();

      protected:
        Tick recvAtomic(PacketPtr pkt) override;
        void recvFunctional(PacketPtr pkt) override;
        bool recvTimingReq(PacketPtr pkt) override;
        void recvRespRetry() override;
    };

    class MemSidePort : public RequestPort
    {
      private:
        PortExampleObject *owner;
        PacketPtr blockedPacket;
        int times_left;

      public:
        MemSidePort(const std::string &name, PortExampleObject *owner)
            : RequestPort(name), owner(owner), blockedPacket(nullptr)
        {}
        void sendTimingPacket(PacketPtr pkt);

      protected:
        bool recvTimingResp(PacketPtr pkt) override;
        void recvReqRetry() override;
        void recvRangeChange() override;
    };

    CPUSidePort cpu_port;
    MemSidePort mem_port;

    void sendAtomicPacket(PacketPtr pkt);
    void sendTimingPacket(PacketPtr pkt);
    Tick handleAtomicRequest(PacketPtr pkt);
    bool handleTimingRequest(PacketPtr pkt);
    bool handleTimingResponse(PacketPtr pkt);
    void handleFunctional(PacketPtr pkt);
    AddrRangeList getAddrRanges() const;
    void sendRangeChange();

    RequestPtr req;
    bool blocked;
    bool is_atomic;
    bool send_packet;
    int times_left;
    const Tick first_latency;
    const Tick atomic_latency;

    bool processing_packet;

  public:
    PortExampleObject(const PortExampleObjectParams &p);
    void startup() override;
    Port &getPort(const std::string &if_name,
                  PortID idx = InvalidPortID) override;
};

} // namespace gem5

#endif // __PORT_EXAMPLE_OBJECT_HH__
