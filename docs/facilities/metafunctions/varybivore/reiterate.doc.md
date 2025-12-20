<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Reiterate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-reiterate">To Index</a></p>

## Description

`Varybivore::Reiterate` accepts a list of variables and returns a function.

When invoked by the times of repetitions, the function repeats the list the given number of times and stores the result inside `Shuttle`.

<pre><code>   Vs...
-> N
-> Capsule&lt;Vs...<sub>1</sub>, Vs...<sub>2</sub>, ..., Vs...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
Reiterate
 :: auto...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Reiterate
{
    template<auto>
    alias Page = RESULT;
};
```

## Examples

We will repeat `0, 1` four times:

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<
    0, 1,
    0, 1,
    0, 1,
    0, 1
>;

/**** Result ****/
using Result = Reiterate<0, 1>
::Page<4>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Reiterate<*>::Page` is implemented as a shortcut to `TypicaReiterate<*>::Page<*>::type`:

```C++
template<auto...Variables>
struct Reiterate
{
    template<auto...Agreements>
    using Page = TypicalReiterate<Variables...>
    ::template Page<Agreements...>
    ::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/reiterate/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/reiterate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/reiterate.test.hpp)
