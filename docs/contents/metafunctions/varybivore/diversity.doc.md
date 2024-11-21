<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Diversity`

## Description

`Varybivore::Diversity` accepts a set of nonrepetitive variables and returns a function.
When invoked, the function appends the arguments to the previously provided set such that the resulting list:

- contains every variable from the previously provided set and the arguments;
- doesn't contain repetitive variables;
- preserves the relative order of every variable;

The resulting list will be held inside a `Shuttle`.

<pre><code>   Variables...
-> Arguments...
-> MakeMathematicalSet(Variables..., Arguments...)</code></pre>

## Type Signature

```Haskell
Diversity ::   auto...
            -> template<auto...>
```

## Structure

```C++
template<auto...>
struct Diversity
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will use `Diversity` to append `0, 1, 2` to `1, -1`:

```C++
template<auto...>
struct Shuttle;

template<auto...Args>
using Metafunction = Diversity<1, -1>
::Page<Args...>;

using SupposedResult = Shuttle<1, -1, 0, 2>;

using Result = Metafunction<0, 1, 2>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Diversity` is implemented as a shortcut to `TypicaDiversity<*>::type`:

```C++
template<auto...Variables>
struct Diversity
{
    template<auto...Agreements>
    using Page = TypicalDiversity<Variables...>
    ::template ProtoPage<Agreements...>
    ::type;
};
```

## Links

- [source code](../../../../conceptrodon/descend/varybivore/diversity.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/diversity.test.hpp)
