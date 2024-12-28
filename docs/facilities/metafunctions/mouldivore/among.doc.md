<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Among`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-among">To Index</a></p>

## Description

`Mouldivore::Among` accepts a list of containers. Its first layer accepts an index and returns a function.
When invoked, the function instantiates the container at the index from the list with its arguments and returns the result.

<pre><code>   Con<sub>0</sub>, Con<sub>1</sub>, ..., Con<sub>I</sub>, ..., Con<sub>n</sub>
-> I
-> Es...
-> Con<sub>I</sub>&lt;Es...&gt;</code></pre>

## Type Signature

```Haskell
Among
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class...>
struct Among
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will pick the container at index `3` out of the list `Con_0, Con_1, Con_2, Con_3`.

```C++
/*** Dummy Containers ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** Metafunction ****/
template<auto...Args>
using Metafunction
= Among<Con_0, Con_1, Con_2, Con_3>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Con_3<int, int*, int**>;

/**** Result ****/
using Result = Metafunction<3>::Mold<int, int*, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

Note that we must instantiate the container before the comparison.
This is because the function returned by `Among` is an alias template pointing to the actual container in the list.
It is not quite the same as the actual container.

```C++
/**** Vehicle ****/
template<template<typename...> class...>
struct Vehicle;

/**** First Test ****/
// GCC compiles.
// Clang and MSVC fail.
static_assert(std::same_as<
    Vehicle<Metafunction<3>::Mold>,
    Vehicle<Con_3>
>);

