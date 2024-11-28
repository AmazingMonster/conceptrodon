<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `AnyFalsify`

## Description

`Pagelivore::AnyFalsify` accepts a class template predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `false` and returns false if otherwise.

<pre><code>   Predicate, Variables...
-> (...||(not Predicate&lt;Variables&gt;::value))</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept AnyFalsify = REQUIREMENT;
```

## Examples

`AnyFalsify` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||(not Pred_0<*>::value))` and `(...||(not Pred_0<*>::value)) && (...||(not Pred_1<*>::value))` are both atomic:

```C++
template<auto...>
struct Pred_0
{
    static constexpr bool value {false};
};

template<auto...>
struct Pred_1
{
    static constexpr bool value {false};
};

template<auto...Args>
requires (...||(not Pred_0<Args>::value))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||(not Pred_0<Args>::value)) && (...||(not Pred_1<Args>::value))
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BXKQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJZkl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbkxeRAB01yfYJhoAgjPEXg4A1MrEmOgA%2Bhr3DxMAHYrI83uC3jMmI5kG80AwZphVMliG8YqhPG8AG5iLyYN7AixUMRKYEAEROoMBQIpxypAN2%2B0OmBOZwuqGul1uAOerwIHy%2Bvy4AMJAIhkMaMLhAkRyNR6MxOO8%2BMJxNopJplJFmrpIsejIO0JZp3OV2uD2IwAU3MeXwAjl48F8FG8IJzgW4PRAGKh%2BZ9vn9WRarbcQCAlXjlssAfDZSi0RjaG8qF4GBBoyCvgQNgxkyTjVZNY8GXtDUcTezOcHrcc7rbMA6nZgXW6bkDPe3vb6BQH/qdq6Hw7jMFGCWYAGzmceu93tr0%2Bv2Cn7C/uWmvYMMRkfRx6x3ZyhOYlNpjMWLM5t4EF4F8l6p6SvDIH5MBRKZrUVOslfYdPRukcVZaE4AJeD8DgtFIVBOE9SxrEhdZNhVMxjh4UgCE0ADVgAaxAAJx0uAAOccpACIFx0kABOY4yOQ/ROEkXgWAkDQNFIMCIKgjheAUEBWPQ8CANIOBYBgRAQHWAhkguchKDQfY6HiSJWG2VQiIAWnIt5gGQWEpEuMxeG%2BQgSDwdA9H4QQRDEdgpBkQRFBUdQBNIXQkgAd2IJhkk4HhAOA0CMMgzgAHkLik/lUCoN5VPHDTJC0nS3j0sxXQ8eT6FRcwUOWXh%2BK0VYICQOTkgUsgKAgYrSpAYApDMPg6F2YgeIgGJApicImgATx83h2uYYhOuCmJtFqfjULkthBGChhaG65ysBiLxgDOWh1R60gsBYQxgHEeamzqLFm0CpFagubZUPCXYgOc2g8BiTyBo8LBAqvPAmO4XhDuIdElDJPZttuowMNWKgDCtAA1PBMDc4LkkYdaLOEURxFsxGHLUQLXP0baUGsax9DunjIFWVBkh6HiODUmZ0BOMlTFgywzA4r7iFMo7ic6bpMhcBh3E8No9FCeYygqPQCgyARJj8JJxZ6QYRZGaoulG%2BpZilvQajqAQ%2BmaeXhgSao1f53JDf6PXFgN1YFAQrYJD8jgQLYwLOOi9TNO03TJH011cGMzLkK4HK0OB1YEEwJgsASdNSBwyRjkuKigUkDRJDMSRxxYvCKLojgGNIJiUMuYjxwIiiCK4ccAkkLgAio8cneczjuN44OBIK0TCvEsLpPKyqMqUthOCaFgsSBNSmDhAwjCSijLi4S4IKMohWbMpJEaslHpDRpQMec3Q6o8ryevtx32N4TjQski43kit5h9H8fJ%2B2me54X1LUHS%2BIx2OMwg7ywTO593iDJCqH8SoZRAPfMeyAp41QolwViNBaCNWaq1ZyfUurrQwQNIaI0HDrQmowAg01ZqBQWktFaa0PobX%2BkYXaEF8BfAOkdZyJ1kBnXWpdLogVbr3S6k9bYEFXrvVQl9H6mA/pbToeEUAbc%2BBgwUJDaGsN4bUPXsjGyW9ZDoychBfe2Mgb0ysJYAmMQibR1JuTTgVMCA02OHTPGjNmbxBXuzaOmseg8z5jkaWwRebm1FjLNIEssjG18bLTIATFacxVtrI2PiNbKy1r0WYUSDZjH6OrU2uthb6ztmsDYttA451Ps7Tgd9iAjzHhPGBz8uCz3nhoH2%2BBl7f0DrlEOpAw4RxGNHa6ecC6zxTkCWuQIgTHFTunauDcOKcGbnxYGQkO5IAkuFEBQDiAD22MPTSLAFBYlhFieplxmQzEMi0kyq87JI2shILR9kd66J0CAY4pBD7eQ%2BifAKjcQrdwilFHZ8U9kHOxMc05/IIBpXAV/LKxw/6LMAWA0q6ykUQIOckZIPwjkUR%2BOC58lTyL1WQfEVBbUOoDSweSwaw1RoEI/pNYhM05oMMwItZaYgqGoU2gDQRvBGEq0OhTReqhTq7E4YIbhN07oPU6gIl6rMRGfXiOIyRAMZGLNBkwCGUMYZwzAqhdRtzUbaMeZjF5BjjCOJsLw8xJMyaZApgAemprjBmFgmbnxZmzW1MTkleKyX49AaSxbBJ6AGiJxRckW0SVzOJmSwkxtiSks2UbAkZImAm7JcxSh5OKdbQpNkvkzPPuUwFbxgWHLBUaGYzS/ZtPhW3UO4dI6UHtgM/ws9jjHACAEFOCCNBdrIgRYtQUuK2Bbv/KMMcQBxznscAiVdkK9vHMhMiOdjjfNmWOyd9sDIjqbq3fKqwvrpGcJIIAA)

By turning `(...||(not Pred_0<*>::value))` and `(...||(not Pred_1<*>::value))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<auto...Args>
requires AnyFalsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AnyFalsify<Pred_0, Args...> && AnyFalsify<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept AnyFalsify = (...||(not Predicate<Variables>::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAzKSuADJ4DJgAcj4ARpjEIGakAA6oCoRODB7evgHBaRmOAuGRMSzxicl2mA5ZQgRMxAQ5Pn5Btpj2xQwNTQSl0XEJSbaNza15HQrjAxFDFSNmAJS2qF7EyOwcBJgsKQa7JoFuu/uHmMduTF5EAHQPx9gA1MgGCgrPysSY%2BKK7pGeN3uDwAak08ExYvQFE8TBoAIJoBhbFIEZ4IhgATwAYmIMlQsc9jgARZ4QB53EwAdjcNLcEAYqHR31%2BeH%2BlxO4OIkOhmFhgWwIBAADcxF5MMtlscrIj4QiAPQAKhVqrV6oV8uVqueABV%2BQRPmrNYjterzSqTQj5WcDkwjidgahKXDETNiF4HF8fugAPoaeU02UI56h54ze3s14CGaYVQpYjPWKoTzPMXeTDE6kWKj4y7UkkywMFotyxG2i5XJ0uwXy92elk%2B31cYvBsPhxqOZDRhix%2BOJ5Op9MSrM5vM0wuBYMT0vW8t7O0O663Z0PBHEYAC7Dyn4ARy8eB%2Bn0xuPxeEJV1Zfo0gPXm5r28RyL7CaTKdozyoXgYEGl2Z%2BBAbAwn7jlOM5lgiFb2pyy4gncd5bjumD7oe/IYtieK0ASWKXk2N4YhuCgPsSZj%2BOY/joaeWHnjhJxXs2t6EQ%2B8rPrs/ZvqmX4/n%2BFgAUBzwEB6nJWCWEERl2vpMB8CQENQ35XC2gq/tKU4cKstCcAArLwfgcFopCoJwdKWNY4brJsmbmIEPCkAQmhqasADWICaZIdwaJIXDUoEGiaRopH%2BGYAAcQX6Jwki8CwEgaDeun6YZHC8AoIA3nZelqaQcCwDAiAgOsBApLc5CUGg%2Bx0AkUSsNsqhBf4AC0/iSM8wDIN2Uh3GYvBskQPLoHo/CCCIYjsFIMiCIoKjqOlpC6FwpAAO7EEwKScDw6laTp9kGZwADytyFeiqBUM8NX1Y1zWtc87VmOSHhlfQiZWVwyy8GlWirBASClSk5VkBQEDfb9IDAFIyQ0LQuzEMlECxFtsQRE0WKrbw8PMMQWI7bE2i1GlNmlWwgg7QwtBI9NWCxF4wDXLQWHI6QWAsIYwDiGTqF1CK/JbXGtS3NsNkRLsGnTbQeCxEt6MeFgW2CXgUXcLwHPEMmSgknsTMi0Y9mrFQBibqCeCYPNO0pIwdMDcIojiKN5sTWoW2zfoTMoNY1j6KLyWQKsqBolkyUcHVMzoKSpgmZYZjxYrvWc57nTdFkLgMO4nhtHoYTzOUlR6IUmQCJMfhzdnPSDBnIxzTUdQCH0EzJ3kZddDj9SzMXwyJGXsx53oEbNM3iyt6sCjmVsEjrRw2mkHFvAJSdtUNU1LVtW5N0QLghAkCR1kvbZWurAgmBMFgiS/qQzmSIEdwAJyBNSkgeWYkj%2BDFmn%2BOfYUcBFpBRdZdz%2BFw/hBefQVf6uS4JpS%2B/hx5bQSklFKW90ofRyp9PK%2B0ir/UBg9SqbBOBNBYCKakdUmCvAMEYK6587hcHcl1fAPU8B9TmubIaVtpA2yUHbaauhkiLWWsjEeY8J7bQ4HtAqtxnhHSBMQHBeCCFvCZiQsh7lbqoHugkdeKxXpa0yl9RRP0HrFQBlooG2DcF1WkUYLg58uA3nBpDaGsNpqo0RnTex6NMbYwcHTfGjACBExJltcmlNqa03lvTNWRgWb6XwD8dmnNprc2QLzOmAsuhbRFmLRGkttj6RlnLGyitlaYFVozUJERQBwL4LrBQ%2BtDbG1NkE%2BhlsRpMNkLbKa%2Bl2GO01iHKwlg3axA9kfb2PQ/YBwIEHQIJJOnWHDpPSONDo5H3Lj0BOSdcj5xCInHumcC7pBztkGuqzC5ZA2aXWODdK7tz2Z3euFdehN3Ti3Tu5yVkPP6EcvuawNhD2eq/XhkDOBiIkfgwhMizFyI0OSFePV17PTUXAnee8D6UBHu/T%2BpCPLUlAdSbykg76NTmnwqBtgYFvQyllXK%2BUDq6LQRVKqWDxHnRYAoEU3YRQgouDMShq9er9VkAwhpY15AsJaToEAwROErXljwza00EqCIOiI462D6WMuZay6CMwFFKMemYQIgRN7Eo%2BpozVlL9EPVFMgFIKRfQsvPr6NlBBJJ0qYXQaxlBbH6ScaTGyHqXE43cYogmXjiak3CZgCmVMxCBJsgzdWGTeARIbhzP2%2BlYnxKCYkoW%2BkUniyxOk6WPJskKwSHkgp6tinqJ1kwPWBsjYm10jZOpw0JCNPGoK%2B2Ir2nGBdt0lJfSvY%2BxjJwBUgdnahwsFMgyMysC9pOdcpZHc5ppzKPcrZRQsjztSNsoudze6XLjmc/o66FmNxeduzZYwD0XLbiepdO6vkDw%2BSNSVEDpV/MVU1BlTK0yqt2Oq5eVC15PT1dvUgu994jCPkLZFSRSE6s0n5TyMUdXUj/s%2B%2BKnBoGpWAyfTSF9NJBVIufSQ59vJXy4MEIWgQpVocSrA96I9Oqocnuh2jDlSCKwyM4SQQA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/concepts/any_falsify.hpp)
- [unit test](../../../../tests/unit/concepts/pagelivore/any_falsify.test.hpp)
