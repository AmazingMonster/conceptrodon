<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Ray`

<p style='text-align: right;'><a href="../utilities.md#ray">To Index</a></p>

## Description

`Ray` accepts a `Rail` operation and returns the operation via member `Rail`.

<pre><code>   Oper
-> struct { using Rail = Oper; }</code></pre>

## Type Signature

```Haskell
Ray
 :: template<template<auto...> class...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Ray
{
    template<template<auto...> class...>
    alias Rail = RESULT;
};
```

## Examples

This function injectively maps a stockroom to a type.
In the following example, We will create an overload set of `fun` using stockrooms `Stoc_0` and `Stoc_1`.

```C++
/**** Operations ****/
template<template<auto...> class...>
struct Stoc_0 {};

template<template<auto...> class...>
struct Stoc_1 {};

/**** fun ****/
constexpr bool fun(Ray<Stoc_0>) { return false; }

constexpr bool fun(Ray<Stoc_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Ray<Stoc_0>{}));
static_assert(fun(Ray<Stoc_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Ray<Stoc_0>) -> std::false_type;

constexpr auto gun(Ray<Stoc_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Ray<Stoc_0>>()))::value);
static_assert(decltype(gun(std::declval<Ray<Stoc_1>>()))::value);
```

## Implementation

```C++
template<template<template<auto...> class...> class Stockroom>
struct Ray
{
    template<template<auto...> class...Sequences>
    using Rail = Stockroom<Sequences...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGz%2BpK4AMngMmAByPgBGmMQgkgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJgAzG4QWC3pgoTDQU94YimF4iAA6bFQ7A3ZAGBQKbGY3H4wkKG5NVDIADWxFQqBYuKB42IXgcNwASkwAJ5AkwAdislxuYpusJREOhkvBCOh6KxOMheIJTCJJKEmAAjl5GJsFCzReKvJkjNymHQblCACJUoh0hlMxFa3X6zDE5XYKEiwGCm0%2BgXfP4hz5An67G4AMTwxHGN2wqlYT0wH1O4dDmYBGduAHlUvE3tlKWHLrLUTLkXK0RjUCSyWqNV7WQR2ZzqcgAPoaa3CoUByG%2BoHl6VIuGjxV1r3k9We0kqlttgj2mmdri9qz%2BwOXHP7G5ULwMNP7AFoBjjTCqVLEG4xRm0feHiA8/nQjvd3FLDc3YiYAjrI8qDEJQfV7AMd0uM8LyvG8708R8GGfPkXQdNdP2/X9/2II9Wz1UD%2ByDK5DhuAAVD0CBLdNLlmRwu1neICAgBhUGXA9EJfFDVw0Fk%2B39JYlm3C4aLwOiiQY6gnw4t9UK4HjNxtfjBN3TM/gBCMqUwM90ATJMwVTUsiJUkNsx3MxIXCAkvCwa0ZV5AtO1bS0KKNQFg1uYBD2PXZTwEaDrxuScbg89jkOkrj0IAWjJcZ0BAEAgNoJQHLs%2BUh0g3yQRggLayCyTQrcd9ZJVL8opVG4Yri3DMGSgslLcvcyPGSiTxbItRKUVomJYm4sAJAgUugJ8KpAXraAANzEREpIK1DuIXFUIH4pY4om7xMAEwdWtozt6M60b%2BoLQbEOG0bVqm/LCpZBalpWsQ9Q2iwOBWWhOCSXg/A4LRSFQTg3GsaxyrWDZU3MSEeFIAhNCelZaRAJJJExDQAA4zDMABONGuCSZGka4QVBWkF6OEkXgWAkDQNFID6vp%2BjheAUEBKchz6ntIOBYBgRAQDWAhUgxchKDQR46HiSJWC2VQkf8CL/EkILkGQG4pExMxeEwfAiGIPBYq4GRBBEMR2CkPX5CUNQodIXRdYAd2IJhUk4Hhnte96Ldp3MMT55dUCoG5Jel2X5cV5WzBuCAPGF%2Bgb1Brgll4ZmtBWCAkCF1IRbICgIFT9OQGAKQzD4OgQTjSgYgtmJwhaXlHd4CvmGIXlcxibRNOZ8GhZeAhcwYWhq5Z0gsBiLxgDcMREprgfQUMYBxH7/BfwcPAxo9C3L00jEtnB8IQSJr7aDwGI7YbjwsAt1s8DJ7heGX4g7yUG0p6MfejChlYqAMYAFAANTwTBrfzRgE9%2BD61EOIY2wDTYqHUP3K2%2Bhp4oH%2BpYfQB8GaQBWKgVIDQGYcAijFW0phLDWDMDTG%2BWssCoMWt0Vu2QXAMHcJ4DoehQjhCGJUEYusihZAEFMPwHCMhcIYPMYYCRdZ2GoQIPokwGH5FEXUcRjQJgDBYQsdhthFE8L0LMVoQi2EiJWAoIGmwJDOw4G9KmbtOB%2ByljLOWwAFZKwRqHCAuBCAkGtGZWO8dX4rAQJgJgWAEiUNhpISEmI0aQgJhoSQZhJD%2BApkkfwaN9CcBJqQMmYNMT%2BC4P4JGaNcb%2BHhljcJQRqa8FpvTRmENX5s05snbmnt%2BaZ2zlHMWbBOAtBYGNQUEUmAznNFwNGmIuCIzVhrEg2s9AQINmA6QEDFBQItroAutt7Y1xMWY0p31OAe15hiG4PsrEBzlmqfpgzhk9nDkyNOUd3GQjMHHKpLMk4pyuenAWWdXlRxQAYIwAyuCUxoLQYuDMIBl37nXKuE8IUNybi3BwE8O6MC7j3PuX1B7D1HrQceV9J4sGnrPNFsZqHL2wV9NeyAN4T23nUC2%2B9D5VxPlsL659L7gxvnfTAD88VP3CKAJ5fAP7f1/v/AsH1wZTNAUbWZsh5nmxgSAAuPzjCIJsHSih6DMHFk4Lggg6B8EquIWU0h2sV5oKoYvZwEBXAaN1sw8owi9CcIaDatI/CGg6MWLInoEj1HSN4eahokilH2t0Zo31eR/VaODawz1%2BjDFG3Wa7futNDk2L6cAJWZzEZhxcZrW5njHmJx8X4gJlATGpPSYMqJgokho3xpCaJsTJC602eU2wlSE6s3ZlzHmXt3nNNFuLdpxAWCBxYAoMaisxoDMxHKcYozXFkMmbIaZUqTayugV9XQkJSArIdlfRN5jk3bIad7X2qgx0TqnTOudy5LmR3iLcyEDzO3PJQJ8%2BI/aP0JEnakVInZp1o07LezsF7ZlF3iCCsFX1oV93BrB2FrcEVMk7t3XuFt0UjzHtg8GWBuUzyZbweexKV793JZSnF1Ld68DpUfXkjKz5a1ZdfeIHKuX4t5dU9%2BTBP4/z/gAsVvAJWGwkNKwQG7FkgB3UqhBhCkFqvgBqrBnBtgVQIVYSwhrvrGvIYpgNNCrV0JdXamNqinXZBdeZ0oyiHVevkUGl1YiLUKLmDZ0Nojw2MI865kNsbVjrCMbHZJpik000sWBm447J03EA7O%2BE8ZnFjOjh4l93jSC%2BP8SMShRMK0KsGZCSESRsbNopgVwUOSj1hbpu2pmaXglJDCXjQUFMkaSExlwFGZgghE0hKFspnAvFPJMarSr/XquvpWDfTIzhJBAA%3D%3D%3D)$Done$

## Links

- [Example](../../code/facilities/utilities/ray/implementation.hpp)
- [Source code](../../../conceptrodon/ray.hpp)
