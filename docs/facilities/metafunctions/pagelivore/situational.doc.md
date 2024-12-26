<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Situational`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-situational">To Index</a></p>

## Description

`Pagelivore::Situational` accepts a list of predicates and returns a function.
When invoked, the function returns its first argument if the argument list satisfies all the predicates and returns its second argument if otherwise.

<pre><code>   Preds...
-> IfTrue, IfFalse, Others...
-> (...&&Preds&lt;IfTrue, IfFalse, Others...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
Situational
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct Situational
{
    template<auto, auto, auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };
    
    template<auto, auto, auto...>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will create a function that returns its first argument if the sum of all its arguments is less than ten and returns its second argument if otherwise.

```C++
/**** SumLessThanTen ****/
// `SumLessThanTen` is the predicate
// that we will pass to `Situational`.
template<auto Initiator, auto...Args>
struct SumLessThanTen
{
    static constexpr bool value
    {(Initiator+...+Args) < 10};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Situational<SumLessThanTen>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1, 2>::value == 1);
static_assert(Metafunction<10, 2>::value == 2);
```

## Implementation

We will implement `Situational` using partial template specialization, where we separate cases via constraints.

```C++
template<template<auto...> class...Predicates>
struct Situational
{
    // Primary template will only be selected
    // when no specialization is available.
    // In our case, it is when
    // (...&&Predicates<IfTrue, IfFalse, Others...>::value) evaluates to false.
    template<auto IfTrue, auto IfFalse, auto...Others>
    struct ProtoPage
    { static constexpr auto value = IfFalse; };

