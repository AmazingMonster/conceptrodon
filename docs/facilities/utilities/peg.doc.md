<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Peg`

<p style='text-align: right;'><a href="../../index.md#utility-symbols-peg">To Index</a></p>

## Description

`Peg` accepts a index and returns the index via member `value`.

<pre><code>Index -> Index</code></pre>

## Type Signature

```Haskell
Peg :: auto... -> auto
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

## Implementation

```C++
template<size_t Index>
struct Peg
{
    static constexpr size_t value
    {Index};
};
```

## Links

- [source code](../../../conceptrodon/peg.hpp)
