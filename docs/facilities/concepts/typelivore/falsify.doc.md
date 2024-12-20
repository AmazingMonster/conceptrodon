<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Falsify`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-falsify">To Index</a></p>

## Description

`Typelivore::Falsify` accepts a callable type predicate and a list of variables.
It returns true if the predicate invoked by the variables returns false and returns false if otherwise.

<pre><code>   Pred, Vs...
-> not Pred{}(Vs...)</code></pre>

## Structure

```C++
template<typename, auto...>
concept Falsify = REQUIREMENT;
```

## Examples

`Falsify` turns a callable type predicate into a concept so that it can be used for subsumption.

Since `(not Pred_0{}(***))` and `(not Pred_0{}(***)) && (not Pred_1{}(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return false;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return false;});

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<auto...Args>
requires (not Pred_0{}(Args...))
constexpr bool fun(){return false;}

template<auto...Args>
requires (not Pred_0{}(Args...)) && (not Pred_1{}(Args...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BQQAOqAqETgwe3r6JpClpjgJhEdEscQmBtpj2hQxCBEzEBFk%2BfpV2mA4Z9Y0ExVGx8bkKDU0tOe2jfeEDZUOBAJS2qF7EyOwcAPQAVLvbANTKxJjoAPoa%2B3vbmyYaAIJeaUaHx2cXJgDMACL7WMi0BAAnklMBATAErAEvhAmF4iAA6RELEwAdgsxwIqwY%2ByoYiUnysKK%2ByI%2BVnutzuOz2LxOpy4lz2N3uj3CwBpZ3pnx%2BfwBwNB4Mh0NhCKRqPRmExxGxuNo%2BNJqOJBIpFKpu32ADUmICGbsmXcCJgWEkDAbPm5hah9gBJT7YCkjYheBwarXKtEU/ae/YjJiOZD7NAMEaYVRJYj7C37ABuYi8mH2YptRKV5OT8vJ91VByoXmxVz1BqNJswZotiPhd2IwAUtopxwAjl48McFPsIAxUAR2ecxQqIJXq%2BWFsj7oHg6HwzFUJ4cbmIMi0RisTi8SX5cmM/rDcbfWvzXDUOWBzWPnb7g2my22x2u0daRpe0T%2B1WFEOFgmzAA2cyf6%2Bd7tcI%2B0LHm%2BFJjgaE77FOM45gw85ikuUr7AQjproSXzKpmVz7AAKpgIw6tcKqbPs2DEMQJD2g0fqnEwChKE01C5magGnvOJIWBwSy0JwAS8H4HBaKQqCcG41jWN6KxrPG5gfDwpAEJoXFLAA1iAASfvCAAcn5SAEKKfpIACcHwGWYHz6Jwki8CwEgaBopACUJIkcLwCggA5imCVxpBwLAMCICAKwEEkcLkJQaBGnQ8SRKwGyqDpAC0hn7MAyD%2BlI8JmLwJyECQeDoHo/CCCIYjsFIMiCIoKjqN5pC6FwpAAO7EEwSScDw3G8fxSnCZwADycKhV2qBUPsCWfslkipel%2ByZWYbYeFF9DhrJXALLwXlaEsEBIJFSTRWQFAQPth0gMAUhmHwdAGsQ7kQDEvUxOEjSAh1vDPcwxCAv1MTaJ0XnyZFbCCP1DC0G9dVYDEXjAOatCyu9pBYCwhjAOIUPNgDeBRvhvUhp0cIbPJ4QGjxdW0HgMStd9HhYL1KF4LZ3C8LjxBTkoXyGmjlNGEpSxUAY1bqngmBNf1IICfJxXCKI4gVTL1VqL1DX6GjKDiZY%2BhU%2B5kBLKgSS1O5HCJSM6BcqYljWGYzls8QBV43rVQ1BkLgMO4nitHooQzKU5R6Pk6QCOMfiNYHtT9H7QyNR0XQCD0YyezkMfVNj8dTJHgwJDHUwh3oPpNJnczZ0sChSesEhdRwfGOb1LnjUlKVpRlkhZW2uB5at5nrZt/NLAgmBMFgCTzqQamSB88ImSikgaJIZiSJ%2B9kaUZlkcNZpC2R8Zjwh8n4olpHxaQEARcKZRlabXdUuW5HkKfzvkBbtQVDWFx2nStsVsJwE1TQGBjPC4EZeEXB4RCVykQe2hVGoy1KvLaQislDKzqroK6LU2rvSrjXJyvAXKDRCnCfYo0G6TRSv8NGc1gGgIuBAJaB0Vofm3hte%2B3kdp7VQMteI4UTocPoUMchRggFcAcjQAE8R7qPTqp9V6SNpHfV%2Bv9BwSNgaMAIGDCGvVoaw3hojFmyNuZGAxkJfAxwui42NuA1QhMDRI1JtUXqlNqavTphsISjNmbyTZhzTAXNUaGNZA/QWTBhai3FpLJGsC5blQQbIJWtUhKoLVnzS2VgtaON1qPA2RtOCmwIObb4KTra23iFAx2o9Y61Ddh7bIodgjuyLv7MOqQg6ZCTrU8OGQGnR2dmnOouc2n51TnHPpvQunZ1sP0mp%2BcM6%2ByzpXZYqwK7rTXtguunASF/wEWyIBICwHt3wJAxhPcWHbX7oPYelBVJ2QcuTDeW8AjwmMgEIyZgXlfi0mfQyV9nKcFvp5B%2BflArBWGtwj%2BMU4qcEaCwFKLAFBRn9FGHZxYRg5QOflaBlVZZlQkDEqqSD4k6BABZdB7UWZYJ6tfAar8RpjVUDCuFCKkW7gIrQ3hh1GEfGYVtHyz8wVHQimylaIB4VJCSKcRFRlTjIoIKcOlCCbriMoJIoScjIbyVVQogGyiOEgzUeDSGxjMAwzhmIXR8kUY81cbwEx2NzH4yscgImtjBD2IplTGmgIXEM3th41m8RvG%2BJ5gE1hfAhYKBFmLCWjAImyDgdEzFcSVZEqScYTWNh0nwH1obDIxtNhmw1lbSwNtcF2wdhk0uQzKkQFcHnRqPsShzKaQUDIta8jNIjrM4ugyXbp16K2ip3QZkNq7TnPtAzR2F07Y00u5dyrku%2Bbg9Zcr9iwvhdGJlBoWUd0OWtLlfdSADyHkMUetybJEp3p88yZhr1cC0hoT8zyF19VcrYO%2B3LhxjxABPEBR8Ajzw%2BAEe95kDJrw%2BBSn5L731V2yk%2Bm%2BJzlKkDZmkZwkggA)

By turning `(not Pred_0{}(***))` and `(not Pred_1{}(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires Falsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires Falsify<Pred_0, Args...> && Falsify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<typename Predicate, auto...Variables>
concept Falsify = not Predicate{}(Variables...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQgAMxBAA6oCoRODB7evv6p6ZkCYRHRLHEJybaY9o4CQgRMxAQ5Pn6B1bVZDU0EJVGx8UlBCo3NrXkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLCn0bIJMdQxX%2Byfnl0c/R59npzOBEw9wMwJMiTcBAAnilGKxMFdlMRMPhRMDSFcmF4iAA6fEANSaeCYMXoCgh2EBaAY6xSBCuADExBkqNCrhCACJXBioBnI1F4dGYEwAdisos5ECJxBJZMwCnxuIWEKs50B31%2Bxw1%2ByuABUFQQFO9tV8tQd/jrrgL0AB9DQm3b/LwZIxIlF2h1cq5YZC0GFwiAmAJWAJS7F4/Eq8UogirN5UFkixISzkqlOAq27d2o21cR3bZ2u4A5u3572%2B/2wzBBkPB8M41BK6MWWPxq6J2hKVVitM99Vm65E9kfQHA0EvZNuCOoW6UwGjYheBxXYeZ8WAq5bq7TRzIK400aYVQpYhYxtXABuYi8iLFFhuvf7AMlz6z2w7Xjeo/O44ek4hadGyVM5iGAClEipc4UQARy8PAUWNZkuzwNlAJte1MVA8ClXnc5D2BE8zxiVBPE/BgIBbNtiATJMe1fAcgRBf9wUhGcQLAiCoNAzA4IQhUmRZVDoXQj1MKubDFXxSkOTMAA2cw5MElC0MhDCuCwzjcMg6kBCPIirhIsiqC/Sj72ot4CCXZNU0zQdswNUYC3%2BXchVtJgFCUZpqC/QCuEpSj0wsDglloTgAl4PwOC0UhUE4NxrGsHcVjWO8zESHhSAITQQqWABrEAAjk3EAA45KkAJRTkyQAE5Eiq9L9E4SReBYCQNA0UgopiuKOF4BQQE67LopC0g4FgGBEBAFYCBSHFyEoNB7joeJIgRThVDKgBaaqrmAZB9ykXEzF4QUiFldA9H4QQRDEdgpBkQRFBUdQRtIXQNIAd2IJgUk4HhQvCyKctizgAHkcTmhlUCoK5NrknbJD2g6riOswrggDxlvoM9zAyhZeGGrQlggJAlpSFayAoCBycpkBgCkMw%2BDoYFiAGiAYhBmJwiaaF/t4bnmGIaEwZibRMAcfnSCWp4CDBhhaD5t6sBiLxgGnWguylrAWEMYBxGV/iHDwS8FRB48JZxDZMvCYEwre2g8BiH7hY8LAQasvA2u4XhTeIEilE5EE9cdowcqWKgDHAgk8EwT6wbhKLMuu4RRHEB6U%2BetQQY%2B/Q9ZQRLLH0J2BsgJZUHpLIBo4LbRnQLlTEsawzB6v2LrNsvOgl14XAYdxPDaPRQnCAZyiGDS0gyV4Jj8CfCleWZBgSDS7G77oxhaAe8hXmo1/qDfF7H5fbA3me9GmZpD/mLglgUFL1gkQGOAirqQd6uHtt2/bDskY6MdwQgJBZL40JuHJYCBMBMCwAkSipACqSESLiOqopJAaEkGYSQckOpFRqk1DgLVSBtUSGYXEiQ5KihKokEqAQAhcHqjVEqr83q9X6oNLK4cxqTVJtNSG81qa0xxmtNgG1P5Iz9HrVGNVcRcFxDFM6JA8CXQ0inW66dpCZyUNnN6ugmbfV%2BvzJ%2BL9uq8F6hDWaOIrgww/gjXa4i3RcCkTIh0mNUDY3iMAswBN2EjRJmTVxFMcYLRpv4umdiGY1S4J1Gg/p4js05m9QWvMpaJOFqLcWksfbS1cbLeWisQYqzVhrLWmSdYhw2DFfAKJjam2rnI1QltgRS1tjUEGjtna8zduUwmspvaZT9gHTAQddZGFDqAHxfAo4KBjnHBOjApYqLTvddRsgs6vRijovOYdG5WCLm00usCK6vGrrXAg9dEicm2c3Vu8R277NvrvY2zgICuDPhpYepQl56EnkUbIW9Z6kG%2BQvEecxx5d0eQwHo4w/nnwea8SFfRgWfJXqfaFyKZiIqPo/ZYqwH43zwUYt%2BnBrGIwPAYexjjZH/3wOdYBN9QE%2BPAZA6BlB8rtU6vbAhRCAi4lqgEGqZh%2BXyRKnQ6qTCeqcFYUNDh40pozShkEgRq11ocCaCwXaLAFCXn3JeBxuIwSGlOtShRSjHqpzuhIZZT1NFrJ0EkUgei/o%2B0McDZh4NeHQ1hqodVmrtW6v1U5FxbjcbpUSF4omo1uGKqpotEJOMQBapSCkW0Oqaq2n9QQW0Xr1Es1iZQeJMUUlK0yoWtJ3cpYy0YHLBWSsKmYFVurMQxTMqlJGV00glS141PNvU5AVsmmCBaQ7J2LtoSdI9j0qW/T0iDODiM8IYziYTKYNHWO8dE7zNkKopZprVk5ztWS4whcbB7PgOXSuelOCbDrgXJulgW4mLboojusDV7gt7v3XI/z3mj2vgC%2BeWRXl/qnlkK%2BoLX1wpRZ%2BmFXR97oo%2BZitFUKoOIYRfB6%2Bt9773WdWKkxRKs1XA1Vqq8frJwBoATSvGdLvHE0ZVAoYsCOWtSSCQkV6UzDsa4CVDQck%2BU4dBn1WwbDw0LFZQg6RVCAjoOSNx9KVU8GJBdeKgTwmn4nT4yw6juVSB%2BwyM4SQQA%3D)

## Links

- [Source code](../../../../conceptrodon/typelivore/concepts/falsify.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/falsify.test.hpp)
- [Example](../../../code/facilities/concepts/typelivore/falsify/implementation.hpp)
