<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalReiterate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-reiterate">To Index</a></p>

## Description

`Typelivore::TypicalReiterate` accepts a list of elements and returns a function.

When invoked by the times of repetitions, the function repeats the list the given number of times and stores the result inside `Capsule`.

<pre><code>   Es...
-> N
-> Capsule&lt;Es...<sub>1</sub>, Es...<sub>2</sub>, ..., Es...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalReiterate
 :: typename...
 -> auto...
 -> typename
```

## Structure

```C++
template<typename...>
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
using Result = TypicalReiterate<int, int*>
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
    template<typename...> class Container,
    typename...Elements
>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Agreements>
    using Mold = Container<Elements..., Agreements...>;
};
```

The result will be held inside a `Capsule`:

```C++
template<typename...>
struct Capsule;
```

Here is a simplified version of the implementation:

```C++
template<typename...Elements>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Capsule<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Capsule<Elements...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Mold<Elements..., Elements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/typical_reiterate/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/typical_reiterate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_reiterate.test.hpp)