/**** Second Test ****/
// Clang and MSVC compile.
// GCC fails.
static_assert(not std::same_as<
    Vehicle<Metafunction<3>::Mold>,
    Vehicle<Con_3>
>);
```

However, after instantiation, both of them will converge to the same result.

## Implementation

We will implement `Among` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the container at the index is returned. Otherwise:
  1. Drop several containers from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `Among` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<template<typename...> class...Containers>
struct Among {};

template<template<typename...> class First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<typename...Agreements>
        using Mold = First<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<typename...> class First,
    template<typename...> class Second,
    template<typename...> class...Others
>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    {
        template<typename...Agreements>
        using Mold = Among<Others...>
        ::template ProtoPage<I - 2>
        ::template Mold<Agreements...>;
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<typename...Agreements>
        using Mold = First<Agreements...>;
    };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    {
        template<typename...Agreements>
        using Mold = Second<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIaa4AMngMmAByPgBGmMQSZgCspAAOqAqETgwe3r7%2ByanpAsGhESzRsVwJtpj2jgJCBEzEBFk%2BftJ2mA4Z9Y0EReFRMXGJCg1NLTntY30hA6VDFfEAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYSa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzCFkN4sDcTKC3MhRugsFRYdhgcDfv8sftAZibgBJFhJehsQRMWoMT4HXHY2mndGXAiYIkGJmwtxMlnkzDsggATyezDYADpRaibpCmAoFKLhR4ybNiApUcDRsQvA4bhcWAJgDCAOxWfV3WFWS7AznE7m85lWtlw/mC1iYWXiyXSm4AMTwSoIKsuao1BC1OqM7O9vv9QMNwJucZultZPLhaQAXpgAPrB/FR%2BM3QOa5TEVBEZRMYCYA1Gk2gs1Ay55xPWlN4dNZgm5%2BPETAARy8PveNwgOdBNbuGiWsfjBeDRZLqDLFfZI7RDfjJhja7zcab9o5AsYztlF2A3eZjAIytBq4u2/jXjSRhuAFlPOgYaOvT7RuyT2fSZerrXqaU5xhuNZ1qBCa2km7JMF4RDHqemDnoIV43nmD4hHqi6VrCdw3HOpblsmbh/ihAEymKwG1uixogeajIwda5pwlBu6kY6h4itR2ASgYHoRqMpDscxe5cUKLq8fxUofEInQCOgIlbtBXLiQeklAXx7pUcKADyBAIDEyqsTeM4hrq4bfgQpA3PJaAMEpNwGUZSpaXRdaNmJpFppm2adnG5lEQuJEwipG6eXeql2pxGlHqK5GoZeAXblhT6vrQ774RZYZwi5xnuSpeYgCAHGEcWxFLnC%2BI3AAtDcZgpcVpXeS%2Bb6/shSW6SqtHhfRvX1re8YceyvntiuUHdn2A4fMO%2BH4ROUFBRVIVVW4E19ZFd4jQ6cU8cKiWUU196PnqGVZZ%2BQl%2BnCh0Xt1NFbQaEEMkNO7eaNrZ%2BR2wEqVN/bdrNI5jlwk4qct864cuKURVBXlqbFTr7bdaHHXGaVnW%2BH4EfZikdf%2Bd3uQNebgQxg1wzFcEIagSH4yjP2vTc6OEaF2XBZDN2dZRhOQf1kE/HSWI0rcV03NgqisMSlZfBiAv/IC6JghCUJ4XCDmbEkyX0zL%2Bz3D4LB8jc8oNIqHzS0x8O8ntUnClG5nyhmGikxa727Yj1u2wQ6qavbXBO%2BbFOu9x7v03bAgZo1A3Oxbgeabxqqe0Ghth6CftXIcL6YA0VBeAwXQCFSOJRwHbjwYhCXEMA6HAkzz6Z0w2e5xS6KftqllwvbGi2T7Xdh2YPcMBmKf0yV7NkRX91opH/O3EIXhJCkSjoAASu8Xi0MGZsXEzs/z6kmDL6v69Y0nA9D24IQ2TcF%2B7LZ1%2B7D1fNp7cK8KGvG/UtXp03C/b/H7XWc5zzgwdkQ9sAlXOuyC%2Bt9BA3yvjA%2B%2BD0Xp4gACrvHfoXAMDRHDIAzLJGIBAICIhKgoZ0uCrxuB/uvWyO8F770oddbAk4p5P1licIWOscaOVFuLFkUsP7T1YcceWAjdg3AAGqYAQHgSEfCMEXB2hyF2%2B43ZaRktKQqFxzISKkTI1OeIRaoNGAXekPxtg3AAOJuDcBKVARI6DvBtqYw2BgnyGHfM%2BIQYjrFUCYHQRxmisHSLIUoJohCCDoGIaQqU7IoLaOkfQdk/966AKbnCUB4D2rXmUgzOJuj27JyjKiJhj88ScPfIY9BJirhmLcC4vUbiXyeOsWgOx9B/HbDMZY7xvjaAynjuSIJeDQkMBLPmcJkS2BkJiSpXJCS4RJIbkAkBqIMmZVRNkvMszSL21Ac3RhpoOArFoJweIvA/AcC0KQVAnA3DWGsPmNYGw8Jgh4KQAgmhDkrAANYgHiJIYUGhJBcH1KCDQ8QNBmAAGyQrMAADlhfoTgkheAsAkBoTu5zLnXI4LwBQIBO7vIuYc0gcBYAwEQCANYBAkgIXIJQFpSR7HEDCM6TgqhYWQtqpCyQNxgDIGQDcKQwozC8H3oQEgeAIlcBkIIEQYh2BSBlfIJQagPmkF0NKgA7sQJgSROA8COScs5arsV6QQjS4MqAqA3HZZy7lvL%2BWCv%2BWYIcHhWkxBhC8pYvBCVaBWBAJADKmV0ogEG%2BgsRgBSD7jQdexlKCRDVZEEIjQ%2BT6t4Em5gxA%2BR6UiNoTohLXktIAnpBgtBU1EtIFgSIXhgAl1oL0tNlbmSGGAOICt%2BBuxdAAG7vDVZgVQnQEJbFeRfaoaraB4EiDqrNHgsBqs9ngVF3BeA9uIJEPeDwWAtonUYD5KwqAGErmIt4mq9KCkbfwWVohxCKsvcqlQ6gK0av0C2lAdzLD6EnXiyAKxUAawyHijgtVET4VMJYawZgsWruIJK3tP6qg1AyC4RyEw/DSqCLMEoZQ9ALwKJkTwrQcP5ApP0LDCwEP5u6NMVDegOhAJ6E0Ujgxyi2GowRnI0rRi9CY/McoKwFCPM2BIQ1HBTmkExbwbFNqOVcp5XygVQqXUQFwOK4gnrQQgx9XulYRkmBYFiBAb5/hQTCgAJygn1JIQFZhJCQvRfESFpnEUcGRaQVFGnhSQq4JC2FpnYXeb%2BVweI5nIXiZNZwXF%2BK3l7pJeSgNlLzW0ooKG2xjLw0srYJwRoLAu36lqkwGST4uCmeFFwAFor8BEBg1KpVcqb3SDvYoB9ardB921bqtNImxMSauZwM11KEI3CtdJu1PLJRFZK2VjQrrUtMvU2Yb10WiX%2BsDbN8NIaw1DHG5G0zXBO4xqZEqeNibk1ZsbRmlNOa80OEbUWi8Jay1qqrTWutDbl1Nq3UYNtlyO2UZ7YBy5/bB1MkbaO45FaJ1TpTbOrYlyF1Lteau9dShN3buwjFg95YFDHswKe8972711YVQ12QTXVVPpAH3Opb7wMfsh9%2BwzVz/0CEA8B8JoH30WEg5J6DsGGf8eqJR5wEBXA0fQ45Hj2HpW4YpGLvIaQSOYeY7RwX9G2PZDQxRtX3Gle8do%2BrwjnHpiS4WPxwTCquvGorVJ21snCt6mK6VgFQ4VNVfU5ppbfqdOYD00MRn4PXPuZK4C/UwX9QgskDZ7l0qevYsiwSmLpKKVUotRttbMQMtbGy/algCgu0Cq7Y7pMowKuqclXoQn17idKrJ4%2By5uhQSkHa3q5dluwvW764ly11rVA57zwXov3IjEQDdWlj15hQSgkW764l8XNtkGS/PkA%2Bf54ZkL6ZjMxeCAZl7w1ugh28UQATRWi7Z33un%2Bzbm/Nt3bHFtLeWn7mBq21rEG915WBPutth7wX73be0VqB2QCHVB0EDHQh0nWnT5Bh3nRgwRxXRiGR0wFRy%2B3R2Wz4EPWxxPTPUYAvVkCJwkBJ0EFrxaxAEb2pzAysDpy/XgF/WZwYEA22CIQoIgygxiGqzg0ZzowpGQ3cHY01ww2KGV2l2IwyDlxlwyBNxYy4Ko16Dl2kLqGN11yl1Y1kL4P1x10EL1xBlWHWCE20PB263Cw4BtT73zxuHX2FC3xd0qxIHd2n201IF0300oBE0D0pxK0n3iHBSBXRUn31B83byxQi1sCixnyWCM0kHiDM3iFhShVM0kFMxBQsy4DIM4FBCtyCJxU90%2BWcxFUCMk2CLCJWFXTSGcEkCAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/among/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/among.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/among.test.hpp)
