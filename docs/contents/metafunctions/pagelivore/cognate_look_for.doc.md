<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateLookFor`

## Description

`Pagelivore::CognateLookFor` accepts a predicate and returns a function.
When invoked, the function returns the index of the first argument that satisfies the predicate, or `-1` if it cannot find the argument.

<pre><code>   Predicate
-> Arguments...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
CognateLookFor ::   template<auto...> class...
                 -> auto...
                 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct CognateLookFor
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<auto...> class>
    static constexpr std::make_signed_t<size_t>
    Page_v {RESULT};
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
: public std::bool_constant<I == -1> {};

static_assert(CognateLookFor<IsTwo>::Page<0, 1, 2, 2>::value == 2);
static_assert(CognateLookFor<IsMinusOne>::Page<0, 1, 2, 2>::value == -1);
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
template<template<auto...> class Predicate>
struct CognateLookFor
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||( (++counter, Predicate<Variables>::value) ? true : false)) ? 
                counter : -1;
            }()
        };
    };
        template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAOzSrgAyeAyYAHI%2BAEaYxCCSGqQADqgKhE4MHt6%2BeqnpjgKh4VEssfEAzFy2mPaFDEIETMQE2T5%2BgTV1mY3NBMWRMXEJSQpNLW251WN9A6XlIFUAlLaoXsTI7BzmFWHI3lgA1CYVbl6OtIQAnifYJhoAgjt7B5jHp8hj6FhUt/dPjwImBYyQMQJObiBILBmAhTHOqAAdMjbod9kwFApDspiJh8KJwRU7o8xsQvA5Dh5gMwgcFUKgANYAMRI/xM/isj0O3MOUNBTEJbnhRGRiIAas08ExovQFH8uTzSeSCNjiKgiMomMBYQruezOQ8eUbDjNHMg0QIxphVMliIdhahDgA3MReHWG416jn/T2ekwAVis/oAIhAlocALSor4gEAsJgMzAAfXS1LxSYIEPSAC9k5miT7fUb9YWi56Y3GE8nU%2BF0Bms3hc/WiRavII4scORGuOzgycDWXfbiCOsGKXBzyIKL2W4ZxBDhBrNY0G2gWRVXi8ATYacJcQpTLMHKibGXd5MOGTkzeWS3iBDlQxEolpeKtfxxPW%2B27ffu/2P76vZhgBXp9hUA48r2/66safIwnCCKinuB6yvKHrcl46RGNiWpvCcwaquqqCatqELIdKsrTgW4Fsv4YEGv8AD0ABUrFsexHGMUx7GHAAKkeBBYuxXGPCxHHiWxIkAk8Zi7Aw%2BxeEcELnHQ1xof8cECjuQoIocACSaFKhSekKLxADuqD/PeyReDKW4mgQ6CxtE9K0EmaAMDMggQnp7xgQRZioiWdHQdJmmCg6%2BmGQQZLGQoACyYSYQA8uEVmHDZdnmhWLmeO5lpNN5py%2Bfh%2BGRj2LbBfRbIkk0ZpJhiSgtBAVI0pgdKMiyxA%2BaZFm3LGJHaUkhzVIcZikGN/UgGebp%2BWVZhLKFppbg1mJxAQLWoNSWkdcyrLFQlSUKKlO7YANuEQsNo3jZNJ7Ta6eEVP55WLeBHArLQnD%2BrwfgcFopCoJws6WNYJprBseGyTwpAEJo70rAyID%2Bv4iIVAAHAAbP4FRYxo6PYwAnBU%2BicJIvAsBIGhJL9/2AxwvAKCASSw3972kHAsAwIgIBrAQNkEOQlBoCCdBxBErBbKomMRhjkiHMAyDmlIiJmLwm5EPuTnVPwggiGI7BSDIgiKCo6is6QujVGZxBMMknA8B9X0/XDAOcMl5z84cqBUIcUsYzLcsK0rkgqwuHgi/Qdo7FwSy8CzWgrBASDC8kotkBQEAp2nIDAFI400LQa6MxA0Qu9EYTNFc9u8OXzDEFcyXRNomAONXpDC2wgipbQVfm1g0ReMAQq0LQjPcLwWDxkY4h93guIOHgTpHi71ot%2BcWzQ2EQKfeblzRDb9ceFgLsxXgFPj6QS/EC5SjBsChjAJcRhwysVAGMAChingmBmclySMG3HWwhRDiENkAk2agXaW30A/FAS5LD6DwNERmkAVioGSPUMeEYvj4VMCDSwZhaZX01svVBXQW71BcAwdwnh2h6BCGEQYZRhjVHyBkAQkw/CsLSOwhgcwhjxGmLUChPRxitFoVMchC8BC9BaPw5hgjbBiM4XoGYcjGHzBYSsBQ4NNgSEdhwb6pAaa8Dpr7aWst5aKxGiHMwC5cCEBIMcKGscYYvxWAgTATAsDxDDKQRGkgKiIiJoEDQkgzCSAxlTf0GMCYkw4GTUgFMqiIgxlwDGaMCZo3Sf6SQXB/REwxsYl2dMGZMzcazROXMk48w9ucQWmdUARzFhLTgzQWBOn8BGJgaIDDYS4ATREXBET/XViQPAWsjbAP1hIaQ4ClCQPNroca1tbbVwMUYkxrsODuz5ucL2Pt2mdO6b0h%2BI1BnDI0GHJpqdI7OIqAtOOL92bJxuWnBpWdI4gCOV09ERgBlcCSAXIulBS7m1rpXNuEL66N2bq3C%2BHdGAEG7r3f6/dB7D1Hm3SeD8Z5orniIpeY9RmqDXkCNuW9aguz3gfK4R8tj/VPufaGV8b6YDvlPR%2BYRQCVL4O/T%2B39f7/1%2BtDIBetQFzNkBAs2/1lkwOfngqwCC94oL8egzBnBsGOVwfAiwhDTHEImaQvxdgRHOAgK4FR1QGElAEXkHh9QrUpAdZkeRCwhHdBkcoiRXCpH1Fkf0DRdrpjepyL6tRgbbUKP0asdYeiY7xM2SUzg9piAdK6T0v5wBzlDJGfY/AGt7kxyeZUjxXifGUAMYk5Jgywn%2BAKf4bG4TIl5OKebUpthynxzZhzbmvN%2BYfLeZHcWbA2lpssSwBQTpzROgGYiGEYw1YFvGZMsVICDaSuNgsmVOhFikFWXbceGznbtrdnUlU3tU0sAnVOmdc6F0qk2s0qOskKiuO7YnV5z7B3PumsgZIyQkyzoJkmB9DVx1zLoCCkuZcK71yhXBhuTcKFt0RV3BgPcXboqHmILFF8cXTwZRPAlC8iUr1JcgdeFL2w73%2BjSyu9KT77mZbwVlaR2X32nty55b8tQCp/n/ABF810zLAVK7dUC919OMLqxByD4BoIwZkMejEYyKusPqgGhqsCqu0cI6RfgLXUKdTaph7rnUFEyE6th9Q3UsL9aIvoTrTUGYDXZxREbnNiPczGnRcaDbHrbbTFN7Sb3TudPerSYx82OJfcsEtCcy3eOGH4ne1aQBmEGRUCo/p/RhMBXjCo/gMlBdMZwMpzN3H%2BISGYVJXAHkYweQTNJZgon%2BHiRUE9wX6YVMS/E1WpXtkJfhpfOI6RnCSCAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/cognate_look_for.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_look_for.test.hpp)
