<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreNoLessThan`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-no-less-than">To Index</a></p>

## Description

`Varybivore::AreNoLessThan` accepts a variable and returns a predicate.
When invoked, the predicate returns true if all the arguments are greater or equal to the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> &ge; Target) && (V<sub>1</sub> &ge; Target) && ... && (V<sub>n</sub> &ge; Target)</code></pre>

## Type Signature

```Haskell
AreNoLessThan
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AreNoLessThan
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
= AreNoLessThan<5>
::Page<Args...>;

static_assert(Metafunction<5, 6, 7, 5>::value);
static_assert(! Metafunction<6, 2, 3>::value);
```

## Implementation

We will implement `AreNoLessThan` using only `<`, meaning <code>Variable &ge; Target</code> is expressed as:

```C++
not (Variable < Target)
```

```C++
template<auto Target>
struct AreNoLessThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Target))) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < Target))) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQgZgCcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmAMxuTF5EANQAKi3AmATH2CYaAILjxF4OFy/EUaghmAUCiuCEMzxeJgCVleF1hFx2ewOmGOp3OqAAdJiAGotPBMGL0BSPcFwi7vT4EC7KYioIjKJh3ElwyHQl6k0mzRzIC5oBjjTCqVLEC4xVCeC4ANzEXmRMPZsJZFwgmPR5gAbOqIAxaUqccQ8QTARcUddbvclhbjQEACLHVmkyG2o725ly2EI/ZMQ4nM5EFUvYC/XaMAhEo5PN0XLyZIxUhmYY1Ha1Uml0%2BMogNBtiCBQq4nO8FM927T3e1F%2B7G4/GE4mRzl4bm8/mC4Wi8X0u4AfQlxsjiuVmPVmu1lIgeoNhMTblNxDuBAtSytTtZjrthdeAHoAFQ73d7jfg7c7q7YIRXXcHzd769by8Q14epEo30YzE/YBhiMvaPhYAXACy9xMFQXgMA42SFkm3y/JE/yAsCoIMCiACstYvCAIAdsiJzvrmg7hmurzgvWyCdkwQLxAQECAc0IFgQ0KGkBcapMUEFyoeGGFSt4mBLIRbzNFyZEUa0EBgGAAFAXR4ECCiLEXGYTFHI8XHSrxdocCstCcMhvB%2BBwWikKgnBuNY1hkmsGwJuYRw8KQBCaJpKwANYgMhZjogEZiSAAHD5yEaEk7kaGqPlHPonCSLwLASBoGikPphnGRwvAKCA8UOQZmmkHAsAwIgIBrAQqTnOQlBoHsdDxJErBbKoPlqgAtGqkgXMAyDclI6JmLwmD4EQ%2BroHo/CCCIYjsFIMiCIoKjqFlpC6FwpAAO7EEwqScDwWk6XpjlGZwADy5wlZSqBUBc9VNS1bUdRcXVmEqHiVfQwo2VwSy8JlWgrBASAVakVVkBQED/YDIDAFIik0LQOzEGlEAxHtMThC0ACem28MjzDEKjB0xNomAOBjpAVdmBAHQwtDo/NWAxF4wCnLQtBpdwvBYCwhjAOINN4L84ESoCe0CoT5xbHZ4Q7Np820HgMRrTjHhYHtBD6jFrOkALxCiko1q7JzMtGI5KxUAYH5YngmDLQdqSMMTI3CKI4iTfbM1qHti36JzKBmZY%2Biy2lkArKgqQNCzjXjOgxzWqYljWGYSWa4NguB90hMNC4DDuJ4HR6KE4RDJUIxLUUWQCFMfjFxkpcMPMwwJEtdhp70ExtNn%2BQN3UTcCH0rS14X9e2C35d6LMvf5wsRcrAolmbBI20cLpCV7clF0Nc1rXtZ1kjdUquCECQxpmLZH32UbKwIJgTBYAkEAuf4RzokkRwBJIGiSN5apxchaopFLUWkDFWy6I1RcFCkkHyoDkKSC4MhJ%2BLFEq8GSqldKp8so/Xyr9Qqx1SrA1Bi9GqbBOAtBYBKAIjUmA8gMLGLgSR0RcHRIZPq%2B9BrDVkGNJ20gXZKDdvNXQilVrrQxvPReCD9ocCOsVc4FwzoXGIaQ8hlDOZ3VofQjQj1UDPXiIfI4ZgT5fWypgvB8Qyogw0QDF6IA5FkOQFQiGSQuDxWhrDeGiN5pYzRsTdxOM8YEyJurUmIYKZUz2rTemjNmbE3ZvrLYhl8B80cALFmjDVAix2MTCWdQ9oyzlmjRWMTPqq2JprbWmBdYcyMAbUAaC%2BCmwUObS21tbbq3tuwianDZCuzmoZPhntDYxysL7bJAdb5GRDtkMOEco79LjgneISdhlT07jJPwEBXDDyWnncodc9AlwaOstIVcGh90WB3Ho3ch5twrqnZZPcBjj22Q3C5eQrmjzuVs/uc9VjrFnu9CKC9drzRXlYhRNilE0LoQw3e/UD5vT0WfUgF8r4jBGX/aKIAji0LfgEWBAQAhHHfpIFqS1RFINsCg/R6D4CYKKidExRjiAEK2MQ66LAFASm5BKcFSJxi9WhSwpaLTHZtKmvIbhXSdDopWmtDarNhEAqSodbBp1zrMtaqy9lkouVekBKOJ65itE2SOHC6phizGAzpWaix7LUipG7DQzs3KCBkWICwFqfA6DOMoK4wyXjqZ2V9T4tOxMAmCCCdTWJmA6YMzEBE9WUSKn5NIHEpuiShYpOQKLdJghMnS1lvLVGeTlaFPVsUjIpS9YVN/EbGpDI6kWytjbfSdlBXjQkO06aYr3aStsd7WOgz/bwCDmMgQLMNwR17QMiw8dEGJzwFgBZ1z06rMzvszZBcTkHOKNkfZuzsjHKLou5u/R9mNxuS3fdA9XknvPfcj5vzp7fImnKpegLOCyJdSytlHKtU7HGFC5h2j3qfXhYi6%2BlB57/xiskdERwjjIQCtAuKsGAihRfQqlKZKMrwtcoEbq2KuBSCSFip%2BXAghSyOPKxBnBgNoPnj1NDVGMMUpWJrTIzhJBAA)

## Links

- [source code](../../../../conceptrodon/varybivore/are_no_less_than.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/are_no_less_than.test.hpp)
