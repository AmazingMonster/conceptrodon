<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Observe`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-observe">To Index</a></p>

## Description

`Varybivore::Observe` accepts a list of variables and returns a function.
When invoked by an operation, the function collects the indices of the variables that can be evaluated to `true` and instantiates the operation with the collection.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Preds...
-> Oper
-> Oper
   <
       V<sub>0</sub> ? (nothing) : 0,
       V<sub>1</sub> ? (nothing) : 1,
                  &vellip;
       V<sub>n</sub> ? (nothing) : n
   ></code></pre>

## Type Signature

```Haskell
Observe
 :: auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Observe
{
    template<template<auto...> class...>
    alias Rail = RESULT;
};
```

## Examples

We will observe `0, 1, nullptr, 3.0` and use the result to instantiate `Operation`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    static_cast<size_t>(1),
    static_cast<size_t>(3)
>;

/**** Result ****/
using Result = Observe<0, 1, nullptr, 3.0>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Observe` is inspired by the talk [Adapting C++20 Ranges Algorithms for Most Metaprogramming Needs in Fewer Than 1,000 Lines of Code](https://youtu.be/69PuizjrgBM?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) from Daisy Hollman and Kris Jusiak.

The primary mechanism is implemented within the helper function `stare`.
The talk [Understanding The constexpr 2-Step](https://youtu.be/_AefJX66io8?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) by Jason Turner provides a relatively detailed explanation of the usage of `std::array`. Here, we will only walk through general ideas.

```C++
template<template<auto...> class Operation, bool...Phenomena>
static consteval auto stare()
{
    // `std::index_sequence<I...>` is created
    // for the length of `Phenomena...`.
    return []<size_t...I>(std::index_sequence<I...>)
    {
        
        // `std::index_sequence<I...>` is created
        // for the count of `true` in `Phenomena...`.
        return []<size_t...J>(std::index_sequence<J...>)
        {
            constexpr auto result = []()
            {
                // We make `std::array phenomena` so that
                // we can access items of `Phenomena...` using [index].
                std::array phenomena {Phenomena...};

                // We will sort `std::array indices`.
                std::array indices {I...};
                
                // We will use this comparison function to sort.
                auto comp = [&phenomena](size_t i, size_t j)
                {
                    return
                    // If `phenomena[i]` is `true` and
                    // `phenomena[j]` is false, then `i` is less than `j`.
                    // Therefore, an index of `true` is always less
                    // than an index of `false`.
                    // As a result, indices of `true` will
                    // assemble in the front of the array.
                        (phenomena[i] && ! phenomena[j])
                    // If `phenomena[i]` and `phenomena[j]` are both `true`,
                    // then we return `i < j` to preserve relative positions.
                    ||  (phenomena[i] && phenomena[j] && i < j);
                };
                
                // `indices` will be reused for the result.
                std::ranges::sort(indices, comp);
                
                // return the result.
                return indices;
            }();

            // `result` is a `std::array`.
            // We collect its front part,
            // which contains all the indices of `true`.
            // Then, we instantiate `Operation`.
            // We return `std::type_identity` to avoid constructing
            // an object of type `Operation<*>`.
            return std::type_identity<Operation<result.at(J)...>> {};
        }(std::make_index_sequence<(...+Phenomena)>{});
    }(std::make_index_sequence<sizeof...(Phenomena)>{});
};
```

Finally, we will make an interface to accept arguments:

```C++
template<auto...Phenomena>
struct Observe
{
    template<template<auto...> class...Agreements>
    using Rail = decltype
    (stare<Agreements..., static_cast<bool>(Phenomena)...>())
    ::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACcSaQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMWCIVDMDC4WJgCRCAgWGSrpjKbjqfjWsQmKjAujWb8AcLASC/ntbgBJFhpehsQRMRpfQ5A8UigFAsVHW5zYjU74ggiYGUGI34o0mxWYLkI1AAOgdaNukKYCk%2BAHlnjzGqRbrFUJ4HXblAhGKh5UwWZc5o5kM6BBNMAA3MS3Ji2nWTTAQZYYgDsViut2Ltx2OxhADYNESQCAIlhVAB9JQARy8r2tcMlQbJVdueE%2ByD1VvQIJLpfL/GItwIodu9CMs9uqColY0IbDEZ7VbtY5LeoIGwYMP8Vn893xWQAXphGwQg5K0RAa3WGA3m5g2x38d3Hfzc0WJYmAWe7jsWoFgWWa4vvWmBNq27bYp2bi/ru/ImH2A7OsORqjoBYETrcU4znOaBeIIy6rhhGgEMQ7bUf2x7URuDDhowTDbhou74WBB5HieZ4XnC163veDoAFJPjBb5wR%2BX5Ifi4k9v%2BEHjsBhaXARBFoAwiaqGk07pkQtx6goXi0AQNL3AJJjnjmqlaepDlaSWUEAOrUiwTAANaclWL7crytxpKGrERgxCioCRirOS5hEAO7UqIx5MMgWxuv2FqfCua4sWxzCcbcXhZEYAmwaotn3NxmlxQRAXEDyyLBaF%2BVMDCBZ5Vujp5kJGmxS57nUvFdC0DqJCWdR9WNYx%2BDpdR1W1XVBDoLWgVNfWeDpe1FiocBvX9Y5PGLYRHm3MNtCjcV1KzlhaAyq0A4CER5EODkM5RZFbQLcdJZGVFd1pFZNlmBWIWbuxlXPngN53v2voibD2gATVP3bQdtV8cQDDo3FUGSlRVZg2FEOnnglUMVh1G0fRfaGHhKOo655bUUTrW2RY2jk5hnxUGISi%2BrOjBrmT3Pzh8nyzoYa6czuOMDeWAAqoZ6lOmC%2BlL5WUWu1PWqLYjxbynz0G6ctaVBkspcems5dRvO0Eo82mwRUHRmmJkfOZBC%2BhtW021WOsMedtBO5B5aukoVT0IxJHUlQxCyFrgtpg1vLfYzWkQKz4Wk5VMIg%2BYFa3GAYDNeDzDs5z57I%2Bn454wTGhZyTFhk%2BeDF02ujfl6elcXrTep%2BqgS5U3RusaKQIe1%2BWgvHol7uHljws0m4twyxo73BaZCRJtSeqmng2/BZk2QJmnNfAW45/FpnLXZ83ucFwXpfE13HP3/nIP9kvK%2B5oEGnp3tsI/6MxDlBaiPsPiBxGn6HemArroCIiQGO7szIWVPsdF8PIjAfFrJ9AgEBwEKF9ADH%2BQDUYgPLJjY8SdTKezQYtShM1NoQN/jjPa9kWGCgZvLNcNCLIU0%2BG1Say1Vop1RLLI6ZtyynTQBdTADhMo83jhRNIAxx4SOduWeKCBNoIHjAqCIAiLpIIIVrYeNMuI4ygkrRgvpZ4GJaIIPAVo1yegSIqHIjt1Gh1uKdBhQiVogAIMiZ4jY8BYEcUEhixkmBJlQGEvREw6KvSMJYsOx5UCxG0HIyyOUgnPBcV6dxAh8R7F7BYrx44GEvjybeMJjBHCRLhK470Hi4S8PvIqCA4lljKXRPyNGPVAGxTYS%2BLyvlQkyXgp%2BRCWx8QQB7JYTq7Ef7ohAj1EhEERnCJAGM2pky5IzOQiJFcQYIBLOYCspy6yhmskGRw4EQo7juliEoYgB8DRXAtLKK0NoiBBnOZGdCVxEleHkc815298ykJnMab5Zo4RfNNMhP6vTnQGDdEGS4wA9TGnqQoKM45ioRGALcAASkwOgQMsCQhqRBZ8WZ8RYpxfKAgCggzwxaLGRsogJj4n9J4J8AKel/mwDmauJZay0vuQA6Vjz1Qqi1HcbAqhWCyn1AquV8qzgYk1bcZpRTjwfMuIin5tJbS9JBCCsFhTGg3IedcbUQgvBpGKJgdApKPYWWVAcIERLSpOpdZkN1HqUETUCNZfVtrWRwggjGTa3LXQEEvNDUST4uCrFjZy%2BNPKk3CRTXeJ8gRkZkllQ6u4IbPbeu1VcP1JKK1ethBGl5W9kJj1uFwX0DBzK0DSLRX0gQ7QaDRLWcldB8SRtaX0vquqFYfEskauNyBGzhwSHgl8ChWC3ldPietXtbgBtde6z1ubsAkI4KsWgnB/C8D8BwLQpBUCcAvpYawY0NhbDzoEHgpACCaHPasbyARJCDoABxmDMCkLg/gNAgZA1wPMeZpCXo4JIXgLAJAaDHre%2B9j6OC8AUCAMev673ntIHAWAMBEAgHWAQNICJyCUABnQBIURN2cFUCBisABaCskhbjADSu24DZheBusIAyFaHb%2BCCBEGIdgUgZCCEUCodQJHSC6A7fFHkaROA8AvVem9f6H2cHdAiOjOTVwce47x/jgmpB2jMLcCAHgZTMenJidNvBiNaFWBAJATH6BkAoBAALoxgBSDMHwOgRpiAEYgLEIzsQIitGRLp3gSXmDEGRM8rJDg0ukDuiy90DBaCpbU1gWIXhgBuDEPbfLWAvJGHEOVvAepXrbwI2puCciETbG/REI0yH71IliDyLLHgsBGdongdD3BeDb2IP6JQjxGvACREYP9qwqAGGAAoAAau8eKrjb3fuk8IUQ4gFNneU2oIzGn9CGGMNYaw%2Bg8AvPgKsVAvacida40SRtpgX2WDMDhhbxA6kEcgKsOw2ScguDfNMPwHawgRGGFUUYHbijH1yJ4ToegseNAWCMRIHaYevQEP0KYuOCik/qLDinkxBio8WBj2wjPEd6F1EzioxOJDQ/WJseT%2BmODXtINh3guHbhWZ43xgTcZ7OOYgLgcT7mwSeZ/Zt1YoYmBYESDmUggHJADqSIERDGhJBmEkFWDQ/gKypGQ6h0g6Gv12grFwCsIGkhwYrP4SQUGTcVjF0Z3D%2BHCMa5I75yjfnqNmfo8F0LxBWNsE4K0FgSY8xcbai6UqXAkh2i4IO0T%2BAiDg8k4p87cmJDSGu0oW7andCRa00wHTc3hei/F8ZjgpnaMIi1tLmz2eSW5/z4OpzLm0huc/WYZYXnNtkf8%2BGCfgWGMhcX25lABgjC564GPGgFkEhxYS2pjLKX8sn6yzl7J%2BXCv1OK6VozFWqs1Yup179DXHvNfvfgNrjgOtGe68gL1vlgNvUEZiNmNsiBNtsPetNrNt%2BgtktpgCth/sSnPttkwLtgdpgEds8CdrwGdrJpdtXrIDdqpveg3g9htoDlYJYK9u9lDg%2Bt9gmJwH9stADs9sDqDgkKXtggwWTo0PDu4NTkjiEG%2BETujiTukEfI0BzpjtITkOIUsLTr0AzgMLIT0PTk0IzooazlzuoVzjoSTvzu%2BkLvoAZkHmppLv3nxoPu2nngXmvErsXogh5jPuHj5lrpgDrqMPrg7mhiAIEHnubnmP4EkAhoEBblbn7hYThpwKHkRnPuRlRjRuZivgnkntsKnjZiwAoEmHGEmMPkihMEXirmEnoAQRdvJsQUprXmQToAEaQE3i3npmYSLoZpYSZrHhZlLtkbkfkYUVaBMGPmvoFp%2BkWrPhHvPigCMQkGkTMYkHkS6o2AUUkI2EUQQI2KoLxlFvvrFpQEfveufmVt%2BkcZfnlnNgVuGEViVmVl/pgJVtVrVq/rwO/k1tAS8a1rDn/l1qoD1kaMAYIKAWpuASllAVNuDnAfNgkIgcgU1qgZMegZgYdsdvlhUZXldiQbUXdg0Zvk9kDjYCNpDvrl9o0J1jsDWNQdYCDhLmDhDh9hoeTn4BAK4OoSjjzhIfjvIQIOoQTgoczrzsoZoZTu0MIZznToycKYYZzuzqKaTtofyRyemmsCYXzq0e3sHpwD0XxjkXkbcCsXaOsU5sriXp%2Burt5v%2BqQNrrrpQMLo7uhhBnaIEIEP4NBn7phk6XmB7jERLnEbYGHuacsABiAJIP4HaEkPBnmJhiBpIOGVwGBiDK0YEO0bEXhu4RachiJt6Z3hMR4aQAtlkM4JIEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/observe/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/observe.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/observe.test.hpp)
