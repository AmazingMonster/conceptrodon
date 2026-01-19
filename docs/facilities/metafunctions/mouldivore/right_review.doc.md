<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::RightReview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-right-review">To Index</a></p>

## Description

`Mouldivore::RightReview` accepts a predicate and returns a function.

When invoked, the function returns true if the predicate evaluates to true for every relative-order-reversing pair of its arguments and returns false if otherwise.

<pre><code>   Pred
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>i</sub>, Arg<sub>i+1</sub>, ..., Arg<sub>n-1</sub>, Arg<sub>n</sub>
->   Pred&lt;Arg<sub>1</sub>, Arg<sub>0</sub>&gt;::value && Pred&lt;Arg<sub>2</sub>, Arg<sub>0</sub>&gt;::value && ... && Pred&lt;Arg<sub>i</sub>, Arg<sub>0</sub>&gt;::value && Pred&lt;Arg<sub>i+1</sub>, Arg<sub>0</sub>&gt;::value && ... && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>0</sub>&gt;::value && Pred&lt;Arg<sub>n</sub>, Arg<sub>0</sub>&gt;::value
  && Pred&lt;Arg<sub>2</sub>, Arg<sub>1</sub>&gt;::value && ... && Pred&lt;Arg<sub>i</sub>, Arg<sub>1</sub>&gt;::value && Pred&lt;Arg<sub>i+1</sub>, Arg<sub>1</sub>&gt;::value && ... && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>1</sub>&gt;::value && Pred&lt;Arg<sub>n</sub>, Arg<sub>1</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>i+1</sub>, Arg<sub>i</sub>&gt;::value && ... && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>i</sub>&gt;::value && Pred&lt;Arg<sub>n</sub>, Arg<sub>i</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>n</sub>, Arg<sub>n-1</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
RightReview
 :: template<typename...> class...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class>
struct RightReview
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

- We will check if every relative-order-reversing pair of `Vay<0>, Vay<1>, Vay<2>, Vay<2>` satisfies `IsNoLess`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** IsNoeLess ****/
template<typename L, typename R>
struct IsNoLess
{
    static constexpr bool value
    { L::value >= R::value };

};

/**** Test ****/
static_assert
(
    RightReview<IsNoLess>
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
    ! RightReview<IsNoLess>
    ::Mold<Vay<1>, Vay<0>, Vay<2>, Vay<2>>
    ::value
);
```

## Implementation

For every element in the list, we will check if it satisfies the predicate if paired with every element behind it.
We will implement this process in two steps.

- First, when given an index, we query the predicate with the pairs consisting of the element at the index and every element behind it.

We will expand the constraint `Prefix<***>` alongside the arguments to pick out the element at the index.

```C++
template<typename, auto>
concept Prefix = true;
```

`RightInspect` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct RightInspect {};

template<size_t...I>
struct RightInspect<std::index_sequence<I...>> 
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
            typename RestElements::type,
            typename Inspector::type
        >
        ::value
    )>;
};
```

- Second, we perform the first step with every index and combine the results.

Note that we wrap the elements inside `Tyy`.

```C++
template<typename Element>
struct Tyy
{
    using type = Element;
};
```

This ensures we can create objects to invoke ordinary functions.

```C++
// Immediately invoked lambda.
[]<size_t...I>(std::index_sequence<I...>)
{
    return
    (...&&(
        decltype
        (
            RightInspect<std::make_index_sequence<I>>
            ::template idyl<Predicate>(Tyy<Elements>{}...)
        )::value
    ));
}(std::make_index_sequence<sizeof...(Elements) - 1>{})
```

Here is the entire implementation:

```C++
template<template<typename...> class Predicate>
struct RightReview
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {
            // Immediately invoked lambda.
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        RightInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate>(Tyy<Elements>{}...)
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Elements) - 1>{})
        }; 
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/right_review/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/right_review.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/right_review.test.hpp)
