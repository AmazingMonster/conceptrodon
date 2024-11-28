<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `AllFalsify`

## Description

`Typelivore::AllFalsify` accepts a callable type predicate and a list of variables.
It returns true if the predicate evaluates to `false` for every variable and returns false if otherwise

<pre><code>   Predicate, Variables...
-> (...&&(not Predicate{}(Variables)))</code></pre>

## Structure

```C++
template<typename, auto...>
concept AllFalsify = REQUIREMENT;
```

## Examples

`AllFalsify` turns a fold expression of a callable type predicate over `&&` into a concept so that it can be used for subsumption.

The following code will fail since `(...&&(not Pred_0{}(*)))` and `(...&&(not Pred_0{}(*))) && (...&&(not Pred_1{}(*)))` are both atomic:

```C++
using Pred_0 = decltype([](auto...){return false;});

using Pred_1 = decltype([](auto...){return false;});

template<auto...Args>
requires (...&&(not Pred_0{}(Args)))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&(not Pred_0{}(Args))) && (...&&(not Pred_1{}(Args)))
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSAMykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHF4ZRgDUysSY6AD6GgcmiQAiB1jItAQAnimYECYBVgE3EExeRAAdMCViYAOwWE4ETYMA5UMRKa5WME3UGJKwaACCJixe3CwCOJ3OXCut3udSer3en2%2Bv3%2BQJB4MhmGhxFh8NoiPR4NRSJx2KxBEwLBSBiF1zc9NQwMBmOIwAU12w/JOAEcvHgTgoDhAZeYAGwGiAMVAEQmnC5MnkQOUKlb2/loBizTCqFLEA4xVCeOFeBgQUEQqEwuEIzB8lH8/lCkVi8OJSUA6XA22KxLKrFqjVanV6syG/PG03m84aK0om3yhT2lZXfMG3PAg1Gk1m44Wrjl36pmuOgQut0er0%2Bqh%2BgNM4Nsg4EYheePIm5RrGzJiOZBnJgKJQtah%2BiWd9MBtEWDhrWicAK8PwcLSkVCcNzWawHBQbLaYOuJHikAiaU9rABrEAAn1QEAA59SkAIwX1SQAE5EhgsxknPDhJF4FgJA0DRSGvW97w4XgFBAHDfxvU9SDgWAYEQEANgIFIAXISg0BFOh4kiVgdlUCCAFpYIOYBkGQA4pEBMxeFOQgSDwdA9H4QQRDEdgpBkQRFBUdRyNIXQuFIAB3YgmBSTgeDPC8rz/O9OAAeQBRizVQKgDh4/V%2BMkQThNEyRxJ1Dw2PoD1zC/FZeDIrQ1ggJBWJSdiyAoCAYrikBgCkMw%2BDoIViGIiAYismJwmaZ5TN4ArmGIZ4bJibQ6jI79WLYQQbIYWhiu0rAYi8YBJVoTkStILAWEMYBxHazVarwAA3TBiO0106gBHZv3CIVUNvWg8BiIyKo8LArJnPBMO4XhpuIL0lBuYVho2ow/zWKgDAVAA1PBMH0my3mvb8FOEURxFUn6NLUKzdP0YaUCfSx9E24jIDWVAUl6WbeNmdBrhuUxLGsMx8NO4hZJm%2BA1lqepnAgVwpj8PTQgWcpKj0QpMgESmGfSJmGCGOnli6HoGjmFm9JJ3p%2BhaTmRiqcYBgFyXRdp8WJGJt9tgV/QLNwqyCJcviBKEkSxLMHVcGkoLkK4UKfzutYEEwJgsASANSCAyREkBBCwUkDRJDMSR9WwkC4NVtCMJAL9AUg/UwLgsCuH1AJJC4AIEP1dXtIIoiSIt8jIpoqK6PspiEqSwLOLYThmhYSawV4pgDkeYbRLgwEuEBW8pKIfG5L0n6lP%2B6RAaUYHtN0dLDOMkrzI4S8U/w2z88c5zy8r6va4MQ4uEb5vLggfzYsCz8zHN8KKNzov4mYxLUAC0ZF6ruujHXrgcJoJ54hyvLtLKor%2Bs/iqqpqhx%2BoNUYAQZqrUrIdS6j1Pqx0BpXSMKNW8%2BATj1GmrNVuqgFpCn6itboVkNpbSKrtHYt4DpHW/Kdc6mBLpDXgfiO6fBHoKBem9D6jB%2Brdz%2BipPusggZaVvMPMGt1MZWChvg2GDsEZI04CjAgaNbjCOxrjeIHdCZwx5hNMmFNPDtD0DTMo8s9KM16NLIxWQxZLAlkLPmUttF5EFt0DRfQ5jmPpoLfmtiqYy3mPoixKtXybGVmbQOU88K8E1jfZed8CTrybi3Q2%2BB26fjNmFS2pBra21GA7VC6FSCYUSI3T2YJE5gjBIkL2Pt47TzCZwdOpF6FUVovRBy59T7EBLjscuAkWAKEmiJSaMS4yzEkgkmSnc1K/WUhIbh6kB58J0CHAyRkTLHQniEjWs8GIAgOE5A4nSPLdN6QcfpjdBlmm3pfXe8RPyJEPvU6KFy4otIeYFEAvSUgpDOMcs4pyNzEBYLBDKL9sqUHfreH%2BbVvzgr/rVQBl9GogJam1RBmBOrdTENA78g1rrEN4EgiaqCrLzWQItbBghcHaXwdtZ4RD9r4zISdeIlDqHXToVnBhTBnqvXep9dhsge5cPGbwkGCzV7GEhjYMRRM7yIyyLNAA9KjCGWNLA4zCXjAm4jiYONJn4cmDB3AeN0fqlx3NTHM0NYYtmvQTWWO1cLdxuRPFWIECLbxixXFeOliuWWPjXGKwCSpVZllU6cF2X8rpPS%2BkDNXDNM5RtEnBWSZnCKVsbZ20oBPHJmEzCN0SIkAIARPaPw0HmmCYEqnWUIrYDOR97SOxAM7JuiQwJx2QoW/UyEYKB0SMGmeVba0TwkhWtOyb/ykFOhkZwkggA)

By turning `(...&&(not Pred_0{}(*)))` and `(...&&(not Pred_1{}(*)))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<auto...Args>
requires AllFalsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AllFalsify<Pred_0, Args...> && AllFalsify<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

