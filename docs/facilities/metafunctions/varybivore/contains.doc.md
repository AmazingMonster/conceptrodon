<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Contains`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-contains">To Index</a></p>

## Description

`Varybivore::Contains` accepts a list of variables and returns a predicate.

When invoked by an argument, the predicate returns true if the argument is in the previously provided list and returns false if otherwise.

<pre><code>   Vs...
-> Arg
-> Arg &in; Vs... ?
   true : false</code></pre>

## Type Signature

```Haskell
Contains
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Contains
{
    template<auto>
    alias Page = RESULT;

    template<auto>
    static constexpr bool Page_v = RESULT;
};
```

## Examples

We will check whether `1` or `-1`  is inside `0, 1, 2, 2`.

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction = Contains<0, 1, 2, 2>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1>::value);
static_assert(! Metafunction<-1>::value);
```

## Implementation

`Varybivore::Contains` uses `Varybivore::IsSame` to compare variables and a fold expression to combine results.

Here's the entire implementation:

```C++
template<auto...Variables>
struct Contains
{
    template<auto Inspecting>
    struct ProtoPage
    {   
        static constexpr bool value 
        {(...||(IsSame<Variables, Inspecting>::value))};
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/contains/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/contains.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/contains.test.hpp)
