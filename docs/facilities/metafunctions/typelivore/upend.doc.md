<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Upend`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-upend">To Index</a></p>

## Description

`Typelivore::Upend` accepts a list of elements and returns a function.
When invoked by an operation, the function instantiates the operation with the previously provided elements but in reversed order.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Oper&lt;E<sub>n</sub>, E<sub>n-1</sub>, ..., E<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
Upend
 :: typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct Upend
{
    template<template<typename...> class>
    alias Road = RESULT;
};
```

## Examples

We will flip `int, int*, int**, int**` and invoke `Operation` with the result.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int**, int*, int>;

/**** Result ****/
using Result = Upend<int, int*, int**, int**>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Typelivore::Amid`.
We will label each element by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding element from the roster.

First, we need to create a label class:

```C++
template<typename Treasure, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Treasure;
};
```

We can pull out the variable of a given index by asking `decltype` the return type of `idyl` if invoked by the corresponding `Key`.
For this purpose, we will convert an index into a type via `std::integral_constant`.
So, the final mapping will be as follows:

<pre><code>std::integral_constant&lt;I&gt; -> E<sub>I</sub></code></pre>

Now, we will assemble an overload set and instruct compilers to pull the elements out in reversed order. Here's the entire implementation:

```C++
template<typename...Elements>
struct Upend
{
    template<template<typename...> class, typename>
    struct Detail {};

