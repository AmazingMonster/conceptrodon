<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Negation`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-negation">To Index</a></p>

## Description

`Mouldivore::Negation` accepts a predicate and returns a function. When invoked, the function returns true if the predicate instantiated by the arguments evaluates to false and returns false if otherwise.

<pre><code>   Pred
-> Args...
-> not Pred&lt;Args...&gt;::value</code></pre>

## Type Signature

```Haskell
Negation
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct Negation
{
    template<auto...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<auto...>
    static constexpr bool Mold_v 
    {RESULT};
};
```

## Examples

We will turn `IsLess`, which checks if the first argument is less than the second, into `IsNoLess`, which checks if the first argument is no less than the second.

```C++
/**** IsLess ****/
template<typename First, typename Second>
struct IsLess
{
    static constexpr bool value
    {First::value < Second::value};
};

/**** IsNoLess ****/
template<typename...Args>
using IsNoLess = Negation<IsLess>::Mold<Args...>;

/**** Tests ****/
static_assert(IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 1>>::value);
static_assert(IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 0>>::value);
static_assert(! IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 2>>::value);
```

## Implementation

```C++
template<template<typename...>  class Predicate>
struct Negation
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value 
        {not Predicate<Elements...>::value};
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCCSXKQADqgKhE4MHt6%2BekkpjgJBIeEsUTFxtpj2eQxCBEzEBBk%2BfvF2mA5pNXUEBWGR0bEttfWNWYNdPUUlAwCUtqhexMjsHAD0AFQbm1vbO5srJhoAguubANQAkiwJ9GyCTFWnW/tHJ7tvu8%2BHB4cEmFcGvxMAGY3L9/vdMMDQQBPBKMViYAB0yOB2FOp2QBgUClOymImHwokBQOw3wUBGIXgcp1CmGA9zS3xMAHYrEd0eiwdcIVCCLD4WxkYjsDdGAQFKjvhzTuTKdS8agiABZTzoKUcllsw7S6XkhnIDECcmYVQJYinCKoTynABuYi8mFO6p1TtZDEVuPxhJ5IJFfzFCiFqJAIDt3khzIAIsCtdKWdGgVrnacuQDISC%2BXDmILkX7buLJeyOV4UkZTiraOgnUDI57FagK2rfaLBIGUSSY0yo52jt9Xu9tp9%2B6dsKpWNdHU8%2BwOPkze2YgcFMV4sNWYXCAPoUpiECUd3svLYXBQBTDYx57b6pn3rgWOgBieGI5NIKf52cdQjaAibpKOsqpAhj1PbEu1jDk9UcA00AYY1TXNS1rTDB1k01R9nwIENkMdKFTi/GD0Cw%2B0IwTJNu0TOdjiPc4FFCVAQJxKcjmvYlbw/IVDmIYA9z/Q4S2CYBjzohjq1rWl6SqKEaIY4MQEbKFOO4oMOwog8qLOAAVM9xQvDZPkgvBkA3JhsWiAgIBo4Szz3NxyUIkBgl%2BYBiDEDcYL1QQoUc18uFRV87JDRy6Rc2g3KNWpPJBbzTl8lTsCI8Nph7Q4DKMkylHqCzaPo6yoQChzBGC1z3IiggvMEHy/JlAh7KC5zivCwwyqiirTg0SUSQSh0ktUlLaig4zTMysAwCEnLQJBfK6pCsLYNK8qCEqkl/JqwLCvq0KSqahbXzMDr4tDYieq1DhZloTgAFZeD8DgtFIVBODcaxrBleZFhwhceFITDbtO2YAGsQAuyREQ0AAOMwzAATihrgLvBsGuGZZlpHOjhJF4FgJA0DRSBuu6Ho4XgFBAXGfq0WY4FgGBEBAeYCASLxFooCA0CuOholCBFOFUMGADYAFo%2BckU5gGQA0pERMxeAJQgSDwQj4n4QQRDEdgpBkQRFBUdRftIXR4gAdxchJOB4M7LuuzReEJgB5JnGaA1AqFOXnBeF0XxZikGzFOCAPHZ%2BhzXMIEuGmXhydO0gICQNmEg5sgWbjhOQGAKQzD4OhfmfSgImt0gImCOpoTN3hC%2BYYhoVtiJtDaH6vrZ/NbYYWgS71rAIi8YA3DEWgSe4XgsBYQxgHEdunzrvAbTPfOTTaJnli%2BoK0bu2g8AiFzK48LB84pPAsYH0hp%2BIS0lEjP4R7XoxrdmKgDG4gA1PBMEN22s1LzXhFEcQNeV%2BQlDUPnA2%2BgR4oGepYfQ68SaQFmKgBIVR%2B4CzssCSMphLDWDMATY%2BxAFYzxgeUSoaQXAMHcJ4Jo/gSETD6DEeIORUgCBGM0RIyR6EMCocUfoLQKiTwEJ0YYZDRgEJ4dUIY3Rgi9A4TQ2wojGF6D1PUdhUww5zAWEsCQFsOBXTxvnQmrt%2BZCxFmLCWPs/a4DlsHT64dvo31mAgTATAsAxAgADWIQJERQyBCjDQkgzCSD5jjC6fMob6E4BjUgWNQ6Ij5lwPmYMoaIz5sDOGHi%2BbaL1oTYmpNrG/UpjTGOdMHZM3IJQZOQcuZsE4HUFgNpmQCyYBiAwZYuBQ0RFwUGMt8BEBwYrT%2Bqsf7SD/trQBetdAZ2NkwU2A8NFaPxjbTg9sGZM1OM7PR7sRaYhHjFFpbSNB%2BwDvHIOToFxmCsZHSmsdUCB2iMU1mlyDn9A2UYZpXBcY0FoNnEmEA8563LsXD%2BvzK7V1rg4D%2BjcxTN1bvnDuXce60D7h/Iel9lh3XwPido09%2B53TnsgBeH9l75zXhvYu29kURxwQfL6x9T6YHPsPIwV9QA5L4PfBQT8X5v0YB/P%2BfT1YDNkEM3Wd1RkgOvmgqwEDCXQOcfdeBaREHIJrGKjBWDojdLwdK1o7RnAQFcLI%2BIgRxGTE4cw3IaQ9UmtYYo41mqqh8IaAIphNqOiiKtVI%2BR9rMiOpdYa6h6iVHvT9WjGZOjOCrIMQ0zZzTWmg1MZ0kgRzQ6nJsaQOxDj%2BjSrRmEiJLTvHMgulDZGQIfF%2BLKLM%2B6nBMlkxvtHPJSB6aOxuaUzm3MOBVI9iwBQNoDQ2ijWmckHTzEKz0Ny7%2BvLP4CqASAIEpBxmTPNiEzRVt0nzMKU7F2qh22du7b2iE5I9l3ITgmoESamX5KbYnEpB6g6hmQAkBIG4e1Qw3H2ggG4N0DKztET53y7oArbl9P9QK66gsuU3FubcUWYE7t3Xu/cvqIvpaS0gqLJ4Ytnqoeevw8WFRXrwQlm9oQkt3uSj%2BVLkg0ovvSgS1a75MEfs/V%2B79D4jrVhIPlWsAGCp0FOkVxhwE2ElfAWBsqjScBWAFJVlhME22wbgqVswnXat1Q6ih6BXXZBYVUc1dCqjqa4YQ3hMiVP6eEXavT0iujmvdXphTb01HKKDUugmob32nA7V220O7fh7ogGYrpCaw4R2TamxxlANFZpANDREQIgQXXhnEHGMXmSxLSc5omtgslnJcZIC67ikbMhxmDSQsMuAQzMKktGQInNzPS1lhd0tUs1aCzk2Yx8UjOEkEAA)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/negation/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/negation.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/negation.test.hpp)
