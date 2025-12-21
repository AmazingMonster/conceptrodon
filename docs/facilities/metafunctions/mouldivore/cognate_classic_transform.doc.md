<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateClassicTransform`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-classic-transform">To Index</a></p>

## Description

`Mouldivore::CognateClassicTransform` accepts an operation.
Its first layer accepts a list of predicates.
Its second layer accepts a list of transformations and returns a function.

When invoked, the function transforms its arguments that satisfy all the predicates with the transformations via a process similar to pack expansion. Then it instantiates the operation with the result.

<pre><code>   Oper
-> Preds...
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? Transf&lt;Arg<sub>0</sub>&gt;::type : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? Transf&lt;Arg<sub>1</sub>&gt;::type : Arg<sub>1</sub>,
                                    &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? Transf&lt;Arg<sub>n</sub>&gt;::type : Arg<sub>n</sub>
   ></code></pre>

<pre><code>   Oper
-> Preds...
-> Transfs<sub>0</sub>, Transfs<sub>1</sub>, ..., Transfs<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? Transf<sub>0</sub>&lt;Arg<sub>0</sub>&gt;::type : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? Transf<sub>1</sub>&lt;Arg<sub>1</sub>&gt;::type : Arg<sub>1</sub>,
                                    &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? Transf<sub>n</sub>&lt;Arg<sub>n</sub>&gt;::type : Arg<sub>n</sub>
   ></code></pre>

<pre><code>   Oper
-> Preds...
-> Transfs<sub>0</sub>, Transfs<sub>1</sub>, ..., Transfs<sub>n</sub>
-> Arg
-> Oper
   <
       (...&&Preds&lt;Arg&gt;::value) ? Transf<sub>0</sub>&lt;Arg&gt;::type : Arg,
       (...&&Preds&lt;Arg&gt;::value) ? Transf<sub>1</sub>&lt;Arg&gt;::type : Arg,
                                    &vellip;
       (...&&Preds&lt;Arg&gt;::value) ? Transf<sub>n</sub>&lt;Arg&gt;::type : Arg
   ></code></pre>

## Type Signature

```Haskell
CognateClassicTransform
 :: template<typename...> class...
 -> template<typename...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateClassicTransform
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class...>
        alias Road
        {
            template<typename...>
            alias Mold = RESULT;
        };
    };
};
```

## Example

We will apply `UnaryMinus` to elements whose value results are divisible by two and three in the list `Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** DivisibleByTwo ****/
template<typename Val>
struct DivisibleByTwo
{
    static constexpr bool value
    {Val::value % 2 == 0};
};

/**** DivisibleByThree ****/
template<typename Val>
struct DivisibleByThree
{
    static constexpr bool value
    {Val::value % 3 == 0};
};

/**** UnaryMinus ****/
template<typename Val>
struct UnaryMinus
{
    using type = Vay<-Val::value>;
};

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateClassicTransform<Operation>
::Road<DivisibleByTwo, DivisibleByThree>
::Road<UnaryMinus>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation
<Vay<1>, Vay<-12>, Vay<2>, Vay<-6>, Vay<15>>;

/**** Result ****/
using Result = Metafunction
<Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

For convenience, we consider only the case where a single transformation is provided. For every element in the list, we supply it to the transformation if it satisfies all the predicates.

We will do this using the following helper template.
It decides whether an element shall be transformed.
The selection is done by a partial specialization, which is specialized by a constraint.

```C++
template<typename Element>
struct Hidden 
{
    using type = Element;
};
// `Puberty...` are the predicates.
// This partial specialization will be selected
// if `(...&&Puberty<Element>::value) == true`.
template<typename Element>
requires (...&&Puberty<Element>::value)
struct Hidden<Element>
{
    // `Hormone` is the transformation.
    using type = Hormone<Element>::type;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct CognateClassicTransform
{
    template<template<typename...> class...Puberty>
    struct ProtoRoad
    {
        struct Slash
        {
            template<template<typename...> class Hormone>
            struct ProtoRoad
            {
                template<typename Element>
                struct Hidden 
                {
                    using type = Element;
                };

                template<typename Element>
                requires (...&&Puberty<Element>::value)
                struct Hidden<Element>
                {
                    // `Hormone` is the transformation.
                    using type = Hormone<Element>::type;
                };

                template<typename...Elements>
                using Mold = Operation<typename Hidden<Elements>::type...>;
            };
        };

        template<template<typename...> class...Agreements>
        using Road = Slash::template ProtoRoad<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_classic_transform/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/cognate_classic_transform.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_classic_transform.test.hpp)
