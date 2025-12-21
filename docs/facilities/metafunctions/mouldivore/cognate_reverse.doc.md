<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateReverse`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-reverse">To Index</a></p>

## Description

`Mouldivore::CognateReverse` accepts an operation and returns a function.

When invoked, the function instantiates the operation with its argument list but in reversed order.

<pre><code>   Oper
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>n</sub>, Arg<sub>n-1</sub>, ..., Arg<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateReverse
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateReverse
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will turn over `int, int*, int**, int**` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int**, int*, int>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateReverse<Operation>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateReverse` with the help of `TypicalTurnOver`, which is implemented using recursion over the total number of parameters.
Each intermediate result will be kept inside a `Capsule`.
When the entire list is turned over, we transfer the elements from the final `Capsule` to the operation.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Turn over several elements in the front of the list;
  2. Invoke `TypicalTurnOver` by the rest to turn them over;
  3. Switch the positions of these two flipped parts and concatenate them together.

We will use `ExtendBack` to concatenate two flipped parts.

```C++
template<typename...>
struct ExtendBack {};

template<
    template<typename...> class Container,
    typename...Elements
>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Agreements>
    using Mold = Container<Elements..., Agreements...>;
};
```

We will use `Typelivore::TypicalTurnOver` to turn over the element list.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Typelivore::TypicalTurnOver ****/
namespace Typelivore {

template<typename...>
struct TypicalTurnOver {};

template<typename First>
struct TypicalTurnOver<First>
{
    using type = Capsule<First>;
};

template<typename First, typename Second>
struct TypicalTurnOver<First, Second>
{
    using type = Capsule<Second, First>;
};

template<typename First, typename Second, typename...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type 
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Mold<Second, First>;
};

}
```

We will use `Send` to transfer elements from the final `Capsule`.

```C++
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here's the entire implementation:

```C++
template<template<typename...> class Operation>
struct CognateReverse
{
    template<typename...Elements>
    using Mold = Send<typename Typelivore::TypicalTurnOver<Elements...>::type>
    ::template Road<Operation>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_reverse/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/cognate_reverse.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_reverse.test.hpp)
