<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AreSameTypeSignatureAs`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#are_same_type_signatrue_as">To Index</a></p>

## Description

`Functivore::AreSameTypeSignatureAs` accepts a function-like type and returns a metafunction.
When invoked by a list of function-like types, the metafunction returns true if their type signatures are the same as the type signature of the previously provided function-like type and returns false if otherwise.

<pre><code>   F
-> Args...
-> ...&&(Args `same type signature as` F)</code></pre>

## Type Signature

```Haskell
AreSameTypeSignatureAs
 :: typename
 -> typename...
 -> auto
```

## Structure

```C++
template<typename>
struct AreSameTypeSignatureAs
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value{RESULT};
    };
};
```

## Examples

We will compare a few function-like types to `int(int, int*)`.

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

/**** Metafunction ****/
using Metafunction = AreSameTypeSignatureAs<int(int, int*)>;

/**** Tests ****/
static_assert(Metafunction::Mold_v<decltype(fun)>);
static_assert(Metafunction::Mold_v<decltype(FunAddr)>);
static_assert(Metafunction::Mold_v<AbominableFun>);
static_assert(Metafunction::Mold_v<decltype(&Tester::fun)>);
static_assert(Metafunction::Mold_v<FO>);
```

## Implementation

The implementation of `AreSameTypeSignatureAs` relies on dissecting the structure of the function-like types into return types and parameter types using the metafunction `Analyzer`.

