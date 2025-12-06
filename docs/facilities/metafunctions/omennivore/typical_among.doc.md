<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::TypicalAmong`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-typical-among">To Index</a></p>

## Description

`Omennivore::TypicalAmong` accepts a packed vessel.

- Suppose the vessel is a container containing elements. In that case, It returns a function. When invoked by an index, the function returns the element at the index via the member `type`.

<pre><code>   Container&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>&gt;
-> I
-> E<sub>I</sub></code></pre>

- Suppose the vessel is a sequence containing variables. In that case, It returns a function. When invoked by an index, the function returns the variable at the index via the member `value`.

<pre><code>   Seq&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>&gt;
-> I
-> V<sub>I</sub></code></pre>

- Suppose the vessel contains operations. In that case, its first layer accepts an index and returns a function. When invoked, the function instantiates the operation at the index with its arguments and returns the result.

<pre><code>   Vessel&lt;Oper<sub>0</sub>, Oper<sub>1</sub>, ..., Oper<sub>I</sub>, ..., Oper<sub>n</sub>&gt;
-> I
-> Args...
-> Oper<sub>I</sub>&lt;Args...&gt;</code></pre>

## Type Signature

```Haskell
-- Pick a `type`
TypicalAmong
 :: typename...
 -> auto...
 -> typename
 
-- Pick a `value`
TypicalAmong
 :: auto...
 -> auto...
 -> auto
 
-- Pick a `Mold`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
 
-- Pick a `Page`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<auto...>
 
-- Pick a `Road`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<typename...> class...>
 
-- Pick a `Rail`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<auto...> class...>
 
-- Pick a `Flow`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<typename...> class...> class...>
 
-- Pick a `Sail`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<auto...> class...> class...>
 
-- Pick a `Snow`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<typename...> class...> class...> class...>
 
-- Pick a `Hail`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<auto...> class...> class...> class...>
 
-- Pick a `Cool`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>
 
-- Pick a `Calm`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>
 
-- Pick a `Grit`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
 
-- Pick a `Will`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
 
-- Pick a `Glow`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
 
-- Pick a `Dawn`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
// Pick a `type`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        using type = RESULT;
    };
};

// Pick a `value`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        static constexpr auto value {RESULT};
    };
};

// Pick a `Mold`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};

// Pick a `Page`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};

// Pick a `Road`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};

// Pick a `Rail`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};

// Pick a `Flow`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<typename...> class...> class...>
        alias Flow = RESULT;
    };
};

// Pick a `Sail`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<auto...> class...> class...>
        alias Sail = RESULT;
    };
};

// Pick a `Snow`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<typename...> class...> class...> class...>
        alias Snow = RESULT;
    };
};

// Pick a `Hail`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<auto...> class...> class...> class...>
        alias Hail = RESULT;
    };
};

// Pick a `Cool`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<typename...> class...> class...> class...> class...>
        alias Cool = RESULT;
    };
};

// Pick a `Calm`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<auto...> class...> class...> class...> class...>
        alias Calm = RESULT;
    };
};

// Pick a `Grit`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
        alias Grit = RESULT;
    };
};

// Pick a `Will`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
        alias Will = RESULT;
    };
};

// Pick a `Glow`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
        alias Glow = RESULT;
    };
};

// Pick a `Dawn`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
        alias Dawn = RESULT;
    };
};
```

## Examples

- We will pick out the element at index two from `std::tuple<int, int*, int**, int***>`.

```C++
/**** At ****/
template<auto...Args>
using At = TypicalAmong<std::tuple<int, int*, int**, int***>>
::Page<Args...>
::type;

/**** SupposedResult ****/
using SupposedResult = int**;

/**** Result ****/
using Result = At<2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will pick out the operation at index two from `Vessel<War_0, War_1, War_2, War_3>`.

```C++
/**** Vessel ****/
template<template<template<template<typename...> class...> class...> class...>
struct Vessel;

/**** Dummy Arguments ****/
template<template<template<typename...> class...> class...>
struct Flow_0;

template<template<template<typename...> class...> class...>
struct Flow_1;

template<template<template<typename...> class...> class...>
struct Flow_2;

template<template<template<typename...> class...> class...>
struct Flow_3;

/**** Metafunction ****/
template<template<template<typename...> class...> class...Args>
using Metafunction = TypicalAmong<Vessel<Flow_0, Flow_1, Flow_2, Flow_3>>
::Page<2>
::Flow<Args...>;

/**** Dummy Arguments ****/
template<template<typename...> class...>
struct Ware_0;

template<template<typename...> class...>
struct Ware_1;

/**** Test ****/
static_assert(std::same_as<Flow_2<Ware_0, Ware_1>, Metafunction<Ware_0, Ware_1>>);
```

Note that we must instantiate the operation before the comparison.
This is because the function returned by `TypicalAmong` is an alias template pointing to the actual operation in the packed vessel.
It is not quite the same as the actual operation.

```C++
/**** Forlorn ****/
template<template<template<template<typename...> class...> class...> class...>
struct Forlorn;

/**** Tests ****/
// GCC compiles.
// Clang and MSVC fail.
static_assert(std::same_as<
    Forlorn<Metafunction>,
    Forlorn<Flow_2>
>);

// Clang and MSVC compile.
// GCC fails.
static_assert(not std::same_as<
    Forlorn<Metafunction>,
    Forlorn<Flow_2>
>);
```

## Implementation

If `TypicalAmong` or `Among` have been implemented in other namespaces, we will redirect the items extracted from the packed vessel to these functions.

Otherwise, we will transform the items into types and employ `Typelivore::TypicalAmong` to do the job.

We will implement a simplified version that picks out types and `Flow`s. Since `Typelivore::TypicalAmong` exists, we will use it to deal with types.

```C++
template<typename>
struct TypicalAmong {};

template<template<typename...> class Container, typename...Elements>
struct TypicalAmong<Container<Elements...>>
: public Typelivore::TypicalAmong<Elements...>
{};
```

To pick out `Flow`s with `Typelivore::TypicalAmong`, we will wrap every `Flow` into a `Florican`.

```C++
template<template<template<template<typename...> class...> class...> class Sorrow>
struct Florican
{
    template<template<template<typename...> class...> class...Warehouses>
    using Flow = Sorrow<Warehouses...>;
};
```

Here's the implementation to pick out an `Element` or a `Flow`.

```C++
template<typename>
struct TypicalAmong {};

template<template<typename...> class Container, typename...Elements>
struct TypicalAmong<Container<Elements...>>
: public Typelivore::TypicalAmong<Elements...>
{};

template
<
    template<template<template<template<typename...> class...> class...> class...> class Vessel,
    // Extract items from a packed vessel.
    template<template<template<typename...> class...> class...> class...Flows
>
struct TypicalAmong<Vessel<Flows...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<typename...> class...> class...Arguments>
        // We warp each of `Flows...` into `Florican`
        // and invoke `Typelivore::TypicalAmong`. 
        using Flow = Typelivore::TypicalAmong<Florican<Flows>...>
        ::template Page<I>
        // The `type` we obtained is an instantiated `Florican`.
        ::type
        // We call the template member `Flow` with the arguments.
        ::template Flow<Arguments...>;
    };

    template<auto...Arguments>
    using Page = ProtoPage<Arguments...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/typical_among/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/among.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/typical_among.type.test.hpp)
