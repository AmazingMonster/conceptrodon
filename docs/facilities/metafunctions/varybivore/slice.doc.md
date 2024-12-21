<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Slice`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-slice">To Index</a></p>

## Description

`Varybivore::Slice` accepts a list of variables.

- Suppose its first layer is instantiated with an index.
In that case, it returns a function.
When invoked by an operation, the function collects all variables with indices greater or equal to the given index from the list and instantiates the operation with the collection.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> Oper
-> Oper&lt;V<sub>I</sub>, ..., V<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function collects all the variables of indices within the interval from the list and instantiates the operation with the collection.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>J-1</sub>, ..., V<sub>n</sub>
-> I, J
-> Oper
-> Oper&lt;V<sub>I</sub>, ..., V<sub>J-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Slice
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Slice
{
    template<auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

```C++
template<auto...>
alias Slice
{
    template<auto, auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will collect all variables from `0, 1, 2 ,2` starting from index two.
Then, we instantiate `Operation` with the resulting list.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<2, 2>;

using Result = Slice<0, 1, 2, 2>
::Page<2>
::Rail<Operation>;

static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will collect variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
using SupposedResult_1 = Operation<1, 2>;

using Result_1 = Slice<0, 1, 2, 2>
::Page<1, 3>
::Rail<Operation>;

static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Slice` using concept expansion.

We will transform variables into types so that we can avoid defining the bodies of helper functions `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

- In the case where the second layer of `Slice` only accepts an amount, we want to remove the variables of the given amount from the front of the list.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to enumerate the
        // unwanted arguments.
        Prefix<I>...Unwanted,
        typename...Targets
    >
    static consteval auto idyl()
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<Targets::value...>;
};
```

`Prefix<I>...Unwanted` tells compilers that this function template is only allowed when `Unwanted` satisfies `Prefix<Unwanted, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `Slice` accepts two indices, we want to collect the variables between them.

