<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::LookFor`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-look-for">To Index</a></p>

## Description

`Mouldivore::LookFor` accepts a predicate and returns a function.
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
 :: template<typename...> class...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class>
struct LookFor
{
    template<typename...>
    alias Mold
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<typename...> class>
    static constexpr std::make_signed_t<size_t>
    Mold_v {RESULT};
};
```

## Examples

We will find the indices of `int**` in list `int, int*, int**, int***` and `int, int*, int***`.

```C++
/**** IsIntDoubleStar ****/
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = LookFor<IsIntDoubleStar>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int, int*, int**, int***>::value == 2);
static_assert(Metafunction<int, int*, int***>::value == -1);
```

## Implementation

The central part of the implementation is this immediately invoked lambda expression:

```C++
[]() -> std::make_signed_t<size_t>
{
    std::make_signed_t<size_t> counter {-1};
    return
    (...||(++counter, Predicate<Elements>::value)) ? 
    counter : -1;
}()
```

The function contains two main components:

1. A fold expression over `||`;
2. A counter that produces side effects.

The comma operator discards the result of counter incrementation, leaving the predicate's result to the fold expression.
The fold expression will short-circuit as soon as `true` is obtained.
Hence, the counter will stop incrementing once the right element is found.

If no element satisfies the predicate, then the fold expression is evaluated to `false`. In that case, `-1` is returned.

Here's the entire implementation:

```C++
template<template<typename...> class Predicate>
struct LookFor
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||( (++counter, Predicate<Elements>::value) ? true : false)) ? 
                counter : -1;
            }()
        };
    };
        template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQgkgCcpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzOFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GB5nBDEhXmhsLcyHG6CwVGxuJ%2B/zpAOBv12NwAkixUvQ2IImA1PgdAUz6f9AcCCJh2QYxSSxRKeZhpUjGKxMAA6NXYm6QpgKD7KYiYfCiKWgnGXcbELwOG4hVCoADWADESLiAOxWS43T03GUcuUKp7MNhqlXYTmMAhYk3Ar03c2Wgg3PWoIgAWU86GjXpMbszMc9s0cyE1AnGmFUqWINyYXiINwAbmIvPKPXnPdn3RdW62TABWKw9u4QJY3AC0GvJIBALCYdswyMywAi6FRJMyAC85wRqS2u1mczvd3mJ1OZ3OF0uV3D15uNWgvIJ4jC3SOuNm7rCO4eu/qCOsGLmvy9CBg2zNxQIgG4IGsaw7wfMhE31Q0/ThUNxXDSNsEnBtvEwYdYQdb0LUwG4QBuKgxCUJY8NBAiAMA4t7zFStSJfD86K7N8h3YtsXXfUFPz3PiBNbH1JXlOFEQDZVg1QrkI23TsvS8TIjBuNNaHQGFQTuBDk1QdSMxQsNBAUECo3410hJpK4hQZWlbmwVRWA5YivkZWy3MudzbhZBQWUEO41hieg%2BkrTyLlE5D4UVQNiNk8MFLjK1fP8ghAq8YLMFC4FSNSDLaDwItjzwBR52VEl4sEUgbnCAh9g1ds3zYrz7P2NTMGaKh7wcbI%2BX2QFIuNaKpKDNULmIYAMOBZTwmAdrOu63lYR0m17SdYgSRSgKgpCiYFMnAySXGyazJxCyWps24ABV3gjPrTmBAtCuRbUlFaCAUw6pguoJBoSVq6rat2QHBH2EG6vqk0sMbYjluWm4zCWZqLie5AXp1eICA%2Br6fp6gR/qqmrQfBg5sWhnCtL4nSXyR/iOBWWhOB7Xg/A4LRSFQTgwMsaxYzWDZYbBHhSAITR6ZWO0QB7SQVQ0AAOMwzCSJIuB7eW5a4F0XWkRmOEkXgWAkDQNFIVn2c5jheAUEATdFtn6dIOBYBgRAQDWAg8oIchKDQdk6HiSJlU4VQ5f8Ed/EkG5gGQIspBVMxeANQgSDwdA9H4QQRDEdgpBkQRFBUdR7dIXQggAd3RVJOB4BmmZZsWOc4AB5GtPZuVAqBuEOw4jqOY5uOOzEgjw/foSs8S4JZeDtrQVggJBfdSf2yAoCBF%2BXkBgCkMw%2BDoJjrYgGIG5icIWgRaveBP5hiARJuYm0TAHAv0hfbkpuGFoc/i6wGIvGANwxC0GttwXgWBpxGHEN/PA%2Boep1neA3Msj8axbGFrVOoDcCoxHRDfDwWAG5ojwIbEBpA4HEBiBkTADxwHAAKkYMWKwqAGEmgANTeGXJuAZn4Z2EKIcQuduEFzUA3Uu%2BhDDGGgpYfQeAYjW0gCsVAqQGjAJHOSZapgeaWDMObUhxBU7wLkd0R%2BDQXAMHcJ4DoehQjhCGJUEYhQMhZAEFMPw9jijZHmMMBIQQ7BGN6BMNo5j8jeLqL4gQoUBjWIWHY2w/jnF6FmK0DxtivErAUPzTYEha4cGZqbBuFsu6h3DpHaOscZZDwgLgZO48hZTxFvQlYCBMBMCwAkIcpBJaSFBCqJIoJtYaEkGYSQ/hjY9n8CkXW%2BtSCG1BFwFUgR/ByySBrfw0tVY9P8Lk4uFsrY2zqfbOeLt55u1bjWb2a9UCjwDkHDgLQWB1hdCOJgmoDCqS4EkFUsz2ZJyILotOQRuFZz4dIARSghHF10DvCuTAq4gKyTks2vALYtw9jWdundu5FOeWIge7zPnDwuUvMeMIwSI2nvQx2C8CXLzOevMeKAXlbxVibGgtB96UCPsXK%2BZ9n5cpvnfB%2BT9iGv3DO/T%2BDcf5/wAbQIBz8wFiMgezfAMDHBwOAV81QSCxTPzQbrdmmDsEIlwVsdmBCiHC1IeQpQVD5WzXJYwpgLC2EcMYFw2QgKc7AtkIIou7MIWiLoeoqwkjMGyLaQopRnAVEEEMncQN1gtGIp0Xo0NqSQl4z8BAVwcSghWPKJ4vQRRHE5ECS4tIDiGhJMWMEnoYTYklviWmho4TK3RISQEvIpa20tpSasdYGTJ76Drps82nACk90jlqV5uLZaQUqT84lMzakz3FqQRpzSRhtImQbEAoJ3n9JdD2JIWtQQDKGZIIICLG6W1sLs5dBz4BHPdp7GlVKx6BzYJwW5vcWAKDrEWOsbyVRiXGInfAPzU7pzdbwj1ed5Cgp9ToHdpAoUwproO7J9ctnNxOQmDuXdv2/v/YB4DCYIAj0JY%2BPEoIl3kqObS%2BIL7LkJD/akVIyIANJGRCR5EqgI671ZfEA%2BHL2a8q/sLUT/KjHP2FYIUVX9FWYF/v/QBwDhZyogca0B0DfGqoQRq5AyDtUPl1bwfVZ8jX4N0Wa3gFqKHWogba/ZfAmEKFYZgdhnDiEAugxIT1%2Bd4PCKQwylAEibAhvgPIxR2RgHbAnHGzR2j4i/P0W0nx6aTFmI7ZY0x3aC3luyNmstbjSiRPzdW0JjQ61ZfK%2Bm5tpXknxKqxY7x/jcsDrSX2nOcLMMjo4PhyOP6/31mI3KcYs6wMkAXZPMl%2ByGlNJaZQLJkzDZKxVKCUEPY1bnuNutl0Czh2Is4Ds229T2mJB7N0zWLpjZy2SFwLgCszAbN1qCHrh3r13qyQnA7V6ZuzxWKQzIzhJBAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/looke_for/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/look_for.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/look_for.test.hpp)
