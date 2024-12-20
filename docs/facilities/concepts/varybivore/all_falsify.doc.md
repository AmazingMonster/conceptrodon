<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllFalsify`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-all-falsify">To Index</a></p>

## Description

`Varybivore::AllFalsify` accepts a callable predicate and a list of variables.
It returns true if the predicate evaluates to `false` for every variable and returns false if otherwise

<pre><code>   Pred, Vs...
-> (...&&(not Pred(Vs)))</code></pre>

## Structure

```C++
template<auto, auto...>
concept AllFalsify = REQUIREMENT;
```

## Examples

`AllFalsify` turns a fold expression of a callable predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&(not Pred_0(***)))` and `(...&&(not Pred_0(***))) && (...&&(not Pred_1(***)))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return false;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return false;};

/**** fun ****/
template<auto...Args>
requires (...&&(not Pred_0(Args)))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&(not Pred_0(Args))) && (...&&(not Pred_1(Args)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSABykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCaAyzmKopxMdMXkSn5yuNxMAGYACLHEwBKwBMEQX5EAB0yJWJgA7BZzgRNgxjlQxEpQVY0WCiY8nuSDkcARdLlxbkcHs9Xu9Pt8EagaVd6aCIVCYXCOcjEaiMVicXiCZgySSyc9KXc8V5cXcmU8CJgWCkDBrQW4hcinsRgApQdhyecAI5ePDnBTHCDC8wANhdEAYqAIXOuECNJpWAfJLI1bOOMVQniVDAgosxmGxxFx%2BNohJBxNJ8ueGq1OulIP1f1Qwr9ppB5ueVptdodTrMrrr7s93o0vuNCgDK0hdZdNeRLrdHq9Z1pXFb/sDzIErK%2BYYjtCjMfRcYTuIIxC8efT5IV1IAKphZgzDmrdrtjthiMQSOTZkxHMhLkwFEoWtRlXquGaY6i0xw1rROACXg/A4LRSFQTg3GsaxjgUDYtkwLsQR4UgCE0P81gAaxAAJnURRJnSkAI0WdSQAE4QRIswQX0ThJF4FgJA0DRSBAsCII4XgFBAFi0NAv9SDgWAYEQEANgIFI/nISg0C1Oh4kiVgdlUAiAFpSOOYBkGQY4pERMxeAuQgSDwdA9H4QQRDEdgpBkQRFBUdR%2BNIXQuFIAB3YgmBSTgeH/QDgPQ8DOAAeT%2BSSvVQKhjhU511MkTTtN0yR9IdDw5Pob5zGQlZeD4rQ1ggJBZJSeSyAoCASrKkBgCkMw%2BDoDViG4iAYiCmJwmaABPXzeA65hiC6kKYm0Oo%2BJQ2S2EEEKGFoHrnKwGIvGAfVaBTXrSCwFhDGAcQFttMa8AANwPIKPjqP4dhQ8INQA5zaDwGIvMGjwsCCtc8EY7heBO4hwyUMFNR2h6jHQtYqAME0ADU8EwdyQpSRgNos4RRHEWyUYctQgtc/QdpQaDLH0R7uMgNZUBSXpuI4VTZnQXlTEsawzHY37iFM06ya6HoshcBh3E8do9FCBZykqPRCkyAQpj8NzJd6IYxeWbnDoEfpJkFvI3Nqeo1bmRWRiqcYBhlvRbxaA2liqNY4M2bYJH8jggNYoKOJitSNK0nS9LMB1cGMrLqK4XLULBtYEEwJgsASGNSGwyQQURCi0UkDRJDMSRnWY3CyNojh6NIRiQTMREQWdNFEhBRIAgCLhKLI5I2N4DiuJ40P%2BMKkSirE8KpIqqrMsUthOFi%2BLjmQAwjF0sjES4REwKMoh2bMtyUas9HpExpRsec3R6s87zesd52m%2BCjgwokv5jii924o0iedun2f57S1AMviJCzBD/KBO7gf4mkpVN%2BpVMooEnrVMiXAWI0FoE1FqbVnL9W6htJBg1hqjQcBtSajACAzTmkFRay1VrrW%2BptIGRg9pgXwOceoJ1qYL1UBdDUG0brdCCg9J63VXo7DAh9L6KFfr/UwIDbaFDwigA7nwSGCgYZwwRkjUha80Y2U3rILGTkwJ7zxqDRmVgiYcNJrHCmVNOC0wIPTcEujmas3iMvTmscda9D5gLXIstgj80tuLOW6QpbZE1m4%2BWWRPHK0cQ0OYpttbdFVn0fWotDZm3Cf4hJAxgnW3WHbGyx9ArOTdqPe%2B4Cn5zxuBAf2S8kLBzymHUgEco6jFjthKBLE7oFyLgERE5EAhkTMF0usiQ66kRdjkzgrdeJg0El3JA4kIqAP/sQIeOxmgsA0iwBQR0dJHS4DPXMsxDL4CXqZcysh14qLsvIbeGidAgBogfHy30smDPYqFXukVoqqGWas9ZmzETbK9BAdKICP7ZRBN/MZf9gFlRmeC0BayUgpEuBssilwfmXDeZvRq8R4HtU6oNFB2KhojTGlgt%2BU1cGzXmlQzAS0VpiBIShLawMeG8GoYdOhZ1GHIEuiwwQbD7qPWel1bh712b8J%2BvEIRIjgbiLGRDJg0NYbw0RiBFCSjrISFUfZc5OMrnaOMITGwBj4Dk0plkamuw6YEyZpYFmzc2Yc0MTbKJus/AQFcBE9x6BUkSx8b0N1gSShxKtmbR1vR1atCSZEnmesUkBq8cbDWrjkkWxjcsG28F7bBzzifV2nAYrvLWccBF3y7wHl%2BaUkg5SQUd3DpHaOlBHYtKuSXfp1EzCtuqBoZ0nSHnN2GbYNuP8AxxxAAnWeVcAjpxBAEDt1ESJ5xBNkx5nF24FUdgZbtZ9KlVtIL9DIzhJBAA%3D%3D%3D)

By turning `(...&&(not Pred_0(***)))` and `(...&&(not Pred_1(***)))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires AllFalsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AllFalsify<Pred_0, Args...> && AllFalsify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<auto Predicate, auto...Variables>
concept AllFalsify = (...&&(not Predicate(Variables)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4mF4iHdlMRMPhRGDSHd4UQAHR4gBqzTwTBi9AUMOwILQDG2KQIdyutFoADExBkqABPO4wgAidwgeJx5gAbCKIAxUPTkai8OjMBBCcRiaTMAoVuqYVZriC/gDzjrjncACqqggKL76356k5Ag33aXoAD6GgthyB1NmmFUKWIWIRqCRKKdLt53ICVgCPIg2NQgpWJgA7BYUQRNgw7lQ2ZhNYmeTntVb7UHHVxXft3QJPd7fTHA6iS9zoXyTOGW1GY3HE8nMKniOnM7QlDmE3noVrgYXDhmvOnviCwRCPtnYR28VdiMBydDKdcUQBHLx4FHmxkstl4TkwtwO52Y9ebwUUqmVsHVu4xVCeacMCDxpMptMMyzYc8wLUFwReJcr1XHF7y3Hd10wA8j1VBkmVZQcLw5K8bw0O8NwUR9t25MxRVItCz0wy9YRvLh8IfPEn2uD1Xx9d9P1ob9fy7AC%2BzuAhiC8ZcrBHEE7SnE1ZjLIFZg%2BWVHSYBQlBaagZyvLgKV/eMxw4NZaE4AJeD8DgtFIVBODcaxrDuBQNi2TASOhHhSAITRdLWABrEAAmFHFEmFKQAgTYVJAATmhYKzGhfROEkXgWAkDQ8OM0zzI4XgFBAPDXJM3TSDgWAYEQEANgIFIEXISg0GeOh4kiVgdlUfyAFoQruYBkGQO4pBxMxeBlIglXQPR%2BEEEQxHYKQZEERQVHUXLSF0OiAHdiCYFJOB4PSDKMtyzM4AB5BFyvpVAqDuJrhVayR2s67rJF6/kPBq%2BhfXMJyVl4HKtDWCAkGqlJarICgIABoGQGAKQzD4OgwWITKIBiPaYnCZoOU23gUeYYgOQOmJtDqHLnOqt4CAOhhaHRhasBiLxgDhJlMu4XgsBYQxgHEamUPqAA3VU9q9OoER2ZzwjBfSFtoPAYjWnGPCwPaBLwBLmdIPniA/JQeXBdmpaMNy1ioAxN3xPBMGWg6UkYDHpuEURxCm0b5CUNQ9qW/R2ZQKzLH0aXMsgNZUDpLImea2Z0F5UxLGsMxUvVob%2BYDroeiyFwGHcTx2j0UIFnKSo9EKTIBCmPw6ML3ohjz0Y6NqeoBH6SZM7yGvukJho5krkYEhruYS70WSWk7pZu7WWzNm2CRto4QzSBS3g0oulq2o6rqerMflcEIEhHK4T6XINtYEEwJgsASX9SC8yRoRxcKE0kDRJDMSRhSSnzQpijg4tIBLoTMHFoWFAmRI0JEgBACFwCKoVkhz32ulWwWV965V%2BkVP6JVjoVRBmDV69U2CcEutdO4yADBGG6qFHEXAcSmQGiQPAw06JO3Gg7aQTtZquwWroaGq11oYynjPGBaUjplQRHcM6i8rptSIezUh5DKFPVQC9eIjkzB72%2BnlVBWD4iVVBvIwGr0UDEMhqFLgeEaC0DhgjJGC0sZoxttYnGeMCYOBtiTRgZMKZU1MjTOmDNBw21ZrrHYnjuaOD5kzKhqghZghtmLboe0pYyzRvLQJX0lQq2curTWmBtZsyMHrUASC%2BDGwUKbc2ltraqwYfbSazDZCsPmqZDhHt9ZRysD7eJ/tz5B16KHcOkdvYWFjvPeOtDE7n1rr0NOGdcil2COnIe%2Bcy7pCLtkJuMzy5ZHmdXZObd6691Wf3Vudc%2Bgd1zl3fuezpnnIGJske6xx6TV4btBaC98ESIMdIihLoICb0GjvFRB9SBHxPqMc%2BXljF4Qll/H%2BAQcRhQCKFMwCLSKJAgSFWee00oZQQao5B8BUGlROlojRxAcE7GaCwNqLAFA8y6jzLgZDISmn6vgQatCRqyEYdU22dS3YgGilwjazNHnoueYddBp1zqqEpdS2l9KcSMqkhAZ6ujFHvWhP8gp6idFAyJdqvRNKUgpEdHS0KjoFUEEdFK5hsN4gWORqjHGtiHW43xoTZx8jSbk0pntLx9MxC%2BNVv43JyTSD4BRLzfmC1BbIGFtEwQsTJbS1lhyJJitUk2wyekLJOtcnhHyT9QpTATZmwtlbYyzlKkTQkDUmaLt6k6D5U04w/TfYxA6YHYOlZOC7HDl7aOlhBlmWGVgdt2yjmTL7nRHOZQzmLKKFkSdqQlkV1OcPA5KddkDEXeM9u1zV0LPGFu/ZPc90zrXbvO59lJ4fz4RizgF1pU0ruCa%2BVS5FU/O3u9XeX0AVAtPpQKeUK%2BV/1RVFMw4GuCJA0MKeFIrUqcCxdlAFl9r4QNAY/aEARoNRWCh/aETz4NwJxVPPqcH54IcQT9NY6sMjOEkEAA)

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/all_falsify.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/all_falsify.test.hpp)
- [Example](../../../code/facilities/concepts/varybivore/all_falsify/implementation.hpp)