```C++
template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to reach the start of `Targets`.
        Prefix<I>...,
        // We use `Prefix<J>...` to enumerate the variables
        // we want to collect.
        Prefix<J>...Targets,
        typename...
    >
    static consteval auto idyl()
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<Targets::value...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Slice
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Shear<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {   
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgBykrgAyeAyYAHI%2BAEaYxBIaZqQADqgKhE4MHt6%2BASlpGQKh4VEssfFcibaY9o4CQgRMxATZPn5cgXaYDpkNTQTFkTFxCUkKjc2tuR22EwNhQ2UjlWYAlLaoXsTI7BzmAMxhyN5YANQm%2B25ejrSEAJ4X2CYaAIIHRyeY55fI4%2BhYVEezzeZkODGOXjOFzcBDuyUwAH0CMQmIQFEDXsCAPQAKjxONOymImBoqlO%2BJxWOBBEwLGSBhp0Nh8OYbFIpyY11QGJeaHBmGSBEJxNJ3wAIqdkV5MBcrJjXrj8acALICVBEBh3cn4qmvGl0hkyy6coinABqTTwTGi9B542IXgcKrVGoemIA7BZTuMmI5kKc%2BeNMKpksQOVzTgA3MTS86ei3EK02mXusWyuNp/Zyt4KimnIQITBNbV43UvfX031GmFwxisI1PV72x1CgtFsMmT2dzPZ6m0yuMy7pABeiIIADpJwBJO1Sp1tprQv4gEBhLCqBFKACO0v50Knk/HQP2jbeXdep0vkv7huBV%2B%2Bbjv96vFdvxq5h8eAYMCgUpwA8vCKJ1AwpBPs%2BpxYlipwAOpfF4SjnAAbBoRIkngqj7o8n4oZKqCnIwPhxFWkqFuBz5QacXgMAA7oYNLoByxDAERggKEeF4QcK6GYZcM4noeci0fRmDoGBnEQcydZsIeAAqTTAJgBDohJ3ynvePp%2BgGAhBtGtDhqaeDoHctAQKs5GURE6pfAQCC%2BshGiAcRIEmLheB/mEkaoAA1qJpzRFqenSipLz3pRwbIkwDh%2BVQxCoCwpE2TeJHJE09Y0sQ7EWdBskIO5pz5bEogIV8NGlXQ%2Bmpcg3kEZGcRaoQtLZacqBUA5CZJvQ7GTq5GgFYI%2BG9aqDDqgIDwoRxoVXgAtF%2BTnAZk0LycxSkKCuQWYJ%2BJ6ysC3Y7fKLyKnipxTuC7lfBSZavlWTK1qymDslJ92zg6Tqncg51xlYqb7Tm5bJYObgjmOh5TuywNIoeABSL0tidZ1KEuBDoCua7BpumA7owOz7lt2Dg8jqMMOuGNY3ulxQ3jPKdtm97XYyqnQuRdMA9WJqoHj35ML%2BAFAb6mTiVNEGUXBVGIb1aGklhAk9bhprElFCCJd6cwtW1vXLYpym9ZNXHcVLfHYZOgt6yL8HiyhksYdCMMy0ecv4YRbDATZhZRpa1pdczV6UWVpx0YIeHabQtS61xVu8W4tvYHJCmrSbXFPfWn6M9tqmaXg/qBjSekGfhRkmWZzVWTSpH2b1838wIvUFR5DBeb5jEBe73iYCFYXQRFKLRYxsXxcr9NfKlKJsBlWWqZRuX5YV3Scohfs0RVpxVTVmB1cQDX6s1rXtR7ybdfbfVhKaQ0umNOvkbNJ6885i2XJrq3rTGm09dtWa7T978HUdBJCLcOwlkpH2A0N13xEEPB1T2bdYbzn/jKD0tMXys2hOzKm6c5xCiJKNZQTBFJfT2l/P6LMQGAwhkKF4LBNiCB5BpDBwpsG4OrBQqhBAaFXhpt7S8g8mTILARzV%2B2Aua/kPC8YAxJaSMG1mnIWz4EJhGAKcAASqifSFwJRYGOFJThpwIDaPvAuYgSMUYgBYEwXyCI0Ybm3LuHGlxmHUVYW/dSesrwrkHgVYytBoSiPEWwNih52TDVGpqaEkD95GyPCeIuql7zmUIfeAhvZVLcKHHgUcSJ8xzHBmkscpxsDEzYZeYkO48DEj/BAPozQHxqLycTcy6DXqYLikQHBiloSVIIOyfJ6BClfXYTEpBJDqwpLcKggRQiD4%2BMwBItivT7xyKMEolR4pTgaNoFogZl5dGbOfO9c6RiVymPMZY0mNjqwdMeATYxRzEQnOsdjas3TpoXKcXo1xIB3EFy8XYsR0y/HKQCc6EarpQl7y9nbR40SZGxN%2Bgkz%2BSSZEjLGeOKZMypHOMvAshRrSvg1KwS0xh3jflooPseXs8Ldq5gpNS6lZYf6nFkm3ZSgC6U0rZaWSlIIwQQihD8AQOxBTomkcAgcbMPwCOBM2J0lcXKEOxHmAAYqU8YeTVCsHpBdHUnKsX5i8MkVISh0CKLbl4dZKyZV3zcEkU4ZgyXavSIs41ChTVChqX/TO1YNDsi4Oya1trpErhxdCf1p4VzKLoNCC11c34IozsgBE3MlDNAgMuEACh6wJqFW4IQeqDWiSdS69kBb1mPDiQi%2BlQhugCEYtgNVBpNUcoOjqnN%2Bq0j5pNeshEXBzV81lW4H1Nq7VNodQo4tBAu0rPdbYtwXrTgDr9TyQNhLLgDv2IukA4bvluCjQwIdf042ZqTQQFNhM00Zu5u03NbajUdvHQOsdXbS2yg4OsWgnAACsvA/AcC0KQVAnBHyWGsN6TY2xcWgh4KQAgmgX3rG8iAd9/hxxIX2JIMw7pJCSEQ/sDQ76ACcgQ30cEkLwFgCQvXft/f%2BjgvA1peugz%2Bl9pA4CwBgIgEAmwCDJGuOQSgaA6R0DiBEesnBVD%2BCQtNJCkhTjAGQP6KQ44zC8FEoQEgRk9D8EECIMQ7ApAyEEIoFQ6hGOkF0D6miKJkicB4K%2Bj9X6YN/s4P%2Ba43GhQ7zExJqTMm5NzskIpnRHgBP0A7BB1YvAGNaHWBAJA/HkiCbIBQCAsX4sgGAFIJINB1lxDWhAaIDnohhCaHcazvACvMA3v%2BaI2hugMcg/x/5/4GC0GKyZrA0QvDAFGSHNa3BeBYFMUYcQrXSk1bwHVHrv7gzdGuLsSDx8agOduNEFEG8PBYAc8iPAZHeukHXtENtYpaSGGALcIwMH1hUAMMABQZo8CYBok5b9kHNPCFEOIPTL3DNqAc2Z/Qx2UDWGsPoPA0Q1qQHWKgQUmQevTT%2BGo0wQHLBmCo%2BvRMWAwdmWqLUTILhiZTHaEEYmgxSjlD0AawoWRPBtDJwUECxPhgVCx6N%2Bocx8d6C6D0Fn/R6dLEZz6SYVPpizG5wsEnyx1gKFAzsCQtmOCftIJR3g1HTgeck9J2T8m/NmB0bgVTIX9hcDC1B876xCxMCwPETH8HJD7HHHh/YGGNBockChXDSE8P6E4CR0gZGDfIa4EhfwBGA/vskFwfD%2BwkIK4c9R2jIB6PneY2x6LHGXM8cS8l4Lwm2CcCaCwSM7pppMC5osrgeHxxcHHJN/ARA0cadkNp970hPtKG%2ByZ3QSQLNMCs712X8vFeOY4M5rj1w1ZMXz4X4vxxjtzvL5XvqEBAtxeC%2BcUEaxwuJ5T5nuIvGkvxWXyMPPBfprT6MGXyofA6Bj0oHlkzZWisldIPfirVWauP/q5IxrzWHNtY6112gPWkG/Wx2Q2v6%2BAxIPQ42DmU2yAM2j%2B82RGv6S2K2dwa2uwv6m222kGe2B2R2g28iiel2uCN2d2D2LIj%2BL2jeumzesgX2xmv6Hef2Z2COVglgwOoO8AEOUOOknAsOyM8OgOSOKOcQaObcnBTOnOfgEArgbOPqIQouDONO6QIEsh%2BQyhmQPOpOPqHOIEHSqhOhvQcwmhywwuAuOQBO/O8wJQihhuGwWw0uthRG/eMenA4%2Bx%2BU%2BBgpec%2BVeOuNeJAq%2BBuRuEWsGpAZuFulAsu3uvu5eTu7o%2BG7o7oqGZgLuYe0eJmsetg8exujGUWyeSAnGrmu%2B2%2BxA2euweeXmLACgkY/okYZe44ho4wymfhdePqlBb21B%2Bm8gre9BOgIA%2BwpAXePeNmnucu9m6RTmaebmbU5R0mlR1RUYdRDRQoi%2B%2B%2B8WAR%2BwQRm%2BMWqxwWRROxIw1R%2BqCItReGCISxCaxALAUml%2BWWmUN%2B%2BWhWG8j%2Bz%2BdwlW1WDg7%2B8UDWTWLWYBmA7WnWYgABj%2BwBg26BfWI2kBYhJmMBcBO2CBi2IOKBaBG2iYWBvAOBSgh2A2J2BBORfAV2JB92j2FBDe7REgNBBm3RP2fRTBxgghNgS2GOXBIEPWWIy4LB1gyOSuqORkYh4OEhIEuO7gguBO8h1hvOShFOqh5OdOChkp2hNQzODAehop7OSpkhHSxhfOrOap2hRh8pWhEuUuumfeYxVGrhMxpwcxNRixVYKqEAuuteARhuG%2BORpuRY4RmORGURIAZg5e%2Bw%2Bw7676TulQGggZ7ogeaRFpNGmRCe7ppA1uleke767oZgwZYe7ukgVQRG%2Bw5pSunAbpkWsuSm0ZBZsZwRqw6w686QzgkgQAA)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/slice.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/slice.test.hpp)
