<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Press`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-press">To Index</a></p>

## Description

`Omennivore::Press` accepts an operation and flattens its inner structure. It returns an uncurried version of the operation. Check out **Examples** for a detailed description.

## Type Signature

```Haskell
Press
 :: typename...
 -> template<typename...>
```

## Structure

```C++
template<typename>
struct Press
{
    template<typename...>
    alias Mold = RESULT;
}
```

## Examples

We will press the following operation:

```C++
struct Operation
{
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage 
        {
            struct Slash
            {
                template<auto...>
                struct ProtoPage {};
            };

            template<auto...Agreements>
            using Page = Slash::template ProtoPage<Agreements...>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

Note that the type signature of `Operation::Mold` is as follows:

```Haskell
Mold :: typename... -> auto... -> template<auto...>
```

After composing with the instantiation map of type signature:

```Haskell
Instantiation :: template<auto...> -> auto... -> typename
```

We rewrite `Mold` as follows:

```Haskell
(Operation::Mold) :: typename... -> auto... -> auto... -> typename
```

This interpretation indicates that if we pass `int` to `Operation::Mold,` we obtain a metafunction:

```Haskell
(Operation::Mold<int>::Page) :: auto... -> auto... -> typename
```

Then, if we pass `0` to `Page`, we will obtain another metafunction:

```Haskell
(Operation::Mold<int>::Page<0>::Page) :: auto... -> typename
```

Finally, we pass `1` and obtain a `typename`:

```Haskell
(Operation::Mold<int>::Page<0>::Page<1>) :: typename
```

By 'uncurrying,' we mean we would like to pass all arguments together via a tuple-like structure.
The type signature of the resulting metafunction will be like this:

```Haskell
Metafunction :: (typename..., auto..., auto...) -> typename
```

Since in C++, parameter packs are not transportable notation-wise, we place them inside suitable vessels, which will yield `typename...`. Since `typename...` corresponds to template member `Mold`, we will invoke `Press<Operation>::Mold` with the results.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Operation
::Mold<int>::Page<0>::Page<1>;

/**** Result ****/
using Result = Press<Operation>
::Mold<Capsule<int>, Shuttle<0>, Shuttle<1>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Press` relies heavily on recursion.
We will showcase a simplified version that handles `Mold` and `Page`.

```C++
template<typename Operation>
struct Press
{
    template<typename...>
    struct Detail {};

// Base case:

    template
    <
        template<typename...> class Container,
// There is only one parameter pack left.
        typename...Contents
    >
    struct Detail<Container<Contents...>>
    {
// We invoke the corresponding template member of the operation
// with the extracted pack.
        using type = Operation::template Mold<Contents...>; 
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents
    >
    struct Detail<Sequence<Contents...>>
    { using type = Operation::template Page<Contents...>; };

// Recursive case:

    template
    <
        template<typename...> class Container,
// We separate the first parameter pack from the others.
        typename...Contents,
        typename...Others
    >
    struct Detail<Container<Contents...>, Others...>
    {
        using type = Press
        <
// We invoke the corresponding template member of the operation
// with the extracted pack.
// Then, we pass the result back to Press for further invocations.
            typename Operation::template Mold<Contents...>
        >
// Unused packs are recycled for further invocations.
        ::template Detail<Others...>::type;
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents,
        typename...Others
    >
    struct Detail<Sequence<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Page<Contents...>>
        ::template Detail<Others...>::type;
    };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEmZmpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLKn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMgTcBAAnqlGKxMLcAPII4jvbJQ7DAibELwOW7KYiYBQKYEmADsViutzpt1B4PemChMPhiLYADpudjgfTbniCQRbgARTAtOi3KlWSkiqE0oE/Ha3CxMJS3URKEAU2n0xnPZl8%2Bmso38un6iEs6FwhHMLk8wLYDUGMm3DxvCIJUjAnbKgAqCASyLwCluAlosLDkVuqVaSNBxBjTGQAGtbvQqAROaazTaOZhuZz3aDBOTdXTeeWBQR8YSxRLaKzi0xPcQm7JGAQFIXeY6c9KfcqAOrBhgAN1QKeRBEDGpIJIU6QY%2BCMDLBBtBtzYlQSYaoDNnqHRmIEg9uAHdCAgD8jMKoa8nQegk6ns1X%2BV5Mqu81LAiLUcejQgCAFrMrcACynjoO2gidt2Do4oEFhSlWVJykhOqXPyoGQqh0I5th66WqyTBeEQPaOs6aqhkImAAI5eIwWzeu%2B9KkeR3LFnB/Z9lWgp1uKLaNtCtEMUxVpuFxpYUYhOKodStyfhEwAMuyv7/miCQnn4IFEWByhMMAElSV2MnylKsryphvq3AASpgyAbJkY7Ipq7CYYRTK4Vhxr4ax5p6ZC1rsnaBYIVRrrNq2LHXMOyJKLGGKbjOyI0MQExJhibAJi%2BaZUMQqAsDeYYpelb4%2BWaqm2kihYmQoMWVeaIU1dyKKlWWFW/nJnX8cK9ZCTBEqRG20J1TJpCou1ZnyQqjWKV%2BKk/lC/7EqSHVzSaSq3COtwRBOU7FWgxALkuK6LYFyLblUe7FUeWmNGel4zsVd4Pg4mDPrGr5ngGjATeeyKxq6KW3AuXi0MKsTJmmRBEguob8ImVAbKVu3jqgoiNN2BGNXmoUAfd2TAThyKQbQ0GjR20kITjFa8bFtxyAwn4fbloatMiJLILCyD0M%2BiO3MjbSBome0Y9p2P%2BbcxMXaKgl0KybUi/B2aOsT7JWfJ6EKjmJM8W4tNrl5EnsagMkRTR9GMQwzGG6btVU12DW4819qckrCTrb53X8r1csNqyonW1sg1weNk3K9NnUDlLSnfmpy1w2trJ40iBNJUTunG0ShnGY7Ku9j7jUy9n/UK9CHtlQh6sIpr0eWRhqFVnrwXVW7lzACSYLcfTH4LRBUHqf7A3Qh3XevKZ1cgRrjdAg3Os/P8fyAr8ey3NgqisM8yJfD6S8Aph5iBBEvNeFgv5uGgNuYKkXaVoq1xHOn2mfGcuI1kKz8PVcMedS3bJtzCqrIudI/bElQEQMm0EZqG3/vbGmUswEFSIAZIyKFOr8l/nNX2H9CRCBdAgQ2mDqRENxhdEiZEzYIIwdg0BuDhTgJQbnCyMptakIrPPDytCjYbhNpQwsY9MDd1LPfbh81lI5zQYnfBaokBZ14XDCBqBUESUEcIyewC64bU4T/KWcD%2BHcjURPckvdGpxxUiooejDlG51ZEYsONNZ7ELYbov%2B5DW75gEZ3IRxjRH0nMQPcmVjkGoCgXY7x6iC59lnmhOue87huCYKkBQ4Md5vyuP/VObt75%2B0Sck1JcTF53CEAgMiBB6CvwOICfRHFNFXD9iUsp9BCmP2KV4VIRQPr2RSRDSpexAQBKEO0zp6Bung2FInTSGdTxXGAmE6EEQCDYmAio1kGhlkgFWdCLgvYF6tIOHZUk4y%2BkDP7mM3pidVpkkVoBLE9M5lQSbEknpElFnYgmo0gg5SJLrMdB80pXzmnbMLi01etw/SkmFLvepLRHDIAAPrUQSAQCAEx0DAQUEiRFJi3DnIIB84ZGQulHIhtiZY8oOCrFoJwfwvA/AcC0KQVAnADaWGsAKdYmxkRHx4KQAgmhKWrBTAESQnINAAA5kgAE4pVcH8BK8VXBKSUmkNSjgkheAsAkBoDQpB6WMuZRwXgCgQC6v5QyylpA4CwBgIgEA6wCCpDIuQSgaAnh0ASFEJEnBVDioAGwAFo/WSFuMAZAyBbhSE5GYXgH1CAkDwOirgMhBAiDEOwKQKb5BKDUAK0guhk3ngxKkTgPAqU0rpXmw1KIyJOuFKgfcvrA3BtDeGyNoqzC3AgB4d19BEw8uWLwc1WhVgQCQG61IHqyAUAgBOqdIBgBSBSDQCGntKCxDzbECIrRYSlt4Fu5gxBYQoliNoBy5reVuoniiBgEY81YFiF4YAiTaC0BNdwXgWAWCGGAOIC1pB8Bc0cC5d9jK7wOTItsXliz6h5toHgWIGIj0eCwHmmseAtUftIC5YgsQiVim/UYeDRgBWrCoAYYACgABqeBMDnk0vS3l/BU2iHEJm5j2aVDqH/QW/QP6UDWGsPoBDJrICrCPFjTgAa0XLVMGyywZgDU4eIIm0k8BVh2HPUTCArhph%2BGTWET0ixRjJqKFkAQem9BmcaAsEY1QehaYEP0KYnhOh6E0w4PokxBhGbs%2B57zlnk1zDaLZnc1QNOcq2BIctHBaV6qrZwW4Tag0hrDRGqNnaIC4Hjf2swgQuCDr5aR1YgYmBYESBAIVIBJCBE5FKwIKqNCSDMJIP1Or/B%2BqlfoTgGrSBavy5yP1XA/XiqlYqv1/hJByvq36%2BL/7DXGtNUVi1o7bVjvtbW51M6519q9WwTgrQWBjkpAGpgVFVxcClZyLgYrY34CICppNWa01sekBxxQXG826BSEWpJe6Ytxf1bwatm362Nv9Sl87KlLvXbFV2ntk6%2B1Sjy2YQrw7LXrZ216bbhVEejF5j%2By7XBdUroTCaiAG7/0Hp3Xu0g1Oj0nrPQ4WnV7Ow3rvf%2Bh9T6X1vtp1%2Bn9f7GWAa0yBvN4HHKglpzBtVjL4OIZ3Sh7YjL0OYd5ThvDSgCMC%2BUqRvgFHqO0fo7aWnHGXsZre7ID7uaeMgBSAYEjcmrCWGE7EUTlWmW32yO%2B6TBAKYikd9YRTwPlOqbdxp%2Bojm/A6eXIFkIy5QtLFMxkczORXP5CT8UbICeTMOc805gLaf9O58aM5nz5Q/NBYL3kIvwWy/DDC9FtYGwosFe67Fyt83EvJZbQTi7V2bsaC7dlh7yP8to%2BK6QUr5XKAxd6/1q7TXKT%2BClcqwIzXWtTbmwazgi2zW6%2BtXah1daXWztx1Ovb2xDstpYAoMcEaxww8tBMO7OXE16FN6x83WarfccZboYIv2JaH6AOHe2%2BHANajqZEN0qg1%2Bt%2B9%2Bj%2BzIGU3aZ%2BSOR8gQ4%2BK2Vq46KB2OrqOBiQd%2BHS8KD%2BUq8KT%2BBA8KMBb2dAZO66m626R6tO9Ox6p656LOhU16t6u6nOmAj6z6YgvOWG/ORGSun6eAQGeAou/64ukGUusEMuvAcuSGsIiuaGKmquvA6u%2BGYI2uJGmB5GhkBudGDGJusgZuEgFuggP%2BX2IAwQ9uxggmzucuYeHukmuwaKAm8mFgQeTKIeWALhHmQE0e7gheeghm5eDeGeKese1mWevmkRxeXmAwsegRSRIW8RietgVebmle8wGRJmEWzeGaIBW%2BwOXesBd%2BtwJBnI5BQ%2B92JAo%2BBWQ6E%2BU%2Bow7uaqc%2BtuV2gQgQ/g8qU2OqPRlII2pRTKO%2BtgS26OywVWkg/gdWSqlIOq4qkgsqXAkqZgs2aqgQoBZRRqy2I6MWMaoxC2%2Bxgq2GnsRMkgQAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/press/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/press.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/press.test.hpp)
