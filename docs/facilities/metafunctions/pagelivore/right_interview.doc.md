<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::RightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-right-interview">To Index</a></p>

## Description

`Pagelivore::RightInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Vs...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>, Vs...&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>, Vs...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>, Vs...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
RightInterview
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct RightInterview
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Page_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = RightInterview<Equal>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

`Pagelivore::RightInterview` is implemented based on `Varybivore::SensibleRightInterview`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct RightInterview
{
    template<auto...Interviewers>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Varybivore::SensibleRightInterview<Variables...>
        ::template ProtoRail<Predicates...>
        ::template ProtoPage<Interviewers...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQS/makAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzOFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GB5nBDEhXmhsLcyHG6CwVGxuJ%2BhxuADUWgiYngAG4kdggISMDIxegAJTwwAQBAAkoJ4qy3gB3T4HQHMNgKFJMTYMpks9nETAwgDsVkuwIImBYKQMxpJTC8RAAdHbqZdxsQvA4btyGLyBUKReLjcQpZhpbj9cCbmGbsbTebMCTI2amBa4VbbfbQdgbpCmAoFHabcptfhRMasWnQ%2BGnS6CDd86giPyMbQy2GTCHLuH2xGTfHE25k6hcw6Lh3y2jK9XiLXUMomMAY23h3qLDdZo5kBmBONMKoUsQbn2bqyxF4dS2LABaLgtu6wpdXm80ocLuPRy3W/t2i7AbUmxgEEs4%2Bdhy8DIjGrGcT1BO5x0nadZxJT9vzYQQc1THFQQNR9m11a90IfdtnwTGM4QIns%2BwHNMMwMbNc3zTBC0I/8mxuYDwmAG56zoGFIOgusGxJWj6OLci0Iwu9cMNS4SKI3s3xuAAxPBiHGQcK1dd1PUwQVhTFCV/RlEkFKUghB1PJipNjLsXyTN9hMorMULzAs8CLd5B3bVSqxrXi6CY0zAI7czrJTG0tJFIQ8CwRj/Pc0dXS8qdwKY9tT3DJKFxXZz1w9Y1t13fdD28E9ooXPzMIXYcTH8Kx/DuCAlhuM9sWXAh0BAEAWCYABrTBkQyYAInQVESQyAAvHrjNLYryqwjDprmm48CoLLN1ymEpvmsMoAHMwADZzB2gTnIYgzFPGUh2O9YQIveYS2oK48liWNKNpmm5tQIdYGBuDQbz1a8JLKl7wzqJRnpelL3s%2BhrL3Qv6wfKq86vh1LsPvdaxNE9bApk4KEMwH9kLchcWNA2CIKg%2BKyfgr98aQv9hLRsqMbw8NsexsjULs6iPxpgm/yJsMSbYjjaC4imJ28xs4TxvmHOpcSgVRhWjUswjXyIeTToIc7925NAGHQHWbLtAB5AgEHiKKLg8t0eTwPlNMu31JX0uFDLO239cNm4zYtpSGcNVsyrZ1XSONm0mszbnHLoo7iwF5rnTiiXUBF3yg/K9nw9Cq7IoTmKk88lOqfR/VUvWmKE0y/WVp3PdZPuorAZKjOgZhKrKtq%2BrGoo8k2o67reqFAahrhUbxvz%2BbSrbjtFuWnK6%2BRuatvtXb9sOlySzcd3tYu7Twsi26QEbx6l%2BmiHMA%2B4gvp%2B2G7wBmf2xBnU55rhfdzP8qV4jtfdo3464R6wEN7HOB8bqoTukeTAp8K5TzLpDa%2BNwYa3lRg/R%2BYZn4LSWm/LcO5P4LggPgua6l7Zem0s7PSgYSS%2B0tgHZu6C2pSXYnxOE/8hKoSIdNRhocdRUzhKA66ctJr0MfpAwqNwwBgFhFBC8nD2xPVgXNFKciFwIK%2BmYGElhbYelIY7chukAxBjhDQ/2HDFEvW4VGQizCfKsKcpvOh6DhyWO7LwxK/DLpgKEQBERM8xHHl%2BiorC/0gTmPKs/IJi43qXyhrIu%2BqDfEty7mfZmpccKYxEVnXGvM6ZW3KkLMCs4xY8QSnBaWOTfzeMZslJWGT8I8IslYsOwVI5UQcjLXJCcCki2KfFNO5TEKVIZsrWpD576hKuP8KZAJgS/F2DcUUUY%2BZVwEHKfYgI5nTP%2BICFWTTpJZPfBHCiUcHJsNcsIm2OcKGGODLNVmDSgqHOuTKS2CcbaU0Sv5aeT4Hk40OYyYgeAmAOzycTECbEybFIBcyNkHI2okIdlcgxrs3AAqBSCxxC4XHRhKf0twZyqnrWxdYj5ZS3DPMDLQjhCsanpJZmGA5uY0XAvoKCwW4LCnkxKXw1FLR0WsuGaJUZANNlbI2XSbAqhWBmh1F8WZWyZkiolQARy8GINZpxdmuPVqgBZRsNYACkVKxSrNgVVYhblMQymuHBq0YioE8AeKB6cLCijFtIm4RrhWKzpUq24ABZS%2BTAqBeAJA0DVgJGUfmIMAK2BTA3NBDWGrIxSkV%2BhuXCM1aqpY%2BLajyi4MaqnK1pLcAAKu8P8EbgTWuRPZeIxlLgQATcG0NDgsgkjMNiPN7i3AaHOkEG4yRB1duPlA913EzBPQVjWutrRgRNqDUmttAgSRxOwN2slfakHnSHZ2tM/jyYeovFOiwHAVi0E4P4XgfgOBaFIKgTgbhrDWGXGsDYJ4wQ8FIAQTQZ6VidQCJIG0GgAAcZgzAAE4IPVFAyBrgupdTSAvRwSQvAWASA0H2m9d6H0cF4AoEAfaf23rPaQOAsAYCIBAGsAgKRrTkEoGgU0dB4iRFYFsVQIGdpnh2pIG4wBkBrikDaMwvBY5EEBa1II/BBAiDEOwKQMhBCKBUOoEjpBdBBGlOiFInAeDnsvde3997OAm2tHRqsqAlqce47x/jgmkFAY0RADwzH6Af0/UsXgxGtArAgEgJjKQWNkAoBAQLwWQDACkMkGgtA/QEYgDEYzLJmDEARHp3gKWmQmxiNoTADgMukCY3TE2DBaDpfU1gGIXhgC9loLQAj3BeBYA6kYcQlXFL5ccKyd4xmtz5etFsL94RjTIbvbQe26I0seCwMZtEeB0NNdID14g9qlAPFa8ACbRhf0rCoAYWN9IZQmyeDer9MnhCiHEIpi7Km1DGc0/oQwxhn2WH0PbAjkAVioBSA0RrZ5yTSNMJYawZgcMrck71r73QutZBcAbKYfggihHCEMCoIwCjpEyAIRHehCjY4YPMYYVQYfLsaBMNongOh6DsLDgQfRWhE/RyT2Ykwqd5CCKzgYqOFgY5WAoN9mwJAGY4Fe0g2HeC4ZuDZnjfGBNCaczcCAuBCAkE0aCLgXnv27ZWBbJgWAEh1VIAByQoIbQQdBIhjQkgzCSB2ph/wO0IP6E4Kh0g6GNc2h2lwHaIGINwZ2v4SQ1QLc7XF8Z3D%2BHCPa5I35yj/nqPmfo6F8L7m2NsE4C0FgrJdRniYHZUCXAIM2i4MBsT%2BAJMRT0BduT13pC3aUPd9TuhkjaaYLpprIuxcS5MxwMztHrQ3Cs9LrjsuC9sSLyX4DSvXNBfc%2Bryd3ndtkYC6gNz8QGNhbX3PkYmYjBF64H22L8XKBJfU1ltLhWL8Ihy3lgrS3iu/lK%2BV4zVWat1Ya4Vlrz32t3vwNqNtHrRrO9frZAQbQrEbOoYzCbGIKbBEGbLYO9ebRbL9FbNbTADbH/ViZffbGcBQI7QME7RgQrGvK7BTevWQO7NTO9FvJ7HbYHKwN7GAz7I3H7P7TgAHFqIHV7CwMHSXCHQReAfnOoOnPwCAVwXHZHA2JnRYTHIoLISQ1ILHBoGQjHUnBoBnSnXIJHdQ3oCnVQlnCnRQrnAw4XVYdYIXTXF3UXIzdTKXGXOzPfCfYvUvDQJXFXCTdXTXJfWPXXTAfXEYI3ZDN3D3Yva3XUfwCDBDUEG3O3YPcPOwzgKPIjZfcjKjGjCzTfVPVjdjTPYgFgOzFgBQVkNcVkSfaMcYcvVXSTavWQWvcgpTeQRvagnQEAUEUgNvDvfTaw7vCPUzJPSzazQo4o0o8ohiKsFzbfYLdXUELXHzUjBPbIkLRjKY9zY%2BZAFIFIZEMoiDZECoggZEVQXjPgOgE/RLZLcIJkK/S4tLW/LrQrR/QQZ/CrP/TAarWrMQT/Jbb/NrRA5rTrQA3rdTUA8ApbSAsbXgGAuAhAubQFFA3gNA9IDAk0LAnbWPPgA7fA47U7EguosgiQCg5TZoh7Nougl7EHJgj7IQ%2B9X7LIRrbYPuBg0HcHeISHFg4QnoZwcQhHdnHQlHMoYnPHZQhQ3koU%2BQkoHnQUznEQsnTQ4wmUjQ/QyU5nGnIw0UznJUgUlUqwgXCwhTLvWwnDTgaXYYkog8MY4sCYjwtXPEbwmPXzPwgIw3EXEIkASDG0UEUEfwfwa3Q/DQT03UX3BIo0vDWwaPeYx6Y3EASQfwc3eDXUTDEDSQaDLgMDXaaw0EQ0yXJI%2B0v9aw0TYM7M0MiMlYFbDIZwSQIAA)$Done$

## Links

- [source code](../../../../conceptrodon/pagelivore/right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/right_interview.test.hpp)
