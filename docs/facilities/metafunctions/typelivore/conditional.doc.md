<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Conditional`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-conditional">To Index</a></p>

## Description

`Typelivore::Conditional` accepts two elements and returns several functions.
Check out **Examples** for more details.
Overall, `Conditional` yields one of the two elements according to the boolean evaluation of a condition.

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
 :: typename...
 -> template<auto...>
```

```Haskell
Conditional
 :: typename...
 -> template<typename...>
```

```Haskell
Conditional
 :: typename... 
 -> template<typename...> class...
 -> template<typename...>
```

```Haskell
Conditional
 :: typename... 
 -> template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<typename, typename>
struct Conditional
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

We will see four examples that present different use cases of `Typelivore::Conditional`:

```C++
/**** Choices ****/
struct IfTrue;
struct IfFalse;

/**** Select ****/
using Select = Conditional<IfTrue, IfFalse>;
```

- The template member `Page` of `Select` is a function that returns `IfTrue` if all arguments can be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as<Select::Page<1, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 2>, IfFalse>);
```

- The template member `Mold` of `Select` is a function that returns `IfTrue` if the value results of the arguments can all be evaluated as `true`.
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
    IfFalse
>);
```

- `Select::Road` accepts a list of predicates and returns a function.
When invoked, the function returns `IfTrue` if the argument list satisfies all of the predicates;
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
static_assert(std::same_as<Metafunction<int>, IfFalse>);
static_assert(std::same_as<Metafunction<void>, IfFalse>);
static_assert(std::same_as<Metafunction<VoidInt>, IfTrue>);
static_assert(std::same_as<Select::Road<>::Mold<>, IfTrue>);
```

- `Select::Rail` accepts a list of predicates and returns a function.
When invoked, the function returns `IfTrue` if the argument list satisfies all of the predicates;
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
static_assert(std::same_as<Metafunction_1<-1>, IfFalse>);
static_assert(std::same_as<Metafunction_1<1>, IfFalse>);
static_assert(std::same_as<Metafunction_1<0>, IfTrue>);
static_assert(std::same_as<Select::Rail<>::Page<>, IfTrue>);
```

## Implementation

The implementation is straightforward.

```C++
template<typename IfTrue, typename IfFalse>
struct Conditional
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
    using Page = Detail<(...&&static_cast<bool>(Agreements))>::type;

    /**** Mold ****/
    template<typename...Elements>
    using Mold = Detail<(...&&static_cast<bool>(Elements::value))>::type;

    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...Elements>
        using Mold = Detail<(...&&static_cast<bool>(Predicates<Elements...>::value))>::type;
    };

    /**** Road ****/
    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;

    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Detail<(...&&static_cast<bool>(Predicates<Variables...>::value))>::type;
    };
    
    /**** Rail ****/
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/conditional/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/conditional.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/conditional.test.hpp)
