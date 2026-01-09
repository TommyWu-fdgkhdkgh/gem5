import argparse

import m5
from m5.objects import *

# -------------- options -------------- #
parser = argparse.ArgumentParser()
parser.add_argument(
    "--example-number",
    action="store",
    type=int,
    default=5,
    help="An example number",
)

args = parser.parse_args()
# ------------------------------------- #

print("test print in the configuration file!")

root = Root(full_system=False)

root.example = ExampleObject()
root.example.number = args.example_number

m5.instantiate()

print("Beginning simulation!")
exit_event = m5.simulate()
print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")
