<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Bind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-bind">To Index</a></p>

## Description

`Mouldivore::Bind` accepts an operation.
Its first layer accepts a list of elements containing pegs and returns a function.

When invoked, the function replaces the pegs in the element list with arguments at the corresponding position from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> E<sub>0</sub>, E<sub>1</sub>, ..., Peg&lt;I<sub>0</sub>&gt;, ..., Peg&lt;I<sub>1</sub>&gt;, ..., Peg&lt;I<sub>k</sub>&gt;, ..., E<sub>m</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., Arg<sub>I<sub>0</sub>-1</sub>, ..., Arg<sub>I<sub>1</sub>-1</sub>, ..., Arg<sub>I<sub>k</sub>-1</sub>, ..., E<sub>m</sub>&gt;</code></pre>

## Type Signature

```Haskell
Bind
 :: template<typename...> class...
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Bind
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Example

We will bind the second and the fourth parameter of `Operation` with `Vay<-2>, Vay<-4>` and reverse the order of the first and the third parameter.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Bind<Operation>
::Mold<Peg<2>, Vay<-2>, Peg<1>, Vay<-4>>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<3>, Vay<-2>, Vay<1>, Vay<-4>>;

/**** Result ****/
// The `void` at the end has not effect.
using Result = Metafunction<Vay<1>, Vay<3>, void>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Bind` is a special version of `CognateTransform` as it transforms pegs into elements from another list. Hence, their implementations are very similar.

First, we will create `Peg`, which is similar to `std::placeholders::_1, std::placeholders::_2, ...` in terms of functionality.

```C++
template <size_t I>
struct Peg
{ static constexpr size_t value {I}; };
```

We will detect the pegs using the following concept.
Since we cannot specialize a concept, `Pegful` will redirect its argument to the helper class template `IsPeg`.

```C++
/**** IsPeg ****/
template<typename>
struct IsPeg
{
    static constexpr bool value
    {false};
};

template<auto I>
struct IsPeg<Peg<I>>
{
    static constexpr bool value
    {true};
};

/**** Pegful ****/
template<typename Arg>
concept Pegful = IsPeg<Arg>::value;
```

We also need to ensure the integer stored in a peg is not zero, as we will subtract the value by one to obtain an index.
This is to conform to the behavior of `std::bind` and the placeholder objects.
Hence, we create the following concept.

```C++
template<typename Arg>
concept Nonzero = (Arg::value != 0);
```

We will pick out elements from the argument list of the finally-returned function via `Typelivore::TypicalAmong` in the following helper template.
It detects and transforms the pegs by a partial specialization, which is specialized by constraints.

```C++
template<typename Element>
struct Hidden
{ using type = Element; };

// This specialization will be used
// if `Pegful<Element> && Nonzero<Element> == true`.
template<typename Element>
requires Pegful<Element> && Nonzero<Element>
struct Hidden<Element> 
{
    // `Replacements...` are the arguments of the finally-returned function
    using type = TypicalAmong<Replacements...>
    ::template Page<Element.value - 1>
    ::type;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct Bind
{
    template<typename...Elements>
    struct ProtoMold
    {
        template<typename...Replacements>
        struct Detail
        {
            template<typename Element>
            struct Hidden 
            { using type = Element; };

            template<typename Element>
            requires Pegful<Element> && Nonzero<Element>
            struct Hidden<Element>
            { 
                using type = Typelivore::TypicalAmong<Replacements...>
                ::template Page<Element::value - 1>
                ::type; 
            };

            using type = Operation<typename Hidden<Elements>::type...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/bind/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/bind.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/bind.test.hpp)
