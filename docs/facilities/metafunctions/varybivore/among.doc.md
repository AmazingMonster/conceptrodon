<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Among`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-among">To Index</a></p>

## Description

`Varybivore::Among` accepts a list of variables and returns a function.

When invoked by an index, the function returns the variable at the index from the list.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> V<sub>I</sub></code></pre>

## Type Signature

```Haskell
Among
 :: typename...
 -> auto...
 -> auto
```

## Structure

```C++
template<typename...>
struct Among
{
    template<auto>
    alias Page
    {
        static constexpr auto value 
        {RESULT};
    };

    template<auto>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will pick the variable at index `3` out of the list `0, 1, 2, 3`.

```C++
static_assert(Among<0, 1, 2, 3>::Page<3>::value == 3);
```

## Implementation

We will implement `Among` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the variable at the index is returned. Otherwise:
  1. Drop several variables from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `Among` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<auto...Variables>
struct Among {};

template<auto First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { static constexpr auto value {First}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    { 
        static constexpr auto value 
        {Among<Others...>::template ProtoPage<I - 2>::value};
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { static constexpr auto value {First}; };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    { static constexpr auto value {Second}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/among/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/among.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/among.test.hpp)
