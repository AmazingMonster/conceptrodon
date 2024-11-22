<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateSituational`

## Description

`Pagelivore::CognateSituational` accepts a list of predicates and returns a function.
When invoked, the function returns its first argument if the argument list satisfies all the predicates and returns its second argument if otherwise.

<pre><code>   Predicates...
-> IfTrue, IfFalse, Others...
-> (...&&Predicates&lt;IfTrue, IfFalse, Others...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
CognateSituational ::   template<auto...> class...
                     -> auto...
                     -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct CognateSituational
{
    template<auto, auto, auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };
    
    template<auto, auto, auto...>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will create a function that returns its first argument if the sum of all its arguments is less than ten and returns its second argument if otherwise.

```C++
// `SumLessThanTen` is the predicate
// that we will pass to `CognateSituational`.
template<auto Initiator, auto...Args>
struct SumLessThanTen
{
    static constexpr bool value
    {(Initiator+...+Args) < 10};
};

template<auto...Args>
using Metafunction = CognateSituational<SumLessThanTen>
::Page<Args...>;

static_assert(Metafunction<1, 2>::value == 1);
static_assert(Metafunction<10, 2>::value == 2);
```

## Implementation

We will implement `CognateSituational` using 'C++20 Constraints.'

```C++
template<template<auto...> class...Predicates>
struct CognateSituational
{
    // Primary template will only be selected
    // when no specialization is available.
    // In our case, it is when
    // (...&&Predicates<IfTrue, IfFalse, Others...>::value) evaluates to false.
    template<auto IfTrue, auto IfFalse, auto...Others>
    struct ProtoPage
    { static constexpr auto value = IfFalse; };

