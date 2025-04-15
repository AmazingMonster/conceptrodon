<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::Analyzer`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#functivore-analyzer">To Index</a></p>

## Description

`Functivore::Analyzer` accepts a function-like type and extracts its return type, parameter types, and qualifiers through various members.

## Type Signature

## Structure

```C++
template<typename>
struct Analyzer
{
    static constexpr bool value {RESULT};
    using return_type = RESULT;
    using parameter_types = RESULT;
    using class_type = RESULT;
};
```

## Examples

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

/**** DummyContainer ****/
template<typename...>
struct DummyContainer;

/**** SupposedResultType ****/
using SupposedResultType = int;

/**** SupposedParameterTypes ****/
using SupposedParameterTypes = DummyContainer<int, int*>;

/**** Tests ****/
static_assert(Analyzer<decltype(fun)>::value == (1 << 3));
static_assert(std::same_as<Analyzer<decltype(fun)>::result_type, SupposedResultType>);
static_assert(std::same_as<Analyzer<decltype(fun)>::parameter_types<DummyContainer>, SupposedParameterTypes>);

static_assert(Analyzer<AbominableFun>::value == (1 << 6 | 1 << 3));
static_assert(std::same_as<Analyzer<AbominableFun>::result_type, SupposedResultType>);
static_assert(std::same_as<Analyzer<AbominableFun>::parameter_types<DummyContainer>, SupposedParameterTypes>);

static_assert(Analyzer<decltype(FunAddr)>::value == (1 << 2));
static_assert(std::same_as<Analyzer<decltype(FunAddr)>::result_type, SupposedResultType>);
static_assert(std::same_as<Analyzer<decltype(FunAddr)>::parameter_types<DummyContainer>, SupposedParameterTypes>);

static_assert(Analyzer<decltype(&Tester::fun)>::value == (1 << 1 | 1 << 6));
static_assert(std::same_as<Analyzer<decltype(&Tester::fun)>::result_type, SupposedResultType>);
static_assert(std::same_as<Analyzer<decltype(&Tester::fun)>::parameter_types<DummyContainer>, SupposedParameterTypes>);
static_assert(std::same_as<Analyzer<decltype(&Tester::fun)>::class_type, Tester>);

static_assert(Analyzer<FO>::value == (1 | 1 << 6));
static_assert(std::same_as<Analyzer<FO>::result_type, SupposedResultType>);
static_assert(std::same_as<Analyzer<FO>::parameter_types<DummyContainer>, SupposedParameterTypes>);
static_assert(std::same_as<Analyzer<FO>::class_type, FO>);
```

## Implementation

