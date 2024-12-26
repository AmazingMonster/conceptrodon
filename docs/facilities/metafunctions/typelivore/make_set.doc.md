<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::MakeSet`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-make-set">To Index</a></p>

## Description

`Typelivore::MakeSet` accepts a list of elements and returns a set that:

- contains every element in the list;
- doesn't contain repetitive elements;
- preserves the relative order of the list.

The result will be stored in a `Capsule`.

<pre><code>   Args...
-> Capsule&lt;(make set)&lt;Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
MakeSet
 :: template<typename...>
```

## Structure

```C++
template<typename...>
alias MakeSet = Result;
```

## Examples

We will turn `int, int*, int**, int**` into a set.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = MakeSet<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`MakeSet` is implemented as a special case of `Typelivore::TypicalDiversity`:

```C++
template<typename...Elements>
using MakeSet = TypicalDiversity<>
::ProtoMold<Elements...>
::type;
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsAGykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcBAAni8APoEYhMQgKOHYUGg/77O5uJjpBReejfI7AgiYFjpAw0uEI5GMViYAB0nJxoMmxC8DiJJLJ9DhVmu%2BOOdwAKsi8KJaA88AA3BKlRGUw7U2n0piM%2BFIl7MNic9kASQYCheDkw6Gw9DYgmxgVx115/II0tl8sVKuIapAd3SXlitDld0m6BAIANmBReCwgkIiKZ5stmGttvtjAITuwJrxSTFIL%2BuzuACV05tsirBUoQKC7o27jS6QzMEyY0bMHdU1bHEY7bTs6RmyyuyaK5NBw6c9zrk3w%2Bj3XdlMRUEQALKedANpsmQu7heNrzZIyjl6wwIPReRlACfBNMSHo9M59HpsRqN4BQo2JMJQoqgVCvvO75gY2n7RiycYJo4SIphafYRMA07ZjipBvuBTYyukcpiD6qpJph744lGSpiF4mAjsRR44XhCrKoRSLUaBWGerh3qMX6RHwr26Y0pmQ6OiaI58Q4yGoYIc5XOBpFQS8UYtjqNIrmum7bkyk4EJJOb5s6iksqKz77g8RniiWdwWP%2B3bEnWz5KW2HZjmyPaIfxElZlJzrPm6AqruuqBbrQO68W54kDp5BDSQu%2B5FuBJ7Iee3ZwtekFoAwD65E%2BrEvvCNELpB36/tZgHAXlOVsRBBC3jGMHZjxbhif2KGReh%2BVgXRnG%2Bmq7WNnJ5HeFRsIVWBxKkuS7ahWmGY6QoenYCxMmVWNwqTY1YUCbNImudNzU6dFYFyTGZlLX1SSmYERb2dqjn6s5xqcrNB3HqewB3EF6CXte/nqcFTJbVy3mXQWF1XX8gIQ0CEr3KarZCa0TQauc0OQ5DwKgg5uprZ2bImk93nXAlZ4bkwADWmBCJgHopex9EEdx8F5QTVxRj9gUafCAPstJBkvCdKOo5qAt3NgqisPS3Y/ALgvo%2BK4KQtCyXwul2zpLOzPCytE1I1qrZY05hq44DLpXL5HpayKwPmTckpCF46QlDak7kh6UuE69dx2w7WRO58LtfYK42W24EQECOof7OHgiHNyVvFjb9zO7QrtUqCRNvUn1NXu9ZMU1TTKh1HBCR3cEcl2XsdgwnhzSp8KdC66CNyii/5KO0ECQQobIt06biZyOXuO%2Bgmc4isoocGstCcP4vB%2BBwWikKgnBuNY1jhhsWzJeCPCkAQmgT2spMBJI7IaAAHGYZgAJxX1w/jn2fXBJEk0hTxwki8CwEgaBopBzwvS8OC8AUCAX%2Be954T1IHAWAMBEAgA2AQIMYcKAQDQHSOgCQohsk4KoM%2BKQAC0KRJB3GAMgZAdwpDsjMLwG0hASDxj0PwQQIgxDsCkDIQQigVDqAgaQXQXBSAAHcMTpE4DwSe09Z770XpwAA8l4RBCi7hATuLgghRCSFkIoSfMwdwIAeHQfQYgsJt4rF4OArQawIBIDQbhIx5BKC2IwYkYAUgzB8DoDSP0lBYjSNiBENoiIxG8H8cwYgiJZGxG0PxYJpA0EzlkQwWgQTeFYFiF4YAxJaC0BAdwXgWAWCGGAOIVJeBiDuRVLkhemBVCVhpLE0ODRpGhliBicJHgsDSPRHgL%2BeTSC%2BliD7J4hSjChiMPvNYVADDAAUAANQ%2BII2RhpYlMOEPKNh0hVlcLUNI/h%2BgikoFXpYfQeBYggMgGsVAatci5PwRGFKphLDWDMAA30xB4yfHgGsOw7lnAQFcDMPwAiwgRBGNUMYAiSg5AEICvQUKmiLFGIkARPzxICAGNMTwXQ9CoqaBioYoKlgQtsFMDoWLCgotJYi8FyLvkb22BICRHAZ5/2kYA1ReDCHENIeQyhuiIC4DocY8wgQuBmN3hMtYCBMBMCwIkCAh8QCSECOyK%2BgQX4aEkGYSQKQf7%2BBSFffQnAP6kC/qK9kKQuApDPlfR%2BKR/CSDvmqtI/9eCAOAaAiVECrGwOsfAhRSCHGoNQIYzB2COBtBYEqJI%2BCmB3ChEUihV92RcFPjQh89DIwCNWSw8Q7CtlKB2bw3Q7jhEkmCUyllrqZEcHkYoj0Ki1FcvjQYM8XBk2po0HogxdiEgmMCGYcVFjIF%2BqcfYlBY6xgJqMO2rgv8aDJ1VD4vxATwmxNCYEyJ0SHCxPidmRJyTpFpIyVknJsSClFJKQvfA5TxKVOkTUupOwd6NLfgvFpbTEQdJ2AvbpvSd4DKGbSS9yEJl8GmXMhZSzGArNkLmjZHD5CFp4QvEt%2BzxmPKsMclp5yFWL2uQIW59yryYeea8hI7ysC4e%2BQ0X5fh/kZVhcCjK1LliQqyNCvI5KgUZA4wiwlSKcW0bRc0UlTHeh0fxax4l8xMUFB47JgllRBNivWJsBlqm35VrZZwDl6jiHTreu2lNp89GCqIMK0x5jJWkGlbKsYeG34mrNcmzVSR/BX2foELVOrHWst4e62wnrh0%2BvgH6hBgaJ0ht7cQLBbBOCRo0SwBQSpyFKmM22SY6ahUMOzXB9ZEhNmyG2ShnQIBghltEXkytUiAtyIDUoxtSWUtpYy1jSY3bovOP7YEIdYHR1dfHY4wbYxUsOxROlq%2BKJMsEBRKoIhHjF3eIgL43hG6119PWxEqJMS%2Bl7sEAelJ17MDpMyWIM9fSL2jJ/fkspFTPm8MfcgBRz7eCvuaacz936unvP/bwQDShhkgfGd68DTAZnzMwIs5ZfSc0FfzcV5DuzyvoeMEcmwOGvn4aaLk3Yn5SOWBeW6t5HzqMSZEy4Rj3G9AguUzSuFfHcjifhbkaTyLyd4rE9TlFwnOcLAE/TylgxxOKbZ4ytTm9xdadqwA3T83iHJdS3cSb7IZtmYzZZ0VfXvVSplXKygTLnMgGvuyQIgR/D30dT/M3qQz7%2Bdl0AoLYCbNH0kP4VVT8kg/zPpIW%2BXAL5mDSG/QIMu3WcGszro1HBqH27D47kLaxuq5CVUAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/descend/typelivore/make_set.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/make_set.test.hpp)
