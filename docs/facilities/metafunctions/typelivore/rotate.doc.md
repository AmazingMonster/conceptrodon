<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Rotate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-rotate">To Index</a></p>

## Description

`Typelivore::Rotate` accepts a list of elements.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function relocates elements of the given amount from the front to the end of the previously provided list and instantiates the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> Oper
-> Oper
   &lt;
       E<sub>I</sub>, E<sub>I+1</sub>, ..., E<sub>n</sub>,
       E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
Rotate
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Rotate
{
    template<auto>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will rotate the first three elements from `int, int*, int**, int**` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int, int*, int**>;

/**** Result ****/
using Result = Rotate<int, int*, int**, int**>
::Page<3>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Rotate` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

`Swivel` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Swivel {};

template<size_t...I>
struct Swivel<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        typename...BackTargets
    >
    static constexpr auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_targets,
        // Collect the rest.
        BackTargets...
    )
    -> Operation
    <
        typename BackTargets::type...,
        typename decltype(front_targets)::type...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...Elements>
struct Rotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAcGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWGkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYYF7rcCMQvJhYVYriC/gCtQcgZrbgBJVn0NiCJiNBk6jXa61ncnXSlCADueAAbvULbarsyjWaVXCuTzWH70VcJkqHLcna73SYAOxWWP3VV271s334rIAL0wAH0CAA6Qv6kWXMNeCNRt20DMEdAgEARLCqHNKACOyvF%2BP1hfzZMCIeB8ZBtxHCpZaY5V1Hsrcw%2Bno9T7L9bgDjCDPbRt0hTAUnwA8s9iGacqQ5/OFdy12wexYmMgANYAFVawEwBAUZ9lA%2Bnc0cyC3AgTJgqhpMQApCrceDoMi1ZTqOECftOOw7Lc2AgYY6AwgAbBo1K0ngqhdmSOEKqgAFeIICoIJgArEMAPiMO%2BtxUMQqAsFRNEsbIvZweeeF0kR/bgUQPZcYIeYvm%2BCinrx87IbceQNBxtw0hMPGXOeI63g%2Bz50VJG6ycsn4ALSbgeCTHgIn74ohC6XryNHaU%2BknvvWq49jJGmaauDm3FgkKrtQrHiZMr7vssbmXgZXkjn2aqDkmgTxVadwAEqoC0zIeky45Lpy9nroW2DGoxH79iCZYRulmUquqQ6yYu6ZwlmuaSpcLDrIIJY/oq5aStSGWoMoTCvtZ9UxfOjUcv6uVNSuBXXoWm7bruPaXMANIsqV3WaV4WRGLc6VMJhsLyv5tCrrZI4IbJmmRs6VY1nWIAsEw965o2wEtpg7avMu7WdQQfbfndo5ubNWVQTB%2BLrZtJrvhu/YQESkXPDmUGMSi%2BLFVtghleiQ6Jj2Rm3aORlJWNiXJQ1EPLoKImFrDmC4%2B%2BO0jntETAFSI00adUqDcNo1wkzLMKIj6IU3VVN2pqNq6pSaGsGyNHfClNqWuq6pghCUK83CYpbGkrPlZr9p3OZR7mqrXq0/lgaLb2Julr1EYW5ZDDJqbepCF4aTFJg6CpR8XgXdlIIcwdPt%2B5kAdBwoIeSnzbuNPiEQEAc/Jp5ngh7Nn6d7HFMuUnHCdh1cEdcyXod89Vc1Z5BOd5xnDf5yW9aC8ugRtyAR3oPiyc5IXXuUo%2BHyStbzvHsgOY7kobTI7W9YKEGM9lW4VcEPyUf%2B4HwcXWi5MWBwqy0Jw/i8H4HBaKQqCcLOljWLcCjrJsvNgjwpAEJox%2BrPeASSPmDQSQzBmAAJygK4P4IBSQuCxljNIU%2BHBJC8BYBIDQqRL7X1vhwXgCgQCpC/lfY%2BpA4CwBgIgEA6wCBpAROQSgaBWR0ASFEIMnBVBJCwsZLCkhbjAGQP%2BKQ%2BYzC8ADoQEgUE9D8EECIMQ7ApAyEEIoFQ6giGkF0FwUgjojxpE4DwE%2BZ8L7fxvpwPcCIaGSlQFQW47DOHcN4fw24gizC3AgB4Rh9AwKYi4MsXghCtCrAgEgBhaQmFkAoBAYJoSQDACkGYPgdBmTEDwRAWIRjYgRFaMiXRvB0nMGIMiPcsRtCYAcNk0gDD4Z7gYLQLJqisCxC8MANwYhaB4O4LwLAr0jDiDqXgGkDhoxtOvsBEpCJtgfzTvUIxSJYhHnyR4LARjFR4FQe00gbpiCxBjo8LpwAkRGG/qsKgBhgAKAAGrvEdOZS%2BH8pHCFEOIeRdylFqCMeo/QhhjDWGsPoPAsQ8GQFWKgI2OQ2nGSJKdUwD9LBmCwRs4gGMAUQFWHYEpjQXAMHcJ4ToegwgRGGFUUYGjijZAENMPwxLMikoYAsEYiQNGooGQIfoUxsUFAZfUNFfRJiDHxYsIltgeXkr0HMNotLCX0pRS/LYEh9EcHPqQTBvBsHWI4VwnhfCBEAOcRAXAYjPHvx8Z/Q5qxqLHVGMi0gf9JCBHzKAwI8CNCSDMJIHCGh/BYVAfoTgyDSCoMCFwfMWEuBYSSKAmBWF/CSEgfarCiqjHYNwfg41RCAnkMCZQsxtDwmRI8SwtgnBWgsBdLGYyTAtwGAOlwUB%2BZA3DPwEQBFdYNF3JkY86QzylCvNUboOJWimA6PaXKhVSrjEcFMdQhEtxLGqtsTw7cVaa11pcW4kJHiYRgjMEavxxCM25oSHQiJbE12jAXTEiBqQaAXQSMk1JqjcmZLKQ%2B/JhTimlLWRUxiVSalGPqY05ptBWllM6Z8np198D9McG6IZIjVCjOZGUyZiDr4zLmciBZ2xr7LNWR/DZWylA7NA5zQ5fATnnMudcspraHlyI7bIF5Kjr69o%2BQcqFVhLC/P%2BfAIFILAKcHBbWSF3yYVwoSE2j43GehcucBAVwwqNF4oqHSvQJLGjyfSFSxo4qlgct6MyoVbKKVSaZU0Hl2mBWivaIZkVZm%2BXKe8WsDYMqHOIJHQmzgs71UVs%2BY4pdgCXF6sbRugN26TWkDNVgRIlrEG%2Bv9TWp1sZ/CgLgYEZ1rro3xtUYm2wyad1pvgBmqh5jD37uIPm7YRa7EsAUC6f8Lpq35iXBMERDbxHNoUfc2REg6OKK7YxnQIBgj9sHXo718rDFZZMVmixVjVBVZq3VhrTXJSuOPaE4LgRQuppIUEtbHiSt7dGLVv2OZ6ugJzMtnMc2O0JJvZQO919n21I/k919aKymfsEN%2B2p4HMANKaS0tpH8QPdMwx0vpXLoNGJGcgMZiHBBTNUahzJGGlkIpw7wPD2yWREYOdt45I1yOYCuTyKjsg220Y6wxt5g2WNfOhTYGZSKeONDaTsFGbHrCwuVfCxFknGXotk5i9TimCU6Y0yUHI6nVM5HM/S4zjQWVWfyEZgX3L5h2YlTZgY6nLNy9lY51%2BBvXMTawR567txqu1duGdxrvoJgBdawakLviwsRYtXK2LIAwH5kCIEfwUDo3oL97GUNmWzc4JywQsL1r/B2tgbGdBSRJAQK4MAswcbEGBFN8qzgrvU1yuEeH3Pke8urA2VkZwkggA)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/rotate/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/rotate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/rotate.test.hpp)
