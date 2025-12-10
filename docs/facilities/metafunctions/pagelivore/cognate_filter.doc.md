<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateFilter`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-filter">To Index</a></p>

## Description

`Pagelivore::CognateFilter` accepts an operation. Its first layer accepts a list of predicates and returns a function.

When invoked, the function removes every argument that satisfies all of the predicates from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? (nothing) : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? (nothing) : Arg<sub>1</sub>,
                            &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? (nothing) : Arg<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateFilter
 :: template<auto...> class...
 -> template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateFilter
{
    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will remove every variable divisible by two and three from the list `1, 12, 2, 6, 15` and instiate `Operation` with the variables left.

```C++
/**** DivisibleByTwo ****/
template<auto I>
struct DivisibleByTwo
{
    static constexpr bool value
    {I % 2 == 0};
};

/**** DivisibleByThree ****/
template<auto I>
struct DivisibleByThree
{
    static constexpr bool value
    {I % 3 == 0};
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateFilter<Operation>
::Rail<DivisibleByTwo, DivisibleByThree>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<1, 2, 15>;

/**** Result ****/
using Result = Metafunction<1, 12, 2, 6, 15>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`CognateFilter` is implemented based on `Pagelivore::Sieve`.
It transfers the result of `Pagelivore::Sieve` to the given operation.
We will use the following function to send the result.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
```

Here is the entire implementation:

```C++
template<template<auto...> class Operation>
struct CognateFilter
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Send
        <
            typename Sieve<Predicates...>
            ::template Page<Variables...>
        >
        ::template Rail<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_filter/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/cognate_filter.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_filter.test.hpp)
