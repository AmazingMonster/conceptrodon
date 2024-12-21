<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Reveal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-reveal">To Index</a></p>

## Description

`Pagelivore::Reveal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and becomes its type result.
Overall, `Reveal` turns a `Typical` operation into its non-prefixed counterpart.

<pre><code>   Operation
-> using Mold&lt;***&gt; = Operation&lt;***&gt;::type</code></pre>

## Type Signature

```Haskell
Reveal
 :: template<auto...> class... 
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class...> class>
struct Reveal
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will reveal `Operation`.

```C++
template<auto...>
struct Shuttle;

template<auto...Args>
struct Operation
{ using type = Shuttle<Args...>; };

using SupposedResult = Shuttle<0, 1, 2, 2>;

template<auto...Args>
using Metafunction = Reveal<Operation>
::Page<Args...>;

using Result = Metafunction<0, 1, 2, 2>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Pagelivore::Reveal`:

```C++
template<template<auto...> class Operation>
struct Reveal
{
    template<auto...Variables>
    using Page = Operation<Variables...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgOykrgAyeAyYAHI%2BAEaYxBIapAAOqAqETgwe3r4ByanpAqHhUSyx8VyJdpgOGUIETMQEWT5%2BXIFVNQJ1DQRFkTFxCbb1jc05bcM9fSVlCQCUtqhexMjsHASYLEkGGyYAzG4bWzuY%2B25MXkQAdDf72ADUyAYKCvcA8klxTI4CdyYaAEEFARiF4HPcAEqYABumDE/wBJn8VkB9zR9yO22%2BpwOF2uNwAag08ExovQFH9UeivGkjPdlExgJh7vsACLvT7Eb4ZM5E4gksmYBQ3K53EAgAgAT0%2B%2BxRiP8rNlCIRAHoAFQazVa7Uq1Va%2B4AFSFBFeWt1gPV2qtmvNiMB5j2YSeXiwLIOaAYqySJspdoBmJOZzxqBFvuBoPBQgQlwI9CV9sBAexQcuIZuAOIwApe2wCPDYIIHK%2BPwYyuR9xpYWAGOlzLZ9yjMbjBwzWdDOdlLIV8b9lbpQi8SRSSnQUIUXlohfrjYIsZxbkS9y4pHuZhXZj%2BezlCKTu1xqZFrezucBferAFlMPUqF5PSW3eyobD4QcPsWeR3AeKGUyzkf27mW7KqetLVmOE5Tns7KXtet6dKWByLsuq7rpu26AsC3LIAA%2BkwLxxAQEDAug4oKKwmC4dmbjgZOK4DkOqSYKOQoQXccyyhwCy0JwACsvB%2BBwWikKgnBuNY1j3AoSwrHWZh7DwpAEJonELAA1iAPGSFcGiSG0ewaDxGhmAAbMZZgABzmfonCSLwLAJIkAlCSJHC8AoICJEpgmcaQcCwDAiAgEsBBJJc5CUGgWx0HEETkZwqjmcZAC0xmSPcwDIMgS5aWYvBMYQJB4CRy78IIIhiOwUgyIIigqOo3mkLoy4AO5ckknA8FxvH8cpwmcG8lyhYWqBUPcCXJal6WZdlVxmPcEAeFF9DECyclcHMvBeVoCwQEgkVJNFZAUBA%2B2HSAwBSGuNCTnE7kQNEvXRGEDSSh1vBPcwxCSm80TaNUXkKZFbCCG8DC0K9DVYNEXjAOctC0O53C8FgLCGMA4iQ3gxD/XgsKI0JmCqNUlxrApYQbNxDW0Hg0Rcl9HhYL1IJ4PZSOkLCxDRIxrKbGj1NGMpCxUAYWYEngmDNW%2BAkKaVwiiOIVWy7Vai9U1%2Bhoyg4mWPoNPuZACyoN6GSI0lxFsqYljWGYzkc/yWB6xACwdCWLgMO4ngtHoIRhP0pSDMuw4FJkHvjHkaQltMAzlLYmD2CW3SjCHrQx3HtQjL0PszP7kyJ9kyeYY0kd%2B%2BUTvSasEhdRwfGkE5vAuWNiUpWlGVZVIs3zbgBUrQ662bYLCwIHCWDxI7pDqZIexXAAnHs/iSDpZiSMZGgGcZU/WRwtmkPZ8lXMZXDGeZU/mQfmlcDxM/GTXvUuW5HmKYLvkBbtQWDWFx2nctsVsJwDQsNC/gkpMEeAYOkXAp5XC4NpPK%2BAiB2z0LLcqCtpBKyUCrBqug1ytSYO1JGldq61z6hwAaIVLj3BGvcP%2BACgEgLRkuCBUCNDzUWgdZaq09hmA2g/byO09qoCWnEcKJ1%2BGsMGFQwBTw0bgIqHwOgGxiB3Qeg1D6L03qkBUV9H6f0HBqKBowAgoNwa9ShjDOGCM1Eoz5msIS%2BBsY1Dxr1QmxMNhqPJrHXq1NaYvQZtYza/JWYKQ5lzJQPNUZGH5qAHhfARYKDFhLKWajEHy0qig2Qyt6pCUwerAWFsrDa08Q7A2RsBAmzNlBXJVsbZxDtkKeATtY442cBAVwYxk7e2KFHPQgcSytK6fkCOmdOnLmdmnHovThkNPggnDOHTi56ALk0JO8z05F1mOtRYyxy7rMpgQm%2BnBKHEH/oA4BkiwEMO0h3WBJB2G924dtAeQ9Bij0plvHeECdL%2BAvv4fwexJCL1SsuQht9bD3y2j5PygVgpDSEZ/GKcUOB/0miwBQ0IsrQnAVcE4wIYFdyKgg2QSCUnVXkGgjJOgQB7FINg3BnUN67Iai5EhQ1yGjURWlZFqL7joogViwsC0RGHXYXsLhYLeEoAFctGFErBioqHNhbl2FeW4UOalWRN0FGUCUUJDREMFI6q0f9XR/DgYGLBhDGxmBoawzEOYtmljwm%2BNILYnGDiGpOOQCTVxgh3FUxpnTSUPimb%2BLUUE7mvNwlVkfsLRksTxaS0%2BNLXgSSKoSFSTVUlqsKXZOMFrGwBS6nCWKQwRGKpiKa0tpYa2ddbZFVqfrFOjS/DNLduMoIbtVnZ26RkVtXbCiDLmRM1OXR06tpGcOqY/a1k50WXnZZE7ZlrNLpsyq%2BCeoMv2Wy%2B4HK0UYt5ZcruNyRX91IIPJgw9KCV1eSAMwEC9h7B4oZXSK873%2BEPtfddrkQWeWPePHi08eLmRMlPSQU8fmzy4JSymew13OU4H3Hhldcrvtg5%2B0VCwOZpGcJIIAA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/reveal.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/reveal.test.hpp)