    // This partial specialization will be selected
    // if (...&&Predicates<IfTrue, IfFalse, Others...>::value) is true.
    template<auto IfTrue, auto IfFalse, auto...Others>
    requires (...&&Predicates<IfTrue, IfFalse, Others...>::value)
    struct ProtoPage<IfTrue, IfFalse, Others...> 
    { static constexpr auto value = IfTrue; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v
    { ProtoPage<Args...>::value };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQAcpK4AMngMmAByPgBGmMT%2BAKykAA6oCoRODB7evv5BaRmOAmER0SxxCZLJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHASYLCkGeyYAzG57B0eYp25MXkQAdE%2Bn2ADUyAYKCk8PysSY%2BFEewULxMGgAgrNiF4HK8PMBmHshIQvExemIweCTAB2KwQ14E14AeiJrz%2BeBYzQAnq8Loc0ZhXgB3Oi0V4CWg0uKvWoOAGYwnE0lMhCMV4MVA8lJ1PBiPAALzRWVeeAUryYADcmHQmDF6A8BYSSa8AJIMdmbd5MJSkFUEFVqkWMQ0E40QH7mABsXr%2BALwQMwILOJqoABVoZhbSGAGJiG2vADyBFFxG%2BzxO2BAIC13kwK1emBzqOBtMlVDjmAN%2BMJdKuNzuRFNYYjtobkpjFdb91QPyTKaD2BdPII0Nhf1QRGUTGA12rBJxFmHSuQ7wEs0wqhSxHV3deRcZpwAIk3Y7QlKdFzjDxfMUPjaGEKrXikBrK2Qppcg3wqlQJmazXm5Xk9nQO9STwKhXndZ4zG9WDfUBBkgzcENwy8SMT07RNk3iNMDQzLN93zJ8R3QqtwUFWsGXrXdUJbHdGw7M8MLbXscNTUE51ef4AEcvDwf41Wgg1YJ9f5EOBG46PQqMqFPeM%2B1wj0COzMR0JWIcoRhe1x0nadrmDZsZMw5jbUU1NlLeIcFyXRwVzQBh103bc2z3NSDxOY9pIMy9sWvE48SxLiqOOM5WKecFgH%2BfZGAIAchy8DIjDJfTXiPMliAnVApxnG5IuithBDw0EAtvYL9npULbm7H5wWIYB4q42Zl1XRy9mchjJRyzAAH0NWs3EMqy7q8vq4qVP3NK/JvCErxmoLwSJAAqFbVrW9aiUxZbVteUNAzi141s2iFtvWs6VuOhbjRMT0NCEHwQkDBQH0MPaGBujQHVpUVn3E/1qJO0lkzRZlGRZWg2RfL5SzS274URTBkQIYssgxW7yJCgzqsYhhMjREgu0eCKxs4yFSNhe6WEer4XoYN7b1xTSmjs1qnK3QDUE8NzcwGiwIDNPGiGIawPUsOqGvzG5Xi4DQ5tK2bpvlhbMZoomHnFxrwUS8JgFeABZTAmioLwGHqP90vhhkkZRgQMTOSnqeehBXudDNMSzEazg1yz5sxZq7J660lBaCADaNk2zfes4uFtMwXkI9y0s89KuA0pX/f9QOvniAhQ8NphjdN3obhl2P49U3Mk/848zDTiwODWWhOESXg/A4LRSFQTg3GsaweQ2LYDzME4eFIAhNAbtYAGsQGxDQHhOMwuGxE4TkkMwNACbEAE4AmkJuOEkXgWAkDQNFINuO67jheAUEBz/H9uG9IOBYBgRAQA2AgUnuchKDQA4dB4iRFYDsVQARPQAFpPSSFeMAZAK4pAPDMLwP0Qs8DoD0PwQQIgxDsCkDIQQigVDqCfqQXQMcmTECYCkTgPBG7N1bhPTunAEz3B/vaVAkFwFQJgXAhB0tJDIKgh4QB9BtzmBHisXgj8tBrAgEgABKQgFkAoBAJRKiQDACkGYPgdA9ipkoDEZhMRwjUjobwUxzBiBUgTDEbQdRH6jwAYVAgCYGCcmYVgGIXhgC3AhnfbgvAsCUiMOIMh%2BB/j1A1IGZhG46j3B2KPcIewD4d1oHgGI1CbEeCwMwkcFILGkBicQGI6RMCHn2IYYAGSjATzWFQAwDUABqeBMBMgTNKNuo9sHCFEOIAhvTiFqGYRQ/Q1SUC90sPoTJd9IBrFQCkXogTIGzFAp5UwlhrAb14KgEpxAMGxPmV0HoWQXAMHcJ4doehQgLHKJUPQhRMgCCmH4GOTzehDHuaMGOwEGhzFeXoP5Ah%2BgtC%2BSMBIvyAVXLyFCgY4KliQrWAoAe2wJAMI4C3C%2BzDr6vB4dA2B8DEFCLMFBXAhASBpWHqnGR9S1iiiYFgBIEBp7%2BBOA8beJxsSSA0OvSQt0NCJE9NvfQnAj6kBPiPB4nouCegCLvWViRJBcESJyz02KyHX1vvfMe9SX7vwUZ/dhv81EaPESAtgnBmgsA1NiSBTB3gGGSlwbeDwuAPA7mgkgGCsGyFwQM6QQylAjLIboXRVCaEWIxViy%2BuzWHGs4ZBa1tr7WOuqdLV17rPoQFEco8RVLF7SN1U/eRijUBiPiH/dR5a82jGTXaj41SXWlxoLQAxd8IDGLIVY8xQTSA9psXYhxDgikuNiu4zxETMA%2BL8WIM8RSQnVPCR3SJji8AxMCZ61QCS9hFJSd0ZhGSsnUlyTsDuBST59pKWUpQlTQk1J1nqxp04FCtPaZ0xgRTen%2BvwYG2QwzSEdzDeMupmyrDTKPXMllncllZBWWso8YHtlX32YcqDyLuhrucBAVwgKY63LKBCx56RnnZBhW81IJHPl3KI78zDkdQWtHI0C%2BjvRGMIoeXCyYzGuPzEI4i9F6xNhotTqKzFTDNWcHVMQG1dqHWNudZmj1ZL8BCwLTS4tcj6WYEZaMaDB9xWStdby7EqrsQrz5TAmOsaWE31sDq2Rz9X4fy/hwqtZrgGgKtTJvhLAFAahXBqF1DwrizFQap71mCY7fv6b%2Bwh8hg2AZ0CAE4pAI20KCdGiTV943f3uOyJNPnYF%2BYC3uYLoX7Q5prSogtJwi2OdLSgar4j3PNdGAFlIKQ%2Boup6hVwORW9FttwkYkxZibFFIHbY%2BxjjR3ltcROqkXjp2%2BP8fOvti6wlnuCQJNdG64nbuQIkvdggD1kKPdkqkp78kHMvaPa95S71LsfSWvgTTX1tI6V0r9frYsSD/UQxLoyUsgeMFMmwkH4ALNg2uTgRI1mTK2ZYHZndUNYHQycrDfgcMXLw8EC5HGfmUaKFkXHHysgE8hRjhj0LcgUeBX0OYFOgU0%2BubxpnomUXCfwVljVOWODSZYL5/zgXytIUq%2BStTkiNMNe07p5lGLDMgDMK61eiREi8plhoVe2I5W87jXZu%2BD86WkBnsr6V2IAiwU9IkHeXAN6yt0QfE42X9e0pLRilBevbNu608U3CZzJBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/cognate_situational.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_situational.test.hpp)
