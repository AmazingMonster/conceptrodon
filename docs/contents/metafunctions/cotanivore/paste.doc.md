<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Cotanivore::Paste`

## Description

`Cotanivore::Paste` is an alias template. It concatenates a variable number of packed containers. The first container will be used to hold the result.
<pre><code>   ...Container<sub><i>i</i></sub>&lt;Elements<sub><i>i</i></sub>...&gt;...
-> Container<sub><i>0</i></sub>&lt;Elements<sub><i>0</i></sub>..., Elements<sub><i>1</i></sub>..., ...></code></pre>

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
- [unit test](../../../../tests/unit/cotanivore/paste.test.hpp)
