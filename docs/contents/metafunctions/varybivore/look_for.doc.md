<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::LookFor`

## Description

`Varybivore::LookFor` accepts a list of variables and returns a function.
When invoked by a predicate, the function returns the index of the first variable that satisfies the predicate, or `-1` if it cannot find the variable.
This function is created to exhibit the power of fold expression and to compare with `Varybivore::Find`.

<pre><code>   Arguments...
-> Predicate
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
LookFor ::   auto...
          -> template<auto...> class...
          -> auto
```

## Structure

```C++
template<auto...>
struct LookFor
{
    template<template<auto...> class>
    alias Rail
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<auto...> class>
    static constexpr std::make_signed_t<size_t>
    Rail_v {RESULT};
};
```

## Examples

We will look for the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto I>
struct IsMinusOne
: public std::bool_constant<I==-1> {};

template<template<auto...> class...Args>
using Metafunction = LookFor<0, 1, 2, 2>
::Rail<Args...>;

static_assert(Metafunction<IsTwo>::value == 2);
static_assert(Metafunction<IsMinusOne>::value == -1);
```

## Implementation

The central part of the implementation is this immediately invoked lambda expression:

```C++
[]() -> std::make_signed_t<size_t>
{
    std::make_signed_t<size_t> counter {-1};
    return
    (...||(++counter, Predicate<Variables>::value)) ? 
    counter : -1;
}()
```

The function contains two main components:

1. A fold expression over `||`;
2. A counter that produces side effects.

The comma operator discards the result of counter incrementation, leaving the predicate's result to the fold expression.
The fold expression will short-circuit as soon as `true` is obtained.
Hence, the counter will stop incrementing once the right variable is found.

If no variable satisfies the predicate, then the fold expression is evaluated to `false`. In that case, `-1` is returned.

Here's the entire implementation:

```C++
template<auto...Variables>
struct LookFor
{
    template<template<auto...> class Predicate>
    struct ProtoRail
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||(++counter, Predicate<Variables>::value)) ? 
                counter : -1;
            }()
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgOykrgAyeAyYAHI%2BAEaYxCBmAGykAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn5cgXaYDlkNTQQlkTFxCckKjc2teR22EwNhQ%2BUjSQCUtqhexMjsHOYAzGHI3lgA1CZ7bl6OtIQAnufYJhoAgvuHx5hnF8jj6FhUDyerxeBEwLBSBlB5zcTCuqAAdIiAGpNPBMaL0BSAl7jYheBwnYKoVAAawAYiQgSZ/FYXid6SdQeDIZhoUyIUwoRdYUREfCHicjkwFAoTspiJh8KIuY86QzcfiCGLiKgiAAlJh0IEMs407U6%2BWNRzIQUCcaYVQpYgnHmoE4ANzEXlZcoNutpzzdbpMAFYrD6ACIQFYnAC0At%2BIBALCYJMwAH0MsBwuh4wRoRkAF4J9N7WWer066kewuFyPR2MJpMptMZvDZ2t501eQRxd2hrjUgPnEult0SgibBj6vs6iB86luScQazWNAt0FkZWSvDS1kXFHENEYzBYvNRx3eTArEPnMlnV2j%2Bnz1vWkBhzt7Xt9rvBkcGrs99%2Bfp9Uy/slk2TBDkuRhOEJybIURT5Z5gAlMFGAIPd8x1LwMiME4NToL4A2VVVUCw2hoVg%2BC2EEBQIMeX8Xh/D0gQAegAKmYljWLY%2BiGNYk4ABVdyQk5WI4l4mLY0SWKE4FXjMA4GCOLxTmhK46DubFJIAzl1zAogTgASVUhUCR0hRuIAd1QIF7xSLwMVXE5y2iYlaHjNAGHGQxczcHScPOXCzAFYtaL/Z51NA21dP0gg8UMhQAFkwjQgB5cILJOKybJNezHOcs1GkEaE9L2btCo7fy9X8Iq6JBYDAIuELNNtSjBQMaDEWeYhgGQoE0LCYAThizBGioFsegEHDCWJclKQuDRSBOLhZrMBbVKjQjiPaijEUBajJLc4142FJRmggfrBuGuphwuIzTPM/cQEPZ1vMKk4zBWL8cSNVd9pFOICGOgamCG2Tzvy2L4oUJL12wA8nU%2BHyfIfV6nw4NZaE4H1eD8DgtFIVBOCnSxrDsjYtlh6SeFIAhNGRtYSRAH1/HhPYAA5En8PZWY0Zm2YATj2fROEkXgWAkDQZsx7HcY4XgFBAGbKax5HSDgWAYEQEANgIKyCHISg0HBOg4giVgdlUFnQ0SSQTmAZATSkeEzF4FciC3dA9H4QQRDEdgpBkQRFBUdQFdIXR5pM4gmBSTgeBRtGMapnHOASq4tZOVAqBOU3EnNy3rdtyR7ZOCAPH1%2BhrX2LgVl4eWtDWCAkD1lIDbICgIAbpuQGAKRFpoWhFxliBonj6IwiaW4o94YfmGIW4EuibRunl8m9bIggktoMeg6waIvGAGFaFoGXuF4LAYyMcRN7wCUentXd44tborh2cmwlBVGg5uaJw%2BnjwsHjyK8GFkfUgN9iAOSUAGMEhhgA3CMFTNYVADAdSRHgTAJkEopEYOPX2whRDiB9u7eQSg1DxxDvoKBKBZyWH0HgaIMtIBrFQCkc6h9Qy/B8qYAmlgzASxAS7W%2B9Dqi1CyC4Bg7hPBtD0CEBYZQKh6DSBkc6Ux2gFAUVkQYMiRjzS6CNBgfRJjiOmIIhevQ5jqOGPELRcwlF6Dcs0MxSwLFrAUMTbYEgY4cHRqQcWvBJYZzNhbK2Ns5r5zMIXXAhASBnDJpXCmcC1gIEwEwLA8RgykFppIPY8Jeb%2BEkBoSQZhJCJFFj6RI3N%2BYcEFqQYWewuDwkSFwRITNuZMwaT6SQXAfS82SN4hOUtbCy1iQrWuqs67q2TlcHWrdUAl0NsbTgTQWD2n8KGJgTUoFzW5vCWp2MnYkDwK7eaBDPZ4OkAQ/2xCg66EWmHCO493GeJ6ZLJOmsrip3TgspZKy1kYS4Js7Zhdi6N1LlEvYL0q5wKVvXaZQK4iTLbqXEAHzllCiML8rgM0e590oIPIOk9R5YLxdPWe88HBYOXohNeG9sZbx3nvA%2BWCT5QPPtSy%2Bxib6Hx2aoB%2BoIsEvxqPHD%2BX9bg/x2Njf%2BgDyYgLAZgCBp9oE9QhQgpgSCUFoIwZjcmRzcHe1ObIc5gdsZXLIbAjhVgqEfzoakxhzDOCsIIOgdhlCLDcJ8bw/Z/DUnaPOiIsRuRlFSNKOYuRhRFEGOUfIooDB7GyK0TUYx9QrFhpsXGnRej5iBocTYxNfqs39GjZopxLjvb3LjkHXxSKvkot6r8rZ8INBhPwM7EFFdwVDPiYk5JlB3GVOqZsvJ/hOn%2BDZvkwp7SvHx0ltLAZ1dFbKzVhrLWcLoVNyNmweZxAWABJYAoe0Jp7Q1pZOMR2ja9kHOwccnV2D9UkJAHzG5kcj4lvHWWxO4ylRpxtBurdO690Ho0uMAFy7gX7D2DEmdtcoUzObrrIDIxd0pBSPGfd3N4yHoIPtL9py6BYoHkPEe08CX4ZnnPBeZLpkr0pfHGlu8xD0qAYys%2Borj6suvrfIO99kCP15a2N%2B2NBWjxFX/LcEreBSvSDKyBZ8FVDL4IghQyDUHoMwUArVXsJC6r9kQg1Ohb3GuME66htD4AMKYVkQ%2B9FIymusC6nGbqsCWqcSm71EBXDWPmgGxYMaVGRrc9586%2BaLFGNTdmiRsahEJrzdIoNlj%2Bi%2BdsemzzBb1ibFcRXcpDyJ2cE/Zuy227d0Oj/aCADEBwlNvLmBuJpAElJJGKkt%2BPaEibL2HsH0Po8nos5nsfwjTn0S04FOuWlX0lmDqVwUFiRQXc3qUkDQgQ357FLX1vp4H3EO16z4/rgya5rBARkZwkggA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/look_for.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/look_for.test.hpp)
