<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::TypicalGetReturnType`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typical_get_return_type">To Index</a></p>

## Description

`Functivore::TypicalGetReturnType` accepts a function-like type and returns its return type via the alias member `type`.

## Type Signature

```Haskell
TypicalGetReturnType
 :: template<typename...>
 -> typename
```

## Structure

```C++
template<typename...>
using TypicalGetReturnType
{
    using type = RESULT;
};
```

## Examples

We will extract the return type from several function-like type.

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

/**** SupposedReturnType ****/
using SupposedReturnType = int;

/**** Tests ****/
static_assert(std::same_as<TypicalGetReturnType<decltype(fun)>::type, SupposedReturnType>);
static_assert(std::same_as<TypicalGetReturnType<AbominableFun>::type, SupposedReturnType>);
static_assert(std::same_as<TypicalGetReturnType<decltype(FunAddr)>::type, SupposedReturnType>);
static_assert(std::same_as<TypicalGetReturnType<decltype(&Tester::fun)>::type, SupposedReturnType>);
static_assert(std::same_as<TypicalGetReturnType<FO>::type, SupposedReturnType>);
```

## Implementation

The implementation of `TypicalGetReturnType` relies on dissecting the structure of the function-like type into parameter types and return type using the metafunction `Analyzer`.

```C++
template<typename Fn>
struct TypicalGetReturnType
{ using type = Analyzer<Fn>::result_type;};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAHFykAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn4JdpgO6bX1BIVhkdFxrXUNTdlD3b3FpYMAlLaoXsTI7BwA9ABUm1vbO7vrqyYaAIIbWwDUACKYia6MyHiYCmfbB8enex87r0eHJ9tnR2YtAAngAvaLPLbfAiYFiJAwws4mADMbgIwJuzDYKOwvwUBGIXgcAKBYOiymIqCI6JuSIA7FY6RcUVZjr8YXCEZgkaiaYxWNyAEqYAikM58rGYAB0MqOxGAChxeIJRIIJLEZOIFKpVIxmBRbmFBAgcoVMqlMyVbIZvzOdrOXlSRjOxEeXloBAA%2BnyeRczkaWb8TEzA2zjhz4UxEQaJQL/SKxbG2ObTYrkbjjvjCcTARrwVrKdS9QajSb5QpzTMzmgGPirT8bcd7Q6ncAXW6Pd69b74wRQw3mcjWT9w7DIzCY3rJWcAGIMetZ1XqkH5kBnRJeCK0PDIZea7VFm4Guc4%2BmMwfD9ljrmTzFxk/p5XZtW5lfRY8Mdb1tcbrc7vf5geupHqiD7YGewYXkGo6clG%2Bq8lOcYALKwnOiaIWwZy1M%2BizwRmRyLjmpL5gaKEsHOWEqg4uEgCAX6PscP6btuu6vvuhbAfBbhkWBEEhkO0FHBGN4IXemEzgA8vWroAI5eHgrpPLJ8mKRBZgAGySbRqA3MQUYkBAloCSGmZUS%2BxHvqBUkMUcTF/qxFnEAaWDIB6eoQOYmkSdpun6cQhlGeBwbnv2vzvJ8EWbN84VnAAkpysKMHU1SQlFYWRRl%2ByCcJcG3vy4nzjZhFqgAKhiO5iAA4iKRqLAwZVHtaFgtsEbY%2BiifpsSRoGFdgtGKe6Xp8oG/GXm8mUvOl5zYKorDwtyk3jRNaVhj8ZjIsErleFgPJuDWyyJAQab4VNmxnFQXgMB0AhPItRzBNuIRnMEaoXQwEAvWKL3rJaDLtgQdVnBoLL0syq0xUwESoCwwSQ/Q52XddtapVlxyOq1AJQzDzBbpgM6XT2L0fYIX2CD91Y3X2Ang/8b1I%2BuqAvdEt1Qr8D3BNyTBeEQs6XUc6DoMQZ5Ihpb2g6FS1nckTNCzzbAlBCdPVCzK0EWZZwlY8MJOU1tr2uzT0vQj72fc9ZNVjW%2BLC66APEAwQMg5BQajYJMVK%2BkZyoBE2jtEdKPfMVs5SbrTb64Inu%2BUQ/kzMTopmwQ5OW2qwX/YDwNDuL1pQTT5xCF4iS5Jg6C1XbDULazaOtlh%2BeF8XIp1WXhOCBLfznJr%2BIq6jatRjunpMAoSgNBA%2BLoLRCgCn3aZuA1FW0NVBAl/Vxaoi5bk3NQl2BbRfJinnBcpEXi9lziRnDviPfIJPg/GiPY8T/3Boz6Ic81fXpfL24RxY7DuP471296l3jXA%2BddbZLxAtgU%2ByoL5X2iDfAgo8QDjzYJPR%2B5Vn7zyPh/VefIIB/35oLLeIAd7V33koUBDdl6QP7OfRwl9%2B7X2Hggu%2BKCH6oiflVV%2BYDj4r3aGvTAHkNLt21rRN6RCSF71rlgiBUDTIwIYXAphiDkGYFQew9BnCF5v3AVxSSOIAE3CAWQw%2B2ieHUOpkcDgcxaCcAAKy8D8BwLQpBUCcDcNYawZwFALCWNycwyIeCkAIJoKxcwADWIBbHIilHSWxti6RcFsWYLgsR4hcDMNIGxHBJC8BYBIDQGhSCOOca4jgvAFAgEKcEpxVjSBwFgDARAIAFgEA3KKCgEA0BwjoNEUIApOCqFiOpAAtOpSQZxgDIF3FIKUZheBF0ICQPAo8Ej8EECIMQ7ApAyEEIoFQ6gamkF0AkAA7npRInAeDWLsQ4kJLjOASW5m0z2VAziDJGWMiZUyzgzLMGcCAHhun0CFv4rgMxeDVK0HMCASAumJB6WQDpcKEUgGAFIMwfA6DawqRACIdyIiw2IMCS5vACXMCJRJb2vsSWkC6WwQQEkGAgjuVgCIXhgBuDELQCp3BeBYBYIYYA4hDn4FdB0AAbo8O5mBVDtG5isQJTMsnOO3BEPSRKPBYDuQSPAeTeWkElcQKGSgrgCqMI9UANS5hUAMAqAAag8E5ElMQ0rWcIZ%2BWzpBur2WoO5xz9CCpQB4yw%2Bg8ARAqZAOYOllacGGSPDqphLDWDMCUw1xBllSsjRUKo6QXAMHcJ4Zo/h82TH6DEBIuQ0gCFGC0JIKQq0MFLQrct2bfadGGI0QtYxW1Iy6A0Jt0xxgjC7bW8%2B/aOZTAGGC%2BYixlgSGuRwexRS7mlLeUM0Z4zJnTMkLM/5uBFkgvWmCiFISZhzAQJgJgWAYiGVIBEyQ0SACcyI6SSA0JIDJ6kCm2PUo%2B/QnAcmkDyQEqU6kuDqViI%2B%2BI6lbGSESc%2B9Sy7DmlPKZUoJp66mNJhc0p53NyCUGRcCvpbBOD1BYOKukwymDVgMM6Lgj6pRcClM4hZUdll6DdRs8Q2zvVKF9Yc3QGKzlMAubyhdS7im8FKY81p3MXlro%2BeM1ygqfkMaYxof5gL4XApFsiMw4L0NWrqbC6G2noj4c6aZlFymjD0a4IUmgHpmaUDxYcsl9RiX6vcxSqlDgaV0qSoy5lIrMBso5VynlgT%2BWCuFc40VbbJU8pY7K5A8qaVKruaq9VwJNUrGcTqvVgTDXGswKamLrUMM2qYPax1zrGCutkFxz1Oz5B8YOc4wTAajBBqTSG1VEbb3RvSDyuNCCE3BosCmqTaaM0DbmG0JGeaC1ZFrYECdZacj1uqDWzbeR0gDqnT26ofbO0rb0At47HaDstrHadotQ6ejrebfOmdviXtZIkyuzgCmN00ZU/RxjzG934Cjrp49hmoXnsvdeygC7APAYY%2B%2B2Jj66R0mRB%2ByQYyEiSfuWU2waHIW1PqU0lpbSLOEd6f0jgZHPksAUOK3c4qAdcnxPMkHSyVktaaxIL1sgfXtZ0CAZEpBhOiauf%2BxdtzkMPNw2qVArzVC0/p4z5ncErYAqszp/xyIDOE%2BhSZoF5mkWa4GAzgunomePs9Czr0iuvVYuc7i/FhLPOBO88CSlPs/P6oCwyplnm4uhfZZy2g3KaXRfNXlvlCkEtSsOTKuVMJ0uCEqJlsN2XcvavTYV3gxWD5lfNRVozVWauYCdS6/VnGPU85a/zv1QuuvGAm6G8N8Ao2HWG5wVYt9E1WEsFNlxM2sBzaO7miArgdsJDW0UDbFatvpEn3WvbBQnuDtHwIE7i%2BLvtomKvw7t2t9Xb3%2BW%2BbPi53To%2B1Lkp327dnDpwzs4lupQ2%2BBwesHuvT1Q6vQMW9WT4cgDMAY2RGRDiXfXsw0GALpAgyQ2vzxwqSqU/zvRAEx1mUkA/ViEkDpDSVSSgIl2RCvyk04BPStQXTmRgMILxz1zmENVSGcEkCAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/typical_get_return_type/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/get_return_type.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/typical_get_return_type.test.hpp)
