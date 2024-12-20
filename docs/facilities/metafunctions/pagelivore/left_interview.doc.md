<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::LeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-left-interview">To Index</a></p>

## Description

`Pagelivore::LeftInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> LeftSides...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Exist (...&& Predicates&lt;LeftSides..., Arg<sub>I</sub>&gt;::value) ?
   I : -1</code></pre>

## Type Signature

```Haskell
LeftInterview ::   template<auto...> class...
                       -> auto...
                       -> auto...
                       -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct LeftInterview
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Page_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

template<auto...Args>
using Metafunction = LeftInterview<Equal>
::Page<Args...>;

static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

`Pagelivore::LeftInterview` is implemented based on `Varybivore::SensibleLeftInterview`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct LeftInterview
{
    template<auto...Interviewers>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = SensibleLeftInterview<Variables...>
        ::template ProtoRail<Predicates...>
        ::template ProtoPage<Interviewers...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQSAMwAnKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJXCm2mPalDEIETMQEeT5%2BgfWNOS1tBOVRsfFJqQqt7Z0FPZODw5XV4wCUtqhexMjsHOaJ4cjeWADUJoluXo60hACeZ9gmGgCCewdHmKfnyJPoWFT3jxezwA9AAqcGg44ANTaNxieAAbiR2CAhIwsjF6CFMFQCABJQTxBF4TAAd2OENBwMBBEwLDSBlpZzcTEuqAAdJyAc9JsQvA5jmiGBisTj8YTiMSyYCTAB2KzPY5K460%2BmMzDM1UMphM86soic9n3Y6HJgKBSG5TETD4US0hTcp7K468/kEY5W1BEABKTDogOdcoVTudyq16uZ%2Bo5XMSD0VoaVroFnqIyiYwA18YTQZdrUcyBNAkmmFUaWIxyjxwRYi8HyDAFouHKACJnCynWWtxLBgMJlV07W6llsw1PYDWumMAgO2O9hNeLJGD3puuJZse4he1BpjPMscTtiCC0xh7ducdrs9rP9tU6jXncN3yMjk8mgzmy3W213mdxkNKhdwmAY5fToT51xTVBQNoZkrRtPA7UwY8jVnM9nhbNsZWeR8h0rAAxPBiEmR0k3dIURUwbFcQJWlJRJUlmQIoiCEdINzxw%2B83A458DVfU0P05ODv3tR1nVIjct2g882OvZ1uL1F92So4Q8CwX9zzEgg%2BWTTdUxXDTlRzJUDITeZ80LYVaVLctK2rbw61kvsZP/Pts38Kx/GbCAVmOetjR%2BEAQBYJgAGtMAAfSyYAInQcKWPOLIAC8Iviv9XNc5z0qy448CoCzi2s05HOy5UoENcwADZKqEhCf2ZZShFUpDDVIY4mOI2NArs2sVhWEySo7dtrQITYGGODQ2wvLCXIG5UGiUfqSpzYbRt8ptuym4r0pbbzFsMztMK2jC0KBGawwHCMFN49l90wScj1EvtAKXHdVwg3Tt3085bvu6dytQ4NAwOk72Iup8HzB3DFONfjkJ%2Bw9p0egDF2A6DwIkn0/Rg77xzuhHkIBEHgavJ55OHIg2sIyZWsrNE0AYdAacUgB5AgEHidSeS0t1BXRPBMUosUaKJejGKpghWrpgRGeOVn2aI/6/0y87byHMmo0Vt8zWQmrEM5lzxMgqTr2VhN1cUhqmv11zDY%2B17%2BqMoqztMvMEPyqyywrNkqxrBzndDU2BpMdzg68ny/NjXN0EC4KwsivBoptOLmSSlKkaD%2BU9qy3L3ZLT2s/SsquTMKqS91urzkttSWsp5j7i633eoLjL5WOFbiDGiaNow9CtpK%2BaPhz%2BmCvzvvsqLo0S%2Bqr9apEyuxUa6vOUlzB6fQeuQG6zAm7HrLlswEaO%2BOdb2x707ZoTAecry4ePeIZu%2BwgB%2BsvI/nRWoiUpQY845Y5xXn/SoFDiIEsawRnnrf%2Bu8BpAMhh8e289cSL2aieABrkG72WOGAMAZx1yNlQcqPqUCW6nyIdlduY0zCnEsLzYUb9BYf1ol/Zkv8FYoNIVlGBqsPhSXOOXe0kD/YX2OJwwccCvpuCrsglCaUhF9nQbWSa%2BDjIHV7oI7KA8lGDTbgfVaeDu4qLUdmTsu0oHHUBk5Ym01XLm2uvDKc1snoo2XBmdGkF4FuDsUef%2BJ0gaXisSrURmpYE8WjNIrWAkbq41%2Bg45GQEQFgRwRjKCoCcYHnsd4nsljVFkxsaEmG74dbgIrn%2BcSylhZ0WlOhTO15cmGnKV/Dm6dbZbntibap/tamchhMQPATABYxNDM9YCr10avwFmUz%2BotzjdN6f0gRaCQDAKNiktwfCpHp2dCI9UST3H1Pon/FBPj9p%2BNUXJYJV1QkzL6fQAZQznFvR2eIq5czDmZJOadMElIvlfOpCCSkxwAAqSFpwUghL8p4nzvlQvBTKMw%2BwGCHC8CcZklw6C3FYthc55NUDHDxEzCmAApEi3MBTYAAI5eDEDKdpmkdRu1vnncsMRUCeB9vZaS8o8TgUSUSrJLw%2BU0ixRrTkTxiDAH1ncgAsgfJgVAvAIqaOjCZjCpluHJZS7Gf5AruNFeKjJ00zIIXCtreILFngQGla0OVCqcjMjMBvdxGhWpBGOGYVq9rOqb19tytcrq%2BonUNcgY15pTWAgtTK61DhbXnD0dgbV4inXH3de6jeW8fW4K4P6iwHA1i0E4P4XgfgOBaFIKgTgbhrDWBdBsLYdY4U8FIAQTQOa1ghQCLKdkiQAAcFVZSJF7RobtfbkiJH0JwSQvAWASA0E6otJay0cF4AoEATqm3FpzaQOAsAYCIBABsAgaRLjkEoGgekdB4iRFYDsVQPb6wVUkMcYAyACxSHZGYXg8EiA9OjkEfgggRBiHYFIGQghFAqHUOu0guggikmIEwNInAeC5vzYW5tpbODM0uIe90qA8o3oqneh9T6X2SDfccCAHgz30HLHsTNvA11aDWBAJAp60jnrIBQCArH2MgGAFIN1NBaC0WXRAGIaH4TMGIDcRDvAJOwmZjEbQq810NtPQjZmDBaDScg1gGIXhgAsloLQZd3BeBYGCkYcQOnCLKcREhNDJZV6XB2A28ItI82QeuDEODUmPBYDQ1pPAU7TOkARPEZlShmx0kMMAa4Rhm1rCoAYcVUJ6LMzSIwGTIHhCiHEMBv98glBqDQ9B/QMWUCVssPofmy7IBrFQGkJoJn6w/BwaYSw1gzDzrC8Qb99m6u9Fs84CArgZh%2BCCKEcIIwqhjCKJkbIAgxt6GKAthgixRg1EG1GgQAxpieC6HoOwQ3mhTCGFNpYs3bCnaW0EeY7R1szZqGsBQNbtgSGQxwAtpA528AXccfDhHH3PuPqRyhEBcCEBIFQxIdHG0JbWOzJgWAEjeVIG2yQiR2QjtlJIDQkgzCSAqjO/wFVUgeYnaQKdMP2QVS4BVLtyQu10/8JILg/gR0VW%2B2hhdS6V1w/XUxndzG91YaPZx7j1HL1sE4G0FgCJZT1iYFrJcXBkjsi4OyEtn6SCqT0AVgDeXpAFbA8VyDug3WwfgzJj7X2fvoY4Jhg9lxji4YrMQOXCulemhV2rjXGhyOUbY9R6HZgVj0YS5uljqAqPxGPVx6PQexiy/l/Wb3fHkhcCdYJ4TlAxOQbk1JrLBebgKaUw4LLampwaa02h3T%2BnDPGay%2BZmLVmS34GtFGsLJmteqCc7SLLbmGhoa8z5m4fmdglsC8FhtPWIuYCixZ2LQEI9JfTAoVLZJ0uZZC/r3LQGjeyBNxBkt5uyvxfa1YKrXnauo4a01zgLWCDrzXBfzr3X4h9Zv89hox2XAMxu8EAzA9ssHNiUDkAAStk0MAZdkdttidoMAAbAU0LtmdhUBtodtdvtgULdqdtAU9usJsG9pmmOp9qhpBn9snp7srsBKrurpruRhDl%2BtDrDgxi2qQIjsjpQB9hTlTmrnjrKOzrKH2vjoTqzlzuQZwLzquhHluruvuthnHhLhelejLu7vescCwAoAiAWAiLQeqJMB%2BvgF%2Brrr%2BrIAbvvtlkfiViAKOpbghqZjbmQfOhhqLjhnlLLuoZodoVWHoT%2BO6BRgnuxtDokGHvzoxpHigIEdRooVEWMNoWkGkOFLockOFPoQQMamoUbnQDnqJuJuELCEXvkVJqXsphXtHuppptpm3pgHpgZmII3iFs3pZhPmZjZp3vZpBo5sgM5gPoSB5iWiPrCOPgFj0tPrwLPpkPPtFpZsvgLnwMluvmlhlkWg2rvoBhIAfqBkVsfjoDYWfsYJVjYNfvAPVo1jkCZsCAFK/pYF1r9j1p/icVtk0H/u4FgeNoAegHgctvNk0BAT8TkF8bdj/nASgYgcCcgbgedugTgQgW8RgQsFCY9u9gQbWsiR5rbtzpwG7iwJ4VoTob4faP4YwVDrRqEawb1OwZgEjmMKjuTpOiAGYGrokIkP4P4HjpnoOokLKPTuIc4YurYHzuSa2iAPjjTrUCXIkIybTiXBoLKCQYkE4b9pIWEWwR5u%2BryUqfyUKaFhzDkCKUAA)

## Links

- [source code](../../../../conceptrodon/pagelivore/left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/left_interview.test.hpp)
