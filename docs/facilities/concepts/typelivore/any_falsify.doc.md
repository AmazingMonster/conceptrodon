<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyFalsify`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-any-falsify">To Index</a></p>

## Description

`Typelivore::AnyFalsify` accepts a callable type predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `false` and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...||(not Pred{}(Vs)))</code></pre>

## Structure

```C++
template<typename, auto...>
concept AnyFalsify = REQUIREMENT;
```

## Examples

`AnyFalsify` turns a fold expression of a callable type predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||(not Pred_0{}(***)))` and `(...||(not Pred_0{}(***))) && (...||(not Pred_1{}(***)))` are both atomic.
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
requires (...||(not Pred_0{}(Args)))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||(not Pred_0{}(Args))) && (...||(not Pred_1{}(Args)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BQQAOqAqETgwe3r6JpClpjgJhEdEscQmBtpj2hQxCBEzEBFk%2BfpV2mA4Z9Y0ExVGx8bkKDU0tOe2jfeEDZUOBAJS2qF7EyOwcAPQAVLvbANTKxJjoAPoa%2B3vbmyYaAIJeaUaHx2cXJgDMACL7WMi0BAAnklMBATAErAEvhAmF4iAA6RELEwAdgsxwIqwY%2ByoYiUnysKK%2ByI%2BVnutzuOz2LxOpy4lz2N3uj3CwBpZ3pnx%2BfwBwNB4Mh0NhCKRqPRmExxGxuNo%2BNJqOJBIpFKpu32ADUmICGbsmXcCJgWEkDAbPm5hah9gBJT7YCkjYheBwarXKtEU/ae/YjJiOZD7NAMEaYVRJYj7C37ABuYi8mH2YptRKV5OT8vJ91VByoXmxVz1BqNJswZotiPhd2IwAUtopxwAjl48McFPsIOXUW5OxAGKgCOzzmKFRBK9WFuOKYHg6HwzFUJ4cbmIMi0RisTi8SX5cmM/rDcbfVvzXDUOXRzWPnb7g2my22x2UV3Hz2%2BwONEOiSOqwpxwsE2YADZzAA%2B9EU7bte37I5aS4D9oXPX9JwEacw32OcFxzBhlzFNcpX2AhHS3QkvmVTMrn2AAVTARh1a4VU2fZsGIYgSHtBo/VOJgFCUJpqFzM1YMvZcSQsDglloTgAl4PwOC0UhUE4LtLGsb0VjWeNzA%2BHhSAITQxKWABrEAAgA%2BEAA4AKkAIUQAyQAE4PhsswPn0ThJF4FgJA0DRSBkuSFI4XgFBAHzdNksTSDgWAYEQEAVgIJI4XISg0CNOh4kiVgNlUCyAFpbP2YBkH9KR4TMXgTkIEg8HQPR%2BEEEQxHYKQZEERQVHUcLSF0LhSAAd2IJgkk4HhxMk6S9PkzgAHk4US/tUCofYcoA/LJEK4r9lKsw2w8NL6HDTSuAWXgwq0JYICQVKknSsgKAga7bpAYApDMPg6ANYhgogGJJpicJGkBEbeH%2B5hiEBaaYm0Towu01K2EEaaGFoIGuqwGIvGAc1aFlYHSCwFhDGAcQ0ebGG8CjajJpDTo4Q2bTwgNCSutoPAYkG8GPCwSaCLwTzuF4SniDnJQvkNInWaMPSlioAxq3VPBMD66aQRk7T6uEURxBajX2rUSaev0ImUGsax9DZ4LICWVAklqYKOFykZ0C5UxlMsMx/KF4gaqpq2qhqDIXAYdxPFaPRQhmUpyj0fJ0gEcY/F62Pan6KOhl6jougEHoxlDnIM%2Bqcns6mVPBgSDOpgTvQfSaUu5nLpYFDU9YJDGjgpN8yaAuWvKCqKkrJDKttcCqw7nOO07paWBBMCYLAEmXUgjMkD54QclFJA0SQzEkADvJMuzXI4dzSE8j4zHhD4AJRMyPjMgIAi4Ry7LMzuuoCoKQp06XIpiy64rmkle6j0DqZTYJwFaa0AwGGeFwOy8IuDwjkpVIg3taq9Q1o1bW0hdZKH1l1XQb0BpDWBm3DufleABVmglOE%2BxFo91WgVf4RMtrwMQRcCAe0boHX/OfE639woXSuqgfa8RkoPREdwoYzCjBwK4D5GgAJ4jfV%2Bl1UGgM8bqPBpDaGDg8bw0YAQJGKNJro0xtjXGAt8biyMCTOS%2BBjhdEpvbZBqhaYGjxozaok1Wbs0BlzDYcleb820kLEWmAxaE1sayH%2BssmDy0VsrVWeNMFa2ajg2QetOpyUIUbKWrsrCWHNjES2i8bZ204I7AgztvgFOsB7ShXsfalMboXLOfgICuCrr1COJQy4x1SHHTIedE55EGSnSO/SC4B2Lr0bp/si51BLpM%2Bu1dK4jLWb0Ou0djrLFWC3XZzNyFd04AwqBMi2RwIQUg4e%2BBUG8IngI8609Z7z0oIZLyPlmYnzPgEeE9kAh2TMECwCZkn62Tfv5Tgn9Qo/yirFeK81xEgIyllTgjQWAFRYAoKM/ooxXOLCMCqdzqroNaprJqEgMltTwdknQIAXLEOGgLMhE134zUAQtJaqgsU4rxQSw8NFOGSNurwj4/CzoRX/iiu6KURUHRALipISRTj4rsqcQlBBTg8pwR9ZRlBVFyS0ajbSxqdEw30SIhGRjkao3sZgDGWMxCWO0gTCWgTeAOPJs46mbjkB008YIbxLM2Yc0BAEnm3sQmC3iOEyJEsYmCL4HLBQCslYq0YCk2QWD0nkqyQbBleTjCmyKb4lp8lbYZHtpsJ2Js3YWAafJJpWBy2Z1qEHEO2RRm9NmDssZBQMjzOThkbZ6cFntJzs0DZ0zFmTtHeXWw6yu2bNrisnZjdm7NVZZCyhpydX7Gxbi6MAqDRCpHvco6Eqp6kBnnPIYi9vkeQZRfcFzkzDvq4GZDQAFAU7qmoFWwX9JXjiXiAFeCC74BG3h8AI37nI2SPh8NlUKAPAbbuVP9H8nn6VIELNIzhJBAA%3D%3D)

By turning `(...||(not Pred_0{}(***)))` and `(...||(not Pred_1{}(***)))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires AnyFalsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AnyFalsify<Pred_0, Args...> && AnyFalsify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<typename Predicate, auto...Variables>
concept AnyFalsify = (...||(not Predicate{}(Variables)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQgAMxBAA6oCoRODB7evv6p6ZkCYRHRLHEJybaY9o4CQgRMxAQ5Pn6B1bVZDU0EJVGx8UlBCo3NrXkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLCn0bIJMdQxX%2Byfnl0c/R59npzOBEw9wMwJMiTcBAAnilGKxMFdlMRMPhRMDSFcmF4iAA6fEANSaeCYMXoCgh2EBaAY6xSBCuZwY0IAYmIMlRoVcIQARK4QfG4kwAdjcIrcEAYqAZyNReHRmBFVmFPIgROIJLJmAUC11EKs50B31%2BxyN%2ByuABVtQQFO9TV8TQd/mbrrL0AB9DR23b/LwZIxIlEer28q5YZC0GFwiAmAJWAKq7F4/ELJUogirN5UdmKxLKnmpvOAl27QOo91cb3bX3%2B4Blj2V0PhyOwzAxuOxxM41CC1PCizpzNXbO0JT6kUF8eGh3XIlcj6A4Ggl65txJ1C3SmA0bELwOK5z4v9wFXU9XaaOZBXGmjTCqFLELHdq4ANzEXkRSpuE6nAJVv5LbZhy8N4F3OJcHhXCE127QUzmIYAKUSKlzhRABHLw8BRW0mVZdk8E5aC3U9TF4MQwUt3OG9gXvR8YlQTxgIYCA%2BwHTAM2ILMc3Hf9pyBEFIPBSF1zghCkJQ%2BDMAwrDtUZZk2VHAjoSIoMSMZMSKOQ7kzAANnMHS5LwxTCMhYiuFIjT8Uos5qLvB8rnoxiqBAli03YocCF3XN82LGdSytUYq3%2BC95XdJgFCUZpqBA6CuEpFjCwsDglloTgAl4PwOC0UhUE4MVLGsc8VjWT8zESHhSAITRkqWABrEAAh03EAA4dKkAJhR0yQAE5Ek6sr9E4SReBYCQNA0UhMuy3KOF4BQQAmqqsuS0g4FgGBEBAFYCBSHFyEoNB7joeJIgRThVFagBaLqrmAZArykXEzF4OUiA1dA9H4QQRDEdgpBkQRFBUdRltIXRzIAd2IJgUk4HgUrSjLqpyzgAHkcV2hlUCoK4Lp067JFu%2B6rkesx%2BQ8I76EfcxyoWXglq0JYICQQ6UmOsgKAgVn2ZAYApDMPg6GBYh5ogGJkZicImmhOHeEl5hiGhVGYm0TAHFl0hDqeAhUYYWgZdBrAYi8YA11oUcNawFhDGAcRDZkhw8BfbVkbvNWcQ2CrwmBVLQdoPAYmhxWPCwZHPLwUbuF4Z3iHopQeRBG3/aMaqlioAxEIJPBMAh1G4UyiqvuEURxH%2BougbUZHwf0G2UGsax9AD%2BbICWVB6SyeaOEu0Z0F5UwCssMxppj96XZbzo1deFwGHcTw2j0UJwgGcohnMtIMleCY/DXwpXlmQYEnMuxJ%2B6MYWjnvIj5qE/6jP/eV8P2wz63vRpmae/5i4JYFGK9YJARjg6VJrIxmrjK6N07oPUkE9fkuBCAkG0rTemqclgIEwEwLACQWKkHqpIRIuJerCkkBoSQZhJA6XGo1bqg0ODDVIKNRIZhcSJB0sKZqiRmoBACFwPq3VmrANBjNOaC1Kqp1WhtZmW0MZ7U5tzKmp02DnXAYTCMNsSbdVxFwXE2VXokDwB9cyRcfql2kOXJQldQa6AFlDGGssAFAKmrwGa6Mdo4iuNjMB%2BMbqqIDFwDRWivQQApmzKmiCzB01EctJmLNUCU3iPtLmsSQlDB8XzbqXAJo0EjPEUW4tQby2lhrApitlaq3VlHTWsTta631sjI2JszYWwqVbJOGxsr4BRI7Z2ncdGqHdsCDW3sajI39oHaWIc2n0w1JHCqMc46YATtbIwydQBRL4BnBQWcc550YBrIxJc/qmNkBXEG2UrE1xTv3KwlhG4xGbtgturxO7dwIL3RIPIrnWCHk4ke%2Bix7YOPo7ZwEBXAv3MovUoB89DryKNkC%2B29SAwr3kvOYq8J5AoYD0cY8LX7XwxVivoKKoVH2fjiklMwiUP3/ssVYf8v40IcSAzgniCbXgML4/x2jYH4Deogr%2ByComoPQZgygdUxoTV9nQhhARcQ9QCN1MwCrdLNR4V1AR01ODCMWmItam1tqYwSXIk6Z0OBNBYDdFgCgXxXhfH43EYJrQvR5XogxANi6/QkEcwG5jTk6CSKQGxsMo72KRoItG0isY41UBaq1Nq7UOsCkEpJ7NEGJAiQzFakijUcwOsmqmIBrUpBSO6W13V3QJoIO6aNpihY5MoHk7KxSDYVSbaUyeGstaMB1nrA27TMDG1NmIJpFUWnLMmaQDpJ9umuz6cgD2gzBDDL9gHIO0IJlh2mRrOZ6QFmJ2WeEVZjN1lMEztnXO%2Bc9myGMYct1Jyq7%2BvZcYeuNzRn3Nbu3AQndNg9zrgPCw3ycq/KwG%2B9FU8QUzzBcEGeH80VIqyJBuDxRKWf1A6fXokHAWvAJTBx%2Bb9z65ARXhnD1Kf60r%2BiG9VTjmXVquJa61r540rkTXA3lNN%2BWRMZkKjBQxsGSpGkkJhqqypmBE1wZqGgdLysoyjWatgREZt1DgkAeDNEcICKQ5IEmyqdRoYkUNGrZMKYAc9aTQiOM1VIDHDIzhJBAA%3D%3D%3D)

## Links

- [Source code](../../../../conceptrodon/typelivore/concepts/any_falsify.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/any_falsify.test.hpp)
- [Example](../../../code/facilities/concepts/typelivore/any_falsify/implementation.hpp)
