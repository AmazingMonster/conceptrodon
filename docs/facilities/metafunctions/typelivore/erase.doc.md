<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Erase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-erase">To Index</a></p>

## Description

`Typelivore::Erase` accepts a list of elements.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.

When invoked by an operation, the function removes the element at the index from the list and instantiates the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, E<sub>I+1</sub>, ..., E<sub>n</sub>
-> I
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I+1</sub>, ..., E<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function removes the elements of indices within the interval from the list and invokes the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>J-1</sub>, E<sub>J</sub>, ..., E<sub>n</sub>
-> I, J
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>J</sub>, ..., E<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Erase
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Erase
{
    template<auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
}；
```

```C++
template<typename...>
alias Erase
{
    template<auto, auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
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

/**** Result ****/
using Result = Erase<int, int*, int**, int**>::Page<1>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase elements between indices one and three from `int, int*, int**, int**`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int, int**>;

/**** Result ****/
using Result_1 = Erase<int, int*, int**, int**>::Page<1, 3>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Erase` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

- In the case where the second layer of `Erase` only accepts one index, we want to remove the element at the index from the list.

```C++
template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        typename...BackArgs
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_args,
        // Remove the next.
        auto,
        // Collect the rest.
        BackArgs...
    )
    -> Operation
    <
        typename decltype(front_args)::type...,
        typename BackArgs::type...
    >;
};
```

- In the case where the second layer of `Erase` accepts two indices, we want to remove the elements between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
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
        typename decltype(front_args)::type...,
        typename BackArgs::type...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke ordinary functions.

```C++
template<typename...Elements>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Expunge
            <
                std::make_index_sequence<Start>,
                // `End-Start` is the number of elements we will erase.
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/erase/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/erase.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/erase.test.hpp)
