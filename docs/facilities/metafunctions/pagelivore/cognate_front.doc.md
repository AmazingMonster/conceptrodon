<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-front">To Index</a></p>

## Description

`Pagelivore::CognateFront` accepts an operation.
Its first layer accepts an amount and returns a function.
When invoked, the function collects arguments of the amount from the front of its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateFront
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateFront
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
}；
```

## Examples

We will invoke the `Operation` with the first three variables from `0, 1, 2, 2`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result = CognateFront<Operation>
::Page<3>
::Page<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateFront` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

`Fore` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<template<auto...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...targets,
        ...
    )
    -> Operation<decltype(targets)::value...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateFront
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Operation>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsAGykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7gA1Jgo75HYEETAsdIGZkEpiI1A0tp4Jixejk66TYheBy8tHXExJCx3eaOZB3NAMSaYVTpYh3LlEO4ANzEXkwsNltOI/MFmBlDzhcuttopNypymImBoqgZhyZLLZTA58IIKJezDYpG13OFVxV23SBDuLrdeA9cIedwIYqtgSs0spgLzP1B/32dwAkqz6GxBH7cp7zoX8w26zmnfcAGIkY0F67M8t%2BzNuQPB1iZjEi9PiuPt10mqxJG1Zx0933%2BtzZABemAA%2BgQAHR7kuR0UTu5T/vEkAgCJYVSbpQARyNOP7Jb3O/JgVHINloLuv7TPvZfsl0AzluVfdFlQMBQvgAeReYhqwESM/3lVpFWVAQ1QNWhw11PB0BRWgfz/CBiJQ39dl2O5sA1Qx0FhFINATd0CQPD8TEYtMeTQLxBDTBBjTaYAfEYAgvioYhUBYfjjQk2Q32uci/2YpNWIgnVUFfKZgEwMTSDI8jwMUv8VgMgBaCC4ISRCGAJLAoUHTAIG03SFBWC9sKNcD2IXaU5wdZsizuDxgGYZlW0kviuyuYC%2BwJWKVw07zsEgphoLuKyEKaQ9xwlEKwswCLZExb9jN/BKzzwDdtzuK4WA2QRkL/I8JRdVAiGUJgdIMmVsyuJTyoAuL4SSvczQtegFCapSvGyIx4y640UzuezaEcgyUNIsqBt/U8CXPEAWCYABrLcr3VW9MAfN5%2BzqhqCHfT8dpQi8KrufDCIJTKbPRCBaTReFxoFSbyW/OdX1M7aUNM3z%2Br/e1YYMirQKIV8rmAV0WVEqb2O22aImABadNhQJUzajrFoJdHMcrMTkoCr95z6%2BtG0ZFnDmo1RWDZTs2dzVmmxBaVwUhaElvhaNnjEyN2eLb6mlrb1e0SsC9xysUJXl3IGdlu4hC8dISkwdAACVPi8NbFdBfH5v1w2smNs2FAtuNlq1pD4Q0MMuDDMx32Z/niydl2reuG3CeDy3lvyvsisa%2BF3ds3GrgvTruvhQJI1TynPe933ff9x0goAFU%2BONooVPBkE3NKlHaCADoUYca5xtw7aN03zbWsNI4ej8YYsDg1loTh/F4PwOC0UhUE4NxrGseUNi2JbwR4UgCE0Ie1mOgJJB3DQAA4zDMABOE%2BuH8Q%2BD64JIkmkEeOEkXgWAkDQvYnqeZ44XgFBAL2N8nkPUgcBYAwEQCADYBB0iInIJQNArI6AJCiMOTgqgD4pDMikSQdxgDICVFIHcZheDG0ICQfCeh%2BCCBEGIdgUgZCCEUCodQgDSC6B9gAdwQukTgPBh6j3HpvaenAYKImgXGVAVA7hoIwVgnBeC7gELMHcCAHgEH0C1FiLgKxeAAK0GsCASB4HpEQWQCgEAjEmJAMAKQZg%2BB0GZMQX%2BEBYiCNiBENoKIeG8DccwYgKIYKxG0JgBwXjSDwNpjBBgtBPEsKwLELwwA3BiFoL/bgvAsBHSMOIWJeBXQODwHqT4gj1TBMRDsNeERmQPynsiWICE/EeCwII9MeAX5pNIIU4gsQHZPEycAZERhN5rCoAYYAChqQfHYVZCea9KHCFEOIOhczGFqEEWw/QhhjDz0sPoPAsRf6QDWKgWMuRUlmWJCmUwlhrBmE/p080WADkQDWHYYJTQXAMHcJ4LoegwgRBGNUMYPsSg5AEDMPwwKsigoYIsUYiQfavPyQIAY0xvmFARQ0N5/QphDH%2BUsIFtgcXgr0PMdosLAXwpeUvbYEg%2BEcDHqQD%2BvAv5SPQZg7BuD8F7yURAXApCNGr20evIZawBJMCwIkZ5pAd6SECDuE%2BgQ74aEkGYSQjEND%2BBSCffQnAn6kBfoELgO4UhcBSAfE%2B18Uj%2BEkBfBVaQmVCO/rYP%2BwrAH6LAQYiBoiYFmIseo5BbBOBtBYHqJIZkmCpXmlwE%2BO4jVTxIUQB5FDZDUMWdIZZShVksN0LYzhTBuFpLpQyh1X8RFQMRHcCRrKZHYKhJshRMa43KNUcY9RsJwRmCFbooBnq/UJFgeYqSraxh1qMNGrgXsaBrQSE4lxLCfEeNCQuvxASgkhPaeE0SkTomCLiQkpJtAUmhIyZs7JU98B5McIU1J8bVClOZKEypDRBG1PqSiRpOwp4tLaWvTp3SlC9NPQTIZfBRnjMmdM0JczU20PTbIFZzCp45o2YMq5Vgdm1KeUck5mFODnIIOgS52yLC3OZfc/CRTDm9Cxc4CArhiU%2Bz%2BZUOFegQVNAYxkKFTRyXLAxX0ZFRK0UQuo0i5oOKeMEtJR0ITJLxN4pY1o9YmwaWKYfsWwRLLpHssjYTaNsb97KL5Ym9thqu0itIGKiVlA6V6oNTG5VSR/An1voEFVaqbWMo05wH%2BLru3uvgJ6yBYiB19uIAGnYwbZEsAUHqJUeo9OAUmMQ/AibyE%2B2gws2D9D5CZsQzoEAwQ80Ft4Tq%2BlAiWGlu9eIyRqgosxbiwlvskxm1DpMSZwIZm3XAMMa19RIXetjFi4bTc8WT6bkSwQTctX032JnZQOdU9l0xLXkt1dbzQmbsENumJ57MDxMSck1Ja8T1ZM/ek3JWLr3FLvcgMpj7BDPpYa%2BjxH7mnmh/bwP9PSWRAcGV1kZXVwOYCmcGKDKbMsSDgww3LayCsoa2dcjDeysPTxw6qTguxzxoZuXchIDzKNSsRe8ujnyONMYBbxzjpRcgcbY7kCT8KRNNBRdJgowmifYoWPJilsnBgcakwz2lSnl5C7U%2BVz%2BnApF1di/qRrzJmu8pSyQEzWidHmcs2MKVD9bMgFPjuQIgR/CXxtW/A3qQD6eYq9551/9zMyv8PKm%2BSQ34H0kOfLgR8zBpAfoEcXzLrd%2BbpUQy3EunWB46TO3IIBJBAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_front/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/cognate_front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_front.test.hpp)
