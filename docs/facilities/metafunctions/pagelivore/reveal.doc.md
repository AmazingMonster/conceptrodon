<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Reveal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-reveal">To Index</a></p>

## Description

`Pagelivore::Reveal` accepts an operation and returns a function.

When invoked, the function instantiates the operation with the arguments and becomes its type result.
Overall, `Reveal` turns a `Typical` operation into its non-prefixed counterpart.

<pre><code>   Operation
-> using Mold&lt;***&gt; = Operation&lt;***&gt;::type</code></pre>

## Type Signature

```Haskell
Reveal
 :: template<auto...> class... 
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class...> class>
struct Reveal
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will reveal `Operation`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Operation ****/
template<auto...Args>
struct Operation
{ using type = Shuttle<Args...>; };

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, 1, 2, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Reveal<Operation>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Pagelivore::Reveal`:

```C++
template<template<auto...> class Operation>
struct Reveal
{
    template<auto...Variables>
    using Page = Operation<Variables...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/reveal/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/reveal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/reveal.test.hpp)
