<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensibleGauge`

## Description

`Typelivore::SensibleGauge` accepts a list of elements and an operation.
It returns a function that, when invoked with containers, will place the previously provided elements into the containers via a process similar to pack expansion.
Then, the value result of each packed container will be collected to invoke the previously provided operation.
Check out **Example** for more information.
<pre><code>   Element
-> Operation
-> ...Container<sub><i>i</i></sub>...
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;::value...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Operation
-> Container
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Operation
-> ...Container<sub><i>i</i></sub>...
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>

## Type Signature

```Haskell
SensibleGauge ::   typename... 
                -> template<auto...> class...
                -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct SensibleGauge
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Example

We will see three examples that present different use cases of `Typelivore::SensibleGauge`:

- We will pack `std::integral_constant<int, 0>` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
template<typename Element>
struct AddZero 
{ 
    static constexpr auto value
    {Element::value}; 
};

template<typename Element>
struct AddOne
{ 
    static constexpr auto value
    {Element::value + 1}; 
};

template<typename Element>
struct AddTwo
{ 
    static constexpr auto value
    {Element::value + 2}; 
};

template<auto...>
struct Operation;

using SupposedResult = Operation<0, 1, 2>;

using Result 
= SensibleGauge<std::integral_constant<int, 0>>
::Rail<Operation>
::Road<AddZero, AddOne, AddTwo>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<1, 2, 3>;

using Result_1 = SensibleGauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>
::Rail<Operation>
::Road<AddOne>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<0, 2, 4>;

