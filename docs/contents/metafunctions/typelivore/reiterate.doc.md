<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Reiterate`

## Description

`Typelivore::Reiterate` accepts a list of elements and returns a function. When invoked by the times of repetitions, the function repeats the list the given number of times and stores the result inside `Capsule`.
<pre><code>   Elements...
-> N
-> Elements...<sub>1</sub>, Elements...<sub>2</sub>, ..., Elements...<sub>N</sub></code></pre>

## Type Signature

```Haskell
Reiterate ::   typename...
            -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Reiterate
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will repeat `int, int*` four times:

```C++
template<typename...>
struct Capsule;

using SupposedResult = Capsule<
    int, int*,
    int, int*,
    int, int*,
    int, int*
>;

using Result = Reiterate<int, int*>
::Page<4>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Reiterate<...>::Page` is implemented as a shortcut to `TypicaReiterate<...>::Page<...>::type`:

```C++
template<typename...Elements>
struct Reiterate
{
    template<auto...Agreements>
    using Page = TypicalReiterate<Elements...>
    ::template Page<Agreements...>
    ::type;
};
```

## Links

- [source code](../../../../conceptrodon/descend/typelivore/reiterate.hpp)
- [unit test](../../../../tests/unit/typelivore/reiterate.test.hpp)
