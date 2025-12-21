<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Amid`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-amid">To Index</a></p>

## Description

`Varybivore::Amid` accepts a list of variables and returns a function.

When invoked by an index, the function returns the variable at the index from the list.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> V<sub>I</sub></code></pre>

## Type Signature

```Haskell
Amid
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Amid
{
    template<auto>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };

    template<auto>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will pick the variable at index `3` out of the list `0, 1, 2, 3`.

```C++
static_assert(Amid<0, 1, 2, 3>::Page<3>::value == 3);
```

## Implementation

We will label each variable by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding variable from the roster.

First, we need to create a label class.

```C++
template<typename Treasure, typename Key>
struct Label
{ static constexpr auto idyl(Key) -> Treasure; };
```

Note that `Label::idyl` maps its parameter type `Key` to its return type `Treasure`. We will pack each variable into a `Vay` so that we can use it as a return type:

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

We can pull out the variable of a given index by asking `decltype` the return type of `idyl` if invoked by the corresponding `Key`.
For this purpose, we will convert an index into a type via `std::integral_constant`.
So, the final mapping will be as follows:

<pre><code>std::integral_constant&lt;I&gt; -> Vay&lt;Variablv<sub>I</sub>&gt;</code></pre>

Now, we will assemble an overload set and instruct compilers to pull the variable out when provided with an index. Here's the entire implementation:

```C++
template<auto...Variables>
struct Amid
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Vay<Variables>, std::integral_constant<size_t, I>>...
    {
        // We bring every `idyl` from its base class to the current scope.
        using Label<Vay<Variables>, std::integral_constant<size_t, I>>::idyl...;
    };

    template<size_t I>
    struct ProtoPage
    {
        // We ask the compiler to find an `idyl` that
        // declares a parameter of type `std::integral_constant<size_t, I>`.
        // If found, the value result of the return type
        // of such `idyl` is the variable of index I in the list.
        static constexpr auto value 
        {
            decltype
            (
                Detail<std::make_index_sequence<sizeof...(Variables)>>
                ::idyl(std::integral_constant<size_t, I>{})
            )::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/amid/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/amid.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/amid.test.hpp)
