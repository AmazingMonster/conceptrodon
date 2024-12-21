<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateFilter`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-filter">To Index</a></p>

## Description

`Mouldivore::CognateFilter` accepts an operation. Its first layer accepts a list of predicates and returns a function.
When invoked, the function removes every argument that satisfies all of the predicates from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? (nothing) : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? (nothing) : Arg<sub>1</sub>,
                            &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? (nothing) : Arg<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateFilter
 :: template<typename...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateFilter
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will remove every element whose value result is divisible by two and three from the list `Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>` and instiate `Operation` with the elements left.

```C++
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename Vay>
struct DivisibleByTwo
{
    static constexpr bool value
    {Vay::value % 2 == 0};
};

template<typename Vay>
struct DivisibleByThree
{
    static constexpr bool value
    {Vay::value % 3 == 0};
};

template<typename...>
struct Operation;

template<typename...Args>
using Metafunction = CognateFilter<Operation>
::Road<DivisibleByTwo, DivisibleByThree>
::Mold<Args...>;

using SupposedResult = Operation<Vay<1>, Vay<2>, Vay<15>>;

using Result = Metafunction
<Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`CognateFilter` is implemented based on `Mouldivore::Sieve`.
It transfers the result of `Mouldivore::Sieve` to the given operation.
We will use the following function to send the result.

