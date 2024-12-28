<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Reveal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-reveal">To Index</a></p>

## Description

`Pagelivore::Reveal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and becomes its type result.
Overall, `Reveal` turns a `Typical` operation into its non-prefixed counterpart.

<pre><code>   Operation
-> using Mold&lt;***&gt; = Operation&lt;***&gt;::type</code></pre>

## Type Signature

```Haskell
Reveal
 :: template<auto...> class... 
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class...> class>
struct Reveal
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will reveal `Operation`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Operation ****/
template<auto...Args>
struct Operation
{ using type = Shuttle<Args...>; };

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, 1, 2, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Reveal<Operation>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Pagelivore::Reveal`:

```C++
template<template<auto...> class Operation>
struct Reveal
{
    template<auto...Variables>
    using Page = Operation<Variables...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIEAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMgTcoPB70wULcTC8RAAdOiodhbsgDAoFLcAPJpBLvHKY4ETYheBy3ABKmAAbpgxMCTAB2KxXW7c26w57wxHItHogBqrTwTFi9AU5K5PK8WSMt2UTGAmFuUIAIoTicRSQJEWLiBKpZgFOjUZiQCACABPYlQzlAtmax2sn7/P6A357W7YVSsZ7qr7An2es7uoFmQIRHFeLAa6FoBhbNIEGWBbCRn23IQIFEEeifCNXPkQhHQoWoC2yy6U6kEXP5giFitO0NHHUkj4h0tg/mQyso6voy7EYAZrNXes0ondslXdkWW4KiLAXn29VapsF%2BiIscTmuZx0al1uxceu5CLxpYqYdD0hReWiN3uXVdK6%2B3zL3x/Pxvbnmu4Vm4GikLcXDgWYUHkoE7aXgctwALKYC0VBeCmPYliC/bloKw4Wgek7Ah%2B64oWhGEODkibavSTIstCc56o0tbWiqar7uO5oYsecHZp2f4vsWByAqRdJmv%2BNHIahTDoZhZLQmBEFQTBvHwdcnYACpmq%2B2FzI4yAAPpMHiCQEBAEzoNaCisJgxkZm4gkEOBX53g%2BEkvpiyyOhwqy0Jw/i8H4HBaKQqCcG41jWLcCjrJsW7RjwpAEJovmrAA1gEkiohoAAcZhmMkyRcP4eW5VwbJstI/kcJIvAsBIGhgcFoXhRwvAKCAYEpSFvmkHAsAwIgIDrAQaQouQlBoE8dAJFEtmcKouUAGwALTLZItzAMgyAQdlZi8PehAkHgVmQfwggiGI7BSDIgiKCo6i9aQuiQQA7nqaScDwfkBUFqVhZwBIouNjaoFQtxLWtG1bTte2omYtwQB4M30MQGqJcsvA9VoqwQEg01pLNZAUBAhPEyAwBSNBNAvgknUQLEAOxBErS2t9vAs8wxC2gSsTaJgDgc6Q02vAQBIMLQ7PPVgsReMASK0LQnXcLwWAsIYwDiDLeDEILjhMiroWYKogsotsSURKCNWhbQeCxHqPMeFgAMEMaDWq6QTLELEP6amCmt20YqWrFQBgTiKeCYG9c7BUlF3CKI4i3QnD1qADr36JrKBRZY%2Bj251kCrKgaY5Crq2WVqpiWNYZitd7xpYIXECrHY%2Bs5C4DDuJ4nR6GEETDFUoyQcU2QCNMfgj5kY8MAsIyJJBbdUQI/RTD3BSL/U7cr5MgwD4sw%2B2LvE96HMbRz0PC%2Bt3FWwSL9HCBaQLW8G1kMretm3bbtUgI0juDHejcwgQuBY2SiHVYCBmRYESC3UgmVJCBFRMkQIVUNCSDMJIZaTV/DLVSDVOqpAGrANRMtLgy1crJHKstfwkgSrIOWk/AGbUOpdTAb1PGQ18YjRBhNUm5M0bzTYJwVoLAGRslWkwbEBglRcGSKiLgOVDr4CII3PQCcrrJ2kKnJQ6dnq6Ggh9JgX1Vb30fs/QGHBgZjRRLccGb9oabRxJrCCciFEaCRijImaMMaBDMKAnGfUuH8ISJNMmqBUajCcUYWRXAwK01BMQBmTNnpczZsLVJPM%2BYCyFp7UWjBxaS2lqFWW8tFbK2FurQO2xim63bobAGJszagmFlbeoAM7YOzZs7ap2N3bC29r7JQ/sNZGCDqAdhfBw4KEjtHWOwt1FJxulo2QacnqhX0VnYO1crB5w6c3YupcBDl0roETU2za71wSI3M08BW5b2Xn4CArgT6QX7hUeeehR6NBeekaejQL5LE3r0HeAwflL0aKvPe7zL6n2PuvSeR95j7w%2BSAtYGxb6opqmYphnB7Efykc42R8icp/2USQHxIDsbgNIJApg0DKD3wIUQuRaC2T%2BGSJVQI6DMG0MYc9ZhthWEBI4fALho1QahOCcQQR2wREwxYAoBku0GREvLBMJRADTpqNkBopZd15A6LWToJIpBDHGJ%2BvoP6fLWpAx4WDCGqh5WKuVaq%2BEEwPHhK8QkHxgR/Eh36gTT1xNJVBrRiAJVt5DIquSIZNVBBDKOq0XQBJSTmasx5uk9NvN%2Bb62FnkwQEspYAxKQrMQ5TPaVNGT00g%2BA9ZUXqc9RpyBzYtMEG056HTHa2m6a7PpnsBl%2BwDqMtc/qw6qmmVHGOxI468AWddCQyz7qGozia6Rxhc42D2bcsKhyGAqx2JZHONdLB1xfg3U6Nyi49G3o8558K%2B5dwBYfL5OQfkvrKMimFQKb2QrBfciFu8n0L0RWvfICKz5QsHoC6%2B6KbqmP%2Bvy3FibbgKqVbcaNqI42koARSv17CIFQNGLA/B9UQCFVRIEQI/hSq0KapRtk5DrUv04Cw7q1L4H%2BCQRVNkTVcqSGKlwfKZgGE1UCAhm17U2G43vgdJjFiqX4a9vTDukggA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/reveal/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/reveal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/reveal.test.hpp)
