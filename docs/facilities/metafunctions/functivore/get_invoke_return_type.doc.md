<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::GetReturnType`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#get_invoke_return_type">To Index</a></p>

## Description

`Functivore::GetInvokeReturnType` accepts a function-like type and returns a metafunction.
When invoked by a list of argument types, the function returns the return type of the function-like type called by objects of these argument types.

## Type Signature

```Haskell
GetInvokeReturnType
 :: template<typename...>
 :: template<typename...>
```

## Structure

```C++
template<typename...>
struct GetInvokeReturnType
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will extract the return type from several function-like type.

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
    double operator()(int, int*, int**) const { return 0; }
};

/**** SupposedReturnType ****/
using SupposedReturnType = int;

/**** Tests ****/
static_assert(std::same_as<GetInvokeReturnType<decltype(fun)>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<AbominableFun>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(FunAddr)>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::fun)>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*, int**>, double>);
```

## Implementation

```C++
template<typename Fn>
struct GetInvokeReturnType
{
    template<typename...Args>
    using Mold = std::invoke_result_t<GetVariadicTypeSignature<Fn>, Args...>;
};

template<typename Fn>
requires std::is_class_v<Fn>
struct GetInvokeReturnType<Fn>
{
    template<typename...Args>
    using Mold = std::invoke_result_t<Fn, Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcAOykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3AQAJ53AD6BGITEICkh2H%2B/0%2BmwuJ2YtBhAC9oq8dr8CJgWIkDBSIVDYXdmGx0f9hsQvA5cfiidFlMRUEQGZgIXErHErpCrKd/hSqTThZDoXDGKxhQAlTAEUgXIVMzAAOkNJ2IwDRgIxpzZHIIXLEPOIfIFAuVio1BAgxtNhv1cxZ0tF/wuQYuXlSRguADcGngmPhkIjlfDUsBmARlgrAVcLm6PSaFN7fYCpX9xZLMadZdSmLTFbrVdnNdq62xvZ6zRaTlbOXi7cSHfzBS6oTm297tQW/SXi8GQ2HgJHo7G8PGhUm8Cnq%2Bm6VmR3mxxcJ0XMaWj9KK5SqzX6cq9Q2tTqb6rW3nJ12bT2CX3HYO7q7NbmvUNOYLjQBhhknEwA1OGdQ2Ceco2IGM4wTBFk1TLdIR3f9RyAst/QlU8/nPOVqwzJVGXrN0m0fFsjRfc1WSRa1bU/XkB2dX9h2wvdDXHICQIEcCGP9adg1g8MEKQ5cUMwNcNzTYgMyw90cP1PifTwksCOLGUL3lWsaOFAAxBhXyY7tuT7EALkSLwIloZcWPtb8OMwRUTPREUxW08sTkrfTrwotgLg84TO3M99LOidyGE2SdrNs%2BzHI/Zz2KFGLPMg7zNN0kiKQMoLhQAWUpEzqMKi46nZBx0zM6rIt7aKoRKlgTMqiL0xAEA4rChK7Ic5AnK/NKhzcFrQuwLzIJ8s8/L00iCpVYKjIAeUnRSAEcvDwRSXk27bdqmswADZVq61A7mRIhiAgQtsstCKhqatxVvimz%2BuSqLiEVLBQSFCBzFOlbzsu6sSFuwtJqy6aco%2BXYLgAFThZcxAAcU1AA1Rc4yRu4hHXdDFNJbZyXm/LAqW4zTLCt9EeR0RaHRggscQpdkFxzB8fk2qRNnOCHzubcnu%2BqEJq6yS2ZkuTCbco8Tx0uHLiZlmpPZ5UuZl4nDlyy9ZfIynn1NSdxPnZXseXDmNc3InMLpxIUcZzHzbVvGCetvXVPRLr0sIrFvn9n4/cuABJOVKUYeoai135sQD75fh1gL9dvCbGPqi4meDhgI1QABrTA3WWBgOePUSg38haKb1Q320DMS5wuIrPHQIXhnQLrghz/P4V2rxaAIRFFTN1mcfVt2FL1ibtU9hjffl3yK/J5P61T059p254LjbjuFHhUEmAUXeIwymnHsz7O84LzUi5L0XqY7aHoODRe9ebA06KNsKYIbpvaBb23t4gE7pfHuzw%2B4DwIDFaePF9QsjnjNIiZw46B0VtsC42BVCsGpMKN4QdkEk18uYYEDBQReHBIqUCqxEgEFrrNbEFwqBeBITUF4uDTjBAciEC4wQbSMIYBAHh2oeGbF9KKC4ikFIMAuBoSUIoJR0PhkwCIqAWDBCUfQBhTCHDpFYWSf4JtcTKNUcweymAjJMKFjwgRgghGCBEQJMCkDfaoJxHw7RAgbKoB4dEXRBD2EME4cKJgXgiAhSYScdA6BiBeQhCdPhcjYZIMuMkbx0TQlsBKCSNxLDo5p2YgjZ4FJvoiTrkGDhwRhQ8M0fwwR3C7HAVAsMGJEii7SNkTDfCiT6HZPSBcVAERtCYAcL47WD106vRKU/Mpgg%2Bmg2urdax95hENMEjaLK4jr7ECkTIosCSpkXHQEsUxszohgxunMRZtiCCbCudsFZjjmmbO2e00snTnFJLQUILwiRciYHQIXLZHNcmnAMV8n5KQ/kAuLsqSxggunwwKcMEZvxJiOHjAfJQjQICAIUKqeEB8h6aizl3K%2Bkjb5uF%2Bv3ZU1AmGQy6r/dAipanCPRNqMFvz/lPNvtgO6jFqzSQxdEd0OK8UEqhOfElULyUnCMWo0x5j770ubkymxdTrmssqt8jlUqhw8s0qigVh8hXYoIO3EAuK2D4rNG4CVl8dWcQpUMqldwIAKoiVEulIAGUqqWXYjV7KIWcrJbq3lD1%2BXoqNVikVlqxU2qJRffO9q9aUv%2BoDRFRSup8M9d6qEzK/XmjZVqwNSb0ShvCuGq1mLhWmq6ha2SsbbWJq5aNV65olV/x9bc/1RalBBpviG/VkdDVVpNWautVrCUEGJXa5tDrW3YHbYy3NqrhG3J6tgbUhz%2Bqyz1YRDgCxaCcAAKy8D8BwLQpBUCcDcNYawW8lgrAVECHgpACCaH3QsXOIAj2An1HEI9R64hcCPWYLgAAOMD5QzDSEPRwSQvAWASA0BoUgZ6L1Xo4LwBQIAUNvvPfu0gcBYAwEQCAJYBBbJagoBANAVI6DRFCKqTgqgwPHQALTHUkBcYAyBBpSH1GYXgfzCAkDwO3No/BBAiDEOwKQMhBCKBUOofDpBdBtAAO7IkSJwHgB7j2nvfZezgK0QmUb6VQC4LH2Oce47xi4/GzAXAgB4Oj9BolEK4HMXgeGtALAgEgWj9s3PkEoIF%2BjMRgBSDMHwOgRTsMQAiIZiIajiAwh07wZLzBUsrQGUMvDL7aNsEECtAJaWVNYAiF4YAbgxC0Gw9wXgWAWCGGAOIcrG9tERmeIZzAqghkhLWC%2B7xsGL0OQiMiVLHgsCGaRHgRDDXSBdeIMopQNxmtGE4aAfDCwqAGFNBjJ46mVqMnS/J4QDNZPSEk/IJQahDNqf0C1lAt7LD6DwBEbDkAFgXRYZwNjbdMKmEsNYMw6GluISwJ9267Q8vpBcAwdwngWj%2BAR9MfoZQkgpDSAIMYrRMd5HSGjzJGO7Cw4EF0UYSPxgw/cbUEYPQKkzAGBMenuO9CTEaET2YnnFjLFWBIPTHAT2ocMxhyzrGONcZ43xyQAmnO4BE%2B559XnX3vrmAsBAmBYwDGh1%2ByQv6ACcgI4iSA0JIaDx1kNHuOgb/QnB4OkEQ4CLg%2BpjpcGOmBg3kHjpHskMBo3x0RcqYw1hnDqvtuEZI/5sjpmQkhZoyooLDGmMcAaCwCMcQ2NMBAgYcMXADf6hdxe4T10xN6Gu9J8QcnruKbuyp3Q0XNNMG0w1wXwu0O8AwyZijITzPi%2Bs1x/eeeC9F6cy5pPSvARmBVz5gj0ewvBeowvgYQ/IsG64Chmg/cfGUESypzLDQysvoP9l3LDhTuFYjiVgkhmKtVZq7QOrp2mstbaxe/AilOvdZU71/rFJTvDaGZjYTYwhTZrAXqzbzYvpLYraYBrav5wRq58B7YKAHaYBHYnYLYV4XYSBXayC17KYXoN6PZGDPbA6vZjZQ7fbUI6J/YA6ZhA5WCWCg6d7g5ibdZfY041Dw6I5ZB46BCM7o45BY41Bs5tC5DY4MBc7M5cGdCs5U546k604U4M5FBCEs7dBiG2D07SFlALAKAPr8486wbt6i6cD96S454tb2Yj76gaDy74DXSxLO4z5q4a5a5YAxDQ6wYO5O4F5m7/oG5xBxCAjm6SCcZtAd5GaYa2Bh6z5%2BZR5IDkaUbx7L7ECMZsCcBp42YsAKARiDQRj576jyjDBCaOGibiZnaV6XZnYEH3YgCAikBN4t66Z25C4GbB7Gax42ioAWaqA5F5EFFFElE2jOaJ7hbOGAiuER7z7jGL6hZzEDD5E/LwiFEG7wgjHwj9FXaxY74JZJYpZH4ZaHE5aDLn4LaX7Fala36YCVbVa1b1Yvov4bbgGNYdaOBdb1bF59bIADYAGCBVBAHvYgFgEzaIRQG8AwEQrwEbaIER67ZMD7aHbHaMCnbYEya4G1G3aEE6ANEkHGAvY2CUHwDUG/YbDbyMEg5g7RAQ4cHQ5KHcEQCuBaECFqHE7CEE444KEcmSG6Hs5VBk506aHckTACnKE6GCHskaGU58Hs4Slsnc76GGGyZt4dHobmHbEXC5H5GRjDGkRNIQAK5OEebTG%2BbuHa5eGC6%2BEgBmAF6AiAgAZm4b4aD2lxAe5B7qkxHYa4ZuGkB67HQCaSDm5gaSBxCQbgZgZultGAhqmd6cDea%2BmwaCYelxkxHxELBLapDOCSBAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/get_invoke_return_type/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/get_invoke_return_type.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/get_invoke_return_type.test.hpp)
