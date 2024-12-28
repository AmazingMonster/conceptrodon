<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::IsSpecializationOf`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-is-specialization-of">To Index</a></p>

## Description

`Mouldivore::IsSpecializationOf` accepts a container and returns a function.
When invoked by a type, the function returns true if the type is created by an instantiation of the container and returns false if otherwise.

<pre><code>   Container
-> Entity
-> Entity == Container&lt;Es...&gt; ?
   true : false</code></pre>

## Type Signature

```Haskell
IsSpecializationOf
 :: template<typename...> class...
 -> typename...
 -> auto 
```

## Structure

```C++
template<template<typename...> class>
struct IsSpecializationOf
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<typename>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Examples

We will check if `PackedVessel` is a specialization of `Con_0` or `Con_1`.

```C++
/**** Dummy Containers ****/
template<typename...>
struct Capsule_0;

template<typename...>
struct Capsule_1;

template<typename...Args>
using Con_0 = Capsule_0<Args...>;

template<typename...Args>
using Con_1 = Capsule_1<Args...>;

/**** PackedVessel ****/
using PackedVessel = Capsule_0<int, int*, int**, int***>;

/**** Tests ****/
static_assert(IsSpecializationOf<Con_0>::Mold<PackedVessel>::value);
static_assert(IsSpecializationOf<Capsule_0>::Mold<PackedVessel>::value);
static_assert(! IsSpecializationOf<Con_1>::Mold<PackedVessel>::value);
static_assert(! IsSpecializationOf<Capsule_1>::Mold<PackedVessel>::value);
```

## Implementation

We will use partial template specialization to dissect a type.

Suppose the compiler discovers that the type is a packed vessel and deduces the vessel as the given container. In that case, the compiler will select the partial specialization instead of the primary template.

