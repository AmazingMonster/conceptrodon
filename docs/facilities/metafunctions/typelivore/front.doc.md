<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Front`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-front">To Index</a></p>

## Description

`Typelivore::Front` accepts a list of elements.

- The first element of the list is returned by the member `type`.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> E<sub>0</sub></code></pre>

- If the first layer is invoked by an operation, it instantiate the operation with the first element of the list.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> Oper
-> Oper&lt;E<sub>0</sub>&gt;</code></pre>

- If the first layer is invoked by an amount, it returns a function.

  When invoked by an operation, the function collects elements of the amount from the front of the list and instantiates the operation with the collection.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Front
 :: typename...
 -> typename
```

```Haskell
Front
 :: typename...
 -> template<template<typename...> class...>
```

```Haskell
Front
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Front
{
    using type = RESULT;
}；
```

```C++
template<typename...>
alias Front
{
    template<template<typename...> class>
    alias Road = RESULT;
}；
```

```C++
template<typename...>
alias Front
{
    template<auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
}；
```

## Examples

- We will check the first element of `int, int*, int**, int**`.

```C++
/**** SupposedResult ****/
using SupposedResult = int;

/**** Result ****/
using Result = Front<int, int*, int**, int**>::type;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

- We will invoke the `Operation` with the first element of `int, int*, int**, int**`.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult_1 = Operation<int>;

/**** Result ****/
using Result_1 = Front<int, int*, int**, int**>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

- We will invoke the `Operation` with the first three elements from `int, int*, int**, int**`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<int, int*, int**>;

/**** Result ****/
using Result_2 = Front<int, int*, int**, int**>::Page<3>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_2, Result_2>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Front` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

`Fore` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...targets,
        ...
    )
    -> Operation<typename decltype(targets)::type...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

Note that we wrap the elements inside `Tyy`.

```C++
template<typename Element>
struct Tyy
{
    using type = Element;
};
```

This ensures we can create objects to invoke the ordinary function.

```C++
template<typename First, typename...Elements>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Tyy<First>{}, Tyy<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<First>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    using type = First;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/front/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/front.test.hpp)
