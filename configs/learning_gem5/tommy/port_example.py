import argparse

import m5
from m5.objects import *

# -------------- options -------------- #
parser = argparse.ArgumentParser()
parser.add_argument(
    "--mem-protocol",
    action="store",
    dest="mem_protocol",
    required=False,
    default="atomic",
    choices=["atomic", "timing"],
    help="type of the memory protocol",
)
args = parser.parse_args()
# ------------------------------------- #

root = Root(full_system=False)

root.port_example_1 = PortExampleObject()
root.port_example_2 = PortExampleObject()

if args.mem_protocol == "atomic":
    root.port_example_1.first_latency = "2ns"
    root.port_example_2.first_latency = "3ns"

    root.port_example_1.atomic_latency = "5ns"
    root.port_example_2.atomic_latency = "6ns"

    root.port_example_2.send_packet = False

else:
    root.port_example_1.is_atomic = False
    root.port_example_2.is_atomic = False

    root.port_example_1.first_latency = "2ns"
    root.port_example_2.first_latency = "3ns"

    root.port_example_2.send_packet = False

root.port_example_1.mem_side = root.port_example_2.cpu_side
root.port_example_1.cpu_side = root.port_example_2.mem_side

m5.instantiate()

print("Beginning simulation!")
exit_event = m5.simulate()
print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")
