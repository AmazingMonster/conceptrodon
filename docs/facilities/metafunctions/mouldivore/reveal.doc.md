<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Reveal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-reveal">To Index</a></p>

## Description

`Mouldivore::Reveal` accepts an operation and returns a function.

When invoked, the function instantiates the operation with the arguments and becomes its type result.
Overall, `Reveal` turns a `Typical` operation into its non-prefixed counterpart.

<pre><code>   Operation
-> using Mold&lt;***&gt; = Operation&lt;***&gt;::type</code></pre>

## Type Signature

```Haskell
Reveal
 :: template<typename...> class... 
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class...> class>
struct Reveal
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will reveal `Operation`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Operation ****/
template<typename...Args>
struct Operation
{ using type = Capsule<Args...>; };

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Reveal<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Mouldivore::Reveal`:

```C++
template<template<typename...> class Operation>
struct Reveal
{
    template<typename...Elements>
    using Mold = Operation<Elements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/reveal/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/reveal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/reveal.test.hpp)
