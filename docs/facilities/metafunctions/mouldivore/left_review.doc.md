<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::LeftReview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-left-review">To Index</a></p>

## Description

`Mouldivore::LeftReview` accepts a predicate and returns a function. When invoked, the function returns true if the predicate evaluates to true for every relative-order-preserving pair of its arguments and returns false if otherwise.

<pre><code>   Pred
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>i</sub>, Arg<sub>i+1</sub>, ..., Arg<sub>n-1</sub>, Arg<sub>n</sub>
->   Pred&lt;Arg<sub>0</sub>, Arg<sub>1</sub>&gt;::value && Pred&lt;Arg<sub>0</sub>, Arg<sub>2</sub>&gt;::value && ... && Pred&lt;Arg<sub>0</sub>, Arg<sub>i</sub>&gt;::value && Pred&lt;Arg<sub>0</sub>, Arg<sub>i+1</sub>&gt;::value && ... && Pred&lt;Arg<sub>0</sub>, Arg<sub>n-1</sub>&gt;::value && Pred&lt;Arg<sub>0</sub>, Arg<sub>n</sub>&gt;::value
  && Pred&lt;Arg<sub>1</sub>, Arg<sub>2</sub>&gt;::value && ... && Pred&lt;Arg<sub>1</sub>, Arg<sub>i</sub>&gt;::value && Pred&lt;Arg<sub>1</sub>, Arg<sub>i+1</sub>&gt;::value && ... && Pred&lt;Arg<sub>1</sub>, Arg<sub>n-1</sub>&gt;::value && Pred&lt;Arg<sub>1</sub>, Arg<sub>n</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>i</sub>, Arg<sub>i+1</sub>&gt;::value && ... && Pred&lt;Arg<sub>i</sub>, Arg<sub>n-1</sub>&gt;::value && Pred&lt;Arg<sub>i</sub>, Arg<sub>n</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>n</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
LeftReview
 :: template<typename...> class...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class>
struct LeftReview
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Example

- We will check if every relative-order-preserving pair of `Vay<0>, Vay<1>, Vay<2>, Vay<2>` satisfies `IsNoGreater`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** IsNoGreater ****/
template<typename L, typename R>
struct IsNoGreater
{
    static constexpr bool value
    { L::value <= R::value };

};

/**** Test ****/
static_assert
(
    LeftReview<IsNoGreater>
    ::Mold<Vay<0>, Vay<1>, Vay<2>, Vay<2>>
    ::value
);
```

- Note that the order matters when the predicate is not commutative.

```C++
/**** Test ****/
// Reverse Vay<0> and Vay<1>
static_assert
(
    ! LeftReview<IsNoGreater>
    ::Mold<Vay<1>, Vay<0>, Vay<2>, Vay<2>>
    ::value
);
```

## Implementation

For every element in the list, we will check if it satisfies the predicate if paired with every element behind it.
We will implement this process in two steps.

- First, when given an index, we query the predicate with the pairs consisting of the element at the index and every element behind it.

We will expand the concept `Prefix<***>` alongside the arguments to pick out the element at the index.

```C++
template<typename, auto>
concept Prefix = true;
```

`LeftInspect` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct LeftInspect {};

template<size_t...I>
struct LeftInspect<std::index_sequence<I...>> 
{
    template
    <
        template<typename...> class Predicate,
        typename Inspector,
        typename...RestElements
    >
    static consteval auto idyl
    (
        Prefix<I> auto...,
        Inspector,
        RestElements...
    )
    -> std::bool_constant
    <(...&&
        Predicate
        <
            typename Inspector::type,
            typename RestElements::type
        >
        ::value
    )>;
};
```

- Second, we perform the first step with every index and combine the results.

```C++
// Immediately invoked lambda.
[]<size_t...I>(std::index_sequence<I...>)
{
    return
    (...&&(
        decltype
        (
            LeftInspect<std::make_index_sequence<I>>
            ::template idyl<Predicate>(std::type_identity<Elements>{}...)
        )::value
    ));
}(std::make_index_sequence<sizeof...(Elements) - 1>{})
```

Here is the entire implementation:

