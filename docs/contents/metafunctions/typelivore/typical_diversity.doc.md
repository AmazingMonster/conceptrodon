<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalDiversity`

## Description

`Typelivore::TypicalDiversity` accepts a set of nonrepetitive elements and returns a function.
When invoked, the function appends the arguments to the previously provided elements such that the resulting list:

- contains every element from the previously provided elements and the arguments;
- doesn't contain repetitive elements;
- preserves the relative order of every element;

The resulting list will be held inside `Capsule`.

<pre><code>   Elements...
-> Arguments...
-> MakeMathematicalSet(Elements..., Arguments...)</code></pre>

## Type Signature

```Haskell
TypicalDiversity ::   typename...
                   -> typename...
                   -> typename
```

## Structure

```C++
template<typename...>
struct TypicalDiversity
{
    template<typename...>
    alias Mold
    {
        using type = RESULT;
    };

    template<typename...>
    using Mold_t = RESULT;
};
```

## Examples

We will use `TypicalDiversity` to append `int, int*, int**` to `int*, void`:

```C++
template<typename...>
struct Capsule;

template<typename...Args>
using Metafunction = TypicalDiversity<int*, void>
::Mold<Args...>;

using SupposedResult = Capsule<int*, void, int, int**>;

using Result = Metafunction<int, int*, int**>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

This function used to be a helper class for `Typelivore::MakeSet`.
It becomes a standalone function since its functionality is intuitive enough that it might be helpful on other occasions.

In general, `TypicalDiversity` is a simplified version of `Typelivore::AreOverlapping` as we won't worry about short-circuit here.
We will implement `TypicalDiversity` using recursion over the second list, which is accepted by the first layer:

- **Base Case**: When only one element exists, the result is:

  1. The first list if the element is already in the first list
  2. or the list made by appending the element to the end of the first list if it is not in the first list.
- **Recursive Case**: Pop the first element from the second list. We invoke `TypicalDiversity` with:

  1. The first list if the element is already in the first list
  2. Or the list made by appending the element to the end of the first list if it is not in the first list.
  
  Then, we invoke the first layer of `TypicalDiversity` with the rest of the elements from the second list.

To check if an element is in the first list, we use a method that is described in `Typelivore::SetContains`.
Namely, we will create a class that inherits every element we would like to check against and use `std::is_base_of` to inspect whether an element is a base of our class.
Since inheriting the same type multiple times is illegal in C++, elements in the first list must be nonrepetitive.

Here's the entire implementation:

