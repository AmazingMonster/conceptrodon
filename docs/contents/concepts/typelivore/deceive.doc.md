<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Deceive`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-2">To Index</a></p>

## Description

`Typelivore::Deceive` accepts a callable type predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns false and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> not Predicate{}(Elements::value...)</code></pre>

## Structure

```C++
template<typename, typename...>
concept Deceive = REQUIREMENT;
```

## Examples

`Deceive` turns a callable type predicate into a concept so that it can be used for subsumption.

The following code will fail since `(not Pred_0{}(*))` and `(not Pred_0{}(*)) && (not Pred_1{}(*))` are both atomic:

```C++
using Pred_0 = decltype([](auto...){return false;});

using Pred_1 = decltype([](auto...){return false;});

template<auto I>
struct Monotony
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (not Pred_0{}(Args::value...))
constexpr bool fun(){return false;}

template<typename...Args>
requires (not Pred_0{}(Args::value...)) && (not Pred_1{}(Args::value...))
constexpr bool fun(){return true;}

static_assert(fun<Monotony<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgCcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BxemUYA1MrEmOgA%2BhqHJv4AIodYyLQEAJ6pmBAmgVaBtxBMXiIADoQasTAB2CynAhbBiHKhiJQ3Kzg25g/xWDQAQRM2P2EWAx1OFy41zuD3qzzeHy%2BPz%2BAOBoIhUMwMOIcIRtCRGIhaORuJx2IImBYqQMwpubgZqEOAEkbtgBXNiF4HIcALICVBEBgvAXMgWHI2HOZMRzIQ5oBhzTCqVLEQ7Sw4ANzEXkw10h8tR/OxvN9gqxwtF4swkte72YbBBQKxxGACgVAtOAEcvHhTgpDhAGNqiWdLgbURA4wmQCBXd5MDHVmDsVabXaHbFUJ54V4GBAwZDobD4YiwzyfX6hSKxWbB24I4xWNWQaXE/5FdjU%2BnM9ncwR8xcNEW/gvy5X3TXVtczAA2cznjd5k4Frh7kvxhSHt1zoG1gUN4VNw4tttUB2XbMr27KHAQKqDiitz6tiprmucTAKEorTUB2kqapuAh6v4bgPkuCpduiFgcOstCcIEvB%2BBwWikKgnBuNY1gmps2weuY/g8KQBCaKR6wANYgIE55AgAHOeUiBOC56SEk/jSWY/j6Jwki8CwEgaBopDUbR9EcLwL5aTxNGkaQcCwDAiAgJsBCpIC5CUGgop0AkUSzpwqjiQAtDJhzAMgFpSECZi8GchAkHg6B6PwggiGI7BSDIgiKCo6gmaQuhcKQADuxBMKknA8GRFFUbxdGcAA8oCdlbqgVCHJ554%2BZIfkBYcQVmNmHjOfQDocVwqy8MZWjrBASBOakLlkBQEATVNIDAFIZh8HQwrEC%2BECxGVsQRC0LyFbwO3MMQLwVbE2j1MZXFOWwggVQwtD7elWCxF4wBSrQXIHaQWAsIYwDiM9GaXXgzqYC%2B6W2vUgK7FxETCuR6W0HgsR5SdHhYGVEF4Op3C8GDxAtkotwiv9yNGLx6xUAYCYAGp4Jg2UVZG30xcIojiIlbMpWoZWZfo/0oExlj6CjL6QOsqCpH0ENeXM6A3LcpiWNYZi6QTxCReD8DrHUDTOBArjTH4WVhIsFRVHoRRZAIxtWxkNsMMMFsrN0vSNPMdtZXrfQDK0zujNUEyDF7wf%2B%2BbgcSLrrE7FHykcJR2llXpDXeb5/mBZIwXZrg4V9YpA1DZT6wIJgTBYIkXakIJkj%2BECcngpIGiSGYkjnppwkpIjqmkOpnFAhJ56iUkolcOegSSFwgRyeeSfpXpBkgEZlNmZZY3WdV9kzXNvVuWwnAtCwzrgl5TCWgYRw1ECXBArRYVEJrUVZWzcWc9I3NKLz6W6MtuX5QdxUE6lXnpVTetV6qH2Pqfc%2B/12pJGvrfLqqAeoJDPP4Mwg1uIr3XjvBIDlZrIMmr1EAkCT5PH%2BjULgWkaDPASBtLa6Ujp7W%2Bkwk6Z0LoOG%2BjdRgBB7qPTKi9N6H0vp4x%2BqTIwgNaL4FOA0MGEM76qGhsKb68MehlWRqjPaGNdi0WxrjLiBMiaYBJn9CRBIV7UyYHTBmTMWaiJfhzBK79ZA8zSrRH%2BAsKbKysCLDR4sq5SxlpwOWBAFZ3G8ardWCRH7awlm7EGBsjaeA6HoM25RI5ZWtn0UOWTsgB2WEHH2HsQ7JPyN7HoCT%2BjzHyZbb2ntSkmzDgsdJBS44KBjglQBicdK8BTqQ6B5DL7wJvlcCAucH5oMLlgkytZSCl3LmMKu3c1IBHgc3cE09wTgn8C3Nuk8566U4IvZeMzV7wHXjZGq%2BDcHED3rsQ%2BvkWAKGdBaZ0V9QxzFCvgB%2BkVoqyFfk4pK8hP5uJ0AEHKeUCp4y6cAw5HAqq2UBIcOqjpiAsEec8157yJxzCQSg/O/h/CYOGqZHBhCprXPJcQl5qRUjnDeUkc4HyCCITRTJFatD1qUAYbRVhT0uJ8vYZdLhyDbq8Iek9KRmBXrvTECIriv0yY6N4NIkGciypQ2QDDFRgg1FIxRmjF42isaa30fjBIRiTFk3Macyx1jGbM0YKzf5jiJDOOSiCvm4KL7GGFjYPxOs6LS2yBDAA9PLIWKtLBq16RrLW/jdYVP1n4Q2DB3ANNSWmmprtcm2wzZkh2fRs2FKTb7epeRGlFIEH7ZpSxalNNDqacOLTanRy2LHAa8dunJ04Ki9FLUnkvJdNi4UuKxnfJIJM4lxc5llwrpQQBPd1JmHgYSwIgRm5UI0IS6SokDm9KObYJe0yRoCRALXa%2B/hRIT0Uhu88ilpLx38LCg9%2BkT18XjiFfd5U30ktmQTTIzhJBAA%3D)

