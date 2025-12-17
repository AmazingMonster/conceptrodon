<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Upend`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-upend">To Index</a></p>

## Description

`Typelivore::Upend` accepts a list of elements and returns a function.

When invoked by an operation, the function instantiates the operation with the previously provided elements but in reversed order.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Oper&lt;E<sub>n</sub>, E<sub>n-1</sub>, ..., E<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
Upend
 :: typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct Upend
{
    template<template<typename...> class>
    alias Road = RESULT;
};
```

## Examples

We will flip `int, int*, int**, int**` and invoke `Operation` with the result.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int**, int*, int>;

/**** Result ****/
using Result = Upend<int, int*, int**, int**>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Typelivore::Amid`.
We will label each element by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding element from the roster.

First, we need to create a label class:

```C++
template<typename Treasure, typename Key>
struct Label
{  static constexpr auto idyl(Key) -> Treasure; };
```

We can pull out the variable of a given index by asking `decltype` the return type of `idyl` if invoked by the corresponding `Key`.
For this purpose, we will convert an index into a type via `std::integral_constant`.
So, the final mapping will be as follows:

<pre><code>std::integral_constant&lt;I&gt; -> E<sub>I</sub></code></pre>

Now, we will assemble an overload set and instruct compilers to pull the elements out in reversed order. Here's the entire implementation:

```C++
template<typename...Elements>
struct Upend
{
    template<template<typename...> class, typename>
    struct Detail {};

    template<template<typename...> class Operation, size_t...I>
    struct Detail<Operation, std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Elements, std::integral_constant<size_t, I>>...
    {
        using Label<Elements, std::integral_constant<size_t, I>>::idyl...;
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
            )...
        >;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements..., std::make_index_sequence<sizeof...(Elements)>>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/upend/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/upend.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/upend.test.hpp)
