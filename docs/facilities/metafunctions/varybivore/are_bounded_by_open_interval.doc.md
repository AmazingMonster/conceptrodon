<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreBoundedByOpenInterval`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-bounded-by-open-interval">To Index</a></p>

## Description

`Varybivore::AreBoundedByOpenInterval` accepts two variables, indicating an open interval, and returns a predicate.

When invoked, the predicate returns true if all the arguments are within the open interval;
otherwise, the predicate returns false.

<pre><code>   Min, Max
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Min &lt; V<sub>0</sub> &lt; Max) && (Min &lt; V<sub>1</sub> &lt; Max) && ... && (Min &lt; V<sub>n</sub> &lt; Max)</code></pre>

## Type Signature

```Haskell
AreBoundedByOpenInterval
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct AreBoundedByOpenInterval
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
/**** Metafunction ****/
// Create a open interval (1, 4).
template<auto...Args>
using Metafunction
= AreBoundedByOpenInterval<1, 4>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<2, 3>::value);
static_assert(! Metafunction<1, 2, 3>::value);
static_assert(! Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<2, 3, -1>::value);
```

## Implementation

We will implement `AreBoundedByOpenInterval` using only `<`, meaning <code>Variable &in; (Lower, Upper)</code> is expressed as:

```C++
(Lower < Variable) && (Variable < Upper)
```

Here's the entire implementation:

```C++
template<auto Lower, auto Upper>
struct AreBoundedByOpenInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(Lower < Variables && Variables < Upper)) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(Lower < Variables && Variables < Upper)) };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_bounded_by_open_interval/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_bounded_by_open_interval.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_bounded_by_open_interval.test.hpp)
