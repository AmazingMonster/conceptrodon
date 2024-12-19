<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Conceal`

<p style='text-align: right;'><a href="../../../index.md#higher-order-modifications-4">To Index</a></p>

## Description

`Roadrivore::Conceal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and returns the result using alias member `type`.
Overall, `Conceal` turns an operation into its `Typical` counterpart.

<pre><code>Operation -> Road&lt;&ast;&gt;{type=Operation&lt;&ast;&gt;}</code></pre>

## Type Signature

```Haskell
Conceal ::   template<template<typename...> class...> class... 
          -> template<typename...> class...
          -> typename
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Conceal
{
    template<template<typename...> class...>
    alias Road
    {
        using type = RESULT;
    };
};
```

## Examples

We will conceal `Operation`.

```C++
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

template<template<typename...> class...>
struct Operation;

using SupposedResult = Operation<Con_2, Con_3, Con_0, Con_1>;

template<template<typename...> class...Args>
using Metafunction = Conceal<Operation>
::Road<Args...>;

using Result = Metafunction<Con_2, Con_3, Con_0, Con_1>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Roadrivore::Conceal`:

```C++
template<template<template<typename...> class...> class Operation>
struct Conceal
{
    template<template<typename...> class...Sequences>
    struct ProtoRoad
    { using type = Operation<Sequences...>; };

    template<template<typename...> class...Sequences>
    using Road = ProtoRoad<Sequences...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJJcpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmgW47eweYRye7%2B0yHxwQAnqmMrJgAdB9H2ADUyAYKCg%2Bby%2Bv3%2BCm%2BAHlnsRbtkviYNABBcbELwOb4eBibMQIxEmADsViR3xJ31ONzuVzOtwu9yeLzYQJBfyYAKBQkwAEcvIxNgp4cTSSi0QRvspiKgiAAlVBMdC40nfAkWb5eTJGMn0pWBAAikOhsIElw53N5mEBn0C2COKoJOptuIVpPJ50uLppbvpzEZlp%2BLLZHxNPKx5oFiMVaoiwG%2BMrl2r14slqFj8uOQbNFuBVodSLtObxSIA9AAqUtl8uF3El0sAFWwQhrZcrRfLreLzYLeLMgQify8WG1bjQIdSBH52dzSPdlMez29719uOF6MxAH0NPncdPaScva8mRPkQRUSuBKuuJup9dXXS5/vF0jl6K12ZL4jt567z6s9bH8eRRiZ6BG%2BH73NeHq3gyC4/qCrKZmGT76gkhoMG%2BkYakIXipEUmDoFK5peLQopHHqULIQ0lwvqQgEMKuwQ0eu1Frhe2aBESnagVSFI7rOUEHn6YJAoixDAOOv6Iuh0YALKYM0VBeFiDTxjR2K0JcZEwhRh4gCAKaXMJon8Wh6rRvhCiEcRurfDJckKQ4cLHFRDH0WuGhMWeLHYDpvFvrMjjIKucEJAQEDjOgOkKK8gXjm4ZkWdRmHYRkuFxURXxLDaHArLQnD%2BLwfjcLwqCcG41jWN8ChrBsmBKt2PCkAQmhZSsADWASSG8GjJPigQaP4GhmAAbINZgAByjfonCSLwLASBobkFVopDFRwvAKCAbmNRwWgrHAsAwIgIBrAQqReAQ5CUGgex0AkUSvJwqijYNAC0g2SN8wDIMg3xSG8Zi8LhhAkHg4UpPwggiGI7BSDIgiKCo6jbToegAO4wqknA8NluX5U1y2cBCZ2naKqBUN8j0vW9H1fT9HVmN8EAeNd9DELVgRcEsvBbTtpAQEgV2pDdZAUBAAtCyAwBSGYfB0DsxDrRAsR47EEQtA8mO8CrzDEA8EKxNomAOBrpBXWwggQgwtDq0jpBYLEXjAG4Yi0OthW27shjAOINv4MQhuOAAbuaeOYKohtnVs9URDsOU27QeCxDCOseFgePHngs1u0HxCxMlOoe0Y8dGE1KxUAYokAGp4JgKNkQV9Xg8IojiDDjfw2oeO6CkBjF6YljWPoCfrZAKyoKO2Su89YUkX3ViWGYS2oNnxAg8HI/dP72QuAw7ieB0ehhBEQyVCMKRFFkAhTH4Z8ZBfDDzMMiRjHUm8CH0kx7/kz89G/EwDEfCxT62D/lfPQsxWgPxPk/FYlV1ibAkNjDgeVSCLSKpwcmT1XrvU%2Bt9X69MIC4CBqzcw7NOYNRLisBAmA5QjAgK1JIgQ3gAE5Aj4kkF1MwkhBrzX8INJhk0ODTVILNdmbxBpcEGqNJho0JH%2BGSP4Fhg0UF4xWmtDa5Cka7QOnzI6RMzoXVFqgZmt17ocBaCwAO%2BJnpMFghqLgTC3hcE6gDfARAV6g1hk3KGEhpBtyUB3G2uhpZoyYBjQqiDkGoPxhwQmJ0zrfFJt8cxljrG2OjPYxxnUGZM0FizNmZgyHcyyrzfmRjckJAMWLFmIBklWJZEYexXA3I0CIgkBWSsbZazVsbLpOs9YGyNm7U2jACAWytnjO2Dsna0BdsbLALBPbeyWr7TeQdXZLVDuHHYxto51DxvHROasU5bCWunTO9Vs65yUPnBZhcowlz4OXBQVca512No3SGLdfGyHbojJaQT9CexQGVSwg9YjDzoctceAhJ7T11LPawC8irL1XhCmBL97LOAgK4UBKRD7lEfnoc%2BDRcVpFvg0SBixv6v0aCAz%2B18N6YtpXMABhKxh0ryAy8B/8CVQIQasOB0MIm4xtitJJxALFWJsfU9JDinEaAZoQtxbMOZcwoaQKhNDEiQtjkIkRDiur4gUfiHqkhOFvRSFE1Rth1FFK0fAHRx1iaVLKULO6bBODmKpiwBQAdvoBwyeccYLiiEgz0B85u0Nvlw38X85GwQQlhKxgIyJKiCZ6JJmTL170fV%2Bu%2BAGhxQbRSM1dXkkhgRCkPJ0VUipIsa2JD9dhVcBbVxFsChKt6MtWny0oB0pavTrb1QHf0/2xthnm0ttbZZmB7aO2dq7eq8zFknN4Cs%2ByayQ5h2QBHHZgg9lxwTknB4xy04r3ObwS5ecC5e3uZox5TBK7V1rnOd5shPlRs8b8zuIBgg92MCCmwBy0VQoaK7QsYVgX93novFFWBgN2BpdvXenKD470pUA4l2RSWYdKKyvl1KmXvzaPSsBGKGhEfQ0/YB/RSXcso/y2B1V%2BWx1TaK9B2bvi5v9YGmk4xFWuJICqytmjKHUKwNqxBeqQBmAcYEQI/h%2BrJHmnJ/EkjlFsdWjaza6q2qSH8Mw/wo0hpMMkEwnqrCuC/s4IEEVi9OBqpEwI/66m7OabtSsbOmRnCSCAA)

## Links

- [source code](../../../../conceptrodon/roadrivore/conceal.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/conceal.test.hpp)