```C++
template<template<typename...> class Predicate>
struct LeftReview
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        LeftInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate>(std::type_identity<Elements>{}...)
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Elements) - 1>{})
        }; 
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBJcZqQADqgKhE4MHt6%2BASlpGQKh4VEssfFcibaY9o4CQgRMxATZPn6BdpgOmQ1NBMWRMXEJSQqNza25HeP9YYNlw5VmAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimMmujMh4mAq3R%2BdXN6f/xx%2BlwuwLM/jCyG8WFuJn8bi8jlohAAnrDsCDzOCGJCvNDYW5kGN0FgqGiMb8jrdlMRMDRVF9DkCCJgWMkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYf57rcCMQvJhYVYriC/gCtQcgZrbgBJVn0NiCJh1BgMnUa7U2s7k66U4K0gj6hgKZ4OS12q7Mo1mlVwrk81gB9FXMZKz1Oqgut0eyUmADsVkT91V9t9bP9%2BPSAC9MAB9AgAOlL%2BpFlwjXijztd7q6BBzBHQIBAYSwqgLSgAjsrxfj9aXi2T/NgYerkyDbtOFSysxyrjPZW4p0uZ5n2QG3EHGCGh2jbpCmApPtTMPhRMzSKu1wrubu2Aa4w2SNfF7e78G2EOAEofAjYMajAEAoN6ymGlxLmMZp4Mgh4CGMmAAG5iAKQq3Hg6DIrQYEQGBS5nnSA4HoKRBDm%2BkEfnW8avvhM5/mMgEssBCj7u%2B07LGBAC0B5Eq20SoJ4BZitBghgfiED7mYABs5iyexa5nhe2YKUu%2BJ0beO68pgT71g4JCtjuFEfmuWkhrcDEAUBggKIZ94aeBDmtih3gqgpnGjumE5pv4arAhSdzRgQf5Ie8ADuXpMnOm6ctF2aBve2n7qOh4GCeUrnrB8UQVWNYxiF4UYpOCkbvF26JXupZMSaIEVlBirVpK1KoEQACynjoOJxWUbe0GOHBInMqoyTELcAmeLcLnKg5SZ%2BSZakAKxWAtPluHmhYlmWaIQHxbYMB2XaYL2rxboOpZopxqkfrNDkmTSBAbAwt0fpJ50yXJeFXfNa5YJCO7Pd9n09d9INBdRDZNi2IAsEwADWhbtpgnY9n2WzEZ5nlfSDt6GXFzIYVhOFwkpWUcqOO3NnZzwFphwEovi1UsWSk6pkOl3A9jS7LM5YjTVjJnLB5c0g0m9wU1DMPwzT%2B1I4dx39nC62oFQQ4QIzNnLLcXG3FwzMpvc7MmaLqrjsDxu%2BfaS6lWT5VfpgQ7q7VmPA146RGLc7W0Ogsrys1bUdQz1kgcl6IW95Xn%2BQ6toArqlIAGJ4MQYy3NgqisGyOnfNa0f/ECGJghCUI6Zy95FsQTCEKBzvZwctwAGpMMikUgtbW6kagBoVrlkoN6iE4WLcfWwfBbpDSNaFEJNvPF8m5apib5t%2BTXewGgoESoAA4jS/qjVnPp41uZmPsE/JHzpP5dw1nr6mvm/b8yxBFcL05DwNCFj6N420FPrldQPwQ81csuWE8ofyAOVDCeeYdI6L3tHqAAKv%2BZu4ZGj9QLMeJQzQQRAyXEFAqmAwoDlvlvTAO86ozlbJ7TqcJe74g0GifktC4S61HIwxu%2BIzAMPruwuEnCMYQSXOAtylwhZwJzjHZetwhBdAEN7VO6d6DIKjuIk4ecAq10QcnPe1wdgWWQnEJQ3DURwnoSlQw3smFuBYTlVBsF0EnjiI2K4OCZxgDALcPByFCpwhvuvEhZDnaCJAFQ/EljrFsOMW4Ux2AIkcK4ZYvhocBEUJAFNYRQsOCrFoJwBavA/AcC0KQVAnAVyWGsIPdYmxi5gh4KQAgmhMmrFhiABakhiwaAABxmDMAATh6VwBanSOlcETImaQ2SOCSF4CwCQGgNCkHyYU4pHBeC2XmfUgpmTSBwFgDARAIB1gEGSAicglA0CsjoHECIIZOCqA6dJLi0lJC3GAMgOCUhixmF4JlIgxBMJ6H4IIEQYh2BSBkIIRQKh1CbNILoLgpAwrl2SJwHgWScl5IaUUzgAB5BExzJTK1uHch5TyXlvJ1m0swtwIAeAufQUamIuDLF4BsrQqwIBIHOckS5ZAKAQC5TykAwApBJBoLQB%2BtkIDRExdEMITRkQot4LK5gxBkTYuiNoBsirSDnJqtihgtAFUwqwNELwwA3BiFoLZbgvAsAwyMOIY1icGx4CQh8TFSMugIm2LUsIzIJmFKRNEcuqqPBYExYqPAMybWkDdcQASShHj2uAEiIwDTVhUAMMABQddwrYp5NqwFwhRDiDBUWyFahMVwv0IYYw1hrD6DwNEWykBVioGSOaa1XEiQgNMGUywZgllxr%2BVgFtEBVidG6M4CArhJh%2BHhSEOYpRyh6FSOkc0c7V0FHNAMZdixqi1B6DMTd8LJ3ml6M0XdQwKi2GPZ4NoehoKXqXdeiQE7KlbDffodFCzMXLKJfcx5zzXnvMpdS3AhASAwhqcyup6bVgIFIVgeI47SDNMkP4YsPT/BjI0JIMwkhpJzIWtJHp37JnTICFwYs0kuDSQ6T04Z0lWkDOw9JX9MLlmrJAOs9N2y9kcoOXik5fKBX0uuWwTgTQWBIUTFxJgqVa06x6cWajhSfkkH%2BfCotwLS3SHLUoStMLdBJERUwZFNq0UcFyRxpZOLhMEqoABklzyjzuy4CptT1LaXcvpdB/wKwWV8cE2JuIpz%2BWoDpcMNzwr%2BnzLFRKyg0qYXKvldq1Lqr1WaocNq3VwF9WGsxSas1FraBWu1Xa2tjrCn4BpN0N11r1OqC9cybVfqaiYqDSG5EYbtiFMjdG2pcaE2YCTVVsIoBNkZqzTmvNBaY06ZLaC/TsgK3QsKSZmtaa%2B1WEsI25t8A20dsyF2ntcodvWEHbwVAw7aZjonTUF107Z33tyAu/aV6Fg3rXYULIr3535HXZkT7K7T2PanQwC9LR/uPvB%2BemYIP91PuhzkAHyPEcVHfRsT9TLyM2cWddzgzmgOKfc559p4H8C/P80yoLU2ENIeGKhiZUzSAzP8CpvDiYFo9NGf4fDhHJDwoJ1ilZtgeNwam/x%2BAgnDn4vC6F4gEntjSdJSwBQSE4JIQ88WTcYxvlU80y2bTshdPLfBfIQz62dB5DMxZ1FeOMWcfs0chEtxCWqDVxrrXOu9eShpZF3zcR/P%2BFg6yrZIXA88oV1H%2BlqTkDJGSAWbXPSCx%2B4LJ7/TdBEtSplXK1V6X89qo1VqmNeXBAFaNTVzAprzWWutbUyrDq%2Bu2udfV91MLPXIG9W1wQHWYVdflb1iNfzBu8GG2kUbLJxtpql5mpg2bc0EPzYwQtpulsSBWxCq3Va8gGG2/WvbQb7tFOOwhTgOw%2BIXYHUOuII73WtoPU9vwM79onqCB9l9X2t1A4EO/n7O6X%2BoOT%2BEOUO7%2BZ6R6fQGOj6d6qOMBUBQBiwWOVSX6Ey%2BOf6ROmetw6umuk0vu/oycashuDKMGdObKDOTAyGlAVmrOMyvSxY/g/gC0gyQucyjBiY9GtmhOYuayku5BaGIAkgC0WGIyiYcyHSkg/SXAXSMk5G/gTudmYu4egs5GXyXBouZBjSsaBimQghQAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/left_review/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/mouldivore/left_review.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/left_review.test.hpp)
