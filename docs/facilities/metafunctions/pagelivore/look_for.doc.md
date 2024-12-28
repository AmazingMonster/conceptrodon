<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::LookFor`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-look-for">To Index</a></p>

## Description

`Pagelivore::LookFor` accepts a predicate and returns a function.
When invoked, the function returns the index of the first argument that satisfies the predicate, or `-1` if it cannot find the argument.

<pre><code>   Pred
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Pred&lt;Arg<sub>0</sub>&gt;::value ? 0 : (
   Pred&lt;Arg<sub>1</sub>&gt;::value ? 1 : (
                &vellip;
   Pred&lt;Arg<sub>n</sub>&gt;::value ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
LookFor
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct LookFor
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
/**** IsTwo ****/
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

/**** IsMinusOne ****/
template<auto I>
struct IsMinusOne
: public std::bool_constant<I == -1> {};

/**** Tests ****/
static_assert(LookFor<IsTwo>::Page<0, 1, 2, 2>::value == 2);
static_assert(LookFor<IsMinusOne>::Page<0, 1, 2, 2>::value == -1);
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
struct LookFor
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwA7KSuADJ4DJgAcj4ARpjEIJIAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGYIshvFhbiYwW4CABPZ4AfQIxCYhAUcOwIPMEIYUK8MLhbmQE3QWCoOLxvwB9MBIL%2Be1uAEkWGl6GxBExGl9DkDmQyAUCQQRMByDOLSeLJbzMKSmF4iAA6NU425QpgKT7KYiYfCiaVg3FXCbELwOW6hVCoADWADESHjAlYrrcPbdZZz5Yrlag1SqAGqtPBMWL0bEmkGe27my0EW561BEZRMYAK92ekyumOxz1zRzITUCCaYVRpYi3JVEW4ANzEXkzl3z2dzWdbsZMAFYrN37hBlrcALQaikgEAsJh2zAorLASLoNGkrIAL1nBBpHc7HpzbpbO8748n09n88Xy/ha43GrQXkECVhruHXBz9zh%2B8Pnf1BA2DDzX6xhAgY5m4oEQLcEDWNYd4PmQSb6oavrwiGxBhhGHw4hODbeJgQ5wg6XoWpgtwgLcVBiEoyz4WChEAYBHqweKVZkS%2BH70Tub6DhxbbvmCn68ex26xt6UoKvCNYBmqqHoZGW4Hh6XhZEYSbpiRcL3AhKaoGmGakjJ4aRiB0b8S6fH7kywqMnSdzYKorCciR3yWVZAq0tcRxsgoAAqADuqD8gcQKichbiSWy8nxlarI%2Bf5IJkWkXgRngxbHrEtq0CiaAMHMgikqysJgnxmlmBqe5vkJwI2QcXkALIREpADykSBWcYoSj6xphf6EXRma6IJnVDUKM1zYJUltApXGBDoBO6WeFlpYtHl8IFRpGkjq%2BJpPlYgTme5zK3N5HwEJ8zn9byKUotqShtBANr2k6xD5bFqBYSAuniW4GikLcXC/WYAPvThTaFcVtxmMslWFldN0JAQ922o6zqrQo9UME1kTvZ9pI/X9ANAya2GNupRUbS%2BUP8Rwqy0Jw3a8H4HBaKQqCcGBljWHG6ybOp4I8KQBCaNTqx2iA3aSCqGgABxmGYyTJFw3bS1LXCBIE0i0xwki8CwEgaD9jPM6zHC8AoIA/YLTPU6QcCwDAiAgOsBCJQQ5CUGgHJ0AkUSsNsqhS/4w7%2BJItzAMgxZSCqZi8AahAkHgs3/fwggiGI7BSDIgiKCo6hW6Quj/b5GJpJwPA03TDNCyznCNcqLu3KgVC3P7gfB6H4d/RLZiQR4nv0FW%2BJcMsvCW1oqwQEgHtpF7ZAUBAU8zyAwBSIDNC0MxZsQLEVexBErSIqXvC78wxCIo1sTaJgDiH6QHvcgQzW0AfedYLEXjAGFtC0Gb3C8FgU5GHEC/PA%2BoHB4DrB8Ku5Yr7Km2PzCI4pNbM0mrEDEp8PBYCruiPAutf6kAgcQdKShHgAOAJNIwQtVhUAMMABQQZ3i%2BUas8Rm/Nk7CFEOIDObDs5qCrgXfQhhjDQUsPoPAsQzaQFWKgNIjQf7DgpBpUwHNLBmCNgQtCWAJGDh6FfRoLgGDuE8J0PQYQIjDCqKMf6xRsgCGmH4KxmQbEMAWCMRI/07C6L6JMdoRiCjuPqJ4gQ/Q2guIsW42w3i7F6DmCEsxixLGrAUNzLYEhy4cHpqQQ2vBjbNwDkHEOYcI5d0grgOOA8%2BbDwFpQ1YCBMBMCwIkbRotJBghVMkME6sNCSDMJIfw%2Btuz%2BFSJrbWpBdZgi4CqfwXB/BS2SCrfw4tFbtP8JkquxtTbmyqVbce9sJ6OzrsqN289UB929r7TgrQWB1kCMOJgmoDAqS4MkFUEzmaxyIBovQbDU6cOkNwpQvC866EBkXJgJdf5pIyVk6uHBa7O2VA3JuLd8n3MEX9Z5rye4nOnv3WE4JIYj0oTbSe2KZ5HIXv3FADzl4Kx%2BmvDelBt552PvvG%2BLLT7n0vtfPBd9GAPwYE/Kur936f2/jff%2BgigHM3wKAxwECf5vNUDA8UN8EH1CrigtBiIMHbGZtg3B/MCFEMwCQyVERQDbL4DQuhDCmGMBvt8jh6c/myB4bnZmwKBEUKUVYERKCtFSJkTkORCiio%2BusKo7J6iE6QMkTosBzgICuCif9UxFRXF6GsY0FN6RHGNFCUsfxvQgmRN8fY%2BNjRgmDDiRm9xpb8jlpidW9NYTUlrA2Ckoe%2BgK6rLzjk5FbctSPIxZLEp%2BAPl4vGZU0ewtSC1PqaMbRwydYgDBM8rpgRuzJDVmCbpvTJD/Whes2wmyZ07PgHsp2LtyWkv7j7NgFziAsDbiwBQdZix1ieSqMSEwY7jvjonTO7C04SBdVnAF7qdCrtIKC8FZdu3pMrn2muBzEyN2bi%2Bt9H6v0/sTBAXuOLHz4jBNOoleyKUJBvacxI760hpBRJ%2B5IKJcMolUMHPgdAGVbx3nvU%2BbLeNnwvrom%2BvLBCP2ftKzAb8P5iDFXgiVgDdV/xAZ4%2BVUClXIFgaqh8SDeCav3jqrBaEDW8CNZkE1EozUUMtdQ9MNrMCMOYQ62QPznVAbdXw6D1KUDCJsP6%2BAgbZGcB2OOcNKi1EJA0bG7RHiE1%2BCTQYnNabzGFtzSUHIOas05ALZYitXiBg5ti5W7xOXwlNsKyVmtrau1JI7enSFSGjacAwyHV9776w4flBMMdZTJ1D0JdsmpdSGmUDSSM3WcsVRgjBN2JWB79bTcCDM3tTWTYnottU0gzTuxtNVoEfWUsUhcC4DLMwKzNZgka9kzgA2x5pOjit67a2z2rAIVkZwkggA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/look_for/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/look_for.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/look_for.test.hpp)
