<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateErase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-erase">To Index</a></p>

## Description

`Mouldivore::CognateErase` accepts an operation.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.

When invoked, the function removes the argument at the index from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.

When invoked, the function removes the arguments of indices within the interval from its argument list and invokes the operation with the result.

<pre><code>   Oper
-> I, J
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>, Arg<sub>J</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>J</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateErase
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateErase
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
}；
```

```C++
template<template<typename...> class>
alias CognateErase
{
    template<auto, auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will remove the element of index one from `int, int*, int**, int**`.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int**, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateErase<Operation>
::Page<1>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase elements between indices one and three from `int, int*, int**, int**`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction_1 = CognateErase<Operation>
::Page<1, 3>
::Mold<Args...>;

/**** Result ****/
using Result_1 = Metafunction_1<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateErase` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

- In the case where the first layer of `CognateErase` only accepts one index, we want to remove the element at the index from the list.

```C++
template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        typename...BackTargets
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_targets,
        // Remove the next.
        auto,
        // Collect the rest.
        BackTargets...
    )
    -> Operation
    <
        typename decltype(front_targets)::type...,
        typename BackTargets::type...
    >;
};
```

- In the case where the first layer of `CognateErase` accepts two indices, we want to remove the elements between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        typename...BackTargets
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_targets,
        // Expand `Prefix<J>` to count the unwanted arguments.
        Prefix<J> auto...,
        // Collect the rest.
        BackTargets...
    )
    -> Operation
    <
        typename decltype(front_targets)::type...,
        typename BackTargets::type...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `Tyy`.

```C++
template<typename Element>
struct Tyy
{
    using type = Element;
};
```

This ensures we can create objects to invoke ordinary functions.

```C++
template<template<typename...> class Operation>
struct CognateErase
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Operation>(Tyy<Elements>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Expunge
            <
                std::make_index_sequence<Start>,
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Operation>(Tyy<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_erase/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/cognate_erase.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_erase.test.hpp)
