<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Negation`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-negation">To Index</a></p>

## Description

`Pagelivore::Negation` accepts a predicate and returns a function. When invoked, the function returns true if the predicate instantiated by the arguments evaluates to false and returns false if otherwise.

<pre><code>   Pred
-> Args...
-> not Pred&lt;Args...&gt;::value</code></pre>

## Type Signature

```Haskell
Negation
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct Negation
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };

    template<auto...>
    static constexpr bool Page_v 
    {RESULT};
};
```

## Examples

We will turn `IsLess`, which checks if the first argument is less than the second, into `IsNoLess`, which checks if the first argument is no less than the second.

```C++
/**** IsLess ****/
template<auto First, auto Second>
struct IsLess
{
    static constexpr bool value
    {First < Second};
};

/**** IsNoLess ****/
template<auto...Args>
using IsNoLess = Negation<IsLess>::Page<Args...>;

/**** Tests ****/
static_assert(IsNoLess<1, 1>::value);
static_assert(IsNoLess<1, 0>::value);
static_assert(! IsNoLess<1, 2>::value);
```

## Implementation

```C++
template<template<auto...>  class Predicate>
struct Negation
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value 
        {not Predicate<Variables...>::value};
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCAAzAAcpAAOqAqETgwe3r7%2BgemZjgKh4VEssfHJtpj2JQxCBEzEBLk%2BfgG19dlNLQRlkTFxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJgSbhBYLemEhbiYXiIADo0ZDsDcbsgDAoFDdlMRMPhRBCEtggeNiF4HDcIphgG9skCTAB2KyXLFYmFPOEIpGotEANRaeCY0XoCgxQK5NypNIIBOIqCIyiYwHhnK5bI5F1lstmjmQ2IE40wqlSxBu0VQnhuADcxF5MDcZfqsTqGCqlcS8KT4VCRcQxRLMAo0SiMSAQI7vPDWQARSG62VspMJXVu7mg3lkxHI1ARoMhyXSrVYryZIwE9UuyEJpUq1BqjUI4viyUR6UZlmJ5Ms75/X4An67G7YVSsJ4uz5A0dD04Dq6He4KYJh/Gzy488EB/NEG4AMTwxHGpBuAtQNyEmDQDHQZYu8tpdzXG97Ka5hr9JoYZotVo2nasbOlmrrssep6Kgi163gID59j2lxpv2yGDrcr4RKg654h8i7bjmu78gWEYXMQwBSuSQKVmEwCrlhOH4vWdIMkyAgIq%2BjFRiALZ7mRFFdlRSGAuh%2Bw3AAKmGBCbvhT7NEaAD6TB4nEBAQJh2HvlCXDnlw3EgZgSyoXJTLIEpKmtOpCgMVpbg6TcGj6U6hnGd%2BZnKUollgGA9GaXiCL2WYTlxkZGYcCstCcAArLwfgcFopCoJwbjWNYcprBsdZmAkPCkAQmjhSsADWIBRZIKIaEkZhmAAnDVXBRZVSRcKyrLSJFHCSLwLASBogRxQlSUcLwCggIE%2BXxeFpBwLAMCICAawEKkyLkJQaCPHQcQRKwWyqEkABsAC0%2B2SDcwDIMaUgomYvC%2BkQwboHo/CCCIYjsFIMiCIoKjqJNpC6DpADuxBMKknA8BF0WxQViWcAA8siy2KqgVA3HtR0nWdF03FdZg3BAHgbfQVrmDlSy8BNWgrBASDrakm1kBQEB0wzIDAFIZh8HQIKnpQ0Qw9EYQtAAnuDvCC8wxDC3D0TaLeE25etLwEHDDC0KLf1YNEXjAIitC0KN3C8FgLCGMA4iaye8t4PaYYw%2Bat7IlsuVhCCHUJbQeDRCDUseFgMMEMGPVG6QtvEDaSgJqCZue0YBUrFQBgUUKeCYIDcOpIwYufcIojiB9z3yEoagwwD%2BhmygqWWPoXujZAKyoKkDSG4d4wPgkCamJY1hmINYcPXb9fdNbzgQK4Ux%2BDpIRhEMlQjDpRRZAIE96IvDTzMM8Q6XYI%2BNBMbSeB0eg7w4vT7xvc9b7Y%2B8r9v58zws88rAoGWbBIkMcDFpADbwQ1owdx1TrnUuuVPGEBcCEBIK6bKXByZ5XjisBAmAmBYHiBAYq/gEgohqgkNqGhJBmEkPtPqUV9o1X0JwLqpAeo5RRPtLg%2B0kg1WavtMqDUcH7W/jDIaI0xrwMmtTOaNMFqIxWkzFmxNtpsE4C0Fg9pWSHSYNiAw1YuA1RRFwCqt18D3TwI9HShdXr52kIXb6Jc/q6E5sDUGYsP5fx/rDDgCMlrIhuCjf%2BGNTo4jNjjdRmiND40JvTYm0CEhmDgZTKawiJFxFWszVARMRjeKMGorggQaC0B5qNCA/M/oSxFtnfJUsZZywcNnJWjAVZqw1glLWOs9YG2zibGOWxalW1PrbQ2CUHbICdtnV2dQYae29iLP2rSKZB2zmHCOmAo6myMLHUAAi%2BBJwUCnNOGcs4h0MXnd6JjZBmN%2BglSx5c45dysNXYZdd0GJSbtkFubd6znJ7n3OIA9rnPzqLvFw95b5BHvBfRYC8MhLxyIffIwLijZEBfPYep8BB9EmOCyecKGiIoGA/Tex8b7IuxXMTFl936rHWG/WBFDP7Qz%2Bn/dGgDlE%2BLURoiq%2BMIH3VCbAimCDSBIJQSMG5HUqE0PUfg1kUUaqtQSAQohkgdIOJ4bYPhkTBHwGEYtJGcSYnECkVsWRmMWAKHtMae0DLdzjG0ZAh6T1ZBGL2TnQ5pdEikGsWDI2djKWDXhqI5GqNVC6v1Ya41cJxiBIScEuIoSEgRPjtNWmIaGbqtjcTGMyBUipAUkamqCkTUEAUj6kx3M4jZNyQlIpGtcolpKfLcpCTlaq3VjDOpusxCNJDs0hZ4zSD4CJB0u2f0el9JDgM92vBhk%2B2FmMgOkyQ7TIyLM6OCzaJRsTuqNZqd06ZzirlHZb0JD7K%2BsXI5OgHUqOMFXGwVz4ANzuaaTg2w26V27pYXuv9%2B56MHjck%2BDQfnuFxVPAFBKgVpBBQ0P5a9oX/thR%2Bs%2B/Q/mQYRffcoWK77QZ/dffFCHCVkpfiS96rquFUs4GjX1BqHQBpBEG8BOioGk3ZfwqmiDkGoMoB/AVIBaoogSAkKKjVpV9Q46yRheH3XDXleNTlJVJBRWwS1VkfUkiSHqlwKqZhOEdQSG63%2BnAOUCI/jdQTGnhOKpWGHTIzhJBAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/negation/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/negation.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/negation.test.hpp)
