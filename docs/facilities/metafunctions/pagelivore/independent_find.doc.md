<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::IndependentFind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-independent-find">To Index</a></p>

## Description

`Pagelivore::IndependentFind` accepts a list of predicates and returns a function.
When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
IndependentFind
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct IndependentFind
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<auto...>
    static constexpr std::make_signed_t<size_t> Page_v
    {RESULT};
};
```

## Examples

We will find the indices of `2` in list `0, 1, 2, 3` and `0, 1, 3`.

```C++
/**** IsTwo ****/
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = IndependentFind<IsTwo>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);
```

## Implementation

We will implement `IndependentFind` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct IndependentFind
{
    template<auto...>
    struct ProtoPage
    { static constexpr std::make_signed_t<size_t> value {-1}; };

    template<auto First>
    struct ProtoPage<First>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<auto First, auto Second, auto...Others>
    struct ProtoPage<First, Second, Others...>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    ProtoPage<Others...>
                    ::value != -1
                )
                { 
                    return 2 + ProtoPage<Others...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgABwAbKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGZwshvFhbiYwW4CABPZ4AfQIxCYhAUcOwIPMEIYUK8MLhbmQE3QWCoOLxvwB9MBIL%2Be1uAEkWGl6GxBExGl9DkDmQyAUCQQRMByDOLSeLJbzMKSmF4iAA6NU425QpgKBRqlXKYiYfCicXYsG4q4TYheBxshhYZ72xgEABi4XQeIA7FYrrc/bdZZz5Yrlag9TTff6rTaCLcDagiMomMAFZG/SZvbc5o5kJqBBNMKo0sQswR0CAQCwmABrTAorLACLoNGkrIALzrBA1ADcxF5MLDvQBaLgZ%2B5wiyD8dgn3AtMBiVB6XwpVEW5u4gTCOXf2l622%2BOJ5MK%2BEbrfmkG7jOT9Pz3fZvC5tAMAtFkur1C3XveAeX3f%2B68/3/f8TH8Kx/HuCBlluIcNQpCsq1res8EbI0W3hdtO23YDgMAu8cN3PAqDzF9xTfW4oHDMxknMZIDSNR95TNNwzy7c0K2/ftlmWICCJAzNDQIDYGFuDQJynWkdz44D6iUXjpPTATMCE4gRJHcSx3knCxygrTFOnWcr09AzJN3QMpRPNwP3XPBNwIUhbmsoRMGfdAHI/PUAHkCAQeIzQtKS/WjA9iATVAkxTUlWIc5zXIc7zfM3cML3na8APwoKWhzEjX2LRzQy/PtfwywdDIU0DwMg6DYPNUty0rGs6wbJt0LcTD0IChTSr0viiJysjix6gjKPVajaPo40mKi2zz2wDiiu4obtKUlSRLEmcJKuJaZNoJRbj659cuIbb/xGlVaPGw1JtNUlYoED12JATjMEWkqCLSwThNuUcNs0ra3pw2SBwO/MBuOgHgIgE6CMPcLj1JBK/OSzqupw%2Baf1uMAwDhe4YNHCH/x4gmjMnaGcM%2B1TbjMWFLDjUKj0i%2BFEaS9UUsC1Hd3R/sNOJgDjNMjnbiBsnFMnCm1J%2B0n%2BYJnSifZoyTNS/mZwFv1zODFdQz1S5gENCVnX83ivCyIw42PWEwVx2GIssnW9e5AhdVZ3EVa25XZyZYVGTpO5sFUVhOQHb5Pa9gVJOZNkFAAFQAd0/YOrnV5crIK1lt2C2NWWjuOQRAW40i8GJaEfOqKxiVBPBRQ6WkEUlWQt6dcbMDVAPd8OjluABZZSmCoLxCT5BPLiTyyPLVS5iGAQ2rmN8JgC7nu%2B4HnIG7tB0XkEN17Tr7PUG3CsbdJCep%2BRid27uKOPkd/kDiBB9kBRbUlDaCBu5aJeHByUkNAcoIqYcsEOIua/ktjjKmPFXaXHvo/HU8QCCv0Xv3T%2BAhv6/wAUAp6RUG5gJHBAiwHBVi0E4P4XgfgOBaFIKgTgbhrDWCzOsTYv5wQ8FIAQTQBDVjVgCJIFUGhEhmDMAATkEVwfwfDEhcE9J6aQRCOCSF4CwCQGgf5kIoVQjgvAFAgB/mw8hBDSBwFgDARAIB1gEALvZCgEA0AcjoPESIrBtiqBSEOZIkhbjAGQLmKQKozC8AYkQYgeByxBH4IIEQYh2BSBkIIRQKh1B6NILoIIMcMRpE4DwQhxDSHsMoZwTyyoLG3FQMRZxyRXHuM8d4nh1MIAeFsfQEs%2BIuDLF4LorQqwIBIBsWkOxZArE9L6SAYAUgzB8DoOKTclAYi5JiOEVoiIMm8DmcwYgiJPIxG0C5XRLCbEO08gwWgizElYBiF4YAVlaC7SWaQLAVYjDiBObZbZeBuwfFyYWFyyptgsPCOKWRFDi4xAxGsjwWBcnojwIo7gvA3nEHLkoR49zgDFyMOw1YVADBTwAGrvBjp5R0NywnCFEOIaJxK4lqFyck/QhhjC0MsPoPAMQtGQFWKgNIjQtEcCHBSHGphLDWDMGouFQSsCsqgj0F5zgICuGmH4IIoRwjDCqKMIomRsgCHlXoYomqGALBGAkIIdhpVNEmO0TwnQ9AmuQWa%2BYyrFhqtsOa7VxrzUGtVUa1YCgGFbAkFkjgJDSCqN4Oo24ZSKkeK8d9GpFFcCEBIDTMELS2notWL5JgWAEiSq4ZIMEKpBFgmkRoSQZhJDJGUf4ZIgj9CcHkaQRRyaVTJC4MkRIgiJHJH8JIURhbUghryRo2w2jWHooMcYrppjCnKnIJQQZjSHFsE4K0Fg3ZPRDiYJqAwpsuCCJVFwXh/j8CBOCXoYlESyXSApUoKliTdBjNSUwdJMKA1BoHeogp5jlTFNKS4txW66XfT3QejQFF6m9MaUmswrTR16M6d01ADT4izusYhiDowtRGF3VwH%2BNBaCTK0RAGZiSVkLJuaRtZGytkOBuXs50Byjm5NOecy51yYW3IlHSx5FD8CGk/m87lFDPnIG%2BTcv59RclApBYiMF2wKGQuhSwuFCLMBIq43PMdmLkwKFxZgfFhL2PntJVEq9shKUJIofe2laKBVWEZUCiV7LOU5G5byss/KGUWGFaG0VwT3lsqlbalw9pXXBHtB6pY6qSg5FC7qxoEWnU2saP0KYlqCjGvqKalLgwHWGutS6tLCrnX2oqHllpawNh%2BvK7It9uSw0Rv/Zh%2Beu7928LjcexNzSYPtI4aQDNWbKABvrY2vdJbPT%2BEEVIsEpby09uDXVzgmiR09c6ROpAZiLEofnfYxxy7iAsH/SwBQ3ZczdhaxZCYR6E1irPbIC9JmYnyBvRZnQIAwSkEfc%2BzJtbA05MSR%2B6dsYSnhsO8d0752mKxjqWhvpSawTdbHZO7b/S50w8aU9ZAaQ0gojO4IlEF2CAolUG48Z%2BG/LTNmfMtZ5GqfrM2ds2jiH9mHOOTxzAZyLliDYywu5XG5O8F4y8gTHzVBfPFGJwQEnElSYWbJiFQTFOwviCptTDyNNwb4FinTeKCWMCJXd4zEhTOxOe9St71n6WCvs8yxzlDnP5k4DseCtmhUiviGK/zkqks5GC%2B4QreglWlc9TqjVjRYuh5yAlo1gXksFfyEV73AhstR/ywMULcw2gp/Kz6yrUTX1/bUZwEH7ijsna/BD00UP42BKTSm2DHT02YEzaMSVsjhsgCESqMEYJ/BiJ7co7vno23zf%2B4t4dOi02kFzf4AtkjPTKMSJIERXB%2BHUR%2B2CAvoax8rYDX4kfheh079IHCrIzhJBAA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/independent_find/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/independent_find.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/independent_find.test.hpp)
