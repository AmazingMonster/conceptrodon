<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TypicalReiterate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-typical-reiterate">To Index</a></p>

## Description

`Varybivore::TypicalReiterate` accepts a list of variables and returns a function.

When invoked by the times of repetitions, the function repeats the list the given number of times and stores the result inside `Shuttle`.

<pre><code>   Vs...
-> N
-> Shuttle&lt;Vs...<sub>1</sub>, Vs...<sub>2</sub>, ..., Vs...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalReiterate
 :: auto...
 -> auto...
 -> typename
```

## Structure

```C++
template<auto...>
struct TypicalReiterate
{
    template<auto>
    alias Page
    {
        using type = RESULT;
    };

    template<auto>
    using Page_t = RESULT;
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
using Result = TypicalReiterate<0, 1>
::Page<4>
::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalReiterate` using recursion over the times of iterations.

- **Base Case:** Handle several numbers of times directly.
- **Recursive Case:**
  1. Iterate several times;
  2. Reduce the total times by the same amount;
  3. Invoke the first layer of `TypicalReiterate` with the times left;
  4. Concatenate two results.

We will use `ExtendBack` to concatenate two parts.

```C++
template<typename...>
struct ExtendBack {};

template<
    template<auto...> class Sequence,
    auto...Variables
>
struct ExtendBack<Sequence<Variables...>>
{
    template<auto...Agreements>
    using Page = Sequence<Variables..., Agreements...>;
};
```

The result will be held inside a `Shuttle`:

```C++
template<auto...>
struct Shuttle;
```

Here is a simplified version of the implementation:

```C++
template<auto...Variables>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Shuttle<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Shuttle<Variables...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Page<Variables..., Variables...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/typical_reiterate/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/typical_reiterate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/typical_reiterate.test.hpp)
