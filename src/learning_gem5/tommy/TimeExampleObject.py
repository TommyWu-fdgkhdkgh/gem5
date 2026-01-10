from m5.params import *
from m5.SimObject import SimObject


class TimeExampleObject(SimObject):
    type = "TimeExampleObject"
    cxx_header = "learning_gem5/tommy/time_example_object.hh"
    cxx_class = "gem5::TimeExampleObject"
    latency = Param.Latency("1ns", "latency between events")
    times_lelft = Param.Int(10, "how many times we want to trigger the events")
