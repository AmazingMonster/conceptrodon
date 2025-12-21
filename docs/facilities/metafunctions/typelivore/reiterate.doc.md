<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Reiterate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-reiterate">To Index</a></p>

## Description

`Typelivore::Reiterate` accepts a list of elements and returns a function.

When invoked by the times of repetitions, the function repeats the list the given number of times and stores the result inside `Capsule`.

<pre><code>   Es...
-> N
-> Capsule&lt;Es...<sub>1</sub>, Es...<sub>2</sub>, ..., Es...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
Reiterate
 :: typename...
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

We will repeat `int, int*` four times:

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<
    int, int*,
    int, int*,
    int, int*,
    int, int*
>;

/**** Result ****/
using Result = Reiterate<int, int*>
::Page<4>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Reiterate<*>::Page` is implemented as a shortcut to `TypicaReiterate<*>::Page<*>::type`:

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

- [Example](../../../code/facilities/metafunctions/typelivore/reiterate/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/reiterate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/reiterate.test.hpp)