    // This partial specialization will be selected
    // if (...&&Predicates<IfTrue, IfFalse, Others...>::value) is true.
    template<auto IfTrue, auto IfFalse, auto...Others>
    requires (...&&Predicates<IfTrue, IfFalse, Others...>::value)
    struct ProtoPage<IfTrue, IfFalse, Others...> 
    { static constexpr auto value = IfTrue; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v
    { ProtoPage<Args...>::value };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQAcpK4AMngMmAByPgBGmMQgAKxmpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJgAzG4QWC3pgoW4mF4iAA6dFQ7A3ZAGBQKdGo5TETD4UQghSYoHjYheBw3ISELxvbJiIEmADsVkuNx5N222xuRLwLBaAE8brCnvCbgB3Oi0G4CWjiuI3OyYBwkoG8vkCmUIRg3BioNWpDV4MR4ABezIENzwChuTAAbkw6EwYvRUdrefz7gxFetsUwlKR7QR7Y79YwfTy/RACeYAGzJokkvBkzAU6F3KgAFRpmDDuYAYmJQzcAPIEA3EfEYyHYEAgV3eTBLG6YVtM8kSk1UcuYb3c3mS8EI6HIoj3fOFsNTk2lwfzlGoAnV2vZ7CxtUEGl0omoIjKJjABEjnkciy75nIbECcaYVSpYhO1c3buYG5QgAiM7LtBKFC14cj%2BwFsheuo3HmCAOjcqT9BaCoKGayBIdatoBnKtAKqq6qaugO5%2BngVA3AmGJmCmlFpqS8LZm4uYFl4Rb/suVY1vE9beo2zafh2cF7sxw4XDqY7woiC4zkxLGSUugEyau64cXWlKQcSACOXh4MSjrkd6lGpsStHkoijFzqx8lhhunGJjxLZiMxSw7tStIRoex6nhODGzsxxZUABFbWXWtlYjuV43o4d5oAwj7Pq%2Bkmft%2BkJ/mZzHAd%2B7JgZCXKApBYkQpOinohcwDEqCjAEFuO5eJkRiCp5SV/u5qAnmeiIlWVLyVSF4GXDu%2BVeQuBIXMQwBVZBsyRfeMUgnFb7Tq1mAAPrOmFnKCsQR4tZ57WjVxmK8Q5X6gb1gKZadQI/H8RwAldNzYKorBPF%2BnyXdd/wQVchz0j4IRZgoMGGHmhqvd8AomEmGhCL9/2AwwwMMBDGiRhKBrwUZGbiWDqNvLKX7YQqCF4n236QwyBA9iytBI8JA0Se%2BdwMFkbwkCuaLFXtqkXC5dLQywf14nDCNspyznNFN0WxS%2BNwxKgngfkda0WBAjPM0QxDWImlgjWNHaIjcXAaCd2Ui1lOVvbcACymDNFQXgMA42QfKcQJ04V7Oojr40XDV4TADc1u2/bjt2r%2B9KMphrLQnzAsAwgQMxo2QLNotu1jT1Jt9d833A%2BMjqg9z4sZktIZKK0ECB0wdsOw0iJcGGZgHfZbaNWHXBOZnhe3iXeLxAQFc21Xwe19ChsN03iW/mHZgdxYHArLQnCJLwfgcFopCoJwbjWNYaprBsx1mJCPCkAQmjzysADWSSSKiGgBGYZgAJxP1wiT3wEXDsuy0iLxwki8BYBIDQGhSCr3XpvDgvAFAgFAWfNe89SBwFgDARAIA1gEFSCicglA0CPDoPESIrAtiqACEmAAtEmSQNxgDIDvFIVEZheDpnVngdAeh%2BCCBEGIdgUgZCCEUCodQCDSC6HrjKYgTBUicB4AvJeK9z4b04JWFEWCIyoFIqQihVCaF0INrfMwZEPD4PoK%2Bcwx8li8HgVoFYEAkB4NSAQsgFAIAOKcSAYAUgUg0FoCCOslAYiKJiOEMUMjeDBOYMQUUlYYjaA1PAk%2BeCuqVgYMqRRWAYheGAEiHCMDuC8CwCKIw4gRH4GJI7Z0WZFFPg1CiLYJ9wggj/uvWgeAYiSKiR4LAii9zCjCaQSpxBZZKB/KCQwwBWlGHPisKgBgxoADU8CYBlJWM0q8T6cOEKIcQfDNmCLUIosR%2BhxkoB3pYfQbSYGQBWKgVIDQ8nkPGIRZKphLDWDMBAwZxA2FVOud0eJ2QXAMHcJ4DoehQjhCGJUEY9cihZAEFMPwsKMjwoYPMYYCR674QaH0SYoL8hYrqACgQuKBiQoWDC2wEw2j4qRVSuY5KMUSBWAofemxmX6HkWAxRkCbhaModQ2h9CDFkVwIQEg34j7tysdMlYBomBYASBAK%2B/hISoifpCH%2BGhJBmEkJDDQiQkxP05f/QBIBj6oiTFwJMAQn6fyTIkSQb8NVJm5SIyB0DYGn2mUg1Bdj0GqOwS4txpiiFsE4C0Fgzp2TkKYNiAwdUuBP1RFwO%2BzD8CsPYfXTZ3CdnSD2UoA5IjdApAkVIsJciODLzdRA5Rgb1GaLIQK%2BN4yDbJtTcjCAxjHGmMlZCGeMqEG2PsagEx8QcGuNHT2kYOJxlJrHj4vxMCICBJERE0J%2BTSDrqiTEuJDh%2BlJIqiktJpTMCZOyWIQC/TCnjJKevMpALKl5PXjU5AdT%2BmNLqIo1p7SxRdK2OvXpQDN2DOGZgUZRSJl%2Bx9bM08ChFnLNWYwfpObtm8PzbIfZwj14luOVM15Vhzk/qucqjedzsgPKeb%2BAj7zPnxG%2BVgEjLKiUhz8BAVwiLwXAvRdCzFaQUUNE48i4o2QeOLEJT0El1KhP/NY6SsTlLZh4ryHSpTZLyhMvbqsdY7KtN/2reA3gvL%2BU6NnYm9td9RUZoleY6V3qh1yswAqkYpG/4ANIEAyEybtXskSE/b%2BkIdV6qdTWoznBPVwJ9cgtBGC1ETpDYQ4hEbiAsB0SwBQzo7zOiTaicc4x03ioYxw2Qub0P8PkIW7DOhzWkDLdI/JlaDM8rrZglEipNFpYy1lnLeWIxdqnU4vtkJLH2ZsUgkdY7nG4IG6YlsyBUipBWkmpavWlqqCoXwOgS6AlBJCVE/p27omxPiQe0dyTUminSWerJOSr2bpvcUgDBTtKPqqSI1977N2fuabwH9HTRT/p6d84DJ9QMZHA2M4p0Gh18DmfBpZKy1koZK2hiQGGBGVcOTVhNxgzk2GI/AG55GHycG2E805bzLAfKM18n5THZMNCBSClTXH0AKb43CwTtK9Cc9E4y3jehsW9Gk9ziTxLGjUvZ4LkXLOsWS/5%2BJllbLeGNYUe6zgfLOuZY/D1uifWxXqz7XZ6xF9SDysVZQSt7mgHP1RJCSEiR35OpAfb9kNrQtKKgbYL1JulgqskIkdVX92QgICJIV%2BXAH6URNZCNXtave%2B8rUwj3HrRum8GZkZwkggA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/pagelivore/situational.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/situational.test.hpp)
