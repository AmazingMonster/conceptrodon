<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sequnivore::Paste`

## Description

`Sequnivore::Paste` accepts a list of packed sequences.
It concatenates them together and uses the first sequence to hold the result.

<pre><code>   Sequence<sub><i>0</i></sub>&lt;Vs<sub><i>0</i></sub>...&gt;, Sequence<sub><i>1</i></sub>&lt;Vs<sub><i>1</i></sub>...&gt;, ..., Sequence<sub><i>n</i></sub>&lt;Vs<sub><i>n</i></sub>...&gt;
-> Sequence<sub><i>0</i></sub>&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

`Sequnivore::Paste` can also handle `std::integer_sequence`. The function `static_cast` integers to fit into the first sequence.

<pre><code>   Sequence<sub><i>0</i></sub>&lt;Type<sub>0</sub>, Vs<sub><i>0</i></sub>...&gt;, Sequence<sub><i>1</i></sub>&lt;Type<sub>1</sub>, Vs<sub><i>1</i></sub>...&gt;, ..., Sequence<sub><i>n</i></sub>&lt;Type<sub>n</sub>, Vs<sub><i>n</i></sub>...&gt;
-> Sequence<sub><i>0</i></sub>&lt;Type<sub>0</sub>, Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Paste :: template<typename...>
```

## Structure

```C++
template<typename...>
using Paste = RESULT;
```

## Examples

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
- [unit test](../../../../tests/unit/metafunctions/sequnivore/paste.test.hpp)
