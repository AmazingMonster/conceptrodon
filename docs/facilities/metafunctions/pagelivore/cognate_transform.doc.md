<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateTransform`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-transform">To Index</a></p>

## Description

`Pagelivore::CognateTransform` accepts an operation.
Its first layer accepts a list of predicates.
Its second layer accepts a transformation and returns a function.

When invoked, the function transforms its arguments that satisfy all the predicates with the transformations via a process similar to pack expansion. Then it instantiates the operation with the result.

<pre><code>   Oper
-> Preds...
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? Transf&lt;Arg<sub>0</sub>&gt; : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? Transf&lt;Arg<sub>1</sub>&gt; : Arg<sub>1</sub>,
                                &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? Transf&lt;Arg<sub>n</sub>&gt; : Arg<sub>n</sub>
   ></code></pre>

<pre><code>   Oper
-> Preds...
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? Transf<sub>0</sub>&lt;Arg<sub>0</sub>&gt; : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? Transf<sub>1</sub>&lt;Arg<sub>1</sub>&gt; : Arg<sub>1</sub>,
                                &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? Transf<sub>n</sub>&lt;Arg<sub>n</sub>&gt; : Arg<sub>n</sub>
   ></code></pre>


<pre><code>   Oper
-> Preds...
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg
-> Oper
   <
       (...&&Preds&lt;Arg&gt;::value) ? Transf<sub>0</sub>&lt;Arg&gt; : Arg,
       (...&&Preds&lt;Arg&gt;::value) ? Transf<sub>1</sub>&lt;Arg&gt; : Arg,
                                &vellip;
       (...&&Preds&lt;Arg&gt;::value) ? Transf<sub>n</sub>&lt;Arg&gt; : Arg
   ></code></pre>


## Type Signature

```Haskell
CognateTransform
 :: template<auto...> class...
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
        template<template<auto...> class...>
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
/**** DivisibleByTwo ****/
template<auto I>
struct DivisibleByTwo
{
    static constexpr bool value
    {I % 2 == 0};
};

/**** DivisibleByThree ****/
template<auto I>
struct DivisibleByThree
{
    static constexpr bool value
    {I % 3 == 0};
};

/**** UnaryMinus ****/
template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateTransform<Operation>
::Rail<DivisibleByTwo, DivisibleByThree>
::Rail<UnaryMinus>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<1, -12, 2, -6, 15>;

/**** Result ****/
using Result = Metafunction<1, 12, 2, 6, 15>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

For convenience, we consider only the case where a single transformation is provided. For every element in the list, we supply it to the transformation if it satisfies all the predicates.

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
    // `Hormone` is the transformation.
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

                // `Puberty...` are the predicates.
                // This partial specialization will be selected
                // if `(...&&Puberty<Variable>::value) == true`.
                template<auto Variable>
                requires (...&&Puberty<Variable>::value)
                struct Hidden<Variable>
                {
                    // `Hormone` is the transformation.
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

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_transform/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/cognate_transform.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_transform.test.hpp)
