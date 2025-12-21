<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateReverse`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-reverse">To Index</a></p>

## Description

`Pagelivore::CognateReverse` accepts an operation and returns a function.

When invoked, the function instantiates the operation with its argument list but in reversed order.

<pre><code>   Oper
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>n</sub>, Arg<sub>n-1</sub>, ..., Arg<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateReverse
 :: template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateReverse
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will turn over `0, 1, 2, 2` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 2, 1, 0>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateReverse<Operation>::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateReverse` with the help of `TypicalTurnOver`, which is implemented using recursion over the total number of parameters.
Each intermediate result will be kept inside a `Shuttle`.
When the entire list is turned over, we transfer the variables from the final `Shuttle` to the operation.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Turn over several variables in the front of the list;
  2. Invoke `TypicalTurnOver` by the rest to turn them over;
  3. Switch the positions of these two flipped parts and concatenate them together.

We will use `ExtendBack` to concatenate two flipped parts.

```C++
template<typename...>
struct ExtendBack {};

template<
    template<auto...> class Sequence,
    auto...Variables
>
struct ExtendBack<Sequence<Variables...>>
{
    template<auto...Agreements>
    using Page = Sequence<Variables..., Agreements...>;
};
```

We will use `TypicalTurnOver` to turn over the variable list.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Varybivore::TypicalTurnOver ****/
namespace Varybivore {

template<auto...>
struct TypicalTurnOver {};

template<auto First>
struct TypicalTurnOver<First>
{
    using type = Shuttle<First>;
};

template<auto First, auto Second>
struct TypicalTurnOver<First, Second>
{
    using type = Shuttle<Second, First>;
};

template<auto First, auto Second, auto...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Page<Second, First>;
};

}
```

We will use `Send` to transfer variables from the final `Shuttle`.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
```

Here's the entire implementation:

```C++
template<template<auto...> class Operation>
struct CognateReverse
{
    template<auto...Variables>
    using Page = Send
    <
        typename Varybivore::TypicalTurnOver<Variables...>
        ::type
    >
    ::template Rail<Operation>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_reverse/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/cognate_reverse.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_reverse.test.hpp)
