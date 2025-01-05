<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateSlice`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-slice">To Index</a></p>

## Description

`Mouldivore::CognateSlice` accepts an operation.

- Suppose its first layer is instantiated with an index.
In that case, it returns a function.
When invoked, the function collects all arguments with indices greater or equal to the given index from its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>I</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function collects all arguments of indices within the interval from its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I, J
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateSlice
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateSlice
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};


template<template<typename...> class>
alias CognateSlice
{
    template<auto, auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will see two examples that demonstrate two different use cases.

- In the first example, we will collect all elements from `int, int*, int**, int**` starting from index two.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int**>;

/**** Result ****/
using Result = CognateSlice<Operation>
::Page<2>
::Mold<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

- In the second example, we will collect elements between indices one and three from `int, int*, int**, int**`.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult */
using SupposedResult_1 = Operation<int*, int**>;

/**** Result ****/
using Result_1 = CognateSlice<Operation>
::Page<1, 3>
::Mold<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateSlice` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

- In the case where the first layer of `CognateSlice` only accepts an amount, we want to remove the elements of the given amount from the front of the list.

```C++
template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        typename...Targets
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the uwanted arguments.
        Prefix<I> auto...,
        // Collect the rest.
        Targets...
    )
    -> Operation<typename Targets::type...>;
};
```

- In the case where the first layer of `CognateSlice` accepts two indices, we want to collect the elements between them.

