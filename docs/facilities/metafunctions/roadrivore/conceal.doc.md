<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Conceal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-conceal">To Index</a></p>

## Description

`Roadrivore::Conceal` accepts an operation and returns a function.

When invoked, the function instantiates the operation with the arguments and returns the result using alias member `type`.
Overall, `Conceal` turns an operation into its `Typical` counterpart.

<pre><code>   Oper
-> Args...
-> struct { using type=Oper&lt;Args...&gt;; }</code></pre>

## Type Signature

```Haskell
Conceal
 :: template<template<typename...> class...> class... 
 -> template<typename...> class...
 -> typename
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Conceal
{
    template<template<typename...> class...>
    alias Road
    {
        using type = RESULT;
    };
};
```

## Examples

We will conceal `Operation`.

```C++
/**** Dummy Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** Operation ****/
template<template<typename...> class...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Con_2, Con_3, Con_0, Con_1>;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = Conceal<Operation>
::Road<Args...>;

/**** Result ****/
using Result = Metafunction<Con_2, Con_3, Con_0, Con_1>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Roadrivore::Conceal`:

```C++
template<template<template<typename...> class...> class Operation>
struct Conceal
{
    template<template<typename...> class...Sequences>
    struct ProtoRoad
    { using type = Operation<Sequences...>; };

    template<template<typename...> class...Sequences>
    using Road = ProtoRoad<Sequences...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/conceal/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/roadrivore/conceal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/roadrivore/conceal.test.hpp)
