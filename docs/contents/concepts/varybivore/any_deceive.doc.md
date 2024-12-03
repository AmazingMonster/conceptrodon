<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyDeceive`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-3">To Index</a></p>

## Description

`Varybivore::AnyDeceive` accepts a callable predicate and a list of elements.
It returns true if there exists an element whose value result fails the predicate and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...||(not Predicate(Elements::value)))</code></pre>

## Structure

```C++
template<auto, typename...>
concept AnyDeceive = REQUIREMENT;
```

## Examples

`AnyDeceive` turns a fold expression of a callable predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||(not Pred_0(*)))` and `(...||(not Pred_0(*))) && (...||(not Pred_1(*)))` are both atomic:

```C++
constexpr auto Pred_0 = [](auto...){return false;};

constexpr auto Pred_1 = [](auto...){return false;};

template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (...||(not Pred_0(Args::value)))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...||(not Pred_0(Args::value))) && (...||(not Pred_1(Args::value)))
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgCcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BxoDHOYqqnEANRMXkSnysSY6AD6Gqcm/gAiz4FWga8QF0QAdIDViYAOwWW4ELYMU5UMRKF5WEGvBEmDQAQVRaP2h2OZz%2BqGutweXGebw%2BXx%2B%2BMB/2BYIhUJhcMwKKRKPRmIImBYqQMnJebnxpwAki9sJi5sQvA5TgBZASoIgMACemNBVnRp01pzmTEcyFO2M5uPOlwJADcxF5MM8wSLWf51Rj7Y6OVyebrmf43AQlalGKxMNS0cRgApRZjbgBHLx4W4KU4QamgtzJiAMBWEu6PCDB0MgEAW7yYVYlzGGo4nU6xVCeGFeBgQWngzCQ4jQ2G0eEO0HI9noznc3me72%2B/1sIMhsP%2BMXoqMxuOJwHJ1PpgiZh4aHOT/OFq0l1bPMwANnMR4TSZBKcvaYzNyzXC3eYLluLpfR5eN1drVHrjbV9LbU4CElT1EV7DF0R1PV7iYBQlFaah635OVVwEFUvS4cNp0bYEHQ4dZaE4QJeD8DgtFIVBOBTSxrG1TZtmtcx/B4UgCE0fD1gAaxAQIj3%2BAAOI8pECEEj0kJJ/FEsx/H0ThJF4FgJA0DRSFI8jKI4XgFBAFS2LI/DSDgWAYEQEBNgIVJLnISg0G5OgEiiANOFUQSAFoxNOYBkH1KR/jMXg7kIEg8HQPR%2BEEEQxHYKQZEERQVHUfTSF0LhSAAd2IJhUk4HgCKIkj2IozgAHlLkstdUCoU4XKPdzJE87zTl8swEw8Oz6DOJiuFWXg9K0dYICQWzUnssgKAgYbRpAYApDMPg6E5YhtIgWJCtiCIWiVHLeHW5hiCVYrYm0eo9JY2y2EEYqGFoLakqwWIvGAAVaE7bbSCwFhDGAcQ7tjE68DNTBtKSo56kuXYWIiTlCKS2g8FiTL9o8LBCuAvBFO4XhAeIaslFeLkvrhox2PWKgDFDAA1PBMDS4q/VIljwuEURxBipn4rUQqUv0L6UGsax9Hh7TIHWVBUj6YHXLmdAXleUwaMsMx1Ox4gQqB%2BB1jqBpnAgVxpj8VKwkWCoqj0IosgEfWzYyC2GGGE2Vm6XpGnmK3Uq1voBlae3RmqCZBjd/3veN32JE1%2BidjD2SOGI1TCo06q3I8ryfMkPyE1wILOuk7repJ9YEEwJgsESRtSG4yR/H%2BCSQUkDRJDMSQj2U3iUhh%2BTSEU5j/iEo9%2BKSfiuCPQJJC4QIJKPOOko0rSdNYknDJMwazLKqzxsmjrHLYTgWhYM0QVcpgDQMIwmqSf4uH%2BcjAqIVXQtSpnItZ6R2aUTmkt0OaMqy7a8pjgrp4lVXhVKqu996H2Pl9M%2BF8r6tVQO1BIh5/BmB6vPfSA0hrwJGh1ayE0sFTTAQfZAJ8ZpJC4CpGgtBFrLVWklXam03r0P2odY6Dg3rnUYAQK6N1Cr3Ues9V6mN3oEyMD9ci%2BBbgNEBsDa%2BqgwacjelDHohU4YI02sjXY5E0YYxYtjXGmB8afVEREUA6C%2BDkwUFTGmdNGBvUfizaKL9ZAc0SuRT%2BPNibyysJYQWsRhZlzFhLTgUsCAyzeF46wSteCoBVmrfxmsej/R1nrTwHQ9BG3KKHVK5s%2BiBxydkH2yw/YexdgHVJ%2BR3aJO1v0eYhTTbu1duUg2QcFiZKKVHBQEdop/1jmpaJnBzjED3gfI%2BxCoE1BgU8CAmdb5INzmg/qBci4l0oH/DuXdz71xBOPEEIJ/ANybqPKe6lOCz10gvIyplzLlVwRvByTkOC7w8iwBQZp9RmgmUOOYAV8C3xCmFWQT9HGxXkG/VxOgAjpUytlTGPSAEnI4KVCylxTiVUGSwZ5rz3mfI9HMOBCDs7%2BH8KgvqBll53LGjZfBHUCzIFSKke4Hykj3C%2BQQGCQyxLzSoQkGha0Nr7UYfyg6R0TrsPgRdLh11briMwA9J6YhBEsQ%2BoTTRvAJH/WkYVUGyBwaKMEMo2G8NEZKg0ajVWOisYJH0YYwmJiF5kyYJTamtN6Z2MBQ4iQTi4pgq5pCkhfMFY2FUfEii4tsjAwAPTSwDd4iwUSKKxKwCGkpySGDuCaektNdTHb5Mthm7JNs%2BjZuKVUz2jS8jNJTTUwYxa9A6imPmlptbuobC2JHFtMNenxwGU8%2BqLy3mnCZf8VlGdfkkDmSS/OpBC7FzGGXduCkQBmHPkSwIgR67kI0ES0S/Fjn9M0rYOepKSzlxAJXC%2B/h%2BIj2kuuo80lRLR38PC/ded0F/38nuoqB7j3rGxpkZwkggA%3D)

By turning `(...||(not Pred_0(*)))` and `(...||(not Pred_1(*)))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AnyDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyDeceive<Pred_0, Args...> && AnyDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept AnyDeceive = (...||(not Predicate(Elements::value)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxmpK4AMngMmAByPgBGmMQgQQAOqAqETgwe3r4ByanpAmER0SxxCUF2mA4ZQgRMxARZPn6Btpj2jgK19QRFUbHxibZ1DU05rQojveH9pYNmAJS2qF7EyOwcBJgsSQZbJgDMbkxeRADUysSY%2BKJbpGcEAJ5JjKyYAHSf2PRsggqH2BMGgAgmgGOskgQzsCGI8ACJVTB4ABumDOhzhZwgn3eJgA7G58W4IAxUFDLtc8LdMBBvttGAQFCAQMixF5MAtOYcrCCgcCAPQAKmFItFYv5fKFIrOABVMJMFGdRRKQVKxerhSrgXywZNMKoksQzidzhT0AB9DTog6YkwAVisdrhEBNqBxC3xFiuBFWDDOVDESm5%2BLhwd5IN1WwNRtdFyuFq41ttDvtztd7s93t9/sDmGDeNDBx52pBWx2ezzR1jAEkAXzJsQvA4zgBZARkgSPPmevlnPtnSZMRzIM6R/WG42nVBnVneNGe2sFsPapdF7ul7a7IeVtxPF7MNg44HEYD/A6AkFXACOXjwV0VMPhiJRO7Nlvux9POLrEYEeujZwxKgnj%2Bl4DAQB6eJepgPrEH6Aa0EGa5LuGwJllu%2BxHHuryHp8n5nhex6YDed7ytCsIIusL6HG4b4aB%2BJ4KN%2B57omY/jmP45FPlRqI0W%2BXAMV%2Bnw/qCf5RhOQEgVQYEQZmMHZgQjaVlYKElsCg7DuaTAKEoDTUGBNFtqSRCwjRXB1ueEEekWHBLLQnB2rwfgcFopCoJwhKWNYA4rGs85mAcPCkAQmi2UsADWIB2pI7waJIXB4gcGh2hobGBAAHOl%2BicJIvAsBIGj0c5rnuRwvBMvRIUubZpBwLAMCICAKwEEkpzkJQaA7HQ8SRG8nCqOl/gALT%2BJIZzAMgI5SO8Zi8JSRDEHg6B6PwggiGI7BSDIgiKCo6jVaQugCQA7sQTBJJwPB2Q5TmhW5nAAPKnK1UKoFQZwDcNo3jZNZzTWYWIeF19BGuYgULLwVVaEsEBIJ1STdWQFAQPDiMgMAUhBDQtBbMQTIQDEd0xOE9SPJdvDE8wxCPA9MTaFUVVBZ1vwEA9DC0GTB1YDEXjAMctCIeTpBYCwhjAOIXOkdUqJMgd%2BpVKcGxBeEWz2QdtB4DEZ3Ux4WB3YpeD5dwvCosQQFKAiotGBrRihUsVAGKeABqeCYMdD37kLq3CKI4hbd7u1qHdR36GLKDWNY%2Bia0ykBLKgkIZLLQ2TOgGKmF5lhmCVpuLVgMcQW0HQZC4DDuJ4zR6KEMwlGUegpGknSZOXOQCfXBQMH0NeDAJlTVF0UxjH4PftAzNRTJ3AwJD3A/N0Pww9BPcxT0sCi%2BesEjXRwjmkMVvClR9g0jWNE1TTFAO0vgC2seDkN20sCCYEwWAJAXkWSAc7wAJwHHikhxWYkh/CFTtP4T%2B2UOC5VIPlQK7x/BcH8OlT%2B6V4HRS4Hab%2B/gd53VKuVEAlU7a1QarDJqz02rI1RiDXqbBOD1BYMiPEQ0mCjgMEYP6n93hcFinNS%2BJAlorVkOtP20gA5KCDgdXQQRTrnXJpvbeu97ocCei1U4Zw3rGmIHQhhTDkAsOAGwjhsVAaoGBvEa%2Bixb7VRhnDYxCMQbtRRjYtGtD6FDR0WLLgn8uD0WxrjfGhMDqU1JkLQJ1Nab0wcELZmDI2YczutzXm/NBbG2FtsMWEtXL4CuNLeUd15bIEVkLFW7Q7oay1qTXWGxXIGyNkFU25tMCWzSeEUAli%2BCOwUC7N2HtGBewEb7TawjZCB32q5CRodbbpysJYKOMR85xwTn%2BTgycCCpxtJM6wWc945yWjk2OhdR7OAgK4QeldS6L1rq3fIjcTmXIbhkc53d9l9wYN0UYs89C90bq86YxRJ4fJntkOeg4GgPOXssVY68uCyNugdfezitHMLFvozhVoL6EBINfKFFjob30fs/Sgm9IHQPYXFPE6C8SJUkAA0aAl5E4NsHg4KBC6qNWai9exFCep9Q4LQ76LAFDIhHMiDx7wKyTG4ei3O/C1r9IkIMnaoiRk6BAAcUgUiLrG2hVg2Fj1SGvXerysa/LBUzhFWKqEEAga2NMWDA4EMmWtOIZypGHVHEgxZMgJISRzTCs/uac1WkNGjT4HQXxlB/GuRCZzIKUawkM0icYlmMTOYZMwDzPmYgklBRFmkypvBMmjxlrk1QCstiFMEMU9WmttaPAqfrRaNSTbxHqY062zSCEOyYM7V27tPbJO9oIgZ215CKuDiq8ZxgI7TNKXMtyCyGCy35CncOGcLCbLctsvO8AV4j2eSXMugLTnoFBXXK5GQbmkDbo3E9w8i79x6Bez5Y8F7Vz%2BdPB97z30gtfUvDe4K/J/rVnI7BnB1EsD5QKoVZrtyTCxLgSVmL7VQzCqQB%2BT9BgFzVkSxI7CDgHDtCleKhU8N4gQdqkqnBcH4MsRFEAkg7RfztOlNin9JCf0Sj/Lgqq1YHBhRRsqDqcXgNmuRvelHBModNmkZwkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/concepts/any_deceive.hpp)
- [unit test](../../../../tests/unit/concepts/varybivore/any_deceive.test.hpp)
