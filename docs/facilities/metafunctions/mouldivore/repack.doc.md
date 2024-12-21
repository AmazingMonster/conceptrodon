<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Repack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-repack">To Index</a></p>

## Description

`Mouldivore::Repack` accepts an operation and returns a function.
When invoked by a list of packed containers, the function concatenates the packed containers and instantiates the operation with the result.

<pre><code>   Oper
-> Con<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>...&gt;, Con<sub><i>1</i></sub>&lt;Es<sub><i>1</i></sub>...&gt;, ..., Con<sub><i>n</i></sub>&lt;Es<sub><i>n</i></sub>...&gt;
-> Oper&lt;Es<sub><i>0</i></sub>..., Es<sub><i>1</i></sub>..., ..., Es<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Repack ::   template<typename...> class...
         -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Repack
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

Here, we first concatenate `std::tuple<int>`,  `std::tuple<int*, int**>` and `std::tuple<int**>`. Then we pack the result into `Container`:

```C++
template<typename...Args>
requires (sizeof...(Args) == 4)
struct Container;

using SupposedResult = Container<int, int*, int**, int***>;

using Result = Repack<Container>
::Mold
<
    std::tuple<int>,
    std::tuple<int*, int**>,
    std::tuple<int***>
>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Mouldivore::Repack` is implemented similarly to `Typelivore::TypicalPaste`. Intermediate results are kept in `Capsule`.
After all elements are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<typename...>
struct Capsule;

template<template<typename...> class Operation>
struct Repack
{
    template<typename...>
    struct Detail {};

// Base Case:

    template<template<typename...> class Container, typename...Elements>
    struct Detail<Container<Elements...>>
    {
        using type = Operation<Elements...>;
    };

// Recursive Case:

    template
    <
        template<typename...> class ContainerA,
        template<typename...> class ContainerB,
        typename...ElementAs, 
        typename...ElementBs,
        typename...Others
    >
    struct Detail<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
    {
        using type = Detail
        <
            Capsule<ElementAs..., ElementBs...>,
            Others...
        >::type;
    };

