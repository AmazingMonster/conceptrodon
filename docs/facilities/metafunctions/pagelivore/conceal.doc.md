<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Conceal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-conceal">To Index</a></p>

## Description

`Pagelivore::Conceal` accepts an operation and returns a function.

When invoked, the function instantiates the operation with the arguments and returns the result using alias member `type`.
Overall, `Conceal` turns an operation into its `Typical` counterpart.

<pre><code>   Oper
-> Args...
-> struct { using type=Oper&lt;Args...&gt;; }</code></pre>

## Type Signature

```Haskell
Conceal
 :: template<auto...> class... 
 -> auto...
 -> typename
```

## Structure

```C++
template<template<auto...> class>
struct Conceal
{
    template<auto...>
    alias Page
    {
        using type = RESULT;
    };
};
```

## Examples

We will conceal `Operation`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2, 3>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Conceal<Operation>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 3>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Pagelivore::Conceal`:

```C++
template<template<auto...> class Operation>
struct Conceal
{
    template<auto...Variables>
    struct ProtoPage
    { using type = Operation<Variables...>; };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/conceal/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/conceal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/conceal.test.hpp)
