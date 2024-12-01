<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Graphite`

<p style='text-align: right;'><a href="../../index.md#identities">To Index</a></p>

## Description

`Graphite` accepts a `Grit` and returns the `Grit` via member `Grit`.

<pre><code>Grit -> Grit</code></pre>

## Type Signature

```Haskell
Graphite ::   template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
           -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
struct Graphite
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RESULT;
};
```

## Examples

This function injectively maps a `Grit` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Op_1 {};

constexpr auto fun(Graphite<Op_0>) { return false; }

constexpr auto fun(Graphite<Op_1>) { return true; }

static_assert(not fun(Graphite<Op_0>{}));

static_assert(fun(Graphite<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Graphite<Op_0>) -> std::false_type;

constexpr auto gun(Graphite<Op_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Graphite<Op_0>>()))::value);

static_assert(decltype(gun(std::declval<Graphite<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Operation>
struct Graphite
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Args>
    using Grit = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAnKSuADJ4DJgAcj4ARpjEIADMABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyZJbnsHR5gnZ/uHTMen53cPNxf3V4%2B3l9dP348AnulGKxMAA6cEnbAAamQBgUCnBoMhMLhCIhSWhsKY8MRyKxOPRmNRuIxKOxCihAHkgcR7rlISYNABBSbELwOKEAcVp6QQhCuzJMAHYrMyoeKob93j8vtLPm8XlLFbLlQqPmdAcC2CSieSdWSCUjSfi0UbdYa8cTwUziMAFAyxRKvNkjFziIQoScACJUml0gTXG12nUnUVM4Ve0OM8PMgD0ACpE0nkynY9GE0moQAVbBCLNCKHJtNxlOlovR6NK9VVmVq2vPasqxt1gFA5jawkG02WvWdk36/t9q1m6Os9kEX0AfQ0npFEajguZNflDfrf1eq5X6%2BXGrbIIHw57FuNh5PvbNXZDzLHHOpk64s6sQsjSTD6eTUIAYnhiJNs5g/3LRcmTQBhJkwVR0mIKEmC8IgoSoLwGAgbkmF5flrjvDRIRWR8oWITACE2BgELEJRQ1nSNgNA8DIOg2D4MQ5DUPQl47y4HC8IIojiBIgg2Q%2BCxKIra9WkcZBJ3JBICAgBhUAnJiUJ5Pk2PSacGTnZ8VhWBcYxZMS8AkqT2moJClLQlT1XYjSny9bTdPfTMhEwUD0H/QCk2LPTzCSCJYS8LBPVOOC6EIf4HT0mi9jomC4NQKFgDMljLMwtTsIxXCAFpkUmdAQBAKgyMwScCE1BzmSiiCoNi%2BDEuY5SMNOayMqhbLSVy/L%2BK8YrSqBcr9LpIz4Wk2T5KhLBYV6zBoDMjqQAm2gADcxGuZLGrcLCGQxCBtJWfLlu8TAdNfESBvEyThpMhappm5C5oWg7Voa1T7y27Adu0/axG646LA4NZaE4ABWXg/A4LRSFQTg3GsawoQUDYtkwT0zCSHhSAITR/rWABrEAgckUENEkLghSSDQgY0Mx/H8MwUjSQGOEkXgWAkDQNFIMGIahjheAUEAOcx8H/tIOBYBgRAQA2Ah0jg8hKDQA46ASKIQU4VQUn8TL/EkBLkGQKEpFBMxeEwfAiHdPKuBkQQRDEdgpBt%2BQlDULHSF0a2AHceU4HgAeB0G3Z5yk4NlidUCoKENa1nW9YNo2zChCAPCV%2BhoJ8rgVl4IWtDWCAkEV9JlbICgIEL4uQGAKQzD4Og9l/ShYjd2IIjaf5fd4FvmGIf5KVibQXKF9HFbYQRKQYWh2%2BF0gsFiLxgDcMRaH57heCwFhDGAcRp/wAiHDwRaALdiCXLgnZ0YiPZGYh2g8FiWke48LA3f4vBWdX0hD%2BIWIskwL19k3rfIwWM1hUAMHaAAangTAntqSMA7k7O24hHb8EEIoFQ6hp4e30JvFAsNLD6DvvzSAaxUDpCaCvTKuVvSmEsNYMw3Mv6WyPiQ3og9cguAYO4TwXQ9BhAiCMaoYxrYlByAIGYfgRFZDEQwRYoxEjWzsOwgQAxpg8MKIohoyjmhTCGAIpYwjbC6IkXoeY7Q5FCIUWsBGmxtgSH9hwEGnMg6cCjprbWutgD60NoTROEBcCEBICjNGWcMYgLWAgTATAsCJB2qQPGkgkigkCEkIUkhiZmEkP4dmQMeiM2ZqQVmaNQT%2BC4P4FIgQUhlIJlwIGKT/DOOnjzPmAswnCzzhLfOUtQ5y1LuXNOqs2CcDaCwRaQpMpMDJK6LggRQRcCJqbc2JA8BW0QaIZB0hUHOwwW7XQNdvZoQ7g4pxXNeDBx6eHSOIyxkTKmcAQ2sz5kzmTqgVOCRglmFCTnEWXT%2BkJHlmXV5Rc04gGueMrERgZlcA5jQWg9d%2BYQCbtPLubcEEop7n3AeDgEEj0YAQcek83az3novWgy8EHr0ATsCGu92GHxXhDE%2ByAz4IMvg0N2t975tyftS7O7p37oy/j/JQ/8N5GCAaAdpfBwEKCgTAuBYN0ZbKQQ7TZsh0GuywSAGuBhgG0KsAQzlxC4lkIoZwKhBB0A0PwRYBhZymErJYXEpR%2B9nAQFcCY62/DKjyL0KIponqMjSKaBY5Ymi%2BgqOMeoyRbDXU6IWPo31iio0FBjWYvRPrLH2PWLYh2xzA5NNcWC25EL7kzLmUTJOASLbBMztncJpBInRLGHE/JLNkizOJkKOpQoyaSEyTra2pzIacBaYLEBotOlIGlmHAFfziCDJ2CM2OLAFCLQNotctlxJiLMCZbPQyr1mqqdhqzBENdBJFIAc9IRz9AB0adzTgIcZZwShBHGCxAWArrXRurd7w/wvLeenVGSQvkTt%2BUC4uc7IMgvXekNSm7AiTm3QQSSn6da1zhQkBFSKIboqnujfDmLB44teaPfFE8p40swHPBeS8V7o0peK3lM8fx0qPtPJlLKP5suvrwTlD9/g8pfvyhBQrf6isARESVudpVMEgdA2BbYEGHvthINVaCXZnp0MkHBeqbWENiMa0h5Dcgr1jB1fV9DGEJGYcZ2NTROHcNTXwrhobDH%2BtyIGzz5RE1ZvDdo1RHRo2mK0XGoL7mFFGMGIG9NkXs02KRtmxmJyXEcA/V%2B3Wq711QkQ6CFDValnAZCfW9pESokxMoA4gprMzCzKSEkIGlMSbswa0KcpD6zmjtsK0752l4kgEkEDZJQMUjU0CJIQIZNUlcEvYzJIBbH28zabnBxJtOsjuW31tYX9sjOEkEAA)

## Links

- [source code](../../../conceptrodon/graphite.hpp)
