<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::RightReview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-right-review">To Index</a></p>

## Description

`Pagelivore::RightReview` accepts a predicate and returns a function.

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
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct RightReview
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Example

- We will check if every relative-order-reversing pair of `0, 1, 2, 2` satisfies `IsNoLess`.

```C++
/**** IsNoLess ****/
template<auto L, auto R>
struct IsNoLess
{
    static constexpr bool value
    { L >= R };
};

/**** Test ****/
static_assert(RightReview<IsNoLess>::Page<0, 1, 2, 2>::value);
```

- Note that the order matters when the predicate is not commutative.

```C++
// Reverse 0 and 1
static_assert(! RightReview<IsNoLess>::Page<1, 0, 2, 2>::value);
```

## Implementation

For every variable in the list, we will check if it satisfies the predicate if paired with every variable behind it.
We will implement this process in two steps.

- First, when given an index, we query the predicate with the pairs consisting of the variable at the index and every variable behind it.

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
        template<auto...> class Predicate,
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
            RestElements::value,
            Inspector::value
        >
        ::value
    )>;
};
```

- Second, we perform the first step with every index and combine the results.

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

```C++
[]<size_t...I>(std::index_sequence<I...>)
{
    return
    (...&&(
        decltype
        (
            RightInspect<std::make_index_sequence<I>>
            ::template idyl<Predicate>(Vay<Variables>{}...)
        )::value
    ));
}(std::make_index_sequence<sizeof...(Variables) - 1>{})
```

Here is the entire implementation:

```C++
template<template<auto...> class Predicate>
struct RightReview
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        RightInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate>(Vay<Variables>{}...)
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Variables) - 1>{})
        }; 
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/right_review/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/right_review.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/right_review.test.hpp)
