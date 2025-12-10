<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::LeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-left-interview">To Index</a></p>

## Description

`Pagelivore::LeftInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.

When invoked, the function first binds the variables to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

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
LeftInterview
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct LeftInterview
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
using Metafunction = LeftInterview<Equal>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::Page<0, 0, 1, 2, 2>::value == 3);
static_assert
(Metafunction<-1>::Page<0, 0, 1, 2, 2>::value == -1);
```

- We will find the first index of the value which is greater than `1` in the list `0, 0, 1, 2, 2`.

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
using Metafunction_2 = LeftInterview<Less>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction_2<1>::Page<0, 0, 1, 2, 2>::value == 3);
```

## Implementation

`Pagelivore::LeftInterview` is implemented based on `Varybivore::SensibleLeftInterview`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct LeftInterview
{
    template<auto...Interviewers>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Varybivore::SensibleLeftInterview<Variables...>
        ::template ProtoRail<Predicates...>
        ::template ProtoPage<Interviewers...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/left_interview.test.hpp)
