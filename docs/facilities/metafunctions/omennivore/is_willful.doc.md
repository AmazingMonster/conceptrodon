<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsWillful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-willful">To Index</a></p>

## Description

`Omennivore::IsWillful` accepts a type.
It returns true if the type is a packed `Will` and returns false if otherwise.

<pre><code>   Type
-> Type == Will&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsWillful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsWillful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsWillful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct WillLike;

/**** Items ****/
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct CalmLike_0;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct CalmLike_1;

/**** Tests ****/
static_assert(IsWillful<WillLike<CalmLike_0, CalmLike_1>>::value);
static_assert(! IsWillful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsWillful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance
>
struct IsWillful<Sunshine<Perseverance...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCAAzNIADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn4B1bWZDU0EJZExcYnSCo3Nrbkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLMn0bIJMdVf7J%2BeXR99HH2enZwImHuBiBJgSbgIAE9koxWJhwdgAaNiF4HLcFAB1Oi0KheWgAkwAdgsV2mjmQVzQDFGmFUyWIV2iqE8VwAbmIvJgrsSLFQxEpiQARcGk4WiwnnIEgl4I87gtwAq7Kq7Sh6yhVq0EIiFajW64HqsEGmXGyGG7UKpheIgAOntiKpBgUCnttsdyGdrodCWwTqYLrdHq9Qd9/sDPr9noDCiuQi8NIQYUwpCVKr1ZozOvNpuzWc1Fv1bmtdsj4e97rD0YjlajIbL1YrwZjbuUcSUbLihnWhN9yIIqPRNyxOLxBIh8cTyYVbeIHa7DHWoaRfflJLJjQpVIEtPpjOZrI53m5vIHXPFCTFRJFl8lFx%2B3z%2BX22V2wqlYD257wBz4fxzvz5XAAapgLo1G8/5SoWmbQXmsEFrmCFGnBiEQiWqDLuWmGNth9a1lhDZ4Yi/aDgQVzYrQtChAA1jqVjyp8%2By3NKsbflBqE5shSGWiaXG8TxxY2hhhEtiJNbNuJVZEauZwomiZHFrQLA0ZgAD6GgSgxgLwfxRb5rpMEcehuGifhOFiU2UmmcR5xyeiinKXgtGqVwmn/Ix1wACqgQQrGQbJm54MgqkxnEBAQMOFG4viCpRSpCoOSp6mkFciVOWprl9r6IAgEeXILG55JBSFYHNBAYBgBiUVjgqYQEIiOV5ZgBWXhwSy0JwACsvB%2BBwWikKgnCKpY1hkisawnmYCQ8KQBCaG1SzUSAnWSLaGgABxmGYACc21cJ1G3rVwRJEtIHUcJIvAsBIGiBL1/WDRwvAKCAgRzX1bWkHAsAwIgIArAQyQ2uQlBoPcdBxBE8KcKo60AGwALRw5IVzAMglJSLaZi8Jg%2BBEMQeDoHo/CCCIYjsFIMiCIoKjqB9pC6FwpAAO7EEwyScDw7VdT180DZwADyNpA2RqBUFcsOI8jqPo1cmNmFcEAeOD9CMuY00LLw71aEsEBIGDyQQ2QFAQAbRsgMAUhmHwdBAnOlDRHz0RhE0UKc7wzvMMQUIC9E2iYA47ukGDTwEALDC0G79NYNEXjAIptAvdwvBYCwhjAOI0d4MQAeOJ2Sf9XSAc2hsM11TUfO0Hg0Rs97HhYHzA54NdyekJ2xDMkoQrAunVdGPNSxUAYwAKEBeCYMzAuwr1M0k8IojiJTc802ofOM/o6coNY1j6NXL2QEsqDJHUScI6M6DgkKpgjZYZgPe3BNYPvEBLHYueZC4DDuJ4bR6CEyZzCGEzAoGQBATD8MAtIoCGCzEGPEJmb8HDdDGC0H%2BuQEE1HfgIHozRYHlCAbYFB4C9DTFwQAuBEhX7jXWJQ/QPNSD3V4I9CW8MkYozRhjVaCsIC4EICQHkU0uCa1mgPJYCBMBMCwPEF%2BpAlqSASLabaCRToaEkGYSQcNbqdThttOhF0rqJC4LaOGXA4brW2kdOGK19pKLhgwvmj1nqvRER9XWv09b/WFsDE2ZtVZQzYJwJoLA2REgRkwf0Rg5bbVtEYwueMSCE2JrIMmi9pDLyUKvemuhras3Zu7bmHBur2Ppo9IWgMbRXDFiwqWKNoyRK4NE2JitlaG1VgIhIZhhHa0%2Bh43xcQQam1QCrIYdTLZ7UCDQWgdsXoQEdvTT2rsg4LO9r7f2gdW4h0YGHCOUd%2BoxzjgnJOM1U69w2Hs7O79858yLsgEuQdy7nX6lXGurt65nK1gTFuM126d0wN3NORg%2B6gFcXwYeo9x6T2nkHOeKSKZpNkCvOm/Vskb37tfKwlhd7RGfofY%2BmRT7n0vui6wd8mEP0JqBeAr9MFIOcBAVwxCmb/1KBQyBhRMiMtICAuoeD5gYK6NgohaCIGdCwfUFBvKCGkNQTkEV0rJXwKoasGhQi9FFMYfzDg1S2EROAFEmJa1Fa8Pxu0oRWtRGkHEZIoYMjzqXVINdBI0TVFEk6ttE6SR1HIyZhqxxthnHdLcfADxAMRYDL6cQfxGwgnSxYAoNklI2QNNtNqUYON4mPySaTBecKqbyAyUinQiQWZsw5snAp6qHGCy8aLcWqhY3xsTcm1NZElZDNaXEdpCQukDy%2BvrdtRtw0DtVrlZAyRkiqSTdtVSLbVL1rSbbdsDsnYu29ks1dPs/a5yDpswQ4dI5832fHMQicg4nMBe80g%2BAc5IKufTG5dzW4PMrtXWuUI3mN0%2BUHH5aQ/k90BWEYFOtQVMBHmPCeU9GDQuSTmiQ8LqYFrXsWgwaLt6YueTigaeKdycE2OfLeN8LCkoGuSp%2BVLRW0r8PSr%2BnLmUDHwfArlUC6icu5ZkBVJCaV1BwTK3%2B/KxU8Y4wgoVsqSESvIQx2hChqEUwrbzEpnAJYNoTeyZtspRhGozaantrixESKkZQAp9rro7VtAkBInUDqSC4LdczRIzHFIepwJxb0LVyM6oo46RJbrrUkHtLgm0zB2POgkeTTmnouJ1gU7GjmmHOciwtNu7YP6SCAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_willful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_willful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_willful.test.hpp)
