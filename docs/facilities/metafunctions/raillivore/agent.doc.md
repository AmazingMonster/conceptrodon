<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Agent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-agent">To Index</a></p>

## Description

`Raillivore::Agent` accepts an operation and returns a function.

When invoked by a packed stockroom, the function extracts the list of sequences from the packed stockroom and instantiates the operation with the list.

<pre><code>   Oper
-> Stoc&lt;Seqs...&gt;
-> Oper&lt;Seqs...&gt;</code></pre>

## Type Signature

```Haskell
Agent
 :: template<template<auto...> class...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Agent
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

- We will create an `Agent` of the `Operation` and invoke the returned function with `Carrier<Seq_0, Seq_1, Seq_2>`.

```C++
/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

/**** Operation ****/
template<template<auto...> class...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Seq_0, Seq_1, Seq_2>;

/**** Result ****/
using Result = Metafunction<Carrier<Seq_0, Seq_1, Seq_2>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Raillivore::Agent` uses partial template specialization to extract sequences from a packed stockroom. Here is the entire implementation:

```C++
template<template<template<auto...> class...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
    struct Detail<Stockroom<Sequences...>>
    { using type = Operation<Sequences...>; };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/agent/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/raillivore/agent.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/agent.test.hpp)
