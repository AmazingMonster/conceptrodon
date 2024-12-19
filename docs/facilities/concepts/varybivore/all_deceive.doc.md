<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllDeceive`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-3">To Index</a></p>

## Description

`Varybivore::AllDeceive` accepts a callable predicate and a list of elements.
It returns true if the predicate evaluates to `false` for the value result of every element and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...&&(not Predicate(Elements::value)))</code></pre>

## Structure

```C++
template<auto, typename...>
concept AllDeceive = REQUIREMENT;
```

## Examples

`AllDeceive` turns a fold expression of a callable predicate over `&&` into a concept so that it can be used for subsumption.

The following code will fail since `(...&&(not Pred_0(*)))` and `(...&&(not Pred_0(*))) && (...&&(not Pred_1(*)))` are both atomic:

```C++
constexpr auto Pred_0 = [](auto...){return false;};

constexpr auto Pred_1 = [](auto...){return false;};

template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (...&&(not Pred_0(Args::value)))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...&&(not Pred_0(Args::value))) && (...&&(not Pred_1(Args::value)))
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgCcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BxoDHOYqqnEANRMXkSnysSY6AD6Gqcm/gAiz4FWga8QF0QAdIDViYAOwWW4ELYMU5UMRKF5WEGvBEmDQAQVRaP2h2OZz%2BqGutweXGebw%2BXx%2B%2BMB/2BYIhUJhcMwKKRKPRmIImBYqQMnJebnxpwAki9sJi5sQvA5TgBZASoIgMACemNBVnRp01pzmTEcyFO2M5uPOlwJADcxF5MM8wSLWf51Rj7Y6OVyebrmf43AQlalGKxMNS0cRgApRZjbgBHLx4W4KU4QanmABsKYgDAVhLujwgwdDIBAFu8mFWpcxhqOJ1OsVQnhhXgYEFp4MwkOI0NhtHhDtByPZ6M53N5nu9vv9bCDIbD/jF6KjMbjicBKbTGYIWYeGlzU4LRatpdWzzMqePCaTx9XmZu2a42/zhctJbL6IrxprdaoDabavp7dOBElT1ET7DF0R1PV7iYBQlFaagG35OU1wEFUvS4cMZybYEHQ4dZaE4QJeD8DgtFIVBODcaxrG1TZtmtcx/B4UgCE0HD1gAaxAQJk3%2BAAOZMpECEFk0kJJ/CEsx/H0ThJF4FgJA0DRSCIkiyI4XgFBARTmOInDSDgWAYEQEBNgIVJLnISg0G5OgEiiANOFUPiAFphNOYBkH1KR/jMXg7kIEg8HQPR%2BEEEQxHYKQZEERQVHUHTSF0LhSAAd2IJhUk4HhcPwwiWNIzgAHlLjM9dUCoU5HOTFzJDcjzTi8swEw8az6DOeiuFWXhtK0dYICQKzUhssgKAgAahpAYApDMPg6E5YgNIgWI8tiCIWiVTLeBW5hiCVArYm0eptMYqy2EEAqGFodb4qwWIvGAAVaC7DbSCwFhDGAcRrtjQ68DNTANPio56kuXZGIiTk8Pi2g8FiNKdo8LA8oAvA5O4Xg/uIGslFeLl3uhowWPWKgDFDAA1PBMGSgq/SIxiQuEURxEi%2BmYrUPLEv0d6UEoyx9BhjTIHWVBUj6AGnLmdAXleUxLGsMwVIx4hAv%2B%2BB1jqBpnAgVxpj8JKwkWCoqj0IosgEHXjYyU2GGGQ2Vm6XpGnmc2kvVvoBlaG3RmqCZBmdn2PYNr2JDVmidmDqSOAIpS8tUirnNc9zPMkbyE1wfy2okjqusJ9YEEwJgsESJtSA4yR/H%2BUSQUkDRJDMSRkwUriUkhmTSDkhj/n45MeKSHiuGTQJJC4QJROTaP4tU9TNKYwm9MMvrjOK8yRrG1q7LYTgWhYM0QScpgDQMIx6qSf4uH%2BEi/KIJWgqS%2BmwqZ6QWaUNn4t0abUvSjbssj3KJ8KpfSrlS3jvPeB93rH1PufJqqAWoJCPP4MwnUZ46V6v1GBg1WoWVGug8awDd7IEPpNJIXBFI0FoHNBaS14pbTWs9GhO09oHQcM9E6jACDnUunlG6d0HpPTRi9XGRhPokXwLcBof0AYX1UMDTkz1wY9DytDWGa0Ea7BIsjVGjEMZY0wDjN6QiIigBQXwEmChyaU2powZ6d9GYRUfrIVmcUSJv05gTGWVheZKIFsXYWotODiwIJLN47i5YKwSNfFWgt7Y/U1trTwHQ9D63KEHJKJs%2Bh%2BzSdkT2yxvau0dr7eJ%2BQXY9Bif0eY2SjYuydoU3W/sFjJJyeHBQocIrfyjspXgsc8GgIIeAmokCngQDTlfeBWdkE9VzvnQulBv6t3bifGuIIR4ghBP4Wu9ch7jxUpwKeWlZ76SMiZEqWDV62XshwLerkWAKDNPqM0/ThxzF8vgK%2BgVgqyHvnYqK8hn5OJ0AEFKaUMpozab/bZHAiqmUuKcMq5xiAsCuTcu5DyPRzGgbAjO/h/BIO6rpBepzhqWRwa1QsyBUipHuPcpI9xHkEEgvC4SM1yEJEoctVaO06Hst2vtQ6LCYGnXYRdK6IjMC3XumIPhjFXp4zUbwURP0JF5SBsgEGcjBAKKhjDOGSpVFIyVpo9GCQdF6LxoY2exMmBkwplTGm1iPm2IkPY6Kvz2YAsIdzWWnj%2Baq1IiLbIAMAD0EsPUeIsPLTpitlbeLViUjWfgtYMHcDUxJiaKl20yWbZNqTLZ9DTbk2Nbtql5FqXkgQ7t6lLEqXUv2OoA4NMqSHLYYcOoR3aTHTgcKEU1Wubc04VL/i0tTi8kgoycU51IHnAuYxi4t1kiAMwJ8sWBECDXEhGgsVCR4lszpOzbDT1xaWEuIAy6n38DxQeEkV3JgkkJCO/gwU7rUuM1iEcfLbvyk%2Bg96wMaZGcJIIAA)

