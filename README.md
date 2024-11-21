# mstd - Mopo3ob Standard Utilities
## What is this?
mstd is an expanding collection of boilerplate that I use across a range of projects.

## Misc
#### primitive.h
Contains aliases for primitive types for size gurantees.
#### errorText.h
Contains color coded messages using ansi escape codes. 

## Memory
#### allocator.hpp
Contains wrappers for C-style procedural allocators. They have the ability to count allocations to check for leaks.
#### Arena.hpp
Defines an allocator that can quickly allocate memory, but must free everything at once.

## Geometry
#### VectorX.hpp
Defines a vector class with X components.

#### MatrixX.hpp
Defines an X by X matrix.

#### Rotor.hpp
I am fueled by my hatred for quaternions.
