<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsGritful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-gritful">To Index</a></p>

## Description

`Omennivore::IsGritful` accepts a type.
It returns true if the type is a packed `Grit` and returns false if otherwise.

<pre><code>   Type
-> Type == Grit&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsGritful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsGritful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsGritful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct GritLike;

/**** Items ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct CoolLike_0;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct CoolLike_1;

/**** Tests ****/
static_assert(IsGritful<GritLike<CoolLike_0, CoolLike_1>>::value);
static_assert(! IsGritful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsGritful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency
>
struct IsGritful<Sunshine<Consistency...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCAAzNIADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn4B1bWZDU0EJZExcYnSCo3Nrbkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLMn0bIJMdVf7J%2BeXR99HH2enZwImHuBiBJgSbgIAE9koxWJhwdgAaNiF4HLcFABxYiEKheWgAkwAdgsV2mjmQVzQDFGmFUyWIV2iqE8VwAbmIvJgrsSLFQxEpiQARcGk4WiwnnIEgl4I87gtwAq7Kq7Sh6yhVq0EIiFajW64HqsEGmXGyGG7WamFwtgAOntiKpBgUCnttsdyGdrodCWwTqYLrdHq9Qd9/sDPr9noDCiuQi8NIQYUwpCVKr1ZozOvNpuzWc1Fv1kOtzDtkfD3vdYejEarUZD5ZrleDMbdHhpeFpDGQUMJvuRBFR6JuWJxBDxBIh8cTyYV7fSXZ7oaR/flJLJjQpVIEtPpjOZrI53m5vMHXPFCTFRJFl8lFx%2B3z%2BX22V2wqlYD257wBz4fxzvz5XAAapgLo1G8/5SoWmbQXmsEFrmCFGnBiG6iW8LLhWmFNthDZ1lhjZ4YiA5DgQVzYoQoQANY6lY8qfPstzSrG35QahObIUhlompxPHccWsKlpguGtoRon4ThYm1sR5womiZEeJ41GYAA%2BhoEr0YC8F8UW%2BY6TB7HQoJGFSc21ZEeZ4kttJq5nHJ6KKbQykqVwGn/Ax1wACqgQQLGQXZm54MgKkxnEBAQCOFHjviCpRcpc4sk5eA0WppBXI5zmuf2vogCAR5cgsbnkkFIVgc0EBgGAGJRROCphAQiK5flmCFZeHBLLQnAAKy8H4HBaKQqCcIqljWGSKxrCeZgJDwpAEJo7VLFRIBdZItoaAAHGYZgAJw7VwXWbRtXBEkS0idRwki8CwEgaIEfUDUNHC8AoICBPN/XtaQcCwDAiAgCsBDJF4BDkJQaD3HQcQRPCnCqBtABsAC0COSFcwDIJSUi2mYvCYPgRA4ugej8IIIhiOwUgyIIigqOon2kLoXCkAA7sQTDJJwPAdd1vULYNnAAPIg8DZGoFQVzw8jqPo5jVzY2YVwQB4kP0Iy5gzQsvAfVoSwQEgEPJFDZAUBAhvGyAwBSGYfB0ECxCvRA0T89EYRNFCXO8K7zDEFCgvRNomAOJ7pAQ08BCCwwtAewzWDRF4wBuGItCvdwvBYCwhjAOIsd4MQQeOGyoH83SQcgxss31TU/O0Hg0Ts77HhYPzg54DdaekEXxDMkoQrAlntdGAtSxUAYwAKEBeCYCzguCSHpPCKI4hUwvtNqPzTP6FnKDWNY%2Bh169kBLKgyR1KnSOjOg4JCqYo2WGYj1d0TxdH50BeZC4DDuJ4bR6CEyZzCGMzAoGQBATD8MAtIoCGCzEGPEZmdh34CB6OMH%2BuQEE1CQfUMYfQAFwL0NMVBOQIG2BwbA8oQClgKAmusCQPMOA9VIA9XgT1JaIxRmjDGWM1qKwgLgQgJAeTTS4FrOaw8lgIEwEwLA8QIBLX8AkW0O0EhnQ0JIMwkgEZ3S6gjHa%2BhOBXVIDdGatoEZcARhtHax0EarQOsohGTD%2BZPRem9MRn09Z/X1gDEWIMwZm1QKraGsMOBNBYGyIkSMmD%2BiMPLHatouDrTxgTEgeBibMwXuTZe0hV5KHXgzXQNs2Yc09vQxhzCBYcGFkDEGVxxZsOlmjaMMSuBxISRoJWKsjZqyEQkMwoidZfS8ebNWfjhlDCaVbfagQaC0Hto7Z2DNvbuxDks32/tA7Bw7mHRgEco4xwGnHBOSdaApxDhnAeGwDl53fkXVOA1S7IHLiHKuF0Bq13ru7JulztY4nbrNLuPdMB90zkYQeoB3F8DHhPKeM854dwyUvSm2TZBr3pgNApW8h63ysJYfe0RD5yMGqfTI59L7X2xdYB%2BLCn6pJfoSxBDgP4QFcOAv%2BX9yHzEgYUTIrKuXQI5UAt%2BjLkE4N5UKuoKDcGlHwQg0VaCSGEKlQMCh8CqE0MpqUvmDNWFSw4dE4AsT4nrSVvwwmPSRHa3EaQSR0ihiEouoY4xcS1FEi6jtU6SQNGo2ZuU5xthXEDI8fALxgNRajICV0oJbBOChJliwBQbJKRshababUowkkCKJiTWQmSkXU3kLktFOhEis3ZpzNOmrHHaqFj4sWEtVBxoTUmlNaayLKwjcbHpCR%2BnD2%2BgbDtIzTZjPiIm5IyQVLJp2ipVtKkG3ZLtnEeZLs3a%2BxWSuv2AcC4h22YISO0d%2BaHMTsnVOs1zmgu%2BaQfA%2BdGW3JLqoMuQJnmCGrgzd5DcoRfJbr8kOAK0hAv7qCsI4LdaQqYOPSe09Z6MHnjmxFEhkU00LRvEtBgsW71xe8glx9iU7k4JsS%2BO874WCpYNGlWAsPiqZSy%2BVbL0ACvgaQEBdQxVMcyPRghmDhXYN6GKhlEqyF4JVQQuVxDhMzEE5ytVqxaEiP0QwrVj1OCS0bYm9kLbZSjBNck9Wwie3uIkVImRlB6GOpALtW0CQEhdUOpILgd1LNEgsVWxTz1/XvStctSQXUlEnSJHdDakh9pcC2mYBxF0EgKZYZwS1%2Bm5O42c1F1zgalhd3SM4SQQA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/omennivore/is_gritful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_gritful.test.hpp)