```C++
template <typename Known>
struct AreSameTypeSignatureAs
{
    template<typename...Unknowns>
    struct ProtoMold
    {
        static constexpr bool value
        {
            (...&&(
                std::is_same_v<typename Analyzer<Unknowns>::type_signature, typename Analyzer<Unknowns>::type_signature>
            ))
        };
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;

    template<typename...Unknowns>
    static constexpr bool Mold_v
    {
        (...&&(
            std::is_same_v<typename Analyzer<Unknowns>::type_signature, typename Analyzer<Unknowns>::type_signature>
        ))
    };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISdKuADJ4DJgAcj4ARpjEEpIAnKQADqgKhE4MHt6%2B/tKp6Y4CIWGRLDFxUkl2mA6ZQgRMxATZPn4AzABstpj2RQwNTQQlEdGx8dWNza25XbZTw6Gj5eNVAJS2qF7EyOwcAPQAVMcnp2fnh/smGgCCRycA1AAimMmujMh4mAoPp1e39wuQLO/xu1zBZnaoWQ3iwDxM7TcyAUBHwggR2HB5ihDBhXjhCLcBAAnm8APoEYhMQgKDFYgGnB43Zi0YkAL1ivxOoIImBYyQMvPhiJJb2YbDptxRxC8DiZLPZsWUxFQRFFmHhAHYrJqngirLdwbz%2BYKNYT1eKNQAlTAEUgPC2sTAAOldN2IwFp7UxUspsoI8rEiuIytVqtJmEJNoIEHdntdzrWkrB2vBD3TDxRTEcyAeaAYKMwqmSxEzqJAIC8oQI7TMFIeADcxF4zdquMK3ISHu0TLr9WmMwP0150kYHRGyelgMwCNsze0ng9o7GPQoE0n2gabhn4bcdyPQsAHsRvl5aAQKRHhYvo/3DXuM8aBdnIyK%2Bc/eeaI5aExi8wYFB%2BDxBGpMJiGTfdRyPZImidXliEvN4fgRRdgMaJZwMROM11dOlNyxPt8PvG4n1NDtHTYJdbXtCiXTdVdk2lf1A1ZDkQxVNUIyjW0V3jV01jzAQUWTXstx3LMc0EgteWLUsUXQCsq0EWt6ybbxWwsdtCS7TotTcB4tMRLse0IrchweA8x3VSc8GnbM52vKiY2w9c723QcH2HKDj1Pc9EPnG9bTc8zSJfc131NL8xSdX9vX/JhAIeNDQNiCCM0s6DYLYeD/OQhcktkFLMLcFzcO9YLTPpEiIrCkVvydB4ADEGEYv05WZIM2JAB5ki8KJaDwXMOtYpUOPDN5CWav9RN7PUiLBW5Qs/Orosoqbyt9GV2oVNjJoYQ5k263r%2BsGljg1DTiJsRdafRTMSMwk0780LWSywUytqxUgM1JbcyZs8ncDI7LszD08ydwgcHAfTQzO0Rbt4QAVlu6HoeG86xvVPaMQrH7IwBnckwB2aKrmszFpq5aiXqyiAFk%2BWamiaY1BottnE9WrZs7dsRemWGah5Wf9OcKwOjabiOvqBqGnbRrDLHeYZlrxf%2B9z00e3Nnpkks3sUz662%2B5t8bVrV7uh2Guy0zVOwJjNIdt83gfh9okZR1Gd3RtiLvG183D5m7caNqH0yJk2Sfm8yMviwD/McoWHDnUngopk1aup1aNUagB5ZMTwARyrE8fnzwvvlN8xOmzitUDeKkiGICANx1PVNuYz3UuunPxclk6Zc6ju3CwGF1UhsxK6z6va%2BzEhG43W7VfExpJK1osdfkvXlINxsg%2BJ1MHaB3sbZNiHg8Bi34a05HT492XiqH88I1H8fJ9iaeG7WOfA/U0/Q53cPyZNlHGECUFCxxQk1LuZlKrEUBMCOBxxQSwIeAASRNHyRgS9MhcgQeCWB8DgSgiNJTec6dGANQANIMFQAAd2VrdJi7UTxCCdAAFQjEIWyM45w3FpIaPeJslq%2B1ogmOQDAADWVDaFejdurNqAZva008OgP6/D3Yayki9HWURUCeG3t/feC93Z21/GPCu9tj5GNke9PAoCFBOjJA2KKZDKLt2KqIiRNCCw4xANZKcXCTxMwztzAe7jJFeO9BWXxnD7Ic3FpYkOv9Ub/xUWTKqO5BFOJ/PRT0aUvKHgeIo2g6BHIKKUYSUqzo8IAPScQzJMVXShM8dI8y6iV6vW0bowp6AHEqLNoDCAJjOhmOvg9csIAbGTnsY4laziNSuMJI0qR3iol2XZpgQJszgluPEWE6RkSJx%2BJia%2BGRgMP4pKThHBk%2BC/i4MZNgVQrABQahuVc65OCYGMioF4XE/QfgvJuKEAaYQHjVgeF8hgEBqz2mrIcJM2ofLswYA8DQ%2BotQtwWncRkTBtEsFCNi%2BgYLvl1CEtgy44Io43BxXi/qmBGrfMctWSFghoWCFhRoggydMWPHBcSpFqRqyxD%2BdycEgKlgPCYF4IgTVvk3HQOgUsol4Rj3BWizlSD%2BWCE5FKtgKxSw8t%2BaS0EDCAwsO%2BPBAifTRXAtBeCpldoQWsoElrU2CLthIpRZuVVfDUkfO5US/oDxUBRG0LUAgQr3k8LkRAi15lQU11fvXRudqWUEDZc6xVJ5EXItRSTb1arGT00aPqrB/yo6FqYMWgQjl3SYGYWwNhbwOGrO4V6NwjKoUOtTXPfNjxTUonDWS302ZBpkhAbEGM5bK1%2BBAF0npiJ74j3BXPJu4INajsAuOiAk7/WZArLO6Zg9agPzeBAOlDBZXyuXW5NdY7mhbttBWndzgZ1KLnSVKlzAaVnoxCuodOZ11KDvdun5u6X1FLfQux%2BFc%2B3wQrEun917MHIAA5u4DvK92voPdnBDm4OAbFoJwRGvA/AcC0KQVAnBOyWGsJmLYOwzSQh4KQAgmg8MbDESARG7RnSakRojTUXBEZmC4AADhE1wLgZhpAEY4JIXgLAJAaA0KQEjZGKMcF4AoEAymWOkbw6QOAsAYCIBAFsAgvU7QUAgGgfkdBYjhCdJwVQInOgAFpOiSAeMAZAuYpDOjMLwTA%2BB654AUlwGQggRBiHYFICL8glBqFY6QXQ4XqFUmSJwHg%2BHCPEaS%2BprOkqLOBqoA8ZzbmPNeZ8wZSQ/mHgQA8LZ%2BgCrGNrF4LprQGwIBIBs8kOzZArM9b6yAYAUgzB8DoPBLTEAohJaiHi4gxJMu8Dm8wBbWdg2hqW6QGzbBBBZwYKyJLWAoheGAG4MQtAtPcF4FgFghhgDiD06QfAJ46gNm%2BElostRJV7CYwKmTZGBpRCpAtjwWAkuUjwAp67pB3vEG0UoF4d2jBAtAHpjYVADCegAGpfGoVnMUW3%2BCRdEOIWLxP4sqHUE9lL%2Bh7soGsNYfQeAohacgBsGuvzOCufkihUw1HLBmDU3D4goWPvs56H0XdEBXAzD8OF4ISwygVD0AUDIAg5eq7SOrhgIxlerEl6G%2BoCxNfhZqLywYzQ9djEqPMIYpu7dW6VzbiQGwFB0d2K7/QOWVN5c4KVlz7nPPed8zV0GEBcCEBIEq9oXBWvMdYx/UgCBMBMCwHERupAOOSG4wkdompJAaEkFJzoSnEadCSDJuTpAFOx%2BdJ0LgnQRMJHE50RGkhBN5%2B6Kp3g6nNPaYT%2BjgzxmuumcK5K8glBBtNYc2wTgTQWANk1K5pg8UxxcASM6LgzoyNBaj6LsLcWotk%2BkBTxQVOku6DG2lpgGXrvZY4ER33T38vj4DKgErZWg9r6PBvrfO%2B6sGtesmsY8zB492t9NR9p9YhJ9rNUBGtxhgEjAN8uBlMaBzxBVKAZsnsVsmhFsYdcC1sNsHAtsdsMF9tDsntjtTtztaBLsttbt7tHsyMXsjd3srtd9VBvteQtt/sksgcQdiQwc9gyNIdocmM4cEdMAkcmDDxE8%2BAscFBcdMB8dCcYcKdj8YtT9ZBz9EsacQAxsDAjAGcBcbAgc2dM9OdMgrsedUQ%2BdGdBdhdYgD9xdM9zd%2BgXAGB3BPA2g9BFdSgXdws1d%2BgHdgjMhrddU9B3Djd7cfDcgzdegjcBBLdFgAjIizcTc4j5dHdUjlgVc49NhthPcCiZMn8e9yN/cv8KskDf9N9t8NA6tI964Y8482tE8NgU809xhM8q95MQB2hN8i9eMEhNRNR2hi9JAPNwtyi%2B9bAB8IDOsR8kAzMLNYDoDiBZ89gF8KsWAFAGxcwGw/9TQURAtgsSBQs9ANDSctC4tdDqcyNdB2hSAb878stvdH9csX9OACtzNJVitSsdi9iDijiXwURAD4DgDORsR2hwD5CoCIS%2Bs1iESmsQB9jkhkgHEN8yRjiLxVAPNxsMDiAptsCyNCD8CmMyT1sQ0SCYcyC9sDt8CWDMATszsLsrsmNGCUcRCbs8BXtHB2DPsuDkAfteDNUAdeABC8DhCIdRdxDeBJC0hpC%2BRZDjCh9McmAcc8cCdGAidZBND4hbiEt7idB%2Bi6djD%2BcrBLBmdWd4AOdkgucDh14LTrAhde8RcxcLC3dEj0MZcvCHd/C8iDcwiNcsitdChwjnd0jDcLdMichsjojkiFgIj8iciHcswnc0j8i3cPcYsH8yi/cOAATPNdj9jGwQTeQwSI8zjmtY9YT0cOjU909KAH9q8FMzBN92h2g%2BMi9UCNBOzNQm9n81NOB%2B8dN2is9/BOh/MAgzARNJBNRxNRMRMBz3j2hPjhyNNB8OsH8Ashze8Ryty2NYdBVd1JAgA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/are_same_type_signature_as/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/are_same_type_signature_as.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/are_same_type_signature_as.test.hpp)
