<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Coy`

<p style='text-align: right;'><a href="../utilities.md#coy">To Index</a></p>

## Description

`Coy` accepts a `Cool` operation and returns the operation via member `Cool`.

<pre><code>   Oper
-> struct { using Cool = Oper; }</code></pre>

## Type Signature

```Haskell
Coy
 :: template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
struct Coy
{
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool = RESULT;
};
```

## Examples

This function injectively maps a `Cool` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Coy<Op_0>) { return false; }

constexpr bool fun(Coy<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Coy<Op_0>{}));
static_assert(fun(Coy<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Coy<Op_0>) -> std::false_type;

constexpr auto gun(Coy<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Coy<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Coy<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Operation>
struct Coy
{
    template<template<template<template<template<typename...> class...> class...> class...> class...Args>
    using Cool = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGzSrgAyeAyYAHI%2BAEaYxCCSAKykAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3MDQa9MJDoSDHnCETDkeCoWiwfDMUjsaiAJ4pRisTAAOgpkOw12QBgUCgpZKpNLpDMpEOptKY9MZzK5PPZnNZ1wA8sTiK8slTAWNiF4HNcPATASYAOxWC7XLXXLEo3GwjGIg04o3ok26w0EIkkti8jks7lspn2/lOvmsu1Cx2M87EYAKaWa7VeDJGRWoTzXSEAEVF4slAgRvv9nshGoBqujaZVX1%2BeY%2BgO%2BO2uADE8MQxtdsKpWI9MO8ToX883/k2bmK4gmGAoG3t/hbzXi9ab8fqzaih5brcxbYKHQLnV6F%2B7vXPXamLrL5QQ4wB9DRR9VqrMQ9OAgcT42X8dj0cj4dW4kz8lrj2v1eL%2Bdul1vxcyghygqYq7lwh5WJm2YXG2ezXFQXgML2Oz/Gg3bAqoKTENc0QRrQsHwRASoIsBGhUosYHXMQmAEGsCFUGIShpoeWZQRcKFjJg6GYdhkZwQwBGoMqULAVwpHkZR1HEAhAFeDiFhMTmlwHNcAAqmBjD2Babk0jjILujpxAQEAMKgO68fxgluMR0pHpmiyLJB5wzDpen0gZ1D4YRQkpCB1ngdGdkOdBza/P8RbXEImAoegVY1qC9aaYpwV5q2UFmBCYS0l4WBRpi1q7gBTCEAGHIKWFwDwYhyECOxnHXEwXhENc5V8Z5lneSRHJkQAtMyYzoCAIB0bQSj5dagWsdVaEYXVDWoE1HkCUR3kiZ11w9fafUDdJmCjcS42JTBqnqZV/6Srp%2BktEZJnXFgtKPpg0D4ZtIC3bQABuYgIq1VklRyEB2YsA0fd4mD2aep3ORdhmvfdj18c9r3A19i1eT5v3YP9dlA2IMlgxYHDLLQnCJLwfgcFopCoJwbjWNY1wKKs6z1uYEI8KQBCaATywANYgIkkhkhoAAcZhmAAnGLXCJMLQtcKqqrSETHCSLwLASBoGikGTFNUxwvAKCAmsc%2BTBOkHAsAwIgICrAQKQNeQlBoA8dBxBEpKcKoQv%2BF1gRNcgyDXFIZJmLwmD4EQxB4P1XAyIIIhiOwUix/IShqJzpC6DHADuEopJwPCE8TpPp7rIoNXbO6oFQ1ye97vvAP7gcC2Y1z8c79CYSzXCLLwxtaMsEBIE7KQu2QFAQMPo8gMAUhmHwdDAhWlDROn0RhM0BL57wa/MMQBIitE2iRcbbNO88BAigwtCbybpBYNEXjAG4YjDVvd8goYwDiLf%2BCUQ4eBvTUunDikUGqbDZmEYESsKa0DwNECUe8PBYHTgBPAatuC8EAcQbCShowfyMLAownNlhUAMP6AAangTAWcOxkzZvwOOohxBJwYSnFQ6hb6Z30J/FAtNLD6DgQbSAyxUApHqAbDgXU%2BoxlMJYawZgdZYMjlgIR/0ujHyyC4Bg7hPDtD0CEMIgwKjDBjoUTIAhJh%2BFMekcxDA5hDHiDHOwGiBC9AmLovITjaguIaOMfohj5gmNsH4yxegZgtHscYxxywGZrA2BIQuHASZaxLpwGuXsfaSD9gHIOLcIC4EICQKMaVu692IcsBAmAmBYHiGo3mkgIRkjFhCBWGhJBmEkP4DWiR/Bi30JwFWpA1aszJP4Lg/ghZi1lv4fmUtmn%2BBSbfXW%2BtDbs2IWbS2g9rbl3tuPSeHc3ZsE4M0Fgb1VRdSYA6MMXAxZki4ILUO4cSBRz0Kw%2BOzDpCsMUOw9Oug545yYHnDBiTkna14KXHZldq610yVc4Agdbn3IPG3EeHdikQjMD3NZJsB5D1QO3OIDsJ74tRcMLkRgblcE1jQWgi8DYQBXrfHeG837Mr3gfI%2BDg35n0YBfK%2BN8Kb30fs/Wgr8MHvxYJ/b%2BgrywaMARIimIDkBgLfpA2o6dYHwI3kgzYFNUHoLZlgnBmA8GSoIWEUAOK%2BBkIUJQ6htC35vKYYnT5shvlp04SAOeBgiGyKsPwzVqiRFiKyBIqRBB0AyL4RYBR4KlFRyAcI9R/9nAQFcKEmOBiygOL0GY%2BoGbUg2PqJEhYXjuiuJCR4qxyb6huP8dmqJYTK25GreE%2BtRjS0xMZvE7u/SknFyWWkmFvtyXwpuXcwWrcCkR3RaU7F/cKlVJqZQRJgzhm3LaaqRIYt5YQnaZ0yQMcwWU04Cso26zzZWxthXIl%2BzXbuw4Cc32LAFBvQDm9cd2IxiPMKco15sh3kuuTu6jhFNdAQlIACoFBc%2B2gtSRwMutsGrXCrjXZ9r732frhJWFFo90UQixX3U2Wy71j0diSqeb6UjeQ/WLXcX6CC7lUJ0GldLl6r3XnvVlnH96H2Pty/F59L7X3TkKp%2BL8JFsywGar%2BureC/zlUA2%2BSqVXirVdA3gmqEEEh1SgyOBrMFxGNaaqVFr1mkKYBQqhNCnyOoA86iQrrBAgd%2BSACDPrjDRoEdEINlMQ3VU4FsTafr5GKLiMoxNajnEpr8Gm7RBas0dqCXmrIBaUslACTmstPi60Fui7WvxJagltry4VzLjbe2xKZgk2DA6dZDvQ2%2B64tGyQManU8zuJTCPlNIJU6pww1FKzXV625EIISJGloejWY3VQTMWfVvWthVlEbsqQepiQmly1VBrIWkhJZcBFmYBZSsIR1fBae%2BdXM%2B0h3m%2BdxbK3lhYIyM4SQQA%3D%3D)

## Links

- [Example](../../code/facilities/utilities/coy/implementation.hpp)
- [Source code](../../../conceptrodon/coy.hpp)
