<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AllDeceive`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-all-deceive">To Index</a></p>

## Description

`Pagelivore::AllDeceive` accepts a class template predicate and a list of elements.
It returns true if the predicate evaluates to `false` for the value result of every element and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...&&(not Pred&lt;Es::value&gt;::value))</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept AllDeceive = REQUIREMENT;
```

## Examples

`AllDeceive` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&(not Pred_0<***>::value))` and `(...&&(not Pred_0<***>::value)) && (...&&(not Pred_1<***>::value))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {false};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {false};
};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...&&(not Pred_0<Args::value>::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires (...&&(not Pred_0<Args::value>::value)) && (...&&(not Pred_1<Args::value>::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQB/qQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJ/kl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcAPQAVAd7ANTKxJjoAPoaR4d7OyYaAIIEmCzJBi8m/m5MXkQAdICvtgHo8ZsQvA4TmdLhpQSYAOxWJ5HVFHGZMRzII5oBgzTCqZLEI4xVCeI4ANzEXkwR0RFioYiUiIAIl9kY9Wez4U99odoecLlwbod7k8Xm8Ppgvj8/qhAf9gaDwZCCALLlx4UjQWj0Y0sTiBPjCcTSeSqd5afTGbRmQi2f4OVzHTzHnyDkcAGpMACeIoOYuer3emOl31%2BRCOAEklU8VVDvT6tRzdRiDbjjUSjhHUJTqVakTH7dyns6nbzbkcqF4GP67qCJSHPt8CD7koxWJgFY9iMAFLGe5gAI5ePBnBRHCAK8wANlnEAYqDVp0FcO%2BPb7IBAFppwK3O8wy2WoIzLxNJLJtCrNYgx6RZwIG1rNuZLuLpfFwalMtb7eYbG7Xt%2B38EEnjOEcx0wCcpyBMw5zghcl3VK4ZQ3BR93zPdt3zI86Tg2dJ2nfCEMXZcYSFVCgIwy0sIPI8TyNM8szNK9qwYW96QfJ8jgICEwysd9OQrfkABUoLVW5Ax2HYjmwYhiBIZV9TwZALiYBQlGaagaxlRMZU1EDgVvY9HQ4VZaE4ABWXg/A4LRSFQTg3Gsax0XWTYrTMfweFIAhNDM1YAGsQEsmd/gADhnKRLIRGdJAATn8WKvP0ThJF4FgJA0IJbPsxyOF4dCgj8uyzNIOBYBgRAQHWAhkj%2BchKDQN46HiSJO04VRIoAWjio5gGQbEpH%2BMxeHOQgSDwdA9H4QQRDEdgpBkQRFBUdRStIXQuFIAB3YgmGSTgeHMqybP8hzOAAeT%2Beq1VQKgji6mdeskfrBqOYazEnDwWvoYlzG85ZeBKrRVggJBmuSVqyAoCBIehkBgCkMw%2BDoF5iHQiAYnOmJwiaH0jt4XHmGIH1LpibRahKnzmrYQRLoYWgCY2rAYi8YAfloW1CdILAWEMYBxBZyC6gpKDzoJWo/m2HzwheCyNtoPAYn20mPCwc7eLwTLuF4MXiFJJQWVeAWlaMfzVioAw%2B09PBMB2y6/x52bhFEcQlpd1a1HOrb9AFlAXMsfRlfQyBVlQZIenQjhupmdAvhZUxLGsMw8v14gpvFsPOm6TIXAYdxPDaPRQnmMoKj0AoMgESY/G2quekGcuRm2mo6gEPoJiL3JW66Kn6lmJvhgSVvZlrvQMWaIfFhH1YFHcrYJBOjhrNIXLeHyx6er6gahskEbJ1wCb/q8rggd8i3VgQTAmCwBJb1IYLJH8f5EoRSQNEkMxJBnbLQvi1KHB0qkEyv4Mw/x/AzgROFfw4VLKWS4EleK4U17nXyoVEAxULblSquDGqN0Gqw3hn9dqbBOrb1esgAwRgPrxX%2BFwf49lxpEAztNbaLt5ru2kJ7JQ3sNq6BRntA6hNl6r3XhdDg106p/COPdLez0%2BpUIFrQ%2BhjDvqoF%2BvEPCYDz4gzKng4h8RGpww0VDP6KBqFI3ilwIINBaDo0xtjDaxN8Y8xcaTcmlMHA81powAgDMmbnVZuzTm3Nda8xNkYIW9l8BnFFuLDaktkDSx5nLLo50lYq3xurbY9ktY6x8vrQ2mBjb8yieEUApVLbWwULbe2jtGDO1kJwxa3DZBe3WvZARftzZJysEHTJocH4RyjpwWOBB47%2BEToHCwqcN7p0zkMuefd25%2BAgK4ce21S6lGHpXNI1csjdzrikfZjcy67N7rnDuY8jkTxWT0TucwdkzwnjcnIxzJ5PIWBXM%2BawNiL1%2BQrMRaDODyJejiSxKiGHXAgEfFh2iz7A0vqQa%2Bt8RgP2CjYoICtgGgMsv8BKll4pmGJXBcKiC4qoI2ug2wmCL5VJwfAPBtVbrGMMcQUh2wmgsD6iwBQFJsQUi4HQqUMwxr4BYVNGazS3atOWvIXhnSdABF2vtQ6utRFnWpVdAhd0HqqF5fywVwr/iirVBAH6ZitEA38Lo7BBjTHQzZY68xArkjJAuEK%2BKFwzUXANdwtG8RHE4zxqTNxoayYUypj4jRdN/GM2ZjEzAbMOZiDCT5Pmptcm8Fif3MW0cmGqCli8VJgh0mK2VqrH0OTNYZwKXreIxTSmmwqdgq2TAbZ2wdk7cJHDZUSDaStRVPsVWWIDsnAZId4Dh0jpkaOOw47jv6bMtO8RWFZwfm3Ho%2BdC7vJLgXaePyTmFEyJs49BzD0txzv3a5/Qz1boHv0S9I8xh3tuaPJ95yXm/Pnv8xamqqV5VBf6o4fKBWUhNWaw%2BEqSAIrtVUq%2BN876UGXrigI4CKVeTMNhrg4UNAziJYBjenAMFYIQ4/EAz96GwMsl/fwll8NeVioA/wWqgMFXpaDZeo0iMSKReR/W6RnCSCAA%3D%3D)

By turning `(...&&Pred_0<***>::value)` and `(...&&Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AllDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllDeceive<Pred_0, Args...> && AllDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept AllDeceive = (...&&(not Predicate<Elements::value>::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgkv6kAA6oCoRODB7evgFBaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJM/jcwNBr0wELcTC8RAAdKiIdhrsgDAoFNdlMRMPhRMDSNcCABPFKMViYVHI7BPRgEBTowFoBgbFIEa7nWi0AAimA2eAAbphrhD%2BdcIHTzAA2eUQBiobn4wl4YlwyEMkFMhQgEAisReLXYA1G7yYRaLCFWC6A76/E4Og7XAAqmDGuI%2BLqdPvtX1davQAH0NO9nRdoY9YfDESi0f5sICxsQvA48QTQxpASYAOx287XYvXGaOZCYgRjTCqFLEa4xVCea4Wk0SgtUMRKfP8225vO9/yF317TOEkNcCN7f7RsFahFI1CypMpghpjPBif9wsl0tNcuVhjV2v1xvN1vi/MWTu0bsDvv2%2B9D3OBm4ANSY5KnOxnIJj4MheNUDuVkLlTdNuQ/clt0BXcyw1Q9jzra4gJbY1LwLW4ewfAEn2HV9RyoLwGG/X8YQAqFKWpNg6XOYhgBZFcLgJABHLw8AJXFeQFIVMFFedNyCHl6IUZdkwudkkNPJtaGuIiGAgG0CwJAg1hIm9u2fe8AyBP853hCkqWYGjUTohjQLozA2I4z0eT5QVhTFeFBNJMzRMTDF5XlOyeMcgSswnVyRLEtkq2BE8GxkuTiMUq8VLUsk0y1KxtIBAidndT1uX9c54OQEMmBxeICGoYj4Sg%2BEuFZJNFJtIcOGWWhOAAVl4PwOC0UhUE4NxrGsUtVnWS8zH8HhSAITQGuWABrEBmrlZEAA45SkZq8zlSQAE5/HWkb9E4SReBYCQNCCdrOu6jheH1IIJo6hrSDgWAYEQEBVgIFIkXISg0AeOh4kiGlOFUZaAFoNuuYBkArKRkTMXh1SIYg8HQPR%2BEEEQxHYKQZEERQVHUe7SF0LhSAAd2IJgUk4HhGpatrJq6zgAHkkU%2B7lUCoa4QblcHJEh6HrlhsxpQ8P76HrcxRsWXg7q0ZYICQX6Un%2BsgKAgZXVZAYApDMPg6GBYh9QgGJGZicJmnJGneHN5hiHJZmYm0IU7rG37ngIZmGFoK2iawGIvGABE%2BX1bheCwFhDGAcQ/Zshx%2BNDzqayFJFNjG8JgSaonaDwGJKftjwsEZtc8GOsPSDFYhGyUQVI6MHOjEm5YqAMBi3zwTAyeZozrdx4RRHEHH0fkJQ1EZkn9CjlA%2BssfRc/1SBllQLkslD0GxnQSVTEsawzAuyvkawBfFK6F2shcBh3E8do9FCcJBgqYZScKTIBEmPxn/SV%2BGDmIYElJuwZ8BC9AmNfPIADahAIaOMfo995hP1sDA9%2BegZgtF/o/f%2BywFCDQ2BIOmHBWqkHOrwS63MwYQyhjDSQcNpS4EICQCUI0uAy3Gk3ZYCBMBMCwAkE%2Bs0kjIm2nmSQGhJBmEkHKU681Nr7Q4IdUgx1/BmGRP4OUeZFr%2BEWs1ZqXAdqbUWkQxml1rogFuk3R6L1FZvTZl9dWmsJaAzYMDch/MsRRyFptZEXBkRJ3wEjFGaNZCY0HtIYe%2BMx5E10HrCmVNrb4MIcQpmHBWYfSRNcTmZDeYQ1cUYdxnjvGi1QOLeIjDFEsLlg9Sxdj4jfQ1oUlWEsUAGCMFwTaXAgg0FoIbY2psia20tr3Pp9tHbOwcL3d2TIvY%2B0Zv7QOwdby9wjlHGOnV8AEnjmKROCNVAp2BL3DOtRGY5zzpbQumxOolzLmNSu1dMC1yWeEUA91m6twUO3Tu3dGC92HkE7GITZBhMJp1SJk9G7bysLPI5x8l4ryrJwdeBBN7%2BH5GC3e%2B94iH09PALBkD47OAgK4ZBpM75lD/noF%2B9RCWpC/vUdBCwIHdGAUgsBH9T64ugbMOBpKAFMtyCy1BsCSUYLwSsNYuDmEyPiYYzgGS%2BaYiacAXJXjwwQDoUjEpzDZZsNIBwrhwxeEnSCFnORCjmrIi2s1TaZhLVmDlItHRG0DFEyMbYExrCnnmPgJY967MalVOIA4zYzQWAQxYAoEUFYRQtORHOMYCNfEkH8aTb5A9fl9wBePAI5NKbUzDnEhmTqWbWI5lzVQIaw0RqjTG7kEAxb1OKVLfwZSzGVLqarX1raGnhpSCkEMkbNohirSGUtISDbxG6WbC29sBmTodk7F2YzCke0mb7FZmAA5BzEPM8uiz65nPDnHRwGzGbJ2QKnPZggDnZ1zvnckpzi7I0ubwa56RbkgnuY3d1LcmBtw7l3Hu5dk1YwkH8vGo9AU6EzfK6eO8IXzyxV1GFR5OBbA3tB8FFg94kIPijTFi9WX1AvlfXlt9L60oQeSrIlKKMlE5UK%2BlUCQGtGZSgnF9RGNkf/ogvolL%2BUceFdg0V2M82OoutK4d1xQ3hpbJW2EYxaHxslkwptTz2GcO4ZQfBxqAhKPtSNMw%2BmuCLQ0HKC1ImSGcGMaYlTpA%2BH%2BE8Ro5qoj/DNWMyNdaMj/D5tE1dN18t8HwzM4kzV1nK4ZGcJIIAA%3D)

## Links

- [Source code](../../../../conceptrodon/pagelivore/concepts/all_deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/all_deceive.test.hpp)
- [Example](../../../code/facilities/concepts/pagelivore/all_deceive/implementation.hpp)