```C++
template<template<typename...> class Container>
struct IsSpecializationOf
{
    template<typename Type>
    struct ProtoMold
    { static constexpr bool value = false; };

    // This partial specialization will be chosen
    // if `Type` is deduced as `Container<Elements...>`.
    template<typename...Elements>
    struct ProtoMold<Container<Elements...>>
    { static constexpr bool value = true; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAOwArKSuADJ4DJgAcj4ARpjEIJIAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMAGY3KDwe9MNDYQBPNKMViYAB02Oh2FuyAMCgUtw8bwiCVxwImxC8DgeCiEaOQeDEeAAXu8cgB5KjAkz%2BKxXW7C25w54IpEEVHoti3AAq0spQpF1NpBFuymIqCIAFlPOhgSLbvyLLc5o5kPiBBNMKo0sRbrFUJ5bgA3MReTDGqEAEVuVDESmhpv5PuDfOVwp2O3lCDwxLSAxZtDNTOT7M5AluAHc6Cn4viEJlGIaRdHbngqMbkhoFWiTDWK8SsOhaZh0LcmMSGxpSS1ycQkdgXowCApsZjKTXJ5HRWDxZCYVK0cw2BPh2DRwolZcjaq6Zrtag9bQDTC%2B0wB0OR4Jxziodgd0aTWaWharQwbXaHU6Xe7vF60J%2BgQNKIlCIb%2BGG4ERruIpihCYEoiuGITpcwDEJgm63k%2BIpeFkRi3CeHZARqWq6vqSJoRhWFjhOlLQVcobhoxPz/H8gK/HstzYKorDPF6XzApxbFnDBnG3D6PgsMiJKyJekTEMSglXPBEpLtKq5Yvej5XPu6puEwaQKF49AAPoaMxQIqfOCGShpKHaVSIFqiShnGWZXCWcCqmLkhMpaZilzEMA24PsCeERMAskMOZ3p%2BgZRkmZg5mUcFd6TmFDFWSCNlqX5mmoWlO4RQRpKmVwcWuYlHmpSFdGZYK2XicoTDIAA1u2ABqmBEvUnyiVcJVRS17VdT1diVQl7nJRZMIRAQpAVoIeyLfNByrctBz0Y1QlHPKPVjv1ByAuaeDIKZXZKG0ED3AyaashyjQ8kiZWzdgIAgERSIjR16Ddb1tC4h9/6esslmnedl0JAQN13ZgzIPZmDDPeeblJSlD4fV9MI/WNANAyAIOYGDWUQxdvXXWAYD0oy8Ppo93K8ueAjlQT2NuLjf3jfUBNEyTjVk1DlPU7dtMI7QGZPUzbhTejnmY59FE461v3/XYvMesTwYcKstCcIEvB%2BBwWikKgnBuNY1hmusmyAWYUI8KQBCaDrqxtSAgSSJiGgABxmGYACcAdcIEvs%2B1w/j%2BNIescJIvAsBIGgaKQRsm2bHC8AoIDJ87xs66QcCwDAiAgOsBBpF4C0UBAaBPHQCRRBinCqD7yQALTJJItzAMglpSJiZi8O2hAkHg6B6PwggiGI7BSDIgiKCo6h56QuhcKQ2bEIZnA8Lr%2BuGy7pucFylcV%2BqqBVi37ed93ve3P3Zi3BAHh1/QDrmA7yy8LnWirBASC1zSPXMg1dAHAJAMAKQZg%2BB0FBIpSgsRD6xAiK0ZEO9eDIOYMQZEXJYjaHhrnR2tdXgEC5AwWgaCV5YFiF4YABlaC0CztwXgWAWCGGAOIKheAMIODwK6Hqh9bTw0rtsR2816iHwlrELe2CPBYEPiBPACdmGkH4cQJ0SgfRgnYRLIwLtVhUAMCFTqeBMDZi5CudB89hCiHEHPSe8glBqEPmvfQ7CUCW0sPoPAsQs6QFWKgNIjQmFtwmGeH0phLDWDMGnNRxAx4CP8T0AhOQXAMHcJ4ToegwjkkWKMdexRsgCGmH4ApmQikMAWCMRI687ApIEP0KYmSCi1PqPUpokxBi5OqXoOYTT8ilNsJ0qpVR8mrAUDbLYEg94cANinQ%2B6dbhXw7l3HufcvaPwgLgEe797ZcC/k7fRqwECYCYFgRIEA3ZJChJiAOUIo4aEkGYFISdAjJADvoTgcdSAJwdpiZIXBkg%2BwDuHZInsQ53NSKnXg6dM7Z0OXnP%2Bxd/6l1PpXcglAwFv0bmwTgrQWCun8G3Jg%2BIDAES4AHTEXBvZD3wEQeJ4914OOnnY6QDjF7OJXroaBm9t7MJmXM6FR8OAn3LpXW4F8lmtxWaS9h99KXUo0E/F%2BQC37GntmYA5P984oqxQkDFNdUCv1GASdhFKuDJxoLQOBWcICIJXpg1BVjHXYNwfghwVjiGjjIRQw%2B1DaH0MYVY1hOjtgm3wDwxw/CmEmyEcgERVjxExxNlImRyI5Fhu/vE5Rjs1EaMwFothRhdGgERXwIxCgTFmIsYwKxzLbGzzZbIDly8TbcrcXoyJVgvFSL8Zc02QScghLCUBLt0TYkJAZYk/tdTeHOAgK4Ep2T0kjKWGUkoOQl3roqau/JyS50dIGFu/djRGldIqD02pnTj19PPcMUZNTxmTNngKg%2BK9FnLJvqa8lCrvZP22fS9Vn9v5HNICcs5ox%2B0x2%2Bb8yljyggB0jlCJ5KRJDryFbC2w8LtVIvgCisuZ8DV6uIDi7Y%2BKb4sAUK6S0roKWYgQhMWlOyx4T1kCyxt1iW0uJAFCDeW80joNffM99x80Xn0vhRqjNG6MMfVM/I1qqEhAahFq/RBcAEKeAURzTb9CbIDSGkUytGA6mVk6ZVQncYHWoSLa%2B1JsXWUMdg5t1BDPVGpIT6yh4bMA0LoWIINKiQ3FszaQCNKTo2CNUMI0EibBASJXqm1BGaFHZqsXm4shadGRTU4YpgxjTHmMsSo%2BtM8JBNoXk41tOgeMduMJ4mwvb4ABMHdaTgOwwkeKiZYGJMK4kJL7eMtpB60kZIGcu9Au6anpHKY0Y9hTGiTd6UN0917mmDNnSt%2BY3SH29NW2Nq9W2L07f2WsDYUyTsx0FQszgSzJPUbdDJhEEx/10pIEB/ZIHEXHNOecygMyYMgEDpiKEUJAihzQ0nEH/ggXCbTpwOFOdQPu0kIEW5Ed/BJx9pIYOXA/ZmFSDHKEb64cZwRb/GZg9Ycwvh2T12qibOpMkEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/is_specialization_of/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/is_specialization_of.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/is_specialization_of.test.hpp)
