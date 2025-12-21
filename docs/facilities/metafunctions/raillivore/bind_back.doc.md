<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::BindBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-bind-back">To Index</a></p>

## Description

`Raillivore::BindBack` accepts an operation.
Its first layer accepts a list of sequences and returns a function.

When invoked, the function adds the sequences to the end of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Seqs...
-> Args...
-> Oper&lt;Args..., Seqs...&gt;</code></pre>

## Type Signature

```Haskell
BindBack
 :: template<template<auto...> class...> class... 
 -> template<auto...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct BindBack
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

We will bind `Seq_0, Seq_1` to the back of `Operation`.

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
using SupposedResult = Operation<Seq_2, Seq_3, Seq_0, Seq_1>;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = BindBack<Operation>
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
struct BindBack
{
    template<template<auto...> class...Endings>
    struct ProtoRail
    {
        template<template<auto...> class...Sequences>
        using Rail = Operation<Sequences..., Endings...>;
    };

    template<template<auto...> class...Endings>
    using Rail = ProtoRail<Endings...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/bind_back/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/raillivore/bind_back.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/bind_back.test.hpp)
