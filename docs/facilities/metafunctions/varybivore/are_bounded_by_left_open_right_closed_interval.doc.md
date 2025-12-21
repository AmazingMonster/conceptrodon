<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreBoundedByLeftOpenRightClosedInterval`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-bounded-by-left-open-right-closed-interval">To Index</a></p>

## Description

`Varybivore::AreBoundedByLeftOpenRightClosedInterval` accepts two variables, indicating a left-open-right-closed interval, and returns a predicate.

When invoked, the predicate returns true if all the arguments are within the left-open-right-closed interval;
otherwise, the predicate returns false.

<pre><code>   Min, Max
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Min &lt; V<sub>0</sub> &le; Max) && (Min &lt; V<sub>1</sub> &le; Max) && ... && (Min &lt; V<sub>n</sub> &le; Max)</code></pre>

## Type Signature

```Haskell
AreBoundedByLeftOpenRightClosedInterval
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct AreBoundedByLeftOpenRightClosedInterval
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
// Create a left-open-right-closed interval (1, 4].
template<auto...Args>
using Metafunction
= AreBoundedByLeftOpenRightClosedInterval<1, 4>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<-1, 1, 2, 3, 4>::value);
```

## Implementation

We will implement `AreBoundedByLeftOpenRightClosedInterval` using only `<`, meaning <code>Variable &in; (Lower, Upper]</code> is expressed as:

```C++
(Lower < Variable) && (not (Upper < Variable))
```

Here's the entire implementation:

```C++
template<auto Lower, auto Upper>
struct AreBoundedByLeftOpenRightClosedInterval
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr bool value
        { (...&&(Lower < Variables && not (Upper < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(Lower < Variables && not (Upper < Variables))) };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_bounded_by_left_open_right_closed_interval/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/are_bounded_by_left_open_right_closed_interval.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_bounded_by_left_open_right_closed_interval.test.hpp)
