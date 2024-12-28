<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AnyConfess`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-any-confess">To Index</a></p>

## Description

`Pagelivore::AnyConfess` accepts a class template predicate and a list of elements.
It returns true if there exists an element whose value result satisfies the predicate and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...||Pred&lt;Es::value&gt;::value)</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept AnyConfess = REQUIREMENT;
```

## Examples

`AnyConfess` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||Pred_0<***>::value)` and `(...||Pred_0<***>::value) && (...||Pred_1<***>::value)` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {true};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {true};
};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...||Pred_0<Args::value>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||Pred_0<Args::value>::value) && (...||Pred_1<Args::value>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQB/qQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJ/kl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcAPQAVAd7ANTKxJjoAPoaR4d7OyYaAIIEmCzJBi8m/m5MXkQAdICvtgHo8ZsQvA4TmdLhpQSYAOxWJ5HVFHGZMRzII5oBgzTCqZLEI4xVCeI4ANzEXkwR0RFgIEMwiIAIl9kY9Wez4U99odoecLlwbod7k8Xm8Pszvr8AUD/CCnuDIQQBZcuPCkaC0ejGlicQJ8YTiaTyVTvLT6YyaVz/BzbfbebcjgA1JgATxFBzFz1e70x0p%2Bf1QRwAksDQcqoW73ZqOTqMfrcUaiUdZSHzTS6Ujwwi2XbNfnHY8%2BQcjlQvAwvXdQRL/Z9vgR3clGKxMID/o9iMAFBGnmcAI5ePBnBRHCAdxFuKenQVw75dnsgECZ6XYZer5ag5MvY0ksm0cuViBbpFnAgbKtUMRKbl5nm%2ByUBr5uJst5hsDuL3sK0GD4ejuOk4ItOIGzrCL7fhu1JrtBFrLHSZgAGzmEhQFAiBM4wkKkHdgocE2gqBGYFuTw7gSqamoeFYMCe9LnpeRzWtKVj3k8oKlscAAqmAzNWPo7DsRzYMQxAkJGep4MgFxMAoSjNNQlYvjGL4ar%2BConludocKstCcAArLwfgcFopCoJw06WNY6LrJslpmP4PCkAQmg6asADWID6Uh/wABxIVI%2BkIkhkgAJz%2BMFDn6Jwki8CwEgaEExmmeZHC8PhQQuSZOmkHAsAwIgIDrAQyR/OQlBoG8dDxJEbacKo/kALQhUcwDINiUj/GYvDnIQJB4Ogej8IIIhiOwUgyIIigqOo2WkLoXCkAA7sQTDJJwPC6QZRmuWZnAAPJ/KVqqoFQRwNUhzWSK17VHJ1Zjjh4VX0MS5iOcsvBZVoqwQEglXJNVZAUBA/2AyAwBSGYfB0C8xD4RAMS7TE4RNO6G28MjzDEO6%2B0xNotRZU5lVsII%2B0MLQaNzVgMReMAPy0LQ%2BHcLwWAsIYwDiFTI4E3gFK8btBK1H82xOeELx6XNtB4DEq3Yx4WC7YyeDxczpB88QpJKCyrzs1LRiuasVAGD2Lp4JgS37e%2B6OTcIojiBNw3yEoai7Qt%2Bjsyg1jWPo0v4ZAqyoMkPRM41MzoF8LKmFZlhmCl6vEAN/P%2B503SZC4DDuJ4bR6KE8xlBUegFBkAiTH4i1Fz0gz5yMi01HUAh9BMWe5LXXQ8w3sxV8MCS17Mpd6BizRd4sPerAotlbBIW0cIZpDJbwqXnU1LVtR1khdeOuB9a9DlcB9zkG6sCCYEwWAJCepCeZI/j/OFCKSBokhmJISGJd5oXRRwsWkPF/hmP8/gkIIl8v4Xy%2Bl9JcAiqFXyc9dqpXSiATKBtcoFV%2BkVI6ZVgagxerVNg9Vl7XWQAYIwd1Qr/C4P8UyvUiAJ0GotR2o17bSEdtNF2c1dBQxWmtdG09Z7zz2hwQ6JU/hHFOkvS6LUiHs1IeQyhj1UDPXiIhP%2B%2B8vo5TQdg%2BI5UQYKIBi9FAxCIahS4EEGgtBYbw0RnNTGqNrY2OxrjfGDhrbE0YAQMmFNdrU1pvTRm1tWa622KZfAZw6h8yZlQ1QQsXjWzFl0XaUsZao3lkEz6CcVZOXVprTA2s2ZGD1qAbKhtjYKFNubS2jBrYMLtuNZhshWGzVMhw92%2Bso5WEsD7GIfsL6B2DpwUOBBw7%2BEjl7GOcd4i0KThfOuPR06ZxyGXYIGdh4F3LmkYuWRm6LIrpkFZNcU7t16H3LZA8271yOf0PZPcxj9H7r3S5edu5TzWBsSee9P58LgZwcRV0cSGJkRQ64EAt40OUXvT6h9SDH1PiMC%2BnkTFBAlt/X%2B%2Bl/hhX0qFMwmLkK%2BUgSFWBc14G2EQQfIpKD4BoOKsdbRmjiC4O2E0FgLUWAKApNiCkXAyFShmD1fANCBpDVkIw2pNsGmuwCMtVa61ma8J2oSg6GCTpnVUMy1l7LOX/G5aqCAT09FKLev4VRyCNG6MBjS01%2Bi2XJGSBcDloULhaouCq5hMN4iWKRijbGdjPU4zxgTFxCiSbuPJpTYJmAaZ0zEH41WAT8mpNICEnm4SBZROQMLWJgh4mS2lrLd0KTFbpOtlktIOSdb5PCIU76fASllItlbVW1SxoSDqVNZ2jSdASsMZ7aONhEndIDkHTITMdhh27e0iwscF7x0Tv2g55y5l3KWegK5hd1k9EXTs4ojyR6nNTh3W5JzW57ouUPbdqyblNwWQPTuZ6a5jwnuNWVBKUrfOdUcFlbLKQaq1ZvPlJAwVGqKUfE%2BZ9KDT2RQEf%2BeKHJmFg1wXyGgkIYufQvTgCCkFAcviAa%2B5DQH6Sfv4fSiGHLBU/v4OVL60qku%2BtPbqKGBEQsw%2BrdIzhJBAA)

By turning `(...||Pred_0<***>::value)` and `(...||Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AnyConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyConfess<Pred_0, Args...> && AnyConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept AnyConfess = (...||Predicate<Elements::value>::value);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgkv6kAA6oCoRODB7evgFBaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJM/jcwNBr0wELcTC8RAAdKiIdhrsgDAoFNdlMRMPhRMDSNcCABPFKMViYVHI7BPRgEBTowFoBgbFIEa7nBjkjwMKiYHHXCEAEWuEDpJgA7G5ZW58YS8MS4ZCGSCmQoQCAAG5iLxq7A6/XeTCLCFWC6A76/E42g7XAAqwuZ73tXzth3%2BDpuSvQAH0NO69v9oY9YfDESi0f5sICxsQvA48QTAxpAbKredrrnrjNHMhMQIxphVCliNcYqhPNdTYbRTKLAQk3CZWLLZn253rZ6/WmA1wQzswyCI%2BDIdHUNK4wmW8nuf7B13s3n801C8WGKXy5Xq7X65hG83W7KO/5s2eewC%2B3trgA1Jjk4ejmEThFI1B3VkXRMLh9PiugJrgWKpbjuFbXFOdYGkeWa3FeF5duel63js1xUF4DAvoC4ZgmqUKUtSbB0ucxDACys4XASACOXh4ASuK8vyAhCji8JLkEPLkQoM7xhc7IQXuNa0BhWEQBaTYEgQazYVQYhKJ23a9kCY74fCFJUswJGomRFE/mRmB0Qxwo8nyApsZRioDlxem8bGGLmAAbM5ZksYKwpWUuXCknZfFsiWwK7lWIliQwElZtJslkqeSHKTelyOi6Yw4b%2BG4qgGTA4vEBDUFh8KPuS8JcKycYSRaF4cMstCcAArLwfgcFopCoJw8qWNY%2BarOscFmP4PCkAQmhVcsADWIC1U5yIABxOVItUyk5kgAJz%2BItfX6Jwki8CwEgaEEjXNa1HC8NqQRDU1VWkHAsAwIgICrAQKRIuQlBoA8dDxJENKcKos0ALRLdcwDIEWUjImYvDKkQxB4Ogej8IIIhiOwUgyIIigqOol2kLoPkAO7EEwKScDw1V1Q1w0tZwADySLPdyqBUNcf1OYDkjA6D1zg2YkoeB99CVuY/WLLwF1aMsEBIO9KSfWQFAQDLcsgMAUhmHwdDAsQ2oQDEVMxOEzTkqTvAG8wxDkjTMTaJgDgm6Q73PAQNMMLQxs41gMReMACK0LQ2rcLwWAsIYwDiB7JkOHgurClTZa20imwDeEwI1TjtB4DERMWx4WBUy2eC7YHpAx8Q1ZKGKIKhxnRjDcsVAGBR954Jg%2BM01p9uI8IojiGjXeY2oVN4/oocoNY1j6Jn2qQMsqBclkAf/WM6DiqYHWWGYR2l7DWDTxJXS2/ULgMO4njtHooThIMFTDD5hSZAIkx%2BHf6QPwwcxDAkPl2IfPTjK0Z88jf1qL/AQvQWgfxvl/Ww/8n56BmBAq%2B8xb7LAUN1DYEhyYcHqqQQ6vBjoswBkDEGYNJAQ0lLgQgJBRR9S4KLQaddlgIEwEwLACR97jSSMiVaMpJAaEkGYSQTl9qTWWptDg21SC7X8GYZE/gnIymmv4aatVapcDWstaauCqbHVOiAc6ddrp3Slg9emL0FZK0Ft9Ngv0iEcyxKHbmy1kRcGRM1aGJA4YI1kMjXu0h%2B5KEHjjXQ6tCbExNlgnBeDqYcDpk9JE1wmaELZkDBxRgnEuLcXzVAAt4g0JkfQ8WV0TGWPiK9RWOTZaCxQAYIwXBlpcCCDQWgWsdZ6xxmbI29tOkWytjbO2xdHZMhdm7Kmntva%2B39vbYO1dNjNXwASKOMcA7uNUAnYE9sU61CphnLORtc5zLFrDIuA1S7l0wJXEORga6gEuvXRuChm6t3bowTuPie6o38bIAe2NmohJHrXNeVhLCTxiHvWe88SycCXgQFe/gxRAusJvfB284axxngfKOzgICuDgT5S%2BZRP56HvvUPFqRX71EgQsYB3QwGwMAc/TF9RwH9CQUS7%2B9LciMoQaywlUDMErDWBguh4iok6M4Mk9mmJanAAya44MEBKEw3yXQsWjDSDMNYcMDhe0ghp0kdI2qyIVq1WWmYM1ZgnLTXUUtbRONdG2H0Qwu5Rj4AmMegzcppTiDWM2M0FgQMWAKF1EWXU9TkT4TGFDfAMMvE%2BS7r4z56N5CBN%2BToAIpAwkk0DpEym9raZmMZszVQgbg2hvDZG7kEB%2BZVLycLfwhTDElMqXLL1LbqkhpSCkAMYbloBkrQGEt/jNbxDafrQ2FtukTsttbQ%2B9shmCBGe7eZmAvY%2BzEFM4uMzrmHNIAs3%2Byy45rOQInTZghtnp0ztnFieccYFxObwM56QLlV2ueEW5Es%2BAPKeW3DuxcE0fIkF8jGqah4ZplWPdeNhdngpapC7cnAtjL0g8CiwyKWqot3vAVBICsV%2BBxSfMlBLr7UvJUULIZKSVZCpbfJlf8%2Bhkp/nhllNHoE8sY//VjAq0FCtRrmu1R0JVDuuEGkNdYK2whSoqmN1DhaqudRLJhLC2GUCwQagIsibV9TMDprg00NBOVNQJ/BnA9EGLuWNEYLjlG1QEf4WqBm%2BqLXEf4PNgmToKZGuIyGxmYlqosyXUdWREhAA%3D)

## Links

- [Example](../../../code/facilities/concepts/pagelivore/any_confess/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/concepts/any_confess.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/any_confess.test.hpp)
