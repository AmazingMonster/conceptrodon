<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Conditional`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-conditional">To Index</a></p>

## Description

`Varybivore::Conditional` accepts two variables and returns several functions.
Check out **Examples** for more details.
Overall, `Conditional` yields one of the two variables according to the boolean evaluation of a condition.

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg::value ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Preds...
-> Args...
-> (...&&Preds&lt;Args...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
Conditional
 :: auto...
 -> auto...
 -> auto
```

```Haskell
Conditional
 :: auto...
 -> typename...
 -> auto
```

```Haskell
Conditional
 :: auto... 
 -> template<typename...> class...
 -> typename...
 -> auto
```

```Haskell
Conditional
 :: auto... 
 -> template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct Conditional
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };

    template<typename...>
    alias Mold
    {
        static constexpr auto value
        {RESULT};
    };

    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold
        {
            static constexpr auto value
            {RESULT};
        };
    };

    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page
        {
            static constexpr auto value
            {RESULT};
        };
    };
};
```

## Examples

We will see four examples that present different use cases of `Varybivore::Conditional`:

```C++
using Select = Conditional<1, 0>;
```

- The template member `Page` of `Select` is a function that returns `1` if all arguments can be evaluated as `true`.
Otherwise, it returns `0`.

```C++
static_assert(Select::Page<1, 2>::value == 1);
static_assert(Select::Page<0, 2>::value == 0);
```

- The template member `Mold` of `Select` is a function that returns `1` if the value results of the arguments can all be evaluated as `true`.
Otherwise, it returns `0`.

```C++
static_assert(
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >::value == 1
);

static_assert(
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >::value == 0
);
```

- `Select::Road` accepts a list of predicates and returns a function.
When invoked, the function returns `1` if the argument list satisfies all of the predicates;
otherwise, the function returns `0`.

```C++
/**** VoidInt ****/
struct VoidInt;

/**** VoidTester ****/
template<typename...>
struct VoidTester: public std::false_type {};

template<>
struct VoidTester<void>: public std::true_type {};

template<>
struct VoidTester<VoidInt>: public std::true_type {};

/**** IntTester ****/
template<typename...>
struct IntTester: public std::false_type {};

template<>
struct IntTester<int>: public std::true_type {};

template<>
struct IntTester<VoidInt>: public std::true_type {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Select
::Road<VoidTester, IntTester>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int>::value == 0);
static_assert(Metafunction<void>::value == 0);
static_assert(Metafunction<VoidInt>::value == 1);
static_assert(Select::Road<>::Mold<>::value == 1);
```

- `Select::Rail` accepts a list of predicates and returns a function.
When invoked, the function returns `1` if the argument list satisfies all of the predicates;
otherwise, the function returns `0`.

```C++
/**** NonpositiveTester ****/
template<auto...>
struct NonpositiveTester: public std::false_type {};

template<auto I>
requires (I <= 0 )
struct NonpositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction_1 = Select
::Rail<NonpositiveTester, NonnegativeTester>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction_1<-1>::value == 0);
static_assert(Metafunction_1<1>::value == 0);
static_assert(Metafunction_1<0>::value == 1);
static_assert(Select::Rail<>::Page<>::value == 1);
```

## Implementation

The implementation is straightforward.

```C++
template<auto IfTrue, auto IfFalse>
struct Conditional
{
    template<auto>
    struct Detail {};

    template<auto I>
    requires I
    struct Detail <I>
    { static constexpr auto value {IfTrue}; };

    template<auto I>
    requires (!I)
    struct Detail <I>
    { static constexpr auto value {IfFalse}; };

    /**** Page ****/
    template<auto...Agreements>
    using Page = Detail<(...&&static_cast<bool>(Agreements))>;

    template<auto...Args>
    static constexpr auto Page_v {Detail<(...&&static_cast<bool>(Args))>::value};

    /**** Mold ****/
    template<typename...Elements>
    using Mold = Detail<(...&&static_cast<bool>(Elements::value))>;

    template<typename...Elements>
    static constexpr auto Mold_v { Detail<(...&&static_cast<bool>(Elements::value))>::value };

    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        
        template<typename...Elements>
        using Mold = Detail<(...&&static_cast<bool>(Predicates<Elements...>::value))>;

        template<typename...Elements>
        static constexpr auto Mold_v 
        { Detail<(...&&static_cast<bool>(Predicates<Elements...>::value))>::value };
    };

    /**** Road ****/
    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
    
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Detail<(...&&static_cast<bool>(Predicates<Variables...>::value))>;
            
        template<auto...Variables>
        static constexpr auto Page_v 
        { Detail<(...&&static_cast<bool>(Predicates<Variables...>::value))>::value };
    };
    
    /**** Rail ****/
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/conditional/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/conditional.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/conditional.test.hpp)
