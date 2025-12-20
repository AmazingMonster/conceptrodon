<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Erase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-erase">To Index</a></p>

## Description

`Varybivore::Erase` accepts a list of variables.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.

When invoked by an operation, the function removes the variable at the index from the list and instantiates the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, V<sub>I+1</sub>, ..., V<sub>n</sub>
-> I
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I+1</sub>, ..., V<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.

When invoked by an operation, the function removes the variables of indices within the interval from the list and invokes the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>J-1</sub>, V<sub>J</sub>, ..., V<sub>n</sub>
-> I, J
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>J</sub>, ..., V<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Erase
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Erase
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
alias Erase
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

In the first example, we will remove the variable of index one from `0, 1, 2, 2`.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 2, 2>;

/**** Result ****/
using Result = Erase<0, 1, 2, 2>::Page<1>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<0, 2>;

/**** Result ****/
using Result_1 = Erase<0, 1, 2, 2>::Page<1, 3>::Rail<Operation>;

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

- In the case where the second layer of `Erase` only accepts one index, we want to remove the variable at the index from the list.

```C++
template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        typename...BackArgs
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_targets,
        // Remove the next.
        auto,
        // Collect the rest.
        BackArgs...
    )
    -> Operation
    <
        decltype(front_targets)::value...,
        BackArgs::value...
    >;
};
```

- In the case where the second layer of `Erase` accepts two indices, we want to remove the variables between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<auto...> class Operation,
        typename...BackArgs
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_args,
        // Expand `Prefix<J>` to count the unwanted arguments.
        Prefix<J> auto...,
        // Collect the rest.
        BackArgs...
    )
    -> Operation
    <
        decltype(front_args)::value...,
        BackArgs::value...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Ditch<std::make_index_sequence<Index>>
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
            Expunge
            <
                std::make_index_sequence<Start>,
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/erase/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/erase.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/erase.test.hpp)