## Implementation

```C++
template<typename Predicate, auto...Variables>
concept AllFalsify = (...&&(not Predicate{}(Variables)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAHKSuADJ4DJgAcj4ARpjEIGakAA6oCoRODB7evgHBaRmOAuGRMSzxicl2mA5ZQgRMxAQ5Pn5Btpj2xQwNTQSl0XEJSbaNza15HQrjAxFDFSNmAJS2qF7EyOwcBJgsKQa7JgDMbgQAnimMrJgA1MrEmPiiu6S3TF5EAHQ/AGpNeCYsXoChO2BMGgAgmgGFsUgRbpDaLQAGJiDJUc63E4AEVuEB%2BX3MADYSRAGKgEQ8nngXpgTAB2KwMnEQf7EQHAzAKZa8k5WKEQyEAegAVOKJZKpcKhWKJbcACrcggKW6SmVQuVS7XijWQoVeDJGe6PdAAfQ02OOeKwyFoFyuEBM/is/lZH2%2BP2WjIsjwIGwYtyo6Ppx2ZOO9YaFBqNwBNTzNXCtNtq9sumCdLud7s%2BqEJ3qZfoDQZD/MZEbLgqhu32h1Dbg9eZ%2BkOIwFBx3BUMeAEcvHhHqqkaj0XhMSc3NTzRo3i224SwUKYTNMKoUsRbrFUJ4g14GBAC77MP7iIHg7QlGWWdHq3sDkwjqdG4TZ%2B3Oy3ML3%2B9zEci0efR%2Bc46ThaM6tgo84dtiZiktBP7Dv%2BY6nMBXCgXOPwLlCS67Ku66btuVC7vuPpFietwEMQXihuG16QjM960maTAKEozTULu45cGC%2B6RhYHCrLQnD%2BLwfgcFopCoJwbjWNYtwKOsmx3OYxw8KQBCaHxqwANYBJIXwaJIXAMscGj%2BBo0HEmYgTBAJHCSLwLASBo04iWJEkcLwCggNOamiXxpBwLAMCICA6wECknzkJQaD7HQCRRDcnCqIExIALTEpItzAMgyC3FIXxmLwNJEBy6B6PwggiGI7BSDIgiKCo6i%2BaQugoQA7sQTApJwPD8YJwnqeJnAAPKfOFCKoFQtxJal6WZdluW6WY%2BIeDF9DrkpXDLLwPlaKsEBINFKSxWQFAQIdx0gMAUjJDQ9oJJ5ECxANsQRE05zdbwL3MMQ5xDbE2i1D5KnRWwghDQwtDvU1WCxF4wANsinncLwWAsIYwDiNDX51AAbtyA0rrUnzbCpES7DZYm0HgsQdT9HhYAN5F4A5yOkHjxCbkoOJ7OjVNGOpqxUAYba/HgmCtUNVwiSp5XCKI4g1bL9VqANLX6OjKDSZY%2BjU55kCrKg8JZEjKUzOguKmJY1hmK57Mlfj%2BudN0WQuAw7ieG0ehhPM5SVHohSZAIkx%2BChAc9IMvsjChNR1AIfQTB7eTR10gP1LMEfDIk0ezMHeh0c0GeLFnqxyRsWwSL1HBCaQLm8G5U3JWlGVZTleVLRAuCECQUHKVtqkC6sCCYEwWCJPupDaZIxxfAAnMcDKSPpZiSMSTn%2BMSM/6JwdmkA5ylfMSXDEoEM%2BBEf/gGf4c/EjXA1uR5Xn975e1BftIWjRFp3nWt8VsJwTQsBxgyFKTBbh2nRrlGeXwuB6UKvgYqeBSooVlpVBW0glZKBVk1XQyR2qdQ%2BpXautdBocBGmFT4twJrvGIIA4BoDwHGi4FAmBloIArSOmtHuKxtoC38gdVAq0EiRTOgIjhIwAFAJSgwq6M8uDTlursYgD0npNS%2Bm9D6pA1E/T%2BgDBwGiQaMAIODSGA0YZwwRueDRqNebbDEvgR4uN8ZNUJsgYmGiyZdAGlTGmb16a2O2hyFmKl2ac0wNzNGRg%2BagGfnwYWChRbi0lowDRKD5bVXQbIZWjUxI4PVvzS2VhtbeL1uPQ2PQTZmwtlrCwNs6520QQ7ceMceiu3drkEOIQ3aFz9qHdIgdsiJw6WHLI3So5O1TnHHOgy84p1jr0dOPtM55yme05Z/RRnFzWGXaqhD%2BpNXrhIuhYCDCMOYXpfEndio902jw5%2Bg9h6j0oJXHee8oH6QZFfBkRlJDL3SihYh99bCPx2n5AKwVQpjWEd/OKCUOAANmiwBQOMco4yYV8OsMw4FdxKmVWQqD0m1XkJg7JOgQDHFIHgrqyNdm332cND%2B41Jrwoyoi5FtxUVQIxQiNhojjo92OH3EFe1%2BGCJOlFXla0QDIpSCkM0HKzRcsYjQ9KfA6CKOUc9V6P0NFaN%2Bv9QG%2BiBGgyMRDKGdjMCw3hmISxrNrGRP8aQexqc8ZIzEi4txrMPEU14N42m5w/GM0CRokJ6Qwk80iREaJu1YlMBFmLCWUsUl4rSRIDJdViWqzJXk4w1SdaxBKQbI2AgkbCjNprK2lhaniXqVgAt4y5mtNzihb2ZQlm9KKFkJtqQ%2Bnh0WUXGZztJn9C7c0tO6y%2B09LGMO6Z2dx2tv7ZtLZCkK5byrns1ynBqEsARUilFaKuUXPgd3DagqB6kCHiPEY48bIvKSFA44xx/CmQMk5B9DJj60o3e5IF3kz2T38LPII0EZ6SBnkZeeXByU2WOOuuunBbm7UrgVT9cHv1CtWOzDIzhJBAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/concepts/all_falsify.hpp)
- [unit test](../../../../tests/unit/concepts/typelivore/all_falsify.test.hpp)
