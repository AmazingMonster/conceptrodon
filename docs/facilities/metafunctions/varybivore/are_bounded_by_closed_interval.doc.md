<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreBoundedByClosedInterval`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-bound-by-closed-interval">To Index</a></p>

## Description

`Varybivore::AreBoundedByClosedInterval` accepts two variables, indicating a closed interval, and returns a predicate.

When invoked, the predicate returns true if all the arguments are within the closed interval;
otherwise, the predicate returns false.

<pre><code>   Min, Max
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Min &le; V<sub>0</sub> &le; Max) && (Min &le; V<sub>1</sub> &le; Max) && ... && (Min &le; V<sub>n</sub> &le; Max)</code></pre>

## Type Signature

```Haskell
AreBoundedByClosedInterval
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct AreBoundedByClosedInterval
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
// Create a closed interval [1, 4].
template<auto...Args>
using Metafunction
= AreBoundedByClosedInterval<1, 4>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4, 5>::value);
```

## Implementation

We will implement `AreBoundedByClosedInterval` using only `<`, meaning <code>Variable &in; [Lower, Upper]</code> is expressed as:

```C++
(not (Variable < Lower)) && (not (Upper < Variable))
```

Here's the entire implementation:

```C++
template<auto Lower, auto Upper>
struct AreBoundedByClosedInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Lower) && not (Upper < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < Lower) && not (Upper < Variables))) };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_bounded_by_closed_interval/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_bounded_by_closed_interval.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_bounded_by_closed_interval.test.hpp)
