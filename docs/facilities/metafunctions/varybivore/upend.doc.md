<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Upend`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-upend">To Index</a></p>

## Description

`Varybivore::Upend` accepts a list of variables and returns a function.

When invoked by an operation, the function instantiates the operation with the previously provided variables but in reversed order.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper
-> Oper&lt;V<sub>n</sub>, V<sub>n-1</sub>, ..., V<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
Upend
 :: auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Upend
{
    template<template<auto...> class>
    alias Rail = RESULT;
};
```

## Examples

We will flip `0, 1, 2, 2` and invoke `Operation` with the result.

```C++
/**** Shuttle ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 2, 1, 0>;

/**** Result ****/
using Result = Upend<0, 1, 2, 2>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Varybivore::Amid`.
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

<pre><code>std::integral_constant&lt;I&gt; -> Vay&lt;V<sub>I</sub>&gt;</code></pre>

Now, we will assemble an overload set and instruct compilers to pull the variables out in reversed order. Here's the entire implementation:

```C++
template<auto...Variables>
struct Upend
{
    template<template<auto...> class, typename>
    struct Detail {};

    template<template<auto...> class Operation, size_t...I>
    struct Detail<Operation, std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Vay<Variables>, std::integral_constant<size_t, I>>...
    {
        using Label<Vay<Variables>, std::integral_constant<size_t, I>>::idyl...;
        using type = Operation<
            // Note that `sizeof...(I)` is the total number of I...,
            // which is a constant.
            // We are doing pack expansion over the second I.
            // The result is a list of form:
            // sizeof...(I) - 1, sizeof...(I) - 2, ..., 0. 
            decltype(
                idyl(
                    std::integral_constant
                    <size_t, sizeof...(I) - I - 1>{}
                )
            // We pull the value result out of `Vay`.
            )::value...
        >;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements..., std::make_index_sequence<sizeof...(Variables)>>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/upend/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/upend.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/upend.test.hpp)
