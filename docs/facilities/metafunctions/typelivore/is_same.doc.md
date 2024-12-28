<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsSame`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-is-same">To Index</a></p>

## Description

`Typelivore::IsSame` accepts a target and a list of elements.
It returns true if the target is the same as every element;
otherwise, it returns false.

<pre><code>   Target, E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> (Target `same as` E<sub>0</sub>) && (Target `same as` E<sub>1</sub>) && ... && (Target `same as` E<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsSame
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct IsSame
{
    static constexpr bool value
    {RESULT};
};

template<typename...>
constexpr bool IsSame_v
{RESULT};
```

## Examples

```C++
static_assert(IsSame<int, int, int, int>::value);
static_assert(! IsSame<int, double, int>::value);
```

## Implementation

We will implement `IsSame` using `std::is_same_v`.

Here's the entire implementation:

```C++
template<typename Target, typename...Elements>
struct IsSame
{ static constexpr bool value
{(...&&std::is_same_v<Elements, Target>)}; };

template<typename Target, typename...Elements>
constexpr bool IsSame_v 
{(...&&std::is_same_v<Elements, Target>)};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCBmAGykAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0bEJCnUNTdmtQ109xaUDAJS2qF7EyOwcAPQAVFvbO7t7G2smGgCCm9sA1AAimImujMh4mArnO4cnZ/ufu2/HR79mAGZgshvFhziYAW4CABPW4AfQIxCYhAUEOwfz%2BHy%2B2K2Pyx5wAkixEvQ2IImNUXts8TjaQcMScCJhiQYmRCobDGKxMOcACr1YCYAikc4w27MNgAOml2FJjAIqIB6JOQ2IXgchIUQm5GIA7BZzhNHMhzmgGENMKpEsRzhFUJ5zgA3MReTB6iwQaWS8xxH1DdAgEB4BRwhTcuGO9my5nyhQi/nEQUENGzEy6y4Qg1pjMAqwnP5MlkUt2QsVcth8gVCkVliWYL3RskKtF/M0Wq02u0Ogla8OO8H5/We6U%2Bv0EANBkNhtgRqNywRxyuJoUp7OZhmnOmvTE7c7YVSsEk87fvLfUjdGvDIOFMBRKBoQHvatjs4LC85vkWfj%2BCNGB53eJgqa5n8l7Xre94EBAYBgJqz4lm437oIsET0F%2Bv5Kv%2BLpAeuJwcPMtCcAArLwfgcFopCoJwbjWNYhqLMsPLmACPCkAQmj4fMADWIBEZIkoaAAHGYZgAJyiVwRFCYJXC6rq0iERwki8CwEgaBopBkRRVEcLwCggBp7HkfhpBwLAMCICAiwEIkXjChQEBoMSdDRKE3KcKoglxAAtHEkjnMAyAmlIkpmLwmD4EQxB4AGrT8IIIhiOwUgyIIigqOoxmkLorQAO5IoknA8ARxGkRxlGcAA8nZtkEOcqBUOcnk%2BX5AVBecIVmOcEAeM59A2sxXCzLwRlaPMEBIE5iQuWQDlTTNIDAFIZh8HQTLEPpEAROVETBPU0JFbwu3MMQ0KVRE2iYA4h2kE5TaVQwtAHVlWARF4wBuGItD6dwvBYCwhjAOIL14MQV2OI6TzlZaV12asrFvpU5W0HgERIqdHhYOViJ4Kpv2kJDxB2ko1wA0YKNGBx8xUAYwAKAAao8uWVeKN3xcIojiCl7PpWo5U5fogMoLRlj6Kj%2BmQPMqCJNUP3ef6EKXKYljWGY2mE9FWASxA8x2OD6QuAw7ieM0/hG1MfQxK0uRpAIowtEkKS2wwFslP04yVPrAidCMJtjG0Xs1MM3TBL0btW7Ywf23oEwNK7MxDQsSwrBIJUcCRmnlTpTVeb5/mBcF/FdRAuCECQ4KAkNI1U/MCCYEwWAxDrpA8ZIAKSqJALyRokhmJIcTqURcSifonDKaQqksZKcRcHEgmiTJcR8ZJncJFpvA6XpBlsVTpkWRNVk1XZ5CUPN/VuWwnD1Cwjq6t5TCmgYRgdaJkpcAJ4WRSQMV6OziVc9IHmSg%2BZZV0CtfKTBCq/TThndeFUODVRsnZeqjVmp50foDF%2Bb8BLdV6tNfqFcARmGGjvYy41JqoD6tEE%2BjlKH4P6CCQGXAJIaRoLQdam1tpZWOvtG6PDTrnUutdfGd15QPSeuVV671Pq0G%2Bjdf6gNgYUXwGDBweBIY/QojDZAcMbqI0UhRFGaN9qY1WBRHGeNWKE2JpgUmijgigDIXwWmDMmYs0YGzWQ/9kqANkLzTKFEwGC0psrKwosjHayljLdIcsFYAiViLCwasN4axilDSWAc1HOAgK4aOrRAih2mO7R2eR0h5JKc7eOxS9ZZKDl0cpNTqg%2BxDkUS2Mco5%2BwdrHFpYcE66wYinROilYFZ04DnFq/lGHP2YdgjQ3VS5RUIVXUhY1a710bpQNO49J6vx7rqIiok5IAl7v3SQrQ4Gb1sNvUaJkzKWWsrVGhZ9XLuQ4NfVqLAFCOhNI6GZrIngEE/mXTWv8vGcx8aleQwCAk6BAACUgECoHFVHunMqWUdKINqigpqHyvk/L%2BcWIYuC6EzUIQCEhNzyEoBJf1J5NL%2BjfMSIkCMzC4T/KGHCVQflVrsOiJwnae1Tp8MFWdC64MbqiMEOI56yjMBvQ%2Bl9H6rEFHkzMX9UG%2BsNHQ1ULDJkejBBIyykY9G0JTHY2ipY3g1iUi2OZPYymTiaZMDpozTAzNWb4z/uCiQvi0rQv5nC4JxhEliwiJEyi0SBA/TWP6YWKtLDJMoqkrW8Bdae1qYbY2WQHYFNaeHHITtqjlJttUKpEdGkdA6dmmO6amnBzLe0%2BpnTG1x0KW0xOCgBnJRgWi7SYyuX%2BU%2Bd8p0BKmREpLl/AalcKU11IHXBu/Rm6KW2bEV%2BAIARESkmc9S67dRz0zuizgW9DKztbkRDusldTqUEpICSXBhLlEUgCXtG8j0rM4iisKB6%2B26XfbMeYhNUjOEkEAA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/is_same/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/is_same.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/is_same.test.hpp)
