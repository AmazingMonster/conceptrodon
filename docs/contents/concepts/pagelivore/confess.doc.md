<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Confess`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-1">To Index</a></p>

## Description

`Pagelivore::Confess` accepts a class template predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns true and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> Predicate&lt;Elements::value...&gt;::value</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept Confess = REQUIREMENT;
```

## Examples

`Confess` turns a class template predicate into a concept so that it can be used for subsumption.

The following code will fail since `Pred_0<*>::value` and `Pred_0<*>::value && Pred_1<*>::value` are both atomic:

```C++
template<auto...>
struct Pred_0
{
    static constexpr bool value {true};
};

template<auto...>
struct Pred_1
{
    static constexpr bool value {true};
};

template<auto I>
struct Monotony
{
    static constexpr auto value {I};
};

template<typename...Args>
requires Pred_0<Args::value...>::value
constexpr bool fun(){return false;}

template<typename...Args>
requires Pred_0<Args::value...>::value && Pred_1<Args::value...>::value
constexpr bool fun(){return true;}

static_assert(fun<Monotony<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEIGYA7KQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7Jv5uTF5EAHRXx9gmGgCCE8ReDgDUysSY6AD6Gnf3JmSVger1BrzmjmQrzQDAmmFUaWIr1iqE8rwAbmIvJhXoCLARnphAQARY7AgHJUn%2Bcn/Xb7Q5Ek5nS7Xfy3B5PF4Ed6fH5cf54/5g8EtSHQgRwhFIlFozHeHF4gnYklkgWU1UPWl7A5MI5M86oV4ASRu/05bwAsgJUEQGABPNXk4UQvBQmGSxGvZmGuXY3FAk3q6lqqk0h50nV6twEO1pRisTBXC73YjABSmh6fACOXjwnwUPK%2Bv2ObhTaZAIF9idZ2ArVf%2B7t2UuRqNoryoXgYEGWeM%2BBA2DHbYiUqvVmvD2oZJZjceYbCTZfTbP%2B2dz%2BcLPz%2BJ0Xdax1YuN138txZgAbOZTxvvvzt6mFEfsUnD5W9w2JU3PTK2x2uz2gX2B1eJVGSsMcAQ5UVXW%2BJgFCUNpqE7EsrQYG0BAdE4b1uNlux7akOFWWhOECXg/A4LRSFQTg3GsaxwXWTYFTMfweFIAhNHw1YAGsQECU8LgADlPKRAmSU9JAATn8USmP0ThJF4FgJA0DRSFI8jKI4Xh7xUtiyPw0g4FgGBEBAdYCDSc5yEoNB9joBIogTThVEEgBaMTXmAZAoSkC4zF4L5CBIPB0D0fhBBEMR2CkGRBEUFR1D00hdC4UgAHdiCYNJOB4AiiJI9iKM4AB5c4LO5VAqFeZzTzcyQPK814fLMV4IA8Wz6CRcxmOWXhdK0VYICQGy0jssgKAgYbRpAYApDMPg6F2Yh7wgWICtiCJWjtbLeHW5hiDtIrYm0TAHG20gbLYQQioYWgtsSrBYi8YBTloWh724XgsBYQxgHEe68xOxx0Uwd7yPhE7zm2FiIl2QjEtoPBYgy/aPCwAqCTwRSPtIYHiBRJRiT2H6EaMdjVioAw0wANTwTBUqK2czrC4RRHEaLmbitQCuS/QfpQGjLH0RH70gVZUDSRp3pciZ0GOYlTEsawzHU3HiGCkH4FWOxAZyFwGHcTxOj0MIImGKpRhS4psgEaY/EtzJrYYBYRkSFLtYcPpJnaQ2Cjd%2BodYEfo2md83XdsL3bb0OZg9NxYLa1%2BitgkXKOGI1SCo0qrXPczzvMkXyWtwQLOqYrgetYsnVgQTAmCwRJu1IbjJH8C5JOSSQNEkMxJFPZTePE2SOHk0hFOYi4hNPfjxP4rhT0CSQuECSTT3TxKNK0kAdLJgzjMG0zSss8bJo6hy2E4VoWHRZIXKYaEDCMRrxIuLgLjB/AiDVkKUuZiK2ekDmlBc0SroOa6VMrbRTmnNSvANIlXMucV4FUvTEEvtfW%2ByB77AEfs/V%2BLU2ojQ6iefwZhy59X0nvY%2BCQrITVQO1UYF8r4uQwT9Lg4kuAqRoLQRay1VqJV2ptM6/D9qHWOqdbGF1GAEGurdAqD0novTemdL6xNtjkXwJ8D2wNQb%2BVUBDXYZ0Yb1AKgjJGm1UaqN6mrLGLFcb40wITb6RgSagD0uTSmCgaZ0wZowJmshf5RX/rITmCVyIgN5qTBWVhBYmJFg3cWktODSwILLfw8sBYWGVjA1W6tYla39h7ZwEBXCRxSibCoLs9BW0aCU9IDtGghyWH7XogcI4%2Bztj0AOTQvYNItuHAYNTo6DFjhUsuawNhJ1GXDKBGdODINQTfO%2BP1sEvw0IXd%2BJAiFl16pXUg1da6jAbnDYeo8n6d2SEvZIyR/Bdx7gvVe6lOAby3q4ne8A95mTKtQyhxBT7bAvu5FgCh0RQnRKwi4DIJj%2BXWZ/UKfjWYBJivIQBISdABDShlLKH1IH5TXsVA%2B5VKr/LqoC4FGIwUQu5K1WhBCEhEP8KQ7eFDqWjS%2BcyjqlZkBpDSN8UF4lvgUugigsS80uEJB4WtDa%2B1BGSoOkdQGZ0JFXRundNRmBHrPTEIo7GyinEWNIOonWWiCrg2QJDAxggjHw0RsjO05j0ZWLOrYzI9iiZOIiC4/qfB3GePpozbGP94USECbFZF3M0WYP5oraJwtNYUQljkd6AB6GWkaokZJVgkT%2BGtRYdIKX4Ip%2BsallLNo02pJQcg1KqTkHpYd3aNCDt7fI7S62e3mMM0OUdWlNs7W28pHbRkKETlFbF9yYGzKJa8ElILyW6hBpSouH9NkMtcVXGuddKAp2OUkJ%2B/ggiBE7uwjQu7RL8VHYVTSthN4VxXY3EAzdn7%2BH4vPJi%2B7TxMVEoPfwOKHkXrIcsFOfkz3r2vf1VYuMsjOEkEAA)

By turning `Pred_0<*>::value` and `Pred_1<*>::value` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires Confess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Confess<Pred_0, Args...> && Confess<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Monotony<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept Confess = Predicate<Elements::value...>::value;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAbKSuADJ4DJgAcj4ARpjEIGakAA6oCoRODB7evnppGY4C4ZExLPGJXLaY9kUMQgRMxAQ5Pn5B1bVZDU0EJdFxCUm2jc2teVUKo30RA%2BVDXACUtqhexMjsHASYLCkG2yYAzG7bu/uYR25MXkQAdPdH2ADUyAYKCk/KxJj4otukTwIAE8UoxWJh7rdsPQ2IIFI8TBoAIJoBgbFIEJ4eBhUTDvJ5HAAin2%2BvyYB2O0J2jAIChAIAAbmIvBCHodsPSmd4LocrMjEUiAPQAKlFYvFEsFApFYqeABU8bSnuKpciZRKNaLVUiBac9uSeVcbqhIQjkVNiF4HCSfgB9DQCkwAdj5SKe7qeU3JeGQLwEU0wqhSxCesVQnieXJZBJdBEtFydhKOrudSd5juRevOl2udzZ2AFFqtmK%2Bdq4jpdAo9nsajl9qIDQZDYYjUcwMYscZZqeTFbTKczO31FKNRCeAEkzUii9aALICVBEBhAiuu6teut%2BhiN4NPXOoSPM9vOiyTxO9/nn9P8wdnA2XYGg5hsSFI4jAeHsgXfACOXjw3wfNiuLvJcpboPaAJvh%2BppfsiDbbE2obhrQTxUF4DAQIsJ7fAQawMGhYhKL2543kiWb3scj5gi%2B9zQZ%2BBbIr%2B/6AViAggZ%2BbjgZBTz0bBzzmIEglsTieKcdxVS8e%2BCj8QKCGBruLaoehmHYS6uH4YC8YkUmZEbj6tpMO8CQENQGGXPODCLgIK7HOWX7slh2G8hwyy0Jw/i8H4HBaKQqCcG41jWJ6qzrMeZiHDwpAEJornLAA1gEki3BokhcE6hwaP4GhmIEgRmAAHAV%2BicJIvAsBIGgaKQ3m%2Bf5HC8HS1UxT5rmkHAsAwIgICrAQKQ3OQlBoLsdAJFE4KcKoBWBAAtIEkhPMAyC%2BlItxmLwPyECQeDoHo/CCCIYjsFIMiCIoKjqK1pC6FUADuxBMCknA8G5HlebFfmcAA8jc/WYqgVBPFNs3zYty1PKtZhPBAHgjfQIbmJFiy8C1WjLBASDDSko1kBQEBYzjIDAFIyQ0LQ2zEHSECxB9sQRE0QLPbwdPMMQQJfbE2iYA4TOkMNsIEF9DC0IzV1YLEXjAFctC0HS3C8FgLCGMA4hiwB3OOAyeIfYG3M3JsUURNs7lXbQeCxA9bMeFgH1xngFXy6QWvEGGSiEjsytm0YsXLFQBgfgAangmC3V9T68/twiiOIJ2R%2BdagfTd%2BjKygQWWPo5t0pAyyoBiWRyzNUzoESpiWNYZh1c7xA7dr2edBrWQuAw7ieG0ehhLMZQVPk6SZAI4x%2BFUBR9ww/Rdws9cON00wD3odgNwIPTNGPgyVCMvSz5M0wr/MlTLAooUbBIr0cJ5NUffVQPTXNC1LStyVQxAuBbQjEVLCjPvLAgmBMFgiRYaQRKkhDi3AAJyHCdJIVKZhJCBCqkEUBJUOBlVIBVSKtxAhcECAVUBBUsH%2BDSv4cBwRaq8Hqo1EAzUfbtS6hjHqv0Bp4wJvDcabBOBNBYAyJ0M0mAvAMEYCGoDbhcBShtfARBq67SqJHQ6MdpBxyUAnK6uhkj3UekzE%2BZ9SGfQ4D9PqNwngAz3MQTh3DeGvGVoI4RKVoaw2xvDAkEUzDI2itQuhzCEiDXxqgOGQwOFcJmhYowXBQFcGqmTCmVMaZXRZgzXmsS2Ycy5jzR2/MaRCxFh9cWktpay15orT2mxfL4G%2BFPLWctfK62QPrXmRsagfTNhbBm1siko2rg7KKztXaYHdkrIwXtQCtV9v7BQQcQ5h0YBHWQsjjryNkPHS6vkVHJ29qXKw6dGlZwAbnOoBci4lzThYCuZCq41y2fvGoC8/AQFcJvEIzcd7dyHr3Oodzh51EeRPeeU9F4z1bhMSedQl4zFKKvOefzciD3XsvTuYKlgrDWEfeFJstEX04MY0xPC%2BGWJCdYjQ0Nn4SMcUjD%2BQyv4/z/pQE%2BKC0FCNSk6IhToMqSBgfNKo2jyG2Eoa4oZND4B0N6n9LxHjiCsM2Bw0GLAFAMl9AyXF5wphiJfjtPa0zo6zNOvIRRiydAgEOKQNRT15aaPeldeqei/qGMBhKhaUqZWRnlQaKYtifH2ISMSw4LjUZtXca6nGwq/Xw0ZMgFIKRbRytAbaBVBBDImPmnwOgkTKDRN8gk0WUU01JI1rzNJggMmi2KZgCWUsxB5MdgU/prTSAlIbuUnWqg9bbFqYIepptzaWyBC0227TeZdPSD0j2/SIiDLRnwEZYzQ7h0djI9VEg5lnW1YnPVKzjCHIzrEc5fk87%2Bk4IKIuqcy6WGOX5U5WBN3fLqE3FukL24PNhbvHuhQshvJeVkT5a8L3Tw3v8qFn7fm9HfeC79N6t4AfvU8/eh9jomvPma9FNqnh2tlY67Yzqn7iJIMS9%2BPK0bkt/kMABJsaVJCEYcQ4/hsppSqmRp02DYN1U4BQqhZLAEgEkP4MB/gCq5VAZIUBGUIFcH1SbQ4pqGMNRw3FJB616NkMY5JxYyxnYZGcJIIAA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/concepts/confess.hpp)
- [unit test](../../../../tests/unit/concepts/pagelivore/confess.test.hpp)
