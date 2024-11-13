<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensiblePlume`

## Description

`Typelivore::SensiblePlume` accepts a list of elements.
Its first layer accepts an operation and returns a function.
When invoked by containers, the function places the elements into the containers via a process similar to pack expansion;
then, it collects every packed container and instantiates the operation with the collection.

Check out **Example** for more information.

<pre><code>   Element
-> Operation
-> ...Container<sub><i>i</i></sub>...
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;::value...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Operation
-> Container
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Operation
-> ...Container<sub><i>i</i></sub>...
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>

## Type Signature

```Haskell
SensiblePlume ::   typename... 
                -> template<typename...> class...
                -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::SensiblePlume`:

- We will pack `int` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will instantiate `Operation` with the results.

```C++
template<typename Element>
using ZeroStar  = Element;

template<typename Element>
using OneStar = Element*;

template<typename Element>
using TwoStars = Element**;

template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**>;

using Result = SensiblePlume<int>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<int*, float*, double*>;

using Result_1 = SensiblePlume<int, float, double>
::Road<Operation>
::Road<OneStar>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<int, float*, double**>;

using Result_2 = SensiblePlume<int, float, double>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::SensiblePlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements>
struct SensiblePlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        // Multiple Elements
        // Multiple Containers
        template<template<typename...> class...Cosmetics>
        struct Detail
        {
            using type = Operation<Cosmetics<Elements>...>;
        };

        // Multiple Elements
        // One Container
        template<template<typename...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation<Cosmetic<Elements>...>;
        };

        template<template<typename...> class...Cosmetics>
        using Road = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename Element>