```C++
template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<typename...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the uwanted arguments.
        Prefix<I> auto...,
        // Expand `Prefix<J>` to collect the proper number of arguments.
        Prefix<J> auto...targets,
        // Remove the rest.
        ...
    )
    -> Operation<typename decltype(targets)::type...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke ordinary functions.

```C++
template<template<typename...> class Operation>
struct CognateSlice
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Shear<std::make_index_sequence<Amount>>
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Incise
            <
                std::make_index_sequence<Start>,
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEgDMGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQnJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZiSEWQ3iwdxMSTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7spiJgaKpvkdgQRMCw0gYWQSCCiXsw2KQ7kxEahydc0DjngRqbT6bCkg87gRiF5MHCrNdQf9AdrDsCtXcAJJs%2BhsQRMJqM3WanU284Um5UoQITBtS1264s43m1Xw7m81g%2BjHXSbKhx3J0u4iwwJWQIPNX2z3s70ErIAL0wAH0CAA6PMG0VXENeMMRtqpgjoEAgCJYVSZpQARxVEoJBrzOfJSSDIJjoLuA8VrOTnOug7lbn748HSY5PrcfsYAY76LuUKYCi%2BAHkXsRzTlSFPp4qeUu2B2ACptYCYAgKI9ynvj%2BaOZBrgSTTAANzEguFdzwdAUVoB8IAfcddl2O5sFUNJDHQWEADYNBpOk8FUNtyWQxVUHfLxBEVZ07i8AB3QwWQQ68fEYO9OzHY9pTQjD4QLbs/yIDtD3o49ILuPJGkIzA7lpSY6KuBi7ivYgb1ovMHxWB8AFpVx3BJ9wELlTz5ISpJkhRq0XFduwTDU4xMkFKXuA0cTwJQ3WZYc500/1%2BRPFzA1BYsw2s947JMPszKSdULKuWcU3hdMs1zfMBUi7MOwAKULLypR82z52Jata0wesmxbbY2yM7BYsrLKGDrBtMGbN55wSorC384LxzCzlfUc8KFy05c5LY9dNzuVS9yaQtn1aV93wYT8f1odjcMA4DQPAwdeJguDyqQlCZXQzDjOwog8IIggiNI8jMEo6TqMEBQxIk1D6R27BZs4paBxW2D4I2u7tvhJLdo0HD31oASjqEtJiFQXc7gYUYo1QKhBQu01aJexj7p%2B1chQ4vMpj0rjxIY3iACVWVQL8hJB4TPlzFGV24u4FLp5S2MG9SGGcs8hKwKFFwgHHbwUFYDNPeqgsxQLgute4PGAZgWSEZFtns0EWvnFX2e0oq1wMfqWeG4zgyVEspWl2XMHlvACtMpqZ3a1q3Di6LO31/GBxS6VUCIZQmBvaNY3jUWNTptWIrwDNszuK4WA2QQRsHN2aQ91AvZvAlI%2BjghY4HRqUeDzr3I7bATRo%2B9nYkrwsiMO4AFlPAQuEFS52hFxRsC6YkstiArKsQBYJgAGss2y3Kqvy%2Bc0/wjPjNLiTBwM22hPmkD4V1nJ0QgTKQEXTNAJo1ECUL1li/JAKHg7BmXenBSA4v/z/YloP59TUOovDKYCFi5/w%2BwcrM8p5s8BEncCAAx2gTnrtBcq59RqhilAnT23t5wgPfhA9Av9s5txtl6O2i4NZ5gPkjEuT4GLlwiMAautc5QN0wNzU8LcUbjjSkoehg4CTMOPBvXuA9t7lRypVaqrZ4RIPRHjGeDEOH90Hjw4e/CCrwm/ugRSQjp6iN/hJOeWCF5ASXm4FeGluzr1KpvU828sCCD3nIouV1j5%2BzPijK%2B1ss7i3tM1R%2B8JMaoA7FcYAtJD5WOUcRCuZDk5CXAXApOCDU7eMwL42STsMTX1vuZSWtoAR6ipAAMQAZMaCqhWDsiEj8ZJKTTjAkxOCSE0IQnwnFNsNId4GqWUOANXcrMlYelcXnDm9UDYwOaWpPW98HT3CEF4NIxQzrEwUF4JubSrgkMriMsZmQJmfGmVKcBui2bwgiAQQ4AodmHC7IM/Uky1mzPmWQ05MzwEm29ObWROiWl6x7NWYJBIzCFmrDXWgqDtmCH2YIfYALdlAoAoC/YRz7T6gvFTWZL4LaZg3EodoBju4KADIikubhFnjPQFc5B%2BL0T2KhcUwEaThnUIEAhGCeT6CzK1KSwpgchlNJxcsvFqyZnujmYE8MozcX4szFwShfShqrz%2Bbs4Fhyp7HKpPi85vLBXCpuagGWdyFbzk2Z8kAbz4RcAFEkbV3zfluB2VKqVoKDkQplSS%2B4MLslMqLGNBFSKEgEFRdWdFbBMUEjZUoDlUym5CoFEqolaoOBrFoJwfwvA/AcC0KQVAnBJyWGsHcBQGwtghPBDwUgBBNARrWH3AIkgcwaAABxmDMAATmrVwfwFby1cECIEaQUaOCSF4CwCQGhUhxoTUmjgvB9KpHzfGiNpA4CwBgIgEAGwCBpEROQSgaA2R0ASFEAMnBVDlsQopRCkg7jAGQG%2BKQOYzC8DOoQEggE9D8EECIMQ7ApAyEEIoFQ6hx2kF0Pqkie40icB4JG6NsaC2Js4FuREi6pRwzuDuvdB6j0nruGeswQCPBrvoFGLEXAVi8DHVoNYEAkCrrSOusgFAICkfIyAYAUgzB8DoCyYg%2BkICxDA7ECIbQUSAd4Jx5gxAURbliNoahY7c2rqRluBgtAeNfqwLELwwA3BiFoPpbgvAsC9yMOIeTACxN4DJuphNOVqGIh2LmnZDQwPIliHuQTHgsBgaVHgbtGnSBk2ILEZZTxtPAGREYAtawqAGGAAoAAah8Eiqk425vvcIUQ4gX3xffWoMDP79CGGMNYaw%2Bg8CxH0pANYEMmjqcUsSeuphU2WDMAOzzxAd6FYgGsOwBnnAQFcDMPw%2BqwgRBGFUMY%2BrijZAEF1vQw2miLBhnoVrDh%2BhvzG/q2bTQkFTYGzUWwC3PBdBm2/NbyxcPrE2NsCQwGOAxtIP23gg64O7v3Ye49p7S1oYgLga92Gc14bzUFtYzomBYESM10gxbJBJBzNWpIraNCSDMJIZCGh/CIWrfoTgnbSDdqSFwHMiEuCIXLdWptiF/CSHrRDxCl2wODuHSAUdQXJ0zuI3OqDS7KPUaw5utgnA2gsC/IERSTAtZZZQ9WnMWOTP4CIA1qs%2Br4uPqS9IFLSg0tft0Axv9TAAMabOxdq74GOCQYXYiO4sH4P3cF5XLgIuxfodQJhhIsJwRmC%2BwRidjO2cJGXVR23ZGsMoAMEYS3XBUg0CbgkVj7Gv38e47x0gUfBPCdEw4GPkmaLSdk2BhTSmVNA3U7mrTWXdMJvwLSObRmwOmeQOZmPVn20Jts/ZlEjmdgJpc253NnnvNKF8wX0hdOQvewi1FmLMfZeJefQr2QqXP0JtV5lwLVWrCWDywV%2BAxW6k5DKxV%2BUC/rC1eu/Vxrq/ehtb8B18qi2QjlX24N9ImQRu5G2wUIbd/Jt9aWDf5b83BgX8/wIVbb/pslstt8hutNsFgAD1tTsjss0oD20ddKdOBbsEND11wLcrcy0gE3tJcHdMdncftSA/sAdKAzs0cMcRdodAh/Bq0W0kgYc4cScKcv0qdbAadvtx0iMGckB51oNPd3diAOcdhudEMWAFAvw3wvxLccw5xJhL0Jcb1pdX0Esn0JAJ830ldp8dAQAkhSB1dNcgMUdztQMmCINmcYN4ZVBhDRDxDJDpCpQIAMMfd7csQkg8D2DJ0SNvdyNeDPDfcxCxlMwJDq1MxbDMwLCFcmMw9KAI8E0485Nc1YiE8xNk9bcpMZM5Mi9MBFNlNVNc9NNWQC9m9NN9NS9Phy9VAzMWRq9BBrMv169uMm9nMGs29eAO8fN8idNe83D%2B8wtItMBoteQR9ZA5dx9FCp90stC59stqsbBbMms19StOBdhMod8as6sEgpdSiitj85t2tOtH9QDesKhADb8SgcgL8Jschr8Ntf9mhgCdslsGgT9/8jjICgDv99jdtwCXiDsWtM0TtDs4CjCB1ECwi7gRCxC7hAipDvRslXs5CPtcD8N8DCCxggd21SCQAa0cwkgkh/AG0Sde0cTAg8dGDgSh0WDad2Ci0QBJB/Bwdm1Ahe1y1JA60uBK0zByd20kggTrtOAkSqSDCL1STeTySXcVg1hPMshnBJAgA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_slice/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/cognate_slice.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_slice.test.hpp)
