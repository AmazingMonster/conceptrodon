<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Stockivore::Paste`

## Description

`Stockivore::Paste` is an alias template. It concatenates a list of packed stockrooms. The first stockroom will be used to hold the result.
<pre><code>   ...Stockroom<sub><i>i</i></sub>&lt;Sequences<sub><i>i</i></sub>...&gt;...
-> Stockroom<sub><i>0</i></sub>&lt;Sequences<sub><i>0</i></sub>..., Sequences<sub><i>1</i></sub>..., ...></code></pre>

## Type Signature

```Haskell
Paste :: template<typename...>
```

## Structure

```C++
template<typename...>
using Paste = RESULT;
```

## Example

Here, we paste `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>` together:

```C++
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

using SupposedResult = Stockroom_0<Seq_0, Seq_1, Seq_2, Seq_3>;

using Result = Paste
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Stockivore::Paste` is implemented as a shortcut to the member `type` of [`Stockivore::TypicalPaste`](./typical_paste.doc.md).

```C++
template<typename...Args>
using Paste = TypicalPaste<Args...>::type;
```

## Links

- [source code](../../../../conceptrodon/stockivore/paste.hpp)
- [unit test](../../../../tests/unit/stockivore/paste.test.hpp)
