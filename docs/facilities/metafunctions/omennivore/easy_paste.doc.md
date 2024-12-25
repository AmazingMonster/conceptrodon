<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::EasyPaste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-easy-paste">To Index</a></p>

## Description

`Omennivore::EasyPaste` accepts a list of packed vessels.
It concatenates them together and uses the first vessel to hold the result.

<pre><code>   Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>...&gt;, Vessel<sub><i>1</i></sub>&lt;Items<sub><i>1</i></sub>...&gt;, ..., Vessel<sub><i>n</i></sub>&lt;Items<sub><i>n</i></sub>...&gt;
-> Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>..., Items<sub><i>1</i></sub>..., ..., Items<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Paste
 :: template<typename...>
```

## Structure

```C++
template<typename...>
using Paste = RESULT;
```

## Examples

- We will paste `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>` together:

```C++
/**** SupposedResult ****/
using SupposedResult_0 = std::tuple<int, float, float*, double>;

/**** Result ****/
using Result_0 = EasyPaste
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>;

/**** Test ****/
static_assert(std::same_as<Result_0, SupposedResult_0>);
```

- We will paste `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>` together:

```C++
/**** SupposedResult ****/
using SupposedResult_1 = std::integer_sequence<int, 0, 1, 2, 3>;

/**** Result ****/
using Result_1 = EasyPaste
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We paste `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>` together:

```C++
/**** Warehouses ****/
template<template<typename...> class...>
struct Ware_0;

template<template<typename...> class...>
struct Ware_1;

template<template<typename...> class...>
struct Ware_2;

template<typename...>
struct Con_0;

/**** Dummy Arguments ****/
template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult_2 = Ware_0<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result_2 = EasyPaste
<
    Ware_0<Con_0>, 
    Ware_1<Con_1, Con_2>,
    Ware_2<Con_3>
>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We paste `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>` together:

```C++
/**** Stockrooms ****/
template<template<auto...> class...>
struct Stoc_0;

template<template<auto...> class...>
struct Stoc_1;

template<template<auto...> class...>
struct Stoc_2;

