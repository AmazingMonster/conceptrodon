<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Reveal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-reveal">To Index</a></p>

## Description

`Roadrivore::Reveal` accepts an operation and returns a function.

When invoked, the function instantiates the operation with the arguments and becomes its type result.
Overall, `Reveal` turns a `Typical` operation into its non-prefixed counterpart.

<pre><code>   Operation
-> using Mold&lt;***&gt; = Operation&lt;***&gt;::type</code></pre>

## Type Signature

```Haskell
Reveal
 :: template<template<typename...> class...> class... 
 -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Reveal
{
    template<template<typename...> class...>
    alias Road = RESULT;
};
```

## Examples

We will reveal `Operation`.

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

/**** Vehicle ****/
template<template<typename...> class...>
struct Vehicle;

/**** Operation ****/
template<template<typename...> class...Args>
struct Operation
{ using type = Vehicle<Args...>; };

/**** SupposedResult ****/
using SupposedResult = Vehicle<Con_2, Con_3, Con_0, Con_1>;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = Reveal<Operation>
::Road<Args...>;

/**** Result ****/
using Result = Metafunction<Con_2, Con_3, Con_0, Con_1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Roadrivore::Reveal`:

```C++
template<template<template<typename...> class...> class Operation>
struct Reveal
{
    template<template<typename...> class...Containers>
    using Road = Operation<Containers...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/reveal/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/roadrivore/reveal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/roadrivore/reveal.test.hpp)
