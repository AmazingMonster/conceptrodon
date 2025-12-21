<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Peg`

<p style='text-align: right;'><a href="../utilities.md#peg">To Index</a></p>

## Description

`Peg` accepts a index and returns the index via member `value`.

<pre><code>   I
-> struct { value = I; }</code></pre>

## Type Signature

```Haskell
Peg
 :: auto...
 -> auto
```

## Structure

```C++
template<size_t>
struct Peg
{
    static constexpr size_t value
    {RESULT};
};
```

## Examples

```C++
static_assert(Peg<1>::value == 1);
static_assert(Peg<1>::value != 2);
static_assert(Peg<static_cast<size_t>(1)>::value == 1);
```

## Implementation

```C++
template <std::make_signed_t<size_t> I>
struct Peg
{ static constexpr std::make_signed_t<size_t> value {I}; };
```

## Links

- [Example](../../code/facilities/utilities/peg/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/peg.hpp)
- [Unit test](../../../tests/unit/utilities/peg.test.hpp)
