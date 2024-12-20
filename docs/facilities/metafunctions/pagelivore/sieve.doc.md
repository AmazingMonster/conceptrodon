<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Sieve`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-sieve">To Index</a></p>

## Description

`Pagelivore::Sieve` accepts a list of predicates and returns a function.
When invoked, the function removes every argument that satisfies all of the predicates from its argument list. The result will be kept inside a `Shuttle`.

<pre><code>   Predicates...
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Shuttle
   <
       (...&&Predicates&lt;V<sub>0</sub>&gt;) ? Nothing : V<sub>0</sub>,
       (...&&Predicates&lt;V<sub>1</sub>&gt;) ? Nothing : V<sub>1</sub>,
                            &vellip;
       (...&&Predicates&lt;V<sub>n</sub>&gt;) ? Nothing : V<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
Sieve ::   template<auto...> class...
        -> template<auto...>
```

## Structure

```C++
template<template<auto...> class...>
struct Sieve
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will remove every variable divisible by two and three from the list `1, 12, 2, 6, 15`.

```C++
template<auto I>
struct DivisibleByTwo
{
    static constexpr bool value
    {I % 2 == 0};
};

template<auto I>
struct DivisibleByThree
{
    static constexpr bool value
    {I % 3 == 0};
};

template<auto...>
struct Shuttle;

template<auto...Args>
using Metafunction = Sieve<DivisibleByTwo, DivisibleByThree>
::Page<Args...>;

using SupposedResult = Shuttle<1, 2, 15>;

using Result = Metafunction<1, 12, 2, 6, 15>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Assuming we have smashed every element that has already appeared, the ordered collection of the elements left is the result we want.

To translate this idea into actual code, we need to implement smashing and collecting.
We do this by:

1. placing each variable in a shuttle separately;
2. taking the variable out of its shuttle if it satisfies all the predicates;
3. concatenating all shuttles.

We can merge 1. and 2. by:

```C++
template<auto Variable>
struct Detail 
{ using type = Shuttle<>; };

template<auto Variable>
requires (not (...&&Predicates<Variable>::value))
struct Detail<Variable>
{ using type = Shuttle<Variable>; };
```

We will use `Sequnivore::TypicalPaste` to concatenate the shuttles. Here is the entire implementation:

