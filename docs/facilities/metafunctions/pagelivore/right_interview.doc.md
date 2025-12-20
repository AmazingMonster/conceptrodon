<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::RightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-right-interview">To Index</a></p>

## Description

`Pagelivore::RightInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.

When invoked, the function first binds the variables to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Vs...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>, Vs...&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>, Vs...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>, Vs...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
RightInterview
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct RightInterview
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
using Metafunction = RightInterview<Equal>
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
using Metafunction_1 = RightInterview<Less>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction_1<1>::Page<0, 0, 1, 2, 2>::value == 0);
```

## Implementation

`Pagelivore::RightInterview` is implemented based on `Varybivore::SensibleRightInterview`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct RightInterview
{
    template<auto...Interviewers>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Varybivore::SensibleRightInterview<Variables...>
        ::template ProtoRail<Predicates...>
        ::template ProtoPage<Interviewers...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/right_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/right_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/right_interview.test.hpp)
