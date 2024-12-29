<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sny`

<p style='text-align: right;'><a href="../utilities.md#sny">To Index</a></p>

## Description

`Sny` accepts a `Snow` operation and returns the operation via member `Snow`.

<pre><code>   Oper
-> struct { using Snow = Oper; }</code></pre>

## Type Signature

```Haskell
Sny
 :: template<template<template<template<typename...> class...> class...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<typename...> class...> class...> class...> class>
struct Sny
{
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RESULT;
};
```

## Examples

This function injectively maps a `Snow` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<typename...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<typename...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Sny<Op_0>) { return false; }

constexpr bool fun(Sny<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Sny<Op_0>{}));
static_assert(fun(Sny<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Sny<Op_0>) -> std::false_type;

constexpr auto gun(Sny<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Sny<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Sny<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<typename...> class...> class...> class...> class Operation>
struct Sny
{
    template<template<template<template<typename...> class...> class...> class...Args>
    using Snow = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGzSrgAyeAyYAHI%2BAEaYxCCSAKykAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3MDQa9MJDoSDHnCETDkeCoWiwfDMQBPFKMViYAB0pMh2GuyAMCgUpOJ5Mp1NpZIhFKpTBpdIZ7Jp1wA8gTiK8suTAWNiF4HNchAxcYCTAB2KwXa6q65YlGYpHY1HazWI2EY6H4wlsLmsxkc5n0i0863cpl087EYAKUUqtVeDJGaUMVAAd2ukIAIvzBcKBAjna7zdhIcqAQrg/H5V9fumPoDvjtrgAxPDEMbXbCqViPTDvE5ZjM1/7Vm4CuIRhgKSt7f4ao2dnEG9E97uok3MM0stmO0eWzkTu2xsUECVSgUAfQ0QaViuTEITgIHWsN/b1XcP/aHRNjk/ttvHNrHVtnF3FkoIYaXXDXViTKYu9b21yoXgYNsdn%2BNAW2BVQUmIa5olQTw/wAiAZTlKFlw0clFnfa5iEwAg1kAqgxCUeM12Tb8LlAsZMAgqCYLg/8GEQ2UEWXLh0Mw7DcOIQD5y8HELBI1NLgOa4ABVMDGVtMwfJpHGQJcrTiAgID9Z96MY5C3FQ0V1yTRZFi/c4Zlk%2BSaUU6gEKQ5iUlfbSP2DPSDJ/Gtfn%2BbNpUwUD0GLUtQQrKShOc9M62/MwITCKkvCwIM8QJJd5yYQg3VZQS3OAACgJAgRKOo64mC8IhrjShjLJQ6y0NZDCAFoGTGdAQBAAjaCUOKTUc8isvAyDcvy1BCospjSpsirrmqi1avqnjMBagk2oC38xIkjK52FOSFJaZTUGfLAqQIE1oAQ8aQG22gADcxARErNLK0VWQgPTFnqs7vEwfSt2W4y1qU47doJfaGMO46nougarqGuNbvux6xF416LA4ZZaE4RJeD8DgtFIVBODcaxrGuBRVnWCtzAhHhSAITR4eWABrEBEkkYkNAADjMMwAE5Wa4RImcZrgFQVaREY4SReBYCQNA0UhUfRzGOF4BQQAl8m0fh0g4FgGBEBAVYCBSfLyEoNAHjoOIIiJThVEZ/xKsCQrkGQa4pGJMxeEwfAiGIPA6q4GRBBEMR2CkH35CUNQKdIXRvf9IUUk4HgEaRlGw5lvl8t159UCoa4Latm3gDth36bMa4IA8I36Cg4muEWXgla0ZYICQQ2UmNsgKAgJuW5AYApDMPg6GBQtKGiMPojCZpcVj3hR%2BYYhcT5aJtA8pXScN54CD5BhaAn5XSCwaIvGANwxCayfd5BQxgHEHf8Gwhw8BO8Sw6ojz8s2UmwmBQX0doPBoiFWePBYDDvOPAotuC8AfsQGCShgznyMD/IwFNlhUAMK6AAangTA/pGyo1JvwX2ohxCB3wcHFQ6gd4R30BfFAONLD6F/vLSAyxUApHqPLDglVaohlMJYawZhpaQI9lgRhd0uhLyyC4Bg7hPDtD0CEMIgwKjDG9oUTIAhJh%2BBUekNRDA5hDHiN7Ow4iBC9AmDIvIhjajGIaOMfoCj5jKNsLYjRegZgtD0Uogxyx8ZrA2BIeOHBkaSyTpwLOltraSFtvbR2RcIC4EICQIMoUq41yQcsBAmAmBYHiKImmkgITElZhCfmGhJBmEkP4cWiR/Cs30JwYWpBRYk2JP4Lg/hGasx5v4OmnMin%2BGCTvGWcsFZkyQarDWDctapz1m3Du5dTZsE4M0FgJ0FSVSYJaH0XBWbEi4AzF2bsSCez0CQv2RDpAkMUGQsOuhe5RyYDHcBASglS14MnaZ6dM7ZwiZs4ADsdl7NXCXVAZc4hJIhGYauozlb10biC5u5d9bt3hZ3dkRhtlcAljQWgA95YQGHjvae49T5EtnvPReDhT6r0YOvTe290Z7wPkfWgJ9wFnxYBfK%2BDKCziIfuw9Gz9kCv1Ph/WoYcf5/3HoAzY6MQFgNJpA6BmBYEcvgWEUAMK%2BCoIUBgrBODT6nMIQHC5sgrmhwoSAXuBhEE8KsHQiVIjmGsKyOwzhBB0DcNoRYfhbzBGe0fkwsRd9nAQFcC4728iyj6L0Ko%2Bo4bUjaPqB4hYljugmOceYzRQb6imLsVGzxriM25CzW4vNiiU3eIJn4qudTAmJ0GaE75Ns0V/O2bshmxd4nu3BSk6Fdd0mZOyZQAJDSmk7NKQqRIrM%2BYQjKRUyQ3tXkY04MMxWYy1aa21mnJFcyTZmw4Msm2LAFAnXtidNt2IxgHISUIk5sgznGqDma8h6NdAQlIPcx5cda0vJCRwFOOt8rXAzlnI9J6z0XrhEWYFoKK6hQhFC2uKtJm7tbgbFF5cQCnpSNZc9rMlyXoIEuVQnRsW4qHiPMes8SVUbngvJeVKQVrw3lvMOjLD7H3YaTLAqrL4yt4DfXlj8d6CuFWy0VX9eASv/riaVwCPbyogXEJVKrOXqrGSgpg6DMHYIJLg3ghr/YSBNYIZ9NyQDvutcYL19DoiOoxs6rKnAtjjVtXwgRcQhEBtEUY4NfhQ1SPjZG8tjjY1ZHjWFko9jo2pusbm%2BNvmc22OTY40tCXkvRYLTWnxhN/E/vrdLRtYHT3XDw8SQjnbDlwZJohtJpAMlZOGKIwWo7LU7IhBCRIXMF3iw6wqdpAzCuy1sCMpDelSB5MSIU3mCpxaM0kBzLgzMzD9MFhCArbyV19sprW52g3NvDbG8sSBGRnCSCAA%3D%3D%3D)

## Links

- [Example](../../code/facilities/utilities/sny/implementation.hpp)
- [Source code](../../../conceptrodon/sny.hpp)
