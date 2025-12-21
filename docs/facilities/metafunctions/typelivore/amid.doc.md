<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Amid`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-amid">To Index</a></p>

## Description

`Typelivore::Amid` accepts a list of elements and returns a function.

When invoked by an index, the function returns the element at the index from the list.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> E<sub>I</sub></code></pre>

## Type Signature

```Haskell
Amid
 :: typename...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Amid
{
    template<auto>
    alias Page = RESULT;
};
```

## Examples

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
/**** SupposedResult ****/
using SupposedResult = int***;

/**** Result ****/
using Result = Amid<int, int*, int**, int***>::Page<3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will label each element by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding element from the roster.

First, we need to create a label class:

```C++
template<typename Treasure, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Treasure;
};
```

We can pull out the variable of a given index by asking `decltype` the return type of `idyl` if invoked by the corresponding `Key`.
For this purpose, we will convert an index into a type via `std::integral_constant`.
So, the final mapping will be as follows:

<pre><code>std::integral_constant&lt;I&gt; -> Element<sub>I</sub></code></pre>

Now, we will assemble an overload set and instruct compilers to pull the element out when provided with an index. Here's the entire implementation:

```C++
template<typename...Elements>
struct Amid
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Elements, std::integral_constant<size_t, I>>...
    {
        // We bring every `idyl` from its base class to the current scope.
        using Label<Elements, std::integral_constant<size_t, I>>::idyl...;
    };

    template<size_t I>
    struct Hidden
    {
        // We ask the compiler to find an `idyl` that
        // declares a parameter of type `std::integral_constant<size_t, I>`.
        // If found, the return type of such `idyl` is the element
        // of index I in the list.
        using type = decltype
        (
            Detail<std::make_index_sequence<sizeof...(Elements)>>
            ::idyl(std::integral_constant<size_t, I>{})
        );
    };

    template<auto...Agreements>
    using Page = Hidden<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/amid/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/amid.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/amid.test.hpp)
