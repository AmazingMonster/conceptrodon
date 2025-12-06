<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::LeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-left-interview">To Index</a></p>

## Description

`Mouldivore::LeftInterview` accepts a list of predicates.
Its first layer accepts a list of elements and returns a function.

When invoked, the function first binds the elements to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Es...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Es..., Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Es..., Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Es..., Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
LeftInterview
 :: template<typename...> class...
 -> typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct LeftInterview
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

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
/****  Metafunction ****/
template<typename...Args>
using Metafunction = LeftInterview<std::is_same>
::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction<int**>::Mold<int, int*, int**, int**>::value == 2);
static_assert
(Metafunction<void>::Mold<int, int*, int**, int**>::value == -1);
```

## Implementation

`Mouldivore::LeftInterview` is implemented based on `Typelivore::SensibleLeftInterview`. It changes the invocation order of the latter.

```C++
template<template<typename...> class...Predicates>
struct LeftInterview
{
    template<typename...Interviewers>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Typelivore::SensibleLeftInterview<Elements...>
        ::template ProtoRoad<Predicates...>
        ::template ProtoMold<Interviewers...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/left_interview.test.hpp)
