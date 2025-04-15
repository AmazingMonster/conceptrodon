<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsFunctionPointer`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_function_pointer">To Index</a></p>

## Description

`Functivore::IsFunctionPointer` accepts a funtion-like type. It returns true if the type is a pointer to a function and returns false if otherwise.

## Type Signature

```Haskell
IsFunctionPointer
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsFunctionPointer
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
static_assert(IsFunctionPointer<void(*)()>::value);
static_assert(not IsFunctionPointer<void()>::value);
```

## Implementation

```C++
template<typename>
struct IsFunctionPointer
{
    static constexpr bool value {false};
};

template<typename FP>
struct IsFunctionPointer<FP*>
{
    static constexpr bool value
    {std::is_function_v<FP>};
};

template<typename FP>
constexpr bool IsFunctionPointer_v
{
    IsFunctionPointer<FP>::value
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzABspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIphJrozIeJgKF7tHp%2BcHX3vvJ8d/ZliwWQ3iwFxMsTcBAAnncAPoEYhMQgKCHYf7/T7fbHbX5Yi4ASRYSXobEETBqrx2eJxtMOGNOBEwxIMTIhUNhjFYmDR/2GxC8DkJCgAYl4GA4MspUMEmcQMQB2KynC6qi6TRzIC5oBjDTCqJLEC4RVCeC4ANzEXkw4KVVDEShMCquEOVf2droZJyZLIpPMhMLuzDYFxFyl5p35goIwrFEpq0tl0XZYc2EfdbrV6vqmu1Aj1BqNJrNlu8PJVaqdFmG6BAIDwCjhVHFkoEcPNKfDsXRHtibqdLr7Xp9JL97MDXJDYfTOoLhuNptosZbCZlgmi7cVmbVBNFK6la7lnbRddL1sVg/7Hzpb0xuwu2FUrBJNtv15vuK9GrwyDhTAUSiNBAu5xq2DCJuu8qQuaMroBAmxzBAcwniAZ6YMhQ6RjmP5/gB0QEBADCoDGIH7gIEFHtBsFIShaEYW6HALLQnAAKy8H4HBaKQqCcG41jWOqSwrDa5ixDwpAEJojELAA1iALGSAAdBokhcAqsQaCxGhmPE8RmAAHPp%2BicJIvAsBIGgaKQHFcTxHC8AoIBWZJnGMaQcCwDAiAgEsBBJF4BDkJQaDEnQ0ShNynCqPp8QALTxJIFzAMgWpSIpZi8Jg%2BBEMQeC1m0/CCCIYjsFIMiCIoKjqK5pC6G0ADuSJJJwPBMax7FSdxnAAPIBf5MaoFQFzRXFCVJSlFxpWYFwQB4oX0EaolcHMvAuVoCwQEgIVJGFZAUBA227SAwBSGYfB0HKjkQBEnURMEDTQi1vB3cwxDQt1ETaJgDhPaQIVkgQ3UMLQj01VgEReMAbhiLQjncLwWAsIYwDiGDeDEN9jjms8nX6t9AVrOJSbMTVtB4BESJvR4WCdYieDmfDpDY8QJpKDcSNGGTRhSQsVAGMACgAGpPPV3VBr9hXCKI4hlZLlVqJ1dX6MjKD8ZY%2Bjk45kALKgSQ1HDsU1hCVymJY1hmLZzO5VgWtIe0mMZC4DDuJ4LT%2BM70z9DEbR5OkAhjK0ySpH7DCe6UAwTFUDsCF0oyu%2BM9tgbHPTBH04fe7YIxNPHgeTI0YezMtizLKsEhtRwbHWZ1dnDTF8WJclqVKdNEC4IQJDgoCy2rTzCwIJgTBYDEdtyZIsSKQAnLECqSCpZiSPElksfEE/GRwpmkOZYmKfEXDxPpE/6XvClcCxU%2BJDZvB2Q5TkSTz7leZtPl9QFQUHag83hZFHANCw5oKrFJg2oDBGEmhPRSXBlKZWyiQPKehJbFRltIOWSgFY1V0GdRqTBmrw3LpXS%2BXUOC9T8gFC4g1a6jUSiCZGYCIHKRmnNHaC1O6xDMCtO%2BrkNpbQ/kw6Ib9DoLRQCAk6E8uBWRoLQS6lAbo1Reg9X6ci3ofS%2Bj9Rm/1GCA2BqDLi4NIbQ1oLDX6iNkaox0ejB22M4ZcTxsgAmv1iadTJhTB61M1hcTpgzcSzNWaYHZiY4IoBOF8H5kLEWYtGAS1kIg0qyDZDy2qlxDBytuamysOrJxtsdZ6wyAbI2sQTZqwsBbK%2BVs8o421onGoTsXbZEDoEVOMwI5B3yBkAOuRg41ALk0uw0dahZzaZHDoMcs5dIznnbOtS9DjNGWXYuwlZkk3wdXTgFD67AJoVwcBkCNAzTbjlFh3cOHrT7gPIelBy4by3uAlSCoz4KnUpIeeCU2gEOvrYW%2Ba03IeW8r5fq/CeG7QimwTgv8xosAUOaLU5pNmKVZM8Ag0D27W3gVE6WMTyryFQQknQcRSBYJwa1NeSyap2WIf1MhQ1VBgohVCmFcLhgMIBcw0SsR2GfK4SgJlfD9oCIGJCpISR2ybLhPSggcIqXIIutEK6MiuKKNBuJeVyjMa/XUYIIGINOq6KhjDOG4ljGczcQjcxkpLG41UPjJk9j1wky4k4ym0JXG01yp43g3jUi%2BOZP47mQS%2BZMAFsLTAotxaMwQWiiQsSKpYsVri4RqszbpM1vALJ%2BtODrBrPGtJRTLbRGtuUu2PSwLVIGaQepxQvbtJaf7HOlaQ4zMGb05OJbC01GTvWzO3Rm0jIaRWouCghKlyLosjqJKVkSouOCyFFo6V%2BgZa3GBi0u5st7qQfug8Bh2xJpckAZhwGxFiCxLSqlLL7oVPvKuo77LvOciu0eLFJ4sX0jpCekgJ7qWnlwWIa9YgjtspwHunDy4ZQvX%2Bq97KFjMzSM4SQQA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_function_pointer/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/is_function_pointer.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_function_pointer.test.hpp)