By turning `(...&&(not Pred_0(*)))` and `(...&&(not Pred_1(*)))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AllDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllDeceive<Pred_0, Args...> && AllDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept AllDeceive = (...&&(not Predicate(Elements::value)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxmpK4AMngMmAByPgBGmMQgQQAOqAqETgwe3r4ByanpAmER0SxxCUF2mA4ZQgRMxARZPn6Btpj2jgK19QRFUbHxibZ1DU05rQojveH9pYNmAJS2qF7EyOwcBJgsSQZbJgDMbkxeRADUysSY%2BKJbpGcEAJ5JjKyYAHSf2PRsggqH2BMGgAgmgGOskgQzsDaLQACJVTB4ABumDOhzhZwgn3e5n8eIgDFQUMu1zwt0wEG%2B20YBAUIBAyLEXkwCzZhysIKBwIA9AAqAWCoXCnnc/mCs4AFUwkwUZyFopB4uFKoFiuB3LBk0wqiSxDOJ3OpPQAH0NOiDpiTABWKzWuEQQ2oHELEwAdgsVwIqwYZyoYiUHPdcKDXJBWq2uv1TouV1NXAtVttNodTpd7s9mG9xF9/togYOVjdIcL3O5Wx2e0wh2Op1QZwAkgDuZNiF4HGcALICYkCR5lj3cs7Ds6TJiOZBnCM6vUGutnJneNEZpvF0MatelsPAiu7cfVo5PF7MNg44HEYD/A6AkFXACOXjwVzlMPhiJRB7cxrN93Pl5xzbhgI2pRmcMSoJ4fpeAwECuh6Xo%2Bn6AYHkWIbbruVY1kerynp8f5Xje56YA%2BT4ytCsIIusH41t%2BGi/heCgAde6JmPirHkW%2BVGojRcYmlw9H/p8gGgsBkazuBkFUNBsEZghOYPG2KHBmWIJjhOJpMAoSgNNQ0E1t2RJEAw/ZHFwzbXrBrqFhwSy0Jw1q8H4HBaKQqCcG41jWKOKxrMuZgHDwpAEJoNlLAA1iA1qSO8GiSFwboHBo1oaKxgQABxpfonCSLwLASBodFOS5bkcLw9J0cFzk2aQcCwDAiAgCsBBJKc5CUGgOx0PEkRvJwqhpf4AC0/iSGcwDIJOUjvGYvBkkQxB4Ogej8IIIhiOwUgyIIigqOoVWkLo/EAO7EEwSScDwtn2Y5IWuZwADypwtVCqBUGc/VDSNY0TWcU1mFiHidfQ%2BrmAFCy8JVWhLBASAdUkXVkBQEBwwjIDAFIQQ0LQWzEPSEAxLdMThPUjwXbwRPMMQjz3TE2hVJVgUdb8BD3QwtCk/tWAxF4wDHLC9LcLwWAsIYwDiJzpHVKiAsuTqVSnBsgXhFsdn7bQeAxKdVMeFgt0EAteWC6QqLEOBSgIiLRjq0YIVLFQBiXgAangmBHfdx5k1twiiOIm0rfIShqLdh36KLKCeZY%2Bga/SkBLKgkIZALg2TOgGKmJY1hmMVJsLVgMewW0HQZC4DDuJ4zR6KEMwlGUegpGknSZOXOT8fXBQMH0NeDPxlTVF0UxjH4PftPTNRTJ3AwJD3A/N0Pww9BPcxT0sCg%2BesEhXRwDmkEVvAle9A3DaN42TdF/1Uvg80sWDEO20sCCYEwWAJAXEWSAc7wAJwHG6kixWYkh/AFWtP4T%2BWUOA5VIHlAK7x/BcH8GlT%2BaV4FRS4Nab%2B/gd63RKmVEAFVbY1XqjDRqT1WpIxRsDHqbBOD1BYMiN0g0mBTgMEYX6n93hcBirNS%2BJBFrLVkGtX20h/Y7SDvtXQQQTpnTJpvbeu87ocEes1U4ZxXoGmIHQhhTDkAsOAGwjhMUAaoCBvEa%2Bixb5VWhrDYx8NgZtWRjY1GtD6GDR0aLLgn8uB0SxjjPGBN9oUxJp7QJVMaZ0wcJ7JmtJWbs1ulzHmfN8ye2FqLcWLl8BXCljKW6ctkAK09srdot11aaxJjrDYLl9Z4ENoFE2ZtMAW1SeEUAli%2BAOwUM7V27tGCe39oIjawjZCiL2i5CRocbbpysJHEp%2Bc44J2ApwZOBBU6WkmZnbO8Rc7ZNjoXUezgICuEHpXUui9a6t3yI3I55yG4ZFOd3XZfcGDdFGLPPQvdG7POmMUSebyZ7ZDnmOBodzl7LFWOvLgsibr7X3s4rRzDRb6M4eaC%2BhASDXwhRYqG99H7P0oJvSB0D2GxTdOgt0CVJAAJGvxeRODbB4KCgQ2qDUmrPXsRQ7qvUOC0K%2BiwBQyJJzIg8e8KskxuGotzvw1aPsBle2GcHEABxSBSPOoLSFWDoUPVIS9N63LRq8v5QuIVIqoQQEBrY0xoMDjgwZa04h7LEbtUccDRkyAkhJBNIKz%2BJpjUaQ0SNPgdBfGUH8S5EJHNAphrCfTSJxjmYxI5ukzA3NeZiCSUbFJVsKlC0lo4aWOTVDyy2AUwQRS1Yay1o8cpesDaezqakBp2wmk21afbJgTsXZuw9kbPp0qJCDO2oHEZOgFXjOMBHGwMz4BzMbgLHkKdw4Z0sFnPeOdFrbILu84uBzS5XOCCc6uPzrnt13W3RuwK3kj0eZ83dm7%2B4LwPUvX5PQb3jwfWclea8NpqppZwdRLAeV8oFUa/ckwsS4HFei61kNQqkAfk/QYBdVYEsSOwg4BxrTJTigVNDboEHquKpwXB%2BDLHhRAJIa0X9rRpVYp/SQn8Eo/y4Iq1WBwoUEdKjarF4CZr4b3oRzjMGTZpGcJIIAA)

## Links

- [source code](../../../../conceptrodon/varybivore/concepts/all_deceive.hpp)
- [unit test](../../../../tests/unit/concepts/varybivore/all_deceive.test.hpp)
