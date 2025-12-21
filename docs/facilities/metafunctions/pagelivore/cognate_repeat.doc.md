<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRepeat`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-repeat">To Index</a></p>

## Description

`Pagelivore::CognateRepeat` accepts an operation.
Its first layer accepts the times of repetitions and returns a function.

When invoked, the function repeats its argument list the given number of times and uses the result to instantiate the operation.

<pre><code>   Oper
-> N
-> Args...
-> Oper&lt;Args...<sub>1</sub>, Args...<sub>2</sub>, ..., Args...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateRepeat
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRepeat
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four iterations of `0, 1`:

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<
    0, 1,
    0, 1,
    0, 1,
    0, 1
>;

/**** Result ****/
using Result = CognateRepeat<Operation>
::Page<4>
::Page<0, 1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateRepeat` with the help of `TypicalReiterate`, which is implemented using recursion over the total number of parameters.
Each intermediate result will be kept inside a `Shuttle`.
When the iteration completes, we transfer the variables from the final `Shuttle` to the operation.

- **Base Case:** Handle several numbers of times directly.
- **Recursive Case:**
  1. Iterate several times;
  2. Reduce the total times by the same amount;
  3. Invoke the first layer of `TypicalReiterate` with the times left;
  4. Concatenate two results.

We will use `ExtendBack` to concatenate two parts.

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

We will use `TypicalReiterate` to reiterate the variables.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Varybivore::TypicalReiterate ****/
namespace Varybivore {

template<auto...Variables>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Shuttle<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Shuttle<Variables...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Page<Variables..., Variables...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
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

Here is the entire implementation:

```C++
template<template<auto...> class Operation>
struct CognateRepeat
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Send
        <
            typename Varybivore::TypicalReiterate<Variables...>
            ::template ProtoPage<Amount>::type
        >
        ::template Rail<Operation>;
    };

    template<size_t...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_repeat/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/cognate_repeat.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_repeat.test.hpp)
