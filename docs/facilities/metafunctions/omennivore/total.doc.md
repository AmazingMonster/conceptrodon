<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Total`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-total">To Index</a></p>

## Description

`Omennivore::Total` accepts a packed vessel and returns the total number of its items.

<pre><code>   Vessel&lt;Items...&gt;
-> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Total
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct Total
{
    static constexpr size_t value {RESULT};
};

template<typename>
constexpr size_t Total_v {RESULT};
```

## Example

We will find the total number of elements contained in `Capsule<int, int*, int**, int**>`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Test ****/
static_assert(Total<Capsule<int, int*, int**, int**>>::value == 4);
```

## Implementation

We will implement the case where we count elements inside a packed container.

```C++
template<typename>
struct Total {};

template
<
    template<typename...> class Container,
    typename...Elements
>
struct Total<Container<Elements...>>
{ static constexpr size_t value = sizeof...(Elements); };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAHKSuADJ4DJgAcj4ARpjEIADMXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMSQiyG8WFuJiSbmQE3QWCosOwIJBfwBWIOQMxtwAkiw0vQ2IImI0vodcdiaWd0VcCJgiQZGbC3AQAJ7PZhsVEgibELwOW4AFVQLVoMIA7FYpfdYVYriDGczyZh0XCQbdtbcVcS1WzOdzWJgAHTm1G3SFMBSfDxkiIJUhanVGxgm82m7AkxgEBQatFXAVCgii8ViNn2lqO4hs71M30KT18pKB4Ey25zRzIK0CCaYVRpYiZvAAL0wAH1QwA3MReTAwpL3Evl1BUT0QeOkv3LBXS%2BVJRXA36074Yo63bCqVjEhtjkejnH064TtxMNIKLz0SlLhlM/WsuFunlmi2p/kEQXCtcbrfqwfLvEij6h%2BeXLN4ZAVm1KNoQMUSpG66bvQbIRAQpC3OBeyQdBMFQYIBwptgIAgLW3gNrCA7NpIvaDhwqy0JwACsvB%2BBwWikKgnBuNY1iZusmyYWCPCkAQmgEasADWIDEZIpoaIEZhmAAnCJXDEYJgRcFKUrSERHCSLwLASBoGikORlHURwvAKCA6nsRRBGkHAsAwIgIDrAQaReBBFAQGgRJ0AkUQmpwqiBP4AC0/iSLcwDIDmUimmYvCYPgRDEHg6B6PwggiGI7BSDIgiKCo6hGaQuipAA7sQ66cDwhEkWRHFUZwADytk2aGba3B53m%2Bf5gW3MFZi3BAHhOfQxbmCkyy8IZWirBASCOWkzlkPZ42TSAwBSGYfB0IyxB6RAsRlbEEStByhW8FtzDEByFWxNomAOHtpCOd2FUMLQu2ZVgsReMAa60LQencLwWAsIYwDiI9eDEOdjjVh8ZUFudtnbKx4H1GVtB4LE%2BVHR4WBlZeeAqV9pBg8QsSZJgjy/UYiNGBxqxUAYwAKAAau8OUVdyl1xcIojiMlrNpWoZXZfof0oHRlj6EjemQKsqBpI0n1eYiWGmJY1hmFpeNRVgYsQKsdggzkLgMO4nidHoYSOosoypMU2QCNMfgW5kVsMAsIyJOM9Q6wI/RTIbBSu70HuTIMpvO3ocxe/ktu2AHTtVObWuMVsEjFRwpEaWV2n1Z5Pl%2BQFQX8e1nYRSQMIsQNbEU6sCCYEwWCJJrpA8ZISSmiJSRyRokhmJI/hqcR/gifonBKaQKkpKa/hcEEInSf4fESS3/ip5l2m6fpZdGSN5mjZZ1W2eQlAzT1rlsJwrQsNWUpeUwVoGEYrUiaaXACWFhdq7FsgJRz0hc0oPOZboi15QKl9JOKdNK8G0lVaytlbh1Qalna%2Bf074PwEh1LqE0erFySGYUuQ1jJbwPk6aaqBuqjGtEYLg4l1I0FoCtNaG1MoHR2pdRhR0TpnQujja6vpbr3TKk9F6b0PqXR%2Bn9AGlF8DAwcHgMGn1KKQ2QNDS6cMFKUURsjHaaNtiUUxtjVieMCZKGJqIiIoB158GpnTBmTNGAs3fuzJKX9ZDcwypRf%2B/NyYKysMLNRGsJZSxyDLOWTZPFKxVgkNW4NxY9Hdn4CArgbbG31tHJYdsSg5ASakh2yTzbRKkf7AYGTcmNE9oHCowdxgB0KaHUpwwY4uzjhsBOXAQGlSXpwDOjU/JkOAEgx%2BGgOq4EIEXPqzTBrl1IJXauow64KSHiPe%2B7cpTERErJJIHcu6SFSGA8qOlbCr1wRveAW8rI1T3g5Yh6CXJuQ4KfJqLAFDVhzNWChpoWQvmfkM1%2BqRWYfwcSleQP8XE6GSKQQBaQ9otMXlpSqO9apUHqnch5TyXlvImKgi5k1MFJBwRTEyY0MU9TOQQxIjy0hpArM8kSFZUUEArKoXyS0aEJDoZtbaR1mFsuOqdEGl0uGCB4Q9cRmBnqvTEEInGIjSZaO%2BkDHWMiIaqChoyJRgh4aZTUSjDkmiMZRV0bwfRhMjGkxMbiqmTAab00wIzZmOMfn2IkI41KgLeYgpvsYIWNgfHwD8dLTgOxESC0VpYZW4DVbRUiXXbWeTYnxO9hHE2ZS6l6Eto0QpKacjZJdkUvolS40hzdtGkpmaQ65vDiW%2BYQck3NLWI0pKkLtnp3pX5e5jzbiUteWqNFBdPmYNGWvYaFcq410oEnOZIBRKmiSEkYiklNlqSnVKboDbOArwMuMhuxFm4ySlGpQIkhxJcCEmYBeCkkitOhbsg5SdQpQvASu/tnFcbMt1pIIAA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/total/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/total.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/total.test.hpp)