```C++
template<typename...>
struct Capsule;

template<typename...InspectedElements>
struct TypicalDiversity: public std::type_identity<InspectedElements>...
{
    template<typename InspectingElement, typename...RestElements>
    struct ProtoMold
    {
        using type = std::conditional
        <
            std::is_base_of<
                std::type_identity<InspectingElement>,
                TypicalDiversity
            >::value, 
            TypicalDiversity, 
            TypicalDiversity<InspectedElements..., InspectingElement>
        >::type::template ProtoMold<RestElements...>::type;
    };

    template<typename InspectingElement>
    struct ProtoMold<InspectingElement>
    {
        using type = std::conditional
        <
            std::is_base_of<
                std::type_identity<InspectingElement>,
                TypicalDiversity
            >::value, 
            Capsule<InspectedElements...>, 
            Capsule<InspectedElements..., InspectingElement>
        >::type;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = ProtoMold<Elements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCCSZqQADqgKhE4MHt6%2BASlpGQKh4VEssfGJtpj2jgJCBEzEBNk%2BfoF2mA6Z9Y0ExZExcQlJCg1NLbntY31hA2VDiQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACex9gmGgCCd/cEmCzJBi/HbgSXyYysmAAdMCbk9RsQvA4Dm4mMkFF56McrA8ni83h9MF8fn9mGxgYCAJIMBR/ByYdDYehsQQKUEPcGQggHAAqvzwoloABE8AA3OLpH4gA7JLzRC7IA6jdAgEDYzAAfTwWEEVy%2BRJJnReFKpjAItP82HxTxMAHZkfcDpaDmj3kxPic5bjMAd1aTHEZKa9daRrb9/njgQAlTCjT3UvV0i1WhlQ5TEVBEACynnQTytRzNafTVq86SMvr%2BR38nMlBGlKAE%2BFqzFoWezRbcdfr0bLMrwCnl0SYSnlqCoXybzezUplcsVyscPzVxLdYWAYd1N1Ig6HVtZyXZYm5fOIAuuD1XVpuMp5Yi8mB9K/r683XN5/Kul4Ph5ZbI524fU5Ors15IXNPxH0fy6D0dUESMh2PWU/VHV5bReA44wTVBk1oVMTmDUMwL1I0DVHP0kSbU1OUIlFn0tG0MSxP0nRdGdNTnf8CAglsIVjeMkxTacNRA%2BdsJYy1TXNIdcznAtnWOEsRwrBgq0yMQrwbRT02k9tO27BU%2BwHciX0taSxyVXVVW/ejeKYpdlObG933vXdVR0yC8JAU9vAvI4HObGE4QRTETJ4rUmIUXDsCfKNDy8%2BFET8t0/2woLgSA0z3T4r1wINRSoLlUiwozEj/HNJtKLtXzvhogF8UCgSDlE/NUPQIsSyQzi0K%2BQLguywq4Koh0yoDQFKvSnSauAA46vlJlJMQjiUK4k42pBJysvy40TTygqHgAegAKh23a9o2p5tp25lsCEZldoOza9uurbLseFEzB2Bg9i8Q4vjOOhjNuMjni64rqJxcqFu%2B%2B4YyZCKfI6h4ivtUrAb6%2B5iGAfUQeG0bMAaKgvGe6sGtfDcbJ3PcvjCAgtp9HlUCVSMZTqr5EeR9rlp%2BtGhC8ZJUiUdBMIRCbi2hWFIpK0nyYOSmlR9UnJcEHbQWZ%2B77jRnnaD5ktEwxpgsZxzIScEaWyf12XFoI%2BWwQaRxkHlbslCaCBpIUAErf1NxlYIH02Y5tJyVdm5FiRDhlloTgAFZeD8bheFQThG0saxJVWdYJMenhSAITQA%2BWABrEBg7MQETTMSQAA4i%2BDjQAE5c40AA2IvAiDjhJF4FgJA0DRSHDrRSCjjheAUEB27TjgtGWOBYBgRAQFWAgRTdigIDQN46DiCIAU4VQi%2BrgBaavJAOYBkAlKRATMXhyUIEglT0fhBBEMR2CkGRBEUFR1GHnQ9AAd2IWFOB4QOQ5h3Tt3TgAB5M4s8Dh9gOBvbeu996HwOMfMwBwIAeCXvQYgRxk6LF4EPEepAIBIEXhuTB5BKAkOXvEYAUgkg0BVvySg0RgHRDCI0S4f9eCsOYMQS4oDojaE1Jw0gi9wygIYLQDh79SBYGiF4YAMJaC0H7hHGRrxDDAHENI/AxAGJ8hUV3TAqhOhnE2CnUm1RgEXGiD/XhHgsDAIIMQPALdVE7miF7Tk6ijAXCMOnZYVADDIwAGp4EwJ/UBOJhE32EByB%2B0gYkvzUMA3QXB9AaJQNYaw%2Bg8DRH7pAZYqBkjVhUVvKUklTCx0sGYLuqAdzOKwPkiAywOhdGcBAVwEw/BpJCLMUo5Q9Cc0KFkTwrRBkFGrP0fpQw0mtOrD0cYozcizOqAxOo0wpmDHiLM6YXS9CjF6Js%2BY2yWkJw2BIABHBQ4d2AT3GBm8d57wPkfSQJ9UG4Avlg7YXBcGp38csBAmAmBYHiM00g2dJD%2BEBOXfwJpJAaESJIaubdg7V3LvoTgTdSAt38FwQE1cuC13LkXQlwdJBcGDjC6uNzpE9z7gPP579R4TyIVPCBZxyEL1QBglea8OCNBYDyE0W8mAHD2BopB5dAR4sMVWS%2B0o0kxLvuIR%2BiSlDJOkboJI39f4R0udczukcwHsqZNAgVQqRVioMPmLgUqZWoPQaQuI2D/BmF%2BfggOhDiHcqdWQeelDMEgHNcK8VRhbVcHbvQl4u4mEsLYbw4R3D2H8MEQ4YRojdTiMkcA2R8jFHKOEVgFgGitFdx0XokMwCjEmJeMIixDcu7WNsZcexmwu5OJccI9xnjvGaLnP4vgQSFChPCZExg0TZDKviU/eQ6q35dy1ekvxlSrCWByXk%2BAhTimZFKeU4sK7rA1MjvUwyTSWmrLaX4Dpsk9k9NkkcgZaShnVlvfkAUmQH0zKqDUbouylndO/WshgCyZglC2fsv9OQAMHKaJ%2Bk5Kw1jnJ%2BRiq5QDaWcAOMGy1oaRq2ulYCDQ7y5VfJwXg/5pBAXAqGGChuWKcVSoRSaSlJoTT%2BERbvNJhqQG91sAyj1zL4CsunrPTlAbeVsE4AK%2BBLAFA8glDyPDGJRhn2I1fRVk64kSASbIJJ86P6BB1ckTh%2Bq0O1ONTPM4UCqCYeICwaTsn5OKeKqMB1PqqEuv8O6gdrKxN%2BooW5wNcmObygU%2BXeUSmCBW1s7vPgdBo39wgMw6RSaE2qJS3wgRQjVEZsEFmqRZbMByIUWIAtqii0lrbbwctXR9FVuMcgUxdbBCWOkU29hrbHHONcSnbtSgvHFp8f2plg6mAhLCREqJqilWadVTpudKS8jWuMFktd1iz3d23QIFRG0RwHuqbUk9jTN2AcvS4G9/69C9LA8c8Z76BCvufR%2Bvp4GVk/vWb0V9czf2HOezdnZH2Lv/dg79x9pzEMPxMzSszHAbN2b3jJuTYsnMvBcxAD5RASO4q80ygFQKQWUEuXRkAZgpX%2BH8MHMu5K25k5NLXKHRqeP90HuRiFJoT5Ma4FIcujGYVcBNCh/wpmGdkZxyh0%2B9PuMi5HssImmQEhAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/diversity.hpp)
- [unit test](../../../../tests/unit/typelivore/typical_diversity.test.hpp)
