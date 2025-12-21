<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Conceal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-conceal">To Index</a></p>

## Description

`Mouldivore::Conceal` accepts an operation and returns a function.

When invoked, the function instantiates the operation with the arguments and returns the result using alias member `type`.
Overall, `Conceal` turns an operation into its `Typical` counterpart.

<pre><code>   Oper
-> Args...
-> struct { using type=Oper&lt;Args...&gt;; }</code></pre>

## Type Signature

```Haskell
Conceal
 :: template<typename...> class... 
 -> typename...
 -> typename
```

## Structure

```C++
template<template<typename...> class>
struct Conceal
{
    template<typename...>
    alias Mold
    {
        using type = RESULT;
    };
};
```

## Examples

We will conceal `Operation`.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**, int***>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Conceal<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int***>
::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Mouldivore::Conceal`:

```C++
template<template<typename...> class Operation>
struct Conceal
{
    template<typename...Elements>
    struct ProtoMold
    { using type = Operation<Elements...>; };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/conceal/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/conceal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/conceal.test.hpp)
