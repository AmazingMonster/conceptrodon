<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsVariadic`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_variadic">To Index</a></p>

## Description

`Functivore::IsVariadic` accepts a function-like type. It returns true if the type has a variadic parameter list and returns false if otherwise.

## Type Signature

```Haskell
IsVariadic
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsVariadic
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*...);

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*...) { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*...) { return 0; }
};

/**** Tests ****/
static_assert(! IsVariadic<decltype(fun)>::value);
static_assert(IsVariadic<AbominableFun>::value);
static_assert(! IsVariadic<decltype(FunAddr)>::value);
static_assert(IsVariadic<decltype(&Tester::fun)>::value);
static_assert(IsVariadic<FO>::value);
```

## Implementation

The implementation of `IsVariadic` relies on studying the parameters of the function-like type using the metafunction `Analyzer`.

```C++
template <typename F>
struct IsVariadic
{
    static constexpr bool value
    { static_cast<bool>((1 << 4) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsVariadic_v
{ static_cast<bool>((1 << 4) & Analyzer<F>::value) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcAJykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3MhhvhBJDsP9/p9NhcTsxaABPABe0VeO1%2BBEwLESBiJEKhBExd2YbAR/2GxC8DjRGJx0WUxFQRCpdwhAHYrPyrpCrKd/kSSWTMBS3LzGKwZQAlTAEUgXeW0zAAOl1J2IwAU9NOjOZBFZYnZxE53O51MwkLcKoIEH1ht12rmxr%2Bgv%2BF39F0mjmQFzQDGGmFUiWIgYI6BAIC8wQIgLMAH1zQA3MReGUmQVcWWOi6A/MiwFin3lysS4mkpjkx2axUXZ3q5tsD1uo2AxEmghMlnoy2461cnn2x3O10GhQe9Uer29pG%2B04B2MNvAhsMRqMx2EJpOCVMZi7Z7x5gtFqEXSQCtwXQuO4ul4WilfVpGnSX1olN%2B1ahcABiDDeqaQ5sqOIAXIkXgRLQW4Wlio42hOdyOiBCICkKn7it%2BdbSv%2BNItphy79oO5rDsh0QYQwmzetBsHwYhVFWqhdroVCpF9j6lbrkGiE7kSe6xvGibJieWY5g6a4BvmfHrgGT5QsWZj3n6in%2BhAGmaeuyluC%2BEIAKw8bpimsSh44cQ6XGgb2CbnrmOmKV6sn%2BmW77im%2BFZficP6EZSAEtgAssSIHtkFbAXHUFHLDZPHgZRkE0VCoUsCB0UDmacUJvRZEnIxcEISGFkclZ8qOml3Ergp/oCduAi7tGomHhJ6ZSReznyc5enXg%2BT78gZbmKdpw1mfphkmCZPW6aVY62hVqVhXZ2AOdJM3%2Bq5Jzrh5Pl4dtAZeKkRihgYCgKBm9oUlcmWxcQNk1t5Nb4VKDY2XKkUykBADy3r3QAjkm90vADQPPNh5gAGw/QmqB3MQDYkBAS44QyWUQSOKVuD9DEwUVLHJcQjpYKC8raWY0PfbD8OI8QyNLjx3XDfVoaNcJzUHuJx7tWe63DUzB2aQNQ2CyNG2KRNN5PtNY2zYTxOYKT9rk5T1PRLT9MImtnWy5tXVPb565HcEwCnUw52XXykI3Tje1Vp5fwfN8zs/MiuwXAAklKxKMPUNT4tsvwoi73y/LWr2NoFxFRUBYHo%2BaHsKAAag0eBMPgphebVG7Bqz4bszGESoJ4vM66L8k51uaaiMMjpF54CJQJLD6SHMEIU0hVoYVrICOZgbe7Y9uGO35BFvbKHZfd6QmRs19e0J7yep%2BnVeZjVlfINX5sEHXxe0I3EDN7eA8d3N3f2b30kDwb%2B3ByHQfu9gqisKSMpvG7Ifv7f7tUF4DAOOkF4X8TjBAQiEC4yYLi/wYBAZM6pkybC9IKC490CDLAYBcDQooBQim/pcJgRcWDBAIfQKBf8AGNQDocf4xsTonEIcQ%2BCmAgJ/2uhAwQsDBDwMEJsRcDsP7bDIf/f2yRkzRCAQSf4oDggyiYF4IgwE/4nHQOgGMFcobQJwfwp2lxRGCDxAotgJQ8TQIoeGKhvxEoXAACrPCJETLOzlpHgMgdAzhap2EEF4bqa%2BFgUGqnQZg7BHkvLDwEaiUx/tUARG0IrAgEjA5owosBX6jjhqQLhurIgdM5juO4V4xc2F/FoOIBgrBFYtGhO0Wcd2tjhgJOof2Tcm9zZKEaBAMAYBF4p2IGnDOCslZ3GoH/Bm2tcwozRs0tMrTogukTj0vpW5HT0NQEQ5gTCWErTGf3B29VpnnVmR0rp8zl79KhCTWgZNNnKNUaMy%2BF4JlNODPstpcyl69JXqYc5itLnKyhnU%2BxCZoF3L7o8k4eyZntJOR8s52NfoX1BQ7DgCxaCcCMrwPwHAtCkFQJwAylhrCBiWCsPMQIeCkAIJoZFCwADWIAjKAm1PyIyRl%2BRcCMmYLgAAOLl5QzDSFRRwSQvAWASA0BoUgmLsW4o4LwBQIAJWUqxci0gcBYAwEQCAJYBBYJqgoBANAJI6DRFCIqTgqguWQwALSQzvMAZAIYpDajMLwTA%2BBsl4HjG0fgggRBiHYFIGQghFAqHUMq0gug2gAHcEaJE4DwFFaKMVUpxZwb68jdUXFQFQC4FrrW2ouPax1khnUXAgB4I19A1FkrmLwJVWgFgQCQIaxIxqyD6pbW2kAwApBmD4HQex8qIARBTREYhxBMTxt4GO5gE7voxLiVO0ghq2CCG%2BgwLEKasARC8MANwYhaDyu4LwLALBDDAHEOG/A90AGZmeCmyMit5FrHJWIwV2KEIRARhOjwWAU0DjwKK49pA73ECLkoG4Z6jBgNAMqhYVADCGiTk8KN30aRLp9cIUQ4hA2YZDWoFNkb9DnpQNYaw%2Bg8ARHlZABYcMahHqtbCa2pgCWWDMNK0DvSsDUeRu0OJ6QXAMHcJ4Fo/ghPTH6GUJIKQ0gCDGK0aTeR0gSeMVJuw/GBBdFGCJ8YfGzFaZ6DImYAwJgjCaDphTkxGgqdmFwBYChiWrAkImjg6LJUpplbmy1Nq7UOsfCWtSEBcCEBIO3QEdm61UrmAsBAmB04DF43SyQjK4iAn5JIDQkh%2BWQ3FUZSGCRBXCtIKK8L2pIZcEhlyuIvLIZGUkOy1LkN3PhplXKhVFKouqo1U2rVGb5HkEoJ2qtpq2CcAaCwTM/IrVMDNideI2ouDamxW6kLXG9CYb9Th6QeGlAEfDboPtMamBxuPS5tzUreAyvTTq%2BRWac15p87N0283FsaDLRW1tVawtmFrR1uDqrm2rM%2B9EAbBqgddtBOe%2BIXAJU0EueIygI7w0zoaJO4DKO50LocEuldvt12bqvZgHde6D1HvJae89l7sXXv43eo9y3VBPqJEut9KbP3fsxL%2BtY2KANAfJaB8DmBIOU5Np1hDTAkMobQ4wDDshNsBu27IfDYbsUHeI0YUjrGbCfp47RxI9HOCMbjMxsjbGOPRC4/emjemaiCeE1kBTgQjOSZyDJmo8nXdKYKM71Teh1P6bMx7iYVQNO1DMzZkzthA8Wb9%2BHn3tn7OOYDWd5NLXOBefzXeSHc24gLaW2W4L2SwsRb%2Bw2mLcWsAxF44VkVIBAS58y8yuI/J%2BSAiy5IW1bQLuptlbYdr9aVVqs1dq3VoOhsmrNRwcbBaWAKEzCGTM83pTDFde6kgnr1ty%2BwwroN8hdsq50HX0gR2TsJv0Em5r0q019fNNm3NM%2B58L6X29YY73wdffMICQEv2B%2BNsB5WkHDtd/AYefRIRINMRfOINMZfAgNMVQW1fteHYgIdJHbFDHNHcldA%2BdWJbHYDXHNdDdNHanInXdfdWgQ9JdCnaDbnE9PAG9RwOnB9RnZAZ9FnfRd9XgdnVHLnf9XpPnXgAXFIIXYkEXDXf7cXSXTAVDdDYDDbbfCQRXYNffQjI/AwDXFjKwSwCjKjeAPXA3DYA8DQ6wdjS7TjT1K3Xjf3W3CAVwIPUgJ3IoF3NoXIWTDIGPZwt3ZTePSPKwzoaPB3P3EPAPKYbwtTfw0TUzEIxw33OzRYZYJzWIwVc7DzdPeAu8WfefM8Z/IkV/ILNfatcLH/KLcveLKvFzIrUVMwXPL/FlTLGHDQL/fkSrS/S7TgNrRVYo0gJLSGZ1SQLLLlSQfkXlblLlJo8/DgQEVPK/XvX/FzF1FonvSLODBYUDVIZwSQIAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_variadic/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/is_variadic.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_variadic.test.hpp)