```C++
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation:

```C++
template<template<typename...> class Operation>
struct CognateFilter
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...Elements>
        using Mold = Send<typename Sieve<Predicates...>::template Mold<Elements...>>
        ::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIAzGakAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdFxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHOaxwcjeWADUJrFuXo60hACeB9gmGgCCG1s7mPuHyMPoWFSX13dmmwzbXj2BzcBDOiUwAH0CMQmIQFF9bt8APQAKjRKN2QkwAEcvAw8AA3EjsEAAFTBeFEtGUTGGT3RKKR3wImBYiQMLOBoPBzDYADoBQibsNiF4HLtyYlKWIaXT9gB2KzygAiBysiNuSKRuwstKebj1IG%2BzNZ7KYnMO3MYrCeNOQAGtMO5ZLCQsQhSKxQQJRSqbKLW47Y7nYJXdEhSZFd9djHdl5UkZdlbnsrdkGnR5Q8Fw7F1XcVWrjZrtQAlTDIZapAn6w1Fm4stkczDGw7R2MNs0Bq28zACvmXXbbWkKXaZ%2BrZ4g3UhtmMdptcsHW/mC2LYQcGBQjsdh4g2GdJxc9vvYehsQTC0j7W6xg88m3H0%2BMAgWBTT6/tw/3gUAeQICGi8KIqu3yeuKkrStStIBtuE53IcJ6sk%2Bwp9pcl4wW6VjwY%2Bggvihq6Xr%2B/7EAoeFXIiUbvjG8bBMAt5PAcqbgX6UHNpRzxuPuN7odEcFuAhZ4EMhAqXvxT64Su2BvjcN43oRAEoWxlwgCAVqFuRqq5nWqLoqOTCJAoXj0LsDJMrcc7ms2lqfsu/bAbcoHega%2BmGZZebIgymJ4Jg1bGeipn1qa86WoFFkLneNkDkOm59soxBOtKLLwnZwrQl6nneax%2BZ5je5ldtZTyiYIQo3g5uzKpg460Fe0mxpGFhxgmtHJgxunOfQwJfLmCoaW5bG5ZZIL5bshUEMVsZxbieBxSOEAMKg3oQChZgAGzmMtsXxaIiXAiNSkgASYheJgcxzPupXlZVO3YaNyU3nVDU0XRKatQZ7VYYhRXAV1kY9XWOUhXl4W9gKI1JWRNVUY1uwALKeOgz1MTKLH7mFS5PBdsK0FdH0EGDylWqR%2BOLmp%2Ba/RqNzaWimKuL5aL%2Bf1qNHhJIGpeKWIMPDdU/STJqNqFwV84DaOkeuw6ji6E6Xt2X58qDHqs967PoMC3Huu9AkkczyVc31AMDQzVlAyLUUjt%2B4IwjUY0xudFWYyjFEQzJ1GJs1sSpmb0Tmuk2Ma6RJN3QWmnk/9gv63rjMy5FG6a3yNzAHFONg/uzu0SWqBMJzbtlbbdDAnHCe%2BxJRPgjzge9RTHkeMAzAsgAYnQLLELTjK852YehxHEWrqLm67B7Fve8lpVVzXmD17QjfGg7Idt1y4eG8LEk9zHG34FtmBJ2xpWxfNqBpxn9vZTJs7z4NRsg9dm%2BOzeKcw3Dz1K53TxCF51bAqvCUb4TKl63ftDK%2BrJ8MdOrg2PjGfGv994ALcP3L2AhOpHxjNzIOdxdYdwFrPBeTNbJrhNn2fOmBE5WweomKBz0d5ECgXneOhDC44NLmTVBFcGQsJYf5SmGJSQb1xs3dhrD%2BF0zrPcf4jx2LHDoOcCMmoPKwzmkQBgZxeGtyCgaY4qBdgAEl5ainFLI3eCip71UmI4ZAg4BB0lUIkJuTA1G7AOt4eiiotFl26jzaROllSEjwKkCI9ALBnFJAAd3USZZR/Mz5o12AANTENotKniCTeLwL4zA/igmoEMWdeoJizEMAsVY3YERUCeDsYdTKAcLAxNoMpexR19hmAAKy7DMCmFqGhkFuTLlpDyCSkkpLSQgBOSizKn2lmwaJsSh4KzKl4nxfiAmDMIZkre2TKS5PyU3IpJTanlNqoqKpNSyn1KabEVpWd2ldPUm45hVNYE1GGQFdBETsFxPFHcwe5cOHDVUKwdk9I/J1gNs8mWNxiDACvrfaGtsqB4gcOkZ6I8LLj0nocd58DkrKSoYcXpczUkBOCZeHFyT5mkkWZZcGylYb/zzmC4BX1y63yEF4RIuQnRllet6FqaKGDAj0fIi4hwuCoTvnIgQAq3BmGFXysVwIuANJAdc2%2B7LDKcqzlC%2BoML/iWyAm4aVBjBVSoEPo8VXBJX4RFca4EZrJIWv5cCVa5q9UmvlV9K4KCWZe2QBCYc0QCAQDeMpBQNpvVJTcMqiel4mUspSGyjeKrLinVzBwBY1SOANN4H4DgWhSCoE4BxSw1hdgKCWCseivweCkAIJoZNCx7QgAaWYPk8ozCSAABytoaRoAAnA2jQy1W2xH0JwSQvAWASA0BoUgmbs25o4LwBQIBJ1Vqzcm0gcBYAwEQCAJYBBEjHHIJQNAbI6DRFCDaTgqhW3LQALTLUkLsYAyBTFSD5GYXg8UiDEDwOgPQ/BBAiDEOwKQMhBCKBUOoFdpBdBtECTCRInAeAps4Omqd1ac2cG/McPd3pUBUF2Jem9d6H1Pt2C%2BlpEAPDHvoE3DYXA5i8GXVoBYEAkBHqlNRg9EA2MnpiMAKQCQaATwApQCIaGIjBAaGcBDvBxPMGIGcb8ERtDlmXRWo9AlvwMFoFJyDWAIheGAAaWgtAF3cF4FgFghhgDiF01NFThIN5ocwKocsxw1gVuCCyVN2bTgRBhPJjwWA0PQjwGOszpBqzECKUocqlmjCnCMNWhYVADDgqiV5QJHtM0Vr/cIKkQHpC5bA2oND0H9BWZQNYaw%2BhkkLsgAsVAiQaimevW8BipgC2WDMDOyLX6sB1YgAsOw9nnAQFcGMVopBAjZhmAMNouQ0gCAmzkFIi2GDTH6GUdoI3agjCaJ4FoehhtwoEF0RoG2ShzdsHt5bEw9sXdmHRxYyxVgSCQ2mjNaHZ34avbe%2B9j7n2SFfbsCAuBCAkHqbEOjDGksLH/BnAYg3SB1skLEPkXbYjykkBoSQLbloToactLtQ6OAjtIGOqHfJlpcH7V21tNOGmSDlRj5aqHIOzvnYuytSW12bpY9urD%2B6KBcdQFR0956OANBYASeU16mCi0TFwLtfIuB8mzR%2Bkg37f2yAA%2BIYDRWlAlcg7oBIsG9LSfeyh6dvBZ2Yd3ccXYuHdhS5l3LhXtElcq7VyDyj7HoiQ7MPR7nK7mOsdF37sgwvuPUZAC72XQ4jBK64JOwTjcF0QFE5B2TknpOkGz/JxTymHC5/U0%2BTT2m0N6YM0ZkzueLNWZs9m/AcU4XVlM%2BrlzFYWS5881UNDvn/NnEC2sbNIWwsVsi9FzAsWG80R5ylpgaWMtZdz7l3XBWQPyENxB7NJvyuJY61YSwNWIgDYa019ILW2tu0P9YbrNvevfsc/V7bJ2/BjY5rdqbHMHtXYWzUL/f/dIX/LbY7GoM7fbLISbMAzoe7GbTbI7G7A7cYa7KYeAy7MoIbEtV7J7VNK3L7TgZ3YgaXWXeXBPD3ZXVXDQEHMHT9SHaHYPJjOHTABHGIJHVNMnCnZXHHeUBpLteUeUWIXHSQO9Noa3dDOdWwLnRjVdddLdHdbDTjaPcXNgTgKXIjFgBQAkUxAkT3JsYYd9fAT9LXNoNffLCQQrWQYrHfHQEAQdM3eDMzS3T7dnDDQXHDPDdQ%2B9TQ7QuxPQiyYYH3cPHjSHWIIPGQ0PFAYIjjKPaIgYbQllCEXQrtCEfQggb1Ygu9PgBuYTDPMTCTeTXPfPBTJTFTEvUXDTLTHTJvTAfTQzMQWvcLeveLEfczOzVvRzSDZzVzbvcLXvbzXgAfSTYfYLL9cfXgSfGNGfeLOfEPPgVLBQdLTATLHkVfHXcw/XKw7fUrOw/fYwKrY/XzM/HNC/cxTgJEANW/LrHraIPrZ/JHGA0bcbZAybabIoBA%2BbVbAAl4lbPIYA9Ax7V/cApAqAo7KoHbCAkAxA7oL/SYc7AEubLAl7IDZwtnGdQgrw3YHwnQ/wxKBaWgiHWjcI2HUgeHLANg97TgkAMwZXWIWIBpTtJnCdOk%2BUftNEm3TgTnJdEklHeUV9XgrgKQLtHgjHLgeUEnWIFw9EyQiI97N9dkiQmHEPBYSLVIZwSQIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/mouldivore/cognate_filter.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_filter.test.hpp)
