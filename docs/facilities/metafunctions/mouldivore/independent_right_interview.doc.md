<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::IndependentRightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-independent-right-interview">To Index</a></p>

## Description

`Mouldivore::IndependentRightInterview` accepts a list of predicates.
Its first layer accepts a list of elements and returns a function.

When invoked, the function first binds the elements to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Es...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>, Es...&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>, Es...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>, Es...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
IndependentRightInterview
 :: template<typename...> class...
 -> typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct IndependentRightInterview
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;

        template<typename...>
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
{ static constexpr auto value{Variable}; };

/**** Metafunction ****/
template<typename...Args>
using Metafunction = IndependentRightInterview<std::is_same>
::Mold<Args...>;

/*** Tests ****/
static_assert
(Metafunction<Vay<2>>::Mold<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>::value == 3);
static_assert
(Metafunction<Vay<-1>>::Mold<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>::value == -1);
```

- We will find the first index of the type whose member `value` is less than `1` in the list `Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>`.

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
using Metafunction_2 = IndependentRightInterview<Less>
::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction_2<Vay<1>>::Mold<Vay<0>, Vay<0>, Vay<1>, Vay<2>, Vay<2>>::value == 0);
```

## Implementation

We will implement `IndependentRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class...Predicates>
struct IndependentRightInterview
{
    template<typename...RightSides>
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
                        ((...&&Predicates<First, RightSides...>::value))
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
                        ((...&&Predicates<First, RightSides...>::value))
                        { return 0; }

                        else if constexpr 
                        ((...&&Predicates<Second, RightSides...>::value))
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

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/independent_right_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/independent_right_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/independent_right_interview.test.hpp)
