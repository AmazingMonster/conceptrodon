<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Reveal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-reveal">To Index</a></p>

## Description

`Raillivore::Reveal` accepts an operation and returns a function.

When invoked, the function instantiates the operation with the arguments and becomes its type result.
Overall, `Reveal` turns a `Typical` operation into its non-prefixed counterpart.

<pre><code>   Operation
-> using Mold&lt;***&gt; = Operation&lt;***&gt;::type</code></pre>

## Type Signature

```Haskell
Reveal
 :: template<template<auto...> class...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Reveal
{
    template<template<auto...> class...>
    alias Rail = RESULT;
};
```

## Examples

We will reveal `Operation`.

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

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Operation ****/
template<template<auto...> class...Args>
struct Operation
{ using type = Carrier<Args...>; };

/**** SupposedResult ****/
using SupposedResult = Carrier<Seq_2, Seq_3, Seq_0, Seq_1>;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = Reveal<Operation>
::Rail<Args...>;

/**** Result ****/
using Result = Metafunction<Seq_2, Seq_3, Seq_0, Seq_1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Raillivore::Reveal`:

```C++
template<template<template<auto...> class...> class Operation>
struct Reveal
{
    template<template<auto...> class...Sequences>
    using Rail = Operation<Sequences...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/reveal/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/raillivore/reveal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/reveal.test.hpp)
