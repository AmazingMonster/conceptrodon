<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Bind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-bind">To Index</a></p>

## Description

`Pagelivore::Bind` accepts an operation.
Its first layer accepts a list of variables containing pegs and returns a function.
When invoked, the function replaces the pegs in the variable list with arguments at the corresponding position from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> V<sub>0</sub>, V<sub>1</sub>, ..., Peg&lt;I<sub>0</sub>&gt;, ..., Peg&lt;I<sub>1</sub>&gt;, ..., Peg&lt;I<sub>k</sub>&gt;, ..., V<sub>m</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., Arg<sub>I<sub>0</sub>-1</sub>, ..., Arg<sub>I<sub>1</sub>-1</sub>, ..., Arg<sub>I<sub>k</sub>-1</sub>, ..., V<sub>m</sub>&gt;</code></pre>

## Type Signature

```Haskell
Bind
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct Bind
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Example

We will bind the second and the fourth parameter of `Operation` with `-2, -4` and reverse the order of the first and the third parameter.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Bind<Operation>
::Page<Peg<2>{}, -2, Peg<1>{}, -4>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<3, -2, 1, -4>;

/**** Result ****/
// The `nullptr` at the end has not effect.
using Result = Metafunction<1, 3, nullptr>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Bind` is a special version of `CognateTransform` as it transforms pegs into variables from another list. Hence, their implementations are very similar.

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

We will pick out variables from the argument list of the finally-returned function via `Varybivore::Among` in the following helper template.
It detects and transforms the pegs by a partial specialization, which is specialized by constraints.

```C++
template<auto Variable>
static constexpr auto Hidden_v {Variable};

// This specialization will be used
// if `Pegful<decltype(Variable)> && Nonzero<decltype(Variable)> == true`.
template<auto Variable>
requires Pegful<decltype(Variable)> && Nonzero<decltype(Variable)>
static constexpr auto Hidden_v<Variable> 
{
    // `Replacements...` are the arguments of the finally-returned function
    Among<Replacements...>
    ::template Page<Variable.value - 1>
    ::value
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation>
struct Bind
{
    template<auto...Variables>
    struct ProtoPage
    {
        template<auto...Replacements>
        struct Detail
        {
            template<auto Variable>
            static constexpr auto Hidden_v {Variable};
            
            template<auto Variable>
            requires Pegful<decltype(Variable)>
            && Nonzero<decltype(Variable)>
            static constexpr auto Hidden_v<Variable> 
            {
                Among<Replacements...>
                ::template Page<Variable.value - 1>
                ::value
            };

            using type = Operation<Hidden_v<Variables>...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/bind/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/bind.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/bind.test.hpp)
