<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Find`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-find">To Index</a></p>

## Description

`Pagelivore::Find` accepts a list of predicates and returns a function.
When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
Find
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct Find
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<auto...>
    static constexpr std::make_signed_t<size_t> Page_v
    {RESULT};
};
```

## Examples

We will find the indices of `2` in list `0, 1, 2, 3` and `0, 1, 3`.

```C++
/**** IsTwo ****/
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Find<IsTwo>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);
```

## Implementation

`Pagelivore::Find` is implemented based on `Varybivore::KindredFind`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct Find
{
    template<auto...Variables>
    using Page = Varybivore::KindredFind<Variables...>
    ::template ProtoRail<Predicates...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQSXP6kAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzOFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GB5nBDEhXmhsLcyHG6CwVGxuJ%2BhxuADUWgiYngAG4kdggADS4XQxEw6AAYrzPgdAcw2AoUkxNgymSz2fyYQB2KyXYEETAsFIGTUkpheIgAOhN1Mu42IXgcNx5DD5AuFdtxquBNzdN012t1mBJnp1TD1cINxtNoOwN0hTAUChNRuU/Pwok1WLDrvdFqtBBu8dQRAAShjaGm3SZVTdZo5kBGBONMKoUsQbsHUDdWWIvJgVRYALRcUt3WEWFUD0FqoGXd0erX%2BwPw6fe/WG1Cx7ERgzR2MXYD8rWMAgpnET91eDJGG4Fugw0F3bPEXOoC9FuFbndsQQx0M40fOkdjjXzgMfSDJcbmFYhxjNC4M2tW17SFXkSTAiDU3VF0jzdP0FzhTDAMXEMjVXSMNxNeMBTwJN3kgydoKzHN80LYsu3dRjqOaStqwYWt60bZtW3bTsWOYtCLknUTmP8Kx/DuCAlhubtV3JEAQBYJgAGtMGRDJgAidBURJDIAC8NIIKixNE0sxzMqybjwKgOK4hsbigFczAANnMVzSMTQCUzcJCTLDJS228TAliWQTrKY/kCHWBgbg0QdhxpETItEuolAi6yLJuaLYrkvtRyS9CsuVaTwuKyd%2B0HRiqu/dVipw2dGqAtxmxXMM1yjD8jRfTBd3fUy3RPcJgHPQsrxvOiHwY59tz6t993ar8/1K6r6ouZq8JbfzSCbEChEwNA7V2tqTQAeQIBB4gPYEaJtXkE0ddBELwcCCF2g6jvQXaLqu8CludSz3U27CANnU6CI6ojuq88ifMG8s0UzW970fGqyxLCr0zY8j7M1bi9qIPiQphLGS2E1KYQkkwpJkuSFIIdAlJU9TNLwbSBT0uFDOMhGrIszKrNsvG6wbQWzOc003I82GKN8/zsSC/iwvFsTsty4g4oSwqqvWynJ3SzthaOhziFV0TJYI6W3Nl%2BG4U%2BgRnsCkBgo7FWyZKocNbigqh118cUv1m5DZsuyTfxsWPasiBzas2DHoQuFfuugGo9SpTmpR%2Bi6BJW3k1TwOg/dJWSbAMBYRvXtY/dcrC8p7Lq7E72bjMGFLHuu0E6dJPLpTz9G9EjOwc7Ka0bhPP3gLovB5d/jEoH/2B8Nhey2bquddWtPybKzLaqB7e1oDycQbnL1cOA/DCPXbrev6/cEeGs9HwmrPppz2bXz3brqTqoFVt/n8yVfj/BAfsQEwCbgAEkvR3wDFkUUYDgTANAf8QE/4z5NWHltJanViJxgTHDZMkE7pPUBoxE%2BENGTEDwEwGI9AbrFUfqNZQTBgACWvHKYgzI2QciUvHB0ic3BUJoXQye/dipDwwSPO82cnxuAnt/VMAD/5/lpCgr4SC6TYFUKwHUnYNFqPUYg9aEDIEKAACoAHcWwGI2lgi%2BLZIHEKRtaMxVjUDAhADcFIXg6G40UiAGIqBPDInDoYAKbhIETQri3VcAsVFALpAAWUwM0KgXgCQNAQacdBM4WoQwuMQYADCLhMJuCktJGSHDwJiaQuEbjrGQSUiwthJJCnFIBgAwxuwbjmPePubJgIKzkWRF1eIBAIAVKYOkzJWQSQaF2kEFuu1QSK1niTCuMSzDhV/sM5AozozjMmak6ZVSGjzMWSstZrt2EjkrlwHZFgOArFoJwfwvA/AcC0KQVAnA3DWGsOWNYGwBJgh4KQAgmhnkrFUgESQRoNAAA4zBmAAJyoqSEixFXBlTKmkK8jgkheAsAkBoBZnzvm/I4LwBQIAFmQq%2Bc80gcBYAwEQCANYBAfHvQoBANA2o6DxEiKwLYqhEWuW7K5SQNxgDICrFII0ZheBkSINQpmQR%2BCCBEGIdgUgZCCEUCodQjLSC6CCJY9EKROA8BeW8j5UKfmcDOoablNxUB2TFRKqVMq5U3AVa3CAHgBX0EbHiB5vAGVaBWBAJA/KUiCrILyuNCaQDACkGYPgdBNTgUoDEB1LJmBcOtbwAtTIzoxG0IdBl4L%2BULTOgwWgCIHVYBiF4YArVaC0FpdwXgWAVJGHECa/A/JqmsneA6ush1DRbHBeETUBLvm0DwDEdEXCPBYAdWiPAJKe2kDHcQIJSgHj9uAEuowUKVhUAMMU%2BkbxLFnSeJ88FmrhCiHEHql9hq1AOrNfoQwxgAWWH0Mu2lkAVioBSA0bt3ZyQV1MJYawZhKX7rVeOsD3Qq1ZBcHaKYfggihHCEMCoIwCjpEyAIXDehCjkYYPMYYVQMPVIEH0SYngOh6DsJh5jEwBiEYWCR2wPHKNBFmK0OjxGqgrAUMCzYEhbUcHeaQClvAqU3E9ZK6Vsr5XwoDbgQgJA26gnDRCi9KwrpMCwAkGSpBYWSFBEaVFoI8UaEkGYSQrkyX%2BFcqi/QnAiWkBJUZo0rkuCuURai7Frl/CSCSI51ySmHVUppXSkzjLo1spjRyl1hpyCUGTSG4VbBOAtBYKyZU3YmCdTPFwVFRouAIuVfgVVeB1X6tfTqiQ0hP1KG/Sa3QGaLVMCtT2%2BTinlOOo4M6rlho3UevFRpqro0at1YRU5IN8aQ2Ge2RGi9zLY2oGDfEXLfKDsbZGJGIwNWuALJoLQbNtKIB5pNaWotu6XsInLZWhwxbSC1r3PWxtzbMCtvbWILtP2%2B3/sHd84dmGx3du%2BZO5A06ftzrqA6pdK6mTrq2N8rdO7wX7sPZgY9UORq7avawhQt7MD3sfT9l92r31ddkF%2B413z%2Bt/vPfBqwQHMegesxBqDnAYOMzg4BiwSGVMoZa2h6znGmN%2BAgK4YTwQ7TicWKRooWRVfUYaBrgTCuGgsbaGxvIIm6hccaDxg3DHROm9yHhwTcw%2BP0bk6sdYsmHm%2BYU/ak1qn1Peou0t2r9WNBOT06qwzxnI3QtIOZyzlB5P%2BcC7Vlzyp/CotxaCVz7mYsJf95wZL9LdssvZZy7lx38tCpFcV4gLBvUsAUKyKsrJlvenGI1/Taq9CM7fbqlnBqevs50CAUEpBBvDZtT7sbiWnXZazO6tTjfm%2Bt/bz5LMgbTsJsM6CJYO20t7ZQNvkNVeT8jBbykFIyI2%2BouRB3ggyJVBSszXd66ub83hCZD997n2q0/b%2B0EABybSHWBzbQ7XB13UhwHVx17Vejh3HRNSRxR13TRwXV4Ex1XQRBx03WoQJ14CJ3SBJy1DJ3PUP0pxvTvQfUYAZ1kCZwHzazZx/THy5wAwQz5xA3gHA0gyyG7W2EUh50Q2Q3iFQwFyk0t0V2w3cDNydwIzKDdy1xo11zI311dwkw4wkONyExkI0J6G4xd3kPUJE20Mdw4xtzUM1ykxk11VGz90pU4GX2lSbxb1bHX2TE30jwMzDX31SyjTM0wAsxGGswJRTxADRSNFBFBH8H8Bc2uw0EiOVDCwL3sOpVsBS1jzChsxAEkH8AcxxWVDJURUkAxS4GRTch91BDsJUyL18LjwJSVWSOqNSIyJWH3QyGcEkCAA)$Done$

## Links

- [source code](../../../../conceptrodon/pagelivore/find.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/find.test.hpp)
