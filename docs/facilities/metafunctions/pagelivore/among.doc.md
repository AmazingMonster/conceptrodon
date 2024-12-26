<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Among`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-among">To Index</a></p>

## Description

`Pagelivore::Among` accepts a list of sequences. Its first layer accepts an index and returns a function.
When invoked, the function instantiates the sequence at the index from the list with its arguments and returns the result.

<pre><code>   Seq<sub>0</sub>, Seq<sub>1</sub>, ..., Seq<sub>I</sub>, ..., Seq<sub>n</sub>
-> I
-> Vs...
-> Seq<sub>I</sub>&lt;Vs...&gt;</code></pre>

## Type Signature

```Haskell
Among
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class...>
struct Among
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will pick the sequence at index `3` out of the list `Seq_0, Seq_1, Seq_2, Seq_3`.

```C++
/**** Sequences ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** Metafunction ****/
template<auto...Args>
using Metafunction
= Among<Seq_0, Seq_1, Seq_2, Seq_3>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Seq_3<0, 1, 2>;

/**** Result ****/
using Result = Metafunction<3>::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

Note that we must instantiate the sequence before the comparison.
This is because the function returned by `Among` is an alias template pointing to the actual sequence in the list.
It is not quite the same as the actual sequence.

```C++
/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Tests ****/
// GCC compiles.
// Clang and MSVC fail.
static_assert(std::same_as<
    Carrier<Metafunction<3>:: Page>,
    Carrier<Seq_3>
>);

