<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::ApplyReturnType`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#apply_return_type">To Index</a></p>

## Description

`Functivore::ApplyReturnType` accepts a type and returns a metafunction.
When invoked, the metafunction yields a function type with the previously provided type as the return type and its arguments as parameter types.

<pre><code>   Ret
-> Args...
-> Ret(Args...)</code></pre>

## Type Signature

```Haskell
ApplyReturnType
 :: typename...
 -> template<typename...>
```

## Structure

```C++
template<typename>
struct ApplyReturnType
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

- We will create a function type with `int` being the return type and `int, int*, int**` being the parameter types.

```C++
static_assert
(
    std::same_as
    <
        ApplyReturnType<int>::Mold<int, int*, int**>,
        int(int, int*, int**)
    >
);
```

## Implementation

```C++
template <typename Ret>
struct ApplyReturnType
{
    template<typename...Args>
    using Mold = Ret(Args...);
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCBmAGykAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0bEJCnUNTdmtQ109xaUDAJS2qF7EyOwcAPQAVFvbO7t722smGgCCm9sA1ACSLIn0bIJM1ec7hydn%2Bx/7r8dHxwSYNwM/3OJgAzG4CABPRKMViYc4AJUwBDB2F%2BQ2IXgc52OiVukKRBCWDAAKtDML8TAB2Kwnc7087/QGPCngqEw5hsAB0POOxGAClRvwZ5y8qSM5wAsp50CDQQARRHIiB8gU8rmzMG0n5U%2BVaylvT4fb7vDbnbCqVi3eEvX6mo0HA0/Myg4LIbxYOVuNAMFaJAiC0Fok7ouqOZAAfSYCiUDV%2BEGFDKG6BAIAUcKjgrpDLBbkTIvpuPxhOJZJhueCKKDqeltHQFcEpHOlY2TZbG1RpHzBcrEErbcErebg42muz9KFJ01oO1HHmtE4AFZeH4OFpSKhOHnLNZzgpFst4eZQTxSARNHP5gBrECLyRcjSSLhU0EaRcaeJxMwADm/%2Bk4ki8CwEgaBopCruum4cLwCggGB55rnOpBwLAMCICAiwEIkXgEOQlBoDcdDRKEcKcKo35xAAtHEkjnMAyDIOcUhcmYvCYPgRDEHgKatPwggiGI7BSDIgiKCo6iIaQuitAA7sQTCJJwPDzkuK4XhunAAPI4dhBDnKgVDnORVE0XRDFMfeZjnBAHiEfQxAgi6XCzLwCFaPMEBIARiREWQFAQN5vkgMAUhmHwdD/MQsEQBE6kRME9SQkpvDxcwxCQppETaJgDjJaQBH3AQmkMLQSWSVgEReMAbhiLQsHcLwWAsIYwDiOVeDEDljgAG6YPV66YKoOU4asp6VpU6m0HgETyelHhYOpBBccBDWkL1xARCkmDygCLVTUYF7zFQBgCgAangmAyZpHJ5XxwiiOIwl3WJajqdJ%2BgtSg1jWPo02wZA8yoP66T1ZRyZgvKpg7pYZiQetXFYP9EDzHYXXpC4DDuJ4zT%2BJjUx9DErS5GkAijC0SQpCTDD4yU/TjJUaMCJ0IzY2MbSMzUwzdMEvS04Tthc2TegTA0NMzM5CxLCsEgqRwy7gepUFGRR1G0fRjHMVZEC4IQJCOSeLlnod8wIJgTBYDEyOkDekiglyACcoJUpIj5mJIcSgYucT2/%2BHCAaQwEnlycRcHE3729%2Bod3lwi6OwkEG8FBMFwUbiEeWhnkYTpOF4QFqB2cRpEcPULDdVSlFMOc7otUx9tclwD5sRxJDcXod0CY90jPUor2SboYVyQpyWy/LCcaRw2lYTh%2BmGcZqtVwYEpcHXDcaNZtk%2BfZ%2BtmIbblIZngX2bnh/9NXRjL1wYE0LQkXRbFkmpYleWP%2BlmXZblq0FYwRUlWV64VVVGqtA6p5SantVY/8Opo16v1NiQ1kAjTyuNBckkpozUSvNCBrllp5XWptJQO1mpGH2qANOfAToKHOpda6jBbqyA7kJLusgXoSXXP3D6B0oZWEsL9CISNAbAwEKDcGCouHWFhoneG3E%2BrwBRgzBw6MICuCFq0QIPNph0wpnkdIKitFUzFpo1GCimaC1ZuTIx1RmbcyKATYWpisjmK5gYwmKMDzSwlig0eitODKxMrRM%2BwBa71wfNZHWnF9bOVcsbUgptzb9Ctig/2gc66PipLHKkL5JBuxoq0MeSdbApz3uneAmdMK6WPvnTehc2CcBLqZFgChuqMW6svLkQI%2BoECbrrBGbd6EPUYSJeQPdWE6BAKCUgg9FINRHmpSSUFJ66RnkZepjTmmtPaUMdelTfL61BLvQ6yEvLbKPv5E%2BMQml4gjC0%2B2EYNkEAjKoGi4Ub7RDvnFBK6Vn4fIyllLqeUv6CGKqVdSADqq1XqqeMBxCsGkHwJ1BRMD1KDWGv8JBggJqoOmrNSEmDFo4NWngrahC9rBFIe5chTAzoXSujdVa7d%2BkSCYaJYZb0xkcOMN9HhaD%2BEbkEQweqaxkxfWhhYCRG4pGI1kezYxfglGY10WomxfMciU2qLo4m1RnHC3kZY%2BxON6btBMZMdRtjxh6rZiLaxvNxauKlkJGZCs5k%2BMebRBpTTzjXLaSyTZ2tm4OWPJE1O7kTZmwtpQWWSTYh11BKCRc74nygRjVSMOjrIKcGTvBaJNtFwO0XN%2BeI9tJD2xfE7Lg4yUGglmWm6CQbLy%2B1YqmxO6ba2zHmOtVIzhJBAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/apply_return_type/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/apply_return_type.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/apply_return_type.test.hpp)
