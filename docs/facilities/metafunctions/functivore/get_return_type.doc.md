<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::GetReturnType`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#get_return_type">To Index</a></p>

## Description

`Functivore::GetReturnType` accepts a function-like type and returns its return type.

## Type Signature

```Haskell
GetReturnType
 :: template<typename...>
```

## Structure

```C++
template<typename...>
using GetReturnType = RESULT;
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
};

/**** SupposedReturnType ****/
using SupposedReturnType = int;

/**** Tests ****/
static_assert(std::same_as<GetReturnType<decltype(fun)>, SupposedReturnType>);
static_assert(std::same_as<GetReturnType<AbominableFun>, SupposedReturnType>);
static_assert(std::same_as<GetReturnType<decltype(FunAddr)>, SupposedReturnType>);
static_assert(std::same_as<GetReturnType<decltype(&Tester::fun)>, SupposedReturnType>);
static_assert(std::same_as<GetReturnType<FO>, SupposedReturnType>);
```

## Implementation

The implementation of `GetReturnType` relies on the metafunction `TypicalGetReturnType`, which is implemented by dissecting the structure of the function-like type into parameter types and return type using the metafunction `Analyzer`.

```C++
template<typename...Args>
using GetReturnType = TypicalGetReturnType<Args...>::type;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAHACspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIphJrozIeJgKF7tHp%2BcHX3vvJ8dnuwuJ2YtAAngAvaKvHa/AiYFhJAxwi4mADMbgIoLuzDYaOw/2GxC8DiBIIh0WUxFQRExdxRAHYrPSrmirKd/nCEUjMCj0bTGKweQAlTAEUgXfk4zAAOllJ2IwAUeIJBCJJOBYnJxEp1OpWMwaLcIoIEHlitl0rmyvZjP%2BF3tFy8aSMF2Izy8tAIAH1%2Bbyrhdjaz/iZmUH2adOYimMjDZLBQHReK42wLWalaj8adCcSCKTNZDtVSafrDcbTQqFBa5hc0Axhta/rbTg7Hc7gK73Z6ffq/QmCGHGyzUWy/hH4VG4bH9VKLgAxBgN7PqskFkAXJJeCK0PDIPNggs64t3Q3zvEMplDkcc8fcqfY%2BOnjMqtW5jX76InhibBtrjdbnd7lqh56se6KPtg54hpewZjly0YGny07xgAsvC85JkhbAXHUL7LAhmYnEur4rh%2B6KoSw87YaqOZ4SAIDfk%2Bpy/pu267m%2BQFFiBCFuOR4GQaGw4wScka3oh95YbOADyDZugAjl4eBui8ckKUpkFmAAbFJdGoHcxDRiQEBWoJoZZtRy75qRbhST%2B64sQB7EFoaWDIJ6%2BoQOYWmSTpekGcQRnGRBIYXgO/yfJsFwACpYjuYgAOKisaywMNFdJvNecGTmJAoSQujGEeZuapbFtAJQQSXEClJY2hYrbBO2vpov6jlWeBdFKR63r8kGAlXh83wDT8YWAgAkly8KMPUNTQtsvzhYN3y/BlE7ccmMpyhWDZOvVFxlRVVV0k1UUxaIpWJaKyWpdxaYWnidHdYJ4YAgt6X9Zc2CqKwiI8q9z0vbNQnmKiwSuV4WC8m4tarEkBDpgRw2XFQXgMA4GQvL9wTbiEFzBLmSMMBAuPirjmxWoyHYEMlFwaKyDIsk94UXEwESoCwwTM/QFz46jAjozC/zbS6Jws2zzBbpgs7I72uOE4IxOCKTNa8/2j2jn9EXc9NKS49EfMA6cmPBDyTBeEQc7Iyc6DoMQ54opp%2BN06Fb3bOuqA6zbZtsKUUKa2jM2HM%2BOZRc8cLEMGTYnC2hvY7jXPI7LYo4wr1a1sMttupTlXU7TUHh9BDOAr7AgXKgETaJgDh6wHZkvnO0k1XaDqx7p0R%2BUZCfywQiup7mwUU1TNPDo7Nr52rjNCF4SR5Jg6D7Vd/u/IL7YT1PqQz3PPZHbjTvq8HwxV78kyOMgXpMAoSiNBAwzoHRCiCqf6ZuHtF2VVdzkV25dzUMjgXiiv0%2BzxfgdfCxkRxHx3A/C%2BJpr633vmfQ0z9M7AMNMLVm7NxaSzytgP%2Bk8AEb1AtgUBKpowQLPlAq%2BBAb4gDvmwB%2BCDzpILfuiFyn9MAQEwZba2v9sK4LXoAxhJYMxELMiQk%2BZDojQMobA2h8D0SIMuoItwLD%2BQeU0pFEOAwQD424f/Ph%2BCQEDnAWI8%2BEiKFUJoZgOhciGEKNAtZaSGYcGryUPw2xBjVYcAWLQTg8ReB%2BA4FoUgqBOBuGsNYC4CglgrB5EDHgpACCaE8QsAA1iAeIqJpT0niPEekXB4hmC4LEWIXAuBmGkN4jgkheAsAkBoDQpB/GBOCRwXgCgQD1ISQEzxpA4CwBgIgEASwCAbjFBQCAaAER0GiKEQUnBVCxA0gAWg0pIC4wBkC7ikNKMwvAZ6EBIHgG%2BbR%2BCCBEGIdgUgZCCEUCodQXTSC6DaAAd30kkTgPAvE%2BL8YkoJnBJKmxGSXKgFx5lLJWWsjZFwtlmAuBADwkz6A21iXMXgnStALAgEgCZSQplkDGdi3FIBgBSDMHwOgoc2kQAiD8iI7NiCgnebwWlzB6WSTLhXTpcSJlsEEJJBgYIflYAiF4YAbgxC0DadwXgWAWCGGAOIe5%2BA3SowAG7PB%2BZgVQFdTZrDiTrCpgTtwRH0vSjwWAfmqjwDUqVpA1XEBZkoG4sqjBY1AF0hYVADCKgAGpPCeZJbEjKrnCFOhc6QJz5BKDUD8x5%2Bg5UoDCZYfQeAIhtMgAsXSNRJWLOvk1UwlhrBmCaXa4ghz1XpvaByjILgGDuE8C0fwtbpj9BiG0PI6QBBjFaMkVIHaGDNu9q2ytPNagjCaPW8Yw6ahdEaAO2YEwx1dr0JMWdRsZgDC4AsSJyxVgSE%2BRwXxDSfnNJBQs5Zqz1mbMkNs2FuB9lIrMKiTdqLElzAWAgTATAsAxCMqQVJkgMkAE5UT0kkBoSQZSNJ1PiBpQD%2BhOBVNIDUp90oNJcA0rEQDxSNLxEkHk4DGkj33Oaa09p8TX09P6ZiwZALTbkEoASxFMy2CcAaCwFV9JFlMBrAYF0XBAPSi4NKQJeyiClqOcGs54hLkRpudG%2B5uhSUvKYG8qV%2B7D2NN4M0/5wzTZAtPWC1Zrk5VQoE0JjQsL4U4sRXbVEZgUXkfdT0rFrNrPRHo%2BM1zhLjNGH41wepNBPS60oNS%2B5zKGgMpteF1l7KHBBu5ZNPlArFWYGFaK8Vkq4kyrlQqwJSqq1qslSJrVyAdVBv1T8o1JrQRmrWIEy11q4l2odZgJ1OX6oUc9UwH1fqA2MCDRGqTYbg1ybuYExTcajAJoLUmo1abf2ZrRpwHNlC82JosEWrTJay3za3VUKtzgICuCXW0QIa6W25F7TUE7Pb8gZDnRuqdnRF0Tu7XYA7o6pjncHcul72Q3tjoe62rdUTd2bvgwe75xHOAGfPTxkz/HBPCdvfgMTtnn2OfRe%2Bz937KD7sQ8hgT4GsmAfpPSVEEHJArLaJp35LTbBkbRd03pAyhkjI84x6ZsyOBsfBSwBQKrdwqsR9yYYuzUcHIk4N0NEhw2yFGzGkAqJSDKdUx8iHGnj1/No7mVAwLVB84F0LkX8E05wq8zZoGqIHNM4xS5hF7n8UW4GILqeXpheAa9KL70Bvw3kuC1SmldLItxOi6CNl5c4s2oS7y/lkW8upZFWK2gEqg3ZZdXV6VikCvqvuZq7VcJyuCCqJVlN1XasWtLY13gzW15tZdR1pzXWeuYH9YGm10vzmy5G1GsbOgleTeMOt5Nqb4AZphktjYMD81WEsJtoJ22sC7ae4d47r3G3oCB5du7nb19tqu/d7786V%2BfdGHvk/M6ehH8eyu8d/3ftfeKBd8H27ol7o11DppMPfcXH54Li4Hu0o3uKO966ONur62OX6Awv6FSBOIAZgAmqIqI2S4G/mGgSB9IGGRGX%2B9ObSHSEBf6IAVO2ykgEGsQkg9IxShSsQmBEOqIn%2BWmnAL67q%2B6Oy2BjB9OtuCwdqaQzgkgQAA)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/get_return_type/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/get_return_type.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/get_return_type.test.hpp)
