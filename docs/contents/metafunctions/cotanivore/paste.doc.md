<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Cotanivore::Paste`

## Description

`Cotanivore::Paste` accepts a list of packed containers.
It concatenates them together and uses the first container to hold the result.

<pre><code>   Container<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>...&gt;, Container<sub><i>1</i></sub>&lt;Es<sub><i>1</i></sub>...&gt;, ..., Container<sub><i>n</i></sub>&lt;Es<sub><i>n</i></sub>...&gt;
-> Container<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>..., Es<sub><i>1</i></sub>..., ..., Es<sub><i>n</i></sub>...></code></pre>

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

Here, we paste `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>` together:

```C++
using SupposedResult = std::tuple<int, float, float*, double>;

using Result = Paste
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Cotanivore::Paste` is implemented as a shortcut to the member `type` of [`Cotanivore::TypicalPaste`](./typical_paste.doc.md).

```C++
template<typename...Args>
using Paste = TypicalPaste<Args...>::type;
```

## Links

- [source code](../../../../conceptrodon/cotanivore/paste.hpp)
- [unit test](../../../../tests/unit/metafunctions/cotanivore/paste.test.hpp)