    template<template<typename...> class Operation, size_t...I>
    struct Detail<Operation, std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Elements, std::integral_constant<size_t, I>>...
    {
        using Label<Elements, std::integral_constant<size_t, I>>::idyl...;
        using type = Operation<
            // Note that `sizeof...(I)` is the total number of I...,
            // which is a constant.
            // We are doing pack expansion over the second I.
            // The result is a list of form:
            // sizeof...(I) - 1, sizeof...(I) - 2, ..., 0. 
            decltype(
                idyl(
                    std::integral_constant
                    <size_t, sizeof...(I) - I - 1>{}
                )
            )...
        >;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements..., std::make_index_sequence<sizeof...(Elements)>>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7qEmPFaN8jsCCJgWOkDMyCQQUS9mGw7gAVYiYJgKTaYUh3Lk81iYO4AaUwaMCGOuk2IXgc1NpDUxAHYLLDrndjXd5o5kHc0AxJphVOliHcmIjUHc8OgUbQIAqUSs7gBadECoUisVwqzXEy6h5hik3QHxoGg/77O4ASVZ9DYgiYTQZh2ByYTgOBoOZGZzmE53MYMoAdPXsJnGAQFOTVQR1Zq5Dz0Hrw1cTZKWWyK5zh%2BzK/CpTW2PXa4GoSKFBLp7zJyqBya1RqCI9MK06LD9ZHo4F%2B6DB2WRxyp%2BPR1Pq2u5wuDAovgB5F7EHO5CXZABemAAPoEHOqZtpuxrbpqTwHrQBKfgkP4CH%2BBDoCAIARFgqhAUoACOXhvJObips%2ByoQYOuy7HcADqsrIMGzKOgwdyoAAbgktCoEw6CmvurFULCSQaG6HomMJkoIMQGzAAgroMAgCSEIY2zzkaJogHc6ReLEyIWjSdIEo2LLNsuppoRhETMsA360EBVrzIIBIAcBBASuB5HKs%2B6nGpG/aDoOXjZEYWqGfCxlZi2qHoZhgiYDZYj2QIjkEM5eCASB7nksqlnurQZH%2BQFxpBREwCStWsKBA8dyId%2BTQEheRUBVRdxRKgTEEAgOZCRoLmoFQc4QKmKziRorpfJ1spEK09IMKMDr9Wmc6kI1TUmi1ADuCB4Mgcl4F8TCWslrSCGpkFrXcLV0Y6Qp3OgqClVpTDIAA1nctrpIY2QCKxHEOpNfFWrxpGrRdLX8opdxCqKtC7vtjp3MikwCXc/DECwICg2tLV9QN9ZDb6fp3Fwf7pZg/WDcN/p3GYErLXcGi1oa51rVgULThAWMXcaomelz3ODsSllxQldkOSdqU%2BQLRVpRlbmmmTFP41TROptTXDkseUb8xdI1S2tKzeSzJrZYVvna2esaXneN5uFeE5VtKs71i%2BS5zlcNmYCZgituRUslSFABK3G8XC1WwUwdAEh7Qrey29NCyALBMC9wFYbauGYARRGy%2BTeO1hAEWmSNnnYBh04xhGFvnpSRY/EmVLYKorBsrK9e13X%2BaxlikLQrKBJWts6QthBDf3LVyEse3Vz2/eduPnWLt%2B1c0G7hP9WWxGHcpkIXjpCUmDoIHnxeLDebnKCAdlbv%2B9ZIfx8w7uYc1V%2Bk8ElZhwSh/%2Bxf4IP/yalTyNc4z3AfqfXc08r53DAWfZ%2B3ZXDv0EL/Ag/9v7IMOBBDCwceIIVfhvDEm8QTbwFJ8CBjJQRmh2kBJcCQCAQETgoGU1DfZuBvgfI%2BJ9YYShgYA7AJcLAcDWLQTg/heB%2BA4FoUgqBOBuGsNYU0Gwtj93BDwUgBBNCCLWC9AIkhawaBSGYMwABOIxXB/D6JSFwXUuppDCI4JIXgGMuAaA0KQcRkjpEcF4AoEArj1ESMEaQOAsAYCIBABsAg2k3IUAgGgVkdAEhRBlJwVQKQkh%2BiSJIO4wBkAWikLWMwvBD6EBIG6PQ/BBAiDEOwKQMhBCKBUOoAJpBdAkw2t%2BdInAeBCJEWIjRUjODvkRFElGqT0mZOybk4muizB3AgB4eJ9AHRYi4CsXg/itBrAgEgOJ6QElkBibs/ZIBgBSFpjQWGCQfEQFiP02IEQ2goi6bwe5zBiAonfLEbQmAHDPNIHEyK74GC0Cec0rAsQvDADcGIWgPjuC8CwMnIw4gwV4CFA4PAHE4WSNtD8xEOxVFWQaP05EsRvzvI8FgfpHY8AY3haQP6sQ75PCRcAZERgNFrCoAYYACgABqHwNqIXEaoipwhRDiFqWKhpah%2BmtP0IYYwcjLD6DwLEHxkA1ioGHrkOFfpiRh1MJYawZgPF/WIG6T48A1h2B%2BU0FwDB3CeC6HoMIEQRjVDGCTEoOQBAzD8N6rIvqGCLHmnoW1GKBADGmM6woJMI1NGjUMd1SwvW2CmB0WNAb00LBTWG1Z6xNjbAkD0jgoi3H9M8XcMZGSsk5LyTMuZuASnLJUWstRnK1iKR4mMCAWiQCSECLWIxgQbEaEkGYSQwkND%2BCSEY/QnAHGkAxoELgtYkhcFSEYyxSR/CSDMSOpIFbmmeO8b4jtAStmhO2eE4ZiJyCUCOUspJbBOBtBYGxXUfpDqLhClwIxtY104vwEQC16ESZiqqZK6Q0qlCyuaboWm7SmCdPhaW8t7jeCeKGZExEoy0m1stAYP9AGgNzIWXspZsJwRmHbRswJN6n0JAfbE1Aiyxi/tOaY1xFzmTEGubc5przHl/OE%2B8z53zfn0oBc2IFIL%2BngshdC2gsK/mIsVSiyR%2BB0WOCxf03FyB8V/KJXYyRpLyUokpTsSRNK6WqMZcylkGnSqcr4Dy/lgrhV/MgxKmpMHZAyqaZIxDCqOVGqsCq0lGq%2B1SJ1clTg%2Bq0KGuVRYU1WHzWWuizahodrcgOqdQUbNbrKj5oyEGpo/q9A%2BqaKGz1iR405cjc0DNlWGt9CjRm2ryx40tazeGzrea6slsLUo4bdiMOVs4NWgjEzOPE1I3optIGSDUdXXRztpBu1YESDFuxS6V0AfHbqfwRjrGBAnVO/dx6PGcDPX41zwSwkRKiSxpjxAX07HfRMlgCg2IWjYv%2B2sE5JhFOW2B8psgoN%2BbqfIODQWdAgGCMh1D3SF1lr6SewZd7dyLVUN937/3AfA93PMtjlGEircCOty9QSdlk/2a9%2BnSyQB/f3kBAHRigLE6AnjmDdA%2BMCbuQ895onhcfK%2BXav5MnBBydBVpzAEKoUwrhao9TyLrMIrRblvTzSDNGfpSZklaqLNWepRauzvAHNKBZc5jlNPuVMF5QKzAQqeTech75iQ/n6lw7lYj0LSrjWRbVVl2LTQ4W7CFuFk1ZqEhgatZq3ouXnAQFcK1kIjqutpuq7kdPOfyiDe60nprSb08Jv6ANkrQ2euDDL5Xj13WbWKOLQW8bGObscGrfjv7dwOdA4rMjQuYPVurPWRtrbvbS37ZAMY2sgRAj%2BHMfulx8/dR1EwwMrxthz30ZWP2yQ/hh1WN1C4lIkhTFcAMWYI9djAjt6w7di9mzS2FOuw/rfu%2B1h/W%2Bn4SQQA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/typelivore/upend.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/upend.test.hpp)
