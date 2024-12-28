<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreNoGreaterThan`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-no-greater-than">To Index</a></p>

## Description

`Varybivore::AreNoGreaterThan` accepts a variable and returns a predicate.
When invoked, the predicate returns true if all the arguments are less or equal to the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> &le; Target) && (V<sub>1</sub> &le; Target) && ... && (V<sub>n</sub> &le; Target)</code></pre>

## Type Signature

```Haskell
AreNoGreaterThan
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AreNoGreaterThan
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
template<auto...Args>
using Metafunction
= AreNoGreaterThan<5>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<2, 3, 4, 5>::value);
static_assert(! Metafunction<6, 2, 3>::value);
```

## Implementation

We will implement `AreNoGreaterThan` using only `<`, meaning <code>Variable &le; Target</code> is expressed as:

```C++
not (Target < Variable)
```

```C++
template<auto Target>
struct AreNoGreaterThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Target < Variables))) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Target < Variables))) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQgAMwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcTC8RFuABVWsBMAQodhgRNiF4HLdLsQoqgAOIE97xBEIQzAkwBKxXW4M26g8FkqEwuGoAB03IAaq08EwYvQFOjgYzblicQRbspiKgiMomCixYyaXTLuLxXNHMhbmgGBNMKo0sRbjFUJ5bgA3MReTAqzW3NW3CDcznmABsnogDHlLqRxBR0rZtz5xAFQswCmWMadAQAIlD1eKaYnEsnVfTGcznqzobCiG7LsACWDGAQRYkMVmGV4skYZUrME7EvGZXKFU22cXS68K27RenqTWmWDc5D8xy3WGI8LRSPtXhdfrDcbTebLYqUQB9K1OkfO13cz3e33SiABoMttyh/mC4Ux5ZxtPq1NJ4fXf5/QG/Pa3bCqKwzzNl8wK/l%2BZwfr%2BtwALKokwVBeAwDg5J8kFXDmEL2pOhbcviwCVtWlx1uEwCwfBiHIY01KtniBKRMSpKgsQFJUtCyTzpcIAgFu2FuPhCgDlW75XGBRyIlG0qgVci7INuTAKEobQQHBLSUShAhsmYpC3IkOnSLcHFVtxNreJgywiZcsnyYp8QEBAYBgORalIRpDBsh6Onabp6Imba5lJhwqy0JwyS8H4HBaKQqCcG41jWBK6ybM25iJDwpAEJoQWrAA1iAySSJyGgABxmGYACc5VcMkJXFVwAQBNIIUcJIvAsBIGgaKQEVRTFHC8AoIBdZlkVBaQcCwDAiAgOsBBpHC5CUGgTx0PEkSsNsqjFR6AC0HqSLcwDILqUicmYvCYPgRDhugej8IIIhiOwUgyIIigqOoo2kLoXCkAA7sQTBpJwPDBaF4VZdFnAAPJwvN0qoFQtxbbt%2B2HcdtynWYLoeCt9CmqlXDLLwI1aKsEBIMtaSrWQFAQFTNMgMAUjaTQtDMYNEAxJDMThK0ACeIO8LzzDEPz0MxNomAOELpDLX20MMLQgtfVgMReMAMK0LQg3cLwWAsIYwDiKreAEihVpRpDRrS3C2zpeEoLNVFtB4DEgNix4WCQwQ4btXrpCW8Q5pKPGYJG67RhZasVAGARPJ4Jgf3Q2kjCy/dwiiOIL0Z%2B9aiQz9%2BhGyg8WWPobuDZAqyoGkjS6ztEzoFC8amJY1hmL1Qc3VbVc9NLjQuAw7ieJ0eihOEwxVKMv3FNkAjTH4M%2BZHPDALCMCS/XY/d9JM7QjwUm/1NvAj9G0a9Txvti7wvehzGfE%2BLNPqwKElWwSGDHBhd1kN9cj217QdI6J1CrYwgLgQgJAnRmDSsTDK0dVgIEwEwLACQIC5X8IkTk5VEiNQ0JIMwkgPSdWSB6cq%2BhOCtVIO1NKnIPRcA9MVcqdUPQFWqtgzyPVeB9QGkNOBo1yZTQpjNOGC06YM3xutNgnBWgsCtAEHaTA9QGAbFwcqnIuBFQuldEgeBbq/Qzo9bO0hc5KHzl9XQ2kAZAyFh/L%2BnCoYcFhnNOEtxEZ/1RgdZAyiyKqPUUVHGqA8bxCgYkMwsDSZjSEeI%2BIi16aBOpvjFA3jVFcC6mzDmlBuZfRFgLWWOSxYSyljLAO8tyyK2VpDNWGstY61lgbCO2wor4HNo4S2usoo22QHbWWjt6iQ1du7AWXtGkkz9rLIOIdMBh0NkYSOoB%2BF8DjgoBOScU5pwDgYrOz1jGyDzp9KKFii5R1blYMuAzK5oOirXHI9dG7NxOe3Tu8Ru4XOfkfNyg9h75EXsEIe58lhLxKDkG%2BgKV7/Onn3Nyp897fNvu8xo0LwWXzvjC0em9d5IvfmsDYb8ibkM/hDL6v8UYAKUUbTGaiNEaBdOA66ISiYk3gaQRByDRiXOapQ6hai8EBGSOVBqiR8GEMkL9ex3DbC8IiQI%2BAQjZrw1idE4gkjtgyLRiwBQVpdRWl8VhCYWiIE3TurIQx2zXryFMfsnQSR/qA2BnrWxhLeowxEQjJGqg1Uaq1TqskEwAlBIJtAxI4To7jUpvEmmCrw2JM1WkNIu5VHbl1QQbc7rjF0AyVzHmfMxZ5OzeLSW/dZalMEOUlWTTMDq01mIWpAd6mzJGaQZp282nW1ULbUEPTBB9K%2BgMj2/Nhk%2BzGQHCZmQpnh1maRENsclTLMTsnVOEV0qbKehIHZb0LUF2td4kubczkV3gNXa5AhdY7Ebju05FgO5cK7ronulyt4fIgK4EFvz0CYtBY0F9s9GjvshQi6%2B%2B8fkPv/fMB%2B69b4Adhei0DFRwN4pfji56Drv5Es4MjD1mrrTetBL6sB2iA0wMZfwhBSCUGUA/pykAFVOSJBSDVEVnVaMBAYShp1/UJXDSZXlSQyQsH1QCJ1YqkgqpcFKmYTyzVEiOq4ZwIjZMP7nVYzJ9jUrVhByyM4SQQA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_no_greater_than/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_no_greater_than.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_no_greater_than.test.hpp)
