<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateObserve`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-observe">To Index</a></p>

## Description

`Pagelivore::CognateObserve` accepts an operation and returns a function.
When invoked, the function collects the indices of the arguments that can be evaluated to `true` and instantiates the operation with the collection.

<pre><code>   Oper
-> Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper
   <
       Arg<sub>0</sub> ? (nothing) : 0,
       Arg<sub>1</sub> ? (nothing) : 1,
                  &vellip;
       Arg<sub>n</sub> ? (nothing) : n
   ></code></pre>

## Type Signature

```Haskell
CognateObserve
 :: template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class...>
struct CognateObserve
{
    template<auto...>
    alias Page = RESULT;
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
using Result = CognateObserve<Operation>::Page<0, 1, nullptr, 3.0>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`CognateObserve` is inspired by the talk [Adapting C++20 Ranges Algorithms for Most Metaprogramming Needs in Fewer Than 1,000 Lines of Code](https://youtu.be/69PuizjrgBM?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) from Daisy Hollman and Kris Jusiak.

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
template<template<auto...> class Operation>
struct CognateObserve
{
    template<auto...Phenomena>
    using Page = decltype
    (stare<Operation, static_cast<bool>(Phenomena)...>())
    ::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhpcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMWCIVDMDC4WJgCRCAgWGSrpjKbjqfjWsQmKjAujWb8AcLASC/ntbgBJFipehsQRMRpfQ5A8UigFAsVHW5zYjU74ggiYGUGI34o0mxWYLkI1AAOgdaNukKYCk%2BAHlnjzGqRbrFUJ4HXblAhGKh5UwWZc5o5kM6BBNMAA3MS3Ji2nWTTAQZYYgDsViut2Ltx2OxhADYNESQCAIlhVAB9JQARy8r2tcMlQbJVdueE%2ByD1VvQIJLpfL/GItwIodu9CMs9uqColY0IbDEZ7VbtY5LeoIGwYMP8Vn893xmQAXphGwQg5K0RAa3WGA3m5g2x38d3Hfzc0WJYmAWe7jsWoFgWWa4vvWmBNq27bYp2bi/ru/ImH2A7OsORqjoBYETrcU4znOaBeIIy6rhhGgEMQ7bUf2x7URuDDhowTDbhou74WBB5HieZ4XnC163veDoAFJPjBb5wR%2BX5Ifi4k9v%2BEHjsBhaXARBFoAwiaqKk07pkQtx6goXi0AQNL3AJJjnjmqlaepDlaSWUEAOrUiwTAANaclWL7crytypKGrERgxCioCRirOS5hEAO7UqIx5MMgWxuv2FqfCua4sWxzCcbcXiZEYAmwaotn3NxmlxQRAXEDyyLBaF%2BVMDCBZ5Vujp5kJGmxS57nUvFdC0DqJCWdR9WNYx%2BDpdR1W1XVBDoLWgVNfWeDpe1FiocBvX9Y5PGLYRHm3MNtCjcV1KzlhaAyq0A4CER5EONkM5RZFbQLcdJZGVFd2pFZNlmBWIWbuxlXPngN53v2voibD2gATVP3bQdtV8cQDDo3FUGSlRVZg2FEOnnglUMVh1G0fRfaGHhKOo655bUUTrW2RY2jk5hnxUGISi%2BrOjBrmT3Pzh8nyzoYa6czuOMDeWAAqoZ6lOmC%2BlL5WUWu1PWqLYjxbynz0G6ctaVBkspcems5dRvO0Eo82mwRUHRmmJkfOZBC%2BhtW021WOsMedtBO5B5aukolT0IxJHUlQxCyFrgtpg1vLfYzWkQKz4Wk5VMIg%2BYFa3GAYDNeDzDs5z57I%2Bn454wTGhZyTFhk%2BeDF02ujfl6elcXrTep%2BqgS5U3RusaKQIe1%2BWgvHol7uHljws0m4twyxo73BaZCRJtSeqmng2/BRkWQJmnNfAW45/FpnLXZ83ucFwXpfE13HP3/nIP9kvK%2B5oEGnp3tsI/6MxDlBaiPsPiBxGn6HemArroCIiQGO7szIWVPsdF8PIjAfFrJ9AgEBwEKF9ADH%2BQDUYgPLJjY8SdTKezQYtShM1NoQN/jjPa9kWGCgZvLNcNCLIU0%2BG1Say1Vop1RLLI6ZtyynTQBdTADhMo83jhRVIAxx4SOduWeKCBNoIHjAqCIAiLpIIIVrYeNMuI4ygkrRgvpZ4GJaIIPAVo1yegSIqbIjt1Gh1uKdBhQiVogAIMiZ4jY8BYEcUEhixkmBJlQGEvREw6KvSMJYsOx5UCxG0HIyyOUgnPBcV6dxAh8R7F7BYrx44GEvjybeMJjBHCRLhK470Hi4S8PvIqCA4lljKXRPyNGPVAGxTYS%2BLyvlQkyXgp%2BRCWx8QQB7JYTq7Ef7ohAj1EhEERnCJAGM2pky5IzOQiJFcQYIBLOYCspy6yhmskGRw4EQo7geGAMwI07pYhKGIAfA0VwLSyitOaY0/yzS0ltL050BgMrNKKdjdCVxEleHkc815mB3mfO3vmUhM4gWmmQn9IM5zIxwoZsVCIwBbjKCYMATkgRrJYEhDUiCz4sz4mhT6TM7jkCNlEBMfE/pPBPkJT0v82AczVxLLWRl9yAHSseeqFUWo7jYFUKwWU%2BoFVyvlWcDErIKTYipEvHSWxUgEAUFGRVBxbhsrej8y4fzcU2iIL0kECL5HWuKbK642ohBeFSEUTA6AABKHsLLKgOECUlpUfV%2BoyAG4NKCJq0qtYUxoGI4QQRjJtblroCCXmhqJJ8XBVgZpaLGbNvLhL5rvE%2BQIyMySevFLceNnsw3aquJG8lzbQ2wmssiq0aKt7IXdbC7AtZKXUvxGPW4KRbgMHMrQE1ZBbiBDtBoetfVNW3AVh8SytrM1cvDgkPBL4FCsFvK6fEXava3Gjf6oNIbc0qV/hwVYtBOD%2BF4H4DgWhSCoE4BfSw1gxobC2HnQIPBSAEE0C%2B1Y3kAiSFXQADjMGYAAnKhrg/gNCIcQ1wPMeZpBvo4JIXgLAkhjy/T%2Bv9HBeAKBAGPKD36X2kDgLAGAiAQDrAIKkBE5BKAAzoAkKIZ7OCqEQxWAAtBWSQtxgBpWnQhswvAA2EAZCtFI/BBAiDEOwKQMhBCKBUOoJjpBdApHijyVInAeCvvfZ%2B6Dv7ODugRDxnJq4xOSek7J%2BTUg7RmFuBADwMpBPTkxEW3gjGtCrAgEgAT9AyAUAgHF0YwApBmD4HQI0xA6MQFiA52IERWjIms7wArzBiDIneVkhwJXSB3XlAQd0DBaDFZM1gWIXhgBuDEPbWrWAvJGHEG1vAepXrbzoyZuCciETbAgxEI0RGf1IliDyCrHgsAOdongMj3BeDb2IP6JQjwBvACREYaDqwqAGGAAoAAau8eKriv0Qc08IUQ4g9OvcM2oBzZn9CGGMNYaw%2Bg8AfPgKsVAJrsgTYk0SHtphAOWDMFR/bxA6l0cgKsOw2TsguDfNMPwKQwgRGGJUUYKQijHxyJ4ToehKeNAWCMaoPQccCH6FMGn%2BRxj1FZ00SYgwSeLHJ7YfnBO9C6gF%2BUJnEgsfrE2Lp2zHAP2kEo7wajtwPNSZk3JuMvn/MQFwKp0LYJwuQYu6sUMTAsCJBzKQODkgV2ocCARjQkgzCSCrBofwFZUP6E4CR0gZHwN2grFwCsiHUO4YrP4SQmGncVhVw56jtH6Nm6Y9F9jMXOMud44l5LxBhNsE4K0FgSY8wSbai6UqXBUN2i4Ku5T%2BAiBo/U/pt7OmJDSC%2B0oH7JndDpYs0wKzu3FfK9V45jgznuMIi1prrzVfyU17r6ugLQXUghbA2YZYEWLssdi%2BGdf8W%2BNJYPyFlABgjA15qBliyCQct5ZM2VortWn8Vaq9k2r9X6lNZaw59rnXusLoJsIN%2BsAchsf18BRtHBxsHMptkAZtat5t6gHNltVtkR1ttgf0tsdsIN9tDtMBjswCyVd8rsqU7sHsntatXttMPsu9ZBvtjMf1%2B9/tzsEcrBLAQcwdMdf0ocExOBYdlp4cgckcUcEgW9sFuDsdXpnAIBXAxcic3xGcydmd6dsh5C0gj4GdBdpdudeg2dRdOdCcWdpC%2Bd5htDlDxcDC8gjCJclClgi01gQMFc/cld7MTN1c58ZMF9p1a96814Dcm9EEwtt808osLdMArdRhbciMA8g9a9Xc8x/BUN8NAg3cPdY9E93DOAU8GNd9WMOMuNXNj989C9tgS8vMWAFAkw4wkwl9cUJhG8jcwk9BqD3tdM6CDMe9GCdAQBghB9h8bMXCx8k8nMc83MNcKiqiai6irQJhV9T94swNa0d90898UAFiEhiiNjEhqi/VGxajUNGx6iCBGxVBpMb8st798tCsKsX8bjKtMkP9ds6twwGsf9WsIDMAOsusetgDeBQDBtMD/iRsccYDJtVBpsjREDBBkCTNUCisMDNs0ccC9sEh8DCDBtiDVjSCbt7tMBHtnhnteBWiO9Pt6CujfteiWDAdEcbBlsMdbdIdGgJsdgaw2DrBkc1dUd0dwdjDGg8d3BDC9BicpcLCKdNC1ChTxTihsg7DhcpDGh2d2gpS%2BS%2Bh%2Bc5TmcJd1DbDzD7DZcnCZchi3CqNOAJiZNKjqjbgDi7RjiAtDdm8wNTdIsYNSBLdrdKBFdYiQA0M7RAhAh/AsNY8NANA/S8xw9MiTSaNbBU9nTlhYMQBJB/A7QMN8NgzENJAMMuBkMQYXDAhjS1dsjQiXSiMlMIyCyozYzVh9tMhnBJAgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_observe.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_observe.test.hpp)
