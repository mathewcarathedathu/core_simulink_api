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

Each block and subsystem may have one of more inputs and outputs, which may flow unrestricted in any directions (i.e) feedback loops are allowed. 

# System architecture

## Block

Each block can have any number of input and output signals. For the sake of simplicity, I am going to set a max value, but allocate the memory for the input and output dynamically. 

In addition to that, there are some common members all blocks should have. For eg, the function definition, the run function, the ability to turn off the automatic run capablity but instead run only on a call from an external source, say a scheduler runnig off a master clock, for eg.. 

For the moment, lets assume that all input and output types are floats. In the future, it will be need to be changed to a template
## Model
Initial impressions indicate that subsystems and models be defined as a bidirectional graph. More details to be fleshed out as the development progresses.

