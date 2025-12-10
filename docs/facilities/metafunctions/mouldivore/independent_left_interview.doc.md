<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::IndependentLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-independent-left-interview">To Index</a></p>

## Description

`Mouldivore::IndependentLeftInterview` accepts a list of predicates.
Its first layer accepts a list of elements and returns a function.

When invoked, the function first binds the elements to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Es...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Es..., Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Es..., Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Es..., Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
IndependentLeftInterview
 :: template<typename...> class...
 -> typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct IndependentLeftInterview
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Mold_v {RESULT};
    };  
};
```

## Examples

- We will find the indices of `Vay<2>` and `Vay<-1>` in the list `Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>`.

```C++
/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value{Variable} };

/**** Metafunction ****/
template<typename...Args>
using Metafunction = IndependentLeftInterview<std::is_same>
::Mold<Args...>;

/*** Tests ****/
static_assert
(Metafunction<Vay<2>>::Mold<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>::value == 3);
static_assert
(Metafunction<Vay<-1>>::Mold<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>::value == -1);
```

- We will find the first index of the type whose member `value` is greater than `1` in the list `Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>`.

```C++
/**** Less ****/
template<typename I, typename J>
struct Less
{
    static constexpr bool value
    {I::value < J::value};
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction_2 = IndependentLeftInterview<Less>
::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction_2<Vay<1>>::Mold<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>::value == 3);
```

## Implementation

We will implement `IndependentLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class...Predicates>
struct IndependentLeftInterview
{
    template<typename...LeftSides>
    struct ProtoMold
    {
        struct Slash
        {
            template<typename...>
            struct ProtoMold
            { static constexpr auto value {-1}; };

            template<typename First>
            struct ProtoMold<First>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else
                        { return -1; }
                    }()
                };
            };

            template<typename First, typename Second, typename...Others>
            struct ProtoMold<First, Second, Others...>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else if constexpr 
                        ((...&&Predicates<LeftSides..., Second>::value))
                        { return 1; }

                        else if constexpr
                        (
                            ProtoMold<Others...>
                            ::value != -1
                        )
                        { 
                            return 2 + ProtoMold<Others...>
                            ::value; 
                        }

                        else
                        { return -1; }
                    }()
                };
            };
        };
        
        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/independent_left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/independent_left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/independent_left_interview.test.hpp)
