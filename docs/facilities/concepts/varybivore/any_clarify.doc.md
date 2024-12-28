<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyClarify`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-any-clarify">To Index</a></p>

## Description

`Varybivore::AnyClarify` accepts a callable predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Pred, Vars...
-> (...||Pred(Vars))</code></pre>

## Structure

```C++
template<auto, auto...>
concept AnyClarify = REQUIREMENT;
```

## Examples

`AnyClarify` turns a fold expression of a callable predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||Pred_0(***))` and `(...||Pred_0(***)) && (...||Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return true;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return true;};

/**** fun ****/
template<auto...Args>
requires (...||Pred_0(Args))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||Pred_0(Args)) && (...||Pred_1(Args))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSABykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCaAyzmKopxMdMXkSn5yuNxMAGYACLHEwBKwBMEQX5EAB0yJWJgA7BZzgRNgxjgRiF5MKCrGiwcTHk8KQcjgCLpcuLcjg9nq93p9vgjULSrgzQRCoTC4ZzkYjURisTi8QSiSCSWTZRSqXdjlQvLi7syngRMCwUgZtaC3MLkU9iMAFKDsBTzgBHLx4c4KY4QEXotxus50jQQU3mlaolkCNlfY4xVCeFVqiBizGYbHEXFUMRKcmkxXPbW6/Uyo1/VAi30WkFW562%2B2O52utHu6ueoE%2Bs0Kf2QswANnMrcryLdHsB9IbfoDLyD2vZofDtEjDGj6Nj8dx%2BMJqbJzyVNIAKphZozDprdrtjthiMQSBTZkxHMhLkwFEoWtQ1YauJbo6jZRw1rROAFeH4OFpSFQTh3UsaxjgUDYtkwFsQR4UgCE0D81gAaxAAJW0RRJWykAI0VbSQAE4QTwswQX0ThJF4FgJA0DRSD/ACgI4XgFBAOiEP/D9SDgWAYEQEANgIFI/nISg0F1Oh4kiVgdlULCAFp8OOYBkGQY4pERMxeAuQgSDwdA9H4QQRDEdgpBkQRFBUdRONIXQuFIAB3YgmBSTgeE/b9f0QwDOAAeT%2BYSCGOVAqGOOTW0UyRlNU9TJE050PAk%2BhvnMWCVl4DitDWCAkHElJJLICgIHywqQGAKQzD4OhtWIViIBiHyYnCZoAE93N4ZrmGIVq/JibQ6g4uDxLYQQ/IYWh2tsrAYi8YAjVoWhWO4XgsBYQxgHEaaHUGvAADctx8j46j%2BHY4PCbUv1s2g8BiFyeo8LAfPxPBqJW0gDuIMMlDBHUNpuoxELWKgDHNAA1PBMEcvyUkYDqLOEURxHMoz5CUNQfPs/QNpQaxrH0W7WMgNZUBSXplvk2Z0D5UxQMsMxGM%2B4h9MO4muh6LIXAYdxPHaPRQgWcpKj0QpMgEKY/Ac0XeiGIXlnZ3aBH6SZebyBzanqJW5llkYqnGAYJb0c8Wh1pYqjWCDNm2CRPI4H96J8pjwoUpSVLUjSzGdXBdNS0iuAy%2BCgbWBBMCYLAEmjUhUMkEFESItFJA0SQzEkVtaPQgjyI4SjSGokEzEREFWzRRIQUSAIAi4YiCOSBjeCYli2MDzicr43KBMCkTitKlLpLYTgIqi45kAMIx1IIxEuERACdKIZmDIc1GTOR6RUasjHbN0KrnNcjrbftuvfI4AKhL%2BEKwsHpSR428fJ%2BnxLUGS%2BIYLMAOsq49ue/iUSSsfgqUpQKPCqBEuB0RoLQWq9VGq2S6m1eGsCep9QGg4eGI1GAEHGpNHyM05oLSWvDNa/0dgAXwOceoB1loz1UCdbU8MLrdB8jdO6bVHrEMyszN6cFPrfUwL9daRgAagBbnwUGCgIZQxhnDd6S8kZmVXrIdeNkAJb2xoDWmVhLAExiETSOpNyacEpgQam4J1HWAZvXJmLMdEW26IrPwEBXCGwcgLMousRbpDFtkVWktUgeJloLNx6tbGaz6HMJxCsQnK3mK4s2RswneLiQMU2wt/brCtmZfe3lbJO0vtFa%2BY8uATynjcCA3s54wX9plIOpAQ5h1GJHVCoC6JXRznnAIiJCIBAImYbpbZEhV3wg7bJnBG7sSBtxNuSBBJBR/l/YgfcdjNBYEpFgCg9pqT2oUxE2ZZjaXwHPfShlZDLzkQjRRmMQBkR3m5FamShmMX8p3YKoVworLWRsrZOzgoQCSv/Z%2BaUQRv3GZ/P%2BhVZmgoAeslIKRLibIIpcL5lxVCDPAZAyg0CAIIKmnBLFSDBqoMfqNDBE0pokMwLNeaYh8HvUIQIthpBSG7QoUdahyBTp0MEAw66t17qtVYc9Dh8NuHpF4X9AR4QhHZREUwcGkNoawz/HBGRpkJDyMsujJROhLmqOMHjTRTDrGATJlkZauwqa4zphYcxgFLFYENRrXoXMea5B8S4xYKTfFFCyOE6WWRknywdQ0eJLqjbBN6FE/1etjatASerbWATYmpMtlBG2WcD6O04K86Kqz1nHDhdsi8W5vllJIBUoFLdg6h3DpQW2rTLkFwGaRMwzbqgaFbF0%2B59cRm2Cbu/f0UcQAx0nmXAIycQQBDbaRPCWcQRZIecxZu2VbZaU7UfKpFaPrxAyM4SQQA%3D%3D%3D)

By turning `(...||Pred_0(***))` and `(...||Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

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
template<auto Predicate, auto...Variables>
concept AnyClarify = (...||Predicate(Variables));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4mF4iHdlMRMPhRGDSHd4UQAHR4gBqzTwTBi9AUMOwILQDG2KQIdyuDAAnm4DMQ8FQmXcYQARO4QPE4kwAdjcIrcyNReHRmAghPZJLJKxWMKs1xBfwB5w1xzuABVMLMFF9tb8tScgTr7pL0AB9DQmw5A6mzTCqFLELEI1BIlF2h287kBKwBHkQbGoQUq4UWFEETYMO4EYheTCqkU89Pqs3Wv22riO/bOgSu92eiO%2B1H57nQvkmYP1sMRqMi2OYePERPJ1Pp4WZ6Fq4E5w53KheRPfEFgiEfNOw5t4q7EYDk6GU64ogCOXjwKONjJZbI5TJhErzGkxS5XgopVJLYLLdxiqE8o/HEGjbY7iaoYiUvczbNQXBF5Z1PBccSvVd1yXTBt13Q0GWZVkiU5U8bXtS9lwUG8125MwADZzAIpDD1Qk9YQwrgsOvPFb2uF0Hw9J8X1oN8GA/Vs4wTJMUznKw%2BxBK0RwNWZCyBWYPmlW0mAUJQWmocdTy4CkPxVAcODWWhOACXg/A4LRSFQTgxUsaw7gUDYtkwfDoR4UgCE0TS1gAaxAAICJxRICKkAJhQIyQAE5oX8sxoX0ThJF4FgJA0C99MM4yOF4BQQAvRyDM00g4FgGBEBADYCBSBFyEoNBnjoeJIlYHZVG8gBaAK7mAZBkDuKQcTMXgpSIdl0D0fhBBEMR2CkGRBEUFR1Ey0hdGogB3YgmBSTgeC0nS9KcozOAAeQRYr6VQKg7jqgjGskZrWvayROv5DwKvoT1zDslZeAyrQ1ggJBypSSqyAoCAfr%2BkBgCkMw%2BDoMFiFSiAYi2mJwmaJlVt4BHmGIJkdpibQ6gy%2BzyreAgdoYWhkZmrAYi8YA4VoWhUu4XgsBYQxgHEcmEPqAA3Q0trdOoER2ezwjBbSZtoPAYiWjGPCwLbkzwGKGdIbniGfJQeXBFnxaMJy1ioAwV3xPBMHmnaUkYFHxuEURxDGwb5CUNQtrm/QWZQaxrH0CXUsgNZUDpLJ6fq2Z0F5UwzMsMxEpVvqed9roeiyFwGHcTx2j0UIFnKSo9EKTIBCmPxqLz3ohmz0ZqNqeoBH6SY07ySvulxho5jLkYEkruZC70SSWjbpYO7WSzNm2CR1o4XTSAS3gkpOhqmpatqOrMflcEIEhbK4V6HN1tYEEwJgsASD9SDcyRoRxYLhUkDRJDMSQCLijzAoijgotIGLoTMHFoQI4VEmhIkAIAQuAhUCskae21kq2DSjvTKn08pfQKvtEqAMgaPWqmwTgp1zp3GQAYIw7VAo4i4DiQyPUSB4H6tRe2w1bbSHtpNJ2M1dDg0WstFG49J6QKSntIqCI7hHTnmdJq%2BCWZEJIWQu6qAHrxFsmYbe70spIPQfEUqgMZG/UeigAhoNApcAvDQWgUMYZwxmmjJGlsLEYyxjjBwlsCaMCJiTMmhkKZUxpnTS2TMtY7DcRzRw3N6bkNUPzMElthbdC2uLSWSMZZ%2BLeuyRW9kVZq0wBrZmRhtagHgXwA2CgjYmzNhbJWtCbajQYbIJh01DKsNdjrcOVhLBexiD7E%2B/tehBxDmHD2kdo7xFjm0oeTdq5%2BAgK4bu1FM5lHbrndI%2Bdsj1yLqkeZpcs6zMbonGuXclk9xGb0Wu8wZkDx7js3Iyze5HMWDnLe6wR6jS4ZtGas8cGiN0RI0hDoIBr16pvRRu9SD70PqME%2BbkDEXlFu/T%2BAQcRBQCIFMwCLCKJFAQFKeW0kopVgUohB8AkGFQOuo1RxBME7GaCwJqLAFCczapzLgxDISGgIN1fAvUqEDVkHQipVtqnOxAOFdhK0GaPPRc83aKDDrHVUJS6ltL6U4kZWJCA90tFyOetCf5uSVGaL%2BkSnV2iaUpBSLaOlgVbSKoILaaVDDIbxFMfDRGGMrGOsxtjXGDiZGE2JqTLa7jqZiC8UrHxWSEmkHwCiLmPMZp82QALCJggoliwllLFkGBQ3y2SbwVJ6R0mayyeEHJH08lMENsbU25t9L2TKSNCQlSJqOxqTofl9TjC9JsDEoZRkA4lk4LsEO7sI4WCjjPGOVC44nyrr0ZOqdzkZxTv3G5KyihZEmUuhZC6K4J2btsgYq7J0twGBuju4xd27M7oe9ZJzbnD2smPV%2B3CMWcBOjKmldxTUKtnEqn5G9npbzegCoFR9KDjyhfy7%2BqKwpmCg1wRIGgCLwtFYlTgWL0oArPhfUBQC77QgCHBsK/lX7QieUh6BOLx5dUQzPZDcCPprBVhkZwkggA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/concepts/varybivore/any_clarify/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/concepts/any_clarify.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/any_clarify.test.hpp)
