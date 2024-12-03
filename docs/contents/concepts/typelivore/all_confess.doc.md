<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AllConfess`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-2">To Index</a></p>

## Description

`Typelivore::AllConfess` accepts a callable type predicate and a list of elements.
It returns true if the predicate evaluates to `true` for the value result of every element and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...&&Predicate{}(Elements::value))</code></pre>

## Structure

```C++
template<typename, typename...>
concept AllConfess = REQUIREMENT;
```

## Examples

`AllConfess` turns a fold expression of a callable type predicate over `&&` into a concept so that it can be used for subsumption.

The following code will fail since `(...&&Pred_0{}(*))` and `(...&&Pred_0{}(*)) && (...&&Pred_1{}(*))` are both atomic:

```C++
using Pred_0 = decltype([](auto...){return true;});

using Pred_1 = decltype([](auto...){return true;});

template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (...&&Pred_0{}(Args::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...&&Pred_0{}(Args::value)) && (...&&Pred_1{}(Args::value))
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgCcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BxemUYA1MrEmOgA%2BhqHJv4AIodYyLQEAJ6pmBAmgVaBtxBMXiIADoQasTAB2CynAhbBiHAjELyYG5WcG3MH%2BKwaACCJhx%2BwiwGOpwuXGudwe9Webw%2BXx%2BfwBwNBEKhmBhxDhCKRKIh6J5OLx2IImBYqQMwpubkZqEOAEkbthBXNEQ5DgBZASoIgMF6ClmCw6Gw5zJiOZCHNAMOaYVSpYiHaWHABuYiR10h8rR/NxXsxepxwtF4uR/jcr3ezDYIKB2OIwAUCsFpwAjl48KcFIcINHzAA2PMnM6XfVoiCx%2BMgEAu7yYVZgnGW622%2B2xVCeQ5ULwMCBgyHQ2EdsRKHlegUBkVi00hsM0yOYaPlhP%2BRU4lNpjPZkF5gsk4uQ3lluMKSvVpF165mfOXrM5y87otcEt/Rcn121%2BvYxvC5uHVvtzvdr2rLspyiIhqitz%2BtiJpmucTAKEorTUF2koagwWoCLqoaPsuCo9hiFgcOstCcIEvB%2BBwWikKgnBuNY1jGps2yYBe/g8KQBCaER6wANYgIEuZAgAHLmUiBOCuaSEk/gSWY/j6Jwki8CwEgaBopAUVRNEcLwx7qZxlFEaQcCwDAiAgJsBCpIC5CUGgop0AkUSsLsqgiQAtJJhzAMg5pSECZi8GchAkHg6B6PwggiGI7BSDIgiKCo6iGaQuhcKQADuxBMKknA8MRpHkVx1GcAA8oC1kEIcqBUIcbm5p5kjeb5hz%2BWYWYeA59D2uYbGrLwBlaOsEBIPZqSOWQFAQGNE0gMAUhmHwdDCsQx4QLExWxBELQvHlvBbcwxAvKVsTaPUBnsfZbCCKVDC0LtKVYLEXjAFKtC0Me3C8FgLCGMA4iPem514E6mCfVRNr1ICuzsREwokSltB4LE2VHR4WDFQieAqV9pCg8QrZKLcIp/UjRhcesVAGPGABqeCYBlpURnt8XCKI4hxZF8hKGoxVpfof0oPRlj6Mjx6QOsqCpH0n3uXM6A3LcpiWNYZhafjxBhWD8DrHUDTOBArjTH46VhIsFRVHoRRZAIxtWxkNsMMMFsrN0vSNPMdvpXrfQDK0zujNUEyDF7wf%2B%2BbgcSLrTE7FHCkcGRGnFdpdUeV5Pl%2BZIAVZrgIU9XJXD9RxFPrAgmBMFgiQ9qQfGSP4QLSeCkgaJIZiSLmakCSkCNKaQKlsUCom5kJSRCVwuaBJIXCBNJuZJyl2m6SA%2BkU8ZZkjRZFU2VNM3dc5bCcC0LBOuC7lMBaBhHDUQJcECEP4EQmvhelXPRRz0hc4lvMpboi1ZTle0CoJyKgvMqW8qo1QdMQY%2Bp9z5PD%2Bq1JIN874dVQF1BIrEzBF0GkZDeu8Ei2Wmmg8a3UQBHxPu5eBRgahcHUjQZ4CQ1obRSgdHaLNWFHROmdBwLMrqMAILde6xUnovTeh9FmP1Sa7CovgU4DRQbgyCqoKGwoWZwx6MVJGKMdro2kQNTWON2L40JpgYmv0jBk1AIZSm1MFB0wZkzRgLNX7s1ih/WQX9kpUV/gLcmysrAiy0eLauUsZacDlgQBWdx/Gq3VgkJ%2B2sJZu2BgbI2ngOh6DNuUSO6VrZ9FDnk7IAdlhBx9h7EO6T8jex6Ck/o8ximW29p7SpJsw4LGySUuOCgY6xSAYnTSvAU7kNgRfBB19b5XAgLnR%2BrFC4DRLqQMuFcxjVx7spAISCW7ghnuCcE/hW7tynvPLSnAl4r2sWveAG9LKVUIfg4g%2B9dhHy8iwBQTpzROmvsGOYQUH6hWfqzN%2BbjWaeL5gETK2VcpfT6SAk5HBypWUBNVWqzymqvPec6L5U45ioPQfnfw/hsGrzwcQiadzSWkPeakVI5xPlJHON8ggcFoGSSWgw1alBmFUQ4Q9diPKuHnV4Wg66Ai7oPRkZgZ6r0xDiNxpIixejSCyOBgo4qkNkDQzUYIDRiNkaoxeLozGBiWbGIyKYkmFjCSrypkwWm9NGbM1xi4mKEh3EJR5l4nQ4LL7GGFjYIJOtqLS2yJ9AA9PLIWKtLBq0GRrLWwTdY1P1n4Q2DB3AtMyWmhprtCm2wzbkh2fRs2lKTb7ZpeRWllIEH7dpSxGltNDiacOHTGnRy2LHQu8d%2BnJ04FAlgLy3kfKxcKHFUy/n4rmcXaxpdy6V0oEA3uKkzBIIJYEQILdaEaAJRJISxzBmnNsMvKdQ1eIgDrjffwQlJ5yXXbmOSEl47%2BFhfunSx7uLx0Cnukqr6cF1jxow7IZ6gA%3D%3D%3D)

