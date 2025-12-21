<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Stockivore::Paste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#stockivore-paste">To Index</a></p>

## Description

`Stockivore::Paste` accepts a list of packed stockrooms.
It concatenates them together and uses the first stockroom to hold the result.

<pre><code>   Stoc<sub><i>0</i></sub>&lt;Seqs<sub><i>0</i></sub>...&gt;, Stoc<sub><i>1</i></sub>&lt;Seqs<sub><i>1</i></sub>...&gt;, ..., Stoc<sub><i>n</i></sub>&lt;Seqs<sub><i>n</i></sub>...&gt;
-> Stoc<sub><i>0</i></sub>&lt;Seqs<sub><i>0</i></sub>..., Seqs<sub><i>1</i></sub>..., ..., Seqs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Paste
 :: template<typename...>
```

## Structure

```C++
template<typename...>
using Paste = RESULT;
```

## Examples

Here, we paste `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>` together:

```C++
/**** Vessels ****/
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

/**** Items ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult = Stockroom_0<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result = Paste
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Stockivore::Paste` is implemented as a shortcut to the member `type` of [`Stockivore::TypicalPaste`](./typical_paste.doc.md).

```C++
template<typename...Args>
using Paste = TypicalPaste<Args...>::type;
```

## Links

- [Example](../../../code/facilities/metafunctions/stockivore/paste/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/stockivore/paste.hpp)
- [Unit test](../../../../tests/unit/metafunctions/stockivore/paste.test.hpp)
