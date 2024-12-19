<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::AllDeceive`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations">To Index</a></p>

## Description

`Mouldivore::AllDeceive` accepts a class template predicate and a list of elements.
It returns true if the predicate evaluates to `false` for every element and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...&&(not Predicate&lt;Elements&gt;::value))</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept AllDeceive = REQUIREMENT;
```

## Examples

`AllDeceive` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

The following code will fail since `(...&&(not Pred_0<*>::value))` and `(...&&(not Pred_0<*>::value)) && (...&&(not Pred_1<*>::value))` are both atomic:

```C++
template<typename...>
struct Pred_0
{
    static constexpr bool value {false};
};

template<typename...>
struct Pred_1
{
    static constexpr bool value {false};
};

template<typename...Args>
requires (...&&(not Pred_0<Args>::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires (...&&(not Pred_0<Args>::value)) && (...&&(not Pred_1<Args>::value))
constexpr bool fun(){return true;}

static_assert(fun<int>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMT%2BXKQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJZkl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbgQAnsmMrJgAdPcn2CYaAIIzxF4OANTKxJjoAH0NM8XiYAlZXl8oV8ZkxHMgvmgGDNMKpksQvjFUJ4vgA3MReTBfMEWKhiJRggAiJwhoIC1OOtJBu32h0wJzOl2ubHut0eIPenwIPz%2BgK4IJJIOhMMa8MRAhRaIxWJx%2BO8RJJZNoFPpNIlusZEteLIOcPZpwuV2YPPuL2IwAU/NefwAjl48H8FF8ILzzAA2f0QBioYW/f5Ajl2h2PEAgNWE5bLEFIxXozHY2hfKheBgQJPgv4EDYMLPk81WXWvZl7U1HC1c613W32x3HJ7OzBuj2YL0%2Bh5mAMDoMhkXh4GnKOt7Cx%2BOYRPEgf%2B72%2BxdD4Oh0UA8UTlsxuMEudJ14p3ZK9M47O5/MWQvFr4ED7lqlGt6yvDIAFMBRKZrUHMc8ICEePMk0ZDhVloTgAFZeD8DgtFIVBODcaxrBhdZNg1Mxjh4UgCE0cDVgAaxAKC/VuAAOP0pCggI/UkABOY46Ow/ROEkXgWAkDQNFIOCEKQjheAUEBePw%2BDwNIOBYBgRAQHWAhki8AhyEoNB9joeJIhuThVCogBaeivmAZAESkW4zF4f5CBIPB0D0fhBBEMR2CkGRBEUFR1Ak0hdCSAB3YgmGSTgeAg6DYIIxDOAAeWUpThVQKgvj0v1DMkYzTK%2BcyzG9DwNPoDFzBw5ZeHErRVggJB1OSTSyAoCAarqkBgCkMw%2BDoXZiBEiAYiimJwiac5Qt4AbmGIc4YpibRanE3D1LYQQYoYWhhp8rAYi8YA3DEbURtILAWEMYBxHW7s6lxHsotRWplO2XDAK6KLaDwGIgomjwsCih88C47heEu4gsSUSk9mOl6jAI1YqAMB0ADU8EwfyYqtfbHOEURxDc9HPLUKK/P0Y6UFQyx9FekTIFWVBkh6ESOH0mZ0BOSlTEsawzAEwHiDsq7Kc6bpMhcBh3E8No9FCeYygqPQCgyARJj8JJZZ6QYpZGaoulm%2BpZgVvQajqAQ%2BmaVXhgSaoddF3Jzf6E3FjN1YFAwrYJHCjgYL4qLBJSgyjJMszJAs71cBsorsK4Uq8Kh1YEEwJgsASPNSBIyRjluJiAkkDRJDMSQ/R4siGLYjgONILicNuai/QohiKK4P0oMkLgoKYv0PZ8wThNEyOJMq2Sqvk%2BLlNUxrUAKrSdI4JoWFxAJ9KYREDCMbKGNuLhbgQ6yiG5%2ByknR5ysekHGlDxnzdHawLgpG133f43hBLixTlK%2BJKvinme54X47l9X9e8tH2rCoLmOGYCO5VJL9yaoVYekCRhv1nsgRerUGJcF4jQWgXUep9R8mNIa%2B0cETSmjNBw%2B0FqMAIMtVaUUNpbR2rQPa/0DpgyMKdBC%2BA/gXSuj5G6yA7r7UepBHyL03pDU%2BtsBCP0/q4UBsDTAoMjrMPCKAHufBYYKARkjFGjA0ayH3q5Q%2BshcbeQQmfQmkNWZWFJkIimidqa004AzAgTNjgsxJhYDmd8uY82sQ7TWBs/AQFcLrJIEtSimxlmkOWWRLaKxSBElWkswkawFobC2OQYn6x6EbOYoS7Z61SWLa2xsEm5PDmsDYztSkCJvp7Tgr9iDT1nvPBBX8uArzXhoIO%2BAt5APDmVKOpAY5xxGInARJcy4ryzgEZuAQAjHGzrnRubcBKcE7mJKGUk%2B5IAUglaB/86raTYJwKeRkWAKFxAiXErTbhshmFZLptkd7uQxi5CQ%2BiPLHyMToEAxxSAXxCv9a%2BkV26xUHolZKxyMqnPOXiK5NzhQQHygA%2BIQDjigPWRAvZUCGowISOc5IyQASXIYgCOFn56n0Q6ug%2BImD%2BqDQmngulk1pqzRIaPRa5CVprVYZgTa21dp01wodcGYjeBsK1pdOmG9VC3V2HwwQT1BGvXeucUR31uaSIBvEGRcjwaKPWTDJg8NEbI1RgwvemM9FPMMfjb5pjjCuLJjEbxiEaaZDpgAekZsTNmlh3GIU8VgZ1GTBYBOFkE4IwtbbSyVnEzI4blaZCjerfmWsUn9HDcGtNRScnRrGOm6JeSbbFOjQ7J2rlAVLLvrUiFXwoUXNhWaGYnSQ49LRT3aOsd46UFdmM/wK9jjHCglBLOKCNADrohRSt0UhK2C7mAxMScQAp1XscCiDdsLDr9NhOiRdjhAuWTO%2BdrtLJTo7t3CqqxAbpGcJIIAA%3D)

By turning `(...&&(not Pred_0<*>::value))` and `(...&&(not Pred_1<*>::value))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AllDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllDeceive<Pred_0, Args...> && AllDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept AllDeceive = (...&&(not Predicate<Elements>::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHASYLCkGeyYAzG57B0eYp%2BcAnimMrJgAdK%2Bn2ADUyAYKCh/KxEw%2BFEe1IHwI90ebFez2w9DYggU7xMGgAgmgGNsUgQPqjaLQACJ1TB4ABumA%2BpwJHwgMPMADYGRAGKgcQCgXgQdcznD9owCEiTtgQCBSWIvJgVitTlY0SjUQB6ABUKtVavVCvlytVHwAKphZn81Zq0dr1eaVSbUfKLocmMczhCHsxoW8hfLZsQvA5/oD0AB9DTykwBWWoj4Rj6ze2cr4CWaYVQpYgfGKoTwfMXeCkhixUMRKEMEmXBgLFk5hm37O0Ou7Op5091oz3etl%2B/1cUthyNRpqOZBxhgJpMptMZrMSymh/O0Qtlkty%2BcV4No21XG5OqEvV6o4jAQXYeWAgCOXjwgL%2BeMJxLJ3Lc7IDGjBu/3jcPaIxw%2BTqfTtA%2BVC8BgIGlUNAQITYGH/AtuSsec5VXat10dSEXW3Z4XwPI9MFPc8DVxfEiW2W8bgfQNnz3BQ30pMxGRo/DryI8kSPbLhyNfN133ReM9hHH8MwAoCQIsMCIPBL0YKLFdUWjft/SYX54gIahAJucICHeYDpWXNEODWWhOAAVl4PwOC0UhUE4NxrGsKMNi2HMzBOHhSAITRdLWABrEADMkZ4NEkLgAhODQDI0Gj6WqZJ9I4SReBYCQNCfEyzIsjheAUEAn1c0zdNIOBYBgRAQA2AgUi8AhyEoNADjoeJIieThVESekAFp6UkD5gGQAcpGeMxeA5IhiDwdA9H4QQRDEdgpBkQRFBUdQctIXRWIAd2IJgUk4Hg9MM4y3PMzgAHlyrKnFUCoD4mta9rOu6j5erMGkPBq%2BgU3MJyVl4bKtDWCAkGqlJarICgIEB4GQGAKQzD4Og9mIDKIBiA6YnCZpbm23hUeYYhbiOmJtDqbLnOqhECCOhhaAxpasBiLxgDcMRZ0x0gsBYQxgHEGncPqckMqWxM6nKnZnLU7oDtoPAYg23GPCwA6CGG%2BLuF4cliDTJQiXZoxJaMNy1ioAx9wANTwTBVqO50WfG4RRHEGabfmtQDpW/QOZQazLH0KWMsgNZUGxLJ%2BZa2Z0CpUxLGsMwUrV4asF94Cuh6LIXAYdxPHaPRQgWcpKj0QpMgEKY/FYgveiGXPRlY2p6gEfpJgzvJq%2B6ImGjmCuRgSau5mLvRoxaDuli7tYFDs7YJF2jgjNIZLeFSq7mrajqup63ynogXBCBIajPu%2B/W1gQTAmCwBJE68yQTmeABOE4AkkfyzEkelEoM%2Bkr/0ThYtIeKnOeekuHpIkK%2BiQAE%2BS4AZG%2B9IZ4HVSulTKLl9Z5UKv9Yqp1yqVTBqgV6dUGocGaCwUkAQWpMC%2BAYIwD0r7PC4H5Aa%2BAhojTGrISa9tpCOyUM7JaugYbrU2pjSe09Z6HQ4CdUq5UPgXQ%2BPgwhxDSEcwoVQvyz0sFAzejvMwX0EE5T%2BgDZRwMMHgzeiAKRRDvgcy4FfLgT4aC0HhojZGS1sboxZo43G%2BNCYOBZqTfkFMqYHVpvTRm%2BJ%2BbOTZhzLmZl8CAl5gaA6gtkDCxZmLaKZlJbS3RnLHYZlFZ4GVs5NWGtMBazCeEUAWi%2BBGwUKbc2ltGDWyYXbaarDZBO0WmZLhbs9YRysF7VJCd/aB3jJwEOBAw4nAJF0qOMd4hxxiX7JOrdnAQFcL3Vi2cyid3zukQu2RG4l1SFs8uOcNnN2TnXHuuy%2B4t1rn0duRyh593ObkPZ/d5jrPuVwEeY9pr8P2kteexiZGmPIeYhRGgaSbyGjvD5e8tEHyPifSgk8v4/0of5AIECAhBUkI/dqrFBGwNsPAn6uV8pFRKmdfRui3r1TYJwfBt0WAKFJAOUkIKrizFoVvOOjCJoNIkE0ua7DWk6BACcUgPCtoqx%2BdAv5x00HnUuvSjqjLmWZjZfaA0OIIAvRUfEHeJwNHEu0SgKl8RKXYISMylIKR/Ssqvv6dlBA5LEBYO1WGNj4h2JRmjXGzifV4wJkTTxWCyY%2BOphEzAdMGZM2CbwUJOtMlxp5o4PmsTVBCz2IkwQ4slqpJlrcDJCslYs3yekQp%2Bxil6zKYbJgJszYWytirWatspr8ubS0l2oqOnGE9jYXp8B%2Bm9H5gqUOHtI6WGjnPWOI1ZmJxrr0VO6cnlZzToPPOpcDlZBWfsooWQ11V3mdc%2BurQLknIWTcgY%2B6u7jAGNul5V6J7rE2OPD5H8p6/JSpwSRLqGVMpZeqvYsxwV0O3h9aFmjfpwuPqMRO0VkX%2BEoScE4BlQoBUSkhgIgCZWfrSoSrK%2B9SDnwMtfAyiQaJX0kFfIKt8uBiuiicD9c9OAwsg2%2B/q2GmO4aNWsNWGRnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/concepts/all_deceive.hpp)
- [unit test](../../../../tests/unit/concepts/mouldivore/all_deceive.test.hpp)