```C++
template<template<auto...> class...Predicates>
struct Sieve
{
    template<auto Variable>
    struct Detail 
    { using type = Shuttle<>; };

    template<auto Variable>
    requires (not (...&&Predicates<Variable>::value))
    struct Detail<Variable>
    { using type = Shuttle<Variable>; };

    template<auto...Variables>
    using Page = TypicalPaste
    <typename Detail<Variables>::type...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGE6a4AMngMmAByPgBGmMQSGgDMpAAOqAqETgwe3r7%2ByanpAsGhESzRsVwJtpj2jgJCBEzEBFk%2BflJVNRn1jQRF4VExcYkKDU0tOe0jPX0lZUMAlLaoXsTI7Bzm8SHI3lgA1Cbxbl6OtIQAnofYJhoAgpvbu5gHR8gj6FhUVzf3ZlsMOy8%2B0ObgI5ySmAA%2BgRiExCApvncfgB6ABU6NReyEmAAjl4GHgAG4kdggAAq4LwoloyiYI2eGNRyJ%2BBEwLCSBlZILBEOYbAAdILEbcRsQvA49hSklSxLT6QcAOxWBUAEUOViRd2RyL2Fjpzzc%2BpAPxZbI5TC5Rx5jFYz1pyAA1ph0Ni8Yw1sLReKCJLKdS5Za3PanS7cV53ZhhSYlT89nG9l40kY9taXiq9sHna7wwDI/ENfdVeqTVqdQAlTDIFZpQkGo0l26s9mcyNIo6x%2BNN82BpgnVCC/lXPY7OkKLFhiO3UgduNdlsg3tEAdDkcKMfZiM2Gd7Rf9wUANUaeCYkXoItIBzu8Z3fYHh%2BIx9PmAsCmnV874JtAsFAHkCAgYgRNtrjuL0JSlGUaTpQMN1ze4jnvR8zwUZd4mwC9YLWKwEKPE96BfVD0L2P8AOIFChTQk0Y3fONExCYAU0/NNfWlf1oNbW5rxBbdr0wzB4LcRC8P48j%2BQvISnwIij0J4%2BMSMA5caJebAQBAa1iyRIt8wbOcLQ47ilN0wNrT5TAL13QjhwMNdxzdOC304zszXnK1P1M8zb2kqzR1snMsIc68TNtSUp23IK2ElLclIsg9cKfc9L0cuMYv5CT8NfMK3NtAd5LIk1KNAmFvRYyCAzzNw%2BIEskpz2NKRMIjCJ1zbC3DJGxari9KGuI/8FOkqiC2vOjk1TQ50wgtj6W3AykuvXzJxBaqLymRxkEhUQRkW%2BDsAgOqRXmAdloaVb1ugrarl2zrnwUA7pICua41y0TprQ1T1O0zS1Q%2B%2B4tUZLEEBOAh6D2RlmTuIzypSz0iolIQAYIIG8wLFE/qEPBMFrEGMTBxtnL07k8Z7TzBzQ7y1wHZRiGdGVWQRAqRRhn00Yx/TqNmiGFz7DqH2E4VrzAn0VUwBo6ESrilQTJMGNG%2BJ0zhwH6G4yj80VL7kcMwnIa5uq%2BfjKm8TwKmxwgBhUB9CBlzMAA2cwrcp6nRFpkEddekBCTEcN5nmbcBb2IWRdoZ2rt1uNowsSX6MYiFmPlhHFZwnmn2%2BFXozVhtAs1zml1ixP6DpkDZuGhjaWAZ4xpKyauSU7ksoi/24UDhOkMwfO3s/Qi24hDTCzTzVbjRRlB8HnGB/RSUW4IMdQZRofZ6ZBsHgBJ4XmOU4LijX6MT9ok8DSSTzjJAB3VAsfRHGOaOXc9gASWhsUJRVHe9/wg/j4Gn3jqpYcBHpVQkmIPYkRUCeD2O7bwHFxYWGvgcMwABWPYZg0zlw0KnbuqDvozzHo/Qku88D7zJAgKmDJsammbPjS%2BXNb7019tg3B%2BDCGYFZoNeMK0v5oAYL/f%2BgDgG0FAR7CB8Yw7QPMPA%2BISDZZ7BQVpZG0iGyj0xLHRGp957g0zhQ7OJMC6%2B0UfHdW/c/rYFUKwDkxCz6kO7FrDRtxiDAHzj8IuewACywsmBUHxA4DIMd0a1hBLQ5%2Bz5X6oAvH4vBL8CFEOFKpEu5VrG2MImgu4DihBeCSCkJQ6AKwKC8LQH05cdHlS4BeMwF4uCwOTnohxmTsm5Ikc4hobiAS1AYCCQpewuDFIQReK2JSynKz0awtao4YgEAgO8VSChbSQjpCCKpOSMIpLSc6WZBArje3zBwRYtBOCwN4H4DgWhSCoE4G4aw1g9gKGWKsMufweCkAIJoDZiwHQgFgWYfkCozCSAABxfNgRoAAnK8jQVsvmJC2RwSQvAWBxA0KQPZByjkcF4AoEAsL7n7I2aQOAsAYCIBAMsAgSQTjkEoGgdkdAYhhFtJwVQXyrYAForaSD2MAZAyA2mSH5GYXg1MiAPnQHofgggRBiHYO0IV8glBqAeaQXQhTD6wiSJwHgmztm7JlYin8JwiU%2BlQFQPYtKGVMpZWyjlXK9gQA8OS%2BgADNhcHmLwdFWhFgQCQGS6UNqSUQHdRS2IwApDFJoDkwClBIgysiCERo5xlW8AjcwYg5wfyRG0JWdFtyyVsEED%2BBgtBo0YtIFgSIXhgCGloLQFF3BeBYBYIYYA4h834Cph42sFaDmYFUJWE46xbkhFZOCg5ZxIiwgTR4LAMqYR4GhZW0gtZiBAKUELGtRgzhGAeYsKgBhbH7nRofH8vIY0yGFdSMV0gJWKBUOofNcr9C1pQKcyw%2Bg8EosgIsVASQmkVvpe8MaphLDWDMAi2d/KW7wEWHYVNGQXAMHcJ4VoeggghH6KUQYhS0kFEyLBiYeQ0hNJmAMcoHQIN1FGM0TDbRCMeOI9MRDswUO2BI%2BMcjUwmh4eQ%2BUMDly1gSFVRwHZcKNWcANXSxlzLWXsqkOaiAuBCAkBgfEe1jq12LAAkwLAsQIBPJAJIeI/J/nxAVJIDQkhPlWw0BoWBVt/n6E4JC0g0L5P8itlwEF/yvnOdgZIUpenunwt4Ii5FqK7lrqxbi11%2BLtXEooN61A1rKXUo4I0FghIFT0qYN5ZMXB/n8i4PyNt%2BA%2BV4AFYUiVIrxDitkOe6VV6QDFIVUwJVlaeN8d84czgWrCUnD2HqncxAkspbSyODLWWcsaAtVaj1MQ5NmAdUFjFLq3UxYm2QKLPqbUgES8l%2Blg3/X/IqHwOgrIyKhvDZGhNB641RqTSmhwB6M2MAINm3NMrC3FtLeWg91ba31oOY2iDLaZXts7ayA9vbqgysHcO84o71gHInVO25s752YEXV9%2BiwWN1MC3TuvdjAD0lePbkM9UrL0HN0MUgwq7f1WAfYO59GnDnvoyJ%2B79ssqf/sAzEYDdOwPVCI34CArhGPweg6xuYqH8hNKF%2BLnDGRRd0fA5Rhg3Qxhkb0Arppyveg0fw2rhjqvCnMa18UHX9qlgrC46b8FzWBMcB6311L6WGKZey7li10m%2BVyYU7N51ynMCqcGPT8Ftn7NZaMwqWB/yFQKniMZyQTLCktf87YQLTrMXYrxQSnVXrVtxbYJwRLxqWAKEJOywkzuWwjB5flkghXBWyFKyew9kqL0yt0IkOrDWVXWd4%2Bq/NmqIu6v1QX5lReS%2BgPL3pEYY3Fu%2Brk/EGbqf5soBn56lbK/Bgl9SZCMv/zIQV4IFM3rTL9vBqOxAMN%2BaLtnenVfxNybU23Zi5mh7Oa80/cwEWktYh3vTs%2B8umHVahsf2IG%2BagOVYwO06oO/avAEOUa0O46D48OvAiOqQyObIqOq6c2fAm6Cg26mAu6%2B606%2BOoqhOFWxOreIAYKt6bONOT6oGDOH6nAyIYyNBFgAGfmQGhWIGL6FGTSUGMG2Q5GCGxubGegaGku%2Bu2G6GcuBG6uXQeughauvOiumuMhuuPQUu9G1GIhYuHG5uYqTWveCKgmw%2Bewo%2BpeE%2BtM5s7usmdqC%2BSmpAKmamlAPGweNWWW8Q8QsCfynmZmnhCoIK/GfenAAWaKDhzykgCoXK4eXAUg/yYeemXACo3e8QRhfmIR3ujy3e3KQRxhSKmRXsM6gEkGkgQAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/sieve.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/sieve.test.hpp)
