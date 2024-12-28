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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQAcpK4AMngMmAByPgBGmMQgAMwAnKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcTC8RFuIVQAHd4qRbrD4XI0ml4lDsMCJsQvA5bpdiJgLOsGFh0BYAJ4AeRxDHugniADcxMCTAB2KxXW6C26g8HvTBQmFw1AAOllADVWngmDF6Ao8cChbdCcSCLdlMRUERlExgOKBULefzLprNXNHMhbmgGBNMKo0sRbjFUJ5bpzvGbrTbBZbbhBZdLzAA2KMQREoj0S24K4hKlWYBS3KNRpOK5WqzPQ25YnHEZbLTM8gAiUKtmt51cSVo1QpFzzFEoxMtll2A5LBjAIasS%2BPNgq8WSMepNmALlb1BqN04lPb7r0H4fVje5o%2BFYLbkOhnfDydTqvVO7teAdTpdbo9Xp9xtNAH12ZmdyGw7Ks2ZI7HkfEBZuDmKZ5umma/tmJ5gRmibFvEZYVg2TZVjW27XP8fyAr8ey3NgqisM8M5fMCOGYWc6E4bcACymAtFQXgMA4OSfBRPw7LcbjkmK6K3KgzK3OEoLEH6oZcGikjLBGVythC4qHlK4ZksAQ4jpc47hMANF0UwDFMY03KJHOZIUlSNL0kyjCssJfoSuJtySOelwgCAT7yW4ykKBuw5oVcpFHLcAAq6aDqxByApeyDPkwChKG0EC0fRjHMQIEpmGiiR4i5fpeJgyy%2BZckXRbF8QEBAYBgNpSX6TkdloultyZcO2ViLl%2BVblcRUxXFZUVVVunJQZ0INYkElZSAOV5QVXUlfFfWJQNNWpdC9kjWNzUTa1U0dYVLT2sVPXlZVC16SlDBpRlaIALRcONk3tRYHCrLQnAAKy8H4HBaKQqCcG41jWFq6ybDO5iJDwpAEJoT2rAA1iAr2SNKGgBGYZjJMkXCvSjARcDyPLSC9HCSLwLASBoGikJ932/RwvAKCAlNQ19T2kHAsAwIgIDrAQaRwuQlBoE8dDxJErDbKoASRldkaSLcwDIA6UjSmYvCYPgRApugej8IIIhiOwUgyIIigqOoLOkLo4lIsQTBpJwPDPW9H3Qz9nAMnCfO6qgVC3JL0uy/Liu3MrZihh4wv0AmZjg8svDM1oqwQEgQtpCLZAUBAqfpyAwBSOlNC0MJDMQDErsxOErR0g7vAV8wxCMjE2iYA4NekELa4MgwtDVxbWAxF4wAwrQtAM9wvBYCwhjAOIfd4OSzHsumruui3cLbBDQn1K7tB4DEtsNx4WCuwQKZk%2BPpBL8QXpKJWYLT7vRjQ6sVAGCpcp4JgSKWZ9EO68IohxBG3/qbNQrsrb6GnigAGlh9B7wZpAVY/FGhjyuhMdAUJKymEsNYMwNMr5a2XognoLdGguGpNMPw4lQjhGGFUUY4lijZAEJQvQTDGgLBGAkcSdhSF9EmO0TwnQ9C8LOv0NonD6HcNsAI1hPCBGSKWFwVYChgZbAkE7Dg70qau1pn7KWMs5YKyVkjMOEBcCEBIBBWO8dn6rAQJgJgWAEgQDhv4RI0pkiJAJhoSQZhJCRgpq9SMqQiYk1IGTcG0pIxcEjAEZIuNIyIyxl4yMOiLa03pozSGz82ac2TtzT2/NM7ZyjmLNgnBWgsHZDyK6TBHQGEnFwZI0ouDIzVhrEgeBtbiX/vrIB0gQFKDARbXQ6UbZ2xrpo7R1NeC0w9rzOEfFfb%2B0MQ06eIcWltI0OHVAkdAJgzMHHHJLMk4pz2WnKOAss4XJzsgRpedMaU0LsXSgZcLZ1yrm3T5DcGRN1IW3DuA4u491dv3Qew9R5t0ng/bY318AL0cEvMe31V7IHXm3LeRNvq733lXI%2BcL45nzblfG%2BmA75TyMI/UApy%2BBvwUB/L%2BP8259MAYbQZshQHm2%2BmMyBT9sFWFgbihBrifppBQZwNBBAMFGQFbg/B8RCEipUfUPhzgICuDkcEakiiGHpEyMw3IQiCiMINRw2hiw9WiMaOIwR%2BQqEkLEQoi1XCRGyONQ6uYEiXVSI0WsDY6jlH6GdukmmnB9EBzlvcjZzTWnI1DBYzW1jlG2NOfYxxzjKCaPCZElpvieSvWSPjRIfiAmSHErMt2dNbDZITqzdmXMeZe2uaU0W4tKnEBYIHFgCh2QOnZLGuSEwOmWK1jrWQ/T2XG3kMM7lOgkikAmfbce0yXYZPdkU72Kzu29v7YOsUExdn7OjokRIxy61nJQLcq5JTr2jD7diV8zTnxDoIM%2BVQss%2BB0FeaXculcG7fP/Y3ZurcL5AsECC3u8LMADyHmIKFF8YVUsJaQBFfDkUr1UGvUEmK2TYt4Lig%2BdICUn2JRfUlmRyX3ypZpXJr8TQMs/t/ZkLKJ1sokByk2s7wELoedAnBQr4HwCQeKnIY8djoP44KiweC5kEO6UQ0V1qcjkPcB6vQNCKiutNSUHIWr2E5F1dI5TAhbVapM00Z1WnfXyIGOZqzdClEqLUYbVdoa5nho/XLHtfbfT7tBIe8xnST0ppOYndNTjRiirCaTEA6NpSntetjctFNT08jie5qtWSmZ2NIPDSQr1PF4x5BTAIkhMZcFRr%2BYNHBEhrrDdWi9mjVaZcyWFmGl94hZGcJIIAA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_bounded_by_open_interval/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_bounded_by_open_interval.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_bounded_by_open_interval.test.hpp)
