<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Deceive`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-deceive">To Index</a></p>

## Description

`Typelivore::Deceive` accepts a callable type predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns false and returns false if otherwise.

<pre><code>   Pred, Es...
-> not Pred{}(Es::value...)</code></pre>

## Structure

```C++
template<typename, typename...>
concept Deceive = REQUIREMENT;
```

## Examples

`Deceive` turns a callable type predicate into a concept so that it can be used for subsumption.

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
template<typename...Args>
requires (not Pred_0{}(Args::value...))
constexpr bool fun(){return false;}

template<typename...Args>
requires (not Pred_0{}(Args::value...)) && (not Pred_1{}(Args::value...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAgl6ZRsenF1cm/gAih1jItAIAE9UpgICYklYkt8IEwvEQAHRIpYmADsFlOBHWDEOVDESi%2BVlR3xR/isj3uDz2BzeZ3OXGuBzuj2e4WAtIuDK%2Bv3%2BgJBYIhUJhcMRyLRGMwWOIOLxtAJZLRJMJlMp1P2hwAakwgYz9syHgRMCxUgZDV83CLUIcAJJfbCU8bELwOTXalXoymHL2HWaOZCHNAMcaYVSpYiHS2HABuYi8mEO4ttxOVFOTCopjzVRyoXhxN31huNpsw5uBoOYbCRCIexGACjtlNOAEcvHhTgpDhAGKgCBzLuLFRAa3WQCAY95MFWlijHoHg6HwzFUJ5cbmICj0Zjsbj8SWFcmMwajSamGb/G4y4xWJOkcP6/57Y9m63253u72TnSNAPiUPawpR3HOMpyWBMzAANnMcC3x7PsuB/GE70A2MbwRadKTnQ0F0OJcVxzBh13FLdpUOAgnT3IlvhVTMbkOAAVTBxl1W5VW2Q5sGIYgSAdZo/XOJgFCUVpqFzc0tSBc14IfO111JCwOBWWhOCSXg/A4LRSFQTg3GsawfTWDZ43MfweFIAhNAUlYAGsQCScCEQADnAqQklRcDJAATn8NyzH8fROEkXgWAkDQgjUjStI4XgAKCcz1IU0g4FgGBEBANYCFSeFyEoNBjToeJImvThVCcgBadzDmAZB/SkBEzF4M5CBIPB0D0fhBBEMR2CkGRBEUFR1Hi0hdC4UgAHdiCYVJOB4RTlNUizNM4AB5eFMt7VAqEOErwPKyRKuqw5arMTsPDy%2Bhw2Mrgll4OKtBWCAkFy1J8rICgIGe16QGAKQzD4OhDWIACIBiRaYnCFogRm3hweYYggWWmJtEwBxodIXK2EEZaGFoKGhqwGIvGAC1aDlNGsBYQxgHEfG2xRxwo0YxaQxR%2BEtlM8JDSUobaDwGJJvhjwsEWsi8GC7heEZ4glyUb4jSp3mjAslYqAMOsNTwTAxuW8s0fa4RRHEHr9f6tRFpG/QqZQXTLH0PmAMgFZUFSBoAI4UrxnQblTEsawzAiqXiBapnHe6enshcBh3E8Do9FCcIhkqEZRqKLIBCmPwU4yNOGHmYYElGuxw4EPpJhj/JC7qYvGgmAYE4WZPbFrjO9FmVo86TguVgUAzNgkOaOBU0hwt4SLtrKiqqpqyQ6s7XAmsu3zrtu5WVgQTAmCwBJ11IGzJH8BEvNRSQNEkMxJHA0K7I8/yOEC0hgv8MwEX8cDUQc/wHKSJIuG8jyHOHotSK0UQCxWVolFKj00prSyu9T6F1CpsGKhPfaAIqZHQ8giLgCINKNSIEHVqo19adSNtIE2SgzZDV0H9CaU1oYDyHiPJaHBVoZXhIcTa49doVTQa8LgmDsFXAgGdF6F0wJPxumZcBUD4HxGyh9VA50Ri8J%2Bh5LgQQaCAniMDUGQ1YaQzRvo%2BGiNkaowlujRRmMCDY1xotAmRMSZk3MRTBWWwNL4FOA4PAjM3a4NUKzQ0aNOZ1EWrzfmkMhZuNukHcWpkpYy0wHLSmRhFagHiirNWCgNZax1owPWsgSHdTIbIU2g0NLUMtkrH2VhbZhIdjvZ2rtOAewIF7H41S/YB3iAQkOO8i5eOcBAVwLdRrx3KPnPQqcGgjLSNnBoHdFiVx6CXZu5dM5hwGTXOY9cJmF1WXkdZbc67jM7v3VY6w%2B7XVvowoBnAuF7QDAYPhAicFz3wPg8Ry8pHpLXhvLelBrIhSCNze%2Bj8kgIk8kkDyZhoUQQcr/dygChrANsKA7590IHwCgelda8jZHEEQVsFoLAKosAUFGf0UZ%2BEImLOMBq7zmqEN6gbLqEhil9QoWUnQARxqTWmhLBhC1kUrRgRtLaqhSXkspdS2lvZhGKNEfEcR/hJF3QSjIhVr08WaoumOZAqRUjnCpR5c4srzgSrIQDbRlBdEaSMXjUy9qTH0zRhjRg1icZ43cZgQmxMxBONMi4lJUTSAePDj45m/jkBsyCYIEJPM%2BYCyBJEkWMS0bxIyIk%2BWKS2TgNVkwdWmtta63McQw2RTmWlPNjyp5xgbY2DqfAJ2Ltshu22J7a2vtLD%2B1HoHYO9Tu5V02ZHaOBy45RwWY3KZ2QZnTtKDs05Szq6lzaGs1uQ6GgrsnQXJu/QZlHO3WcnuFzuqCqRRFO5FrDhkopdGGVp5GJyvnh8q6qrV6kHXpvEYO8QVBQCM/BFvkzDAa4A5DQ4EoXntHpwEBYCfm7xAPvLBn8khn38EkcDvk3K338EKi9UV0WWVvvVKDzCV7walpkZwkggA%3D%3D)

By turning `(not Pred_0{}(***))` and `(not Pred_1{}(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires Deceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Deceive<Pred_0, Args...> && Deceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<typename Predicate, typename...Elements>
concept Deceive = not Predicate{}(Elements::value...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBAKykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJn8bgIAE8UoxWJg7spiJh8KIwaQ7vDEcw2AA6YnYV6MAgKaHYEFoBjbFIEO4AETqmDwADcUdCmXcGKhGWiMXgsZgTAB2KxipkQUng8kKEAgdliLyYYmElbQqzXEF/AHnXXHO4AFUwswUXwNv31JyBhvugvQAH0NJbDkCvBkjKj0c7Xdy7lhkLQ8ZgICZElZEtKmF4iOrNRL0QRNgw7lQxEoteKmZr/NrgdaHb6nVw3fsPV7gD6MaW7gGgyGEWGI1GY3HUAnxRZk6n05nRfmc3mC/bDncAGpMOHloFgiEfQduWNER5UkGzYheByT6cg7sgu5Hu6zD7Cu602aYVQpYh3FeoO7K7xciUPHPZnVSz%2BFm5GqheGm3wgvOLyLtCsLNgSarElcxDAJS/jUtc6IAI5eHg6IWiy2wckujoujicEIeq67XJeYI3neMSoJ46aARAiY9pgKbEGmGa0FmQ7fjq1ygZCS6htB6rEYhyFwZg6GYWazKsnhEEEUEdyiaRSH1mYABs5gabJuGcgpJZcER8EKKp4kUdet53DRdEAQwjHdr2bG4lug6Sky%2B5FuOpqzLOG5NI4yBOkwChKC01CARBU5whBXDrkhjEjhway0JwiS8H4HBaKQqCcG41jWCeGxbFyZj%2BDwpAEJoyVrAA1iAiQaYSAAcGlSIkYoaZIACc/idWV%2BicJIvAsBIGhBJl2W5RwvAKkEVVZclpBwLAMCICAGwECkcbkJQaDPHQ8SRMinCqK1AC0XV3MAyDIHcUiEmYvBCkQxB4Ogej8IIIhiOwUgyIIigqOoi2kLoRkAO7EEwKScDwKVpRl1U5ZwADycbbYyqBUHcZ0aZdkjXbd92SI9dwQB4B30He5jlSsvALVoawQEg%2B0pIdZAUBAbMcyAwBSGYfB0GCxAKhAMTIzE4TNHCcO8FLzDEHCqMxNodQLRV%2B1vAQqMMLQsug1gMReMAy60JxcukFgLCGMA4iG9J9ScgqoPXnUcY7BV4RgqloO0HgMTQ0rHhYMjBBvaN3C8JyxA0UoLI20Y/tGNVaxUAYCETngmAQ6j%2BKW19wiiOI/2F0DajI%2BD%2Bi2ygBWWPoAcKpAayoAyWQu%2BdszoNypiWNYZhTTHb1YE3jFdD0WQuAw7ieO0eihAs5SVHohSZAIUx%2BEZq%2B9EMS%2BjEZtT1AI/STLPeQH906sNHMu8jAkB9zBveini0t9LPfawKMV2wSAjHDpaQSavBpq4wuldG6d0HpmHJrgQgJB1J0wZqnNYCBMBMCwAkMe9VJD%2BEJL1MUkgNCSDMJIDS41GrdUGhwYapBRr%2BDMISfwGkxTNX8M1RIiQuB9W6s1QByNpqzRAPNVOy01osw2hjHaXMebU2OmwU6YDCbBltvdbqhIuCEmyi9Eg71PqyB%2BiXaQZclAV1BroQWUMYZyz/gAoBKMODoy2nGO42NQH4yuso70XA1EaNdBTVAVN4gILMPTSqIjxEyPiLtbmAT2bUxQAYIw3iuBBBoCGeIYsJagwVjLS2OSlYqzVg4S2WtyS631sjI2JszYWyjlbcEtt7bZXwOiJ2ZpkZu2QB7S23tujI39oHGWIcdjZXDngSOFUY5x0wAnRp4RQCLTThnBQWcc550YAXfRxc/pGNkOXEG2VzHVxTr3Kw9cBmjxbm3AQHcu49zrhYAewCh7vXac3ceV9nAQFcE/IyC8yh3xXukNe2Qz6b1SMCnei9AUXwnsfR%2BYLn6XyPn0G%2B0L37PwRbkcFL95gAoxVwT%2B38/o2KRqDEBeMCYXkSdWbx6jNEwPwK9BBhKkGLJQWgjBlA6pjSCL7GhdDEiEh6okbqZgxWaWalwrqfDyWcEEcIxZoj4DiM2pjaJkTiByJ2M0FgV0WAKHZHddkdKBKzGekynRH0jKFwMTsgG8gTEHJ0AEUgljYZR1JbKqaaNJFYxxqofVhrjWmsXL5fxgSaZlX8KExmS0ImxI5hqxN8SjUpBSE6E13UnRmoIE6QNRjhYZMoFk7K%2BSDYVXLYU9WJSAna3KQbZpmBjamzELUiq1tGkjN4C0q%2BzsOmqHdmCHpgg%2Bl%2BwDkHOEwyw4R0tlM9IMyGlJ3mSI9OTBM7Z1zvnOptrtkSF2YDJ1ldXU0trn3c5jd4BXN6C7XYXcz1nMeYPeIw83lj0Pr0KeM9sXz2nm/ZeW9IVZF%2BRCooWR/37w%2BSik%2BrREWws%2BaigYEH77jAGCB3FyHf7rE2D/QlVDbH8M4LjINRqnyhrBOG2BzLaasrCey0gqD0GjDHvykaAQGHSrKmYbjXBmoaA0qK71wD5W2CEXRpmPKcHqLYYkYh1R%2BNlU6lQ/wZKfUzXEzVKhT0hP2LZRJ0gMcMjOEkEAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/concepts/typelivore/deceive/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/concepts/deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/deceive.test.hpp)
