<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AllDeceive`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-all-deceive">To Index</a></p>

## Description

`Typelivore::AllDeceive` accepts a callable type predicate and a list of elements.
It returns true if the predicate evaluates to `false` for the value result of every element and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...&&(not Pred{}(Es::value)))</code></pre>

## Structure

```C++
template<typename, typename...>
concept AllDeceive = REQUIREMENT;
```

## Examples

`AllDeceive` turns a fold expression of a callable type predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&(not Pred_0{}(***)))` and `(...&&(not Pred_0{}(***))) && (...&&(not Pred_1{}(***)))` are both atomic.
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
template<typename...Args>
requires (...&&(not Pred_0{}(Args::value)))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...&&(not Pred_0{}(Args::value))) && (...&&(not Pred_1{}(Args::value)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAgl6ZRsenF1cm/gAih1jItAIAE9UpgICYklYkt8IEwvEQAHRIpYmADsFlOBHWDEOVDESi%2BVlR3xR/isj3uDz2BzeZ3OXGuBzuj2e4WAtIuDK%2Bv3%2BgJBYIhUJhcMRyLRGMwWOIOLxtAJZLRJMJlMp1P2hwAakwgYz9syHgRMCxUgZDV83CLUIcAJJfbCU8bELwOTXalXoymHL2HWaOZCHNAMcaYVSpYiHS2HABuYi8mEO4ttxOVFOTCopjzVRyoXhxN31huNpsw5uBoOYbCRCIexGACjtlNOAEcvHhTgpDhAq%2BYAGy9iAMVAEDmXcWKiA1usgEAx7yYJYLymB4Oh8MxVCeXG5iAo9GY7G4/ElhXJjMGo0mphm/xuMuMViYKuT%2Bv%2Be2PZut9tdpG9/uD4cnHSGhjsSE61go06znGC5LAmZh9vBnbdvBf5DiOXAgTCz6QbG86Lo8y6GquhzrpuOYMDu4r7tKhwEE6x5Et8KqZjchwACqYOMuq3Kq2yHNgxDECQDrNH65xMAoSitNQubmlqQLmhhr52jupIWBwKy0JwSS8H4HBaKQqCcG41jWD6awbPG5j%2BDwpAEJoGkrAA1iASQ9giAAcPZSEkqI9pIACc/h%2BWY/j6Jwki8CwEgaEEekGUZHC8BBQT2fpGmkHAsAwIgIBrAQqTwuQlBoMadDxJED6cKoXkALT%2BYcwDIP6UgImYvBnIQJB4Ogej8IIIhiOwUgyIIigqOo6WkLoXCkAA7sQTCpJwPCadpukOYZnAAPLwoVw6oFQhw1T29WSI1zWHK1Zidh4ZX0OG1lcEsvBpVoKwQEgpWpOVZAUBA32/SAwBSGYfB0IaxAQRAMSbTE4QtECK28PDzDEEC20xNomAOMjpClWwgjbQwtBI1NWAxF4wAWrQcp41gLCGMA4jk22OOOFGnGbSGOPwlstnhIaWlTbQeAxIt6MeFgm10Xg0XcLwnPEOuSjfEaTOi0YDkrFQBh1hqeCYHN23lnj/XCKI4gjeb41qJtM36EzKCmZY%2BhixBkArKgqQNBBHC1eM6DcqYljWGYCVK8QPVc573Ts9kLgMO4ngdHooThEMlQjLNRRZAIUx%2BDnGR5ww8zDAks12PHAh9JMKf5JXdTV40EwDBnCzZ7YrcF3osytGXWcVysCgWZsEhrRwOmkPFvCJcddUNU1LWSG1na4F1j2hc9r3aysCCYEwWAJDupAuZI/gIkFqKSBokhmJIPaxW5AXhRwkWkNF/hmAi/g9qiHn%2BA8kkJIXBgoBQ8tPTaiVkogFStrTKOVPp5T2kVf6gMHqVTYNVBe50ARMyugFBEXAEQGU6kQKOvVZrm0GlbaQNslB2ymroMGC0lrIwnlPGeW0OC7QKvCQ4h156nQang14XBCHEKuBAO6P0HpwS/i9Oy8CkHoPiMVAGqB7ojFESDAKXAgg0EBPEaGsMpqo0Rnjcx6NMbY1xgrfGmjCYEGJqTTaFMqY0zpvYhmGstgGXwKcBweBOZ%2B1IaoXmho8aCzqJtUW4tEZSz8a9KO8tbJKxVpgNWjMjCa1AOlHWesFAGyNibRgZtZA0OGnQ2QttJoGWYY7LWIcrCuziR7E%2B3tfacADgQIOPxmlhwjvEChMcT5VyCc4CArge6zXTuUcuehc4NBmWkYuDQB6LEbj0Gu3d66FzjhMlucx24LMrrsvI%2By%2B5t3mYPceqx1hj2eq/ThUDOBCLOgGAwYiJEkLXvgch8jt5KPyXvA%2BR9KDORikEYW79P5JARIFJIAUzDIvgh5UB/lIFTWgbYWBwL3oIPgEg/K%2B11GqOIJgrYLQWANRYAoKM/ooziIRMWcYHV/ndUoaNC2Q0JDVLGgwupOgAjzUWstBWHCNrYp2igg6R1VC0vpYy5lrLhzSM0bI%2BI8j/CKLehlFRGrfpksNQ9GcyBUipHOEygK5xVXnAVXQiGxjKCmIMlYsmtl3U2PZnjAmjBnEkzJv4zAlNqZiC8bZHxOSkmkACfHEJ3NwnID5lEwQMSRZiwlkCRJMsUl43SRkTJ6sclsngbrJg%2BtDbG1NvY6hlsqnctqfbEVXzjAuxsG0%2BAXsfbZD9tsQOztQ6WHDrPSO0d2nDybocxOycLlpyThszuSzsgrOXaUE5tytnN1rm0PZvcp0NB3YuiuXd%2BgrKuceu5I8HnDUlVihKbyHWHDpQy6MKqrycTVevAFT1dW71IPvQ%2BIwT4wqigEb%2BGLQpmGg1wDyGgexIvvbPTgMC4EgtPiAc%2BRDAFJDvv4JI8HQp%2BVfv4KVD6kr4scq/dqSHuE73Q0rTIzhJBAA%3D%3D%3D)

By turning `(...&&(not Pred_0{}(***)))` and `(...&&(not Pred_1{}(***)))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AllDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllDeceive<Pred_0, Args...> && AllDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<typename Predicate, typename...Elements>
concept AllDeceive = (...&&(not Predicate{}(Elements::value)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBAKykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJn8bgIAE8UoxWJg7spiJh8KIwaQ7vDEcw2AA6YnYV6MAgKaHYEFoBjbFIEO5XWi0AAidUweAAbijoay7hBiYTzAA2UUQBioRlojF4LGYEwAdisitZEFJ4PJChAIC5Yi8mBWRuhVmuIL%2BAPO5uOdwAKphZgovlbfpaTkDrfcZegAPoaZ2HIFeDJGVHo33%2Bvl3LDIWh4zAQEyJKyJNVMLxEIUrJUWdEETYMO5UMRKE1K1nZ/ym4Gur3hn1cAP7IMh4BhjENu5RmNxhEJpMptMZ1BZnN5gtFksKqvlyvVz2HO4ANSYcKbQLBEI%2B07c6aIjypINmxC8DmXq5BOZBdxvd1mHzld1ps0wqhSxDue9Qdz13l5yoecsyzNVVgJrG4bSoLxC2%2BEFNxebdoVhPsCUwIUrmIYBKX8alrnRABHLw8HRJ1mTZDluR3b0/RxDCsKFQ9rmfME3w/GJUE8ItoIgbNlXHYhC2LWhSxnUCzWueDIR3eNUPQzDsNwjDMEI4iHSZFl2W2SikOooImXkhicK7MwxRM9TyK0nkdPrLhaIM4lGKuZjX3fO52M4qCGB4sdMHzATcRPacVVZS9a0Xe1ZnXI8mkcZAfSYBQlBaahoKQlc4SQrhDxwni5w4NZaE4RJeD8DgtFIVBODcaxrDvDYtl5Mx/B4UgCE0fK1gAaxARIRUJAAOEUpESRURUkABOfxRqa/ROEkXgWAkDQglK8rKo4XhtSCNqyvy0g4FgGBEBADYCBSDNyEoNBnjoeJImRThVEGgBaMa7mAZBkDuKRCTMXhZSIYg8HQPR%2BEEEQxHYKQZEERQVHUXbSF0WyAHdiCYFJOB4AqipK9qKs4AB5DNzsZVAqDuJ6RVeyR3s%2B77JF%2BgUPBu%2BgP3MZqVl4HatDWCAkGulJbrICgIEF4WQGAKQzD4OgwWIbUIBifGYnCZo4Sx3hVeYYg4UJmJtDqHaWuut4CEJhhaA1xGsBiLxgF3FltW4XgsBYQxgHEG3VPqHlnfK186gzHYWvCMFCsR2g8BidHdY8LB8YIIHFpd0geWIdilHZd2jCjox2rWKgDCwpc8EwFHCfxTWYeEURxGhsH5CUNR8eR/QPZQGrLH0aPtUgNZUAZLJnee2Z0D5UxLGsMw1vToGsD7niuh6LIXAYdxPHaPRQgWcpKj0QpMgEKY/Fsw/eiGPfRls2p6gEfpJk3vIb%2B6I2GjmS%2BRgSG%2B5hPvR7xaJ/JY381gKHqtsCQOMODFVIKtXg61KYvTeh9L6P0zAClwIQEgxlObcwLmsBAmAmBYASEvbqkh/CEkmoqSQGhJBmEkCKZavVxqzQ4PNUgi1/BmEJP4EUip%2Br%2BH6okRIXAprjX6rA/G61NogG2gXfaR1%2BYnRJhdUW4s2b3TYI9JBtNYwe2%2BuNQkXBCQB3wIDYGoNZAQ3rtIRucMW6I10DLNGGNNZQJgXAgmHBiZnQzHccmiDqZvX0aGLgRiTH%2BggCzIWbMcFmC5q1BRyiNHxEumLVArNRihKluNLgQQaBxniIrZWiNtbq2ruU3W%2BtDYOGrqbckFsrb41tvbR2wlq5uw9l7cq%2BB0S%2BwdPjQOyBg7VzDt0fGUcY7q3jjscqSc8ApxaunTOmBs7dPCKAXahdi4KFLuXSujBq6NxsVDOxsgHEI3Ks49u%2BdJ5WG7lMxeA8h4CBHmPCeXcLAz3gXPYGgz%2B7Lzfs4CArg/62R3mUL%2BB90hH2yE/U%2BqRYUX13tCl%2BK976/wRf/V%2Bd8%2Bgf1RcA/%2BWLciIoAfMKFRKuCgPAVDDxeNEYIKpjTJ8BgwkRNMRg8x2CObUrwdsghRCSGUC6ktIIEcOFcMSISCaiRxpmHlSZfqYixpSMZZwWR8jtmKPgMo06pN0mpOIFonYzQWBvRYAoLkX0uThMJFJWY/1uXzyseDOuZya6XNbgEUgrjMYu3pWqtaRNVFkwpqoC1VqbV2odYyaJmTYnxBwf4RJPM9opITcLQ1ma2a6mQCkFIPpbXjR9LGn0Ea7Fy2KZQUp5UqnWxavWmpRt6mZLNk062vTMB2wdmIDpqcum5zma7H2jg/ZDNUEHMEYzBATMjtHWOcJZmJ2TtXFZ6Q1ngg2fnbVRcmAlzLhXKuqcTnuokOc2Gzcrk6B9Wy4wXye4xGeRVV5DBna7DHp3KelgfkVT%2BQveAoDcW9DXhvUl2915AP3mfZFWRwVIqKFkKD18gV4ofq0bF6LgX4oGMh7%2B4wBjwfJXhyB6xNgQOpWwzx0jOCU0jdan8MbtyRXVM6nBfKkkCtIIQ4howl4SoWgEHhKqmpmDE1wfqGgRRyqDfAjVtg5Gcd5qKihxihGJHodUKTTVRpsP8Ay4NG0lMdTYX9WT3j%2BXKbTsU1ekggA%3D)

## Links

- [Example](../../../code/facilities/concepts/typelivore/all_deceive/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/concepts/all_deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/all_deceive.test.hpp)