/**** Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult_3 = Stoc_0<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result_3 = EasyPaste
<
    Stoc_0<Seq_0>, 
    Stoc_1<Seq_1, Seq_2>,
    Stoc_2<Seq_3>
>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
```

## Implementation

`Omennivore::EasyPaste` is implemented as a shortcut to the member `type` of [`Omennivore::EasyTypicalPaste`](./easy_typical_paste.doc.md).

```C++
template<typename...Args>
using EasyPaste = EasyTypicalPaste<Args...>::type;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzABsZqQADqgKhE4MHt6%2BeqnpjgJBIeEsUTEJSXaYDplCBEzEBNk%2Bfly2mPaFDPWNBMVhkdFxibYNTS257Qrj/cGDZcOVAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimMmujMh4mAq3R%2BdXN6f/xx%2Blwu1yOtw8DQYeAAbiR2CAACoAT2SeFEtGUTBmmC%2BhyBzDYCmSTC24NQkJhcNuJgA7FYriCCJgWMkDEyTLE3AQUYxWJgAHSCjnYEEzYheBy3ZGo9GY7HUum0%2B4c%2BnA347W4WLE4tzakAgxnM1lMdmc7nPAk4zHIADWmHcsiY82IwtFBHFkulaLEctNbmtdodgidIRdsRFDMVV1uMduXnSRlu5pxHPutwD9o8wedKoNNOVsVVIJ2GoASjUNuloTq9QarkyWWzMAbOSDY0mjU2OVyeZbBfzhbdkAYFJ8sw1nZdSG3Yw3jX7k32heGhyOx47nTYZzHF3z%2B9h6GxBJcFKRqdHZ7294KD8zGAQLKft0mr2x%2BwB5AgIaIKFsRk/uhKBBSii3oYlifrjiG0TApyt5HgQJ79sKZ5QZu3bwfej7IeGZ6ft%2BxAKDh/60qq7bxsEwAvs81KxGmXqyhBzYXjG3bPu2aGhrBbiYceRGCmevEPvxA64exsb4T%2ByEsbR2AgCAya5pGBZFspdagncQiYAAjl4UKwsQ8IMT6TG4gc%2BJ8kSJI4lpun6VSpHqXOXZmq%2BArLv%2BYpASBMomfKjn5kparXBqWpKOCtYMvWnYms2rkWny6YkoGtleK8cWeYBnqgYx2Ldhm6CpelrqRmRsYUYmya0WmBVFQwWxBUqjXqrc5bIJWMI1ko%2BpRZczmxS2bjPv1fpMF4RDEauWKfHVWxTsNMWjeNqCTcO023LNmBbjJY0TYKABqjR4EwET0CeZ7PrtK0HUdJ30I%2B04ybub6CpJhF/m6HrAcZ4F5Zym3cYdxDHadmBIR5Z6bVYnJAyD90iShtxvQj4Z5mVMYVVRVWpj5YG%2BsxlztmxMntgD3aw3dYMiWeFOg9hEPiTGyPSYTsbCvJimFnmKlOYtBPE6zO5892z2YGeV2rWuG06Wl9Vg49gsdo2A3xbybDi8tkvrVDCvtqLUrzU9blSttisSzdwOU%2Bd55m5rFtw1tT5GwlL38sjH1XF52W%2Bb9fpk5yCJTrctNnSj2CQzL6XQ24CI2MHt102HeFflJHlo8%2BmPUSmdG47l7IyQL7ak5HcvcYHZ4zCaaIAPqiDM3aB8KEAh1Tyz9hXDSOMgtcQQ3sHYM3Cfw23DMkxJKeESzRPhhzPKNYFXO9U1vV/HsG1ELalKGfJP342ZZwgpaVmkvUqCbwZKZRsFI1xT2LvuaJmVfbnflMgqVgL6pIWatqEXdbzysFzG1qhvEqAFn67yYvlZK9pT6mFRqVDOCYsY8mqklW0sDQGL2BJ/dSJZWoVkIp1P%2B7AAHzn5q2J6wszTUN1HbR%2BU1Rxa1HOvM%2BhtFY3xFrQ82DC1pMI8owmaG9TZ624fQwcfCRIA1PDbURgDb48IkWufsUMnYcLch%2BCev4GQIPAd5SBf03BwO4tI4ikNhHdlUWYpGWjiLpxkpnbGOd9YGPzorQuRcYzGMsSXOa1Npa6SjknRmNiCIIwLjPBSc9sFNRiWpFeYIADqjRMAIC3kZHKr8cTfEPpZYkpJkmGTSRfd%2BZCXJ3zVg/MBXtvqZN9pfD%2BPMV6hV/rqf%2BvVOGq0tOgwMhSMqfX0XU/G0CMHoD6WAxyDjkFZzQQVcZMTcHNIIe1Ih1YSE9WvsLHRQ0qHyK4Xsrp15eHKIEZI24fT2FyPIfs65hzXZKOmswz4fSRGzloaLJ5/ZOIwRkQtA5FSlzHMeYKb5xAHrDQ0a9LRHs9HezxlAzkFzuygvBo/M8LzkUblDPTNFoTU6P3sYrRxqCcYuKGVAiJOzFbtiRZyFF/jQU4pQiE5mQoIlySic8eeTTgrL2CqvW4ABJBQABZTw6AqBeFoPvIE%2BDHhMklPkwM1J4gaDFbQdAJhVWGn%2BaLapWVgLCvVRKqVaNbiVy7kOAQ2JVDJGILcCIqBPC3GhGINK78qBiCULEiwCoeU6tuVyd5kKgUsNBWeD5N5Dz3l/LompQrRXislbQTF2ZQwYWjYIMOEy6Tms7miK1DAbV2odU66VrrvANMAs2T%2BfrmoaQOAmzEwBMDJplcWDU8qajASVfaFVGhm3Nm1dFXVbl9XP2FYO5NZqLUFrQEWpktr7WOudRW91pFPW0G9bWn1ZSVZBv%2BYolcZzNoaz2vyFusan7eUnUwFt07/q%2BNvpeuxujSJ5qrsgQtxbl1lpdW6qt4oa0qTrXEhta9hWllQEwE10qcktS7YqmB6B%2B1QZg1qjQAbyl6rjQahNaHYMzvzV%2B%2BdP7S2roAx6r1wGVSga/pw7ZfzA2dIBUch5/DQ3PJSbrN5o776fJBVin8ML42Qeg4RxFKTU0TlDNmt9ubZ0ketYuktK7y2UdItWn1dG8Fgkg06Wgbb4Pf0Qz25DqGDMYaw/unD17JT6boNO0qH7LWkZU7%2BijlaqNbpo4WHTHStncSY9hsR572Nh0Eaw5APGhaHvEcek5/JNraP7gM%2BzChSwGYfUYrBRin1yZIgp4j373PkfU15zTQHtO7oSXcbAWIkSuOyXiazQD%2BOCgDHej447vL1YUI18leUrggFuMkLwp0C2pXstvREg2/SdZbdmxBizNl8cqf2Bb3XdGGV0ngQynwIDITMPEcw8QjVJtNZyTbV75JrswMsNLwE%2BsDZ9sMq7yUutLcuCNsbE2v0QkMOknec3b7Xbsct/1I7mMhuu2AnbXg9sfFuIdoUx3TtiZg9l2HkS7sPc9nh57TWRk2k%2B%2BD77o3xu0ALX04pcJgevYRf6D7i2ycBUh31YN7X%2BTY//PDxHB2jsneOw5wzl2me2k%2B%2BzEAuPHu3EJyD4npO07DYp39qLNogezYZ4YsHyucGNPravAExuD6/D042O8wZujtrNybu3QJWu30jfyS4xBgBXpBJnZ7e8cby%2B136V37viKzy5WBo3duTiyrBAAMT2zMOXqhWCsma%2BZYsEfjcO4ZGYWIwRhxeCwLRLkXhk8TNt42oQxf8j2nLAoKVwFjOZwr8kKv6Aa91%2BrhoNBMx0Ac2L/QbswQCBnioLQaDQ/bgj7H3sM86B1ig1dGHsEbfaD15a1cTOy%2BCAd7Qd7ilQWZLd97yXzkg/EbPkPwpPvt9J8mmH6Pk0exmUH4ID3y/x%2B3Cz8p/0nRIpF93ARB8Kvqnvjp%2BtXNNNEAQBABfgoHyGAbGm4Jvh3pDJXmkNXh8O3phuGA9n/unv8FHppDUAIChtgInhbjbuBrgYCLpppCgUoK3ugSvuQY3rQWgbXivtXFwF3i/vJIPpgC2sQNXEoIEnLAPoIGeBoGeO0LcEkLcLEAvl/AKpvkwdMogZwb7g1sMoxs/q/rwfwYIU%2BqIePpgeHLIrGBfsEFgKoPocIQ1JyFIWYE/orOYQwJYdYbLLYW4HIW%2BqjDgWvAAfHsZopnAUoE0FAdwSADAWwHAd2Kocgc3qgfQWwVvlwMKNgQoZQacPgY2giGksQMQaQcnuQeHhkZnuBucikggOsEoJ8MZixnUSGuFmTvGn0h3vWnUZzutqcolj1pKC0SkWBu0WtoCo0Xrs0SktXA4QMR0cMbhs/FmK0b4Q8D4CwEiLcIHj4DGuQfUVzj0cBPMf0fRtMWxrMd5PMZMYcUMccXZnsQINXF4ekTQfEXQUoQ3tMk3i3ogWYGgi0ZgW4PMRIWSAwBwahLcTIfMV4b/g8Y2i8WvpcBvgwVvl8eof1pofvorD8amgsSYc%2BH0ZiVIWcY4TSuMZMX8bcRCR9Isf4UAabgBKAeAaEdAbAViDEQiRMXER8ayZMdgGkdQRkVQWXmvNHusE0AgAnknvQEUXyZHryWvHAjaMQE6iwDUbCYMYGketgIIk0XhnAgsRccxqFtdJxlqc/DqQcXuguAaQJgSvjiaRvBMYbmCOsQhMqcARznFmFicZKLZLqeaQovFtcQEhwW0ZaaMdqTpPaVMe6YabsYGfcTKRtCwYkXXsoZRAmU8awe3rEGgjqb8d6QCd6VId6TId6eSYsTCa6fCUkXcTvhoXvh4l4nabmeGcYRdDJKaT4tpMCYGVyTFlFhGXlp2eST/g6f/oAeQUEfSZAYyVEcyZyIgbEOyQkfOakUFBwKsLQJwAAKy8B%2BAcBaCkCoCcBDSWDWDmrCmkjmCxA8CkAECaBrmrA2ggCbmSD8gaAAAcZgZgAAnF%2BVwJue%2BW%2BVwDSDSNIBuRwJILwCwBIBoBIbufuYeRwLwAoCABIbeXuWuaQHALADAIgCAOsAQGNkPhQBAGgCyHQNEKEHyJwKoG%2BfEAALTxCSC3DADIBfpSD8hmC8D2iEAkB4A97tD8CCAiBiDsBSAyCCCKAqDqDoWkC6DtAADuxATAyQnAPA65W5O5d5B5nA7440hFtwqAVAtwNF9FjFzFrFtw7FXxEAHgZF9A9ql5XAywvAaFWgqwEASApFqI9l5AlAXl5FMQwAUgSQNAK%2BP4lAEQWlEQwQjQSIqlvA0VzAxASI74EQ2g3a8VpApFCE74DAtAcVMlWAEQXgwAuotAW6mVWALAhgwA4ghViOtQ1YyFMlmAqgFYTImVvBYF%2B5VOEQSlyVHgWAWl7oeAUF3AvA1YxAjqSgjw1VRgVORgd5qwI%2Bd6Cg%2B07w8l74FomVglwg6Iol0gu1klagWlcl%2BgNVKA1g1g%2BgeAEQyFkAqwqAyQ3QzVdF3eqYpgJ5lgZg8Fk1wMWA91EAqw1QtQzgEArgkwbQpAgQ8wpQ5QeQaQGQAgkNCNBQmQAwcNww0wnQ3adQswKN2NXQeNfQGNQwMQ0w%2BNngrQeglcTQpNiw5NwN55ol6lHA25pAcFvACFxltFDFTFLFbFL51luAPFDl2eTlLlS1qw34MGwwQNpAj5kgsQ/IX5sQIFGgkgZgkgqqGgm58QX5%2BgnAEFpAUFV5/I8QXA8Qb5X5gF8Qz5f5qt8QHNWlCFSFKFN5S1mFOFHleFel40vlJFqAdlFFVFHAjQLA0INIdFTAU0iYXAX5/IXAr5XF%2BARA/1egu1wl4gYlR1SgJ1MlugSQilyl8VrN7NnN2lHAulBF40BlRlJlfNsdVE8didr5yOtl3l0Q1I2eZgzlHt6F7lnlQdndZAxF/l9lKABgRg8dXAEhoVTIhEEVUVMVyVmViVsVqV6VDgmV2V94uV%2BVWlRVJVZVFV41pAVVNVdV%2B5%2BAhkjVHwWlrV7V2w15XVWlvV/VSIg12w%2B5I1Y115k101mAs1l9lEntK17u61mAm121Z9md%2B1Egh1sgx10l%2B5hd51i1n1VglgN1d18Aj1z1mQr171dEmD1gP1XNf1fF99D1HQRNYNENVNUw0NLh9N8N7Q%2BQSNWQjDUNHD3QrDWNtDuNAgvQEw3DNNONoNPQsw/D5NYwfQBNcjdNsNZNEgTNGwWwqjhtbNmlMl3NDdZla0cdCdSdneEAItad3dV5fdrl95pAMtWAMQ8tYFxtptCdGtNIm5X5wFsQmt2tkg7QFdrttg7tNj7l3tSA%2BFhFAd49IdbAnA4dZlSp0IX60ILdTYMwKdotfFGdsgWdB14l8gedKDOgcQpAxdKl41ZdOj8FOlftwEhlxliTCgyTLqaTsU8eNlw9AVljsQ1jntPtMTo9flXTE9yTze1cqTX51c6TW%2BqgjFfAdAC9yFEAkVMl69q9Z96zKVaVGVZ9u9gg%2B9BV19mAxVpVYgp915F98139vAN9uNTVD9bV7UHVZ9r9Ml79sVX9w1wMf9E10QgDwD81oDA9fABgEDG1W1jAO1uT8DOdSDRTp1pTU9xgV12DvVgN%2BDL1nAOwh%2BpD31v10Q/11D8tIN3QLgLhCjMNJQKj7DiN3QCjvD6NyjDN4jdDUj8jYjhNQj7LSj1LLLFNHLOQUNtNcwfLbDajmwLNWj5dLtnAjTTFSTKTbTTIHT5jJAljEt/dbl0tmAstjjrNLjIA35/IsQsQm5/5/jMFprNIVtztujnAbtqFUtCtIAkgm5KtQFNIMFb5kgv5XAH5x2WjsQ1TXNDrWrtjYFnFdrNTiF4bywqwk16QzgkgQAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/omennivore/easy_paste.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/easy_paste.type.test.hpp)
