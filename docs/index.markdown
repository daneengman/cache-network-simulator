---
layout: page
title: "Project Proposal"
---

# Website URL

https://daneengman.github.io/cache-network-simulator/

# Summary

We plan to augment Professor Railing's Computer Architecture Design
Simulator for Students by developing a cycle-accurate network topology
simulator that can simulate how cache coherency messages would propagate
about the network. We plan to use this We will write the network
simulator in SystemVerilog and integrate it into the existing C++
framework by using the SystemVerilog DPI.

# Background

The network topology of a cache interconnect is an important
microarchitectual feature that will influence performance during various
cache transactions, but the exact ways that different topologies might
affect performance is unclear. The CADSS is a lightweight architecture
simulator that will allow us to easily integrate our network simulator
without facing the complexities of a more complex simulator like Gem 5.

SystemVerilog is a hardware description and verification language which
we will use to describe the network. It implicitly supports constructs
of timing and and parallelism that are not present in software
languages, and will allow us to integrate our simulation with other
tools that can measure power, area and other requirements.

# Challenges

We will need to learn how to use the SystemVerilog DPI to interact with
the C++ simulator and accurately reflect performance benefits and trade
offs.

We will also need to develop a variety of network topologies to test
performance with. Given that we are working with a HDL we will need to
handle correctness issues and a level of parallelism that is very high
if we want to accurately represent high performance topologies.

# Resources

As noted before, we will use the CADSS along with SystemVerilog and its
DPI. We additionally hope to use some of Professor Railing's traces to
test the performance of different designs.

# Goals and Deliverables

## Plan to Achieve

We expect to achieve:

1.  Design and integrate interface between the CADSS and an arbitrary
    network for sending cache-coherence messages

2.  Test design with simple crossbar network with no latency

3.  Design at least 3 different networks (Bus, ring, torus) and compare
    performance between different designs

## Hope to Achieve

We hope to achieve:

1.  More advanced networks such as bufferless networks, \"fat trees\"
    with greater bandwidth near root, multi-stage networks

2.  Perform energy and power analysis of different topologies using
    synthesis tools

3.  Try different cache coherence methodologies such as MESI, MOESI to
    see how different interconnects work with different workload
    coherence management patterns

## Plans for Demonstration

We hope to present well defined graphs demonstrating our different
networks, along with designs for how they might be implemented in
hardware. We also plan to present graphs demonstrating the effects of
different interconnects on cache and overall compute performance using
our simulator.

## Analysis We Hope to Complete

Our primary goal is to analyze how different topologies affect the speed
of a multi-core workload with communication. We plan to use traces from
Professor Railing, along with potentially developing our own traces, and
find how different interconnects affect 1. the amount of time the cache
is waiting for messages to connect and 2. how much the overall trace
speeds up based on the topology being used.

# Platform Choice

We are using CADSS because although it does not offer the robustness and
research quality results of more complex simulators like Gem 5, it will
allow us to quickly start focusing on our problem rather than learning
to use the simulator.

We are using SystemVerilog because it is a language we are familiar with
and it allows us to easily and directly express the levels of
parallelism needed in describing a network. It will also allow us to
experiment with synthesis and power consumption.

# Schedule

1.  Week 1: Run basic traces on CADSS and integrate with a very simple
    SystemVerilog network

2.  Week 2: Develop a more complete network in SystemVerilog and test
    its integration with the simulator

3.  Week 3: Develop 3 basic networks and compare performance. Describe
    results for midpoint result.

4.  Week 4: Develop a more advanced network or pairs of networks to
    compare.

5.  Week 5: Finish any other topologies. Perform synthesis analysis on
    power and area. Compare performance and develop final report.
