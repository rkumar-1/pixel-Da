# pixel-Da

Intro 

C++11 standard introduced 'thread' as an abstraction and many knew this support was long due. The good news is this support is evolving into 'parallel stl' in C++17 standard and even more parallel processing abstractions in C++20 standard. 

The Dancing Pixel (pixel-da) project researches application level access to parallel processing on multi-core systems utilizing simple primitives such as setting thread affinity to CPU cores and Process affinity. This is non-tirvial and you have to dance with the Operating system scheduler to get access to the hardware threads.

The goal here is to simplify the Application level access to parallel processing through a framework and benchmark to understand the performance. The task is complicated by the presence of sahred Caches between the CPU cores as well as network and storage bound IO.

The initial build of Dancing pixel (pixel-da) is a simple collection of data strutures that get benchmarked vs stl and parallel stl.
