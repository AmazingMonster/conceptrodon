<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsNoexcept`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_noexcept">To Index</a></p>

## Description

`Functivore::IsNoexcept` accepts a function-like type. It returns true if the type is `noexcept` specified and returns false if otherwise.

## Type Signature

```Haskell
IsNoexcept
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsNoexcept
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) noexcept;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) noexcept { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) noexcept { return 0; }
};

/**** Tests ****/
static_assert(! IsNoexcept<decltype(fun)>::value);
static_assert(IsNoexcept<AbominableFun>::value);
static_assert(! IsNoexcept<decltype(FunAddr)>::value);
static_assert(IsNoexcept<decltype(&Tester::fun)>::value);
static_assert(IsNoexcept<FO>::value);
```

## Implementation

The implementation of `IsNoexcept` relies on extracting the qualifiers and specifiers of the function-like type using the metafunction `Analyzer`.

```C++
template <typename F>
struct IsNoexcept
{
    static constexpr bool value
    { static_cast<bool>((1 << 5) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsNoexcept_v
{ static_cast<bool>((1 << 5) & Analyzer<F>::value) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcAJykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3MhhvhBJDsP9/p9NhcTsxaABPABe0VeO1%2BBEwLESBiJEKhBExd2YbAR/2GxC8DjRGJx0WUxFQRCpdwhAHYrPyrpCrKd/kSSWTMBS3LzGKwZQAlTAEUgXeW0zAAOl1J2IwAU9NOjOZBFZYnZxE53O51MwkLcKoIEH1ht12rmxr%2Bgv%2BF39F0mjmQFzQDGGmFUiWIgYI6BAIC8wQIgLMAH1zQA3MReGUmQVcWWOi6A/MiwFin3lysS4mkpjkx2axUXZ3q5tsD1uo2AxEmghMlnoy2461cnn2x3O10GhQeuYXBioSOrRIEb35ysB2MNvAhsMRqMx2EJpOCVMZi7Z7x5gtFqEXACsArcF0LjuLpeFoqR34rSNOSV6yJJt7S1C4ADEGG9U0hzZUcQAuRIvAiWg9wtLFRxtCc7kdKCEQFIVqwAk4gOlUCaRbfDewZAczQwq08IYTZvUQ5DUPQ4dMI5cc7VwqFqL7H0twDIN0IPIkj1jeNE2TC8sxzB1Tm3Tc/W3AN3yhYszBfNT1IuCA9P0jT71fQEIUfITjPUrirWwviHQE6DewTa9cyM7cvWUgMyx/cU/xrQC63IykwJbABZYkoPbMK2AuOpBwIZZHKE2DzVs0dHUilgoPiuiHGShMWJo042JQtCQwynjbXlLKoucoTVO8/0xP3ARD2jaTTzk9MFJvIympOazNLcYt335UbmvUwypuG0ySwsqzrIDKqxxqycoWywTXMUjyAy8oafICkjty8VIjFDAwFAUDN7QpK48sS5K/KrF7aylBtHLlWKZQggB5b1iEwABHJMgZeIHQbwcHCPMAA2f6E1QO5iAbEgIC9f9v37RKGMygSAZKk4yo4yr4OiR0sFBeVDLMBG/qRlG0eIDHMca30pta0N2skzqT1k89eqvXapsGub80mw79JmqXlpGsbFr2/TVspzBqftWn6cZ6JmdZhEdv62b9oG47xSms7gmAS6mGu26%2BUhB7/re02/g%2Bb53Z%2BZFdguABJKViUYeoanxbZfhRD3vl%2Bd7gLzULKLiiCYPy80fYUUJl1UVd138kSWqD8SecjTqIlQTxhcN2XNx3YM01EYZHRLzwESgeWH0fBd4bximBP1kA3MwDuXd8/8zdI4LPtlDtfu9CSi5jRvaF9tOM6ztNM1/Cxq73WubfXKEF%2BbiBW9fduITprviDw3v%2B8H4jR/DiOw%2B97BVFYUkZTeL2I8/%2B/vaoLwGAOHSC8H%2BJxghoRCBcZMFx/4MAgMmdUyZNhekFBcIGSViAMAuBoUUAoRS/0uEwEuLBghEPoDAgBQD2oh0OP8C2F0TjENIahTAEEAH3SgYIeBghEGCGQYuFetw96BTOH/ShwdkjJmiCAgk/xwHBBlEwLwRBIIAJOOgdAMYq7w1gXgt6btLiSMEHiFRbASh4lgVQ8MNDfhpQuAAFWeESS%2BOcjLyMgdA2B3C1ScIIPwpcK4hGETQaqZYWCcEVj0f5O%2BrtRGXEscHVAERtBqwIDI0OtFcZO1cVNaByMdZEBZnMbxvC/ELgCZnIJVd0FhOwbg3y0T9FxO2A4px6TaH9l3MgNMNslCNAgGAMAS906BLXKrdWdxqAALZgbXMmNKytR6ddaILpU4jMqWMqEjDUAkOYCwthDVZkDxeos3pKyBlDLWYIzZbgqa0Bpgc9RmiZl90UvM2iXSll9NWcvUZe9blq3uRreGjiIwxBALAl5N8Tn526Wc/pVy/l4UJtgI57zTgcAWLQTgj5eB%2BA4FoUgqBOCjUsNYQMSwVh5iBDwUgBBNCYoWAAaxAI%2BQE2p%2BSPkfPyLgj4zBcAABwCvKGYaQ2KOCSF4CwCQGgNCkHxYS4lHBeAKBAHK%2BlBLMWkDgLAGAiAQBLAIMhNUFAIBoBJHQaIoRFScFUAKuGABaOGkgLjAGQCGKQ2ozC8EwPgQpeB4xtH4IIEQYh2BSBkIIRQKh1CatILoNoAB3VGiROA8CxTivFDKiWcD%2Bso41FxUBUAuHax1zrXXurfJIL1BkPAWvoFomlcxeAaq0AsCASBzWJEtWQU1Xae0gGAFIMwfA6DONVRACI2aIikOIJiNNvAZ3MDnX9ZJqSF2kHNWwQQf0GBYmzVgCIXhgBuDELQVV3BeBYBYIYYA4g434CBkAzMzxs2RjVsotYtKpHisJWhCIqM50eCwNmgceBpWXtIC%2B4gJclA3BvUYCBoBNULCoAYQ0AA1J4ia/o0g3cG4QohxARoI9GtQ2aE36FvSgaw1h9B4AiKqyACxkY1AvQ62EDtTBkssGYRV0HiABtfcx9oqT0guAYO4TwLR/CSemP0MoSQUhpAEGMVoSm8jpHk%2BYxTdgxMCC6KMaT4xRNWMMz0BRMwBgTBGE0Yz6nJiNG07MLgCwFCUtWBIDNHBcXyuzUqkt9qnUurdR66tOkIC4EICQM%2BgJXMtoZXMBYCBMBMCwDEDGpAWWSHZXEQE/JJAaEkKKuGsrHxwwSOKyVpBpVxe1HDLgcMBVxGFXDR8kheV5bhn5uNSqVVqrpYl7VeqO0Gvzco8glB%2B0NutWwTgDQWCZn5A6pg1sLrxG1FwbUhLfXRcE4GyNhGw0SGkKRpQ5G426BHcmpgqbL3ed8wq3gSq81GuUYW4tpbgtrathtrbGha07O7Q22LZhm2DZQ9qztQOe2TbNTDhtKADBGHiFwOVNB7nSMoFOuNS6Gjzsg3jlda6HAbq3YHXd%2B6H2YCPSes9F7aXXtvfewlj6xMvovTt1QH6iQbp/dm/9gHMTAbWISsDEHaXQdg5geDzPLZDbQ0wTD2HcOMHw7IUNxHTuyDI7GwlV2qNGBozxmw/6mOZdY8AzgHG4xcdo7x/j0R9vCcy3pqxEmpNZHU4ESzCmcjKZqGp/3mmCi%2B503oN3NRzNB4mFUfTtRbPOes7YWzMeU9TDDy5tzHnw0Pazb1zggWy0utBLet8cRNvbYMlFwpsX4sQ7bcl1L6XKDeeq7VivRXOVxH5PyQExXJDOraE9nNyrbADdbVqnV%2BrDXGrh9Nq1NqOALfLSwBQmYQyZg29KYYPq/UkADXoAjmvw3a6jedvXOgQCAlIDdu76b9CZp64q3N43zRFpLav9fm/t%2BfWGID%2BtPEcwQEQEcHSfdtaHQA3tKbBHAYDfRIRINeeINMHfAgNMVQZ1UdTHYgCdHHQlInAnWlAg1dFJUnSDcnHdPdAnVnGnY9U9Wgc9DdJnRDUXK9aGdnV9ONd9ZAT9PnYxX9XgQXfHEXUDQTCXXgKXFIGXYkOXI3SHRXZXTAHDPDSDY/IjU/Q7XXCja/Q3Ywe3U3Bjc3FjNcK3DYE8bjKwB3Z7ATITIw0zGoD3NPH3IoP3NoXIFTDIezYPDwpPXTOPMzVPLw2PDoAzRPTPZPRzOzL3CPMIlw8PVzRYZYTzBI8VR7fzQvDAl1NfDfK8X/Ikf/SLffRtOLMAxLJvNLAYTLKrKVEAMwCvEArlIrNHDQEA/kJrZ/Z7TgfrdVMorLEAQfL1SQYrAVSQfkYVQVAVNox/DgQEfPF/MfcA7zb1Do0fBLFDBYaDVIZwSQIAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_noexcept/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/is_noexcept.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_noexcept.test.hpp)
