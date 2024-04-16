---
layout: page
title: "Milestone Report"
url: "https://daneengman.github.io/cache-network-simulator/milestone-report"
---


## Updated Schedule

### Past Weeks

#### Week 1 (March 27th-April 3rd)

Goal: Run basic traces on CADSS and integrate with a very simple
SystemVerilog network.

Actual Progress: Ran basic traces on CADSS, discussed with Tony how we
can modify for more advanced designs, experimented with a network design
in C++.

#### Week 2 (April 4th-April 10th)

Goal: Develop a more complete network in SystemVerilog and test its
integration with the simulator

Actual Progress: Completed ring simulator in C++,
experimented with integrating C++ with existing C
codebase. Made decision to switch back to SystemVerilog.

#### Week 3 (April 11th-April 17th)

Goal: Develop 3 basic networks and compare performance. Describe results
for midpoint result.

Actual Progress: Developed SystemVerilog server with
C++ DPI calls to socket functions, and a corresponding client
integrated into the CADSS simulator in C.
Integrated bus and ring networks. Updated CADSS interconnect
to support multiple in-flight messages.

### Future Weeks

#### Week 4 (April 18th-April 24th), Part 1

Dane: Update CADSS simulator to support OOO execution to more
accurately load network with traffic.

Yu-Ching: Write tree network in SystemVerilog.

#### Week 4 (April 18th-April 24th), Part 2

Dane: Update CADSS simulator to support other cache coherence
models (i.e. MESI) and analyze the difference on network traffic.

Yu-Ching: Modify networks to more accurately reflect messages (with
messages composed of individual flits) and support different techniques
(cut-through vs. buffering, etc.)

#### Week 5 (April 25th-May 1st), Part 1

Dane: Select traces that demonstrate notable trends in different network
interconnects and capacities. Write scripts or otherwise collect data
for final analysis.

Yu-Ching: Finish any desired network topologies and modifications.

#### Week 5 (April 25th-May 1st), Part 2

Both partners: Complete final analysis, add an additional analysis like
power analysis based on synthesis, prepare presentation.

#### Week 6 (May 2nd-May 6th)

Cushion time if other weeks take longer than expected, otherwise will be
spent refining analysis and presentation.

## Updated Poster Session Plans

We continue to plan to demonstrate the effects of different networks on
different traces, focusing on traces with high cache sharing that
induces higher network traffic. We will compare different networks along
with network parameters such as bandwidth and latency. To saturate the
network we hope to simulate OOO execution. We will focus on analysis for
the last weeks, comparing a variety of traces and how the trace's
characteristics lead to the results demonstrated in plots.

Our \"nice-to-haves\" are simulating the effects of different cache
coherence methods and how that works with different networks (does more
advanced cache coherence mean a cheaper or lower area interconnect can
be used?). We also hope to analyze power and area of our designs, and
put this in relative comparison with general CPUs, although we are
unsure if our simulator tools will be robust enough to support this.

## Setbacks and Challenges

We did not anticipate the difficulty in connecting
SystemVerilog to other languages, and we particularly
underestimated the difficulty in integrating with CMake.
Although we had some experience with CMake, we did not
realize the difficulties in running with our SystemVerilog
simulator, VCS. We briefly considered changing to a different
language, but decided our experience with SystemVerilog would
be more beneficial and would allow more accurate simulation without
turning the project into writing a simulator-writing project rather than
network analysis project.

## Future Issues and Concerns

We are most concerned with generating sufficient traffic for our network
for an interesting analysis, given the current in-order execution that
blocks on a memory request. We are interested in instead simulating an
Out-Of-Order processor with analysis only stretching to the memory level
(limiting the necessary complexity), but are unsure the difficulty of
this or if it is feasible.
