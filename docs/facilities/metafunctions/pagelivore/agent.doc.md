<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Agent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-agent">To Index</a></p>

## Description

`Pagelivore::Agent` accepts an operation and returns a function.

When invoked by a packed sequence, the function extracts the list of variables from the packed sequence and instantiates the operation with the list.

<pre><code>   Oper
-> Seq&lt;Vs...&gt;
-> Oper&lt;Vs...&gt;</code></pre>

## Type Signature

```Haskell
Agent
 :: template<auto...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<auto...> class>
struct Agent
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

- We will create an `Agent` of the `Operation` and invoke the returned function with `Shuttle<0, 1, 2>`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result = Metafunction<Shuttle<0, 1, 2>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will invoke the returned metafunction again with `std::index_sequence<0, 1, 2>`, which is an alias for `std::integer_sequence<size_t, 0, 1, 2>`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation
<
    static_cast<size_t>(0),
    static_cast<size_t>(1),
    static_cast<size_t>(2)
>;

/**** Result ****/
using Result_1 = Metafunction<std::index_sequence<0, 1, 2>>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

## Implementation

`Pagelivore::Agent` uses partial template specialization to extract variables from a packed sequence. Here is the entire implementation:

```C++
template<template<auto...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<auto...> class Sequence, auto...Variables>
    struct Detail<Sequence<Variables...>>
    { using type = Operation<Variables...>; };
    
    // This specialization handles `std::integer_sequence`.
    template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
    struct Detail<Sequence<Type, Variables...>>
    { using type = Operation<Variables...>; };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/agent/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/agent.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/agent.test.hpp)
