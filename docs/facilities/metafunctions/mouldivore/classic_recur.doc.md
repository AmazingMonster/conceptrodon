<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicRecur`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-classic-recur">To Index</a></p>

## Description

`Mouldivore::ClassicRecur` accepts an operation.
Its first layer accepts a list of predicates and returns a function.

When invoked, the function instantiates the operation with its arguments and uses the type result to call the operation repeatedly until the type result satisfies all the predicates.

<pre><code>   Oper
-> Preds...
-> Args...
-> (...&&Preds&lt;Oper&lt;Args...&gt;::type&gt;::value) ? Oper&lt;Args...&gt; : (
   (...&&Preds&lt;Oper&lt;Oper&lt;Args...&gt;::type&gt;::type&gt;::value) ? Oper&lt;Oper&lt;Args...&gt;::type&gt; : (
   (...&&Preds&lt;Oper&lt;Oper&lt;Oper&lt;Args...&gt;::type&gt;::type&gt;::type&gt;::value) ? Oper&lt;Oper&lt;Oper&lt;Args...&gt;::type&gt;::type&gt; : (
            &vellip;
   )))</code></pre>

## Type Signature

```Haskell
ClassicRecur
 :: template<typename...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct ClassicRecur
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
struct AddOne
{
    using type = Vay<Val::value + 1>;
};

/**** IsGreaterThanNine ****/
template<typename Val>
struct IsGreaterThanNine
{
    static constexpr auto value
    {Val::value > 9};
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ClassicRecur<AddOne>
::Road<IsGreaterThanNine>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Vay<10>;

/**** Results ****/
using Result_0 = Metafunction<Vay<0>>::type;
using Result_1 = Metafunction<Vay<-1>>::type;

/**** Tests ****/
static_assert(std::same_as<Result_0, SupposedResult>);
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

We will implement `ClassicRecur` using a helper regular function, which utilizes `constexpr if` statements to decide whether the recursion should continue.

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
            typename History<
                Sacrifices...
            >::type
        >::value)
    )
    {
        return std::type_identity<History<
                Sacrifices...
        >>{};
    }
    
    else if constexpr 
    (
        (...&&LessonsLearned<
            typename History<
            typename History<
                Sacrifices...
            >::type
            >::type
        >::value)
    )
    {
        return std::type_identity<History<
            typename History<
                Sacrifices...
            >::type
        >>{};
    }
    else
    {
        return idyl<
            typename History<
            typename History<
                Sacrifices...
            >::type
            >::type
        >();
    }
}
```

Note that we wrap around each result inside a `std::type_identity`.
This is to avoid creating an object of an instantiation of the operation, as it might be impossible.

We return the final operation itself instead of its type result.
This is because the type result that we are testing might be an indicator to signal the end of the recursion, and the actual output could be a different member of the final operation.

Here is the entire implementation.

```C++
template<template<typename...> class History>
struct ClassicRecur
{
    template<template<typename...> class...LessonsLearned>
    struct ProtoRoad
    {
        // `Sacrifices` are the arguments that will initiate `Operation`.
        template<typename...Sacrifices>
        static consteval auto idyl()
        {
            if constexpr 
            (
                // `LessonsLearned...` are the predicates.
                (...&&LessonsLearned<
                    // `History` is the operation that will recur.
                    typename History<
                        Sacrifices...
                    >::type
                >::value)
            )
            {
                return std::type_identity<History<
                        Sacrifices...
                >>{};
            }
            
            else if constexpr 
            (
                (...&&LessonsLearned<
                    typename History<
                    typename History<
                        Sacrifices...
                    >::type
                    >::type
                >::value)
            )
            {
                return std::type_identity<History<
                    typename History<
                        Sacrifices...
                    >::type
                >>{};
            }

            else
            {
                return idyl<
                    typename History<
                    typename History<
                        Sacrifices...
                    >::type
                    >::type
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

- [Example](../../../code/facilities/metafunctions/mouldivore/classic_recur/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/classic_recur.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/classic_recur.test.hpp)
