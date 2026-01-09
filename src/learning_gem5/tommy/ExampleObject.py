from m5.params import *
from m5.SimObject import SimObject


class ExampleObject(SimObject):
    type = "ExampleObject"
    cxx_header = "learning_gem5/tommy/example_object.hh"
    cxx_class = "gem5::ExampleObject"
    number = Param.Int(0, "test number")
