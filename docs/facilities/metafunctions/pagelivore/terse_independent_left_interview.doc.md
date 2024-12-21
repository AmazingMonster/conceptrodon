<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::TerseIndependentLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-terse-independent-left-interview">To Index</a></p>

## Description

`Pagelivore::TerseIndependentLeftInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

`Pagelivore::TerseIndependentLeftInterview` prepares fewer base cases than `Pagelivore::IndependentLeftInterview`.

<pre><code>   Preds...
-> Vs...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Vs..., Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Vs..., Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Vs..., Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
TerseIndependentLeftInterview
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct TerseIndependentLeftInterview
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
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

template<auto...Args>
using Metafunction = TerseIndependentLeftInterview<Equal>
::Page<Args...>;

static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

We will implement `TerseIndependentLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct TerseIndependentLeftInterview
{
    template<auto...LeftSides>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...>
            struct ProtoPage
            { static constexpr auto value {-1}; };

            template<auto First>
            struct ProtoPage<First>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else
                        { return -1; }
                    }()
                };
            };

            template<auto First, auto Second, auto...Others>
            struct ProtoPage<First, Second, Others...>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else if constexpr 
                        ((...&&Predicates<LeftSides..., Second>::value))
                        { return 1; }

                        else if constexpr
                        (
                            ProtoPage<Others...>
                            ::value != -1
                        )
                        { 
                            return 2 + ProtoPage<Others...>
                            ::value; 
                        }

                        else
                        { return -1; }
                    }()
                };
            };
        };
        
        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAJwAzKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5snhyN5YANQmyW4EAJ5pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fIE3QWCoLzenw%2BBEwLDSBkhp3OUJhTDhZyYXiIADosS8jgcmAoFFiMcpiJh8KJIc9kq8PhNiF4HEcACrxJQASQYWGunMYg0wVAIHMhxAAbnhMAB3MEmADsVg%2BR0VR0h0NhmHhaMxWJC/OEeCwVJp7yVRzpDIIRxJqCIyiYwHVCqVsvlxpNSrNjKEBgUCDBbqdcr9/rdKqRKLcmtQRNBjuD7vu5stxGtqFt9qDccVztNLUcyFxAgmmFUaWIR0jRxFYi8v2dAFouLKACKnCwnGUt5IujOZ0NqjXo1BHABieGIExjrszOfpjKtNrt6rOo/HBEn06zcqdsY3irmeYLDCLJbLFar3lrO93zp7u5NJn8Vn8TYgyyOdZxgJAIBYTAA1rcWTABE6B3PCWQAF63Gu1K3nem4uvB054FQh7HqWJxXkhJpQNGZgAGzmPhJJkngFKYFSbg6gKQj6hRRKkCOY4TtS37njWyzLHB2EIUcpIEBsDBHBorbti2HzcTx9RKJJ2HZvxgnvo2XZibJG7Nq%2Ban%2Bs2rZaapXbSlh/p9siS4RoOTGroxFZCJgaCctZg5EgA8gQCCsuuG4eha86pou8IrhMjG2fZ6CMa57njtGsFGW62ZZrFcb7mRaGQie5YWexl5TneN6Jepj4Pi%2Bb4ftSOboN%2Bv4ATcQEgWBZyQdBnk8e2iEtW6KGpcWGF6buuHYgRREkeSpmUdReoGgxlksdgbHVpgnG9epW4KcQQkiSpOkSfl8HSb8nX2ehZZLdO/UYkRQ2kiNlLwuNtGTViwV2QI6AvHNF6LTtuUrZgAlrUcyltlt4I5e1Rx7UcB2FmlpYnZmEBw7uvlpmZEWstFRpg3G701kcYBgKcTZKYjwZcV915biT06rUJZgnJYSYpij8Jo1F2IxaDWOKjjS5A%2BTy3iSDXOKntVNxT9f1CQ2onA2DGlk5z046QZX3K212kdrpsWSSZ4aRkS7zAKSUK8oakleFkRiWoufxE16%2BJICAuu/Mj/lnIbxtsIIhLs68Ks5Wrhk5c7A5ahiHuYCb3vNUcFvhMA1v2rbjMLum7tG5HXsED752wf7gfbe8AD0ABUZflxXldF2Cpfl8yFHZ0cFfVx8teV%2B3ZctyDXwMAcXjHPC9lbGk2eTmCIeohZbKOUQRwAFKTt5RzYAAjl4YjSoGO7Jfmh0w2WMSoJ4lbzT2zpsrbhPzwXnya/nEKIv2k9h%2B8xDAGbHxx1bACyv1MFQXhe6NGTiyccmAORclcLycaQp4hiklPCVe69aCTm/Mzd2b8c6gnvu8HeNx8RKDaGCCAv8WgAKATkeEZg3ogHQW4DQjEghHDMIxahrEQBZUvskImZguL%2BzwQQ%2BIa4PgkL/uQhwlCzjS3YXQhhANWGsJoZwwmV8Gx8IsBwVYtBOD%2BF4H4DgWhSCoE4G4aw1hTTrE2LWMwyQeCkAIJoTRqw/wBEkBiDQkguAymSBofwGgCL4TMAADiCfoTgkheAsAkBoBh%2BjDHGI4LwBQIAGEOIMZo0gcBYAwEQCAdYBA0jonIJQNA0I6DxEiKwbYqggn4TrPhSQRxgDIHzFIDEZheCkSIMQfUeh%2BCCBEGIdgUgZCCEUCodQ6TSC6CCBKB4aROA8C0TovRjijGcGcuiQpFpUCoRqXUhpTSWkAzcXTCAHgyn0GOjYrgyxeBpK0KsCASBSlpHKWQCgEBXnvJAMAKQLCaC0GFMkiAMQ1kxHCK0C4izeAQuYMQC4zkYjaDsmkuxpSs7OQYLQaFUysAxC8MACMtBaDJO4LwLAv4jDiDxWOVFeARQUTWcWOy6Jth2PCJCbRUzaB4BiA8BFHgsBrPuHgKJ5LSCMuIIfJQTYoSGGALyowjjVhUAMO/AAauKCUzluQwtGcIUQ4gRn9PkEoNQayZn6AVSgMxlh9B8uSZAVYqAR45DJXWQEhNTCWGsGYeJUqekGngKsOw9LnAQFcNMPwQRQjhGGFUUYRRMjZAENGvQxRU0MAWCMBIQQw0SIEP0KYnhOh6ALY0Ytgx42LCTbYSY7RS0FHzQ2nNia82hssVsCQyyOC6NIHE3gCSjj7PqY05prTTlHAgLgQgJB6a2LufYlVqx3JMCwAkV8pAXGSGSBiFIMpJAeLMJIfCMT/D4USGEjgETSBRNsRifCXB8JBMSEE59/hPH%2BBSPhAdayElJJScu9JTycnPLyVsopnzvlXMqWwTgrQWAihlHWJguIDBWy4IkDEXB3GdPwN03pQRTWDONdIU14yLVTN0CwuZTAFnkt7f2wd6yOCbIKeiI4uzyzECQyhtDeJMPYdwxoadFy3lXIXbw%2B5KrMkvNQJc%2BIxSvkKYk6MRDyG6yCb%2BYkLgDDAXAsoGCqZcKoX6tMwipFKKHD6oxbyLFOK1n4sJcS0l%2BrKUKppYY/ApIJGMrJYYllyA2X6s5fUNZvL%2BVQqFdsQxorxV2KlTKzAcqqWKvjrJtVdoFBaslLqxg%2BqSNGuGeR2QlHJmGJo9a5VPqrD2si06rdrrGgeq9dw2rfqA3xCDUy51PRw1%2BEjZydNsbORtqWMmkoOQRvpBTY0cbdaK19AbTNpbRbW01tzeWlbTaY31vmJt9tPa1gbG7bc69zH/2cB43x1D6GFUA2E%2B46ds7ukLtuTJkDq7MDrtGFu7lt773YY8TKb9MpvGSBPQ0oILGAO2CAw8jJWTcn5O2cpmDFSqkId44clgCgRT5hFFhjEaoJj4bnUGvpshSMlYNeVy1IBUh0YY0si7qypkJPY9srjqFEO4/x4T4npOLTnNU%2B8hdyQl2I6efJxTHySli6uRw5AaQ0g3CJ4kG4wv8E4/I3QQzoLwWQoReZ43iLkWotswpzF2LcXecwASolYg3MSo89S2LFK6V%2BaZVMoLIWJVhe5YYyLAqLgxZFT0hLvAkuZBS/K6lGWQN8HVTl7V%2BX9F2KK0MiQpWxnmoqzoRn1XjB2psA1kNRi3WFk4EXL8HXLD%2BqHYGuijXQ31AGy4Ybu29BxoqFtybWaZuZvm4dib/XC1NB2/kPba3J8Hb70dltAxVsbYXxNztp3hlMfZ/E67fPGl44J5WIXo0RevfnbsD7wHHnfd%2B5u3tgOQBmGw8kZI/g/GeJia/mUL6/0c84IBqkiutuiAJIP4Puv4EEgRIkJIIkN4skDKFwKkNyskDvkOgAdfk4teh0n/rvokpgZxJKqyDkKAUAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/terse_independent_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/terse_independent_left_interview.test.hpp)
