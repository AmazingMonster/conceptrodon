<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsMoldful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-moldful">To Index</a></p>

## Description

`Omennivore::IsMoldful` accepts a type.
It returns true if the type is a packed `Mold` and returns false if otherwise.

<pre><code>   Type
-> Type == Mold&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsMoldful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsMoldful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsMoldful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<typename...>
struct MoldLike;

/**** Tests ****/
static_assert(IsMoldful<MoldLike<int, int*>>::value);
static_assert(! IsMoldful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAMykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMiTcBAAnilGKxMBDsICxsQvA47goALKedBULy0QEmADsFmuM0cyGuaAYY0wqhSxGu0VQnmuADcxF5MNcSRYqGIlCSACIQskisVEi7A0GvRGQmWPOUQqGw%2BFsAB0WqR1IMCgU1w8LzCcVI1xhcOYmq12CejAICiRKIIaIxt2xuPxhMhRqaJuIKttIPtCi1GqdiWRFz55KalOpAjpDKZLLZnO8PL5Lu5EsS4uJorzUsuvx%2B/2%2BO2u2FUrEePI%2BgIrpZOxYr1wAaph9bV3i3pSCleCFWqrZgw06Lqj0QRrjjaOhQgBreVWaNfA7XAAqXYdvb2/wpeGQAH0mN2WhB3XO8QSVdel/K3GECGbnzsI9gQCB09zFpLJ3GR6nueBAQGAYCYteXoqs%2BSJfj%2BmB/nmHDLLQnAAKy8H4HBaKQqCcG41jWOSqzrJmSQ8KQBCaChyyLiA6GSBqGgABxmGYACcHFcOhrEsVwxLEtIaEcJIvAsBIGiBNhuH4RwvAKCAgTUThKGkHAsAwIgICrAQKReC%2BFAQGgDx0HEEQIpwqgsQAbAAtDZkjXMAyBUlIGpmLwmD4EQxB4Ogej8IIIhiOwUgyIIigqOoqmkLoXCkAA7sQTApJwPCoRhWE0XhnAAPIGfpM6oFQ1zWfZjnOa51zuWY1wQB4pn0Ey5iJFwiy8CpWjLBASAmSkZlkEZ/WDSAwBSGYfB0MCxCKRA0Q5dEYTNNC6W8EtzDENCeXRNomAOGtpAmc8BB5QwtCrbFWDRF4wBuGItCKdwvBYCwhjAOIV14MQ%2B2OOyXY5fS%2B0GZslHPrUOW0Hg0QpVtHhYDlLp4BJz2kP9xAskowogu9UNGDRyxUAYwAKO2eCYIleWWodQXCKI4jhbTUVqDl8X6O9KBEZY%2BjQ4pkDLKgKT1E9dljOgELCqYljWGYsno35WB8xAyx2L9WQuAw7ieO0eghCa8zDAlhSZAIkx%2BEb6QmwwcxDPECWqw4PTjK02t5PbtRqwIvQtDbFSG7Yztm3oMw%2B/rtsSCrpEbBH%2BhZaQMm8HJZW2Q5TkuW5TF1RAuCECQvIUR1VEE8sCCYEwWDxMrpD0ZIiQahxiRCRokhmJINlSehNkcbHoniSAbUajZXA2SxHH8TZjE8Q3NnxzlckKUpReqT1Wm9TphUGeQlAjc1FlsJwzQsOyxJ2UwurvTVHEalwzFeT5JD%2BYFsghQz0hM0oLOxbok3Jala2ZRwTCs9YpyQKnpAy1wSrJwqk5ZABgjCX2vsxeqjUBrNXzokMwhcupqTXjvU0w1UBNWGHA96XBuKBBoLQGac0FqxQ2itQ6DCto7T2gdVGx17RnQujla6t17q0EeodV6uNNi4XwD9R2/0nq4SBsgEGh1wYiVwlDGGK14ZiM6n5FGlF0aY0wNjN6Rg8agGXnwYmpNyaU2pqjWmL8wpv1kMzGKuFv7s3xlLKw3NVFKwFkLLIIsxYS08TLOWcQFYA35l0T2fgICuCDglPWZRw4WyKFkBJqRLb1F9gsd23QvaB1dubaJjsCmzDDn7O2Ac%2BgZJDv0CpuTI5rGju1HuQCE65Q4NA1O58EHkKQRoeqOdfIYPap1YupBS7l2GFXESYlSASUSFfZuxJ0IcUEokFubdJAJQ6fPWwi8cEr3gGvXSRUt7GSIWg8ylkOCH0qiwBQ7IqTsn6WCHcd9c4KyfsFemDiIryA/i4nQ/ckopTSs9AB7S575Q3sVUqqgHlPJeW8uUYwUFXMGhgxI2CCbqT6pi5qFz8HxGeSkFIx5XkcWPO8sYx5EVv2mnEWhi1lpbSYWy7au1fqHU4YIbhl1xGYBundB6T1KIiOMZo0gEi1bSMBqoYGwJFGCAhrFVRsNoQaMRtow6ej0gGJxsYsIpjurmKYCTMmFMqaMBps/P5EhHGRSBazUF8DjBcxsD4%2BAfjhacC2GLTm0tLCy0TvLfykSq4O3qBrLWuRilJMGJUvQxt6gZNTVkHJ/to1OxqUU4OHtSkNGdlmqpdTakloaYbJpZEY4iWhSAzgZUkXPI5Ki4E6Ls73xagXcZy8S5lwrpQAB8yJKcQ1IkRI6FeI7KkpO4kI9gGyU4AvZSEya7oXrgJYkUkWKSG4lwNiZgZ4iUSNlRt8kl7dQAZ5JdicV1XtomjZl6tJBAA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/omennivore/is_moldful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_moldful.test.hpp)
