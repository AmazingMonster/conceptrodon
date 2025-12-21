<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Conceal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-conceal">To Index</a></p>

## Description

`Raillivore::Conceal` accepts an operation and returns a function.

When invoked, the function instantiates the operation with the arguments and returns the result using alias member `type`.
Overall, `Conceal` turns an operation into its `Typical` counterpart.

<pre><code>   Oper
-> Args...
-> struct { using type=Oper&lt;Args...&gt;; }</code></pre>

## Type Signature

```Haskell
Conceal
 :: template<template<auto...> class...> class... 
 -> template<auto...> class...
 -> typename
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Conceal
{
    template<template<auto...> class...>
    alias Rail
    {
        using type = RESULT;
    };
};
```

## Examples

We will conceal `Operation`.

```C++
/**** Dummy Arguments ****/
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
using Metafunction = Conceal<Operation>
::Rail<Args...>;

/**** Result ****/
using Result = Metafunction<Seq_2, Seq_3, Seq_0, Seq_1>::type;

/**** Result ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Raillivore::Conceal`:

```C++
template<template<template<auto...> class...> class Operation>
struct Conceal
{
    template<template<auto...> class...Sequences>
    struct ProtoRail
    { using type = Operation<Sequences...>; };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/conceal/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/raillivore/conceal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/conceal.test.hpp)
