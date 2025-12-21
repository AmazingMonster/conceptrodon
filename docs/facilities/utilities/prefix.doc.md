<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Prefix`

<p style='text-align: right;'><a href="../utilities.md#prefix">To Index</a></p>

## Description

`Prefix` accepts an element and an index. It constantly evaluates to `true`.

<pre><code>Element, Index -> true</code></pre>

## Structure

```C++
template<typename, size_t>
concept Prefix = REQUIREMENT;
```

## Examples

This concept works as an enumerator of arguments when expanded alongside an index sequence.
In the following example, We will use `Prefix` to count out the first three arguments and return the fourth one.

```C++
/**** Midst ****/
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    // We use `Prefix<I> auto...` to enumerate unwanted arguments.
    static constexpr auto idyl(Prefix<I> auto..., auto target, auto...)
    { return target; }
};

/**** TheFourth_v ****/
template<auto...Args>
constexpr auto TheFourth_v
= Midst<std::make_index_sequence<3>>::idyl(Args...);

/**** Tests ****/
static_assert(TheFourth_v<0, 1, 2, 3, 4> == 3);
static_assert(TheFourth_v<0, 1, 2, -3, 4> == -3);
```

## Implementation

```C++
template<typename, size_t>
concept Prefix = true;
```

## Links

- [Example](../../code/facilities/utilities/prefix/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/prefix.hpp)
- [Unit test](../../../tests/unit/utilities/prefix.test.hpp)
