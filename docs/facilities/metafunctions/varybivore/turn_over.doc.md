<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TurnOver`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-turn-over">To Index</a></p>

## Description

`Varybivore::TurnOver` accepts a list of variables and returns a `Shuttle` packed with the previously provided variables but in reversed order.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Shuttle&lt;V<sub>n</sub>, V<sub>n-1</sub>, ..., V<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
TurnOver
 :: template<auto...>
```

## Structure

```C++
template<auto...>
alias TurnOver = RESULT;
```

## Examples

We will turn over `0, 1, 2, 2`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<2, 2, 1, 0>;

/**** Result ****/
using Result = TurnOver<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

`TurnOver` is implemented as a shortcut to `TypicalTurnOver<*>::type`:

```C++
template<auto...Variables>
using TurnOver = TypicalTurnOver<Variables...>::type;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADswQAOqAqETgwe3r4BaRlZAuGRMSzxiSm2mPaOAkIETMQEuT5%2BQTV12Y3NBKXRcQnJwQpNLW35nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpiprozIeJgK1wenF1fHv4df5zOlwO1yECC8BAI9A%2B%2BwBBEwLFSBnhJkCbiYENQADocajsECxsQvA5QeDIfRUVYLkCfjtrthVPCGOgLExkABrGF7AFbLbXADqmGuAHc6LRrl4lNcCAg8O8qF4GA5stLUDS%2BWglUwmdqhTKhaliG8EgA3TDoa6GC1G5BrJQW1J9BRYoHwxHIzCotwEACej2YbBxLsC%2BIuhOJBHpjNcrI51xMSSsSVulKBroRSN1XqB11z0ozHq9GKIQbx12QBgU7yEmAAjl5nphSDm88XsTiAGrNPBMWL0BRpkMEghEkkMpkstnsr01%2BuNr1d4g9vtvUtDofUxMt3NuzMotFtoPnYBGhGMAgDjfnPMSzJGa7KJjAIWo26gusNpWetGL5f9oOkNcx6nmwgjOri65UoCyaptS3wggAKn6eCiLQCFrAwADyZrEFyJzpu6WYHpia6huc4YkkhqQoWI6HEFhOHxluMGBFBBF7t%2B6KYtcABieDEGMeLDqOkZUTRaEYdhCRenxAkEEJm5QTekoRMA0p%2Bi%2BgRvmCEJQpxsmCZBaYsWxFy7oWxFELx/FjIBbbvpq6AKeRI4RtcYmoXRDHSWiBkEIBNaOc5CZKXmKn3r6jzxlppK6RSaKBQI6CAX5QmscZKbpXB5zmURXFWX5dncYlzJFSWOKYfqAnORRonIZ5kk4TJNn%2BQ5SWAZVCAJOBwZkSF263qp6mPANr5RhOsbTmikWMKwQoebRjU%2BW4nXdaRIAgDNzk3htuXwg%2BT6cSVyXWXJaVsSZabwX8N2fDSIIAJLumegjaiqd3Xbdt0AuxFn5e2WK/r2/bOeFaleVJuFjQtEn0ZDC7dsDq4Qdgu0abBgKfV93L3TcDKsEiQofcC2OwldgJmIEEQVl4WDRW4mobKkF7BVjsXkkTZNmQWeWHijwluTpHMY7jeygl4qTpPaABKbxeLQkbE2D4uSxk5qywo8uRmNQt6V6ZiAQb1xcIBGjneTtLXBrWt4QCyvWwr0VvhDTVohogEm9cRtmOb2WWwhbyK1zLlvcgAD6TBVgkBAQGM6AbQoc0R5ebhCBLUvq3LCuAQ78khoslIcMstCcP4vB%2BBwWikKgnBuNY1jXAoqzrC%2BlM8KQBCaEXyzsgEkhYhoAAcZhmAAnKPXD%2BEPg9cEkSTSCXHCSLwLASBo7sV1XNccLwCggO7neV0XpBwLAMCICAqwEKkELkJQaCInQCRRHNnCqIPABsAC0H%2BSNcwDIGQMbfuZheDmkICQPA8cTb8EECIMQ7ApAyEEIoFQ6gj6kF0CbYUxAmCpE4DwYupdy5d2rpwTCEIb6RlQFQa479v6/3/oA4BWIzDXAgB4R%2B9AoZt0WLwQ%2BWhlgQCQA/ai3C74QFEU/RIwApAGxoArbqlBYikNiBEZoPoCG8DUcwYgPpMKxG0JgBwWjSAP1AgQTCDBaCaIwVgWIXhgDoloLQPe3BeBYBYIYYA4g7H8WMY4M0biq6YFUMYiEmx24RHhIvKutA8CxFwXojwWBSEjjwKvdxpAcKxDVvcLxRh4lGC7ssKgBhgAKA7K8YUmF/SmNgcIVCiDpANNQWoUhWD9DeJQPXSw%2BgEl70gMsVAzNshuK/nHV8phLDWDMFvHCS4sCDIgMsOwATsguGZJMPwJswgREGBUYYJspbFByJ4doegTn1AYHMIYiQTZrOVA0cYrRzn5AebUdZzzZj7PmEc2wLztl6BmC0W5hz7mrObhsCQRCOBl1IJvXg286Gfx/n/ABQCpCsPYbgCBPDAhcD4R3EpywupMCwIkFZpBe6SECFiUegR54aEkGYSQH917%2BA/qPfQnBl6kFXgSrEH8uAf0HqPGeH9/CSEngyj%2BCLSHb13vvYlR8hHn2EZfSht8KCSNQFw5%2Br8ODNBYCaJIX8mDlgMPeLgo8sRcAHmA/ARBFl6AafA8QSDWlKHaRg3QBscF4K0bC%2BFiKyEcAodfCE1waEooYX/Cs3jja2vtRodhnCxEJHjJTMwRKBHHw1VI8ROrC3DATUYG1XB3YKPhAJZRqj1F6NMTojRBijEmKyeY88VibGkPsY45xrjTGeO8b4qu%2BAbSBLeKQ0J4T4SmOibUUh8TEkaJSZsKu6TMntxyXkhEI7VIlL4OUyp1TamMHqbId1zTkHyG9egqufqunFOmVYPpy7lnDNGQIcZkytIvtmfMhIiyp1DK6F8vwEBXBAt2cyMFCxjlFGudB0gVzshwf%2BY865vQJhvJ2WBp5DBsP9F%2BXc4FgLcNkZ%2BWUUjhKVhrGhbRxeIaFWcFjWiy1iabV2oHjip1JAs0EtzSS0gZKKWUFhXygVtrmVJH8KPOegQWVsulfKjBirbDKrzWq%2BAGqr5UIkSW4gL82CcGNYwlgCgTRAJNFxj0YxHV4qga6y9TSJAtNkG0%2B9OgQDBADfg9xwaSFqfIVq6htDVDmcs9Z2zuoxhpr1Rm/FgQhOqpPiIhL0iDMZe4SAKzksw42dHmHOzBAw4RZaXQGte8IAqIwc2xtWT6v6MMQE0xnbBDdtsWOzADinFiEHVk4dhT10eP8cqIJ06wm2jnVkhdsTeDLqST6NdaSlxbt4DupQ%2BT93FNS2Up8J7MA1LqVkt1rnPUebvR0nzT7jC9JsO%2B%2BAn7rluK2HHHpMzLBzKRQsqBIGqWYY2ZBrZFGYPoHQ/clDiHsjIdQyUEj4LgWfII0R5DgPvmgoR/BgFfQ0cvIhzCujLdCdMaC1vVj5XrgWas9cQrWISu8bxQJwl/DhOieGFSxekmQBjyxIEQI/gp7SvXvzpIorVPk53hpg%2BwmaX%2BHpbPJI69B6SAnlwYeZg5WL0CGTpFnBWeqthaAiXeupdaeWDhTIzhJBAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/turn_over/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/turn_over.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/turn_over.test.hpp)
