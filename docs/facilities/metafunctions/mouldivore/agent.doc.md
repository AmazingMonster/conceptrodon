<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Agent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-agent">To Index</a></p>

## Description

`Mouldivore::Agent` accepts an operation and returns a function.

When invoked by a packed container, the function extracts the elements from the packed container and instantiates the operation with them.

<pre><code>   Oper
-> Con&lt;Es...&gt;
-> Oper&lt;Es...&gt;</code></pre>

## Type Signature

```Haskell
Agent
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Agent
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

We will create an `Agent` of the `Operation` and invoke the returned function with `Capsule<int, int*, int**>`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = Metafunction<Capsule<int, int*, int**>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Mouldivore::Agent` uses partial template specialization to extract elements from a packed container. Here is the entire implementation:

```C++
template<template<typename...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<typename...> class Container, typename...Elements>
    struct Detail<Container<Elements...>>
    { using type = Operation<Elements...>; };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/agent/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/agent.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/agent.test.hpp)
