<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::GetVariadicTypeSignature`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#get_variadic_type_signature">To Index</a></p>

## Description

`Functivore::GetVariadicTypeSignature` accepts a function-like type and returns its variadic type signature.

## Type Signature

```Haskell
GetVariadicTypeSignature
 :: template<typename...>
```

## Structure

```C++
template<typename...>
using GetVariadicTypeSignature = RESULT;
```

## Examples

We will extract the variadic type signature from several function-like type.

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }
inline int variadic_fun(int, int*...){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;
using VariadicAbominableFun = int(int, int*...) const;

/**** function pointers ****/
inline auto FunAddr { &fun };
inline auto VariadicFunAddr { &variadic_fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
    inline int variadic_fun(int, int*...) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

struct VariadicFO
{
    int operator()(int, int*...) const { return 0; }
};

/**** SupposedTypeSignature ****/
using SupposedTypeSignature = int(int, int*);
using SupposedVariadicTypeSignature = int(int, int*...);

/**** Tests ****/
static_assert(std::same_as<GetVariadicTypeSignature<decltype(fun)>, SupposedTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<AbominableFun>, SupposedTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<decltype(FunAddr)>, SupposedTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<decltype(&Tester::fun)>, SupposedTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<FO>, SupposedTypeSignature>);

static_assert(std::same_as<GetVariadicTypeSignature<decltype(variadic_fun)>, SupposedVariadicTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<VariadicAbominableFun>, SupposedVariadicTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<decltype(VariadicFunAddr)>, SupposedVariadicTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<decltype(&Tester::variadic_fun)>, SupposedVariadicTypeSignature>);
static_assert(std::same_as<GetVariadicTypeSignature<VariadicFO>, SupposedVariadicTypeSignature>);
```

## Implementation

The implementation of `GetVariadicTypeSignature` relies on the metafunction `TypicalGetVariadicTypeSignature`, which is implemented by dissecting the structure of the function-like type into parameter types and return type using the metafunction `Analyzer`.