// Clang and MSVC compile.
// GCC fails.
static_assert(not std::same_as<
    Carrier<Metafunction<3>:: Page>,
    Carrier<Seq_3>
>);
```

However, after instantiation, both of them will converge to the same result.

## Implementation

We will implement `Among` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the sequence at the index is returned. Otherwise:
  1. Drop several sequences from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `Among` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<template<auto...> class...Sequences>
struct Among {};

template<template<auto...> class First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = First<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<auto...> class First,
    template<auto...> class Second,
    template<auto...> class...Others
>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    {
        template<auto...Agreements>
        using Page = Among<Others...>
        ::template ProtoPage<I - 2>
        ::template Page<Agreements...>;
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = First<Agreements...>;
    };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = Second<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIaa4AMngMmAByPgBGmMQSZtIADqgKhE4MHt6%2B/qRJKY4CwaERLNGxXPG2mPb5DEIETMQEGT5%2B0naYDml1DQSF4VExcW31jc1Zwz19xaVDAJS2qF7EyOwcAPQAVFvbO7t7G2smGgCCm9sA1AAimAmujMh4mArnO4cnZ/ufu2/HR79mAGYQshvFhziYAW5kAoCOgsFQIdg/n8Pl80VsfqjzgBJFgJehsQRMGovbaY9EUg7Ik4ETB4gy0iFuWn04mYJlMLxEAB0vMR5xBTAUCl53KEmAAjl57k9EX8YcQvA5zscWAJgOCAOxWTWXCFWE5/Fn4tlM40M9mQzk8vkA7ACgzC84AMTwxBhcpOCqVBBVaqMTNd7oInt%2B2r%2B50j53NpshKQAXpgAPq%2B7GhqPnb3K5TEVBEZRMYCYLU6vUAg2/E4ZmOMuN4RMpnHpqPESVeN1Pc4QNMAsuXDSzCNRrO%2BnN51AFotMntIqtRkzhucZyM1y1ua2oUXHYCtumMAgKZvL85eFJGc6T4sQy4ut0eyHb3eEg%2BiuXloeRhdlisf6N0k21uuXKbryj6YHugiHnav6niEGqXuCvYXrm%2BaFmuYEQS%2BtpIu%2Bhq6vq1LHKuyKQr%2BxFWsBr52g6QrPEGMKkGR/4WhylHYTRTrimgDDoIxS5/qygEblR9qCsKooAPIEAgMSHoa0FegQirKqq6qBneBCkOcXECLx5xSTJ7oicii7HNWzGxm4CbJqmR6ZkpPrIeOCG/guFbHiuFlCWx3IYc%2BUGzmZHmweeLlIapAaQgZsnGfxGYgCAq5OahU6Qti5wALTnGYdnxYlXnFpeTJ%2BfuIrYQR/FfhVlZBZ5glrtZjYzr%2BrZSh2zzdte14Dr%2BI7JROaHTnZbm/uZ9WsTavk7uB/m5VGIXwWhiE3vRIYPtNmFldyb7ufO%2BG4TVY0AQ19Y2U2Cm1ecrXtq2HU9n2XCDvxfVjila7NZVpkeQJx0TSBU1PqVc2RgtF5Lde2kdLpxUbf5xkHRmVUHUx40UZNJWQXZoNhTer0DalbgY1h23Qcj%2B0/u8lJouSFyrec2CqKw%2BLFq8KJU18PzIoCwKglekLcSsCQHqGbMXOKUoys8rM0gVf2xccfXi0mGjVUasto/9oaK5KSZcKrMuo0Bk1aw5ypKzlyMG79Gvy9rEpJgC%2BunDs5wALKYPUVBeAwnQCKSGJq4bwmgcQwABX8oPu573u%2BwwJE3hFwBMkrGhaUrXBpzrZiZ/bjsXQlRUPqHW07YRWJCF4CS5Jg6AAEpPF4tC%2BtLxygxXVfJDX9cKI3voQ0reduKn5wZ9lpeGpTFzd73/tUicoPT03y1ux7TBez7NRMnn2AF4NkLD6PFs4RTzsXAAKk8zdkvK9SOMgSa0TEBAQDC6AJQorDJkKTKL5p2mV9XOuDcm6IkHJbU%2B7N9g0y2JDbi6B6aM3pCza%2Bk9IF7E5qgjY5x1zEGII8Ygs8fjkWZOrI2mtqJiRLhdPqOC8ExCdliC%2BMIpYoNOGsc4ABxNwbgBSoDxHQJ4213jsLcAYc8hh4GuyEAANR4VQJgdAhEK1vnge%2Bj9Ggv1hO/T%2BD8oJuF/LQ/BTIo5rxjpvSE28Epg1StgPil1DH0MhAPEWdowEnzWCIsRGoJFuxkTwtA/D6BKI8Zw7h5x5F0BFDfYkqjdFKA0QwPM9k34gA/mwXRTIDENDocQYxq916xy3oiKxhdbFZNwUYpxOtt4kWwG4jg8xaCcAAKy8D8BwLQpBUCcH0ZYawmZFjLCvICHgpACCaAafMAA1iAZpkhuQaAABxmDMAATlWVwZpSzFlcE1JqaQTSOCSF4CwCQGhU7tM6d0jgvAFAgFTuMjpDTSBwFgDARAIBFgEASFycglAAkJAEcQMIn9OCqEWQANgyhCyQ5xgDIGQCPeZZheA10ICQPAb8M78EECIMQ7ApAyEEIoFQ6gnmkF0BnAA7sQJgCROA8EaS0tpEyumcAklyH5vpUBUHOOCqFMK4UIqRdyMwXYPCBJiOCEZsxeCPK0PMCASAAVAr%2BRAFV9BYjACkNnGgTdZKUEiKyyIIQGgAE8GW8BNcwYgZqJKRG0B0R5oyAnPgkgwWgFryVYEiF4YA65aC0DudwXgWAWCGGAOIb1HZOgADcnisswKoDoXJVijJCLSQ5nTaB4EiLS21HgsCsqUngU5IbSDxuIJETu1xw1GBzUYCZ8wqAGDDtIx4VKJK3HaaMnFwhRDiEJX2klahWWUv0BGlA1hrD6FzXcyA8xUBCzSMGjKr9rymD6ZYMwVzK14KwPOiA8x2ixxcDxMYfgM5BBCP0EogwM65FSAIC9ehH01CmAMMolRqhdBGE0TwLQ9AnpqN0RoH671fphD0F9GcoNgZvdMe9x7BkrAkEyjgrTSCXN4NcvlkLoWwvhYiqQoquy4HRQQ8wAJHpyqbfMGSTAsCxCPaQGZkgATclWQCfZGhJDxAhec5pELVn6E4Mc0gpzqPcghVwCFizVk7IhXMzZXGIVYdZdc259yxlNpee8pVnzOW/IoOqvhgLNUgrYJwBoLBY2agykwGi54uCrO5FwBZqL8BEH3XoPteLB3SGHUoUd5LdDZxpXSy16HMPYbZRwDl3yuTnB5XhgVsLBTOdc%2B5jQ4qzNAulQCMwsqdNPMVcqvLmq1UasGBl7VGzU56tpO6Q1xrTW2staQa15r7WOocB111%2B53WetZT6v1Aag0dbDRGqNnT8CtjjQm8lSaU20g6xmqorKc15vNYW1YnSS1ltGZW6tSha3TbgrplthYFDtswJ27tHW/MDoJYF2QI6yWdLCxOxtm6rCWFnZEQ9i7l0CFXeu3sv3rA7pw3uzFCaF3fqdWkM97gANZCvTxcDMwH3JCfekNHl6ci4/fQhz9QGqhI4EKB/9mRCfAd/ZMUnEGgN/pg7YP9WOkMLCWKhx6omMMsvJbh/lBGnMahc25hZZGvMkAKzRkrCr6OYEY4MFjhzxOSdc7xzUzTVl7IBHxyQMKM6xc07YbT8rnmvI%2BV8rlVWKsxEs6sGzgqWAKFjYi2NEuLQwk8xRzFvnZD%2BZe0S%2BQwWPs6BAACUgEX6Uhui4Lq57KjPct5aoV37vPfe7ZDCXLkrKOAgBMVy3ZWUAO7ICZ6rsQPdVyTF71ZSYfcECTOnwLdAmt3IgEa8lXX2vlt73ah1Tr%2Bt8LdR6r1s3MC%2Bv9WICb5apv1r26GmNjh43Bs6ct5Aqa1uCA2%2BSrb%2BazW7eLXgw7vBjs1rpOdxtpW%2BCtpux2rtjBHtB%2BexIV7xLw9jqj994w07/tbZA5dIg4MDBprCvxTpboWDQ5dKw4HrwDHoU6noQCuBs7XpFBk4455BpBs5vppCc6QZIEgas4E7k4/pU4c5M7Y7s7QakGwaUEYHM584KAoYEoJ7qZC6cB8oZ4e7nD17chN7S4UZy7F50akAMZMaUDoYa4gBrLcgAgAjNJbKSBcDnIKGahyYcFJ43Lm4PJiFsbNKca7KajnKLKSAbJcDLJmBqaHIAiJ44acC0alboYopaEOE6El7zCVopDOCSBAA)

## Links

- [source code](../../../../conceptrodon/pagelivore/among.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/among.test.hpp)
