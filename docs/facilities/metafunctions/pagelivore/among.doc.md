<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Among`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-among">To Index</a></p>

## Description

`Pagelivore::Among` accepts a list of sequences. Its first layer accepts an index and returns a function.
When invoked, the function instantiates the sequence at the index from the list with its arguments and returns the result.

<pre><code>   Seq<sub>0</sub>, Seq<sub>1</sub>, ..., Seq<sub>I</sub>, ..., Seq<sub>n</sub>
-> I
-> Vs...
-> Seq<sub>I</sub>&lt;Vs...&gt;</code></pre>

## Type Signature

```Haskell
Among
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class...>
struct Among
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will pick the sequence at index `3` out of the list `Seq_0, Seq_1, Seq_2, Seq_3`.

```C++
/**** Sequences ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** Metafunction ****/
template<auto...Args>
using Metafunction
= Among<Seq_0, Seq_1, Seq_2, Seq_3>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Seq_3<0, 1, 2>;

/**** Result ****/
using Result = Metafunction<3>::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

Note that we must instantiate the sequence before the comparison.
This is because the function returned by `Among` is an alias template pointing to the actual sequence in the list.
It is not quite the same as the actual sequence.

```C++
/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** First Test ****/
// If the following assertion passes
// , then `Metafunction` and `Seq_3` are considered the same.
static_assert(std::same_as<
    Carrier<Metafunction<3>:: Page>,
    Carrier<Seq_3>
>);

/**** Second Test ****/
// If the following assertion passes
// , then `Metafunction` and `Seq_3` are considered different.
// Some compilers might fail on both assertions.
static_assert(not std::same_as<
    Carrier<Metafunction<3>:: Page>,
    Carrier<Seq_3>
>);
```

However, after instantiation, both of them will converge to the same result.

## Implementation

We will implement `Among` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the sequence at the index is returned. Otherwise:
  1. Drop several sequences from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `Among` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<template<auto...> class...Sequences>
struct Among {};

template<template<auto...> class First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = First<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<auto...> class First,
    template<auto...> class Second,
    template<auto...> class...Others
>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    {
        template<auto...Agreements>
        using Page = Among<Others...>
        ::template ProtoPage<I - 2>
        ::template Page<Agreements...>;
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = First<Agreements...>;
    };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = Second<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/among/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/among.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/among.test.hpp)