```C++
template<typename...Args>
using GetVariadicTypeSignature = TypicalGetVariadicTypeSignature<Args...>::type;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcAMykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8dnuwuJ2YtAAngAvaKvHa/AiYFiJAxwi4mOJuAigu7MNio7D/YbELwOIEgiHRZTEVBEDF3FEAdisdKuqKsp3%2BcIRSMwKLRNMYrG5ACVMARSBc%2BdjMAA6GUnYjABS4/EEQnE4FiMnEClUqmYzCotzCggQOUKmVSuZKtkM/4XO0XLypIwXABuDTwTHwyAA%2BnzvalgMwCMtuairhcjSb5QpzZa4qy/kyWf92fDEUxkQaJQKIyKxdm2ObTYq4njTgSiQQSRrIVrKdS9QbI8XzWLY1bEwn7Q6ncBXe7PXgfX6A0GQzzw83o62Lu34ymk/O2acOenM7y9ZLc6LxZuBUXox2K2rSbXtQ27k2RVGzTK5hc0Axhh2TDbTt3HcE%2B27iB6vb69X9PBAwzccw23G8YzvZNrWZJc/hXNMuR5dE9zYbd8zQ6VZUPUtlVVKt1TBM9611S80SnW8pTbO8HwEZ88OtLt7U/Z0fz/IcALuICQODYhQziSdrxbGUaItGDEzghNU05DN9Q3LEcwAMQYI8VUratiIGC5Ei8CJaCHTTNXPMj5LcFTcXpRkpJTRDZLhLMsIuCzGJOY9CNPaIDRUzYOxAHS9IM5AjJInU%2BW81TSys18bOXE5Vy5RzFPQgBZeEVMw5LuTqAiQzUgiQq8tE0pYFSLhyysQxAEBfNc/zdP0wyiOM0jwuK9LIuwaLF2kuy1zMgtuSUgB5Dt%2BIARy8PB%2BJeCappm6KzAANhG6rUDuYgMxICA42s/CNOa2tvNGuqAsa4LDqKtwsGQWg%2BQgcwVuGtaNq24gdrjLrXz2%2BD/k%2BTYLgAFUxIcxAAcRFAA1AcvWBu4hGAsd%2BOhbZYSQuSkv5dCXLLNz1OJOHQdoCGCGh39B2QOHMAR3i8qYnsv13WlwMu4gItxar2IprjMB4pH5J%2B3qAW%2BEW3j%2BwEAElOXhRh6hqFHDnF0Xld%2BGT%2BsxyUDwVDtWL7EmyY4ym9Rp/mJyBkHRGJqGYaHKmTdA/iDREqUOZANqhf%2B5XFY%2BQFsFUVhEW5MWfa9mFbL%2BMw4mCW6vCwFDH1WRICBLXGle2C4qC8BgHHSF5g5OYIDJCC5girTOGAgUuxVLzZLQZC5%2BL4hgLg0Fl6WZU5C%2BCblS/7cn/3LyvBGrwRNnbevG%2BWZvW/jdvw/%2Bi4mAiVAWGCJf6AzrOc/ohXfl1oFl9X5h9MwJSs7N0uh53Gv70fBiE33g2KZOQ%2B15Ps/m/Ay%2Bq5L0fYzop8BAJJpwBuXbezdkil2iHnMOncGBF25EwLwRBnJZxOOgdAxArIomWuXOe8Eu7FyQSgp%2BXoP7oMwdgx6XMB7nxisAkO6dIGCChCgtgJQoRgJqDA1G%2B0CbPDhGzJitp7SEJ7oITeFcf43wAcMbBk9iDTzbvQ98oj4Hd1/lWGhnFB7SL/rRO%2BVZvoNxFFPFuyikywQYcLdOXD0gXFQBEbQmAHA8O9njAqI0FzMTtL3da0Q3o7SviPAgtdZFGInqYxR5jZ4qMktY9yFxSFDi8cI1RviJH%2BM2kQd6cxgmaLHgY%2BiESLAmKbjE0pcT6G/UYQDIQXhEi5EwOgO2iMHZB1gScfe9TGkpGaa02myMv6CHyTfCS3SGlNPQMko28M2l8QEuGb%2Bw8Clzg9oCQGAi3G/EmI4H0TAFBKEaBAYY6BqoKAFN6A5Bp9Y21mdTeZeU0Q3TunqagWdPpih6VMgZ/NcS7WVBmTiByjnGlOecy51y0S3P7rbY2jzHZohfivN%2B9AP64i%2BZMvpLT4WDPktgAF5Y5bAsOdEMFBAzkgAuWwK5JY3AwsNr89pBoXn3XIRg4gnzypYqUDiuZeL/kSV2SS0FJyKUQppVC%2Bl1tYX3PtgsllLjXl3AestTZwwBggHLly752KmUKtLISvGQL9mkuOeCqlkK6UMopvqp55kTrYExb03ldrEUEoScS01oqLXUt5lKm1sNcV/OeUq%2B62ifTaoxdyl1zSZluvxUa4V3qyVispX62lNyZWMuDcytEMzkVH3XqfLO0bdW8vjbmg1Hr4LJtpT68VlrJXWuzbaqt9rWVvJmeyzBOqeVxruQmwVtavX1tTb6q1WbSaDvbYi66Ya3mPXVYIzmdzvRRtLM6qZlb%2BUhprQmOtILx2NozQG1tQbd15rcN2x1W7sU7oeQKw1EkOALFoJwAArLwPwHAtCkFQJwNw1hrAXAUEsFYoZI48FIAQTQr6FgAGsQAfriFKOkH6P10i4B%2BswXAAAceHyhmGkO%2BjgkheAsAkBoDQpAf1/oAxwXgCgQA0dg7%2B19pA4CwBgIgEASwCC6VFBQCAaAER0GiKEAUnBVB4aWgAWiWpIC4wBkDBSkFKMwvBmmEBIHgM5bR%2BCCBEGIdgUgZCCEUCodQ7HSC6DaAAd02okTgPA32fu/XB/9nBhrIMEw4qgFwZPycU8p1TFx1NmAuBADwYn6BYPMHELgcxeBsa0AsCASBROJHE2QYTWWcsgGAFIMwfA6CCOYxACInmIhr2IKCFzvAavMDq8NJxLi2PQdE2wQQw14H1Zs1gCIXhgBuDELQZj3BeBYBYIYYA4gBvTXa3gF0zxPOYFUC45BaxoNQNI3%2BgyERNp1Y8FgTzKo8CUcm6QFbxBl5KBuDNowRdQDsYWFQAwCpIZPHs8NLEDXzPCEtqZ6Qhn5BKDUJ5uz%2BhZsoGA5YfQeAIjMcgAsda3DOBydOWGUwlhrBmHozd38WBkc7XaEt5wEBXBjFaKQQI3cZgDDaLkNIAhqc5BSCzhg0x%2BhlDJ%2BArooxPAtD0HYcntQRg9HpzzkXEu2cTAl9zjhZQFhgeWKsCQbmOBfto55hjgXZMKaUyptTkgNNRdwDp%2BLUHkswbg3MBYCBMCegGKTpDkhUMAE44h0kkBoSQxGlrUY/UtD3%2BhODkdIJRxLUolpcCWnhj3hGlofskNhr3S0dc2YY0xljtvXucZ4xlvjvnkHkEoPluLkm2CcAaCwF0dI5NMAfAYZ0XAPdSi4FKP92mcl6b0KD4z4gzOg8sxDmzugSuOaYM5ybmvtd0d4AxnzAnkH%2Bf18FpTt1Zvhfb53jQUWYvZbizguIZgbepY40Xiv0Qy8iZXkfgYW%2BjBt64DRmgd1oGUCqzZprDR%2BvQd/xazawcH%2By61ll6zBE80G2G1G1oHG3%2B2m1m3mz/XwH4hzhWwm27w22QC23%2B1208wOyO1BBOzWD/XO0u2gxuzu0wAeyQK/Dtz4A%2BwUC%2B0wB%2Bz%2ByuwHyBwkBB1kFH2sz/Qn2hyMFh1x3hwOxJ1RyTlzgxyx0EhxysEsHx0X0Jz01WxRz5xqBcAYHcCF3GFp20MV1mCZw5xqDlySBMPSEMMZw0M6Fl10Jp1F35wVylyVxl26DMMmEaCsOV0WDV1Mznw8yz04HX0N2b23zbw7y73N3wByRPySxSztwdydywBiFJ1Iwjyj3bz93Qw9zpDpDiH90kEUzaAXy80Y1sFzwv3S0LyQH40E1v2v2ICrzWFrxCxYAUBdGChdAiK5GGC0xiN030wB0H2BwBz4MhxAASCnxn1czDy10CPo28xLyrFQAC1UDaI6K6J6LkjkWi3vxyxPziHPwYKv32LiwaLOIGE6MaW9G6I929F6IIG9HWJBzK0/0q2q1q3/0ay%2BNa2cRAKuzAJ6z6ygMwCGxGzGwm2g0QKe1IKm0W3QNWxs3W02zhDwJYT214EIL/xILO1/AoN4CoL6VoKe3oPz3eyYE%2B2%2B1%2B0YH%2B04JM24LGPB34J0EmKEOMDhxsHEPgEkPRw2HBXkLxwJ2iCJzUNJ0cM0Mp20LMLpyKGl2MLyHSDMOZxqG8JFyqDFwFyaHsPVI6AEC1LVPl3cJ1KNK8JcKMJV3A3VySzmPn112CJeIuHaM6NdG2LhF2It1iIS3iLzzSySOd1SM1wyJADMHbziDiAwz91fw0HDLpHj0z0WPKOY1Y0SNIDdyWg00kH9zw0kDpEI3wzwzjLmLiAWMX04ASNe0100wTLLPKKqIWBu1SGcEkCAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/get_variadic_type_signature/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/get_variadic_type_signature.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/get_variadic_type_signature.test.hpp)
