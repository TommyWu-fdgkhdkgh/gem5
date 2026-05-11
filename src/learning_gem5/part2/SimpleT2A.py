from m5.params import *
from m5.SimObject import SimObject


class SimpleT2A(SimObject):
    type = "SimpleT2A"
    cxx_header = "learning_gem5/part2/simple_t2a.hh"
    cxx_class = "gem5::SimpleT2A"
    cpu_side = ResponsePort("CPU side port, receives requests")
    mem_side = RequestPort("Memory side port, sends requests")
