<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::BindFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-bind-front">To Index</a></p>

## Description

`Raillivore::BindFront` accepts an operation.
Its first layer accepts a list of sequences and returns a function.

When invoked, the function adds the sequences to the beginning of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Seqs...
-> Args...
-> Oper&lt;Seqs..., Args...&gt;</code></pre>

## Type Signature

```Haskell
BindFront
 :: template<template<auto...> class...> class... 
 -> template<auto...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct BindFront
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will bind `Seq_0, Seq_1` to the front of `Operation`.

```C++
/**** Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** Operation ****/
template<template<auto...> class...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = BindFront<Operation>
::Rail<Seq_0, Seq_1>
::Rail<Args...>;

/**** Result ****/
using Result = Metafunction<Seq_2, Seq_3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<template<auto...> class...> class Operation>
struct BindFront
{
    template<template<auto...> class...Beginnings>
    struct ProtoRail
    {
        template<template<auto...> class...Sequences>
        using Rail = Operation<Beginnings..., Sequences...>;
    };

    template<template<auto...> class...Beginnings>
    using Rail = ProtoRail<Beginnings...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/bind_front/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/raillivore/bind_front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/bind_front.test.hpp)
