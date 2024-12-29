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
/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = TerseIndependentLeftInterview<Equal>
::Page<Args...>;

/**** Tests ****/
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQSGmakAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzOFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GB5nBDEhXmhsLcyHG6CwVGxuJ%2B/zpAOBv12NwAkiwUvQ2IImA1PgdAUz6f9AcCCJh2QYxSSxRKeZgSUwvEQAHSq7E3SFMBQKVXK5TETD4URirGgnGXcbELwOG4AFXiShZDCwT2djAGmCoBCdYuIADc3gB3XEAdislxukZuMo5coVStQupCnuEeCwpvNFyjN0t1oIN31qCIyiYwHlEajJjDwOz2dzNqEBgUCBrtcjVfDWbbtZjkvlcMVKrVZtb3aj9fzheLpfLXbH7bDOeajmQGoE40wqhSxBug9QNz9Yi8mBhYYAtFwq3dYRZT9fQZ3R/Pe3GBwmbgAxPDEcbUivzpcrRtKdUBLMsSS/H8CD/Od5w7St/wA8dlzwVc0AYDctx3PcDyPE8nyQ09O0IscTH8Kx/DuCAlhuM91XJEAQBYJgAGtMGRDJgAidBURJDIAC92OgkdEJIytq1EsTazwKg1wwsUsJhSSpKjKBdXMAA2TT9UNVC5VNNxky9IQ03eXVSE/b9fzNRjD28TAliWAiVPE28DQIdYGBuDQbzvGlYJcqM6iUZzAvg9zPNoy8Hz85SSKvajQrgkN72IpCrxvfzCJfKU3yISyoIsnChEwdD0CKhNdQAeQIBAHRgwiJwLYgi1AmcIKsggLJKsqLJquqf3UkSAu7eD2zisdZhXOTMO3Xd3zs48lJGgCOySwiyIoqiaLos0l3QRjmLYji8C4w1eLhAShIawKiPWqSZJmhS5vusS1LVMwtM%2BnSjX0kkjNTdNzIK6zsFsvDHNe%2BLFwi4gvJ8mKMsuKHCOCk9HvQ2adxRpD3uVTTtINX6TX%2BlMTKB1VutKgR0GxcH7MhiapPCzAPLhm5otvJGgSZsS0ZuDH12e4gcYAiBRZIkCwP7Nx%2BodIbM1u%2Bd6aWsAwFhO4oolscnN56Gub1lTYa8swYUsZrWulkk5cG4dFaV7sVf7A2Vpc7nte7NGPbbFm2a8i9fO5pWEt113SJSzK9Yyh8kujtKfbinKZb3XULmAA1xXdDMkq8DIjALGcYVBTXGy1JAQCTi3p3AuE04zrkCB1O3I9guOsqjJP4yHZU68wTPBGzxDc/CYAC7LIvNal9ra/TvuG6b/GRxj5GI%2BXnmriFBlaVubBVFYDkTy%2BRlN6P5Ht/2G5sAARy8MQ%2BX2QFO7y/cWQq/KACkYKa6/b9oUN46XDyVCT1NxzRiKgTwuF7JPg7CyCeGsbif1Xo%2BZB/kmQ3AALKsyYFQLwBJeSnwuE/NwKdVQXGIMAQeFxh75ywc0XB%2BCsgTztA6TAToXTPEEADH08QAyYGDHCH%2BYgYKMStrXChC9qRr2Prce04wPiEKmqhZEWolCtGBBAOhOC8EOCyCSMwdMQBiLcBoCyQQbjJAsYYxa%2BFi4ILME5NeSjkAqO1PEaClxNHYIYbogQJIA42SMdPExZiLKWIMYEmx8Di5RUcRYDgKxaCcH8LwPwHAtCkFQJwNw1hrA5jWBsfCYIeCkAIJoBJKwWIBEkMqDQAAOMwZgACcTSuD%2BHqXUrgIYQzSCSRwSQvAWCJFMWkjJWSOC8AUCAUxZT0kJNIHAWAMBEAgDWAQFISpyCUDQOyOg8RIisC2KoOpGkzwaUkDcYAyBVxSGVGYXgukiDEDTHofgggRBiHYFIGQghFAqHUHM0guggiBnRCkTgPBEnJNSeUzJnAqpKg2fmVAsljmnPOZc65HMammwgB4XZ9BsbFKWLwWZWgVgQCQDslIeyyAUAgNS2lIBgBSGSDQWgvopkQBiLCmI4QWgIghbwPlzBiAIiqjEbQpVZklJ2Q3KqDBaCCsBVgGIXhgAkNoLQKZ3BeBYGYkYcQKrvzSrwH6d4sLNylSVFsEp4QxR9IybQPAMR0Rio8FgWFaI8BDN1aQc1xBwFKAeAa4AzqjDlJWFQAwlCABqQYqquiFT84QohxDfLefIJQahYXAv0IYYwuTLD6BdVMyAKxUApAaDqs85INamEsNYMwYyA3PPTPAFYdhTXOAgK4KYfggihHCEMCoIwCjpEyAIftehCiToYPMYYVRujdsaBMNongOh6C7b41dcxh0LDHbYNd06gizFaAu0dVRO0FM2BIKFHAUmkFGbwcZNw0VnIuVcm5OKbgQFwIQEgZtQRcBJaUyNKw6pMCwAkaipAqmSFBMqJpoIekaEkGYSQGkNAaH8BpJp%2BhOADNIEM4DyoNJcA0nUppnSNL%2BEkG05DGkn2wvGZM6ZYG5kUuWZS1ZiLNn0sZYSg5bBOAtBYH6EMZ4mAagMPnLgTTlRcFqQ8/ATyXlBEzR89N0hM1/JzYC3QyRQVMHBbq%2B9j7n1wo4Ai9ZSobgorfScj9MmC0cwU0pjQv78U0sJUBhxpLI0LKpagAl8QtkMpCz5kYmojDyeqHwOgnLKA8sBSKgVya0tiolVKhwya5XugVUq2Fqr1Wau1cm/VBajUZPwAaXR5qdUZKtcgG1yb7V1Fhc611AqPVbAyd631JSA1BswCGqrI9AvRtLAoeN/DE2MGTZptNXydOyD0wCjJhn80RobVYYtXWy2wcrdWzgtaCC02LrtptLb4htoteW5dO6XDOhPcEZ0F7FjjqKFkV7s6GgfcPduhofRJgbryKeuoK6QcDH3Yurdx6wcDqPXusocOQOrHWLe9HfSLMsc4I59FFyYuj3k4p2pv7/1PKAyBgLnGIOYCgyMWDfSiMkYU2hkM/gmndNBOhzD9HmOAtY7YdjZL5mLJWWspF4XBP7MOaJ4gLAMUsAUH6VcfpSd9nGCpgDbbXmyC0ytlN63c0gFBKQYzpnIUEYfTCoX8K%2BPItRcr1X6vNf6XzHiyLtKgOglA2LilwXQt0u2d7wlIA1cpBSMiDXTTkRa4IMiVQ5yEscodMl3l/KxUZaz%2BKyV0q8shflYq5VNXMBqo1WIcrfrKuGr63qk19WLWAua61v17XHW8C626hEvWvXPMG7wYb6RRvinGxGzjfAY0zYTUmv1S3PkSFW787NG2dBm%2B24Wxt%2B3S0dsyVWrIOrtgMSu5YZtL7W2mUO52yHT3e0vcR3oIdqPL0zonQ0X77%2BsgA6XUD3oCPcgkc/8BBocf94d%2BhXsz0YcX9Ptr1McvlzM7cxl8dk8LkVc1cDx3cTRPdKdAM8QacONyV6dGcYN71WcQBmllRQRQR/B2l6NsNqCQxKNBdkCJkRcZlwM4MQBJB/AkMukQxsM6lJBWkuAGlPobdQQkCX1OBaciCbd7kWDpC2CA8VgA0MhnBJAgA)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/terse_independent_left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/terse_independent_left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/terse_independent_left_interview.test.hpp)
