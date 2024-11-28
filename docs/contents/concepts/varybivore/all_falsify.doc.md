<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `AllFalsify`

## Description

`Varybivore::AllFalsify` accepts a callable predicate and a list of variables.
It returns true if the predicate evaluates to `false` for every variable and returns false if otherwise

<pre><code>   Predicate, Variables...
-> (...&&(not Predicate(Variables)))</code></pre>

## Structure

```C++
template<auto, auto...>
concept AllFalsify = REQUIREMENT;
```

## Examples

`AllFalsify` turns a fold expression of a callable predicate over `&&` into a concept so that it can be used for subsumption.

The following code will fail since `(...&&(not Pred_0(*)))` and `(...&&(not Pred_0(*))) && (...&&(not Pred_1(*)))` are both atomic:

```C++
constexpr auto Pred_0 = [](auto...){return false;};

constexpr auto Pred_1 = [](auto...){return false;};

template<auto...Args>
requires (...&&(not Pred_0(Args)))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&(not Pred_0(Args))) && (...&&(not Pred_1(Args)))
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSAMykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHGgMs5iqKcQA1ExeRCfKxJjoAPoaJyaJACJPAVYBLxDnRAB0AJWJgA7BYbgRNgwTlQxEpnlZgS94SYNABBFGovYHI6nX6oK43e5cJ6vd6fb54gF/IGg8GQ6GwzDIxHItEYgiYFgpAwc55uSkA1HEYAKZ7YDE3ACOXjwNwUJwgVPMADYVRAGKgCATbg8IEKRStDRisRycScYqhPNCvAwIDSwZgIcQoTDaHDEgikWy0RyuTymYl%2BRdUFT9aLEuK0VKZXKFUqzKqE%2BrNdr7ho9cKFIaVk8Eyq4wCVWqNVrrjquBmDUa0SbDsdzZbaNbbfa6c6TgRiF4A56MRjZkxHMg7kwFEoWtQbXyuGK7UCPRw1rROAFeH4OFpSKhOG5rNYTgoNltMLnEjxSARNIu1gBrEABZV/AAcyqkAWByskAE5Eh%2BzMllw4SReBYCQNA0Uh103bcOF4BQQAgy8N0XUg4FgGBEBADYCBSC5yEoNAuToeJIlYHZVBfABaT8TmAZBkBOKQ/jMXhbkIEg8HQPR%2BEEEQxHYKQZEERQVHUZDSF0LhSAAd2IJgUk4HglxXNcry3TgAHkLlwrVUCoE4KOVajJFo%2BjGMkZiFQ8Ij6FOcwzxWXgkK0NYICQQiUmIsgKAgDyvJAYApDMPg6A5Yh4IgGI1JicJmgAT0U3gYuYYg4o0mJtDqJDz0IthBA0hhaAS8SsBiLxgH5Wg3US0gsBYQxgHEErZSyvAADdMHg8TDjqC4dnPcIOUAzdaDwGI5NSjwsDUzs8FA7heA64gLSUF5OQa0ajCvNYqAMEUADU8EwaSNJSRgap44RRHEQTLpEtQ1Mk/QGpQPdLH0Mb4MgNZUBSXouso2Z0GeF5TEsawzGgpbiE4zr4DWWp6mcCBXCmPwpNCBZykqPRCkyAQ0dx9J8YYIZseWLoegaOZCakxHen6FoyZGKpxgGWm2aZrGWYkBGj22Xn9BUyC1JggyqJouiGKYswFVwdi7P/LhHIvba1gQTAmCwBI7VIO9JESP4f2BSQNEkMxJGVcCHy/IWgJAkAzz%2BV9lSfL8ny4ZUAkkLgAh/ZURfEmC4IQ1XkNcjC3Kw7S8J8vzbNIthOGaFg2uBSimBOZADCMRivz%2BLg/k3NiiBhripMuvibukO6lAe8TdGC2T5MS5SOFXQPoM0mPdP0lO04zrOc%2BAPOC6LqzUBs%2BJTzMFXnJQqP4/ifDfMnzzbJAfv0%2BzhquC/LgIJoWgwoiqLxOS%2BKaov1L0syhwatyxgCAKoq1NK8rKuqhbavWowms3fANx6gdS6sXVQvUOQ1UGt0NSo1xrxSmjsTcs15rniWitTAa16p/3CKAcOfA9oKEOsdU651v6V2ugJGush7piU3I3Z6W0wZWHenAr6utfr/U4IDAgwNXjMIhlDeIZc4bfUpq1ZGqNPDtD0JjMoPMpJ416BzJRWRmZLFZvTam7NpF5Dpt0CRfQ5jqJxnTGmuj0ac3mPIjRgtDybAFsrO2HcoK8DFlvQeO9c57zHo8CA8tS6nmVk5NWpANZa1GLrQCwFSCgUSPnM2wI/bAmBIkc2lsfadzcZwEOiFtqoUjkgbCOkV5L2IInHYKcaIsAUG1BibUfH%2BlmKxfApdOLcVkFXKhQl5B1zoToR2Mk5IKQWm3Fxotu44QuCcPSZxiAsGqbU%2BpjTBydS1BAay69p72USHPfJi815eVKYcjedSUgpDuA0r8dwmkEBHPMz8IVj7xFPtFWKqUr7vLShlLKD9J55WfoVYqADMBlQqmIL%2B546obSQbwQBrUQFqR6sgPqUDBAwPEnAiacVEEzRhqgxa8QMFYI2rg/Ju0mAHSOidM665zwUP4hIahwk%2BmPUGcPV64NWGfXhluP6WQuoAHogacpYRYSGbjoaw3YQjAxSM/AowYO4CxsilUmIpqogmKrFHE16OqzRcqGbmNyJYrRAhGbWMWKYqxHMBxcxsaYvmDiBJjNUkHTgcyFkmRqXUk4Vy/i3Llq0kgQS9nh3VprbWlA24xNAmYfOiREgBACGbA%2BGhE0fifFk9SsFbCh3noaPWIADYF0SE%2Bb2/4U3Kn/B%2BO2iQ3Vd1zQWtuLFs3BzDi5NYS0MjOEkEAA%3D%3D%3D)

By turning `(...&&(not Pred_0(*)))` and `(...&&(not Pred_1(*)))` into concepts, we allow compilers to perform proper subsumption.

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
template<auto Predicate, auto...Variables>
concept AllFalsify = (...&&(not Predicate(Variables)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAbKSuADJ4DJgAcj4ARpjEIGakAA6oCoRODB7evgHBaRmOAuGRMSzxicl2mA5ZQgRMxAQ5Pn5Btpj2xQwNTQSl0XEJSbaNza15HQrjAxFDFSNmAJS2qF7EyOwcBJgsKQa7JgDMbkxeRADUysSY%2BKK7pJfnRAB07wBqTXhMsfQKJ2wJg0AEE0AwtikCJcQbRaAAxMQZKgAT0uJwAIpcIO9XuZAviIAxUNCbnc8A9MBAvsQfn9MAplkyTlZQcCQQB6ABUPN5fP5HPZ3N5lwAKgyCApLnzBaDhfyFTzZSD2eCZphVCliM8Lqhrrd0AB9DTo45Ykz%2BKz%2BDEQF6oXHLEwAdgstwIGwYlyoSMwLOdGL9bNBat2mu1dv1d0NXFN5stFptdodztdmHdxE93toSj9ToDx1ZKtBu32h19pyT7xBxGAAOOQNBtwAjl48LcpbCEUi8KiTm4yUaNE9q7XcYDVQJ1WHLrFUJ4vV4GBBHS63R6vT7cwGgyCSwcmEcK7rcSO6w3q5gW22GTC4Yjsz2UX2B8bhzWFGP6%2BizASf7euw%2BvanC%2BXBvqO7zjsGk6hlqM5zrQC5Liuqbpp6BDEF45ZWHm7LsjMB4UoaTAKEozTUIufZcICy6OgWHCrLQnD%2BLwfgcFopCoJwbjWNYlwKOsmyYN%2Bxw8KQBCaPRqwANYBJIrwaJIXBOscGj%2BBoP6BGYAAcWn6Jwki8CwEgaEOrHsZxHC8AoIBDuJbH0aQcCwDAiAgOsBApBc5CUGg%2Bx0AkUSsNsqhaYEAC0gSSJcwDIMglxSK8Zi8OSRC0ugej8IIIhiOwUgyIIigqOo9mkLooEAO7EEwKScDwDFMSxEkcZwADyFyedCqBUJcIXhZF0WxfFclmNiHh%2BfQ2rmCJyy8HZWirBASC%2BSk/lkBQEDLatIDAFIyQ0LQuzENZECxE1sQRE0KK1bw53MMQKItbE2i1HZom%2BWwggtQwtBXSVWCxF4wBnHC1ncLwWAsIYwDiH9151AAbgyTUarUFzbKJES7IxJW0HgsRVfdHhYE16F4EZYOkIjxCzkoGJ7FDuNGBJqxUAYtYfHgmDlS1KSMNd%2BXCKI4h5Zl8hKGoTVlfoUMoDxlj6Hj1mQKsqBQlkoNhTM6CYqYljWGY5lU2lSPK503RZC4DDuJ4bR6GE8zlJUeiFJkAiTH4oEuz0gyOyMoE1HUAh9BMNt5P7XQvfUsw%2B8MiT%2B7M7t6PhzQx4scerPxGxbBI9UcMxpBmbwFk9aFEVRTFcUJSNEC4IQJDCVwM1iczqwIJgTBYIky6kDJkjHK8ACcxxOpIClmJIgQmUEA96RwBmkEZImvIEXCBFpA9aav/iKf4Q/BIXzWWbYNnN/ZC0uYtbntV562bRNgVsJwTQsPDTphUwlzIAYRjxQPrxcPJZK%2BBUp4HSqBUW2VhbSFFoVCWJVdDJEqtVa6ud84Hwsm1DyFxLhdWeMQF%2Bb8P5fyhr/f%2B8lRqoHGgkYSKxZrM0cktShK0JreQ2kwraz9X5hWIUYLgA8uBDn2odY6p0Sq3UuvzcR91HrPQcPzd6jACBfR%2Bk1f6gNgbZn5hDBm2x2L4FuAjJGJUUbIDRvzTGXQmq43xpdImujZq0nJqJKmNNMB00hkYRmoAz58DZgoDmXMeZ8wphAoWuVoGyFgcVdiCDpZM11lYeW1ilbd1Vj0DWWsdZywsAbIuRtQEm27gHHoltra5A9iEK2qcnae3SK7bIocKleyyNUv2ZtI5BwTo0pOEdA69Gjg7WOScunlOGf0Vp6c1hZ1yqgxqJVi6cMIZ/b%2BwBSEAJNDXYB9cpqNzoWfVu7dO6UFzvPRef8FJOl3k6ZSkhx6RVAugzgVkT5zQck5Vy7kOqsLvgFIKT98H9RYAoeGcV4Z8NeGWGYQC65pQyrISB4SBZRMliAY4pAkE1TBrMguTUMHX06t1Z%2BgLgWgvBZC6EEAxrMOoVNY4TdXkLUYVQtaPl2ETRACClIKRDRgoHoaclREAXQLoMIygoj2JSN%2BqJSVMiXryMoR9JR31fp6MwADIGYhNEU20Z4%2BxpB9GR0RqDdiJizEUwsdjdi1iCYojsSTRx/MXHpDcfTTxERvHzV8UwdmnNua81YqJUJOUJARIKuLaJOhUVxOMNkhWsQUkqzVpOTgHItayz1pYXJHF8lYATe0vppTE6gXtmUIZtSihZCLakOp3tBlpx6ebTp/Qq3FKjuMutNSxjNu6fHdtpb62NymYJHOs80G4s4HglgxKQWXF5RCg8EpsS11Sg3elLdSBtw7iMbu2NTlJD/scY4/g1KKRMoep0a8cXzKecfWy67e7%2BEHv4LSP4B6SAHspYeXA0XY2OHM8yN6GW5ySlegDR8gOUwSBkZwkggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/concepts/all_falsify.hpp)
- [unit test](../../../../tests/unit/concepts/varybivore/all_falsify.test.hpp)
