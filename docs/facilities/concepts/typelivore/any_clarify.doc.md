<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyClarify`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-any-clarify">To Index</a></p>

## Description

`Typelivore::AnyClarify` accepts a callable type predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...||Pred{}(Vs))</code></pre>

## Structure

```C++
template<typename, auto...>
concept AnyClarify = REQUIREMENT;
```

## Examples

`AnyClarify` turns a fold expression of a callable type predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||Pred_0{}(***))` and `(...||Pred_0{}(***)) && (...||Pred_1{}(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return true;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return true;});

/**** fun ****/
template<auto...Args>
requires (...||Pred_0{}(Args))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||Pred_0{}(Args)) && (...||Pred_1{}(Args))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSABykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCXhlGp%2BdXNyYAzAAixywyFoBAAnilMBATAErAE/hAmF4iAA6VErEwAdgs5wImwYxwIxC8mF%2BVgxf3RPysz0eTwORw%2BF0uXFuRwez1e4WAjKuLN%2BAKBIPBkOhsPhiJRaMx2MwuOI%2BMJxNJmIpyppz3ph2OVC8%2BLu7KeBEwLBSBiNvzcEtQqORT2IwAUv2wtPOAEcvHhzgpjhAbZi3P6zkyNNKVRA7Q6VujnmgGLNMKoUsRjjFUJ5tbqIOisTi8dqxEpleTabSjSazSSfpakdbURHHT9nc83R6vT6/RiA52g19Q%2BTw/aFFHjuYAGxj9uo/2Bz7Mvvw%2BtR2mx%2BOJ5Op9M6hhZ6W5%2BUEomVsl/Esau7HAAqmFmrMOBt2u2O2GIxBItNmTEcyEuTAUSha1C6haXBOlmlIWBway0JwAS8H4HBaKQqCcAGljWMcCgbFsmAjmYPw8KQBCaJBawANYgAEo7Ioko5SAEGKjpIACcPwMXh%2BicJIvAsBIGgaKQ8GIchHC8AoID8URCGQaQcCwDAiAgBsBApEi5CUGgJp0PEkSsDsqg0QAtIxxzAMgyDHFIyJmLwFyECQeDoHo/CCCIYjsFIMiCIoKjqFJpC6FwpAAO7EEwKScDwUEwXBxFIZwADySIqQQxyoFQxz6aORmSCZZkWZIVk%2Bh4mn0Mm5j4SsvCSVoawQEgGkpFpZAUBADVNSAwBSGYfB0EaxBiRAMSxTE4TNKCEW8CNzDEKC8UxNodSSQRGlsII8UMLQ41%2BVgMReMAlq0LQYncLwWAsIYwDiNtnqLXgABu16xQmdRIjsBHhEa0F%2BbQeAxKFM0eFgsWEngPEnaQD3EKmSh/MaF0/UYxFrFQBgOgAangmBBfFELwQRznCKI4geQT3lqLFAX6BdKDWNY%2Bi/WJkBrKgKS9MdBmzOg/KmGhlhmEJkPEA5j1M10PRZC4DDuJ47R6KECzlJUeiFJkAhTH4gUq70QyK8sYu3QI/STDLeSBbU9SG3MOsjFU4wDOregfi01tLFUayYZs2wSFFHCwQJsXCRlhnGaZ5mWWYPq4HZZV4VwlWEUjawIJgTBYAkWakORkg/MiLEYpIGiSGYkijnxlFMRxHBcaQPE/GYyI/KOGKJD8iQBAEXCsUxySCbwwmieJCdSbV8l1YpSWqS1bWlTpbCcJl2XHMCF0WUxyJcMiiG2UQQuOYFBOucT0ik0o5N%2Bbo3UhWFE0%2B37vdxRwiXKUiqXpQvxnL%2B8XBrxvNwQMVjVSq4TrvHaq0kx7T3iGpVqqASqjE/p1JiXB%2BI0BBPEAaQ0/JTTGhNUg2CZpzQWg4XBK1GAEHWptWKO09oHSOrgs68MdiIXwOceoD1jpb1UC9I0uCPrdFij9P6Y1AZMKqkLMGBFIbQ0wLDc6RgEagGHnwVGCgMZYxxowXBB8ibuWPrIMmvlEIXypojHmVhLD0xiIzDOLM2acA5gQLm/wzHWH5n3QWwtrHu26AbPwEBXAO0CvLMoNtlbpFVtkE2GtUjhO1grUJZsfEWz6HMQJ%2BtklG3mCE12jtUlRNyQMF2Ss47rE9u5W%2BMU/KB3fjlBBq916b0jvgHewC45VUTqQZOqdRgZ3Isg/iX1q61wCMiZiAQmJmAmWYUciRO6MX9lUzgA8JJIxkqPJASlkrQMgcQWeOxmgsGMiwBQd1zJ3W/siCsswbLNPsnvTyhM3ISD0V5U%2BhidAgB%2BMFUK4UToVIWUJBKE8UppQykck5ZyLlXJSv/WBgD4jAJ%2BKA1ZEC4VNW2Wi0qIBTkpBSJcc5TFLjQsuKoeZqC%2BoYOGqNGauD8GzXmotEhsDVrkI2ltZhmBdr7TEHQ8GDD5GiNICw267CnpcOQK9Xhgh%2BHfV%2Bv9UEIjgbiNwVI9IMi4byK5KslGTB0aY2xrjLRshD66IeQYimnyTHGFphYwRXikKsyyMdXYnMaa8wsG4pCHisD2vNr0SW0tcjROCYsYpMSihZDSVrLIRS9Z%2BoaHkoNjskm9EybG22TtWj5LNlbeJOSSke2wt7Sud8A6cDBTlY5pzjgEsuZ%2Ba8MKo4tPKm0oeNUk4pzTpQH2QzPn1zmXhMwQ7qgaFHOMgFfclm2EHmAqMmcQDZ3Xq3AIRcfgBFHXhBilcfiVMBSJNtJFK7WQnQ/dpw81iQwyM4SQQA%3D%3D%3D)

By turning `(...||Pred_0{}(***))` and `(...||Pred_1{}(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires AnyClarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AnyClarify<Pred_0, Args...> && AnyClarify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<typename Predicate, auto...Variables>
concept AnyClarify = (...||Predicate{}(Variables));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4CABPFKMViYO7KYiYfCiMGkO5MLxEAB0xIAas08EwYvQFDDsCC0AxtikCHcrgx4W4DMQ8FR4XcYQARO4QYmEkwAdjcErc6MxeGxmAlVnFAogZO5lOpKxWMKs1xBfwB5wNxzuABVMLMFF9jb8jScgSb7rL0AB9DQ2w5ArwZIxojFuj2Cu5YZC0BFIiAmAJWAKq/FE4k68UWDEETYMO4EYheRXQ5UCnX5kFOw7%2BzGurie/be33ActuqvB0PhxGYKMx6PxgmoUXJ1OYdPETPZ3O6iWF8f6u33KheTPfEFgiEfPNuBO94lXYjAGnQunXDEARy8eAx1rZHK5PPhMJlAfduO3u9FtPpAlmmFUKWIdxiqE8O45wYCB%2BzTDMgLEJRxxVEtrmXF5VzvDdRWfPcD23TATzPS1WXZTlyV5O8XUfVkdwUV9935MwADZzBovCr0I29YRIrgn3IyiMIZT9v1/f9AOA0ClXA4csxzPMCzgm5TQtWZqyBWYPnlV0mAUJQWmoec7y4WlQKLCwODWWhOACXg/A4LRSFQTgpUsaw7gUDYtlRcxoR4UgCE0Iy1gAaxAAIaMJRIaKkAJxRoyQAE5oQisxoX0ThJF4FgJA0DRSAsqybI4XgFBADKvMsozSDgWAYEQEANgIFICXISg0GeOh4kiFFOFUEKAFpIruYBkGQO4pEJMxeDlIhuXQPR%2BEEEQxHYKQZEERQVHUYrSF0diAHdiCYFJOB4YzTPM7zrM4AB5AlapZVAqDuDqaO6yRev6wbJGG4UPCa%2BhfzcrgVl4IqtDWCAkEalJmrICgIDBiGQGAKQzD4OgwWIfKIBiE6YnCZp4X23gseYYh4TOmJtDqIqPMat4CDOhhaFxtasBiLxgHXWhaHy7heCwFhDGAcRGZw%2BoADdLROr86gJHYPPCMETLW2g8BiHaiY8LATuzPBUq50hReIf8lAFcE%2BcVoxvLWKgDF3Ek8EwTazqRCyPOm4RRHEBaXeWtQTo2/Q%2BZQaxrH0JX8sgNZUGZLJOc62Z0EFUx7MsMxsr1iaxbDroeiyFwGHcTx2j0UIFnKSo9EKTIBCmPx2PL3ohhL0Z2NqeoBH6SZ87yJvunJho5nrkYEibuYq70JSWn7pZB7WJzNm2CRDo4MzMpOnK7q6nq%2BoGoazGFXBCBIaj3P%2BzzzbWBBMCYLAElA0h/MkaFCRi8VJA0SQzEkGj0sCqLEo4ZLSFStCMwhJoQ0XFIkaEiQAgBC4LFKKyQsq8BynlAqJ9irAwqiDKql06pQxht9VqbB2rryemGPmg0oqEi4ISKyY0SB4EmuxF2s13bSE9kob2a1dCI22rtPGC8l6INOhwC6NUCR3BumvB6PUyF%2Bi4JQ6hHoICfXBt9Q%2BZhj6AxKlg/B8R6rQ1QF9UYsj4ZRS4BlGg4Z4howxmtAmOM8akHsUTEmZMHCOKpowGmdMGZWSZizNmHNHE8xNjsPxQtHCi05rQ1QkswSONlt0E6itlY4zVmEgG3JtYeT1gbTARteZGFNqAdBfArYKBtnbB2jBHHMLdvNNhsgvarSstwv2ZsE5WEsMHGIocb4R16NHWO8dA5JxTvENOfTp7dxbn4CArgR7sSLmUAeZd0gV2yB3auqR1l12LqsruWdW7Dy2aPGZvQ27zBWZPUeJzcjbLHlcxYpc/rrFnvNARx01qr3uo9O4JiKFUJobvfA41D5/QBqfUg59L6jBvv5cxGV5b/0AQEQk0UAhRTMFi2iiRYGRWXt8zgKDCrm1KpgpA1Urr6N0cQQhOxmgsB6iwBQwsBrC3kYSSEloCCjVBfQxhi1XZzQkI0paHCWk6BAAlXhe0uafMJdlc6ODrq3VUMy1l7LOXcvksowxqj4iH2hJoslOj9UQxpea76IA2UpBSK6DlUVXQ6oIK6dVbDkbWMoLYqyziGYeT9a48mHjDHU1pvTE6/jWZiCCTrEJRSMmkHwBiEWYs1oS2QFLBJggkkKyVirDkGBE2a2ybwXJ6R8nGyKeEEpQMylMGtrbe2jtamyBYQ0oVzSfbSvacYUZNgUlTOspHD8nBdixwDonCwyckGpwYenG%2Bzdeg5zzvcwuucJ4vJ2UULIizt0bM3Y3TOPdjkDD3Uu3uAxD2D3GGe05Q8r37Jua8meLl56/0ESvTgd0NVsruI6rlq5dV7zBb9E16Cz4XyvpQBeKLpXAPxfFMwyGuCJA0DRTFiqkHEtsKgrR2pb4gHvlQyBAQ37QgCOh%2BKEVf7Qi%2BUq3KaCgYLxGlh4RkKIO62sdnSQQA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/concepts/typelivore/any_clarify/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/concepts/any_clarify.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/any_clarify.test.hpp)
