# pixel-Da

Intro 

When C++11 standard introduced 'thread' as an abstraction in C++ for the first time, many knew this support was long due. The good news is the language's support for thread abstractions continues to evolve.

In C++17 standard, users can set 'parallel stl' as an execution policy to the algorithms where it applies. With C++20 standard the evolution continues. In C++11, you cannot compose a set of tasks into a work flow. This changes with C++20 which allows a composition of tasks.

The Parallel Dance

The Dancing Pixel (pixel-da) project researches application level access to parallel processing on multi-core systems. The aim here is to utilizeg simple primitives such as setting thread affinity to CPU cores and Process affinity and to dance with the Operating system scheduler to get access to the hardware threads. This is then benchmarked to understand performance.

The goal here is to simplify the Application level access to parallel processing through a framework. The task is complicated by the presence of shared Caches between the CPU cores as well as network and storage bound IO.

The initial build of Dancing pixel (pixel-da) is a simple collection of data strutures that get benchmarked vs stl and parallel stl.
