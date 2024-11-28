<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Diplomat`

## Description

`Diplomat` accepts a sequence and returns the sequence via member `Page`.

<pre><code>Sequence -> Sequence</code></pre>

## Type Signature

```Haskell
Diplomat ::   template<auto...> class...
           -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct Diplomat
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

This function injectively maps a sequence to a type.
In the following example, We will create an overload set of `fun` using sequences `Seq_0` and `Seq_1`.

```C++
template<auto...>
struct Seq_0 {};

template<auto...>
struct Seq_1 {};

constexpr auto fun(Diplomat<Seq_0>) { return false; }

constexpr auto fun(Diplomat<Seq_1>) { return true; }

static_assert(not fun(Diplomat<Seq_0>{}));

static_assert(fun(Diplomat<Seq_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Diplomat<Seq_0>) -> std::false_type;

constexpr auto gun(Diplomat<Seq_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Diplomat<Seq_0>>()))::value);

static_assert(decltype(gun(std::declval<Diplomat<Seq_1>>()))::value);
```

## Implementation

```C++
template<template<auto...> class Sequence>
struct Diplomat
{
    template<auto...Variables>
    using Page = Sequence<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAOwapK4AMngMmAByPgBGmMQgAMz%2BpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmiW47eweYR25MXkQAdPdH2ADUyAYKCk9CmACOXoybjxMGgAguNiF4HE8ACJ4faoFhMAhA4EmfxWEFPTFPU77REXY7XO73ABqLTwTBi9AUgIxWK8mSMT2UTGAmCeRyhnx%2BfwYAOOpOI5MpmAU91ugMS6JR/ihRylyIA9AAqFWqtXqhWKtVPAAq2CEOqETzVmpByvVFtVppRIJx50uhNQYppoII4MhX2%2BAH0NOy0ajZZLkci7XiHTcnQ9EthkWCIQQud6uH6rDK5cGzdqAGJ4YjjXUihMmjPAtAMcaYVSpYhPR1PKheBgQGFwhFI46en2PJYpp7ETAEdYMetiJRyv2ykHIssVqs1usNpst2jwxGXTtcbu9/uD4jDt1/ccBkuzRzIL1Md7xAgQBioBOL5uwldt9c/LvR1GpqFLJbpqcgqeeDnpeSitNQjZPq2a4du%2Bm6fv6Mq/v%2BNrAuaKpcmW6AFvmxZTmYiThK8XhYOyxw3HQhAAJ4utOAiztWtYRk8wCQcuq7tm4nYaFuAC0jxPOM6AgCAVCjpgXoEFRqT4vKIIzjsc5MUQLFsc%2BHFvkmfECUJIkHhJUkyShsbNGeF5XuBd4JlgryGZg0CQbpIA2bQABuYiXOxr6wd6PGftGEC/ksInud4mB/kGAGuoiwHmWBN4uXZDlNk5LmhZ56neVxcEStggW/iFYh/BFFgcCstCcAArLwfgcFopCoJwbjWNYglrBsbLmIkPCkAQmhlSsADWICVZItwaJIXD%2BIkGiVRoZgAGwLWYAAcK36Jwki8CwEgaEEtX1Y1HC8AoIBBH1dVlaQcCwDAiAgGsBCpDc5CUGgex0PEkSsFsqgrQtvELZILHIMgTxSLcZi8Jg%2BBEIKwlcDIggiGI7BSEj8hKGo/WkLoiMAO7EEwqScDw5VVTVONHQA8jcz0JqgVBPH9ANAyDYMQ2YTwQB4H30DWXVcEsvAXVoKwQEg72pJ9ZAUBAUsyyAwBSGYfB0DseaUDEOMxOELRUaTvC68wxBUdTMTaJgDiG6Q71sII1MMLQBuXaQWAxF4wBXLQtCndwvBYAiRjiK7%2BD9g4eCuSKOOVlbNxbD14Q7BVru0HgMRE6bHhYDjbp4Dt/ukFHxAxBkmBQrshjAGnRj9SsVAGMACjEngmD49TMm1T1/DI6I4joz3mMqOort4/oVcoC1lj6Onp2QCsqCpA0fu8UJHKmJY1hmIdxfw9H8/dFbDQuAw7ieB0eihOEQyVCMiNFFkAhTH498ZI/DDzMMCSI3YR%2B9BMbRz75B/nUP%2BAg%2BitE/rfb%2BtgAHPz0LMSB18Fh3xWAodqmwJDkw4NVUgB1eBHWZv9QGwNgCg3BmNLmEBcCEBIOyAiQsRZ1xWAgTATAsAJECqQYakhEi3AAJzJEkBNMwkgFp7UqgtfhG0OBbVIDtbqtwFpcAWitfhK0VGjS4JVQRC08FU04CdM6vU67XTuhLB6dMXpywVvzb6bBOAtBYK5fwvEmAvAMIyLg/DbhcHGtDWGJA8AIwxijfu0hB6KGHjjXQqtCbE0Ntg3B%2BCGqcFpk9G4TxGa1mIM41x7jXhV3Bj4vxvoebwmlvzehiQzDCxMZdcWksKky1evLZp/MQBOJcbxQpRhvFcCCDQWgGtToQG1q7Y2%2BsbaTNNubS21tC520YAQR2zscbu09t7X2NtA5VxDvVMOf8o5%2B3qrHZA8cbZJzqDjNOGd9bZy2PVPOBcerF1LkoCuQdq7hFAA0vgjdm6t3bp3G2g8wlowibIKJ2NR4gFVp44wU8bC3Lnlwxey9OCrwIOgdeSLt4EN3sE/eXDf4R2cBAVw8DEZX3KF/PQD8GhUrSG/BoUDFggJ6OAuBQCX6HzJY0ABbK76wP6EyxBAxkF0qFqsdYmDpUp2SQYjgOS8luI8UU7xvjxrcxoXDapjD6lixYWwjhlBsFyIUT4ia/gdH%2BGmpIURQNEYpKOkY86pibr3UevTVptivo/UcbktmLAFCuTBq5TV5xxgBNofDPQYK%2B4QoxtCke9VdCJFIPEkm/skmU1djTKxDMmZOODaG8Nka8T5nKXzeI1TEh1NFldCxfrZZvXaSMMNqRUhegjfwr0UaCAXiDRE9W8RRnjPqjMl2PUp1zKPjbJZDsnYuwOZgD2XsxDbMLrs4OjyA65iOdHV2ZyLmFyuSneqtzM5UQebnQULzeBvLLp8vZPzTENxZICtuHdGCgtkOCiQkLBAppiUkcetcN5WGnii%2BAC8l7ZD9gqXSkGt473iHvVFaDQH8pPmfPIvKaU33Zcy4o2QmUMuyEKmBpKGgQMAfhhB2HaOCsldAhB3KGM/xY7Stj0r0GyrRrm/R%2BbOAqtLWGp4vbbgDp1YEgWDCG3MNIKw9hIwuEpwtXCnxiREiVTmpNPaOn/CqOE4dQxthjGNt/NwkAkhKoCMqitRa/DJD8OmskLgGaU6JDzWZ46hqBoyKhqZgh5mrMrGLpkZwkggA%3D%3D%3D)

## Links

- [source code](../../../conceptrodon/diplomat.hpp)
