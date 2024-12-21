<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Find`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-find">To Index</a></p>

## Description

`Pagelivore::Find` accepts a list of predicates and returns a function.
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
Find
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct Find
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
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto...Args>
using Metafunction = Find<IsTwo>
::Page<Args...>;

static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);
```

## Implementation

`Pagelivore::Find` is implemented based on `Varybivore::KindredFind`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct Find
{
    template<auto...Variables>
    using Page = KindredFind<Variables...>
    ::template ProtoRail<Predicates...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM2akrgAyeAyYAHI%2BAEaYxBIaXKQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxXIm2mPZFDEIETMQE2T5%2BATV1mY3NBCWRMXEJSQpNLW25nWN9A2UVIwCUtqhexMjsHOYAzGHI3lgA1CbbbgQAnsmYAPoExEyECifYJhoAgjt7B5jHp8hj6CwVGerw%2B7wA9AAqaGQw4ANWa52ieAAbiR2CAANJhdDETDoABiOMOMMh4KhMMOvRaJJh4NBBEwLGSBkZJzcTC8RAAdLyQe8xsQvA5DtiGLj8UTxaCTAB2KzvQ5Kw6M5mszDs1Usphs06cnl87bYQ77JgKBS87nKPH4USMp5G0HKw6C4UEQ7W1BEABKD1oTuVcosLqajmQJoEY0wqmSxEO%2BtQhxRYi8PyDAFouHKACInYM5vMyxXKrXqzVM7W6jlc1CW54mgzmy1vYB4pmMAgOl7FpVedJGQ6%2Bui/bMe4he1BD/2nFtttiCC2Gl7bBUfWW5ldFt6lnUavU1w5E4hjflvV0isUSwk49lHk%2BO95BgNKndV1976sG7n101N3nW/E8DtTAu2fEMhRFT0fT9MCg0DHtnRDHUgIjBgoxjOMEyTFM0wQ50nzwxClRMABWKwSOzCBFkOdN6wBEAQBYJgAGsbnSYBwnQW52XSAAvG4CFPIiiIIt5hPEw48CoVD0NjQ4oDrMwADZzCUgDbV3B03DvQSjQY5NvEwRZFjAiTA3lQ48QINYGEODQ82OdctzMojaiUUyXLgqybJorMV0c3NCJE9cqI84inM3BCC0isExJLCsy1Od92QTOsjQbM1F25WdMHbBchOVPswmAQc/RHMcJyndkcryzs0uXVdosa95kv3IhDzwY8CFIeMDyETA0HFHrUt5AB5AgEDiUCBTuN1RRxG0pXQW9OrGHr%2BsG9AevGybj3qmV5TA1qzgS3cUpreqMr/K0bSAzSCqVc93SgycYKiiziKCpCwxkxkMN69qDNTY4vtElzjjI0jKOo2j0voxiWLYvAOPxbjTj4gSHoksHweVKTfujWMwokhS%2BWU1T1Lu%2B0Vq6559Jw4zifErzMGs4hbPs/yC0fL7xLcn58cG2TiCZ4TSe/cnlMp4CtI2gRlr0kAgaMkzeeElm2dsvz8ycnm4txw5%2Bck6Shb%2Bom1aIiBRbMy9FpvU4dqm/aLYkhj3wq6C6HZaXNOd/WDeVenDMOMAwBOUdM2txDVf98G4Kj8TvPZw4zGOSx5vFO3pQdianaXBPhLd07GQ916vdOH37T9gPEKD1MHIL8LAtimv%2BcbxzgyT2zI653XY/VkKY%2BZiLV3wkfnPitUzqS4uPxG790t/LKavnTssaKgcp3Kl6qpnVtctXrKQRiprQQpaF4URZE0TxBjbclYlSXJUlDmwcVaWhek9fP2Elo/skf5UnGO6J%2BDJZ7linlWeeP5GxZUriBU8T0OrSkfIdBCx154ImIHgJg0R6DTX9hvEqygmDADTNsUc99rzZzcFgnBeCQLV0DiAd2O8YIV1ujLfaJ9x4Qhfn/J%2BgC37oH/l/WKP9SSSM/mfF%2BAAVECnZREyKkSoskW5PgMH2F4I47JBobGSGvB8sUMEHgAJKINmiKUxChZEAHdUCghAIcZIXg8EoXhtEVAnhrim0MLpNwpiRzhxTvWJ8vDjHgLarWXkbxiDAAIUQw4ABZVmTAqBeE0fUcqS12TWLsQ4oxDESFkOqnEo%2BjoT4zWQsga4mU4gEAgCkpo6TMmZHZBoHqSQU49W2HTJWOEgkUJTiZGKMwwy1PNPUxpqSWkODaacDphwum9MVsrQZEcuAjNXBwZYtBOAkV4H4DgWhSCoE4G4aw1gXSrHWGmMw2weCkAIJoHZyxmIgBIpIbkGhJBcFlNsDQJENDKSUmYAAHGC/QnBJC8BYAkDpRyTlnI4LwBQIAOnPOOTs0gcBYAwEQCAVYBAXHdQoBANAzI6BxAiKwTYqgwVKXTEpSQhxgDIHDFIbkZheCASINg9Aeh%2BCCBEGIdgUgZCCEUCodQWLSC6CSLY%2B4yROA8F2fsw5LzTmcFGlyElhxUDSXpYy5lrL2VLK%2BanCAHhKX0DjDsTZvBMVaGWBAJAFLkhUrIGS91nqQDACkIEGgtBGTHkoNETVyJmDEHOCq3gkbESjWiNoAamLHkUtXqNBgtAY2yqwNELwwAOS0FoGi7gvAsBMSMOIXNnUU2ohApq6MA0uSbEeWERkezZW0DwNEe40aPBYE1XcPAcKy2kBRHETxShsxMkMMAbtRgXnLCoAYeJcI8CYFsaNK4RzHlCuEKIcQ4r91SrUJq%2BV%2Bg50oEuZYfQPa0WQGWKgAxmRS3pgBOHUwlhrBmCRRO4g/KG2Pq6HW5wEBXCTD8EkEIYRBjlGGEkAoGQBCQb0Eh%2BocwhiVBA3MgQ1JWieHaHoOwoGGjAMw/B7DMwJiEdyKMcjsH5gIeWAoG5GwJBqo4Ac0giLeDIsOEaplLK2UcotfJXAhASBpweYsR1S7liTSYFgeIVFSDvMkNsbkABObYspJA/LMJIJSGhAVKS01CjgMLSBwoedyJSXAlJgq02ChznyuAkR00pHjmrkWovRU8pdOL8WusJbqrk5BKA%2BttTStgnBmgsBRLKdMTAMoDi4Fp7kXBvk8vwHyvAAqkj7pFUe6QJ6lBntlboQIiqmDKrLZx7jvGtUcB1cSrk%2BrpLxcS8l1LJV0uZe%2BfJa1HrbXSbMLJgLWKXVutQDauIEXyWzZG8MLrSXTRGHS1UPgdAQ1oogOG2V8bo2xtIEd84ibk0OBO%2Bmjsmbs2arzQWotJaTsVrndWk5%2BA8RzInaWk5TbkAtpO%2B22omru29sRAOzYJzh2jsef%2BqdmAZ2VvncVQLK7SEKHXZu7djATtFcPWK0rshT0ypOVVy9i6v1WFveDh9qnn31DfR%2Bih1Of1/riIB%2BnLHaikZcOKVD0HxQUYWIhtIyGsi0agykcXGHGNYeI7z3DZG%2BiC5w/UfDIuEO2GAWr6j/R5eUY4ysNY7HNkWcaz5zg8ZiAJaSyl9bfWMtZY0OJ3LUn7UTada80ginlOUE41ZmzGWfmyg87Kf5khDPMqSE13zth/Pe5dcFpARKSULai9S2lcXbcmpYAoFE4YUT9fVGMHLkn%2BWCtkMVonEr5DlbJzoEA2xSA1bq6qi3GrZXIta3qg1NuWB54L0Xkvml3RWqW566T2wveBZC5nr1kXJ%2B2qVsgZIyRrjF609cUvBBam59KztqaYaI1hERCds7F2U3XdmxmrNObPuYHzYWsQL2x1vardD8ttafsNtlQDoHMdEHTtE5cHPtc4KHIdbBOHXgBHNIJHWdKtNHKbPgVdLHDdLdHdfHavQnCQYnSVBvc9ZvSnYwG9GwOneAJ9F9SMTgcEeiNnSwX9Pjf9LnSg9XTIfndwKXPQGDUoBXMXQoTINXdDTILXKjJXDXXXbg0YCQnoBjPgo3ejVXaQnXWYQ3UXFjNjMVBrLvJFa3eLIfQvJMUfe0cfCTPlaTB1SbZ1BTTAJTYYVTTtIPfwDLbYbYEiIFX5EzNw2URzbzbvTgPzDFeTNTEASQEibTEiMFZSLTSQLTf5XTLgFvTtbYXQvjQI6wn3TtblfwvQlFTI4ycdKaDgyQIAA)

## Links

- [source code](../../../../conceptrodon/pagelivore/find.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/find.test.hpp)
