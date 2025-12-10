<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::TerseIndependentLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-terse-independent-left-interview">To Index</a></p>

## Description

`Pagelivore::TerseIndependentLeftInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.

When invoked, the function first binds the variables to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

`Pagelivore::TerseIndependentLeftInterview` prepares fewer base cases than `Pagelivore::IndependentLeftInterview`.

<pre><code>   Preds...
-> Vs...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Vs..., Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Vs..., Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Vs..., Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
TerseIndependentLeftInterview
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct TerseIndependentLeftInterview
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Page_v {RESULT};
    };  
};
```

## Examples

- We will find the indices of `2` and `-1` in the list `0, 0, 1, 2, 2`.

```C++
/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = TerseIndependentLeftInterview<Equal>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::Page<0, 0, 1, 2, 2>::value == 3);
static_assert
(Metafunction<-1>::Page<0, 0, 1, 2, 2>::value == -1);
```

- We will find the first index of the value which is less than `1` in the list `0, 0, 1, 2, 2`.

```C++
/**** Less ****/
template<auto I, auto J>
struct Less
{
    static constexpr bool value
    {I < J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction_2 = TerseIndependentLeftInterview<Less>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction_2<1>::Page<0, 0, 1, 2, 2>::value == 3);
```

## Implementation

We will implement `TerseIndependentLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct TerseIndependentLeftInterview
{
    template<auto...LeftSides>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...>
            struct ProtoPage
            { static constexpr auto value {-1}; };

            template<auto First>
            struct ProtoPage<First>
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

            template<auto First, auto Second, auto...Others>
            struct ProtoPage<First, Second, Others...>
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
                            ProtoPage<Others...>
                            ::value != -1
                        )
                        { 
                            return 2 + ProtoPage<Others...>
                            ::value; 
                        }

                        else
                        { return -1; }
                    }()
                };
            };
        };
        
        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/terse_independent_left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/terse_independent_left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/terse_independent_left_interview.test.hpp)
