<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsSame`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-same">To Index</a></p>

## Description

`Varybivore::IsSame` accepts a target and a list of variables.
It returns true if the target is the same as every variable;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target same as V<sub>0</sub>) && (Target same as V<sub>1</sub>) && ... && (Target same as V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsSame :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct IsSame
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsSame_v
{RESULT};
```

## Examples

```C++
static_assert(IsSame<1, 1, 1, 1>::value);
static_assert(! IsSame<1, 1.0, 1>::value);
```

## Implementation

We will implement `IsSame` using `Varybivore::SolitaryIsSame`.

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsSame
{
    static constexpr bool value
    {(...&&SolitaryIsSame<Variables, Target>::value)};
};

template<auto Target, auto...Variables>
constexpr bool IsSame_v
{(...&&SolitaryIsSame<Variables, Target>::value)};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgZgDspAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1EKehC0AngCSCkKsmIcHu9smGgCCBJgsqQYfJgFuTC8RFIh0BRD%2B2Ber3GxC8DmOpwmVxudyhJiSFkOs0cyEOaAY40wqlSxEOMVQnkOADcxF57uiLFQxEp0QARP6YtkctFvD5fH6YP4AoGoQ4ANRaeCYMXoEKhMLhBARtDOxGRtzYQolxClMswIO1utlAUhbwZWOaOLxAkJxNJ5MpNO89IxBFhgqS7ICnM93LNbz2B2VqvVdweB2evM%2B3yYv3%2BYNFABUWsBMAQQQmAHTZw3S%2BgKOVvBXw64awVmjFQw7Vi2xvC4/G2klkim0am08uvGuHBkQbOZ8wANiHJxVSNLqP%2Bub1ChByeIqYIEJAICddKWXO9aN9W/972jAqFCcO88XGZF/en%2BcLr0bHztLcpE7YAH0qduLH3s0OR4iLs/BSnSU80wWcTxTNNl1XDsNx3Kw90DR4kMeSNXkQo5E1AggFHDfZUPQ5CkNQ%2BVLXrF8mAUJRWggAChS4EF6MORiuCgtdMA3XdoVI5ByMo%2BICAgMAwEOWj/mYzMNAY1iYI5DgVloTgAFZeD8DgtFIVBODcaxrCxNYNnpMwAh4UgCE0OSVgAaxARSzEzJIzEkAAOJzFI0ABOWyNEHJyggUjhJF4FgJA0STVPUzSOF4BQQEksy1Lk0g4FgGBEBANYCFSIFyEoNAvjoeJIjuThVCcwcAFpB0kQ5gGQXEpEzMxeEwfAiB1dA9H4QQRDEdgpBkQRFBUdQEtIXR6IAd2IJhUk4Hh5KUlTzI0zgAHkgSypVUCoQ5SoqqqarqpjJEaw4IA8fL6FJcxjKWXh4q0FYICQPLUgKsgKAgV73pAYApDMPg6A%2BYgYogGJlpicILjm3hIeYNVVpibRMAcGHSDythBFWhhaHOZasBiLxgABWhaBi7heCwFhDGAcRRvwYgUccKlQOWokUaBLYTPCD5/PUlUYmmtUPCwZa3TwYKKdIFniHJJRWU%2BGmVSMcyVioAxgAUMU8EwCbVtSRg0a64RRHEfrjaGtRlvG/QaZQHTLH0PAYhiyAVlQVIGnJ8rxnQP5WVMSxrDMCKZfa1m3e6JnshcBh3E8Do9FCcIhkqEZ6KKLIBCmPwM4yLOGHmYYEnouxo4EPpJgT/JS7qcvGgmAYU4WdPbEbnO9FmVoi7TkuVgUfTNgkBaOGU0hwt4SLdrKyrqtq%2BqTrMM7cEIEgeyMrg7tM1WVgQTAmCwBIICsgpM3cgIkkkDRJEcwdQsUwd3P0ThAtIYLjMzQcuB89ynO/xTJBcEUufQc49lqRWirFbeCUnqpWeulDa2VPrfSukVNgnAWgsCpEkcqTA8QGCMExdymYuASWaq1EgeAOr0WNj1M20gLZKCtqNXQAMpozRhiPMeE8VocHWplIEhxtqgmIFgnBeDkAEOAEQkhEkzoXTelddeAQzBbweoleBKD4g5S%2BqgS6IxMHYPKpImmXB3JcEkjQWgwNQbg1GnDaGUsHEIyRkzNGGNGAEGxrjfGmBCbEzEGTNGVMlZbHUgzaOLNybqXZsgTmaMeZ1GWgLIW5wRZhPujqSWJkZZy0wAramRhlagBgXwDWWsdZ6wNqpEytDTZ9QYbIS2I11KsNtirQOVhHYC1dsfDSntsje19v7TpwdQ7xHDr0/udcHAxwgK4Du9Fk7lGLnoTODRFlpHzg0Huixa49Aru3auuco6zMOXMZuqzS5HLyCcruTcVm92HqsdYQ9N7P1HktUaU9DHiPwTTGRpCNDLwoddDeaid6kD3gfEYfT/Kv3fsQ6%2BSRgFJCSAEG%2Bkgqr0R4RA2wUD1GwPgPAjKm0dFaOIGgrYmCDosAUFSXEVIzGZgFOMchq92qdVkHQhpA15BMJaToEAQR2GzQplwr5EU1qIK2jtGl1U6UMupMy1lSpzp6MUfEZRAQIWlM0Rq965KDVXVXMgVIqQ3xmJfKq8ioiqqA2sfEWxEMoZqjRs484iNkaoylh4rGOM8b0z8UTEmQSpYhKKRk0gETZlRLZqoDmHwEmCCSaNFJFx0liyyWjXJGR8mKyKeEEpj0ylME1trXW%2BtDZSzqb1CQjTBoCutsK9pxgHY2B6fAd2AybScG2L7e2QdLAh0nmHKhEc%2BllzOX4eZcdNnLNTnsrZxRsibPWdkXZrcp0NErm0Y5ncZk7sbpukubd%2BibPuSe55A9Xl9QlWA75nAREsFpfSxlKrYxYRBRy5Rm97qQuhYfSgI8EWJGIQEAIik3KANChBpIPkH1SqiviuKkLrKSCSI1FFXApDuWRefLgKR/IBElZPTg/6YEjyaohsjyHCUrBlpkZwkggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/is_same.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/is_same.test.hpp)