struct SensiblePlume<Element>
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        // One Element
        // Multiple Containers
        template<template<typename...> class...Cosmetics>
        using Road = Operation<Cosmetics<Element>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCCSAKykAA6oCoRODB7evnppGY4CoeFRLLHxXLaY9kUMQgRMxAQ5Pn6BdpgOWQ1NBCWRMXEJyQqNza15VWN9A2UVEgCUtqhexMjsHASYLCkG2yb%2BbgQAnimMrJgAdDfY9GyCCofYJhoAgmPEXg4A1EKMGWi9GUuUwrzeJgA7FZ3j84T9trt9mCjoi9kwDqizhc2Dcrs8fsgDAoFD8APLnYgYrLPcHwn6fb4EH7KYioIgAJVQTHQPzp8KhMLe9PpAHpRT8ALJeWiOPaYH53HaMAhPWEiuHiqUyuX0H4eQRMMJxNXCjUInbozHHS3Iw7HbHMXE3AlEpgkvEeBRsRzIJ7%2BF7qjWM34AEUwjTo/I1guj5rhXgyRgR2L5/lD5Mp1IE9q9PrwfvtSoequeeNp/iF8ahocOQrjYol0tleHlivuKtN8a1ZPC%2BtkRvCxAb8LRdtRtoxKId5yd1xdAcJxNJeYjBdpQZFIeZ4cjtFz6XzpgDI7hsc38cTYWAKfOaYzFLi2YYB%2B9a%2BPbmLnbLC5eldPfKQrW/7vABY5Tva4HWqcs6XOWi5uh6Nyrr6/qBmaGpXsmXI8vePy7ka%2B5HChBYKPB2AgCAMEolWApAXW4JxlB07MZBjpwb%2BS7umRNxvMAxCYMqjwbhhPxYTeOG8ocGasuyqCSfafECUJqrkQxoH0SBELvKxWKwWw7YqSJ25/ACeBAiooJFh2ggieeom6TaSIQXpOLzviCHLpmT51CJ9ImbJnLclJm72d2Eq9gqX62Re8Jas2uoKgakZDl25qORl7HOh52BcUhVwkYWJ6xQmSYScFeGPlSvnEYe77%2Bp%2BNkED%2BOXqaJNZtUxk7Qd1LFZe5rrLniSmCSWaFxuJPySXhgXycFin8aNnZqVpHWre8ooAFTbTtu2iuCW3bQAKtgQhHTt%2B0bbt12bZd2kQmY/hhESXhYGmbhoAwGwpKWxX3Zl%2BlRU1ImTQAWnEqC9MQZ7poZJadTpvVsYDcMqiDZXkuEUN4dFBCbQjbwA25qO2X9k1HQA7pD4yktJJN4/j62E0jrlzmp7wmVVz4E1qR2YGMPwaIx7yTUIXgpAUmDoBy/M6pVWY1W4YQEKQPzK5tqvq4zf71iLGMywoct0/8DCAsCVlHMrImUQpRxczV6E2/NRzg2yUOq5F7s/JT1NNONTMzL6AD63FxAQEBjOglEKJcIcNQbOqq2LEvpFLCeys8iw8xKfMC1wwtvKL4uS9LsuykHXDyz5NKW4IGs/FQtDcnjqvoKsFnawTk3pwQFd4SbZuWT407K6rjfN637f0NbIC2249s147s/O/PWPjBWusfI0weh80EcEFHIAx2wcf2j3FdJ8Xqel4b5f5wGWdM7z/PMmYBdFynSg3zqQdmFX1U1yVoIMeTcMT1zbl4DuncmbdzLr3P%2BxszIWRBMPe0o8G6gJVj8CBFkZ5zwXjmP6TseT2ldr7MgmNMBex9lDf2m9A4FjjkoPekdo6x3dGfOBv9L6fzTlwt%2BD86wcGWLQTgiReB%2BA4FoUgqBOBuGsNYBkqx1gKnMP4HgpACCaGEcsAA1iARIkgrgaEkFwSE/gNCJA0GYAAbDYswAAOBx%2BhOCSF4CwCQGgNCkEkdI2RHBeAKBAN4rRUjhGkDgLAGAiAQCrAICkLwKsKAQDQLsOgcQIiXE4KoBxNiAC0NjJA/GAMgZAPwpBXDMLwKWhASB4CjlUfgggRBiHYFIGQghFAqHUGE0gugqgUypCkTgPARFiIkdomRnAySJIScyVAVAfg5PyYU4ppTylGL/hADwaT6DQzUVwRYvBQlaGWBAJAqSUjpLIMky51yQDACkGYPgdBtjECCRAaIkzohhCaCcEZvAfnMGICcMk0RtBdFCRo1JJZey0H%2Bb0rA0QvDADcGIWgQTuC8CwCwQwwBxCIrwAJboAA3fmkzMCqC6IkzYGjlY1EmbQcyVIQUeCwJMggxA8AeKxaQMlxBoip3DLiowTKjDaOWI3JgwAFAADU8CYApo%2BSRGimnCFEOIdpaqulqEmf0/QeKUAKMsPocyQTIDLFQD9LImK8mR2kqYSw1gzB%2BP5VyrA5qIDLE6N0ZwEBXCTD8FUEIxp5jDCqAUTIAhA35HSFGhgcwhiVGqLUHo4wWieDaHoH1dQob9FDUm7N6aY3THTYm8o4bvXKI2EsFxHBxE%2BMmf4pZuSClFJKWUipWzcC1P2Y9Q5xyJXLAQJgHkwwvWkH0ZIfwVwACc/hISSBMWYSQNivGJBsbOutbjSAePUVcGxXAbEONnQ4o9hiuCJHnTYxtvT/GBOCZoiVETonnNibMxJ5BKB3L2ZktgnAmgsBJZCPJTAuLJi4LOq4XBjHVPwEQd1eg1UtM1dIbVShdW9N0M8wZTBhlYrGfWiZd7pkfvmYswDwHQPgZvJB6DxifjbNQLsuIfJHpmCOU%2BsJZyLnMauXsr9KS%2BP3MoyBt0RhINcG8TQWUJpKBfN6UCv5ALSBKZBWCiFDgVMwpVHChF0ikUorRbQDFKmcV4oJQZolkK8BksxdIyl1LtgqfpaI3pTLogspOGyzY0jOXcpU/ywVShhUWevM%2BqVMr5WKuVSp5DGq2lodkDqnp0jsMGvFY6qwJqPOestdagQtr7Xpiy8611cR3XkotSmmzfqA2ZqmEEBg6By0LAjXGuoJbUgdayK18NNXfX1GLQ1oNA3c1loLRW5NMwJgjaLbMSbbWq1rBrYcutDbfG8GbaJ6j4naNQZgxoRjPaENsfUZxk5OjSAjrHfECdbmd17qgyYyEV7ITmMkCuwpVRNtTICbYR9l2zmvqQHEuZgmf0ZKyRwQDqyWAKBJWUkldHkRjDg72%2BpSHZAocSx0%2BQGHUs6ACKQXD%2BHRnreI340j8TEk/AWT8WHRT4eI5%2BMjqDqPmRMZY32/w/gLvPrfZDm537hN7JAIjiWQc2dBw5yHYgLBCkvNk%2B8%2BT3zfkgpU2p0F4LIXaeY7Chg8LJmGdReizFGjzOit89i6zpLyW9Mc8gGlLnBAMvc8yv5PmOVcp5RooLQqdhhfFdxvgBgosKqVbOOL2OEsSCS50gnericGEy8amwuX4D5bqJi0UrDSuWBdVtt19SqsTpzVkFwzWushtKIW9rhQshdcjXUPr02ai1aG30Lr5eBB5tb/N2buRRszfzbXqbtaFDVraYRjbTbOAM/l3DhHSOUdTgFhAE7JAzsDq46c4do6sB3cI49kAZgoO88SFY0xXjeeQmPbeqn/2gkhKHZOkYc7EgONsbOyQs7zELq4ECDc38Epy204EHW40IyqQfzAP%2ByB2WH5QyGcEkCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/sensible_plume.hpp)
- [unit test](../../../../tests/unit/typelivore/sensible_plume.test.hpp)
