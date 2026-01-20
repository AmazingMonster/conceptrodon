<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Slice`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-slice">To Index</a></p>

## Description

`Varybivore::Slice` accepts a list of variables.

- Suppose its first layer is instantiated with an index.
In that case, it returns a function.

When invoked by an operation, the function collects all variables with indices greater or equal to the given index from the list and instantiates the operation with the collection.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> Oper
-> Oper&lt;V<sub>I</sub>, ..., V<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function collects all the variables of indices within the interval from the list and instantiates the operation with the collection.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>J-1</sub>, ..., V<sub>n</sub>
-> I, J
-> Oper
-> Oper&lt;V<sub>I</sub>, ..., V<sub>J-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Slice
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Slice
{
    template<auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

```C++
template<auto...>
struct Slice
{
    template<auto, auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

- In the first example, we will collect all variables from `0, 1, 2 ,2` starting from index two.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 2>;

/**** Result ****/
using Result = Slice<0, 1, 2, 2>
::Page<2>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

- In the second example, we will collect variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2>;

/**** Result ****/
using Result_1 = Slice<0, 1, 2, 2>
::Page<1, 3>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Erase` using concept expansion.

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

- In the case where the second layer of `Slice` only accepts an amount, we want to remove the variables of the given amount from the front of the list.

```C++
template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        typename...Targets
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the uwanted arguments.
        Prefix<I> auto...,
        // Collect the rest.
        Targets...
    )
    -> Operation<Targets::value...>;
};
```

- In the case where the second layer of `Slice` accepts two indices, we want to collect the variables between them.

```C++
template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<auto...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the uwanted arguments.
        Prefix<I> auto...,
        // Expand `Prefix<J>` to collect the proper number of arguments.
        Prefix<J> auto...targets,
        // Remove the rest.
        ...
    )
    -> Operation<decltype(targets)::value...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Slice
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Shear<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {   
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/slice/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/slice.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/slice.test.hpp)
