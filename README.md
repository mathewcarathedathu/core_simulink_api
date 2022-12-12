# Introduction

This project aims to fulfil the requirements of the take home task from Mathworks. 

The main aim of the task is to develop a set of classes and associated API to query the properties of the simulink model during compile time

Although the task calls for only the functions needed to answer queries, testing requirements dictate that the project have the capability to define blocks and subsystems and create models.
# Simulink Model fundamentals

A model can be decomposed using the following hierarchy

~~~
A model is composed of sub-systems

A subsystem is composed of one or more blocks.

Each block performs some function.
~~~

Each block and subsystem may have one of more inputs and outputs, which may flow unrestricted in any direction (i.e) feedback loops are allowed. 

# Project Organization

I used Visual Studio 2022 as my development environment. The project files are included in this repository. 

All of the essential code is written as hpp files. They are placed in the include directory. Examples of blocks created are placed in the include/blocks directory. A test script (also containing the main function) and set to be the entry point for the VS project is in the test directory.
# System architecture

The system is designed at multiple levels.

## Data Unit
This is the fundamental unit of data storage. For simplicity, I have assumed that all data is of type double. The data unit also contains an update index to determine relative age of the data

## Func unit
This is the base class for blocks and subsystems. Contains basic variable (like id, etc) and supporting functions. It also contains the input and output signal defintion.

## Block

Each block can have any number of input and output signals, which is set at run time. The block functionality is derived from the func unit and data unit classes and builds on top of it. 

## Subystems

This is similar to block, with slightly different methods serving functions specific to subsystems.

Since the question is asking only for the query functions, much attention wasn't paid towards this functionality. For eg. subsystem doesn't have a common input/output bus. And the nodes are run individually, not at the subsystem level.

## Graph Edges
 The mechnism for transfer of data are represented as graph edges. In this implementation, the input port of each block is pointed to the memory location of the output port of the parent.
## Model
 This brings everything together. The nodes (blocks and subsystems) are held together using a graph topology. The list of nodes are stored and a map of connections between them are used to define the replationships. Currently blocks and subsystems are treated differently. 

Initial impressions indicate that subsystems and models be defined as a bidirectional graph. More details to be fleshed out as the development progresses.

# Scope for improvment

Although I have completed the tasks listed, I felt that there is a lot of scope for improvement. An incomplete list includes

1. Right now the model assumes that all ports are connected and that there are no dangling edges. A check can be instituted. 

2. Right now data transfer between nodes occurs at the memory level. Although in the execution mode I have defined it will work well, it wont hold up in an asynchronous environment. For e.g, in a case where each node is running at its own independent rate, this implementation is ripe for memory access errors. Although using mutex operations is the obvious choice, a better option may be to use double buffers as we can better ensure availability of memory locations. 

3. Subsystems are currently just assumed to be a big box over a group of blocks. A better implementation is to use subsystems as black boxes with the model having no visibility into the inner block architecture and functioning. The memory needed for this is already allocated in my implementation, just not fully implemented. 

4. All the fuctionality needed for a typical Simulink user workflow has not been implemented. That is a big area for improvement. 

