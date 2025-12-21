<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyConditional`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-any-conditional">To Index</a></p>

## Description

`Typelivore::AnyConditional` accepts two elements and returns several functions.
Check out **Examples** for more details.
Overall, `AnyConditional` yields one of the two elements according to the boolean evaluation of a condition.

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg::value ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Preds...
-> Args...
-> (...||Preds&lt;Args...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
AnyConditional
 :: typename...
 -> template<auto...>
```

```Haskell
AnyConditional
 :: typename...
 -> template<typename...>
```

```Haskell
AnyConditional
 :: typename... 
 -> template<typename...> class...
 -> template<typename...>
```

```Haskell
AnyConditional
 :: typename... 
 -> template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<typename, typename>
struct AnyConditional
{
    template<auto...>
    alias Page = RESULT;

    template<typename...>
    alias Mold = RESULT;

    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };

    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will see four examples that present different use cases of `Typelivore::AnyConditional`:

```C++
/**** Choices ****/
struct IfTrue;
struct IfFalse;

/**** Select ****/
using Select = AnyConditional<IfTrue, IfFalse>;
```

- The template member `Page` of `Select` is a function that returns `IfTrue` if any of its arguments can be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as<Select::Page<1, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 0>, IfFalse>);
```

- The template member `Mold` of `Select` is a function that returns `IfTrue` if the value result of any of its arguments can be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 0>
    >, 
    IfFalse
>);
```

- `Select::Road` accepts a list of predicates and returns a function.
When invoked, the function returns `IfTrue` if the argument list satisfies any of the predicates;
otherwise, the function returns `IfFalse`.

```C++
/**** VoidInt ****/
struct VoidInt;

/**** Void Tester ****/
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
static_assert(std::same_as<Metafunction<int>, IfTrue>);
static_assert(std::same_as<Metafunction<void>, IfTrue>);
static_assert(std::same_as<Metafunction<VoidInt>, IfTrue>);
static_assert(std::same_as<Metafunction<double>, IfFalse>);
static_assert(std::same_as<Select::Road<>::Mold<>, IfFalse>);
```

- `Select::Rail` accepts a list of predicates and returns a function.
When invoked, the function returns `IfTrue` if the argument list satisfies any of the predicates;
otherwise, the function returns `IfFalse`.

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
static_assert(std::same_as<Metafunction_1<1>, IfTrue>);
static_assert(std::same_as<Metafunction_1<-1>, IfTrue>);
static_assert(std::same_as<Metafunction_1<0>, IfTrue>);
static_assert(std::same_as<Metafunction_1<nullptr>, IfFalse>);
static_assert(std::same_as<Select::Rail<>::Page<>, IfFalse>);
```

## Implementation

The implementation is straightforward.

```C++
template<typename IfTrue, typename IfFalse>
struct AnyConditional
{
    template<auto>
    struct Detail {};

    template<auto I>
    requires I
    struct Detail<I>
    { using type = IfTrue; };

    template<auto I>
    requires (!I)
    struct Detail<I>
    { using type = IfFalse; };

    /**** Page ****/
    template<auto...Agreements>
    using Page = Detail<(...||static_cast<bool>(Agreements))>::type;

    /**** Mold ****/
    template<typename...Elements>
    using Mold = Detail<(...||static_cast<bool>(Elements::value))>::type;

    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...Elements>
        using Mold = Detail<(...||static_cast<bool>(Predicates<Elements...>::value))>::type;
    };

    /**** Road ****/
    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
    
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Detail<(...||static_cast<bool>(Predicates<Variables...>::value))>::type;
    };
    
    /**** Rail ****/
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/any_conditional/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/any_conditional.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/any_conditional.test.hpp)
