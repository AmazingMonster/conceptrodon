<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Gry`

<p style='text-align: right;'><a href="../utilities.md#gry">To Index</a></p>

## Description

`Gry` accepts a `Grit` operation and returns the operation via member `Grit`.

<pre><code>   Oper
-> struct { using Flow = Oper; }</code></pre>

## Type Signature

```Haskell
Gry
 :: template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
struct Gry
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RESULT;
};
```

## Examples

This function injectively maps a `Grit` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Gry<Op_0>) { return false; }

constexpr bool fun(Gry<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Gry<Op_0>{}));
static_assert(fun(Gry<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Gry<Op_0>) -> std::false_type;

constexpr auto gun(Gry<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Gry<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Gry<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Operation>
struct Gry
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Args>
    using Grit = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGzSrgAyeAyYAHI%2BAEaYxCCSAKykAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3MDQa9MJDoSDHnCETDkeCoWiwfDMUjsai8SjMQBPFKMViYAB01Mh2GuyAMCgU1MptPpjOZNIhdIZTCZLLZvP5XJ5HIF3PZfIU1wA8mTiK8srTAWNiF4HNcAOLEYmAkwAdisF2uJuuWKJiNhGMt6JxNvxuKtdvN1oIpPJbHFoqlXslwtZEqFnID3v9grF1POxGACmVxtNXgyRi1xEI10hABFZfLFQIEVGY17IUaAfqM8W9V9ftWPoDvjtrgAxPDEMbXbCqViPTDvE51msD/79m5yuK5hjS2sXF3Owmuuezp0EpeO22o93MT0iv3B8M%2B7dB32Hg8RkMqghqjVygD6GnThoN5YhJcBM%2BXa9XDvtFrfn5/G4pI9Tz3MNA2AsD9xDHciwuVV1QIbNry4e8rDLCsLmHPZrioLwGF7PZ/jQCdgVUFJiGuaJUE8bDcIgbVdShG8NFpRYUOuYhMAINY8KoMQlGLe9ywwi4iLGTBSPIyjqJwhg6J1BEby4Fi2I4rjiDwi8vBxCxBMrS4DmuAAVTAxknPtYKaRxkGvKU4gICAGFQBCZLkhi3CY5UHzLRZFnQ84ZismymTs6haPohSUiQzzUIzHy/Mwgdfn%2BetriETAiPQdtO1BHsp30xLqyHDCzAhMIGS8LB0xJMlrwvJhCFjbk9JS4BcPwnZCIEMSJOuJgvCIa5Wtk8LGMi5juVYgBaNkxnQEAQF42glFq914pErqSLI3r%2BtQQawvk0aoom65polWb5s0zAVrJNb8qw4zTPa/4ArwazbJaBynOuLAGTdMloFo86QB%2B2gADcxAREb3LG5VuQgHzFnm8HvEwXzn3PRU3uCj6Qb%2BzAAdkoGQeRyGDuho7sFpeGfKRsQtLRiwOGWWhOESXg/A4LRSFQTg3GsaxrgUVZ1h7cwIR4UgCE0JnlgAaxARJJEpDQAA4zDMABODWuESVWVa4fV9WkFmOEkXgWAkDQNFIDmuZ5jheAUEBralzmmdIOBYBgRAQFWAgUn68hKDQB46DiCIKU4VQVf8SbAkG5BkGuKRKTMXhMHwIhUzmrgZEEEQxHYKQ8/kJQ1Gl0hdFzgB3BUUk4HhmdZ9mK/tmV%2BoDhDUCoa5o9j%2BPgET5OlbMa4IA8UP6HIsWuEWXhXa0ZYICQEOUjDsgKAgVf15AYApDMPg6GBVtKGiCvojCZpiQb3gL%2BYHUZWibR0tdiWQ%2BeAgZQYWhr7d0gsGiF4YAbgxBLRvv/EEhhgDiD/vgDiDg8CgxMhXcS6V%2BqbAlmEYEJsua0DwNEBUOoPBYArhePAFtuC8CQcQSiSgMyQKMHgow0tlhUAMDGAAangTA1dRwcwlvwfOohxDF0EaXFQ6g/5V30FAlA/NLD6HwU7SAyxUApHqE7Dgk1ZqZlMJYawZg7bUOzsglRXQX5ZBcAwdwnh2h6BCGEQYFRhi50KJkAQkw/CuPSO4hgcwhjxFznYCxAhegTFsXkIJtQQkNHGP0Rx8wXG2DiZ4vQMwWj%2BOcYE5YQs1gbAkE3DgbMbat04L3GOcdJAJyTinUeEBcCEBIOmEqs954sOWAgTATAsDxHhqQeWkgISUg1hCI2GhJBmEkP4K2iR/Aa30JwM2pALbi0pP4Lg/gVYa31v4RWOsRn%2BBKX/e2jtnaSxYR7b2y9fYd0DpvbeU8I5sE4M0FgoN9STSYJKZMXANaUi4MrdOmcSB4BziXAuIjpBiMUBIiuugD61yYPXShhTim214G3W5Xce590qd84Ayc/kArvOPVAk84jNIhGYOe5y3ZLxXmSteU8g5b0ZTvXkRhflcGtjQWgx8nYQDPn/O%2BV9wEiofk/F%2B4D36ME/t/X%2BXMAFAJAbQMBlCIEsCgTAxVLYLFIM0VzVByB0HgKwbUCueCCFX2IZsLmZCKES2obQzA9DNWMLCKAOlfB2EKC4Twvh4CxEQqLlC2QMLy5SJAAfAwzC9FWAUZa5RfS1EaM4Nogg6BdHyIsIYjFxjQWmL6cEhBzgICuFSbnBxZQAl6DcfUCtqQfH1EyQsKJ3RQkpIiV48xJbYmzASTWoJnbcjdvSfE6tWSCkrDyUXVFLdjllNxfHDlBLfn/OVmPBpWdKWtNpYvDpXSemUEKUslZfzxn6kSBrQ2EIJlTMkLndF3NOCnJdhcz2Ps/adxZQ88OkcOCvPjiwBQoMk6gzXdiMYQLGnZz0EG4RIaS7hskVzXQEJSCIuRY3BZRT51204O3f2/Vrjd17kBkDYGINwjbKS8l08SoQhpQvd21zf0b2DmyqeIBQMpEiuBjW15IMEGvKoTovL%2BWn3PpfHUYrpPEkfs/Bw0qyUfy/j/CuSrgGgM0RLLAbroG2t4HAvVyC/5GpNeqs1ODeCWsIcSG1pDUwOqoXEZ1rqtUeouWwpgnDuG8LJPw3g8HC4SFDYIZDcKQDoZjcYbNijohJtUeorImitjnTjQYoxcQTGJZ7fUKxNiR32OsS2pJdasgNvKyUAdk620xLCa0LtaTom9oa6VwJyS%2BgNrHe1qduSRZTpNmi0pHAyNVOA6B64/HKRCc3cC%2Bj4smPtNIJ07pww%2Bkm1PVGv5EIISJF1g%2Bq2u39SbKOfhh2tgznMZ8v0kYwyDb6itirSQ2suBqzMIck2EI8MYpfXumWOG05nd%2Bxd67yxqEZGcJIIAA%3D)

## Links

- [Example](../../code/facilities/utilities/gry/implementation.hpp)
- [Source code](../../../conceptrodon/gry.hpp)
