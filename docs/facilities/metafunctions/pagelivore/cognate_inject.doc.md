<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateInject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-inject">To Index</a></p>

## Description

`Pagelivore::CognateInject` accepts an operation.
Its first layer accepts an index, which indicates a location in a list.
Its second layer accepts a list of new variables and returns a function.

When invoked, the function injects new variables into the location of its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Vs...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Vs..., Arg<sub>I</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateInject
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateInject
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page
        { 
            template<auto...>
            alias Page = RESULT;
        };
        
    };
}；
```

## Examples

We will inject `10, 11` into index one of `0, 1, 2`. Then, we will instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 10, 11, 1, 2>;

/**** Result ****/
using Result = CognateInject<Operation>
::Page<1>
::Page<10, 11>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateInject` using concept expansion.

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

`Enrich` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<auto...NewVariables>
    struct ProtoPage
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
            // Collect the rest.
            BackArgs...
        )
        -> Operation
        <
            decltype(front_args)::value...,
            NewVariables...,
            BackArgs::value...
        >;
    };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateInject
{
    template<size_t Index>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...NewVariables>
            struct ProtoPage
            {
                template<auto...Variables>
                using Page = decltype
                (
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoPage<NewVariables...>
                    ::template idyl<Operation>(Vay<Variables>{}...)
                );
            };
        };

        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_inject/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/cognate_inject.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_inject.test.hpp)
