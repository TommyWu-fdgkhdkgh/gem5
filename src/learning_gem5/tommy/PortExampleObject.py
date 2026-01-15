from m5.params import *
from m5.SimObject import SimObject


class PortExampleObject(SimObject):
    type = "PortExampleObject"
    cxx_header = "learning_gem5/tommy/port_example_object.hh"
    cxx_class = "gem5::PortExampleObject"

    cpu_side = ResponsePort("CPU side port, receives requests, sink")
    mem_side = RequestPort("Memory side port, sends requests, source")

    is_atomic = Param.Bool(True, "use atomic memory protocol")
    send_packet = Param.Bool(True, "this example object need to send packet")
    times_left = Param.Int("3", "how many transaction we want to generate")
    first_latency = Param.Latency("1ns", "latency of first event")
    atomic_latency = Param.Latency("1ns", "latency of atomic access")
