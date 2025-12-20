<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalConjureSet`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-conjure-set">To Index</a></p>

## Description

`Typelivore::TypicalConjureSet` accepts a list of elements and returns a set that:

- contains every element in the list;
- doesn't contain repetitive elements;
- preserves the relative order of the list.

<pre><code>   Args...
-> Capsule&lt;(make set)&lt;Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
TypicalConjureSet
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalConjureSet
{
    using type = RESULT;
};
```

## Examples

We will turn `int, int*, int**, int**` into a set.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = TypicalConjureSet<int, int*, int**, int**>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will traverse the element list and only collect each element's first appearance. We do this by only collecting an element into a capsule if it has not already appeared. Then, we will concatenate all the capsules.

We will expand the constraint `Prefix<***>` alongside the arguments to skip the examined items.

```C++
template<typename, auto>
concept Prefix = true;
```

We check if the element we are inspecting has already appeared using the following static member function.

```C++
template<typename Inspecting>
static consteval auto idyl
(
    Prefix<I> auto...front_args,
    Inspecting,
    ...
)
-> std::conditional_t
<
    (...||std::is_same_v<Inspecting, decltype(front_args)>),
    Capsule<>,
    Capsule<typename Inspecting::type>
>;
```

In `std::conditional_t,` we check if `Inspecting` has appeared in `decltype(front_args)...`.
If so, an empty `Capsule` is returned.
Otherwise, `idyl` returns a `Capsule` containing `Inspecting`.

Here is the entire implementation.

Note that we wrap the elements inside `std::type_identity`. This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...Elements>
struct TypicalConjureSet
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    {
        template<typename Inspecting>
        static consteval auto idyl
        (
            Prefix<I> auto...front_args,
            Inspecting,
            ...
        )
        -> std::conditional_t
        <
            (...||std::is_same_v<Inspecting, decltype(front_args)>),
            Capsule<>,
            Capsule<typename Inspecting::type>
        >;
    };

    template<typename>
    struct Hidden {};

    template<size_t...I>
    struct Hidden<std::index_sequence<I...>>
    {
        using type = Cotanivore::TypicalPaste
        <
            decltype
            (
                Detail<std::make_index_sequence<I>>
                ::idyl(std::type_identity<Elements>{}...)
            )...
        >::type;
    };

    using type = Hidden<std::make_index_sequence<sizeof...(Elements)>>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/typical_conjure_set/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/typical_conjure_set.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_conjure_set.test.hpp)
