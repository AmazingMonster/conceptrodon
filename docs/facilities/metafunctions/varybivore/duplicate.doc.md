<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Duplicate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-duplicate">To Index</a></p>

## Description

`Varybivore::Duplicate` accepts an variable.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function creates copies of the variable of the amount and instantiates the operation with the result.

<pre><code>   E
-> N
-> Oper
-> Oper&lt;E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
Duplicate
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct Duplicate
{
    template<auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four `0`:

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 0, 0, 0>;

/**** Result ****/
using Result = Duplicate<0>
::Page<4>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

One way to implement `Duplicate` is through recursion.
We start with an empty list, adding the variable while subtracting the required number of copies until the number reaches zero.

Our method will be different.
The goal is to generate all the copies 'simultaneously' in the sense that there are no intermediate stages.
We will achieve this by pack expansion.

We want to bundle the variable and each index from a `std::index_sequence`.
Then, we will pull out the variable from each bundle by a pack expansion over indices.

First, we need to create a `Bundle_v`:

```C++
template<auto Variable, auto>
static constexpr auto Bundle_v
{Variable};
```

The entire implementation is presented below:

```C++
template<auto Variable>
struct Duplicate
{
    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            using type = Operation
            <Bundle_v<Variable, I>...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<size_t I>
    struct ProtoPage
    : public ProtoMold<std::make_index_sequence<I>>
    {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsAOykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/oCqUDQf99ncAJIsdL0NiCJhNb5HYF06mA4G0453CxeBjoegAfQAblzDsCCJhmQYFQSmIjUHcAGptPBMWL0Uh3NVEcnXeaOZB3NAMSaYVTpYhG9XC0XizDSzEpCza4i6/WYEwpB5wqzXQX3B5eFl4UQK2XnUEKpUcgPw40an1%2B%2Bimq6TYheByPKPI2MBsNe0F3Kt3JMslMEggol7MNg56t3PMFgh3ZTEVBEACynnQsIrQZDFKu7drytTbmyAC93QQAHRrhlt6udwu9/uoIe0dAE4kgEARLCqCVKACOXjec4Za5X5MCGOu7cDoan7erM/r8L/FU03VJ90StAwFC%2BAB5F5iA5XJNx/DsCHzQsnlaOhKyQ0cv2wn8vGyIwaybTBYUCB47hghJ4IELC8KrAkRTFSUpQJTM9QNRl0VA18J3fbDA2DQIvzon9ALncTVRAtcwKhJhIKfK5gGITBFUYAgFEQ/DCOAO4ACUmDoMiKPQwzaAJJSVLUwQFB47BT0bF4%2BO/Bjx2Eydp0VOsgLcRzGFYTBFOU1S2Q0rSCIiXSDxHOEKN3Qdhws4LrI0uznNEyT4UXZcuN4/iq23bt4tQZQmGAMsXLuEA7nSLx9RjHs%2BwSw9jwIdBTxYJgAGt3XPO0r0wW97wJDdeLyyrP0E9L8prLzZykoggqs0LNPG9sIqI0ryuMxq9y2udLJC9TbJksaRLckTKT5H5w0OO5sFUVgWVIm6ruuuVJzpSjYJohh43lOb/zcdM0rNFCu2%2B6immmm4hSEKMSkwdA9M%2BLxaG7V6rg23T4fSRHkdR9GdqouDofhDRDQpu4qY0F9Lth%2B4UYUNGMe5UFsf0wnu1ioto1LAlafG099oJSQc1PAzMPhEnfrpz6hQAFU%2BVmPrB%2BDkAleSlHaCATxABQAs11a3CZlnDVx/HTfR9EVhDDg1loTh/F4PwOC0UhUE4NxrGsDsNi2UisR4UgCE0e21i6gJJBXDQAA4zDMABOROuH8OPY64FIUmkR2OEkXgWAkDQKdd93PY4XgFBACnQ7d%2B3SDgWAYEQEANgIWqCHISg0GZOgEiiALOFUWOkgAWiSSQ7mAZBLSkFczF4JHCBIPB2q4GRBBEMR2CkDf5CUNQw9IXR14Adzg9JOB4B2nZdo/y6gxEO7uVAqDuYex4nqeZ7uOezDuCAHhe70EdEHFYvBa5aDWBAJAPd0h9zIBQCAcCEEgGAFIMwfA6AKmIFXCAsQj6xAiG0FEV9eBEOYMQFEUFYjaEwA4MhpAe6hSggwWgpC66kCwLELwwBga0FoFXbgvAsCdSMOITh%2BAVIODwFKT4R87T0MRDsYOEQFS53dsiWIcEqEeCwEfFCeBC7CNIHI4gsQsiYCeGI4AyIjBhzWFQAwwAFCag%2BKfKirtg78E3qIcQu8fH7xUOoThJ99CGGMD7Sw%2Bg8CxCrpANYqB0hNCEaPYksVTCWGsGYMuZjfRYHiRANYdh6FNBcGKGYfh15hAiCMaoYx14lByAISpegmlNEWKMRI68SkyIEAMaYnguh6F6U0AZQxalLAabYKYHQhmFB6bMzp9TunFP9tsCQN8ODO1IKXXg5d34j3HpPaes9o7/wgLgZeoDwRcHASHBxawECYCYFgRIRTSCR0kIEFcidAjZw0JIMwkgkjF38EkRO%2BhOD51IIXQIXAVxJC4EkWOicM5JH8JIVOfyki7PvpwSu1cHl12gc3GBrcn6Ii7sg1AwD%2B6Dw4G0FgUoUijyYOBCJv9E4rgRe7JeRB8l6ECVvfx0hAmKGCUfXQmDz5MEvsIrZOy9ke04I/duiIX5vw/scjlREuDct5QAoB8CQGwnBGYe5kD67kpQSA6ltqxhySMPqrgFMaDowSHgghnCKEkMYb6qhNC6EMJMcw9SrD2FH24bw/hgjGGiIiRI92UjSmyPkZwxRyBlGMLUQ0I%2BWidEoj0Tsd2hjjHBzMRYpQ1jE2RQcXwZxrj3GeMYcKvxO8xWyAlYfUJIBMEGHsZkqw0StGFMSck3IqT0nkSHdk3JCR8nyISb0VNzgICuFadUsUyzliNKyM0vI8yqkZH3R0yZXSRkNFXc0WZm6V19JvQsc9KyRm3qPa%2Bp9lQL13PWJsDZP7c5KvxRwQ5n9J5Ot0vqnlMcAFXIFWa%2BFlrHmkGea8sYHzc4wrhdywFKR/CJyzoEIFIKsV4s4eXQlNd62Nxbm3Du9raUmvpWwTgTKv4sAUFKS0UooOzkmIvfAArV5CtkCKjte9u0hPdroYIsr5XXyhdsu%2B5HVWUu7K/d%2B7HOPcd4ymSYRrGMIIQ4EJDJKG6wMM3apBDrEhcbxtKfVEo%2BMEAlKoCeWCPW4MoN692AaOHBz80G0pjCw2CAjRw5NmAeF8LEHGkxCbxElpEXgaRjg5FCL5aoJRCoc2CDzZwgtJDi0GN9OW3glbLE1vEXWszTiypNswB45srbRPtokJ2wQkmpUgGCAOyJWSR2xLHR7CdAghG7BPLOywOT9l5NXkuj5ozcjlPcO%2Brd6Ad3TPabkO923yjPt3fesZb6CjHqW/0pZB3pnzEGadj97RNurN/QHTZimgMqZA25yeHGuN3B49y5zsHBMkAQ3ciByHUNvMoFsrDfbuWBECP4NOWLi4I5SCisjZcCW2CJValYEcQCSH8L8zOKRi6x0kCnLg8czC4tzoEZTWOK7EqgVshemP9nY7x2sMx2RnCSCAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/duplicate/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/duplicate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/duplicate.test.hpp)
