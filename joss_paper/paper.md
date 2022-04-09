---
title: 'WRENCH 2.0: Cyberinfrastructure simulation workbench'
tags:
  - C++
  - distributed computing
  - simulation
authors:
  - name: Henri Casanova ^[Co-first author] ^[Corresponding author]
    orcid: 0000-0001-6310-0365
    affiliation: "1"
  - name: Jesse McDonald
    affiliation: "1"
  - name: Loïc Pottier
    orcid: 0000-0002-7681-3521
    affiliation: "2"
  - name: Rafael Ferreira da Silva ^[Co-first author]
    orcid: 0000-0002-1720-0928
    affiliation: "3"
affiliations:
 - name: Information and Computer Sciences Dept., University of Hawai`i at Manoa
   index: 1
 - name: Information Sciences Institute, University of Southern California
   index: 2
 - name: National Center for Computational Sciences, Oak Ridge National Laboratory
   index: 3
date: 1 May 2022
bibliography: paper.bib

---

# Summary

Computer Science researchers in the field of parallel and distributed
computing typically need to conduct large experimental campaigns to
validate hypotheses and evaluate proposed approaches. These campaigns are
often labor-intensive (due to the need to develop, configure, and deploy
the required software stacks), and time- and energy-intensive (due to the need
to obtain statistically significant numbers of experimental results that
are never perfectly reproducible on real-world platforms). Furthermore,
experimental scenarios are limited to those platforms configurations
available to the researcher, thus making it difficult to explore a range of
scenarios that span current, upcoming and/or hypothetical platform
settings. One way to side-step these difficulties and constraints is to use
*simulation*.  The objective of the WRENCH framework is to provide
high-level abstractions and corresponding APIs to make it straightforward
to implement simulators of complex experimental scenarios that are accurate
and scalable.


# Statement of Need

Over the last couple of decades, many frameworks have been developed that
can be used to build simulators of parallel and distributed computing
applications, runtime systems, and platforms [@tikir_europar09]
[@hoefler_lsap10] [@gridsim] [@cloudsim] [@icancloud] [@dissect_cf]
[@cloudnetsimplusplus] [@fognetsimplusplus] [@simgrid] [@ROSS],
some of which are being actively developed and have garnered sizable user
communities among Computer Science researchers.
These frameworks differ drastically in terms of
simulation accuracy, simulation scalability, and easy-of-use. Simulation
accuracy should be the overriding user concern, and yet some popular
(because they are easy to use) simulation frameworks have been shown to
suffer from poor accuracy. Each framework makes different design choices
for simulation models, thus achieving different trade-offs between
scalability and accuracy. At one end of the spectrum are "microscopic
models" that aim to capture most low-level behavior (e.g., packet-level
network simulation, cycle-accurate CPU simulation) but as a result can
suffer from high time- and space-complexity, which hinders scalability.  At
the other end are "macroscopic models" that abstract away most low-level
behavior, typically via mathematical models and can thus suffer from poor
accuracy.

The SimGrid project [@simgrid] has placed a large emphasis on both simulation accuracy
and simulation scalability, which have been achieved via state-of-the-art
macroscopic models that have been validated extensively and implemented
efficiently. These models are sufficiently scalable that complex simulations
can be executed relatively quickly on a single core. SimGrid provides
foundational simulation abstractions for building simulators for a broad
range of applications, runtime systems, and hardware platforms.
Essentially, it provides the necessary abstractions for simulating the
execution sequential processes that run on compute resources and that can
communicate by exchanging messages over network paths.  While widely
applicable, these abstractions are low-level.  As a result, implementing
SimGrid simulators for complex scenarios can be labor-intensive.
Furthermore, many SimGrid users end up re-implementing essentially the same
simulation components. There is thus a clear need for higher-level
simulation abstractions that make it straightforward and low-labor to
implement simulators of complex scenarios, but that build on SimGrid's
low-level abstractions so as to achieve simulation accuracy and
scalability. The WRENCH project [@casanova2020fgcs] was established to answer this need.



# Design and APIs

![WRENCH Design and APIs.\label{fig:wrench-architecture}](wrench-architecture.pdf){ width=85% }

Figure \ref{fig:wrench-architecture} depicts the overall WRENCH software
architecture. At the bottom is SimGrid, which, as explained in the previous
section, provides all foundational simulation abstractions as well as ways
to describe a physical platform to simulate.  Using SimGrid's S4U API,
WRENCH implements a number of simulated "core services." These correspond
to software services that are commonly deployed on hardware resources to
make it possible to use these resources for performance computation,
storing and serving data, monitoring network load, keeping track of data
replicas, etc.  A simulator specifies which particular services are
deployed on which simulated hardware resources, and configure the behavior
of these services. For instance, the simulated platform could be comprised of a
cluster, and the simulator could specify that this cluster is managed by a
batch service that provides access to the compute nodes in the cluster
using some batch scheduling algorithm.  WRENCH then provides an API, called
the "Developer API" by which a user can implement a simulated runtime
system that executes an application workload using the core services
deployed on the hardware platform.  WRENCH was initially designed
specifically to simulate the execution of scientific workflow applications.
The Developer API in WRENCH v2.0 has been made more general-purpose and the
application workload can consist of arbitrary sets of independent and/or
dependent actions to be performed on the deployed services.  Finally, using
the "User API", in a few lines of code one can initialize the simulated
execution of a workflow with a runtime system using deployed services on the
hardware platform, launch the simulation, and process the simulation
output (which consists of time-stamped simulation event traces).

# Software

WRENCH v2.0 was released in April 2022. The code is hosted on GitHub at
[@wrenchgithub] and consists of C++ libraries, tool programs, and example
programs. All information regarding the project including documentation
is at [https://wrench-project.org/](https://wrench-project.org/).  Note that
WRENCH is not only used for Computer Science research purposes, but also
for education as it provides the basis for the simulation-driven
pedagogic modules for the [EduWRENCH](https://eduwrench.org) project.
WRENCH has been actively developed for over 4 years with a software release
every 4 months on average. Unit testing is implemented using Google Tests
and code coverage has been between 80% and 90% for several years.
Continuous Integration is performed on every push to the master branch
using Docker images for a variety of OS and compiler versions. The main
current development effort targets the implementation of a simulation REST
API on top of which thin APIs for programming languages other than C++ can
be quickly developed, starting with Python3.


# Acknowledgments

This work is currently funded by NSF awards 2106059, 2106147, 2103489,
and 2103508.

# References
