<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# Functional Nature

I did not create the library with any functional concepts in mind, mostly because I was oblivious to the relevant knowledge.
However, the idea of composing functions is natural and familiar, as passing a lambda expression to a standard algorithm is already prevalent.
The library is based on C++ facilities and explained in C++ terms.
It is not an attempt to implement functional syntax on top of a primarily imperative language.
Knowledge about functional languages is not necessary to use, contribute, or fully implement the library.
Functional analogs only serve as an illustration of the underlying logic.

Haskell is the language we will be using in this documentation.
Functional analogs will only serve as illustrations of the library's facilities and will not be explained in detail.
For example, while lambda calculus is the foundation of functional languages, we will not dive into this concept since our illustrations will be based on the high-level abstractions implemented by Haskell.

## Type Signature

The primary reason why we use Haskell is its type-check system. We will employ the system to validate our compositions.

Consider the following C++ code:

```C++
template<typename...>
struct Mold {};

template<auto...>
struct Page {};

template<template<typename...> class...>
struct Road {};

template<template<auto...> class...>
struct Rail {};

using MoldInt = Mold<int>;
// Fails since `int` does not match `auto`.
using PageInt = Page<int>;

using PageOne = Page<1>;
// Fails since `1` does not match `typename`.
using MoldOne = Mold<1>;

using RoadMold = Road<Mold>;
// Fails since `Mold` does not match `template<auto...> class`.
using RailMold = Rail<Mold>;

using RailPage = Rail<Page>;
// Fails since `Page` does not match `template<typename...> class`.
using RoadPage = Road<Page>;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCcpK4AMngMmAByPgBGmMT%2BAOykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHASYLCkGeyYAzG4EAJ4pjKyYAHQPp9gmGgCCs8ReDgDUALKe6G%2BJkSVkSABFTlY3i9XnsDkdMKc3EwvEQHncnjCPl8CN9lExgJggSDgRCTlDXjC4YcmMcztSEUjLtdmGx0U9vsgDAoFOyTs83tifgAlVBMQHA0FkilU/Y0unnOWMs4otGPfmc7m89UC94ET4iph0YlSyEwmFeDJGP4AgCSgiBJzBNto6CR4QImPJMIA9D7vgAxI20BTfK3bIEANg0HpM0e%2B6FQmFDDFQuJYtOQCCjGlVqDjGgxb0t4WAeIJmHtuNOzvxhPdgi9MuLVrLdcwAHkIo7axWkVwm77/UG6KHw0SCwP44nk99U%2BnM9mC8ybmwC0XXiXrf9XV2J06XW6zgP%2BWboS3S99ReKdxKD9ej25b4O3n7A8Gx%2BEIwXn9Okym02%2BDMCCzHMGVpREVVRVA%2BWwTUmB5dcLVbK9g1vHtULoJFn1Pb1z03FDhWDdsMKIrCznbF9XjfEcQzDL8J2jSi/1necgMXMClQgpkrlXe4dXgxDow3LcywfEiayvMVH0o3CLA4NZaE4ABWXg/A4LRSFQTg3Gsawww2LYJzME4eFIAhNAUtYAGsQGUwszECAAODQAmUpzIxOSRqkkSN9E4SReBYCQNA0Uh1M07SOF4BQQDCiyNIU0g4FgGBEBADYCBSVFyEoNADjoeJIluThVA8gBaSNJG%2BYBkGQb4pDuMxeEwfAiGIPB0D0fhBBEMR2CkGRBEUFR1ES0hdC4UgAHdiCYFJOB4RSVLUyytM4DtUWy3FUCob4ysjSrqtq%2BrGrMb4IA8Ar6GIIETK4FZeASrQ1ggJB8pSQqyAoCAPq%2BkBgCkMw%2BDoPZiFiiAYjWmJwmaC5Ft4GHmGIC4OxibQ6gSsz8rYQQu1oeHxqwGIvGAZFaBDBHSCwDMjHEIm8GITG8AAN2TNbMFUOpUR2MyPW6NbaDwGI5pRjwsDW/U8GC7heDZ4gYnSTAwX2QxgCFoxLLWKgDGABQADU8EwaaOxZKmeuEURxEGi2RrUNbJv0NWUD0yx9GF2LIDWVAUl6WKOHK2YjzBUxLGsMxIvljqsE9iA1lqepnAgVwpj8KbQgWcpKj0QpMgEVOc/SPOGCGLPRimhPen6SZPHaPRK4aOZS5GBIK7mAu24GZullb%2BPDO2CRlo4VTwrWqL9oqqqarqhrJCai7cEIEg7tMx7zK1tYEEwcVRjj0hbMkE47gCE5EkkDRvN80LlMjIIlI4QLSGC0y7kjLhIycgInPf5TJC4ZST5%2BQirwKKMU4rr0Sq9NKb0MpbRyj9P6N1ipsE4M0FgLNEjlSYPBa0XAAh3C4HcTSrUl7R26rIPq1tpC2yUPbcauhgazXmgjIeI9gHrQ4JtLKqJvi7W%2BGgjBWCcFljwQQohF0rqfRuivMwa9npJRgYg%2BIuVfqoGuqMARmCuRqzwVwMKNBaBgwhlDcaSM4ZUzMSjNGGMHBUxxowAg%2BNCaaWJqTcmlNZbU1VnTHYLjGbMzZv7YhXNkA8ypvze%2BmkhYizhuLXxT0OoyzMvLRWSgVa03VqWLWfBdYGyNibM2niLaUIGtQ2QdsxqaQYU7TWocrBu2ibHb2vssj%2B0DgQYOdTw6R3iNHdmXsug9CyC4Bg7ha55HTqM7u2cpq516B3VIRdejTPLoM5mAhq6tHGWnNZic%2BhN0zi3eu7dtnHK7ocnug91ibAHg9fyw9VrjXHpooR2jcH4MIRoBebVl7mFXk9DepAt47wSHve%2Bj9n74IvokABiREheTML5P%2Bo8nmcDAfFbJKV0qZW2iopRxBkE7DQVPFgCgWb1RZqIhEswWo/LIVNYpVtSlDXkLQypOgQAnBmnNBastWGPMihtOBO09rEuqqS8l3xKX4OpbiS6aipHxBXicORmL3oKq%2BnijVN0QDkpSCkAA%2BtKg1sqDVipBoY%2BIxjoawxRhY21qN0aYzsWo3GjiGAEzWq4smYgPFmRpmremfimb1ECRzEJYTPERMFsLUWFw4mS0SVTFJSt0mBqyZAnJBI8nG1Nowc2FCmUSDKcNNlDtOU1OMK7GwjT4DNL9pwH0QcXZh0sBHEBUdOr9L3g3JOKdTmTPQCs1uiyihZAWXMrIw767dHWfsgYCze3zpaNOzuNdcg7NmOcsoRy7kKH7gNflKLBUcH4cQFgJKyUUqpRBWY3zSErwegCyBm9t5YFBUPCF%2BQ7gnBOMpeyf9Qq/sSB/Y9IC0W2HAfIlYNkQCSHwXCjQeCL5cBOJGZSiQzC/3uScAV4HooQJekPZqYGOHPqI6QeWGRnCSCAA)

Restricted by C++ syntax,  we must declare the kind of parameters the template accepts inside its template head.

- The `Mold` accepts types, hence the `typename` and `...` inside `template<*>`.
- Similarly, the `Page` accepts values, hence the `auto` and `...` inside `template<*>`;
- the `Road` accepts containers, hence the `template<typename...> class` and `...` inside `template<*>`;
- the `Rail` accepts sequences, hence the `template<auto...> class` and `...` inside `template<*>`.