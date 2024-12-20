<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllConfess`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-all-confess">To Index</a></p>

## Description

`Varybivore::AllConfess` accepts a callable predicate and a list of elements.
It returns true if the predicate evaluates to `true` for the value result of every element and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...&&Pred(Es::value))</code></pre>

## Structure

```C++
template<auto, typename...>
concept AllConfess = REQUIREMENT;
```

## Examples

`AllConfess` turns a fold expression of a callable predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&Pred_0(***))` and `(...&&Pred_0(***)) && (...&&Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return true;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return true;};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...&&Pred_0(Args::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...&&Pred_0(Args::value)) && (...&&Pred_1(Args::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAgmgM45iqqcSHTF5Ex6cXVxM/gAIocTEkrElgRBvkQAHQIpYmADsFlOBHWDEOBGIXkwQKsyOBBPuD1JewOfzO5y41wOd0ez1e70%2BsNQVIutKBoPBkOhbIRcKRqPRmOxuPx/kJxKlpPJN0OADUmABPOn7BkPAiYFipAzaoFuNmHACSQOwpPGuIcStVctRpMOTsOs0cyEOTO1LK%2BP3ZADcxHiwaizUSSY8UTKrBHHhT9ocqF4sTdNdrdfrJW4CCrUoxWJhBQ9iMAFObSacAI5ePCnBSHCCC8wANmbJ2pGggRZLIBAAe8mCWSMZAmZH0OMVQngTSYgwrRmAxxCxVDEShJYZjWp1eqYBv8WZzebYheLpf8FselertYbCObrf%2Bl07p57fbxg7BZhbX/rja/D%2BpLhn27XtAwHIcnhHL0xwnKdEwYWcUXnRcsRxPF12JTc4yOAAVTBxnVW5yW2Q5sGIYgSEtZo3XOJgFCUVpqCTQ1lRVQ0uDLc9ZyRKUOBWWhOCSXg/A4LRSFQTg3GsawXTWDZME/fweFIAhND4lYAGsQCSJs4QADibKQkmRJtJAATn8EyzH8fROEkXgWAkDQghEsSJI4XgFBAIJVNEvjSDgWAYEQEA1gIVIfnISg0F1Oh4kifNOFUAyAFpTMOYBkHdKQ4TMXgzkIEg8HQPR%2BEEEQxHYKQZEERQVHUPzSF0LhSAAd2IJhUk4Hh%2BME4S1PEzgAHkfgighDlQKhDmSps0skDKssOHKzHrDxYvoT5zCUpZeF8rQVggJAYtSOKyAoCBjtOkBgCkMw%2BDobViC8iAYgGmJwhaFVut4d7mGIFUhpibRMAcb7SBithBCGhhaC%2BxqsBiLxgCNWhaC87heCwFhDGAcR4ZrEHHD9fCBreEGfi2ZTwm1ATGtoPAYg6/6PCwAacTwRyMdIYniAnJRgR1HH6aMNSVioAwS0VPBMFaobcxE5SyuEURxGqpW6rUAbmv0HGUGkyx9AZrzIBWVBUgadGUvGdBuVMSxrDMNyeeIYqSZN7pCeyFwGHcTwOj0UJwiGSoRhaoosgEKY/DDjII4YeZhgSFq7E9gQ%2BkmP38mTupU8aCYBiDhZQ9sfOo70WZWgTkOk5WBQ5M2CReo4ITSFc3h3Om1L0sy7LJFy%2BtcEKzbrK4HaVNFlYEEwJgsASWdSC0yR/DhCzkUkDRJDMSQm2cnSzNsjh7NIRz/DMOF/CbZE9P8PSkiSLhLLMvTW4G9zPO88e/IO4LDtC0bIvOpdDaCU2BJS7vNZABgjBLTMnCLgcIxIFSIC7EqLUlYVVVtIdWShNaNV0HddqnVvpNxbm3QaHARrhR%2BBNKaM05oeigcAGBcCEGrVQOteIikzBjz2v5X%2BQD4hRQuuwk6G0UCMK4GZLgQQaC0Ees9V6jVfqfTBso/6gNgagy5hDRgBBoawwGgjJGKM0ZgyxkLLYYl8CnAcHgYm6NEGqHJtqMG1M6gDXpozT6LNLG7RdpzZSPM%2BaYAFtjIwwtQBfz4BLBQUsZZy0YGDdBKsqpYNkBrBqYl8E6xFnbKwBtPHG3nmbC2nArYEBtiCPJDsnbxBQW7eeKdbHOAgK4MuLVA7lETnocODR2lpFjg0Kuixs49DTqXTO0cPbNLznMQu3Tk4TLyFMiuBcunV0bqsdYDdR4H1Ia/TgndZrpUgTjZh8CrgQEHsgxSo9doT1IFPGeIx55aWkUEWmR8T5JDhOZJIZkzAAq/HpB%2BpkX6NTfrYD%2BvDv7wF/mFMaQiBHEBAVsFoLB0osAUH6d0fpJFwgzOMfK%2BBkHFVKrIDBqSaryBwZknQAQ2odS6hjEh/UIXDX/uNSa01MXYtxfiwl40IBrVEZwra/geGiwCkdERp0kWyrETi1IqRzh4rMucQV5xVBgtkfIygiixJqLhspI1GjCZgx0VDGGcMrGYERsjMQpiubmPCb40g1jPb2NJk45AFNXGCHcXTBmTMVQ%2BLZv4sGQSMghMFuE8IkT9rRKYJLaWst5ZJIpSkiQaTaq0q1gyxhet7YFKNvAU25tsjo22NbIt%2BSLCO3bs7V2RTa45xmd7X2yyA4%2B2GcXXp2R%2Bn9tKPMjZozc7pzaJM8ubaGgTt7UnEu/R%2BmrPnZsuu2yqqsvBW5Q52r5pYpxYcNVBLdz4SFdckgtzJVf0ntPWelAm5fICGfUF1kzDvq4HpDQTZ/nbvbpwd%2BPkHmL2Xg/W%2Bm9/BJG/dZEyB9/Bsp3R5T%2B%2B0m55T/eQ%2B5N7ubxEyM4SQQA%3D%3D)

By turning `(...&&Pred_0(***))` and `(...&&Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept AllConfess = (...&&Predicate(Elements::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBAKykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJn8biYXiId2UxEw%2BFEYNIdwIAE8UoxWJgAHRE7CvRgEBTQ7AgtAMbYpAh3K60WgeBhUTAKBR3aEAETuECJBPMADYRUiUXg0ZgICTwWSFCAQAA3MReTArFbQqzXEF/AHnXXHO4AFQ55K%2BBt%2B%2BpOQMN93F6AA%2BhoLYcgTTZphVCliHc4QiHc7uf4%2BSZElZEjyIP7UILNQB2CzIgibBiY4hqrUmeM8rM6q325FOriu/bugSe72%2BmOIouOku87nhsNRmNx7NJzAp4hpggZzBZnN54EFw53ABqTCxpaBYIhHwHMJrD0pINmGYcE6nII7ILu%2B7usw%2BkruHrBVb98NQdxV3kw3MTK6H/m1wOfr7tY6oXjT3xBc5eBdoTcbFcWYNhBSuYhgApfwqWuZEAEcvDwZEuSZFkBHZTlgMDIJGWghRBVXa4zy9H07hiVBPDub8GAgBNO27NMqDEJRB1zfNQXBQCoRhUC8QgokoJgkioMwZDUI5RlmVZbDYLcPCMREoiiUpbkzFFTSZMwtkOQUwMuGUwjiLg6kK3PCiqJouiGI7ZNU3TTMX2zTiRxuI1TVmGc1yaRxkEdJhOXiAhqB/YDJyxYCuFXOCGM1F8ODWWhOESXg/A4LRSFQTg3GsaxDw2LZ73MfweFIAhNCStYAGsQESYUCQADmFKREnjYVJAATn8DqzH8fROEkXgWAkDQggyrKco4XgFSCSrMqS0g4FgGBEBADYCBSeFyEoNBnjoeJInxThVBagBaTq7mAZBkDuKQCTMXgJSIYg8HQPR%2BEEEQxHYKQZEERQVHURbSF0IyAHdiCYFJOB4ZLUvSqrss4AB5eFtoZVAqDuM7hUuyRrtu%2B7JEe/kPAO%2BhfVKrgVl4BatDWCAkH2lJDrICgIFZ9mQGAKQzD4OgwWIBUIBiZGYnCZosTh3hJeYYgsVRmJtDqBbyv2t4CFRhhaBl0GsBiLxgFhZkFW4XgsBYQxgHEA2pPqJUOWRr06nhHZyvCMEUtB2g8BiaHFY8LBkb7PBRot0gneIKilB5cEbb9owqrWKgDBg8c8EwCHUbA2WAeEURxH%2Br75CUNRkfB/QbZQfLLH0f2FUgNZUHpLJzfO2Z0F5UxLGsMwpujt6sCbhiuh6LIXAYdxPHaPRQgWcpKj0QpMgEKY/CM1feiGJfRiM2p6gEfpJlnvID%2B6NWGjmXeRgSA%2B5g3vQjxaW%2BlnvtYFCK7YJARjg0tIJNXg01cYXSujdO6D0zD8lwIQEgGkyp0wqinNYCBMBMCwAkMedVJD%2BAJD1eMkgNCSDMJIYU40GpdUGhwYapBRr%2BDMASfwwp4xNX8E1RIiQuC9S6k1QByNpqzRAPNFOy01rMw2hjHanNuZU2OmwU6YDCbIAMEYe6XUCRcAJFlF6JB3qfVkD9Yu0hS5AwrqDXQAsoYw1ln/ABQCUYcHRlteEdxsagPxldFRNt1GaO0eTVAlN4gILMEghmS0JGyPiLtLmgS2ZUxQKovmXUuBBBoLQYWotxag3ltLfOuTFbK1Vg4fOmsyQ6z1sjQ2xtTa0HNuVK2icdhZXwMiR2ztQau2QO7fOXtujIz9gHaWwdmn0zehHcq0dY6YHjtbIwSdQCLVTunBQmds650YPnUuRi/omNkGYkGWVLHV2Tr3Kw9dBmjxbm3CsnBO4EG7iGM5/dB7xGHs7Zu48r7OAgK4J%2BRkF5lDvivdIa9shn03qkUFO9F7AovhPY%2Bj8IXP0vkfPoN9YXv2fki3IkKX7zCBVi2m6xNg/2JT7exAjOAeIJqeJJvitEuhlPgV6CDab0xQaQNBGDRjYLGkEH2tD6GJAJN1RIXUzASs0k1bhnV%2BGg0EbYYRyClliPgBIzamMYlROIPInYzQWBXRYAoJUd0lRcA0ZCM0z0WV6I%2BkZbZRddkFwOZXAIpBrGwwtnYpGCq0ZSKxjjVQRqTVmotQSK13kIAU3icE0q/gwmiMiXE9m2qU0JNNSkFIjpzVdUdJGggjpg0mKFvELJEspaK3yZWpWKs1alMCVrCp%2BsWmYCNibMQdT86NPmaM0grSr5O3Njo1QbswS9MEP032/tA5YhGaHcZ%2BcpnpBmQneZ4RFmMz4CstZOc86R0db9CQezAbl0OTod1STa59wuY3eA1zejm12F3a95yLAD2AUPd6Hyx6H16FPGeuL57TzfsvLe0Ksj/KhUULIoH95fLRSfVoyL4XfPRQMOD99xgDCg/izDv8SXFQIxS31U1qXFruMa01N5w0Fpgba6m/V2UqsZqg9BmDKB/yFQERhsr%2BpmAE1wJqGhhTivlWRmaSqRFLNqiAXBmj2GJBIdUET/UOrUP8KR4BnAOUyeoU9cT2nJPhI1FHMtk9JBAA%3D%3D)

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/all_confess.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/all_confess.test.hpp)
- [Example](../../../code/facilities/concepts/varybivore/all_confess/implementation.hpp)
