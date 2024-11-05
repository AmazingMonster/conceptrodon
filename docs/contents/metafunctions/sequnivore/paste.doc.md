<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sequnivore::Paste`

## Description

`Sequnivore::Paste` is an alias template. It concatenates a variable number of packed sequences. The first sequence will be used to hold the result.
<pre><code>   ...Sequence<sub><i>i</i></sub>&lt;Variables<sub><i>i</i></sub>...&gt;...
-> Sequence<sub><i>0</i></sub>&lt;Variables<sub><i>0</i></sub>..., Variables<sub><i>1</i></sub>..., ...></code></pre>

`Sequnivore::Paste` can also handle `std::integer_sequence`. The function `static_cast` integers to fit into the first sequence.
<pre><code>   ...Sequence<sub><i>i</i></sub>&lt;Type<sub><i>i</i></sub>, Variables<sub><i>i</i></sub>...&gt;...
-> Sequence<sub><i>0</i></sub>&lt;Type<sub><i>0</i></sub>, Variables<sub><i>0</i></sub>..., Variables<sub><i>1</i></sub>..., ...></code></pre>

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

Here, we paste `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>` together:

```C++
using SupposedResult = std::integer_sequence<int, 0, 1, 2, 3>;

using Result = Paste
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Sequnivore::Paste` is implemented as a shortcut to the member `type` of [`Sequnivore::TypicalPaste`](./typical_paste.doc.md).

```C++
template<typename...Args>
using Paste = TypicalPaste<Args...>::type;
```

## Links

- [source code](../../../../conceptrodon/sequnivore/paste.hpp)
- [unit test](../../../../tests/unit/sequnivore/paste.test.hpp)
