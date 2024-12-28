<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AllFalsify`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-all-falsify">To Index</a></p>

## Description

`Pagelivore::AllFalsify` accepts a class template predicate and a list of variables.
It returns true if the predicate evaluates to `false` for every variable and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...&&(not Pred&lt;Vs&gt;::value))</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept AllFalsify = REQUIREMENT;
```

## Examples

`AllFalsify` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

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
template<auto...Args>
requires (...&&(not Pred_0<Args>::value))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&(not Pred_0<Args>::value)) && (...&&(not Pred_1<Args>::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQgAMyJpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAggSYLKkGzyaJbkxeRAB0AM%2B2HuD3GxC8DmOpwuGhBJgA7FZHocUYdZo5kIc0AxxphVKliIcYqhPIcAG5iLyYQ4IixUMRKBEAEU%2BSIezNZcMeewOULO5y41wOd0ez1e70wn2%2Bv1QAL%2BQJBYIhBD5Fy4cMRINRaOaGKxAlx%2BMJxNJFO81Np9NojPhLMSbI59q5Dx5%2B0OADUmABPIX7EVPF5vJgfL4/IiHACSCseSshnq9GrZ2vReEx2MNBMOYdQ5MpFsRUdtnMejod3JuhyoXgYvtuILFQZD0v%2BAIexGACmjbcwAEcvHhTgpDhA5eYAGzjiAMVAqk782FfNsdoEgEBmqlLJYg9PPI1Ekm0SvViBbxGnAjrGtWxlOosl0WBiVS7NypedxLAx6nPsDzBDkeAmYE5AVOM6qpcUpviua55puNJAeOw6jghIHTrO0ICpB7bvtgq7rpgm7bgau6Ziah5VgwJ60uel6HAQ4KSreLL3i6FYACp/iqNz%2Bts2yHNgxDECQiq6qm5xMAoSitNQ1ZSuqH4nlu9ocCstCcAEvB%2BBwWikKgnBuNY1homsGwWmYiQ8KQBCaCpKwANYgAEY5/AAHGOUgBPCY6SAAnIkXnmfonCSLwLASBoGikFpOl6RwvAKCAkXWdpKmkHAsAwIgIBrAQqS/OQlBoK8dDxJErBbKobkALTeYcwDIJiUh/GYvBnIQJB4Ogej8IIIhiOwUgyIIigqOoKWkLoXCkAA7sQTCpJwPCqepmk2bpnAAPK/HlKqoFQhyVWONWSHVDWHE1ZjDh4xX0IS5gWUsvDJVoKwQEgRWpCVZAUBAH1fSAwBSGYfB0M8xAJRAMRrTE4QtF6i28DDzDEF6G0xNomAOAjpBFWwggbQwtDw%2BNWAxF4wDfLQ1rY1gLCGMA4gk7%2BDh4GSf5rXimO/FslnhM8anjbQeAxHNKMeFga30XgYXcLwbPEMSShMi89NC0YNkrFQBgdu6eCYNNG2pIw2M9cIojiINpsjWoa2Tfo9MoIZlj6MLCWQCsqCpA0CUcFV4zoJ8TKmJY1hmDF8vEJ17Pu90mMNC4DDuJ4HR6KE4RDJUIxTUUWQCFMfjZxkucMPMwwJFNdhx70ExtMn%2BQV3UVcCH0rSl5n5e2DX%2Bd6LMrfpwsWcrAoJmbBIy0cBpUVrbFB3VbV9WNZIzXDrg7V3eZXCPVZGsrAgmBMFgCQnqQDmSIkfx%2BfCkgaJIZiSGOEVOT5QUcCFpBhYkZh/IkY7wi5iQuQCAELg/kfIuSnuNWK8VErbxSq9TKb1srbXyj9P6t0ypsE4IdY6WIDBGHOj5P4XA/g6TakQSOXUpqmz6hbaQVslA23GroYGs15oI3HpPaKvBYpbVyr8Q4e1Z5HVqsgPBwACFEJIVdVAN14jwU/lvZ6qVEFoPiAVX6MjPq3RQGIrgPkuCRRoLQMGEMobjSRnDbGFiUZowxljWWOMZF4wIATIma1Sbk0ptTBxtNVZbB0vgU4LM2Y%2B1IaoLmzxsZ8zqGtIWIs4bi38U9SOMtLLy0VpgZWdMjBq1AHAvg2sFC631obY2DjqHmwGnQ2Q1sxo6WYfbdWwcrDOziW7Y%2BntvacD9gQAOiQg5OwsGHbhEco7tKHo3FmzgICuG7lNNO5Qy56Bzg0OZaQi4NDbosBuPRm5dzrgXWOUzGg1y2VnTu/Q1m9wGP3JZm9VjrFHvcgWnDp6cCETg0R9MJHEKuBAVe5D5GbyejvUge8D4jGPg5AxkUBZvw/gEP4vkAg%2BTMKioCLkQHeQgTFTg0CkoazSggpAOUdrqNUcQDBWwWgsFqiwBQZJMRkj0X8CU4xWr4HIZ1bqsgaFVKGvIBhdSdBJBmnNBassOGrUgZtZBu19qqDpQyplLK2UqggNdLRcj7qJEUYSlRmivrksNdoxlqRUjnGZT5c4arziKroaDeIpjoawxRlY11qN0Zx2xrjRgLjCbEwCZgMmFMxDeMsr4nJSTSCBKriEjm4TkDcyiYIGJgthaiy9IkyWKTsbpIyJklWOTwh5JegUpgOs9YGyNlpSyFT%2BoSGqcNIVttRViMdiHVprt4Aey9tkH22x/YdpaUM8O8QKHR2PpXY5Cck55EOQsjO2z1nFGyGslZ2Qzkd2nQ0Futd5090mbu05tz24932QeiuJ7FlnvucPR5A0pU4u4e8%2B1hx6WMvJKq4MnEV6cpIECvVcDd770PpQce8KkhfyxeZMwcGuAuQ0GOFFz71pxVsDApRm4T4gDPkQgBARb6JACEh8yXkX6JGlbi9DWHx4tVQ1A2BL0Vjy0yM4SQQA)

By turning `(...&&(not Pred_0<***>::value))` and `(...&&(not Pred_1<***>::value))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires AllFalsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AllFalsify<Pred_0, Args...> && AllFalsify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept AllFalsify = (...&&(not Predicate<Variables>::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQgkgDMpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJiSbhBYLemEhbiYXiIADo0ZDsDdkAYFAobspiJh8KIQaQbkjUWiAGotPBMGL0BQYoFoBibVIEG4XWi0ABiYkyVAAnjdIQARG4QNEo8wANjlEAYqE5BKJeBJ8KhNOIdIZmCZSWwIBAADcxF5MEslpCrJcgT8/qd7YcbgAVfUEPGfZ2O71274u1XoAD6Gg%2BTsuMKecIRFNQ0uZl3GxC8DnxhJDGiBJgA7LaLjdCzdZo5kFiBONMKpUsQbjFUJ4bmbvJhRXmqAL4TmxTbs93e/6roGM8GuOH9gCo%2BDNYjkfH0YagcnUyqR1w%2B/mi8XmqXywxK9Xa/XG82LW2LB3aEpcz2kvmbwPAQHbjSRX7gaDoxCoXH7omLsuaavhuQJbiW6p7geNbknOTbmq2uYWHcD53n2t73s%2B%2Bw3FQXgMOOuyTp%2B06xnO0oXMQwAGtgQKEgAjl4eCEni3J8gKeDCgiQahmS5GUQmi6XKyUFHg2tDYbhEDWnmhIEOseGXteqH9oOU4xj%2BpForxVE0Zg9GMfqXI8vyV7sUKnEjhoPEUQo/GYnKcqGaxJkcVCXFcFZfELtRgkViCh51qJ4kMJJiEyXJNwECmmpWMpT5Drc7rjPhALgcgwZMLi8QENQuEIuuhqSdad4cCstCcAEvB%2BBwWikKgnBuNY1jFmsGwIWYSQ8KQBCaCVKwANYgAEsoogAHLKUgBDmsqSAAnEkU3tfonCSLwLASBollVTVdUcLwCggJZ3XVSVpBwLAMCICAawEKkyLkJQaCPHQ8SRKwWyqGNAC0003MAyBllIKJmLwapEDq6B6PwggiGI7BSDIgiKCo6jHaQujuQA7sQTCpJwPCleVlU9bVnAAPLIrdnKoFQNwfbK32SL9/03IDZiSh4T30LW5gdUsvBHVoKwQEgj2pM9ZAUBAoviyAwBSGYfB0CCxD7RAMTEzE4QtEKeO8JrzDEEKpMxNomAOLrpCPS8BCkwwtA66jWAxF4wCIjy%2B3cLwWAsIYwDiI7%2BkOHgJr6sTVZm8iWydeEIJlajtB4DE2OGx4WDE5FeBrZ7pAh8Q9ZKGKoK%2BwnRg9SsVAGJRVJ4JgGOk6kjAW1DwiiOI8PN0jajE%2Bj%2Bi%2BygjWWPoif7ZAKyoBy2Qe594zoOKpiWNYZjbbn4Oh6P3Rmw0LgMO4ngdHooThEMlQjO5RRZAIUx%2BGfGQXww8zDAk7l2JvvQTG0e/5M/dSvwIfStA/E%2BT9bDvyvnoWYACj4LFPisBQLVNgSAJhwCqpAtq8B2rTL6P0/oA0kEDSUuBCAkFFO1LgfMuplxWAgTATAsAJEkqQAayQURzRzJIDQkgzCSFlBtIaM0locBWqQNaSQzAoiSLKHMI0kgjQCAELg80ZojVQcTHae0DoUOOkLC6wsroUzupLaWXNXpsE4HTBmWIDBGBZjNFEXAUQ1VBiQPAEN3LNxhm3aQHclBd1RroBWWMca6yQSgtBJMODkxusiG41NMH0x%2BtiX2Ni7EOPZqgTm8QSGiPIQLE6uijHxHulLdJYsuYoCsXLGaXBLI0FoMrVW6tUb621hbZphtjam3NtnK2jAbZ2wdjVJ2Ls3ZXgtt7YuWxBmB0cCHD2jjVARxBBbGOdRiYJyTtrVOkz%2BY6izp1XO%2BdMCFx9kYEuoAtF8Ergoautd66N2zu41ucMvGyE7ijGq/je6l3nlYQe6yR4MPHg0KeM854DwsEvdBK8XFrwYS/IOzgICuDAe5Q%2B5RH56HPg0FFaRb4NEAYsb%2BPQ/6gM/tfDeCLGjvwJafEB/QcUQIGFAjFZDVjrAQayuOoTVGcDiRYxJ1iuC2PsWGCAhCwZZLIfzShpBqG0JGAwga1TLJxyESIgIKJZoBBmmYHVZhZQjQUdNFRqM1G2A0bk7R8BdHXUpkUgpxATFbBaCwH6LAFAmjLCaIVKJpzjBBvgMGLjIayA8c8hG8gfHvJ0CAFIgTcaexCUTU1ZN9FUxpqoN1HqvU%2Br9ZyCAHNSmZJ5kkHJZdToixKeLe1VaymetSKkYM3qZrBjzcGTNXilbxAaRrLWhtWl9qNibTeFsemCFtvbYmQzXZiFGdncZpztmkHwISIOsyw4LOQJHZZghVnx0TsnIUWz067ItgcjIRyi6nPCOcwWlymBVxrnXBuVVOqPNhhIF5iMo3d1jV84w4Kh4xABWPCeFZODbBnv3BelhIW1WhVgEDFKt5Ip3jitFx9CW4uKNkHFWLsg0uAfCho/8P55HJcRt%2BcxmVAPAaS8jdHqPoto6yuB7K4ZJpNdtXlHabjus9U2XNcIkpisDcQnmUrNGCyoTQuhlAkFqtjWIo17UzBqa4CNDQsptVcfQZwdRh0ZVMKSHYmRAROFJACFp9qU0BFJGTdx3aUneoCOBrp8J0qtErFzpkZwkggA%3D%3D)

## Links

- [Example](../../../code/facilities/concepts/pagelivore/all_falsify/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/concepts/all_falsify.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/all_falsify.test.hpp)