By turning `(...&&Pred_0(*))` and `(...&&Pred_1(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<typename Predicate, typename...Elements>
concept AllConfess = (...&&Predicate{}(Elements::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAHKSuADJ4DJgAcj4ARpjEIGakAA6oCoRODB7evgHBaRmOAuGRMSzxicl2mA5ZQgRMxAQ5Pn5Btpj2xQwNTQSl0XEJSbaNza15HQrjAxFDFSNmAJS2qF7EyOwcBJgsKQa7JgDMbgQAnimMrJgA1MrEmPiiu6S3F1fMbAB0v9j0bEEChO2BMGgAgmgGFsUgRbuDaLQPAwqJgFApbicACK3CC/b7mABsRIeTzwL0wJgA7FYqViIP89owCAoQCAAG5iLyYZbLE5WCFg8EAegAVOKJZKpcKhWKJbcACpolm3SUyiFyqVa8Xq8FCrwZIz3R7oAD6GkxxxxWGQtA%2BmAgJn8Vn89KYXiI%2BL5NMeBA2DHexG5/OpWL5xwFeohBoiwGNT1NXEt1tqdsuDqdLrdHtQXupFl9/sDwYjofDkaFu32h0pp3dRFuAEkQUKZkGHLcALICVBEBjnIX5oW3Ee3GZMRzIW5QmaYVQpYi3euoW6c7x3fPNukhwXb0uCiFVg4T2tndNfTD48HEYDA46giGPACOXjwjwxCKRAlR6JOblJZoaG8163viLYQjOuzzousSoJ4txUF4DAQN6BaYH6xABlQYhKCG24HuCR41n%2B9oXleN53g%2B16YC%2Bb5ovCiLIj%2Bd7/ia5rARRYH3piZjErxDFfiiaIsQBiYcaBvzgZCAiztBtywfBiHIahhaYcWta0lig4QuOk6mkw6IJAQ1BIX%2B3YML2AgDqcXAtveKHlhwqy0Jw/i8H4HBaKQqCcG41jWGO6ybBuZjHDwpAEJoTmrAA1gEkjfBokhcFSxwaP4Gi8YSZiBMELkcJIvAsBIGhAR5Xk%2BRwvCskBkWeU5pBwLAMCICA6wECkHrkJQaD7HQCRRDcnCqIEhIALSEpItzAMgU5SN8Zi8GSRDEHg6B6PwggiGI7BSDIgiKCo6j1aQuhcKQADuxBMCknA8M5rnuVF3mcAA8h6nVwqgVC3CN42TdNs23PNZi4h4fX0Iu5hhcsvB1VoqwQEgvUpP1ZAUBAKNoyAwBSMkNB2gkrIQLEz2xBETTnHdvDk8wxDnK9sTaLUdXhb1gIEK9DC0FTJ1YLEXjAG4Yi0Ky3C8FgLCGMA4h83RdTsmiz1zrUHrbOFES7PlXm0HgsTXfTHhYM9BCrcV4ukIrxCwUoWJ7NLutGFFqxUAYt4AGp4JgF2vZ81P7cIojiHtm3yEoajPWd%2BjSyg/mWPoeuspAqyoLCWRi2NMzoNipiWNYZgVVbq1YEnKGdN0WQuAw7ieG0ehhPM5SVHohSZAIkx%2BOdrc9IMTcjOdNR1AIfQTLXeQD10LP1LMvfDIkA%2BzB3ejjs0s%2BLPPqwKEFWwSA9HBuaQ5W8JVv2jRNU0zXNCWgwy%2BArTxMNw87qwIJgTBYIkZdxZIxzfAAnMcKkkgkpmEkISUq/hCR/30JwQqpBiphW%2BISLghJAh/0CCg/wyV/AAMJIfZ6lVqogFqs7RqLUkZtQ%2Bl1DGWNIaDTYJwJoLB2RUjGkwacBgjRcD/t8LgiUlp3xIGtDashtrB2kKHQ6EcTq6GSFdG61M94HyPi9Dg70OoeluN9JcxBmGsPYbaaWwMeF8ItBAcGqNIYPxWE/eqiNkaoAhgkbqmNHGWJGEwlhY1DFGG4VwICBNdjEGJqTE6tNKb%2B3CfTRmzMHD%2B3ZsyLmPNnr80FsLREYtwqSwdtsLy%2BBHgKyVidFWyA1b%2B01l0Z6ut9aUyNrkuGZt/ZWxtpgO2UsjCO1AHYvgbsFCe29r7Rg/tQ5iN2hI2QUjjpeVkdHJ2ucrDx2qaXFOacZKcEzgQbOVp5n50LgkYuStk7lyns4CArgl7nQbmUOeLd0ht2yGPTuqQ7k90bjcieFdh6L0ecvSeQ9egzzeevZe3zchPJXnMa5wKuCb23rtJRT0Ton08fojhRjuG8MSriXAhASAPxhbYhGL834f0oHvOBCCeFJSpDgqkqVJCgMmudFRhDbDEIiqQpqrV2qfRcbQgaQ0OBMIBiwBQ7IpzsgxTWGYAjcXFxEVtIOYyA6TMjiAY4l1rq3XFgi/BSK3pUK%2Bj9YVU1RXitXFKk8MwwZuLRg/Y4sMOXdIofy9GPVbWQw5MgFIKRTSSr/qaaVBB9K6MmnwOgQSQlkwpvTSJMaGZMxZvExxHMkm8zyZgAWQsRaZIlvbDp9TSD5KnorMWXkSllIthU7WvBqkG3OHUk2jSLbNPSK0/NMtYykNdkwD2XsfZ%2BwtiMpVEhxkHXDlMnQ6rZnGDjjYJZ8AVk9DFsKLOsc86WALsfIua1Dll0Hj0KuNcwX12rmvZuXcXlZAuc8ooWRz392Of8keLQfkfJOQC/oD755jH6DeiF37d5rA2DvGFMD96IoqpwHRLARViolZa3Y1rb5yvxY6%2BG0VSCv3fiMMu%2BUKVJB4ccY4/gMrJVKsRqkqC9VQaqmykhdjYogEkP4f%2BQReJ/0kH/VKgCuAavyscSDx9OCEsw/lRaNHhN0Yw7yS2RNK6SCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/concepts/all_confess.hpp)
- [unit test](../../../../tests/unit/concepts/typelivore/all_confess.test.hpp)
