<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::InsertValues`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-insert-values">To Index</a></p>

## Description

`Omennivore::InsertValues` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts a list of variables and returns a function.

When invoked, the function inserts the variables to its argument list according to the `std::index_sequence`s.
The result will be stored inside `Shuttle`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>k</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Shuttle
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, V<sub>0</sub>, Arg<sub>I<sub>0</sub></sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, V<sub>1</sub>, Arg<sub>I<sub>1</sub></sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, V<sub>n</sub>, Arg<sub>I<sub>n</sub></sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
InsertValues
 :: typename...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct InsertValues
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will insert `-1, -3, -5` to indices `1, 2, 3` of `0, 2, 4`.
To do so, we will calculate the distance from one index to its immediate next.
We will keep the first index, `1`, since it represents how many variables we must pass to reach the first target position.

<pre><code>   1, 2, 3
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;2-1&gt;,
   std::make_index_sequence&lt;3-2&gt;</code></pre>

We will pass these sequences to `InsertValues`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = InsertValues
<
    std::make_index_sequence<1>,
    std::make_index_sequence<2-1>,
    std::make_index_sequence<3-2>
>
::Page<-1, -3, -5>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<0, 2, 4>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<NewVariables..., Variables...>;
};
```

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

The index pack within each `std::index_sequence` will be wrapped into `Prefix` to produce concept packs.
Then, we expand the concept packs alongside the arguments to reach the desired positions.

```C++
template<typename, auto>
concept Prefix = true;
```

`Shuttle` is used to store the result. We declare `Shuttle` as follows.

```C++
template<auto...>
struct Shuttle;
```

Here is a simplified version of the implementation.

```C++
template<typename...>
struct InsertValues {};

/**** Base Case ****/
template<auto...I>
struct InsertValues<std::index_sequence<I...>>
{
    template<auto NewVariable, auto...>
    struct ProtoPage
    {
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the desired position.
            Prefix<I> auto...front_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> Shuttle
        <
            decltype(front_args)::value...,
            NewVariable,
            BackArgs::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<auto...I, auto...J>
struct InsertValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<auto FirstNewVariable, auto SecondNewVariable, auto...>
    struct ProtoPage
    {
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the position for the first new variable.
            Prefix<I> auto...front_args,
            // Expand `Prefix<J>` to reach the position for the second new variable.
            Prefix<J> auto...middle_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> Shuttle
        <
            decltype(front_args)::value...,
            FirstNewVariable,
            decltype(middle_args)::value...,
            SecondNewVariable,
            BackArgs::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct InsertValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<auto FirstNewVariable, auto SecondNewVariable, auto...OtherNewVariables>
    struct ProtoPage
    {
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the position for the first new variable.
            Prefix<I> auto...front_args,
            // Expand `Prefix<J>` to reach the position for the second new variable.
            Prefix<J> auto...middle_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> ExtendFront
        <
            decltype
            (
                InsertValues<OtherSequences...>
                ::template Page<OtherNewVariables...>
                ::idyl(BackArgs{}...)
            )
        >
        ::template Page
        <
            decltype(front_args)::value...,
            FirstNewVariable,
            decltype(middle_args)::value...,
            SecondNewVariable
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/insert_values/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/insert_values.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/insert_values.test.hpp)
