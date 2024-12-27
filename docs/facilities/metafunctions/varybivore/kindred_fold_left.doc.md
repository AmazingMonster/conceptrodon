<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredFoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-kindred-fold-left">To Index</a></p>

## Description

`Varybivore::KindredFoldLeft` accepts a list of variables.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function left-folds the list using the operation and the initiator.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, V<sub>2</sub>, ..., V<sub>n</sub>
-> Init
-> Oper
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, V<sub>0</sub>
   &gt;::value, V<sub>1</sub>
   &gt;::value, V<sub>2</sub>
      &vellip;
   &gt;::value, V<sub>n</sub>
   &gt;::value</code></pre>

## Type Signature

```Haskell
KindredFoldLeft
 :: auto...
 -> auto...
 -> template<auto...> class...
 -> auto
```

## Structure

```C++
template<auto...>
struct KindredFoldLeft
{
    template<auto...>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail
        {
            static constexpr auto value
            {RESULT};
        };
        
        template<template<auto...> class...>
        static constexpr auto Rail_v
        {RESULT};
    };
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
/**** Subtract ****/
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction 
= KindredFoldLeft<3, 4, 3>::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1>::Rail<Subtract>::value == -9);
```

## Implementation

We will implement `KindredFoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<auto...Variables>
struct KindredFoldLeft {};

// Base Case:

// Fold once.
template<auto Variable>
struct KindredFoldLeft<Variable>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value
            { Operation<Initiator, Variable>::value };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Fold twice.
template<auto First, auto Second>
struct KindredFoldLeft<First, Second>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value 
            { 
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first two parameters,
// and recurse using the rest.
template<auto First, auto Second, auto...Others>
struct KindredFoldLeft<First, Second, Others...>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value
            {
                KindredFoldLeft<Others...>
                ::template Page<
                    Operation<
                    Operation<
                        Initiator, First
                    >::value, Second
                    >::value
                >::template Rail<Operation>
                ::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQSXADMpAAOqAqETgwe3r4BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8YkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLKn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMSTcTC8RAAdIiAGqtPBMGL0BRQ7DAibELwOW4AaXC6GImHQADFPOgQpgqARbiYAOxWZkAEShViuwJ2O1uFiYSluMKUIGBvP51No6FuAi28OBoPB70wUJhcNQtxRxDRGLVSRxVzxBMZJIYZIp0tp9II6p1evo2IlrOBt3dt2Vz1V6thRAeDCy7xIzquHtuJsJymIqCIyiYwDVYY9LO5l3D4a9EINbizPuhftQiMVhtuyAMCgUtwA8ql4u9sqH0xn3ZHGdHY6gAEpMOhultM13JgceuaOZBlgQTTCqVLEW6F24ANzEXiTzZH7tTNbrxAbAnV90DjmDZG1qPRTsNIBAK%2B8mEHnKSaZHLKfaf7LbzkOh35zheLbEywrBRi0uYByTBRgCCxQ1PwzLxMiMW4ezoJkknZW4OyIVDaHVcDINeGDALg594LfLkJWHT0wW9H8NQRRECMwKDBFgo0N1uRDwmALCEwfKFMOw1B40TfCIJYojQMRZ0yJ5DlKJ5H4pRpT0AHc8AVJVaOzX1NVuSk8GICZSAXfShEwNALSbNtiVJckqRpOkGXVQzjIIUyLKs9Am1TeC/z0/0jyDIhiCbcNbOE0T13DPzqMzHT81zRL6IAmTS3LIUq1retGnCgdIpjHDezw%2BKUyHTiRzHTTJwYadZ3nRc7zXJkypbbd4M3D0cr3PLoU6rqd1yxt%2Brawb3WCk9QtMtyJgGrrsRvZrME8yyBB8sbX2vW9VxiwaKLkyryvfKijvdALfxS/9NRI7BgKysCJNYmD8pbbjkNw9ChKK7sSvEwjoOkkscUO2KFMO/yrsCosmKeqTXq4pDeOir6sJ%2B6L/skwHbsUoFwY/ZSUMsjZMiXB9RXYU6%2BQM1SCA0rZTIQQx0HoT0EAfGh3PUrVUlaVhMFBYzSElBcLVuclkBJh93t4gh2fFzAJkVK4LoYrVZo8sz/S89bTLS%2BFqzl%2BJ2NxAh8UJc1LUcmVnLtaENdW7zTMN9njJx%2BSXw9VXF0mtFQoRwrOwx6i4rOmiVXo72bvSu7MsrIbepGjiqrN000c7XD5sHT2uuqicrPqucta1Zas7BnPxrsi0HOtW31Rd433bDkcbz/PixNG5vBp6/cGHVMvu93Xv%2B82yuJuPP2SBmoy5tHhbtuWx31oH%2BfsCW3aV4zRaQDbzPoR7vrk7H251/vTeDorsGTqUsPVajxjgfuytHoBtiEfDGWUJK1HhL3txmOekDWSFcL6nQShHa6D8AHwzgtRT%2BKNBLpzjPxTGgCcYQ3xlTf4fxAS/D2LcbAqhWDPAfF8Xk2CARYLuEILwMQzZMEJGQlWUMCz6UuHrfSVhYGXFsjQuhe4HAugrnnWqhdGr6VLiHVktxLgAFoLCPlxqAm%2BeDbgAFkBZMCoF4BgDhsifDONpCB0MwLEGACbK4n8NEtG0boj4EoMJVytrXW06oUi3GkLcJI28MbQkuGYoBpECbXCOLcAAKorRkTCeEtHHAAfSyvEAgEBrFaJ0Xog80IuDbz/nw%2BhgiF67S%2Bog2RABOZYXIOCrFoJwAArLwPwHAtCkFQJwNw1hrARnWJsASZgkg8FIAQTQVTVgAGsQC1MkPCDQAAOMwZhSmlK4LU2ZMyuDMmZNIGpHBJC8BYBIDQGhSCNOaa0jgvAFAgCOUMppVTSBwFgDARAIB1gEFSHCcglA0BPDoPESI/NOCqBmf4WR/hJC3GAMgCcUh4RmF4BSQgJA8DoD0PwQQIgxDsCkDIQQigVDqFuaQXQQQ1J7lSJwHg1S6kNOGS0zg1Y4TvMZKgKgtwgUgrBRCqFtwYVmFuBADwPz6DznMP05YvAblaFWBAJA3zUi/LIBQCAcqFUgGAFIMwfA6CC0uRAGItKYjhFaAATwpbwQ1zBiDGurDEbQlkbkDO%2BURasDBaCmsJVgGIXhgAwloLQS53BeBYBYIYYA4gPVGXtXgMmAbmkzmJqCM15BBD1FpbQPAMQ9xWo8FgWlZs8D7MDaQMmxAYgZEwOyMEob01GGGasKgBhzFIjwJgNSOVGkDLRcIUQ4hsVdrxWoWlxL9ChpQB0yw%2BgM2XMgKsVAqRGgBtkRMHyGFTCWGsGYU5JbdRYGnRAVYdgo3OAgK4aYfggihHCMMSooxCgZCyAIM9egigPoYAsEY1QehHqaJMdonhOh6EPRkn98wr2LFvbYX9T6ghzDaO%2Bm91QD3dK2BIKlHB6nHNpWctlwLQXgshdCqZfKIC4ERSKvpXBxWDLrasdmTAsAJH3aQcZkgkjwlKUkTZGhJBmEkP4Q5tT/ClP0JwXZpB9n9PhIEfwMzSlrP8JM5ZHH/CYcJWci5VzqO3OlU8mVLzGUfKVSq4V/y2CcFaCwJczJZFMHushLgpT4RcGmfC/AoVkWotkBi3t0h%2B1KEHYS3QmrSVMHJYGtDGGTm8DOQyt5cI5SsvZXhuzvEHNOemfywV8rhVMj6WYKjkq7l6eM/ET5yrUBCtGJlIwDmuBHJoLQHVlB9WEotSapNbWrU2rtQ4JNTroIurdbSz13rfX%2BqTcG6t2xmn4Alo4GNtL42S0TUW8IoJtnNPTZmk1ObpsSt1IWgZJay1KErSGowNbQDab4I2hQzbW3tqTV27zWLfOyAHQS5pQWR21rXVYCdW292zvndkRdy7BJ/Y3Vu%2BIO7FbwAPfUb9LgLTQeCBaeDSw73FGyKjl9jQMcQaA40foUx/35Bg4j4DJPBhgY/YBqDZPz2QdA%2BUOnlG1gbBQ%2Bz7ZkWsOcBwxy8F1XUuOecxoflpHQq5bFRKmjpA6MMcoGhsTEnHPceZLU0pGykg8b45IIIUW6XnNsJpwrOn4B6deUysrJXiCme2BZzlLAFBLgnEuNL2YJiubIx5oIz2e2vZxfIfzn2dAgBSCFsLlKRPoZpWp%2BlBnmWJady7t3HvVQTEyxV7L8RpdJAK3W%2B5srs8KptyX4Vt5kCpFSHE93pS4me4IHE1QYKtWNeNs1g1RqrUde79a219q%2BsVeda691M3MBep9WIcbRbJsXb26QWbUaFuEqW3CbYAy1upsJVtrNxrdt5oO0m475azvVp4oXhtCY7strbXWDtvB/eYokG93FIeh3h5%2B8YcdNhAfw5aSDlOJwDsMumOuupYJutFtusinDjOl%2BsBsju4IznoJeqzghs%2Bveo0LjpgdkATp%2BkTn0AznkEzgQQINTngfTgMKjrBjTmgZjkhpzlihFnHqcvzi3uCs7q7suOnqCJniRm5iQNLpRrLtprRpgPRqMExtsiriAAsvCEkEkLUisvrocgocyDJqpqwcbpctcnLixrUuxussyIcjMpIEslwHMmYCptskkCwdFpwCIVKmhnCpofYcbmbqsCWpkM4JIEAA)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/kindred_fold_left.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/kindred_fold_left.test.hpp)
