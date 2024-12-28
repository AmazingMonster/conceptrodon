<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SensibleRightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-sensible-right-interview">To Index</a></p>

## Description

`Varybivore::SensibleRightInterview` accepts a list of variables.
Its first layer accepts a list of predicates and returns a function.
When invoked, the function first binds the arguments to the end of every predicate;
then, it returns the index of the first variable that satisfies all newly formed predicates, or `-1` if it cannot find the variable.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Preds...
-> Interviewers...
-> (...&&Preds&lt;E<sub>0</sub>, Interviewers...&gt;::value) ? 0 : (
   (...&&Preds&lt;E<sub>1</sub>, Interviewers...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;E<sub>n</sub>, Interviewers...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
SensibleRightInterview
 :: auto...
 -> template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct SensibleRightInterview
{
    template<template<auto...> class...>
    alias Rail
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
using Metafunction = SensibleRightInterview<0, 1, 2, 2>
::Rail<Equal>::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::value == 2);
static_assert
(Metafunction<-1>::value == -1);
```

## Implementation

We will implement `SensibleRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct SensibleRightInterview
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...>
        struct ProtoPage
        { static constexpr auto value {-1}; };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};

template<auto First>
struct SensibleRightInterview<First>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...RightSides>
        struct ProtoPage
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<First, RightSides...>::value))
                    { return 0; }

                    else
                    { return -1; }
                }()
            };
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct SensibleRightInterview<First, Second, Others...>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...RightSides>
        struct ProtoPage
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<First, RightSides...>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<Second, RightSides...>::value))
                    { return 1; }

                    else if constexpr
                    (
                        SensibleRightInterview<Others...>
                        ::template Rail<Predicates...>
                        ::template Page<RightSides...>
                        ::value != -1
                    )
                    { 
                        return 2 + SensibleRightInterview<Others...>
                        ::template Rail<Predicates...>
                        ::template Page<RightSides...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMz%2BpK4AMngMmAByPgBGmMQS/lykAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZn84WQ3iwNxM/jcBAAnk8APoEYhMQgKGHYYHmMEMCFeKEwtzIcboLBULE4n7/WkA4G/XY3ACSLBS9DYgiYDU%2BB0BjLp/0BwIImDZBlFxKYXiIADp5VTLuNiF4HDchIwMjF6AAlPDABAEZmCeIANzeAHccQB2KyXG4Om6i8XczDE53s11SmWoeWyrE3CFMBQKP3KYiYfCiUWY/zY%2B2O5Wqgg3cOoIg69G0YGO6G2nO5x0eiVu2HSuUKuMFws3JNqtNEZRMYBuhM1ky22vNRzIQMCcaYVQpYg3cuoG6msReTB5iwAWi4HbuMIseeX/jtQLbheLXrLPr9F2AEbFjAIsfjFxrDq8GSMqebM5hd1TxHTqCbLeJR5PnPPfqpDdqzXFdqSvIsxU9SVYV3aC3DHAC40DAwQzDCMo1dC9gNvcJgBuTM6GhfwXwbVACOzWFw0jPBo3eRDsSAy4l1ApjLlg0t4J9G4ADE8GIcZFQuOsUw1BgtV1fVDWNUViHNTArVhXj%2BIIQSO03XN2PdSCS29Ct/SQoNUPlKiMJjQTc2E1933I4C1OAjTtL3Ti9L1A1hDwLAsO3CzUWTKzG0fezHTU4LvOvWYez7MTRSHEcxwnKcnzC9t82S68HRMABWKxMruCAlhuOcAzJEAQBYJgAGtMCRDJgAidAUWJDIAC9qpUqs0vSuzOvSx08CoKKB1i6Eet6m4oAAswADZzCmkyaMw4klPGUh8Mk9zPPo0rJ28TAliWIKxtzEKIwIdYGBuDQVxA1jwKO686iUQ77tnG5TvOwrFw3G67pepd8ue47rXXdTr2Yxit1%2BhyXTghD5R/TBT0ELyocdHD70/J9iP8j9AthBGkf/SsGNBjLgZYyHoagjjNP3PSA0M0N4ePRG/xR3N0bw8iiJIt8Myzb8WcJpn9JJm0QbA2nnPHZaCFW%2BKNTQBh0Hlg95QAeQIBB4hRyzRPEzBXKkk1ZMtJa%2BJW9VMCVlWbk17X%2BPom1SadRy4KluHReQ4MRfm2j2cTXz6z5siBe3brUYdD21dlI2NveczwqDlNSMx56Qoy0au25GjBpi4dRy4nbpxGyPCwjl7guyrK8oKoqkJKsrKuq2r6sa2EWraxPK4ryvC36vPBwLwGjomhVptmv3FsUi25bWtyhA8ujie2xL9pHsaTswM7iAuq7vuY26%2B8LR6ZwHpWhuHrP0rH/0J%2BmqezNhRWBFtuPF82leQGLvaDuvsHOzvV3jcL6q5D6U2Po6U%2BNxz79nzsQDevUICIPuvrPA2pDbrWkmaM2sJ7Y6ydv/MapV2L4QFpRdCC0YyELLsfEhbsZxp1hO/JeItu6QNzKvXaNwwBgGfJ9FB14/60KOiFQRY0gEXTMNCSwVsxLoIkm5bBpt5LEnwY7Ym4jer0JhjOGyFDqL%2BxoRwmsOjqYPi/Mw9aH9l6iy0elLh05rr2OCuTI%2BJjT4uLJquSRAiD5uJESlWuiDwYuyBhLdxNZo56QJmzdhHM7x4UxjzHGTC3CxLPGwqsENwkU2AlLaJvpibeyMrKDJyN2GczIYRfhpF9HpKFmzJ2ENQlgQFIKfkhwbjYFUKwdkM4vgMkFPSW6jJukAEcvBiF5PsQEhSWSqyIDcAAUoJSy2BJliGdsBCKucL7wJuDEVAngEq7VsraZkPN%2BGrPJi025m4hm3AALLbyYFQLw%2BIeSDLYgw3SRSynEGACjKpLzmjvM%2BVkFJaCMFx2UXJBSbgNCrWSDcMwq0zCCVKvUjZUyKLYFKmki4gKsli1GV0gAKu8c8MzTjAl2cgJEPt4gqUuBAUFbyPkOCyMSDFcZHFY3XC%2BMwB0Ib0sZSGZlwI2WvPBVygQxIFxYn5Vc7GC4RUWA4CsWgnBMq8D8BwLQpBUCcDcNYawtY1gbCfKCHgpACCaE1SsCqIBMqSFlBoAAHGYMwABOH1XBMqeo9Vwa01ppDao4JIXgLAJAaCRfqw1xqOC8AUCAJF9qDWatIHAWAMBEAgDWAQFIMpyCUDQGyOg8RIisC2KoD1U05xTUkDcYAyBexSFlGYXg1EiDEA8nofgggRBiHYFIGQghFAqHUJm0guhkgWjRCkTgPAtU6r1Q6o1nB1YymLSmVAA060NqbS2ttIC3XSIgB4Ct9ARy4i4EsXgGatArAgEgctKRK1kAoBAd9n6QDACkGimgtAZKpogDEDdMRwgtHhMu3gUHmDEHhOrGI2hrYZtteWv86sGC0FgzOrAMQvDAHgrQWgqbuC8CwOVIw4gCN8XQ3gU07wN2DmtjKLYtrwiigjYa2g6C0RIY8FgDdqI8Axso6QZjxAjlKAeDR4A/GjAOpWFQAwQKABqlp1ZPH1bawdwhRDiDHQZydagN1zv0IYYwZrLD6HQamyAKxUApAaBRucZJnymEsNYMwibpN9s8vAFYdhGPOAgK4KYfhkihHCEMCoIxkiFEyAIKLehksNHmMMKo3QwuNAmG0TwHQ9ChblfluYcWFiJdsAVtLYwCtZYS1UELlrNgSFXRwXVpAE28CTTcQ9jbm2tvbee8auBCAkBkUkB9dqVMrG1kwLACR8qkGdZIfwsofX%2BDDRoSQZhJBTTjZlKaPr9CcCjaQGNSRZRTS4FND1Prg1TVdQGrbU1usbqTSmtNs3M0vrza%2BgtO6S3ft/Te6tbBOAtBYKaa0c4mDe3vFwH1souDuu7fgXt/bkgGeHcZ6QpmlDmZnboNFC6mBLsox1rrPXN0cG3UWmUNx939frYNxHeFkeo/deNK9H6b1TeFY%2BlT2a32oGvfEUtP7xf85GEGIwyOuBIuA6BygEGZ0IZg3B0gmukMobQw4bXWGzw4bwxuwjxHSPke19R6zdHDX4AjFy5jFHDVseQBx7X3G6gbv4zEQT8JhNbENWJiTtrpOycwPJu3uERdqebAoLT8kdOMG17jozo6CeyDM9Ow1pOrPKe81YOzfvHMrZc25zgHmCDoC87ZiwfnesBdYcF3LZWXDKzq8EZWjXFhJfSCl7IRW8j96KFkXv1XSsND6JMYf0W2/T4a5V7LJXatz9XxVsoK/72rHWG1nfEaaefc4Kzo9zb5ec5R2jjQY3MeTbvTNp9jrSALaW5QDrF2rso929aTKPrQ3%2BB7YHaSDJC05fa2A/ZP7/bwCA6Fq7pS5g5Vo1pQ7EAsDHosAKCmi9imhc4ljjAY4TaBYDqyB46Z7jryBE6546ABCkDk6U4rpnadbrozpJoM67rM4HroGYHYG4GYQpiXoy6fpTb%2BCP4i6A6IFfplqCE3rfzIApApBIg4E%2BpIh4EEBIiqBNp8B0Cq7gaQbQZIba667IaoboZG7i7Ya4b4YO6YBEYkZiDW6Sa260bB5UYMbO4sYzru6e6Sbe68a8B%2B4B5B6iZ9ph68AR7pBR5igx7KZ/Z8DqaJ7aa6Zp4kEZ4SBZ4TqUEWY0EGCF7172YxBl7OauZZAUbbAlRF6%2Bb%2BbxCBYsZOYL5ZAd7uDr4xY97L5NbpYD4NBd4Zbj5tF971ECAz6Fa5Dz5T69BL5b7tH1b9Bd6zCtAT7Na75WrtaMFH4sEn4aHNoYFYETi8Exj8Hja9pTb3rC5/bzaYCLYjArYRqf4gC%2BqyiBCZSBogFxqBDWj3YfbrHJoQHppzarYgCSCZSbYhrWhxoeqSD%2BpcBerTSMH%2BDMGJqcCnHPodZdqfEInfFQErDSYZDOCSBAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/sensible_right_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/sensible_right_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/sensible_right_interview.test.hpp)
