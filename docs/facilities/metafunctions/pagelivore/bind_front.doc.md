<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::BindFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-bind-front">To Index</a></p>

## Description

`Pagelivore::BindFront` accepts an operation.
Its first layer accepts a list of variables and returns a function.
When invoked, the function adds the variables to the front of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Vs...
-> Args...
-> Oper&lt;Vs..., Args...&gt;</code></pre>

## Type Signature

```Haskell
BindFront
 :: template<auto...> class... 
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct BindFront
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will bind `-1, -2` to the front of `Operation`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult */
using SupposedResult = Operation<-1, -2, 0, 1>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = BindFront<Operation>
::Page<-1, -2>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<auto...> class Operation>
struct BindFront
{
    template<auto...Beginnings>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Operation<Beginnings..., Variables...>;
    };

    template<auto...Beginnings>
    using Page = ProtoPage<Beginnings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCCSAMykAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0bEJCnUNTdmtQ109xaUDAJS2qF7EyOwcAPQAVFvbO7t722smGgCCm9sA1ACSLIn0bIJM1ec7hydn%2Bx/7r8dHxwSYNwM/xMcTc/0Bj0wILcTC8RAAdIiQdhzsgDAoFOcAPKJaKPdLI35DYheBznCzBdAAMWIsl%2BJgA7FYTudWedwbdIdDYQjERZMMBggxgsAFISWWziaSCOdlLSiMomMAoRLWYzmcc2Vr2QDOcDQTzUIj4QA1ep4JgRehiuLYX7atleVJGWVKzDnEEAEWxuOI%2BIE0P5goYwqMCmNpHOZuIFqtmHDSNtII1WsZnuT9NVOoh%2BphcKNfIFQpFNrtWadItdyo9cW9ctQCrdgaLIZLxsJcQ1aYzJ1%2B70%2Bu2%2B/fO2FUrFu7pefYHX0zPzMcWCaK8WBrbjQDBWiQIpbnw5xeKeU5OHKBUIN%2BfbSZOUrJB791R7PzeO3OQi8iVymHQACV415aBlDZvgrF130/FJvz/BQAJlL0fUPAlQQAWlac5kLMSMNEjLgOy7F8LgAWUwOoqC8TcjwOX5Ty5C9eXhY5iFFcVjlA4BzmI0jyIcdIa29CkGGpWlBGhe9/QYFiQBARVlWhVDIwwyTpKbUFGNFK87U7PdX2g2Dniok42POXTAL4jiSKYMiKKQtxsPOXCky03sCK2c4ABV4yAgzjgmRxkAAfSYDFogICAhnQKSFFYTBAptNwTIISNwK/X9/0A5FZifDh5loTgAFZeD8DgtFIVBODcaxrHOBRFmWd1zDiHhSAITRsvmABrEA8skeENAADjMMwAE4hq4PL%2Br6rgGQZaRco4SReBYCQNGwoqSrKjheAUEBsJa4rstIOBYBgRAQEWAhEjhchKDQG46GiUJos4VQ%2BoANmQ17JHOYBkGQeyerMXhv0IEg8Ai1p%2BEEEQxHYKQZEERQVHUfbSF0VoAHc/USTgeBy/LCta0rOCxOFLplVAqHOF73s%2B77fv%2B%2BEzHOCAPDu%2BhiA9BcuFmXg9q0eYICQW7EnusgKAgYXRZAYApEwmhAOibaIAiQmImCeoAE8cd4NXmGIDWsQibRMAcbXSFu%2B4CCxBhaC1lGsAiLxgBhWhaG27heCwFhDGAcR7bwYgTccAA3eNCcwVQTbhVYmuCf45pK2g8AiP19Y8LBCYIGMlo90hQ%2BICJIM9AEfaToxWvmKgDFFE08EwdGDyKprIeEURxDhlvEbUQm0f0H2UEqyx9GT7bIHmVBt3Sd3kPCr1TEsawzHW/OYywUeIHmOwg/SFxBNGFpSECYJehKfpWlyNIBH3nIUkvhgpj6GJxkqbeBE6EZPGaPQt54t/hm6Y%2B0wz62H/tfcY/8H6nyfpvWqKwJB4w4AVUga1eAbSpm9D6X0fp/SkIzZmuAQYcwatzXmFd5gIEwEwLAMQN6kE6vEeEQ04gzQ0JIMwkhXorTyq9Ia%2BhOALVIEtRq8JXpcFen1Iak1XrdTGkw16yDCYbS2jtZqFdDonUFmdUmV1xaS3Zo9NgnB6gsGDgyZCTBUQGBdFwIa8IuC9SBvgIgq89At2hu3aQnclDdxRroTCmMmDYw9ggpBKCiYcBJhdOE5wKboJpl9NEPt7K2PsRoZmrMRbs05nEMwPNVH7QFkLVAbNojXQlsUzJ/RElGBsVwbC8t/jECVirFGutNZmzafrQ2xtTa5wtowK2Ns7YlQdk7F2bszZe1LqsEZAdt6h3diVCOUd/hmzjpUQmScU6a3TjM3m2czb50LkoYu3sjBl1AAUvg1cFC13ro3M2bi26w08bILuyMSp%2BL7uXeeVgh5bPXuPSeAhp6z1rL8xey9oirzDmPNor8/AQFcGAw%2BglIEzHPrfaoKKL7VHRcAn%2B1R36NE/mMeFv8agQMAY/b%2BoDSUHwmA0fF0CFhLDgdzPhiCCYozQdTTBlikk2Lsb1fBTiSDZJIfk/m5DKHUMoAggRQjbGsIZHlIa004hsI4ZIVoYSlG2BUXzA6R1TrnTJmUvRD0nocGMbTFgChg5/WDkKs8QxHGELBq42Q7iXnw3kN4j5OgQAJACUE3GnLQmKOJto8mlNVB2odU6l1kIhjpIqaLbJcQ8lGsKSgdN7MLX5v6I6z8/lnVDX8q6gg/l42eLoI05pqt1b6w6c2g2Rsg5m36YIa2ttCajOdmICZucpnnL2aQfAgceILPDpHZA0c1mCA2SjLZqcNa7Mzgc3ORyi4l3OSKNRVclS3Lrg3XETdeBPJhhIV5CMA092Dd84wg8bAAvgEC6o7s1jhQHgvSwS9UErzBrC2hhKd5Ir3vS/waLqVQJvnkdIOKsXpGZd/F%2BFLiUorA3/SYsGMUgK6FhqlRQaUcpqmy2GITuXrU4FTBNjrzjlvhFW0VhCJXZrIaQChVD%2Bi0LmoqkAw14RxDiHlcaOqVoiYZOIhRPLODKN2px%2BheVGFTQZCtPqkhRpcAGmYeRc04jUdQfJqVbVOWA1kzRzapnZjzHzqkZwkggA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/bind_front/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/bind_front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/bind_front.test.hpp)