```C++
template <typename>
struct AnalyzerPrototype {};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...)>
{
    static constexpr std::uint32_t value {1 << 3};
    
    using type_signature = Ret(Args...);
    
    using result_type = Ret;

    template<template<typename...> class Container>
    using parameter_types = Container<Args...>;
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...) const>
{
    static constexpr std::uint32_t value {1 << 6 | 1 << 3};

    using type_signature = Ret(Args...);
    
    using result_type = Ret;

    template<template<typename...> class Container>
    using parameter_types = Container<Args...>;
};

template<typename Fn>
struct Analyzer: public AnalyzerPrototype<Fn> {};

template<typename Fn>
struct Analyzer<Fn*>
: public AnalyzerPrototype<Fn>
{
    static constexpr std::uint32_t value
    {
        1 << 2 |
        (
            1 << 3 ^
            AnalyzerPrototype<Fn>::value
        )
    };
};

template<typename MemFn, typename Structure>
struct Analyzer<MemFn Structure::*>
: public AnalyzerPrototype<MemFn>
{
    static constexpr std::uint32_t value
    {
        1 << 1 |
        (
            1 << 3 ^
            AnalyzerPrototype<MemFn>::value
        )
    };

    using class_type = Structure;
};

template<typename FO>
requires requires {&FO::operator();}
struct Analyzer<FO>
: public Analyzer<decltype(&FO::operator())>
{
    static constexpr std::uint32_t value
    {
        1 |
        (
            1 << 1 ^
            Analyzer<decltype(&FO::operator())>::value
        )
    };

    using class_type = FO;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMxmpK4AMngMmAByPgBGmMQSgaQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJXEl2mA6ZQgRMxATZPn5m0jV1Ag1NBCVRsfGJQQqNza25Hbbj/eGD5cNVZgCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjJrozIeJgKd8cX17dnAJOvyulxBZn84WQ3iwdxM/jcyDG%2BEEcOwoNB/0BWMOwMxdwAkixkvQ2IImEUGN8jrjsbTzujrgRMESDEzYfCCABPF7MNio0FjYheBx3K7MWicgBe8WUxFQRC5L1hAHYrMqHnCrNdQUyWeTMOy3IrGKwDQAlTAEUh3Y28zAAOkdV2IwAU/OuguFBFF4qlMrlCu5mDhbgtBAgztdjvtK3dINVoLuSbuY3JeGQdzQDDGmFUyWIKYI6BAIC84QIgQA%2Bt6AG5iLwGkyqriGkN3fxNjX%2BLVXZOw659rzpIw2oOV9LAZgETaN/wPO5hiMuhTR2PdxPJjdJofhYB3YifLy0AjVoPs%2BdhzUM3vJ3XE/Uhu%2Bs4McoN26OozMGBRfDxk%2BbEHGg7DnuyRNKaTLEKeLxfHC85/o0AEhpGK6Ovy67auqV7aoyzL3myj5vqaC6WtatqmtGKFxp6IpimIfrELK8rykGIaLihq6ZgIYxxk2PZ9qmjgZlmOZ5gWSIlmWghVrW9aNs2rbwncABsKpuHcLYhm2HZYRhIIDsmO4jsa454JO5IzueJHhhxjprvxm4GduIH7oex7QbOF6Wth%2Bk3kmT4PhyeHPoRPIUWh/jYF%2BTA/ncCFMEhkVbncRmgeBbCQR5sFznFsgJREgHwrZ9roT2nY%2BTqwWBUaRFsHcABiDDUQQQq0b60oJHcyReDEtDpj69EdUxgYvCGjWfnx5V6ZVepMqFJp1eNSUei1XoDRKHVjQw%2BxxiAXU9X1GZ0Rt/rMcaW28QmTmFmmwncUyYmFsWpbljJdx1t4wbXZN119pp8JtmYanJX2EAg32yb/W42mwgArGiv0Q0mx0McNLGjfCS3YCWH0NuDSaxt9ullcT14BXNr5hXVACyzKNWRtUGg0rXTgezUs%2BtDEhrTLCNXczNejOJY7ctVx7d1vX9SjQ0BujL5uDzWPoldfk3UJXHZg9%2BZPZJr1mNW71yclP2q39inqZpyrQ4jSZgzbENQzDJjw/jEPS6dI3y4rTWRTjRv24TqtTWV12pdFP4eVZAsODOFWkzhVzk/L5GLQA8nGB4AI5lgeXxZznnwqlYZjKfVqclqgLzEOSJAQPZ5UrRz7uFW4Ze7ftktHe18QhlgULGmDJdlxXVc18Qddrgj8YOUmgn9SJWviUWuvSfrsmfcbKtI0mlvW6byZ2/vSOO0pmku/bfbN73tTHkGg%2Bl%2BXICV/EY8T6ifsbwHm9diHqth1CMUFCRzgg1dO0146%2BUxHSGk9xsCqFYMSA0PwMR0mQQncwEIGBQi8DCEMWZtjJAIG6UWKD7hUC8FgikXw0FXHCH1CIdxyx3HIQwCA5ZrTln2LGVUrlWaUg0JqFUGoE54iYDEVALBwhiPoMwih3RsxUhxKCMOVxxGSOYL1TA9UKFWXLGwwQHDBBcI1jxaafxjiyMoZkLqqByzxGodSUEdD5h3CYF4IgDUKFXHQOgAsfFYQlxYUIiq5j7ipDsQWDxbBFgFhYfIhxSjG5rQACqfEgsrGejCGD0INEwlh%2BirRZIIMYheRdeGbH4YIhu8Yf7XjxHEikdxUAxG0LUIhij6RJJFG3TCmSmHP2rkQceKwCmGOKSsEx3p/EHj4XcAR3ZgmYVqSIixDwfAsE5PFACHTgRJ3mu%2BCKU8aLejWSwDZWyCohJuBYoQXhkgFEwOgC0CgjwEGSWeGhYdbn3LSI855rz3lKhAeWK5eJvkPPQModKlp4iAsLp8ly4LfmQuhZBOF2V5ynPOXlRKbh2FFJFmiMx1z7ipLGAkzpVw57IErIA%2BINlu4tz7rfF41AKGTw/g2c8ICIAn3Uv4FY9cVq3VpT%2BelEAJIgAUKaUVyFGXX37nfFhHKQC51eR5a0SKlBPLcm81ikUhVUsaEJUVShmgSuXlKmVMU5WDR7vCZlA9lXvxAGBauGV4hZRDFizZOLLmRU1XciFUL3UwuIOi1EhqBTGvTKa8VV8ipqKkZo7RPtsYgFxp5HlfKVJqQ0ubdsgqfLUrjeayV0q2CyqKvKxNEjk30FTS6tV7ljSBp%2Bdq/5x44WRuLTGmldKy2WorZgKtbgE1jqTRohtFCXVuogp640xC3A%2Boufa7Abbg2othUGYh2Ao3CpNQOhldqmU3wHqm7xviVWZu5TlXlBbViGpLUei1z1h2jvHY6u%2BF6fHEBVc2k8rb%2BZBuRZ2vVGM929pFS%2B8t1ql2frPd%2Brxv6VVzo9VBRd3r1m%2Bv/P69dwH22PJDfO8NO6e3EufWK81CHFWsvMMpMlkESzOt9hmuSt75z3q0qfPNOblJFr0pRs14ZYOVptdWk9CqWWYHvox4YIAWPpoAxqgjEKwPdoNVBw9VGRNDrg7ak6p7aMyfo3JhICn2Wzq3Rhsj8IV1%2BrXRu5FxH0MRs04JvtpbdNvv0xJwzUmB6mbSfJxTJYAERyA2Z8jv8hPxpra3MB6ab1wWzbxgt/Gn2eZg3psT8H4tt1Y8poDWq/m6o05Bjz0GdOvpLO%2B8TY78uJZLGhsNXq7PYdXYVfDJWUWhrRbZirPZYuDp87lgzXNMZNZQN%2BIBQGCuDdBBwNYtBOCw14H4DgWhSCoE4NDSw1gUwbC2I2cEPBSAEE0EttYABrEAsNJD2g0JILgyp/AaFhhoEuykzAAA4fv6E4JIXgLAJAaA0KQDbW2dscF4AoEA4OLubaW6QOAsAYCICfu47qVoKAQDQESOg8RIimk4KoH7ykAC0ylJB3GAMgDMUh7RmF4I8wgJA8DFi4DIQQIgxDsCkNz%2BQSg1CXdILoLnAB3auyROA8GW6t9bovoepyx%2B4ppVA7hk8p9T2n9ONIPaBhADwBP6B%2BNOysXgiOtBrAgEgfHyRCdkFx/bx3IBgBSCCDQY89jKAxFFzEKRxBOSy94AH5gQfU4tLaSH0g%2BPSQEFTtk4PSPSBYBiF4YAbgxC0Dh9wXgWAWCGGAOIFP%2BADx1BrJ8UXuZajuJ2GduxK2U99RiNXIPHgsCi5angEHefSCV%2BIOIpQTxC9GHoaAJHawqAGFdAANQ%2BBL1OPIY/8B56IcQAvV9C5UOoFP4v9BF5QNYaw%2Bg8AxDh5ANYlcqGcAp0iOCph9uWDMFDgfxAOdV8v7YTA9gKQuAYO4J4G0HoKEPMGUBUHoAUBkAIJMH4FzlARSAMOAUsN/r/vULMLAXoF0BSL0M0EgUMJUDMH0JgVzqmHgWAQQRIGsAoEdtsFQQDhwGthDkrpwJruTlTjTnTgzgbncBALgGzmbv4FwBbudpdoKqQAgJgEwFgAkHXKQLdpIP4PaAAJz%2BDKiSBPYdDKRg6wzKTKEMFA6kAg5CH2jKRcDKQ/bKE/bmH3ZcCwyqHKTMEp7Q6w7w6iGT4o7o626Y4EDY7kCUAu6m7E5sCcBNAsA1jKgU5MDRQjhcDKH2hcCPYs74BDIc56Bb684b7SBb6KA76i66BBBS5MAy557y6MGK7OGcAq6%2BFq6oAa5a4cExF7hxEJGPa8HG4O6m4BKBAiFW7I7eGBHxD%2BF44SKdHDAAJGBxFcDg5e6QRw4QB%2B4p5h5NDJ5nbLER5R4OAx5x6MAJ5J6i5p4Z5Z60A54x4F5F4l5bZl5tJ4CV655bY17IB14x6N6i4t5t6%2Bqd4p7d695nYD5D6YAj4XG7hiF8Az4KDz6YCL7L594ZHr787ZGyC5Ei574gBBAGBGBH5P42At4X5yHX6ZC5535FgP7H7P6v7xDv5YB4nUE/43HOAQCuAkHBAAH4ExKQFpDQFZBAG5DwGcmIEUHsmkF0nyK4EtA8lwGoH0kMBilskQGkEYESlYGzBylLDUG0H85lFMGQ68DQ5sHa404THNHxGJEaC8H8FDLdHCGW5iFrCSHSHDByFN6GHGHxFPbKj2HKivaSBaHPZOFQ6cCuEI6gmo4Y4bA1E44BGjGO7BE7BhE64sAKA1gZg1gtHPhjDJECFpFc5wl84SCImCDIm75ba6D%2BCkBFElFy4MHaksEcDVHY7q6a4JlJkplpn6hjDtHRldEYICo2keEDFdlDHO6DkJDJn3KVipnKGVjpkniqDU58B0BzG%2B7%2B6B6rGh6rmR6tJbF947GCCJ4SgHGYDp6Z7Z655nbnFj47BXF4Dl6OB3HV6qC15MgvGCA/5vFn4fEd5XmW7v6/G8D/G/JAlj4gkeHT5MBz4L5L6MAr6yCZEImC5Fn5EBAH6YmP7Fw4ln40nbaEKEmcC7ASRoXWAv66lv4f5YXYGZD/6AE5CSmgGlCUF8mFCZDMkIGZCqmEEUU9CKk0VYEik4EqmCnylEETBKkKl9DsX0E0GbB0HCHVkVEBkcBNk06JnJnvRtlMgdl8EpEkBWm9G2kSFSEyGUBlEulonxH%2BD%2BCwwfbPZg4WXKgWH%2Bm6mBm2BuF9HiEKGwwqGww/YlzKGSDKGvZqFVAMH%2BDyVOUw7uHW5lHM6OXbbOVuVrAD7pDOCSBAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/analyzer/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/analyzer.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/analyzer.test.hpp)