using Result_2 = SensibleGauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>
::Rail<Operation>
::Road<AddZero, AddOne, AddTwo>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Typelivore::SensibleGauge` separates cases according to the number of arguments.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

[*Check out this test to see how it works.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEElxmpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcBJgsqQa7JoFuBACeqYysmAB0d9j0bIIKx9gmGgCCE8ReDgDUQkYmVi9AA4kwvMBMO8PiYAOxWT5/ZF/Xb7Q7Qk5og5MI4nCFEO43V5/ZAGBQKP4AeUuxFx2VeMJRf2%2BvwIf2UxFQRAASkw6EyUfDER9mczsRjjqc9ji8acLlc2ESSWSmBSiQARTAANzwWxegTeSLFyNZ/y1LQFxpNwsFJuZXkyRlRCr%2Bxw11Np9IEdvtyKlWt1%2BqlDz2jAIBuwIBA2rEXlud0ZgRFfvhGuOKftvvFMslWNzuMx8suzCVicNpPJlMDesxRtF9rN7It/NoAZ1tcZ1rFtu7fsdEWALsubsCHppCW9DGzWZONa2Ice4cj0dj3gTxMNGZn/rh6eTMJ3qILcolhal5xL12VFdV6ru88wkaPA%2BdPNQTHQo49LYFc47%2Bo3lGICXpima7vuIq%2Bmep4nkWBKoEBlZqgoRIfMAxCYGGzxdg2yKvkOfJ0N%2BHJcryrZSuhmHYRGQHbp8ab0bCnwwUWoGlpgfyhk8BC4U2AJAngIKYOCkJFtx4a4b2eHHui575nJcoIUhd6UhOdKNLhzL8Zy3KoERbbdtJfqsRecEXgqHEqVWmoAU%2BWn2gRfzvp%2BJHqVOR7tkG9knBJgivKucYbkm4FunuTHQeZCmyvBXiEuW2DIfeNxUVhPHPt2TkGSRunkX%2BbipTRqEJRF4UHgxFUfAA9AAVHV9UNVVMK1XVAAq2BCK19VNZ8LUNY1h4MWYgQRGSXhYKObhoAwWypBGUksVFxaKpxfm8Vunz8R86DoAAWgkqBugxCJHTJcyOMgpICBMmCqKkxB/AhfxrvGvrCmtgXroxyand9UGLYpbGWdcXFLv5G1fAQPz/Nt6BUpEh4nb6516ldDA3XdD1PS90JGQiH0xkFbqWH8XB/b9ZX/R8plYsDbCgzRfFQ2yfyw61ADuqCIxYp3aS0F1oxj92PXFh0429%2BNgwQn3xsTPNmOTiOQYN1NLcpJWbcz/zuZp5XMdVVV/K1T7shoKtOUIXipEUmDoDyT5eLQ7Lup6k6624GikKTXsK1ueswllDtO79Y4CejQlghCUJShM6DRhEuwYWIAD601zODbgJ17Zt%2B/W0YGVKOsMhD%2BcfuglE7ftXJe7D8OYDXO0c1zftUyjyDJyhCQEBAsfRgo1wdwabj2wojsEF7lvWxktsj2PrzLBFvWG8bEyk%2BbTpDpPNt20HBDJ1wbleu7XA%2B17gQhevg7Obv%2B8kYC4fCaJ0cnMjBBxyACeYEntCp9dLQZ1nP4OdsCkFfu/T%2B39f7o3/utTOggvZk0NKA7svcP6CC/nSH%2BacYFSkAb7esuF84UROEXH0JcQAuXLicWuCMW4qzboPJQbQe5vz7gPNUUpZ5OwnlbbeXD1rYAXv7JeRsTZ/AVpVC2vDp471Hk7ZOZhD5u2Lh7U%2BfxJAX0kRva%2Bci96KJdvfYEkcxJSjAfHdBkDsGGFgYA4ByCzqsLQYnTBUD042PgWvJBZinEYJTlYgBHj8GHnIQXEhR9i55woWXCue0DoNzhpEeJTdNH6wYZ3ZhqD%2B5sEHpw3ePCp5KFkXPQ0QiLAcFWLQTg/heB%2BG4LwVAnA3DWGsCydYmxOLmECDwUg0sOBaGWKsAA1gESQNwNCSC4HCQIGh/AaDMAANnmWYAAHMs/QnBJC8BYBIDQntalaFIA0jgvAFAgE9r0/ppA4CwBgIgEA6wCCpDiuQSgaB9h0ASFEa4nBVDLPmQAWnmZIP4wBkCXSkDcMwvBbaEBIHgOOJ9%2BCCBEGIdgUgZCCEUCodQfSdB6HZnSVInAeAVKqTUzQ9TOBUjik89kqAqB/F%2BQCoFIKwWk1GYoiAHh3n0Aep0rgyxeAXPKVcpAbzUgfLIBQCA4rJUgGAFIFINAnYJFORAWIFLSCxAiK0M4xLeDauYMQM4VJYjaEwA4fVpA3k8XhrQPVuLSBYFiJCNwYhaCnLqU6vYhhgDiEdfgTCDg8DaifJq26Fq4rbG6Z/SpjraBCTpMajwWBNVQzwNsr1obiCxGnlqFgvqE1GApasKgBhgAKAAGp4EwOzCctTulIuEKIcQ6Km1YrUJq3QJ8DDFtMJYaw%2BghKnMgKsVAc1siev%2BbHd0/arCWDMAc1A2biDwrDaOnoFrGguAYO4TwnQ9BhAiMMSoowT5FCyAIaYfhz0ZEvQwBYIxqibuDQIfoUx935BPnYLdfRJiDGPYsM9th/3Xr0HMNoj7T3VFWAoNpWwJCko4NU0g%2BzKUcEZX8wFwLQXgo5X8CAuBYV8uGgKoVJbVgIEwJ%2BUYEAhkgEkIEG4ABOQIcJJDjLMJIeZuz/DzOY%2BsjgmzSDbK6TceZXB5nLOY8syT/gJn%2BFY/M1DmqjknLOT0ktVzbkQCQA82lLyZWoB5Z875HBWgsG1HCf5TBkLOi4Mxm4XAxnQvwEQVdCKMXNtRRIaQ7alCdsdboFIBKmBErqUhlDaHDlUppXFP49LHrEEs9Z2zqp7OOecxoAj3KJW8uJoEMwgrNO4tWLplAxm8sJEM7K3lIALNWf%2BelhVzGuCe2VbsYgaqNWOsNbqq1fXjWmvNZar1Nrwx2odQc51rr3Weu6VgAtRh/XTbwEGxwobPUHIjcgKNVrY2aoTbEJNZwU3bAOemzN3Ts25qUPmwtg4tNlqYBW6ttb61WqbSi1tfnZAdpxQc4L%2BhfUoGaZYIdsQR10cORO66nBp1v1nWDiwi76krrXVD2D9Rf3OAgK4MDJ8j3lCfXoC9jQCdpDvY0KDSxv3Y9fU0UDn6b0vsaO%2BgDxPoPgaZ3kFnEGOcntp7B%2BDaLIvksdUcpLKWbN2aHA5pzYyCNEfcwVsjJX%2BmUeo1gRI0O43CdE458ZcJFNwimZILjQKT7RbU7YDTwqys6b03F8e0raumbYJwCzLKWAKG1JdbU8uMQTFc8R%2BFegvstrRb9zFAWAd4uCKF8LJLBNRdU7Fx58XEte%2BBT7v3z1A%2BFlXlyyrkqCuBGK/b0VFWTNSteSXurfvrbJwD8x5OQe97Z74HQTr3XNWDYdd0/vw2t1WvG4ISbmqZvADdbQD1VrFuFvO7wQNv7NvhtUJG3Y%2B30FxoOUdk7Z202rqu7wG7eafXLce6Vvg5aq01rrSWT7shvtR68/9rtIBgi9uMMjiHmOYeNCepVS9xzrWCo6HLo5YD/4/oM47p7q86Hq7o07AZk7ZAU6oGlCAYk5069Bvo84Ho4E46M7zBYFc7fr4FfogYkGc5C5rAbAIYCop7i5LqcBS7e6%2B7%2B4F67BF7K4kCq4V4UakBUY0Y65Ib64gBmCOaBCBD%2BCzITK7LSFwhSYqYS6cDqbnKCHDKSD%2BAsb%2BDLILLMaSDMZTJsZcBf6cCBDMHobkalZIZQoqEsHHLq7lKrDZqZDOCSBAA)

## Links

- [source code](../../../../conceptrodon/typelivore/sensible_gauge.hpp)
- [unit test](../../../../tests/unit/typelivore/sensible_gauge.test.hpp)
