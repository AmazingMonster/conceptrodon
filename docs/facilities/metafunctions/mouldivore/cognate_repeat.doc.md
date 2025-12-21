<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateRepeat`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-repeat">To Index</a></p>

## Description

`Mouldivore::CognateRepeat` accepts an operation.
Its first layer accepts the times of repetitions and returns a function.

When invoked, the function repeats its argument list the given number of times and uses the result to instantiate the operation.

<pre><code>   Oper
-> N
-> Args...
-> Oper&lt;Args...<sub>1</sub>, Args...<sub>2</sub>, ..., Args...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateRepeat
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateRepeat
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four iterations of `Vay<0>, Vay<1>`:

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** Operation ****/
template<typename...>
struct Operation;

/**** SuppoesedResult ****/
using SupposedResult = Operation<
    Vay<0>, Vay<1>,
    Vay<0>, Vay<1>,
    Vay<0>, Vay<1>,
    Vay<0>, Vay<1>
>;

/**** Result ****/
using Result = CognateRepeat<Operation>
::Page<4>
::Mold<Vay<0>, Vay<1>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateRepeat` with the help of `Typelivore::TypicalReiterate`, which is implemented using recursion over the total number of parameters.
Each intermediate result will be kept inside a `Capsule`.
When the iteration completes, we transfer the elements from the final `Capsule` to the operation.

- **Base Case:** Handle several numbers of times directly.
- **Recursive Case:**
  1. Iterate several times;
  2. Reduce the total times by the same amount;
  3. Invoke the first layer of `Typelivore::TypicalReiterate` with the times left;
  4. Concatenate two results.

We will use `ExtendBack` to concatenate two parts.

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

We will use `Typelivore::TypicalReiterate` to reiterate the elements.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Typelivore::TypicalReiterate ****/
namespace Typelivore {

template<typename...Elements>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Capsule<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Capsule<Elements...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Mold<Elements..., Elements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
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

Here is the entire implementation:

```C++
template<template<typename...> class Operation>
struct CognateRepeat
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = Send
        <
            typename Typelivore::TypicalReiterate<Elements...>
            ::template ProtoPage<Amount>::type
        >
        ::template Road<Operation>;
    };

    template<size_t...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_repeat/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/cognate_repeat.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_repeat.test.hpp)
