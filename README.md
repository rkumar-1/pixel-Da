# pixel-Da

Intro 

When C++11 standard introduced 'thread' as an abstraction in C++ for the first time and many knew this support was long due. The good news is the language's support for thread abstractions continues to evolve.

In C++17 standard, users can set 'parallel stl' as an execution policy to algorithms where it applies. With C++20 standard the evolution continues. C++20 allows composition of asynchronous tasks into a 'Work flow'.

The Parallel Dance

The Dancing Pixel (pixel-da) project researches application level access to parallel processing on multi-core systems. Simplifying the Application level access to parallel processing is the goal.  The aim here is to to dance with the Operating system scheduler to get access to the hardware threads. This is then benchmarked to understand performance.

We can use simple primitives such as setting thread affinity and process affinity and gain control and assign CPU resources to needy application level compute and IO tasks. But, does this application level knowledge help us to perform better than the OS scheduler? What else can we leverage?

The quest to discover simple primitives and techniques to effectively provision and divide the work between multiple cores makes this project interesting. One suspects that this needs to be codified into an Application framework.

The initial build of Dancing pixel (pixel-da) is a simple collection of data strutures that get benchmarked vs stl and parallel stl.
