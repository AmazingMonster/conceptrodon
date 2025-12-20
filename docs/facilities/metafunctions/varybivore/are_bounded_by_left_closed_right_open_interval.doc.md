<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreBoundedByLeftClosedRightOpenInterval`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-bounded-by-left-closed-right-open-interval">To Index</a></p>

## Description

`Varybivore::AreBoundedByLeftClosedRightOpenInterval` accepts two variables, indicating a left-closed-right-open interval, and returns a predicate.

When invoked, the predicate returns true if all the arguments are within the left-closed-right-open interval;
otherwise, the predicate returns false.

<pre><code>   Min, Max
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Min &le; V<sub>0</sub> &lt; Max) && (Min &le; V<sub>1</sub> &lt; Max) && ... && (Min &le; V<sub>n</sub> &lt; Max)</code></pre>

## Type Signature

```Haskell
AreBoundedByLeftClosedRightOpenInterval
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct AreBoundedByLeftClosedRightOpenInterval
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
// Create a left-closed-right-open interval [1, 4).
template<auto...Args>
using Metafunction
= AreBoundedByLeftClosedRightOpenInterval<1, 4>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1, 2, 3, 3.5>::value);
static_assert(! Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4, 5>::value);
```

## Implementation

We will implement `AreBoundedByLeftClosedRightOpenInterval` using only `<`, meaning <code>Variable &in; [Lower, Upper)</code> is expressed as:

```C++
(not (Variable < Lower)) && (Variable < Upper)
```

Here's the entire implementation:

```C++
template<auto Lower, auto Upper>
struct AreBoundedByLeftClosedRightOpenInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Lower) && Variables < Upper)) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(not (Variables < Lower) && Variables < Upper)) };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_bounded_by_left_closed_right_open_interval/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_bounded_by_left_closed_right_open_interval.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_bounded_by_left_closed_right_open_interval.test.hpp)
