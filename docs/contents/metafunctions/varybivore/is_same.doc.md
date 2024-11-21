<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsSame`

## Description

`Varybivore::IsSame` accepts two variables.
It returns true if they are the same and returns false otherwise.

<pre><code>Left, Right -> Left == Right ? true : false</code></pre>

## Type Signature

```Haskell
IsSame :: auto... -> auto
```

## Structure

```C++
template<auto, auto>
struct IsSame
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto>
constexpr bool IsSame_v
{RESULT};
```

## Examples

```C++
static_assert(! IsSame<1, 1.0>::value);
static_assert(IsSame<1, 1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto, auto>
struct IsSame
{ static constexpr bool value {false}; };

template<auto Variable>
struct IsSame<Variable, Variable>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEEtIADqgKhE4MHt6%2BAcGp6Y4C4ZExLPGJUraY9kUMQgRMxATZPn5B1bWZDU0EJdFxCUm2jc2tuR0Ko30RA%2BVDUgCUtqhexMjsHASYLMkG2yb%2BbkxeRKQA1CdEh9gmGgCCU8ReDucAkgpCrJh39yYA7BZzlMmI5kOc0AwpphVMliOdYqhPOcAG5iLyYc4AixUMRKAEAEUOQMJxN%2Bv22u32PyOV1Q5wAak08ExYvQbr8ni8CO9Pt9Dm4mcQWWzMBchSL2f5bg9scDGmCIQJobD4YjkWjvJjsQRnj9/kT/CSDWTZQ8APQAKmtNtt5t%2BVutABVsEInTb7Rbbd7LZ6/g8QWCAPpMBRKZoQMBgXlfNgCrgXLgAOg0NxAIE1GMWpseCrwyBDYYSBAgH1jNLcCfOXDTGfRmGzRo4y1onAArLw/BwtKRUJw3NZrMDVuttWZ/DxSARNM3lgBrEBtyQpyRcf7%2BDRtjRmQKBMwADn3%2Bk4kl4LAkGg0pC7Pb7HF4ChAV%2Bn3ebpDgsBgiBAqwIyVO5CUGgux0AkUTfJwqj7oEAC0gSSOcwDIOCUhJmYvCYPgRDCugej8IIIhiOwVT4fIShqDOpC6AmADuxBMMknA8C27adpRd4APKnP%2BPKoFQ5xQbB8GIch1bLmY5wQB4IH0PC5gTosvAvloywQEgwHJKBZAUBAGlaSAwBSGYfB0NsxCPhAsSUbEERNAAnkxvA2cwxB2RxsTaJgDiOaQwFsIIHEMLQDmvqQWCxF4wDHLQtCPtwvBYCwhjAOIoX4MQXmOCimBxT2MJeacmyThE2ytqFtB4LE9GuR4WCUbqeDnvFpDZcQiJKASOzJRVRgzssVAGMACgMngmA0RxySMD5pGEeIJGyIoKjqKF1H6MlKCDpY%2BiVY%2BkDLKgyR1HFMFTOghwEqYljWGYt6tThOXwMsdiZZkLgMO4nhtHoYSzGUFR6AUGQCOMfgJoDdT9H9CydC9Ag9GMn25Amz0ON00yQ4MlQjL0IN6CCzQY/MlRPSOGwSCxHAdte7GcAJ0FwQhSEoeJkm4IQJBYuOXCKVOfXLAgmBMFgiQQPOICSP4SYAJz%2BP8kgaJIZiSIEl5toEUvHhwp6kOeE5JoEXCBPuUv7obS5cG2MvBDevB3g%2BT686%2BqlfmpP7cQBOl6bJ4FsJwTQsCi/wwUwEIGEY1ZS0myZ5VhJB4LhCYzaIc3SKRi0UStIDGXRDGORTVM272nBcX%2BpznHxlzEAHQch8gYfABHUcppJ0mabJnP%2BGYPPKW%2BrtewkgG6agMlDP7gcwXXyVcFLXBXjQtBmRZVmhc59k%2BavrnuZ53nNX5jAEIFwWUeFkXRbFPmJd1mw9ulL3ZblGGqAV2w%2BSVNSURVVX2bV19KcKTWTlau1TAnUkpGB6qAJ2fBBrDVGuNSaXZJxJyIsMNO5Flo9l0MZeuG0rpbU/rtUWvZDqZGOqdc6l0rCWBurbO68cHp7RhqjZwEBXC4wTD9UomMAZpCBlkRGoNSDg0yITf6yMaiw3qNMdhTC6jwxmFwomeNpECOUb0URCwSZrDJtzTWBcaYcErtXYOodkqN2jqzWOckubdz5qQAWQshhELKtrXWkcFb/Etv8dcitlarmpqFO2tgHY92dvAV2v4eKD37sQH2mx/bCRYAoFE4IUTTyTNSKYGErHxzwrIWaxFU4LXQZRXQ/hSA50YvFfObFAnF3drxfiCSEJJJSaidJmSeRSWHm3BIHd/C2KgX3HpWlokjNkhmZAyRkhBjSVLIMnSQxV3giZBeCQl7WVsq5deWy3IeUyj5PeAUgohRvpgCKUUxDn2apfcBv8wp4Ayqje%2BlF8rIEKq/QQ79yqVWqnZH%2B9V/4%2BSAWkEBXVwEREgSpaBTAhojTGhNKazVkEpxkIIdOGCdABDWr1Sh1htqxEIftEhypODmlOrgqhFgaG9joVgIlsjXqsPejIzhcwxFCN4XUGRwjii/W4eIrocMVE5EESjOR6N%2BVKORiKr6Mr1FSrEVo0c5M9G1NvLTZp5xWmpI6aCHKXS2bYQ7tzJSdiHHC0oBTVxWdI7%2BH8G2Lcq5Lz2v%2BEbAJGr7zBOfHYhckg2zSzbPuHcUtJBS3XLLLg5Syr%2BHVbbTgZqnYU3Qh6%2BNXrQnLFaukZwkggA)

## Links

- [source code](../../../../conceptrodon/varybivore/is_same.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/is_same.test.hpp)
