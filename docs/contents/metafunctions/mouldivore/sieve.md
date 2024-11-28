<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Sieve`

## Description

`Mouldivore::Sieve` accepts a list of predicates and returns a function.
When invoked, the function removes every argument that satisfies all of the predicates from its argument list. The result will be kept inside a `Capsule`.

<pre><code>   Predicates...
-> E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Capsule
   <
       (...&&Predicates&lt;E<sub>0</sub>&gt;) ? Nothing : E<sub>0</sub>,
       (...&&Predicates&lt;E<sub>1</sub>&gt;) ? Nothing : E<sub>1</sub>,
                            &vellip;
       (...&&Predicates&lt;E<sub>n</sub>&gt;) ? Nothing : E<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
Sieve ::   template<typename...> class...
        -> template<typename...>
```

## Structure

```C++
template<template<typename...> class...>
struct Sieve
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will remove every element whose value result is divisible by two and three in the list `Monotony<1>, Monotony<12>, Monotony<2>, Monotony<6>, Monotony<15>`.

```C++
template<auto I>
struct Monotony
{ static constexpr auto value {I}; };

template<typename Val>
struct DivisibleByTwo
{
    static constexpr bool value
    {Val::value % 2 == 0};
};

template<typename Val>
struct DivisibleByThree
{
    static constexpr bool value
    {Val::value % 3 == 0};
};

template<typename...>
struct Capsule;

template<typename...Args>
using Metafunction = Sieve<DivisibleByTwo, DivisibleByThree>
::Mold<Args...>;

using SupposedResult = Capsule
<Monotony<1>, Monotony<2>, Monotony<15>>;

using Result = Metafunction
<Monotony<1>, Monotony<12>, Monotony<2>, Monotony<6>, Monotony<15>>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Assuming we have smashed every element that has already appeared, the ordered collection of the elements left is the result we want.

To translate this idea into actual code, we need to implement smashing and collecting.
We do this by:

1. placing each element in a capsule separately;
2. taking the element out of its capsule if it satisfies all the predicates;
3. concatenating all capsules.

We can merge 1. and 2. by:

```C++
template<typename Element>
struct Detail 
{ using type = Capsule<>; };

template<typename Element>
requires (not (...&&Predicates<Element>::value))
struct Detail<Element>
{ using type = Capsule<Element>; };
```

We will use `Cotanivore::TypicalPaste` to concatenate the capsules. Here is the entire implementation:

```C++
template<template<typename...> class...Predicates>
struct Sieve
{
    template<typename Element>
    struct Detail 
    { using type = Capsule<>; };

    template<typename Element>
    requires (not (...&&Predicates<Element>::value))
    struct Detail<Element>
    { using type = Capsule<Element>; };

    template<typename...Elements>
    using Mold = TypicalPaste
    <typename Detail<Elements>::type...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACcSaQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5oERyN5YANQmgW5ejrSEAJ6n2CYaAIK7%2B4eYJ2fIE%2BhYVHcPzzMewYBy8x1ObgI1zSmAA%2BgRiExCAp/k8AQB6ABU2MxRw8LQYeAAbiR2CAACrQvCiWjKJgTd44zHogEETAsNIGNkQqEw5hsAB0QtRjwmxC8DiOlLS1LEdIZJwA7FZFQARU5WNFPdHoo4WenvNwGkAA1nszlMblnXmMVjvOnIADWmHcsiRkWIIrFEoIUqpNPlVrcDudrsE7oSIpMyoBRzjRy8WSMRxtH1VRxDLo84YikcCmueao1pu1uoASphkBsskTDcaS482RyuZhTWdY/Gmxagzb%2BZghQK7kcDvSFHi3bniI9SB2412WzzobbBcLAthhwYFGPsy1JzZZyml32B9h6GxBKLSCcnvHD3y7Sez4wCBYFDOb52jw%2BhQB5AgIBIUTRNcAW9SVpVlWl6SDHcIynCFT3ZZ9RQHO4r1gvcEKfQRX1Qtcrz/ADiAUPD7jRGMPzjRMImAO93lOdMIIDaDW0oj43APW8MI9Z4zkQ88CBQoUr3459cNXbB30eW9b0IwDULYu4QBAG1i3I9V8wbLEcTxJg0gULx6COJkWSeedLVba0vxXQcQKeMDfSNfTDMsgsMSZI4hDwTBa2MnFTMbc0F2tIKLMXe8bKHEctwHZRiBdWU2RROzRQRH1PO82tTQo6TO1CntrPeUTBBFW8HKOVVMF3Whr1yuNowsBMk1o1MGN05z6Ahf58yVDS3LY8yCoiorsIIUr43igBHLw8HiscIAYVBfQgVCzAANnMNa4oS0QkqwpCSrXZSiTELxMGWZYD3Kyrqv2gTxvq5Umpoui03agzOr40busa6M%2BobW9BssyFCsfA6CGSsi6ue5MAFlPHQN6mLlFiD3C5d3hupFaDu59IeUm1SIJpc1MLf6tUebSmWpkz3J08lMAmMdae1Gm2exALTSBV4wXos4LjoG4ozM/LgaYC5UCOABJL00sleHFqIBhbnIxq5kcZBhwEBlVDSYgjnFogjhO7x6OVGWix6v7Sbp7EKuJPAsliegLGuckAHdJZZwLmzCqzhqOAA1MRZfFSVVQdp2Xbdz3soLMqWg1rWGB1vWjliVBPGN07WOhhrg9oY6c5OMx/COMw0zajRrc09SbdZnSI6JR28GdzBXfJBB4sZfyzV9oaMaDkOUuuyPW%2Bjzvu7jq7E%2BpZPU/1jOs5Ns60eVAui9Nkuy8CSvAnTavLbco%2BtI8pyPp7jm%2B%2B7YHe2/WyofK8%2BXPrymPOwVRWE5S/mWv4KQeGgOR4xBgCQwBNROGVUmBUC8CCRob0vI%2BWBk3FubcO6eyvCgqO7c3Zd0wJZKGyl4a0HQBCYBoDSKvwgbRIQXg0jFBdBWD6vo2rP06sBNwCsloCFuGcLgaEjhcKVrwtwZgBFCJ4RCLg/hur3Frs8J41CjhMMMiw/egioEwLgTkNsnCBDcOVlI8R%2BjhFSLEfhQRJjJFnHMZJSxitrFuA2hYiRhi%2BEyJAp4/qqVLTUlhKOBIBAIDfGUgoO0/jkpuBUbQAgV5aH0MyIwxmqi7iXXzBwVYhcOD%2BF4H4DgWhSCoE4BxSw1gjgKHWJseiQIeCkAIJoDJqxHQgDWhoAUZhFT%2BEVIqaRGhAhrS4FwMwSQ1r6E4JIXgLAJAaA0KQPJBSikcF4AoEAsz6n5IyaQOAsAYCIBAOsAgaQLjkEoGgDkdAEhRDtJwVQAAONaABaNakgjjAGQJrKQ7TeAJSIMQPA6A9D8EECIMQ7ApAyEEIoFQ6gNmkF0FwUg7tERpE4DwTJnAclzIaYUzgP4LhHN9KgKgRw7mPOea895RxPkVwgB4c59B9a7C4MsXg6ytCrAgEgM5MoGUnIgNyi5iRgBSDMHwOgbJiKUFiNi2IERWjXFRbwWVzBiDXB/LEbQlZ1m1LOQJH8DBaAKthVgWIXhgBGloLQFZ3BeBYBYIYYA4hjWzS1cSRm2LMCqErBcbYtSIhsiyQUq4sRESqo8FgbFCI8BTJtaQWsxAM5KEqvaowVwjANNWFQAwoDA7eXdj%2BPkiqIXCBpGC6QQL5BKDUNi%2BF%2BgHUoGsNYfQrcVmQFWKgNIjRrUPO%2BAxUwpTLBmAWfGv5WBW0QFWHYV1zgICuGmH4BFYRcyLFGAi4o2QBDzr0OuxoCwRiJARVOhwfRJjtE8J0PQR7Gj9DaHuqoq7bCnq3Ye09d6ljMrWBsLYEh0XZNydixZJL7lPJeW8j5kh2lHAgLgQgJAS6BGZayjNqwAJMCwIkCdpBmmSECAKJIgRFSSA0JIMwkhWkaH8GtVIWSJmkCmQhgUAy1q3KSLcrga1/CSGkfh0Z8zeCLOWasupGatm7M5fs/FxyKD8tQPSy51yOCtBYESRUDymAbgdVSpIAouACgKT8kg/zAWyBBeIcFFaoXVthboUVSK9KKt/ZivjOKOB4sORcI4RKDbEGU6p9TI5kxcG07pjQUG6U8oSPBswLLhMbI5Vy2TEWyDSYFQykASmVMPIC8KpIXBZk0BiYBKVMq5WqqLcq%2BV6rNUOCLbq58%2BrDXYpNWai1Vqi12odU6gp%2BB4rHtrNa/TXqqxsiLf6%2Bo2Lg2huuOG7YBSo0xtqfGxNmBk2dZoiJrNTAc15oLYwItFbTNluLZZmFBSbN1vTf2qwlhm2xHHe2ztORu29v3ld6wQ7%2BMjv%2Be6ttPRp1%2BFnQwV0%2BQF0hCB2%2Bh9O6cjPvSJkDdDAIcHr%2B8egQN6z0g8vfUf7aPEeXqfeegoL75jLv3T%2Bz9VSydZKcwBzg3nfNqY04F4LemoMwd%2BfBxDsX2UocwGh0YmGaOTJAIEbTxHOlJG6YEEjZGuNYthQJ2wQm2WbO2Xsg5BK%2BWpfk2wTgSnyUsAUESTWRIgsChbBMb5%2BBflGYRQd0tEhy2yBOzW4XiLkUObGX%2BuXCzcWScJcSvXLyDdG%2BNqb83y1wuCvg4EGLyv4soES4KzXie0tG/obCE3SRYTh/8T555YrCuSogNK2FFWyuxrL2qjVWrauyb1Qao13XMCmvNWINrsaOuptm7al1fX3Wws9d6kbsaxuBt4JN%2BVM3I1/IW7wJbiTVupvW3Fvg2aFC5swPmwtsa7egod8dqtp2dCu4MJdxtN3g33cKY97WnB0QhLe4O4dCRR0/cw1enILggcw6XRUUna64dGgYcocygSd70kcP9Ud8cMdD0scUcmhX0wD31H0BgYc5hb0kDV1J1Klv0P0qd/15dadA8jhg9jcw8LIJhWcrc4MmVY9kNSBUN0NKBf1aMplhkBRAhAh/B/BiM8s%2BkCNmNvd%2BNOBBM1l6DmkRcBRFRSMzAzBblJARlAhblblFRiNPdAgCCfclkudGlPczBNDhDtC49Vh40shnBJAgA%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/sieve.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/sieve.test.hpp)
