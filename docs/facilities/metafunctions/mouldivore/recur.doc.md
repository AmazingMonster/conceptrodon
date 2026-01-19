<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Recur`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-recur">To Index</a></p>

## Description

`Mouldivore::Recur` accepts an operation.
Its first layer accepts a list of predicates and returns a function.

When invoked, the function instantiates the operation with its arguments and uses the result to call the operation repeatedly until the result satisfies all the predicates.

<pre><code>   Oper
-> Preds...
-> Args...
-> (...&&Preds&lt;Oper&lt;Args...&gt;&gt;::value) ? Oper&lt;Args...&gt; : (
   (...&&Preds&lt;Oper&lt;Oper&lt;Args...&gt;&gt;&gt;::value) ? Oper&lt;Oper&lt;Args...&gt;&gt; : (
   (...&&Preds&lt;Oper&lt;Oper&lt;Oper&lt;Args...&gt;&gt;&gt;&gt;::value) ? Oper&lt;Oper&lt;Oper&lt;Args...&gt;&gt;&gt; : (
            &vellip;
   )))</code></pre>

## Type Signature

```Haskell
Recur
 :: template<typename...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Recur
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will increment `0` and `-1` until they are greater than `9`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** AddOne ****/
template<typename Val>
struct AddOneHelper
{
    using type = Vay<Val::value + 1>;
};

template<typename...Args>
using AddOne  = AddOneHelper<Args...>::type;

/**** IsGreaterThanNine ****/
template<typename Val>
struct IsGreaterThanNine
{
    static constexpr auto value
    {Val::value > 9};
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Recur<AddOne>
::Road<IsGreaterThanNine>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Vay<10>;

/**** Result ****/
using Result_0 = Metafunction<Vay<0>>;
using Result_1 = Metafunction<Vay<-1>>;

/**** Tests ****/
static_assert(std::same_as<Result_0, SupposedResult>);
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

We will implement `Recur` using a helper regular function, which utilizes `constexpr if` statements to decide whether the recursion should continue.

```C++
// `Sacrifices` are the arguments that will initiate `Operation`.
template<typename...Sacrifices>
static consteval auto idyl()
{
    if constexpr 
    (
        // `LessonsLearned...` are the predicates.
        (...&&LessonsLearned<
            // `History` is the operation that will recur.
            History<
                Sacrifices...
            >
        >::value)
    )
    {
        return Tyy<History<
                Sacrifices...
        >>{};
    }
    
    else if constexpr 
    (
        (...&&LessonsLearned<
            History<
            History<
                Sacrifices...
            >
            >
        >::value)
    )
    {
        return Tyy<History<
            History<
                Sacrifices...
            >
        >>{};
    }
    else
    {
        return idyl<
            History<
            History<
                Sacrifices...
            >
            >
        >();
    }
}
```

Note that we wrap around each result inside a `Tyy`.

```C++
template<typename Element>
struct Tyy
{
    using type = Element;
};
```

This is to avoid creating an object of an instantiation of the operation, as it might be impossible.

Here is the entire implementation.

```C++
template<template<typename...> class History>
struct Recur
{
    template<template<typename...> class...LessonsLearned>
    struct ProtoRoad
    {
        template<typename...Sacrifices>
        static consteval auto idyl()
        {
            if constexpr 
            (
                // `LessonsLearned...` are the predicates.
                (...&&LessonsLearned<
                    // `History` is the operation that will recur.
                    History<
                        Sacrifices...
                    >
                >::value)
            )
            {
                return Tyy<History<
                        Sacrifices...
                >>{};
            }
            
            else if constexpr 
            (
                (...&&LessonsLearned<
                    History<
                    History<
                        Sacrifices...
                    >
                    >
                >::value)
            )
            {
                return Tyy<History<
                    History<
                        Sacrifices...
                    >
                >>{};
            }

            else
            {
                return idyl<
                    History<
                    History<
                        Sacrifices...
                    >
                    >
                >();
            }
        }

        template<typename...Sacrifices>
        using Mold = decltype(idyl<Sacrifices...>())::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/recur/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/recur.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/recur.test.hpp)
