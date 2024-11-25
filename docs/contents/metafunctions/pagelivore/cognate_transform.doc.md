<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateTransform`

## Description

`Pagelivore::CognateTransform` accepts an operation.
Its first layer accepts a list of predicates.
Its second layer accepts a transformation and returns a function.
When invoked, the function transforms its arguments that satisfy all the predicates with the transformation and instantiates the first operation with the result.

<pre><code>   FirstOperation
-> Predicates...
-> Transformation
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>i</sub>, ..., V<sub>n</sub>
-> FirstOperation
   <
       (...&&Predicates&lt;V<sub>0</sub>&gt;::value) ? Transformation&lt;V<sub>0</sub>&gt;::value : V<sub>0</sub>,
       (...&&Predicates&lt;V<sub>1</sub>&gt;::value) ? Transformation&lt;V<sub>1</sub>&gt;::value : V<sub>1</sub>,
                                    &vellip;
       (...&&Predicates&lt;V<sub>i</sub>&gt;::value) ? Transformation&lt;V<sub>i</sub>&gt;::value : V<sub>i</sub>,
                                    &vellip;
       (...&&Predicates&lt;V<sub>n</sub>&gt;::value) ? Transformation&lt;V<sub>n</sub>&gt;::value : V<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateTransform ::   template<auto...> class...
                   -> template<auto...> class...
                   -> template<auto...> class...
                   -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateTransform
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail
        {
            template<auto...>
            alias Page = RESULT;
        };
    };
};
```

## Example

We will apply `UnaryMinus` to variables divisible by two and three in the list `1, 12, 2, 6, 15`.

```C++
template<auto I>
struct DivisibleByTwo
{
    static constexpr bool value
    {I % 2 == 0};
};

template<auto I>
struct DivisibleByThree
{
    static constexpr bool value
    {I % 3 == 0};
};

template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

template<auto...>
struct Operation;

template<auto...Args>
using Metafunction = CognateTransform<Operation>
::Rail<DivisibleByTwo, DivisibleByThree>
::Rail<UnaryMinus>
::Page<Args...>;

using SupposedResult = Operation<1, -12, 2, -6, 15>;

using Result = Metafunction<1, 12, 2, 6, 15>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

For every variable in the list, we transform it with the second operation if it satisfies all the predicates.
We will do this using the following helper template.
It decides whether a variable shall be transformed.
The selection is done by a partial specialization, which is specialized by a constraint.

```C++
template<auto Variable>
struct Hidden 
{
    static constexpr auto value
    {Variable};
};

// `Puberty...` are the predicates.
// This partial specialization will be selected
// if `(...&&Puberty<Variable>::value) == true`.
template<auto Variable>
requires (...&&Puberty<Variable>::value)
struct Hidden<Variable>
{
// `Hormone` is the second operation.
    static constexpr auto value
    {Hormone<Variable>::value};
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation>
struct CognateTransform
{
    template<template<auto...> class...Puberty>
    struct ProtoRail
    {
        struct Slash
        {
            template<template<auto...> class Hormone>
            struct ProtoRail
            {
                template<auto Variable>
                struct Hidden 
                {
                    static constexpr auto value
                    {Variable};
                };

                template<auto Variable>
                requires (...&&Puberty<Variable>::value)
                struct Hidden<Variable>
                {
                    static constexpr auto value
                    {Hormone<Variable>::value};
                };

                template<auto...Variables>
                using Page = Operation<Hidden<Variables>::value...>;
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = Slash::template ProtoRail<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_transform.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_transform.test.hpp)
