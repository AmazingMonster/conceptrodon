<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyConfess`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-3">To Index</a></p>

## Description

`Varybivore::AnyConfess` accepts a callable predicate and a list of elements.
It returns true if there exists an element whose value result satisfies the predicate and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...||Predicate(Elements::value))</code></pre>

## Structure

```C++
template<auto, typename...>
concept AnyConfess = REQUIREMENT;
```

## Examples

`AnyConfess` turns a fold expression of a callable predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||Pred_0(*))` and `(...||Pred_0(*)) && (...||Pred_1(*))` are both atomic:

```C++
constexpr auto Pred_0 = [](auto...){return true;};

constexpr auto Pred_1 = [](auto...){return true;};

template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (...||Pred_0(Args::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...||Pred_0(Args::value)) && (...||Pred_1(Args::value))
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgCcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BxoDHOYqqnEANRMXkSnysSY6AD6Gqcm/gAiz4FWga8QF0QAdIDViYAOwWW4ELYMU4EYheTAvKwg16IkwaACCaPR%2B0OxzOf1Q11uDy4zzeHy%2BPwJgP%2BwLBEKhMLhCP8SJRrKxWIImBYqQM3JebgJpwAki9sFi5nCHKcALICVBEBgAT05YKxp01pzmTEcyFOOO5ePOl0JADcxPDnmCxcjURjQeyrA6MdzefyWW4CMrUoxWJgaejiMAFOKsbcAI5ePC3BSnCA00FuJM3O6PCBBkMgEAW7yYVbAjGGo4nU6xVCeU5ULwMCB08GYSHEaFUMRKVF2l3ot183We72%2B5hsQPB0P%2BCUYyPR2MJwFJlPE9OZhTZ3PwgvPMwANnMW/jiZBycPqZJGdHq8t%2BcL2IEuNL5cr1dr9YZzaZ8I7KK7Or19yYCiUVpqBrQV5QYRUBFVfw3C4MNxzrYFWQ4dZaE4QJeD8DgtFIVBOGTSxrG1TZtkwTd/B4UgCE0ZD1gAaxAQIt3%2BAAOLcpECEEt0kJJ/E4sx/H0ThJF4FgJA0DRSEw7DcI4XgVwkqisOQ0g4FgGBEBATYCFSS5yEoNBeToBIon9ThVFYgBaLjTmAZB9Skf4zF4O5CBIPB0D0fhBBEMR2CkGRBEUFR1CU0hdC4UgAHdiCYVJOB4FC0Iw6icM4AB5S4dIIU5UCoU5zK3KzJBsuzTgcsx4w8Qz6DOcxyNWXhFK0dYICQAzUiMsgKAgdrOpAYApDMPg6G5YgVwgWIUtiCIWmVeLeGm5hiGVNLYm0epFIogy2EENKGFoObQqwWIvGAIVaFoFduF4LAWEMYBxCOmMNrwM1MCu7CjnqS5dgoiJuVQ0LaDwWIYuWjwsBS2E8FE67SDe4hyyUV4eXu4GjGo9YqAMEMADU8EwSK0sHeaAuEURxH8rz5CUNQUvC/R7pQaxrH0EGV0gdZUFSPorosuZ0BeV5TAIywzGkhHiHc974HWOoGmcCBXGmPwIrCRYKiqPQiiyAQVe1jJdYYYZNZWbpekaeZ9Yi%2BW%2BgGVoTdGaoJkGa2XYdjWnYkOXiJ2b3BI4dDJJSmT8ss6zbPsyRHPjXBXNq/iuAayjMfWBBMCYLBEjrUh6Mkfx/h4kFJA0SQzEkLdxMYlJAeE0hRPI/42K3ZikmYrgt0CSQuECHit2D0KZLkkAFMxlT1NazTMt07repqky2E4FoWDNEELKYA0DCMMqkn%2BLh/k%2B/AiCljyIupnzKekamgrp0LdCG6LYvmxLA%2BSwf0un7LcvOYgV7XjfkBb2ADvPeB9KqoGqgkMiZhk5NWUpPOeCQ9I9QgR1GqIBl6rwsoA%2B6NQuASRoLQUa41JqhUWrNUm5DlqrXWg4Um21GAED2gdFKx1TrnUuqTW6aNdjYXwLcBob0PrOVUN9bkpN/o9BSsDUGs0Ia8MalLWGFEEZI0wCjO6Rh0agCUljHGCh8aE2JowUm58KZ%2BSvrIG%2BIVsL30ZhjEWVhLBs1iBzHO3NeacH5gQQWbxHHWHFrwVAktpZuLlj0F6itlaeA6HodW5QvYRR1n0N2yTsiO2WM7W2ltXYxPyDbCJCt%2BjzAyVrG2Vs8mq3dgsBJmT/YKF9n5F%2BQcpJBM4D/P%2B69N73RAfvJ4EA47HzIknRqqdSDp0zmMHOtcRIBF3qXEEvcQQgn8GXCu3cB7SU4MPUeujx7wEnlpLKyDEHEAXrsZe1kWAKDNPqM0NR/gejmM5I%2BblT5kwvhYsm1j6YBCijFOK11mlvy2RwDK2lLg5Typc4q1zbmnHubvJ52UIBVTQVAuq/hYFjwQagzqJy8XoNuakVI9xEX3GRX%2BX%2BXFhpEISCQqaM1lqUKZStNaG16EQJ2kw/ah0%2BGYBOmdMQnC4bcK0Qo0g/CXpCJSl9ZAP0JGCCkUDEGYNlTyKhko0mqiMjqNRloiIOjmp8H0YYomJM4ZmN8hISxgVaY2J0H8oBzNRY2BkWEnCPNshXQAPQCxdU4iwgScIhKwB67JUSGDuEqXEqNpSzZpL1jGpJhs%2BjxqyYUu2FS8hVIjcUwY6a9A6imMm6phak4bC2H7CtgMWkh3aTC04cK7kPORbHV5Cd6qjN0WnDOWdKAvzrqJMwu9/BBECKXfBGgx2cWYpstpslbAjxTj23OIB85738MxLu/EJ1bn4pxAO/gQULu7c1F%2BTl52pUXXAgs8N6XZHXUAA)

By turning `(...||Pred_0(*))` and `(...||Pred_1(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AnyConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyConfess<Pred_0, Args...> && AnyConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept AnyConfess = (...||Predicate(Elements::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGE6a4AMngMmAByPgBGmMR6AA6oCoRODB7evv6kCUmOAsGhESzRsVy2mPa5DEIETMQEaT5%2BUmUVKdW1BPnhUTF6CjV1DRnN/R1dhcUSAJS2qF7EyOwcBJgscQYrJgDMbkxeRADUysSY%2BKIrpAcEAJ5xjKyYAHTP2PRsggrb2CYaAIJoDEWcQIB1%2BDGuHgYVEwCgUB22ABEDhBno8TAB2NwYtzHU54c6YCCvVaMAgKEAgABuYi8mCmU22Vj%2BP1%2BAHoAFScrncnmslkcrkHAAqMLJB25fL%2BAp5Ms5kt%2BLIB/UwqjixAOe0OuPQAH0NPCtkiTABWKzGhEQTWoVEM9EWE4EeYMK7EWmMjEI93Mv5Klaq9VWo4nXVcA1G00mi1Wm0Y%2B2YR3EZ0EV2Yd3oz1bJkKv4rNYbVM7QMASS%2BLP6rocBwAsgJUERwSzYyyDi2DqNHMgDr6VWqNftUAdqd5MPC7SX016FRPM42c6t1kxNjsbndmGxUb9iMBPltvn8TgBHLx4E5wsEQgTQ2HbHHBvWXTfb1Gln0CZX%2Bg6RVCeA5ULwMCBbTjBNnSoMQlDTT1vV%2BXMFyXNwV3uddnkfHc903TAjxPGFQXBSErx3W9TnvUEtwUZ9d3hMwADZzGo3CLyhGFCO1HVSlIp9nhff43z9Xsvx/P8AKAh0nRdN0ZwnaD23xHUmFhGICGof8bxrBg6wEa4by4Utd0AhlMw4GZaE4Y1eD8DgtFIVBOCxSxrDbOYFhHcwth4UgCE0IyZgAaxAY1JEeDRJC4dEtg0Y0NBo6izAADli/ROEkXgWAkDQNFICyrJsjheHJDLPMsozSDgWAYEQEA5gIOJ9nISg0DWOgYjCB5OFUWLqIAWmoyQDmAZBOykR4zF4PEiGIPB0D0fhBBEMR2GaGb5CUNQvNIXRSgAd2IJg4k4HhjNM8y1pygB5fYapBVAqAOdqup6vqBoOIazGRDxGvodVXK4KZeEKrQZggJAGriJqyAoCAQbBkBgCkMw%2BDoFZiHJCBIjWyIQlqa59t4DHmGIa5TsibRMAcHHSAa94CFOhhaGxorSCwSIvGAXZaFocluF4LAWEMYBxAZ/ATgcPBKRhNaVVJ/YlnckIVhMhnaDwSIdoJjwsDW5M8FSrnSDF4gvyUBFVj5pWjC8mYqAMbcADU8EwTbTtXcmlrm8RFtkRQVHUBmNv0PmUGsax9GV8lIBmVBgRSTnOv6dBEVMezLDMbL9YmrAw8AlpScqFwGHcTxGj0IIQm6IpelKbJkgEIYmiyRJq4YcYehKbORYEdpBkL4Y28qTvOlLiYK9sAZ6m7uvRjqZvy5KGYFCcxZpkSjgzMyk7OFujrut6/rBsC16iXwcaqLc36PItmYEEwJgsFiLO/MkLZHgATi2dFJGCsxJGo9LjWo5/l7JVIKlNyjxqJcGorFZ%2BsUIEBS4MaV%2B1E14MxynlEABULYlXKkDSqF1aoQyhp9FqbBOC1BYJSdEnUmBdgMEYZ6z9HhcCCqNI%2BJBJrTVkG7Ba0glpe1Wr7EA8Ntq7RxodFex0UGcHOtVfYBxroamIOQyh1DkC0OAPQxhQU3qoA%2BjEE%2BZgz7/WKjgwhMQ6qQx0aDT6IAyEUM6qovmXBn5cAyjQWgSMUZowZnjLG5MfEEyJiTMmutKakhpnTNaTMWZsw5uTHmpslhWSFjnUW4sGaS2QNLcmctyhrSVirLG6tEl/Qmjrdy%2BtDaYGNrzIwZtQBFUttbBQdsHZO0YC7Thoh3Y8M9itH2VldDwzUYHJONh8mZwjlHN8nBY4EHjoaROVhk6pxiOncW4de4pDzgXdIdcS4FBbvEBulRa5HJyCkaekxSh2BSR3UepzrnlFuVUUelzh6TzHrsvorzB6HJ%2BrMeYi9/kK1XllXgOUFFKKoTQvmGimH6kPoQEgJ8fp/QvqQK%2BN9ehZwVkAkBDDgrogQeiMKkgv49VKGC6ynA0EYIaVg%2BAOCqqXXMaY4gxClhkIeiwBQlJOyUicY8fM/QWFIvThw2aXTuEyEEHw/pOgQBbFIMIvaXMxGgvXhwaRl05E3S5b1HlfLByCuFSCCA70rF6NclsQxmCTGWLBqyh11i%2BVxDiDqAVz8dSmrkoonqCN3ExE8ejTGBM/GhsJsTHO5NQmCHCfTJJmBmaszELE3W8TanFMZthEWYtOZWQyVk3WOSFZWXyarC8GsGZazKbwCpiQqkm1qSEepAM%2BBNJaY7Z2utXZSsyLwvpa1dBKuGYs4O4z4CTMqJzVkccRlLIsCncFadJrrKzjc9ufgICuAeaQfZZcrn13OTXceZzG5vNbhuvu9zT2PNaHcsYvyZ7fI6Luj5F6l7z0BQtdVEjsob31QcQ1/KTWLlFMiXAYqUW2oaZfa%2Bt9KBiLxYIhhWwtjGkiiFdKaH0SQOQf%2B3Kth0Hn1g6QB%2BxoX7GlijRZ%2Bkhn5hTflwEdnAth/vBTSkjAMxEjXw%2BxwjRj6R6yDVsyQQA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/concepts/any_confess.hpp)
- [unit test](../../../../tests/unit/concepts/varybivore/any_confess.test.hpp)
