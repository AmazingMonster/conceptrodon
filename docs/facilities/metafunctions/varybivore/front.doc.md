<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Front`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-front">To Index</a></p>

## Description

`Varybivore::Front` accepts a list of variables.

- The first variable of the list is returned by the member `value`.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> V<sub>0</sub></code></pre>

- If the first layer is invoked by an operation, it instantiate the operation with the first variable of the list.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> Oper
-> Oper&lt;V<sub>0</sub>&gt;</code></pre>

- If the first layer is invoked by an amount, it returns a function.

  When invoked by an operation, the function collects variables of the amount from the front of the list and instantiates the operation with the collection.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Front
 :: auto...
 -> auto
```

```Haskell
Front
 :: auto...
 -> template<template<auto...> class...>
```

```Haskell
Front
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Front
{
    static constexpr auto value
    {RESULT};
}；
```

```C++
template<auto...>
struct Front
{
    template<template<auto...> class>
    alias Rail = RESULT;
}；
```

```C++
template<auto...>
struct Front
{
    template<auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

## Examples

- We will check the first variable of `0, 1, 2, 2`.

```C++
/**** SupposedResult ****/
constexpr auto SupposedResult = 0;

/**** Result ****/
constexpr auto Result = Front<0, 1, 2, 2>::value;

/**** Test ****/
static_assert(SupposedResult == Result);
```

- We will invoke the `Operation` with the first variable of `0, 1, 2, 2`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult_1 = Operation<0>;

/**** Result ****/
using Result_1 = Front<0, 1, 2, 2>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

- We will invoke the `Operation` with the first three variables of `0, 1, 2, 2`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 1, 2>;

/**** Result ****/
using Result_2 = Front<0, 1, 2, 2>::Page<3>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_2, Result_2>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Front` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

`Fore` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<template<auto...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...targets,
        ...
    )
    -> Operation<decltype(targets)::value...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto First, auto...Variables>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Vay<First>{}, Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
    
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<First>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;

    static constexpr auto value {First};
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/front/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/front.test.hpp)