By turning `(not Pred_0{}(*))` and `(not Pred_1{}(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires Deceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Deceive<Pred_0, Args...> && Deceive<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Monotony<1>>());
```

## Implementation

```C++
template<typename Predicate, typename...Elements>
concept Deceive = not Predicate{}(Elements::value...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgBykrgAyeAyYAHI%2BAEaYxHoADqgKhE4MHt6%2BAaRJKY4CoeFRLLHxXLaY9vkMQgRMxAQZPn5cgXaYDmm19QSFkTFxegp1DU1ZrbYjvWH9JYNcAJS2qF7EyOwcBJgsCQZbJgDMbgQAngmMrJgA1MrEmPiiW6RXp%2BfMbAB0X9j0bIIKh2wJg0AEE0Ax1gkCFcACIdTB4ABu10OMKuDFQ0Nu9zwj0wJgA7FYCTCID9towCAoQCBEWIvJgvh8FocrKDgSCAPQAKl5fP5As5HJ5fKuABVMMMFFd%2BULQSKBYreXKQRyvCkjDc7ugAPoaK6oq5YZC0V6YCAmACsVktpKYXiITJZRLuBFWDCuVDESlZhJhLIObNVoPVYWAWvuOq4BoOaONprO5qtNrtDtQTsJFld7s93vxgb9AaDHK2Oz2%2Bbc9qIVwAkoCOcNiF4HFcALICTECE4czMcq79q7DJiOZBXcHDTCqBLEK5V1BXOneFFEusk33stcF9mg0u7YcVs3vRlfEHEYAAg5A0F3ACOXjwd2lcPWSIr2N1Gmep/PTProPHWxTjO0SoJ4npeAwEDOlmmBusQHperQPoFmu24gru5aHMciZHky34Xlep6YHeD6SrC8Kvlh756l%2BZ4KL%2Bl4GmYABs5jMeRL7IlR2pRrRP5fH%2BYICBOQFXCBYFUBBUGZtm8EvE2%2BbEjCPagkOI46kwChKA01AQVh7YYkQDDdkcXD1peUFFhwSy0Jwlq8H4HBaKQqCcG41jWIOKxrCiZgHDwpAEJo1lLAA1iAlqSB8GiSFwBIHBoloaCxzFmP4gS2Rwki8CwEgaJ%2BjnOa5HC8NSn5BU51mkHAsAwIgIArAQCQOuQlBoDsdBxBElycKo/jMQAtMxkhXMAyCjlIHxmLwOJEMQeDoHo/CCCIYjsFIMiCIoKjqJVpC6OUADuxBMAknA8DZdkOcFLmcAA8g6zXQqgVBXH1g3DaN41XJNZhXBAHgdfQM7mP5Cy8BVWhLBASDtQknVkBQEBwwjIDAFIZh8HQWzENSEDRDd0RhPUJznbwRPMMQJx3dE2gdBVAXtX8BB3QwtCk3tWDRF4wCVrQSFk6QWAsIYwDiJzpGdMi1J7ZOHQOhsAVhFsmXObQeDRCdVMeFgN0EPNuXcLwyLECBShwiLRjq0YwVLFQBjngAangmCHXdbyC8twiiOIG1e9tag3Qd%2BiiygHmWPoGvUpASyoFCaQywNwzoKipiWNYZhFSb81YNHUEVFUaQuAw7ieM0eghDMxSlIkySpAIYwtDkdfVH01fzAX9NdFMjdDJUXcCN0DRtwMZSTD0vflEOw9V6PEhLAo3nrPP%2BhXaQhW8MVb39UNI1jRNUV/WS%2BBzUxYMQ7bSwIJgTBYPE%2BfhZIBwfAAnAcBKSDFZiSMx%2BWWsxL9V5ZRyiAfyHxmJcGYv4F%2B/hIGRS4JaN%2BzF143WKqVEA5VbbVTqjDBqj0WpIxRsDbqbBOD1BYIiAkA0mBjgMJqLgL8PhcGijNE%2BJAFpLVkKtX20h/ZKEDntXQmNjqnTJpdDg9kUF7WKg9JqDorgvVnMQChVCaEmlFj9RhzD9QA1QEDOIZ8zDg0Clg3BRC4itWRno%2BGwMQDkMoQNdRRgGFcE/DQU0cQ8YEz2hTEmgtfFUxpnTBwgsmaUlZuzG6XMeZ8wFkbIW2xRbi2cvgO4UtJQ3TlsgBWgtlaVBuurTWJMdYbGcvrPAhsAomzNpgC2SSwxYPtkwJ2Ls3Ye3iV7bh61eGyADrtZyQiQ42zTlYCOhS86x3jsJTgScCAp1jCMjOWc4g5wyTHTunRnAQFcJPIIJcR5zDHrkeu6Qy7jGbnkNIBya5T37psmoPczlN3aPcoe0wihzyno8zIzypjXPmAvJe61xGSI3rdDgSiVHUNoRohhTDor/VwIQEgZ9FgX0qgsK%2BN876UHEdlUguUDiMJigSRBBJ4qSG/sNcoYK0G2AwSYjF2D4C4Mak9Sx5jiAkI2OQz6LAFCIlHIiOF5ZhisORTnThK0fbdM2vIfh/SdCgNICIs6RsQXXWkfdfBz1Xq8pGvywVC4RX7mGP9QGNiDGgwOMYyGVUzHWIRhyx1tjBUJASDqYVL8dSioIBpZRw0sYeNxpQbxzkAkcwChGoJ9NQl6OZhEjmKTMDc15mIOJAVhZJNKbwVJXdpaZNUPLLYuTBD5L2oUrWJwSl6wNoLapyRamJKtg0plTSWmu3dowT2XCZUSB6VtBVQdlV0OMOHGw4z4CTOqDLTkycw7p0sJnTe2cFprPzi86oxdS4/Irvs2ehza6XIbk8o9Jz/lj03d3Cep7bmF0Hn8g9Nzx6jFvS%2B95swbmAtWMvRYQDQWoM4JCvlAqhUmq2Ga4%2BErUW2svqQa%2Bt9Bj50yvi3KZhGEHAOJaJKsV8qYYJFAqRRVODoMwRisKIBJCWlfpafwLEX6SBfvFd%2BXADhAIOJq4jJVGVQ3EdNIjm8SM8ZCqQE2KRnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/concepts/deceive.hpp)
- [unit test](../../../../tests/unit/concepts/typelivore/deceive.test.hpp)
