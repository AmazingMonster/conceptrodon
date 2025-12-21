<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Total`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-total">To Index</a></p>

## Description

`Omennivore::Total` accepts a packed vessel and returns the total number of its items.

<pre><code>   Vessel&lt;Items...&gt;
-> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Total
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct Total
{
    static constexpr size_t value {RESULT};
};

template<typename>
constexpr size_t Total_v {RESULT};
```

## Example

We will find the total number of elements contained in `Capsule<int, int*, int**, int**>`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Test ****/
static_assert(Total<Capsule<int, int*, int**, int**>>::value == 4);
```

## Implementation

We will implement the case where we count elements inside a packed container.

```C++
template<typename>
struct Total {};

template
<
    template<typename...> class Container,
    typename...Elements
>
struct Total<Container<Elements...>>
{ static constexpr size_t value = sizeof...(Elements); };
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/total/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/total.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/total.test.hpp)
