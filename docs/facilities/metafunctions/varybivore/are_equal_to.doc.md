<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreEqualTo`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-equal-to">To Index</a></p>

## Description

`Varybivore::AreEqualTo` accepts a variable and returns a predicate.
When invoked, the predicate returns true if all the arguments are equal to the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> == Target) && (V<sub>1</sub> == Target) && ... && (V<sub>n</sub> == Target)</code></pre>

## Type Signature

```Haskell
AreBoundedByOpenInterval ::   auto...
                           -> auto...
                           -> auto
```

## Structure

```C++
template<auto>
struct AreEqualTo
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

```C++
template<auto...Args>
using Metafunction
= AreEqualTo<1>
::Page<Args...>;

static_assert(Metafunction<1, 1.0>::value);
static_assert(! Metafunction<1, 2, 3>::value);
```

## Implementation

We will implement `AreEqualTo` using only `<`, meaning <code>Variable == Target</code> is expressed as:

```C++
(not (Target < Variable)) && (not (Variable < Target))
```

Here's the entire implementation:

```C++
template<auto Target>
struct AreEqualTo
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Target) && not (Target < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
    
    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < Target) && not (Target < Variables))) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQgZgCcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmAMxuTF5EANQAKi3AmATH2CYaAILjxF4OFy/EOACOXjEV1QzxeJgCVleF2hFx2ewOmGOp3OqAAdOiAGotPBMGL0BSPUEwi7vT4EC7KYioIjKJh3Ikw8GQl7E4mzRzIC5oBjjTCqVLEC4xVCeC4ANzEXkRUNZ0KZFwg6NR5gAbKqIAxqQqscQcXjMAoLkjrrd7ksjWY1ZaLpryRAbsQ7uTjTq9filh6jQEACLHZnE8G%2Bo7MhnQuH7JiHE5nIhKl7AX67RgEAlHJ4y6FeTJGCl0zBGo7eilUml5pHxxNsQQKJWE4Oho0Z2G7CNR5GxzHY3H4wlN9l4Tnc3n8wXC0W0u4AfTFjZZjIhCtrlvVtu1Xf1huNDqd5tVqptWvtpudJwuru7Bo9u59ftBgdvr1BAHoAFRv98fp/P99XbBCK7vl%2Bryvh%2BoFAWCrzhgiSIxmi6I/MAqbpi8WbhMAFwALL3EwVBeAwDjZHehbfL82AAkCIInFwvYvCAIAToiJwITW6J1iGrz9sgk5MAoSitBAWHNLh%2BENEiXCkBcXCohojx0RK3iYEsD5vM0HLcbx8QEBAYBgJh2HCQRAhiRJZgSUcskgPJUpKcGHArLQnAAKy8H4HBaKQqCcG41jWCSawbPm5hHDwpAEJodkrAA1iAjlmKiARmJIAAcSWORoSSxRoKpJUc%2BicJIvAsBIGgaKQrnuZ5HC8AoIClWFbl2aQcCwDAiAgGsBCpOc5CUGgex0PEkSsFsqhJSqAC0KqSBcwDIJyUiomYvCYPgRC6ugej8IIIhiOwUgyIIigqOoDWkLo4kAO7EEwqScDw9lOS54UeZwADy5xdeSqBUBco0TVNM1zZJkiLQqHj9fQgpBVwSy8PVWgrBASB9akA1kBQEAo2jIDAFIpk0LQOzEDVEAxM9MThC0ACed28BTzDEFTr0xNomAOLTpB9VWBCvQwtA06dWAxF4wCnLQtA1dwvBYCwhjAOIgt4L8BFigaz18mz5xbCF4Q7A5p20HgMTXYzHhYM9BC6kVUukKrxDCko3q7HLhtGOFKxUAYiEYngmAXa9qSMBzW3CKI4j7SHR1qM9536HLKA%2BZY%2BhGzVkArKgqQNJL43jOgxzeqYljWGYFV2%2Btatp90bMNC4DDuJ4HR6KE4RDJUIziUUWQCFMfgdxkXcMPMwwJOJdjV70ExtA3%2BSj3U48CH0rRD23I%2B2JPPd6LMS8tws7crAo/mbBID0cM5ZXPZVv1jZN02zfNINmAquCECQFrBbDoXuysCCYEwWAJBAKK/gjioiSEcAIkgNCSESiqEqjkVQpH1gVUgRVgqohVFwbKSQkqYMcpILgjkwEqnPqdSq1VaqfwaojVqSN2ofW6hjLGkMhpsE4C0FgYoAjjSYFyAwOYuBJFRFJdyK0X7rU2rIHa4dpCRyUNHU6uhTJXRurTE%2BZ9yq8Equ9Tq5wLjfQuOwzh3DeFy0koI4RYNUAQ3iG/MwH94aNVoUw%2BIPVMZWNRpDEAhiuHID4bjJIXBSoEyJiTMmp16bUw5hExmzNWbsxtlzZMvN%2BbPSFiLMWEsOYyxdlsdy%2BBlaOFVpLERqhNY7A5rrOoz1DbG2pmbXJcMrYcztg7TATtZZGFdqAKhfAvYKB9n7AOQcbYhykXtGRsgo4nXcoouObtC5WCTjU1OgCPKZ2yNnXO%2BcFnF1LvEcuKz95z0Mn4CArgN7iWbuUYeehO4NAuWkfuDRl6LFnj0Be69p69yricxeAwd43NHp8vI3yt7/OuSvY%2Bqx1hHxhnlU%2BT1SGcAMcQDhXCeG%2BNMQIoR0kn6rVftDexX9SA/z/iMVZSDCogCOIIqBARCEBACEcaBkgpriQ0S9KqtgKEOOofAWhHVPquOccQFhWx2EAxYAoMUnIxTYoROMZa%2BLxHiVGWHcZB15ByOmToalpBlG3SlmoxFFU3r0K%2Bj9CV00pUyvFPKyMBo7Tgw8TYoKRwiU9Kce4tGwrvWeJlakVI04BGTgVQQbiqKpp8DoCEygYT3LRIFiFRNsTq4c0SYIZJAs8mYGFqLMQmSbbZM6Q00g%2BTx5FPVqU5AWsKmCCqQbI2Jsqb1Itk0m2LSMhtOdp0tC7tel0n6b7f2gdXIhTVbtCQEzDrapjnqvxCci5LJTvAdO6yBCSyfLnRdiyLAl00WXPAWBDk/JrmcuuDyrmt1eY84o2QHl3OyC89up6J79AeWPX5k9n2rzBR%2B79ALIVwoPjCvaxqSGmo4CilgkrpWyvtTscYeKxFvxhnDYlpL/6UBPsgoqyRURHCOI5NK%2BCSqEYCNlCDmjODkLqsS6KgRFr0q4FIJIdKwFcCCPrI4JrqNct5SfJaVHOXoaoSsO2mRnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/are_equal_to.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/are_equal_to.test.hpp)
