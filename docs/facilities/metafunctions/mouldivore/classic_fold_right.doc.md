<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicFoldRight`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-classic-fold-right">To Index</a></p>

## Description

`Mouldivore::ClassicFoldRight` accepts an operation. Its first layer accepts an initiator and returns a function.
When invoked, the function right-folds its argument list using the operation and the initiator.

<pre><code>   Oper
-> Init
-> Arg<sub>0</sub>, Arg<sub>1</sub>..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>,
        &vellip;
   Oper&lt;Arg<sub>n-1</sub>,
   Oper&lt;Arg<sub>n</sub>,
       Init
   &gt;::type
   &gt;::type
        &vellip;
   &gt;::type</code></pre>

## Type Signature

```Haskell
ClassicFoldRight
 :: template<typename...> class...
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct ClassicFoldRight
{
    template<typename>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will right-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   1-(3-(4-3))
-> 1-(3-1)
-> 1-2
-> -1
```

```C++
/**** Subtract ****/
template<typename A, typename B>
struct Subtract
{
    using type
    = std::integral_constant<int, A::value - B::value>;
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= ClassicFoldRight<Subtract>
::Mold<std::integral_constant<int, 3>>
::Mold<Args...>::type;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>
>;

/**** Test ****/
static_assert(Result::value == -1);
```

## Implementation

We will implement `ClassicFoldRight` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct ClassicFoldRight
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<typename...Elements >
        struct Detail {};

        // Base Case:

        // Fold once.
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Element, Initiator>::type;
        };

        // Fold twice.
        template<typename First, typename Second>
        struct Detail<First, Second>
        {
            using type
            =   Operation<First,
                typename Operation<Second,
                    Initiator
                >::type
                >::type;
        };

        // Recursive Case:

        // Write out the last two folds, handle the first two parameters,
        // and recurse using the rest to obtain the initiator.
        template<typename First, typename Second, typename...Others>
        struct Detail<First, Second, Others...>
        {
            using type
            =   Operation<First,
                typename Operation<Second,
                    typename Detail<Others...>
                    ::type
                >::type
                >::type;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };
        
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIAAcAJykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkizp9GyCTE13xxfXt2f/Zx%2BV0uVwImGeBjBJn8bjBEI%2BmGhsIAnulGKxMAA6bHQ7B3ZAGBQKO4AeTRxA%2BuVxIMmxC8DjubkJ2WQADFPOgAEp4YAIAggkwAdis1zuYrucJeCKRBFR6LYjwYOQ%2BJGpovFtPpBDuymIqCIAFkOSDxXchSKrqbTZLIYiYbK0cw2NjMdhXowCMS1ZarWLNQyACKYVp0M3CoUB6EWk2%2Bu67XZ3CxMJSM5PsAXq33xu7s2joO4CbaYmO%2Bm3S%2B1yp2YO5u8Ee72xu7%2B7VBkO0JG1t78/zYEtW819xtebJGCVys3%2BAOk8mUgQd92CUiK5VEYi4kAgB12i2NiNRjM%2BrMJ3P5ggAdzwRcH4rLUIrjoxObwxEmS63VbuQkwaAY6AbsebO5WyYOgkVZZ9X0/b8BD/HtrzFAdM0bO5hwiYAxzReD%2B0ncUyQSWcGDAiCCFILDG3fR88IpJokS/H90FIpDkNjB4lUcFU1yY5iJ2wDctzI2N103OV9y4hDBUjfxozEuME05b9NmyAA3as3DTEAD0bbMAHViEIasNm1AgEGrQkjLPVA7n4PMFCXBBDHQegJRMqziIlCy7nSNoMTBF9GMPK1swcu5iAUl9q1Q0djOrULJglSzUFiEMGGc6sIhXEhixk287RRB8FXAl8SIw%2BVqzomC30rDEXRJaKX3/X1AOA0CYUKyDyt/JdapMl8XQa/twxk01IvQ/ihvFaEpzFKiCKIor/O4q0KIVGaaJhDqGIE5jlurZr2xhbqEgUPq4PG5i%2BJEs7sN44TMKu00hP4qSsL3Z7riwnKZSq51sSuYBQrrQQFH64aR3Qo08wnKc9qRP6Aa7Y6cR7C7MLegLXp3QSkM%2B%2B9SpdOHMEBz1%2BpGu4IfzSadT1Q1jRhAmicR4s4LRjGDz%2BAETiBdma1UVgXmrb4QXZjnzgPcx/AiAkvCwCc8swAB9AgKUIYHTuBX5jk/LwkopBlBeuHG5Y/K5Kvy6srDVwChG1pWmAcAVBoC0mxvRnDJnQDcIjBf6xHln95kEJEvaXK4NyUsQvGrABaRMw4ju1exZiTRPVm5NYNYMmCoLwGAcXIvlFg3wSlO8jeq37iGAVXe2uUmM9abPc8%2BAUcKZZMWRPbleW7NxrZ1u3uxr0OQHJpF3c9wRMB92g/YEAOe%2BDu5/GpNWN1HunK8Zx6RJZjX7nkhQvFobV9auUmD6P7VKfrrOc7zud3phPtx5AL2p4pGf/daQOYUXrhcQWhqAgHtX6T2nrPBg88g6LiXgA5%2BwCJ7ew/hAqBv8YGSG9CvaSad7gABVMBxVPvMRwyB5btwSAQCAF9j5x28NWSalMo5cBWFGDgaxaCcAAKy8D8BwLQpBUCcDcNYawTYNhbHoWYfwPBSAEE0GwtYABrEAnDJCYg0EkMwZgUgpC4JwjRSQuCCkFNIDhHBJC8BYBIDQGhSC8P4YIjgvAFAgFsXIvhbDSBwFgDARAIBDLpC8CRCgEA0DPDoAkKIGJOCqCSIEKOgRJB3GAMgZAdwpCYjMLwTA%2BBVx4A9lwGQggRBiHYFIIp8glBqHkaQXQhSzwUnSJwHg7CuE8JqY4kkQTAnalQFQO4sT4mJOSak9JaizB3AgB4cJ9BiBmikcw3g7itBrAgEgMJ6QIlkBCRsrZIBgBSDMHwOgvkXEQFiDU2IEQ2jImabwK5zBiDIhJLEbQ353EyLCV2EkDBaC3I8aQLAsQvDADUrQWgLjuC8CwCwQwwBxAAvwKFPOKlIX8MwKoBSYI7nkEnmY/htA8CxApE8jwWAalKzwFYqFpAVLEFiFkTAQZYVGEJUYeRawqAGCrgANTwJgM8eFeEyP4MU0Q4hymisqSodQAK6n6DhSgERlh9BEpcZANYqB0hNEhVHd2k1TCWGsGYBxdK9JYHVRANYdh3m5BcL%2BGYfhClhAiCMaoYxCklByAIR1egvVNEWKMRIhSbX32aFMDonguh6FDU0AY7RA3uuDbYCNvqQ0RsTcsZh6xNjbAkK0jg3C7EdM4AMuJCSkkpLSRkiZEBcCEBIPM6RKwlkcrWCZJgWBEhWtIMoyQ/hMQpH8CYjQkgzCSECDYzhgQ0hmIsaQKx0jMSBC4IEVIhjAiqL0UO4I9jeCOOca42RHKvG%2BLWf47pQTyCUF2bMqJbBOBtBYEpQUUcmD4gMKOLgKRMRcHUdk3JJB8l6ClSUiV0gpWKBlTU3QRyGlMCaVCgtRa90CM4F0ggPSCz9MGRWj9cL0k/r/RoSZ0zNmzKbWYFtx6PGrPWagGZCRr2hIY%2BRsYBI4Xfq4LYmgx8jqUAuQCh5NycXCaeS8t5DgcVfI9D8v5NSgUgrBRCnFMK4UIv4Ui21qKakYqxTsGRb98W8EJcSm5ZKdj8MpdSmRdKGVKGZeptCJ6uVMF5fywVjocWgfFWUiDsgoPVLlSAI5n7jDKpsKZy1mrtW5F1fqychqrCWBNfus1%2BSCHwGtQ0W1zgICuDTSEX8maPUZCyN6vIUbCievKwG11SxSuxv6KmqrTrei5fDQserQaY0tYKG1%2BYCbutJvzTmiRo2zEoZLRwMtQykkca/UR9Rkz62ribYsmjKz22YE7WMHtc7LEBB/aOwUnCUjGP8GOidkhCmoYPbYI9yzPHeL8QEq9OzWNbPvTsJ9wyWAKCUmkpS37MS2kmABht5qQOyDA35ipgXZX8N0P4Ug8HEMtP0G04tALOmXt6Thv7AOgcg7B9qKZn2KPi38NRp7dGUAU6Yx9xjiRAfpHSPLYHKR5ak/lqoRJxy%2BMvgE5c65TzROi%2Bea8950mGPfN%2Bf8zTmBgWgrECpmlanWWWehc%2BbTmWAV6eQEEgzvAjM1NMyS5EFmKV6Rs7wOzjLHOsuc7Rvg3KFB8oFUK7zMPfMSH84IBHMGAgKvZUl6wqrYjRYEbFuenBdjjzDyl01CRzWZY1e1sN9r3Ctb0C6yoPWaulFyIV/1uQSvJqawIeNkb%2Bsxpy2G6v5feuDEK4NoYw2s3WvEXm7Nk32k49LXzpJ/3Ad3E56DhEcU62AbmeLDbtPtu7e7QW%2BdVjtGYn8P4Th%2Bibs2M34KNd2OHGcEPW4ttvaQCSE4YOoxgobFJEkLorgmizDBDMf4fvx%2BnGbYUZjjgWSj990T8f8Vg1g6VshnBJAgA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/classic_fold_right/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/classic_fold_right.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/classic_fold_right.test.hpp)
