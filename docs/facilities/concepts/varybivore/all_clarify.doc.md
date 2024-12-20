<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllClarify`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-all-clarify">To Index</a></p>

## Description

`Varybivore::AllClarify` accepts a callable predicate and a list of variables.
It returns true if the predicate evaluates to `true` for every variable and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...&&Pred(Vs))</code></pre>

## Structure

```C++
template<auto, auto...>
concept AllClarify = REQUIREMENT;
```

## Examples

`AllClarify` turns a fold expression of a callable predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&Pred_0(***))` and `(...&&Pred_0(***)) && (...&&Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return true;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return true;};

/**** fun ****/
template<auto...Args>
requires (...&&Pred_0(Args))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&Pred_0(Args)) && (...&&Pred_1(Args))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSABykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCaAyzmKopxMdMXkSn5yuNxMAGYACLHEwBKwBMEQX5EAB0yJWJgA7BZzgRNgxjgRiF5MKCrGiwcTHk8KQcjgCLpcuLcjg9nq93p9vgjULSrgzQRCoTC4ZzkYjURisTi8QSiSCSWTZRSqXdjlQvLi7syngRMCwUgZtaC3MLkU9iMAFKDsBTzgBHLx4c4KY4QEXmABs7rOdI0EFN5pWqJZAjZX2OMVQnhVaogYsxmGxxFxVDESnJpMVz21uv1MqNf1QIr9FpBVuetvtjudrrMHprXqBvrNCgDkJr7qryPdnsB9Mb/sDL2D2vZYYjtCjDBj6LjCdx%2BMJabJzyVNIAKphZozDprdrtjthiMQSBTZkxHMhLkwFEoWtQ1YauJaY6jZRw1rROAFeH4OFpSKhODcaxrGOBQNi2TBWxBHhSAITQ3zWABrEAAjdRFEjdKQAjRN1JAAThBHCzBBfROEkXgWAkDQNFIH8/wAjheAUEAaLg3831IOBYBgRAQA2AgUj%2BchKDQXU6HiSJWB2VQMIAWlw45gGQZBjikREzF4C5CBIPB0D0fhBBEMR2CkGRBEUFR1HY0hdC4UgAHdiCYFJOB4d9P2/eD/04AB5P5BIIY5UCoY4ZLdeTJEU5TVMkdTnQ8MT6G%2BcxoJWXg2K0NYICQUSUnEsgKAgXL8pAYApDMPg6G1YhmIgGIvJicJmgAT1c3hGuYYhmp8mJtDqNiYNEthBB8hhaFa6ysBiLxgCNWhaGY7heCwFhDGAcRJodfq8AANw3LyPjqP4dhg8JtQ/azaDwGInK6jwsC8/E8EopbSD24hwyUMEdTWq6jHgtYqAMc0ADU8EweyfJSRg2rM4RRHEUyDPkJQ1C82z9DWlBgMsfRruYyA1lQFJekW2TZnQPlTEsawzHo97iF0/bCa6HoshcBh3E8do9FCBZykqPRCkyAQpj8Ozhd6IYBeWVntoEfpJm5vI7NqeoFbmaWRiqcYBjFvRTxaLWliqNYwM2bYJHcjgv1oryGNCuSFKUlS1LMZ1cG05LiK4NLYIBtYEEwJgsASGNSGQyQQURAi0UkDRJDMSQ3Wo1C8NIjhyNISiQTMREQTdNFEhBRIAgCLhCLw5I6N4BimJY/32Kynjsr4/yhMK4qkskthODCiLjmQAwjFUvDES4RE/y0ohGb0uzkaMxHpGRiy0es3QKsc5y2ut22a%2B8jg/IEv4gpC/uFKHtbR/Hyf4tQRL4igsw/YyjjW67%2BJhKK%2B%2B8qSlBh7KnhLgNEaC0GqrVeq1kOotVhtArqPU%2BoOFhkNRgBBRrjS8lNGac0FqwxWr9HYf58DnHqHtRaU9VBHW1LDM63QvJXRui1e6hD0qMxejBd6n1MDfVWkYP6oAm58GBgoMGEMoYw1egvBGJll6yFXlZP8G9Mb/WplYXGDCCbh2JqTTg5MCCU3BKo2m9N4iz2ZuHNWvQOZc1yOLYInNjaCwlukEW2RlZ2MllkRxstLENDmPrVW3R5Z9E1vzbWBt/HuIiQMbxpt1gWxMrvTy1kHbn0ipfEeXAx4TxuBAT2M8oK%2B3SgHUgQcQ6jHDshYBNELpZxzgERE%2BEAh4TMC0msiQK64Ttikzg9dWIA04i3JA/EApfw/sQHuOxmgsAUiwBQO0VI7SyYiHMsxNL4BnrpfSshF4yLhvI9GIASJbxcktJJ3T6K%2BXboFYKoVZnzMWcs1ZgUIAJV/o/FKIIX4DPfj/fKYy/l/wWSkFIlwll4UuM8y4qgumgPAZQSBf44ETRgsihB/VkH32GmgsaE0iGYGmrNMQuDXr4L4Sw0gxDtpkIOpQ5Ax0aGCDoZda6t1mrMMemw2GnD0jcJ%2Bnw8IAjMpCKYKDcGkNoY/hglI4yEhZHmVRgonQRzlHGBxjYDR8AiYkyyItXYFNsY00sHTWuDMmaaLNkE9WfgICuACfY9AsShYuN6PazxJQwkmwNla3oitWhRMCWzDWMTPVON1krWx0SjahuWGbcCltfYZz3vbTgdzIpzIWcccFKyzwbhefkkghTvlN0DsHUOlBrZ1KOXnTpxEzD1uqBoN0zSLm116bYBur8AwRxAFHceJcAiJxBAEJtxEcIZxBMky5jFG6ZWthpVtB9iklrevEDIzhJBAA%3D%3D)

By turning `(...&&Pred_0(***))` and `(...&&Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires AllClarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AllClarify<Pred_0, Args...> && AllClarify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<auto Predicate, auto...Variables>
concept AllClarify = (...&&Predicate(Variables));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4mF4iHdlMRMPhRGDSHd4UQAHR4gBqzTwTBi9AUMOwILQDG2KQIdyutFobgMxDwVAAnncYQARO4QPE48wANhFyNReHRmAghLZJLJKxWMKs1xBfwB5zVxzuABVMLMFF9Nb8NScgVr7uL0AB9DRGw5A6mzTCqFLELEI1BIlE2u287kBKwBHkQbGoQVKgDsFhRBE2DDuBGIXkwypMkZ5adVJstPutXHt%2B0dAmdrvdYe9qPz3OhfJMgfrIbDEfTMcwceICaTKbTGazwJzhzuVC8Ce%2BILBEI%2BqdhzbxV2IwHJ0Mp1xRAEcvHgUYbGczWeyOTC3FbbZiF0vBRSqSWwWW7jFUJ5h6OIFG2x2E1QxEpe5ns6C4IvNOx5zjiF7LquC6YJu276gyTIskSnLHqeGjnouChXiu3JmKKeEIfuyFHrCp5cBhl54te1xOneboPk%2BtAvgwb6trG8aJsmM5WH2AHqrq%2Br0uO1yzB8krWkwChKC01CjseXAUm%2BSrQhYHBrLQnABLwfgcFopCoJwbjWNYdwKBsWyYLh0I8KQBCaGpawANYgAEwo4okwpSAEkbCpIACc0I%2BWY0L6Jwki8CwEgaOhOl6QZHC8AoIDoXZulqaQcCwDAiAgBsBApAi5CUGgzx0PEkSsDsqgeQAtL5dzAMgyB3FIOJmLwEpEGy6B6PwggiGI7BSDIgiKCo6hpaQujkQA7sQTApJwPDqZp2n2fpnAAPIIgV9KoFQdzVcKdWSA1TUtZIbX8h4pX0O65jWSsvCpVoawQEgJUpGVZAUBAn3fSAwBSGYfB0GCxBJRAMTrTE4TNByS28LDzDEBym0xNodSpTZJVvAQm0MLQCOTVgMReMAcJMkl3C8FgLCGMA4gk3B9QAG76utLp1AiOw2eEYIaZNtB4DE82ox4WDrUmeCRTTpDs8Qj5KDy4IM8LRj2WsVAGEu%2BJ4JgM2bSkjCIyNwiiOIw19fIShqOt036AzKDGZY%2Bgi0lkBrKgdJZNTNWzOgvKmJY1hmHFCvdRzntdD0WQuAw7ieO0eihAs5SVHohSZAIUx%2BORWe9EM6ejORtT1AI/STEneSl90WMNHMRcjAkpdzLneiiS0TdLC3axmZs2wSCtHBaaQsW8PFh21fVjXNa1Zj8rghAkFZXBPbZmtrAgmBMFgCRvqQzmSNCOIBZGkgaJIZiSMK0WuX5oUcOFpCRdCZg4tCwqRok0KJAEARcECn5ZI48NoJVsMlDeaU3rZXerlHahVfr/TuhVNgnAjonTuMgAwRgWp%2BRxFwHEelOokDwD1ci1sBqW2kNbMadtJq6BBnNBaiNh6j1AfFba%2BUER3H2lPY69VsEMzwQQoh11UC3XiFZMw68XrpTgcg%2BIRU/oSK%2BndFAOCgZ%2BS4OhGgtBwaQ2hpNZG8NTYmNRujTGDhTa40YPjQmxM9Kk3JpTWg1MbJ0zVjsJxLNHDs2psQ1Q3MwSm35t0dawtRbwwlt456bJZY2QVkrTAKt6ZGHVqAaBfAdYKD1gbI2Js5aUItkNGhsg6ETT0owx2Gtg5WFdpEj2B9va9D9gHIOLsLBhwnhHMhUcD5l16PHROuQ87BATt3DO%2Bd0jZ2yNXMZBcsiTJLjHeuFc27zI7nXcufRG5p2bh3DZozDkDGWb3dYA8hpsLWpNSeGDBGaJEYQu0EAl5dVXrIzepBt671GAfZyOj0KC2fq/AIOJ/IBD8mYKFeFEiAN8mPda8VEqQLkTA%2BAcC8q7WUYo4gqCdjNBYPVFgChWbNVZlwfBkJBIdXwF1MhvVZBUNKWbCp9sQAhWYYtGm1zEW3K2ggvaB1VDEtJeSylOJqWzHEZI%2B6wVoSfKyQo1R30cUqvUWSlIKRrQUr8taKVBBrQipoWDeIhiYZw1RmYy1aMMZYxsRIvGBMibrWcRTMQbjTaePSbE0g%2BAURsw5pNLmyAeahMEOEoWIsxYchiVLeJpsknpBSardJ4RMmvWyUwXW%2BtDbGx0jZYpg0JBlNGrbSpOgOU1OMJ0t2MQmlex9iWTguwA7OxDpYbp%2BlelYAbasnZwz27kVTmUA50yihZCHakGZhd9k9y2bHdZAwp2DIbqcudUzxjLs2a3ddo751rwuRZIej92FIs4IdUVZK7i6sldOaVry6UrwemvZ6Xyfl70oMPEFHL37wuCmYQDXBEgaGFJCvlcVOAopSl8o%2BJ9AF/yvtCAIoHgo%2BUftCG5kHwFouHu1CDE8oNQNemsBWGRnCSCAA%3D%3D%3D)

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/all_clarify.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/all_clarify.test.hpp)
- [Example](../../../code/facilities/concepts/varybivore/all_clarify/implementation.hpp)