    template<typename...PackedContainers>
    using Mold = Detail<PackedContainers...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCCSAGykAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0bEJCnUNTdmtQ109xaUDAJS2qF7EyOwcBJgsiQbrJgDMbgQAnomMrJgAdJd72CYaAIJDxF4OANRuTIkKXvR7Vve3d3Wm22mD2Bw2WyYO32RxOzDYl3O1xeyAMCgULwA8idiFD0tcAY9ngQXgAlTCJJjIADWAJMAHY/ncXiyXkDIdCDsdTgirrsbvdWS8ia8ACKYOp0F4Mqz00W/On3AD0SpeFiYSjeGvYiuZrPZILBBqhoJh3PhFz52BRaIxHkETGC0VIbPNZ0R2HobEECgJgtZIpJ4sltDB9slIWIYM9G0YBAUiIJ/IBQplKaFrK8qSMrpO0t2oqxOLxAmjXrjCatCv9LIZ8t2TIBKrJmGQS1SADdMFqlCBdULjTsa/m3OmM2yIYazXD3VabRq7bJHZG7qQxxnB6auTPeUj%2BfP0W8l07iDZ1wO3buY96CA8Xef9ZfLedr3GLAo18OLzvn5iCAhol9Yc/T1FlAxeYNHVDfZw2XaI7jLWNBAeRN%2BRdWCTysfZX0Ed9UOwF0/wA4hKz3AVQOlRkHxZLNgmAXNuz2QtILoaiRzYoV3k%2Bb4txw29SJdPi8KtT8KPHFkiMAxMv1Za4QBAWFTSZVM5WrBDh03I0n0RZQqWpTB3GPSNfWTYdaJzABZTx0HzZiJSgsFdJpAyMOM/D5MUtS6y85UACp/ICwKgqVJtApeAAVTAhgxQKQr8oKEoCuL1IQsxdmCVEvCwEcvEcWhCEOECAU06ceWfO5iGAEzyOITAAEcvDwWqMQgVIAC9MFQKhEQgCqqtmWymJeSRZkJAgnleVzoh8u5zPooQvESXIDPJL5aBJIapqjfZggIF1dt8/bBH8o6CACpNG3uOaWzWjaCxbSkaTDIzptMu55Ks2h0DpfZ1yGdAPMWn4dsEa5RKFf7Aa2LcDtO/ywb%2BggAYUoGYeO%2BG3ou3UJkcZAAH0F2iAhWqR%2BSFDOAmTLcVbvj2l4FqWlIVqi2nrlGhsOHmWhOAAVl4PwOC0UhUE4UdLGsYVFmWRi0p4UgCE0Tn5mpEAeZ585dh5rgzAADg0XY4npOIAE4ed2SQef0ThJF4FgJA0DRSAFoWRY4XgFBAR2FcFznSDgWAYEQEBFgIRJcvISg0E2OholCM5OFUHW4gAWjiSQXmAZBkBeKRzjMXgDMIEg8AB1p%2BEEEQxHYKQZEERQVHUH3SF0VoAHdcUSTgeC53n%2BcV4XOExXKw5JLqXkTlO04zrOc8kPOXggDxo/oYhpVl2ZeG9rR5ggJAo8SGOyAoCB98PkBgCkMw%2BDodYSMoCJ%2B4iYJ6kOLveCf5hiEOTEIm0VtvbllHG8mIGC0Ffk3LAEQvDAHeLQWgHtuC8CwCwQwwBxAQKav/PAXYEFC0wKoVsuVVhy12pUfu%2BUIi4i/h4LA/dxp4Dtog0gXZiARCZuKFBRh8pGEVvMKgBgqoADU8CYFbtiRgb9a7CFEOIGu5d5BKDUP3Fu%2BhUEoGsNYfQeAIge0gPMVAiRqgIOTv9JiphxaWDMC7FhxAS5RXgPMOwWDnAQFcKMFopBAhOmmP0VouQ0gCHcTkFIASGBTD6DEcYlRnE1GGI0TwzQ9BOIcB0OJ4SSi%2BNsHEoJ4w0neIiRIRxUsViFKthwPmTt%2B6u3HknVO6dM7Z1zmYBeuAi6r3MLsLgG95a8PmABJgWAYgQGVrEXY5xja7HpJIDQkgzDxAdjzE2ZSbakDtp084cQuBxB1sbHWWyeaSC4DzCZCRna8Fdu7T2PSfY70DrvYOw9w7H1PivOObBOD1BYB2ekycmDzhzFwY25wuDnDwfgIgtjS5SMrrI6Q8j65KKbroK%2B7cPhvx7uUvuTdXZD1DrlF4Y9PnfN%2Bf8%2BigLgWgoXkvA%2BK8167DMN0revt7kvOdM81Ay9%2BhEp%2BaiVBgKuCOxoOtQC99H7Py/pIj%2BL8f5/wcJIoBcYQFgP7pA6BsD4GSOQag9BQt8C1RSTg/u%2BDCHrEkaQ7mTcKFUMODQ1YQt6GMLliwthSgOHarorwvgAiFDCNEeIgWct5EwurnC2QCLG5C2Raonh5irCWC0TohxwtDHpGMaYgssbrBWPOTYuxujhltBiS4BghksgeK8UUApfiQnVByUkGt6R0kzCie0AQnQRgJLGIWlJba8mVoyZErJXQ60TAaE23xRSlglK6WUipZyB4cBeNyklvKAVApBRoFp4KSB0q6ZvXppB%2BmDMoBilZaygUzPpMc%2Bk9JzZzLTq0edFzbBXKZbc%2BA9yQ4jwjifDlNLY7xw4J8qeLAFAdmzh2clIIhgF23ZCvQQaZEhqkeG5RIBdikFRZ3RBGK51VMHo80eVAl3EBYCBsDEGoMmiGFSv9h86W7EZZ6lldGV4/tZTEcDS08aQeNnjaDBACakbTtfYVd8IAPyblKiVTDpPf1/v/eVHLgGgPAbqzAUCYFiA1UwrVXC7VIMwQa%2BxTdjVtlNUw815DtHWttXQ2xjreDOvYRsd1PCbleqYEIkRYi4SSMQ1XCQoa66KIjTodD0bjAaPjRQ/N%2BiU0CAQUqSGmbLHWOiJC%2Bxeju3VGLaWxJrQK29AHcEvI6Q63%2BOqOOwdyTqjtviWWpJ0Se2xMmPkkruTh2do8aO7o7Xm2TulqUi1eHsWcBI2R9OoHwMvF4%2BcATW62m7qYzcvpmABn9ALRas9IAzBAt2JrHmMyBX60mdsypY23Yvq9gelWkg55px1vSQFcR6W7BmXENWZTdhYpdpwfdq2yn5wu39q7b75gsNSM4SQQA%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/repack.test.hpp)
