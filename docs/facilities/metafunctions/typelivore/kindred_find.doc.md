<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredFind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-find">To Index</a></p>

## Description

`Typelivore::KindredFind` accepts a list of elements and returns a function.

When invoked by predicates, the function returns the index of the first element that satisfies all predicates, or `-1` if it cannot find the element.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Preds...
-> (...&&Preds&lt;E<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;E<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;E<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredFind
 :: typename...
 -> template<typename...> class...
 -> auto
```

## Structure

```C++
template<typename...>
struct KindredFind
{
    template<template<typename...> class...>
    alias Road = RESULT;

    template<template<typename...> class...>
    static constexpr std::make_signed_t<size_t>
    Road_v {RESULT};
};
```

## Examples

We will find the indices of `int**` and `void` in list `int，int*，int**，int***`.

```C++
/**** IsIntDoubleStar ****/
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

/**** IsVoid ****/
template<typename Element>
struct IsVoid
: public std::is_same<Element, void> {};

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = KindredFind<int, int*, int**, int**>
::Road<Args...>;

/**** Tests ****/
static_assert(Metafunction<IsIntDoubleStar>::value == 2);
static_assert(Metafunction<IsVoid>::value == -1);
```

## Implementation

We will implement `KindredFind` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct KindredFind
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    { static constexpr auto value {-1}; };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First>
struct KindredFind<First>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First, typename Second, typename...Others>
struct KindredFind<First, Second, Others...>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    KindredFind<Others...>
                    ::template ProtoRoad<Predicates...>
                    ::value != -1
                )
                { 
                    return 2 + KindredFind<Others...>
                    ::template ProtoRoad<Predicates...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/kindred_find/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/kindred_find.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/kindred_find.test.hpp)
