<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateSegment`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-segment">To Index</a></p>

## Description

`Pagelivore::CognateSegment` accepts an operation and returns a function.

When invoked by a list of indices in ascending order, the function collects the differences between adjacent indices and instantiates the operation with the collection.

<pre><code>   Oper
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> Oper&lt;I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateSegment
 :: template<auto...> class...
 -> template<auto...> class

--The list can also be provided via `std::index_sequence`.
CognateSegment
 :: template<auto...> class...
 -> template<typename...> class
```

## Structure

```C++
template<template<auto...> class>
struct CognateSegment
{
    template<auto...>
    alias Page = RESULT;

    template<typename>
    alias Mold = RESULT;
};
```

## Examples

We will invoke `Operation` with the differences between adjacent indices collected from `2, 3, 6, 8, 10`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    static_cast<size_t>(2),
    static_cast<size_t>(3-2),
    static_cast<size_t>(6-3),
    static_cast<size_t>(8-6),
    static_cast<size_t>(10-8)
>;

/**** Result ****/
using Result = CognateSegment<Operation>
::Page<2, 3, 6, 8, 10>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will pop the last variable from the list and then subtract the new list from the original one. The process can be described as follows.

<table>
  <tr>
    <td style="text-align: center">Original</td>
    <td style="text-align: center"><code>I<sub>0</sub></code></td>
    <td style="text-align: center"><code>I<sub>1</sub></code></td>
    <td style="text-align: center"><code>I<sub>2</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>i</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>n</sub></code></td>
  </tr>
  <tr>
    <td style="text-align: center">New</td>
    <td style="text-align: center"></td>
    <td style="text-align: center"><code>I<sub>0</sub></code></td>
    <td style="text-align: center"><code>I<sub>1</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>i-1</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>n-1</sub></code></td>
  </tr>
  <tr>
    <td style="text-align: center">Subtraction</td>
    <td style="text-align: center"><code>I<sub>0</sub></code></td>
    <td style="text-align: center"><code>I<sub>1</sub>-I<sub>0</sub></code></td>
    <td style="text-align: center"><code>I<sub>2</sub>-I<sub>1</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>i</sub>-I<sub>i-1</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>n</sub>-I<sub>n-1</sub></code></td>
  </tr>
</table>

We will use `Varybivore::TypicalPop` to remove the last variable from the list. Then, we will employ `Send` to utilize the result.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
```

The result of `Varybivore::TypicalPop` will be sent to `Detail`, which performs the subtraction through a fold expression.

```C++
template<size_t I, size_t...J>
struct Detail
{
    template<size_t...K>
    requires (...&&(K < J))
    using Hidden_t = Operation<I, J-K...>;
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation>
struct CognateSegment
{
    template<size_t I, size_t...J>
    struct Detail
    {
        template<size_t...K>
        requires (...&&(K < J))
        using Hidden_t = Operation<I, J-K...>;
    };

    template<auto...Agreements>
    using Page = Send<typename TypicalPop<Agreements...>::type>
    ::template Rail<Detail<Agreements...>::template Hidden_t>;

    // Indices can also be passed using `std::index_sequence`.
    template<typename>
    struct Hidden {};

    template<size_t I, size_t...J>
    struct Hidden<std::index_sequence<I, J...>>
    {
        template<size_t...K>
        requires (...&&(K < J))
        using Detail_t = Operation<I, J-K...>;

        using type = Send<typename TypicalPop<I, J...>::type>
        ::template Rail<Detail_t>;
    };

    template<typename...Agreements>
    using Mold = Hidden<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_segment/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/cognate_segment.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_segment.test.hpp)
