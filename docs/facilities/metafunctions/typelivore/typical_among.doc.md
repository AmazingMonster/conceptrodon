<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalAmong`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-among">To Index</a></p>

## Description

`Typelivore::TypicalAmong` accepts a list of elements and returns a function.

When invoked by an index, the function returns the element at the index from the list.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> E<sub>I</sub></code></pre>

## Type Signature

```Haskell
TypicalAmong
 :: typename...
 -> auto...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalAmong
{
    template<auto>
    alias Page
    {
        using type = RESULT;
    };
};
```

## Examples

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
/**** SupposedResult ****/
using SupposedResult = int***;

/**** Result ****/
using Result = TypicalAmong<int, int*, int**, int***>::Page<3>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalAmong` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the element at the index is returned. Otherwise:
  1. Drop several elements from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `TypicalAmong` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<typename...Elements>
struct TypicalAmong {};

template<typename First>
struct TypicalAmong<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { using type = First; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>::type;
};

template<typename First, typename Second, typename...Others>
struct TypicalAmong<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    { using type = TypicalAmong<Others...>::template ProtoPage<I - 2>::type; };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { using type = First; };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    { using type = Second; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/typical_among/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/typical_among.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_among.test.hpp)
