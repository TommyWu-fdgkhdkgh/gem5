import argparse

import m5
from m5.objects import *

# -------------- options -------------- #
parser = argparse.ArgumentParser()
parser.add_argument(
    "--latency",
    action="store",
    dest="latency",
    required=False,
    default="1ns",
    help="latency between all the events",
)
parser.add_argument(
    "--times-left",
    action="store",
    dest="times_left",
    type=int,
    default=10,
    help="how times we want to trigger this event",
)

args = parser.parse_args()
# ------------------------------------- #

print("test print in the configuration file!")

root = Root(full_system=False)

root.example = TimeExampleObject()
root.example.latency = args.latency
root.example.times_lelft = args.times_left

# Change the global frequency from "1ps" to "1ns"
# m5.ticks.setGlobalFrequency("1ns")

m5.instantiate()

print("Beginning simulation!")
exit_event = m5.simulate()
print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")
