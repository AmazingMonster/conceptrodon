<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Among`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-among">To Index</a></p>

## Description

`Mouldivore::Among` accepts a list of containers. Its first layer accepts an index and returns a function.

When invoked, the function fills the container at the index with its arguments and returns the result.

<pre><code>   Con<sub>0</sub>, Con<sub>1</sub>, ..., Con<sub>I</sub>, ..., Con<sub>n</sub>
-> I
-> Es...
-> Con<sub>I</sub>&lt;Es...&gt;</code></pre>

## Type Signature

```Haskell
Among
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class...>
struct Among
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will pick the container at index `3` out of the list `Con_0, Con_1, Con_2, Con_3`.

```C++
/*** Dummy Containers ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** Metafunction ****/
template<auto...Args>
using Metafunction
= Among<Con_0, Con_1, Con_2, Con_3>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Con_3<int, int*, int**>;

/**** Result ****/
using Result = Metafunction<3>::Mold<int, int*, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

Note that we must fill the containers before the comparison.
This is because the function returned by `Among` is an alias template pointing to the actual container in the list.
It is not quite the same as the actual container. However, different compilers may have varied opinions.

```C++
/**** Vehicle ****/
template<template<typename...> class...>
struct Vehicle;

/**** First Test ****/
// If the following assertion passes
// , then `Metafunction<3>::Mold` and `Con_3` are considered the same.
static_assert(std::same_as<
    Vehicle<Metafunction<3>::Mold>,
    Vehicle<Con_3>
>);

/**** Second Test ****/
// If the following assertion passes
// , then `Metafunction<3>::Mold` and `Con_3` are considered different.
// Some compilers might fail on both assertions.
static_assert(not std::same_as<
    Vehicle<Metafunction<3>::Mold>,
    Vehicle<Con_3>
>);
```

However, after instantiation, both of them will converge to the same result.

## Implementation

We will implement `Among` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the container at the index is returned. Otherwise:
  1. Drop several containers from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `Among` by the rest of the list and its first layer by the reduced index.

A simplified version will be as follows:

```C++
template<template<typename...> class...Containers>
struct Among {};

/**** Base Step ****/
template<template<typename...> class First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<typename...Agreements>
        using Mold = First<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/**** Recursive Step ****/
template
<
    template<typename...> class First,
    template<typename...> class Second,
    template<typename...> class...Others
>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    {
        template<typename...Agreements>
        using Mold = Among<Others...>
        ::template ProtoPage<I - 2>
        ::template Mold<Agreements...>;
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<typename...Agreements>
        using Mold = First<Agreements...>;
    };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    {
        template<typename...Agreements>
        using Mold = Second<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/among/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/among.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/among.test.hpp)
