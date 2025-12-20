<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Cotanivore::TypicalPaste`

<p style='text-align: right'><a href="../../../facilities/metafunctions.md#cotanivore-typical-paste">To Index</a></p>

## Description

`Cotanivore::TypicalPaste` accepts a list of packed containers.
It concatenates them together and uses the first container to hold the result.

<pre><code>   Con<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>...&gt;, Con<sub><i>1</i></sub>&lt;Es<sub><i>1</i></sub>...&gt;, ..., Con<sub><i>n</i></sub>&lt;Es<sub><i>n</i></sub>...&gt;
-> Con<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>..., Es<sub><i>1</i></sub>..., ..., Es<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
TypicalPaste
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Examples

Here, we paste `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>` together:

```C++
/**** Container ****/
template<typename...>
struct Container {};

/**** SupposedResult ****/
using SupposedResult = Container<int, float, float*, double>;

/**** Result ****/
using Result = TypicalPaste
<
    Container<>,
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPaste` using recursion over the total number of packed containers.

- **Base Case:** Handle several amounts directly;
- **Recursive Case:**
  1. Concatenate several packed containers at the front directly and place the result into the first container;
  2. Invoke `TypicalPaste` with the newly packed first container and the unhandled containers.

A simplified version will be as follows:

```C++
template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedContainer>
struct TypicalPaste<PackedContainer>
{
    using type = PackedContainer;
};

// Recursive Case:

template
<
    template<typename...> class ContainerA,
    template<typename...> class ContainerB,
    typename...ElementAs, 
    typename...ElementBs,
    typename...Others
>
struct TypicalPaste<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
{
    using type = TypicalPaste
    <
        // Put ElementAs... and ElementBs into the first container `ContainerA`
        ContainerA<ElementAs..., ElementBs...>,
        Others...
    >::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/cotanivore/typical_paste/implementation.hpp)
- [Source code](../../../../conceptrodon/cotanivore/typical_paste.hpp)
- [Unit test](../../../../tests/unit/metafunctions/cotanivore/typical_paste.test.hpp)
