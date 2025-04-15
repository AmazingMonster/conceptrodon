<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsRvalueReference`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_rvalue_reference">To Index</a></p>

## Description

`Functivore::IsRvalueReference` accepts a function-like type. It returns true if the type is rvalue reference qualified and returns false if otherwise.

## Type Signature

```Haskell
IsRvalueReference
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsRvalueReference
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) &&;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) && { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) && { return 0; }
};

/**** Tests ****/
static_assert(! IsRvalueReference<decltype(fun)>::value);
static_assert(IsRvalueReference<AbominableFun>::value);
static_assert(! IsRvalueReference<decltype(FunAddr)>::value);
static_assert(IsRvalueReference<decltype(&Tester::fun)>::value);
static_assert(IsRvalueReference<FO>::value);
```

## Implementation

The implementation of `IsRvalueReference` relies on extracting the qualifiers and specifiers of the function-like type using the metafunction `Analyzer`.

```C++
template <typename F>
struct IsRvalueReference
{
    static constexpr bool value
    { static_cast<bool>((1 << 9) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsRvalueReference_v
{ static_cast<bool>((1 << 9) & Analyzer<F>::value) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcAJykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3MhhvhBJDsP9/p9NhcTsxaABPABe0VeO1%2BBEwLESBiJEKhBExd2YbAR/2GxC8DjRGJx0WUxFQRCpdwhAHYrPyrpCrKd/kSSWTMBS3LzGKwZQAlTAEUgXeW0zAAOl1J2IwAU9NOjOZBFZYnZxE53O51MwkLcKoIEH1ht12rmxr%2Bgv%2BF39F0mjmQFzQDGGmFUiWIgYI6BAIC8wQIgLMAH1zQA3MReGUmQVcWWOi6A/MiwFin3lysS4mkpjkx2axUXZ3q5tsD1uo2AxEmghMlnoy2461cnn2x3O10GhQeuYQswANnMK97SN9pwDsYbeBDYYjUZjsITScEqYzF2z3jzBaLUIucQFbguhcdxdLwtFG%2BrSNOkvrIkm3tLULgAMQYb1TSHNlRxAC5Ei8CJaD3C0sVHG0JzuR0IIRAUhV/cV/zraVgJpFtcPXftB3NYd0OiHCGE2b14MQ5DULoq1MLtbCoUovsfUrbcg1Qg8iSPWN40TZMLyzHMHS3AN8yE7cAzfKFizMZ8/VU/0IB03Tt3UtwPwhABWATDNUziMPHHiHT4yDewTa9cwM1SvUU/0y2/cUvwrP8TgA0jKRAlsAFliQg9swrYC46ho5YHIE6DaNghioUilgIPigczSShNmKok5WKQlCQxsjk7PlR0sv4jcVP9ET9wEQ9o0k08ZPTOSb3c5T3KM%2B8XzffkTK81T9PGqzjNMkwLIGwzKrHW0asyqKnOwFz5IW/1PJObcfICoj9oDLxUiMUMDAUBQM3tCkrlyxLiAcmt/JrYipQbBy5VimUwIAeW9Z6AEck2el4QbB558NXAGE1QO5iAbEgIC9AKv2os00KtHDAeK0r2Iq9LiEdLBQXlfTlzhkAEeiZHiFRtGBP68bmtDVrxPak9pPPbqr228aWZO3SRrG4WJp21SZofN95qmxbidJzByftSml2p2mkaIBm5iZrbevl3a%2BrewLtzO4JgEuphrtuvlIQegHfKrJ3kW%2BN2fldy4AEkpWJRh6hqfFtl%2BFF3e%2BX5a0%2BxtQvIuKwKgvKWS9hQlVczAVSoaIHgUwT3LZsTI3aiJUE8fmDfF5Sd2DNNRGGR1i88BEoGll84gXVdsdHHCEX13N25NvzCL%2BD7ALzGOFTj70C4khvaAuZPU/kjOs4YVY00zBqq73GvrYIeuS9oJuIBbx92%2BXTuMrcePnJANP%2B6Hz2w4JR/UWwVRWFJGU3hfp%2BI4%2BXYLhUC8KvGoLxv6nGCChEIFxkyAOARAZM6pkybC9IKC4z0CDLAYBcDQooBQimOiiC4TBi4sGCCQ%2BgcCQHpDAc/U45sLonFIeQ5CmAwLAPujAwQCDBBIMECgxcK5lwu3/pcIB1CBAIVQMmaItDg7/EgcEGUTAvBEHAsAk46B0AxkrqucR%2BCRFnAAckGRMY1FsBKHicRDgaFB0OAyRO5oAAqzwiQkz8o1LhUCZSwPETwtUXCCACNXB3SuGCsE4LwT5QehiiHWMDqgCI2hlYEDkfYzGLJHYePcrAzW9NUb%2BL4UEs%2BQilz4XQaqCJuCKwGJiUdYeRjLguOGGk34zU0zWyUI0CAYAwDzxTmnZez1V7fTJrQCm4i9a33kmjSs7TOnRBdAvQZmBM7DNWI6JhqAyHMFYewjavdMCzIcbuZAHTrqLJ6X05ZS9Vkrw2VCMZFN9maO0VMu%2BTt5kXO6Tcm8Qzs5KxVncNWzS3EJkmT3aZN5jn9lOecrpSyBm3LWQCvieNNpQr7k7DgCxaCcDMrwPwHAtCkFQJwEylhrCBiWCsPMQIeCkAIJoHFCwADWIAzKAm1PyMyZl%2BRcDMmYLgAAOYV5QzDSDxRwSQvAWASA0BoUgRKSVko4LwBQIBFVMuJTi0gcBYAwEQDTVRiE1QUAgGgEkdBoihEVJwVQwqlwAFolySAuMAZAIYpDajMLwTA%2BBtZ4HjG0fgggRBiHYFIGQghFAqHUDq0gug2gAHckaJE4DwXF%2BLCXMtJZwf6JrVEXFQFQC4DrnWuvdZ618kgfUXAgB4K19AdH0rmLwbVWgFgQCQJaxI1qyDmt7f2kAwApBmD4HQNxGqIARFzREchxBMQZt4PO5gi7/pJJScu0glq2CCH%2BgwLEuasARC8MANwYhaAau4LwLALBDDAHEAm/Az0bGZmeLmyMytVFrAZTIqVJKUIRCRoujwWBc0DjwHKm9pB33EGLkoG496jBQNADqhYVADCGgAGpPGTf9Gk27Q3CFEOIKNxHY1qFzUm/QD6UDWGsPoPAEQNWQAWAjUBnAnWwntqYSllgzAqrg8QINH62PtBSekFwDB3CeBaP4GT0x%2BhlCSCkNIAgxitFU3kdISnLEqbsJJgQXRRhyfGBJmxxmRg9CUTMAYExrOab0JMRoenZhcAWAoGlqwJBZo4ASpVubVVlsdS6t1HqvW1q0hAXAhASCLkBB59tzLdakAQJgJgWAYio1IOyyQXK4iAn5JIDQkgJVLgVWZJcCQpUytIHKxL2olxcCXMKuIYqlxmUkAKwrS5AsJtVeqzVjKUt6sNd241BBTXkEoEO5ttq2CcAaCwTM/InVMCthdeI2ouDahJf6uLIng3RpIxGiQ0gKNKCowm3Q47U1MHTTevzAXlW8FVQWqbRaS0hYrW60ED7XxxB23t%2Btja%2B3NoS2YNtI30N6p7ds8H0QZsWoR8O/7Rh4hcEVTQcZsjKCzoTauhoS6YNE/XZuhw27d3%2BwPUe59mBT3nsvdehld6H1PpJS%2ByT77r37dUN%2Bok27/25qAyBzEYG1gksg9BhlcGEOYCQ%2Bzi2o3MNMBw3hgjjAiOyHDWRi7shKPxpJbd2jRh6P8ZsEB1jOWOM0K4zxwEVw%2BNWAE0J6IR2xM5cM5ZvwEBXBObaIEWzymchqZqAH7T6mGBufsxZmoJmmhma097%2BP1mY8Gcc0n5zafg/6d84sZYPmPP6Gzf1lVnAfthc25bbbu2ND1ti9rBLSWYedoWOlzLAwcu1dlSAQEQPSs8riPyfkgIyuSFdW0V7ea1W2GGx23V%2BqjVLE%2B2a2bqP5t2o4MtytLAFCZhDJmbb0phh%2BoDSQINehiO68jfrmNV2jc6D76Qe7j3M0l/8zmgb%2BbC3mm%2B6oXfffQ/Y/L6YYUHDfPEcwQEQEaHBfLteHJtJHQdCAmIA/RIRIdeeINME/AgNMAAi7SdPHGdOdBdEnBlMnTEDdZJSnGDanfdQ9EnTnBnM9C9WgK9bdNnFDSXW9PAV9RwHnT9fnZAH9IXQQKoEXZjMXCXCDETGXXgOXFIBXYkJXM3WHVXdXTAfDQjGDa/UjW/E7Q3ajZ/AwM3Z3RjK3eAdjRITjDYE8Mw13N7YTUTa3TzKoIzX3f3LPQPRTXPdzSPcPLw/w3TXw2PFPToTPLIZPNwn3BPdPbPboCPFzGzIoEPYvLzQvSNZ7L/cvDgMtQAg/K8EAokMAmLc/FtRLWAlLdvDLLLSgPzOrOVMwIHaA3lUrLHDQaA/kVrMvN7TgIbLVKo3LEACfH1SQMrYVSQfkMVEVYVLoj/QEbI3o2fOAvzX1HomfZLdDBYODVIZwSQIAA)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_rvalue_reference/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/is_rvalue_reference.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_rvalue_reference.test.hpp)
