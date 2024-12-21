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
using SupposedResult_0 = std::tuple<int, float, float*, double>;

using Result_0 = EasyPaste
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>;

static_assert(std::same_as<Result_0, SupposedResult_0>);
```

- We will paste `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>` together:

```C++
using SupposedResult_1 = std::integer_sequence<int, 0, 1, 2, 3>;

using Result_1 = EasyPaste
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We paste `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>` together:

```C++
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

using SupposedResult_2 = Warehouse_0<Con_0, Con_1, Con_2, Con_3>;

using Result_2 = EasyPaste
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We paste `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>` together:

```C++
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

using SupposedResult_3 = Stockroom_0<Seq_0, Seq_1, Seq_2, Seq_3>;

using Result_3 = EasyPaste
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>;

static_assert(std::same_as<Result_3, SupposedResult_3>);
```

## Implementation

`Omennivore::EasyPaste` is implemented as a shortcut to the member `type` of [`Omennivore::EasyTypicalPaste`](./easy_typical_paste.doc.md).

```C++
template<typename...Args>
using EasyPaste = EasyTypicalPaste<Args...>::type;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzPGkAA6oCoRODB7evnrJqY4CQSHhLFEx8bG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdFxCQr1jc3ZbcPdvcWlg7EAlLaoXsTI7BzmscHI3lgA1CaxbsjD6FhUh9gmGgCCm9u7mAdHXo60hACel9d3ZlsMOy8%2B0ObmIhmAmAU31uPwA9AAqRHwvYeeoMPAANxI7BAABUPok8KJaMomMMnkj4bCfsw2ApEkw1ijUGjMdiDgB2Kww24ETAsRIGPkgggExisTAAOml0Juw2IXgce3xhOJpPJnKsHIAIoduXdbrDYXsLGSnm4zSAfj8%2BQKhZgRWLaU9ScgANaYdyyJjBaKy%2BWKgjKglEsTq4VHV0er2CH0hYiykxcn57VN7LypIx7UWJJ6HbV7KOejyx30J2L6pO6ivWw3GgBKmGQK1SGPNltrN1tgqYwphRxTae79sdued0sllz2OzJCmZpfjN1Ig9Tw97DqOOfFbAnU5nCjnJfqZZsK%2BzTolE%2Bw9DYgjlpAOtzT57Hl%2Bl1/5jAIFgUy6fQ4vHdpQAeQIBBoihfsrluAMlRVUMSTJCM3CPONojuI4P1vAg5V3WJsAfVCTxBLCvx/PCCL2UDwOIBQKOtZN/1TDNgmAF881iAt4LVJCHSY543DPZ8iMXEiby/XDpQfUjBHImV8L/G5n2faiIN3fjLhAEAtz1Bjq0rGEdU7BEkT2IRMAARy8dEsWIHFuLDXi9kpalbmdelGSecyrJs9kkwMrt%2BR7ZCt3HeToLlAgFTgkMeI1fyq10nkbiNE0zRRDtkrXELAJdRlo28rxGDWf0osDYNVUc8kQSLdBCuKjcIoS/iWKzLdngLWr6oBDdKyMmtktSxtm1ozF2yUK0sqCkd%2B0E/jso3C1XlQCjpwMA8zMsoqeqXM8FpBJhltW/c526tZT34w6iAnAA1Bo8CYCJ6HvR8lLTK6VulO7iAep7MB/RTn1Ct9JVU2jrXwn5YKDBzEOqo4zswDC3G%2B37nro8KH0RqwjlRx76DkycFKosC1PChj9WfVq2Pa/MKoQ8M%2BLe1MQSEtNEeRvG/skyUHy5gmMaJgi2dTMHBbPTTtLFJK7n6gL9tmvbpvXUdt0wB8PuO9bTq2hrdvm5WctfNgNaO8K1tnTarIai7mfY51lX1u3gbYZVbefTWvvu/Gkd/V6PbNyV%2Bf%2B389tyicxYhiLofpuLkI5kFcSXPZg55y4sd1nqcbcXEbBT72/sJ9OSZo8XIcMym02p9iOtjqq%2Bzt1n%2BOfBOjiTh9JkcZAAH1RGGROMOwCBU4UeYJw7%2Bou97pCB8uYeC4FsfMZFkuycnDT8K0nSBtl/TO0SwbKTMoh3TZOytNhxnnKRVybnchkmTqVBT9svNGINQK7RVzdw/JmCypipVOGfJNSJR3nCY0polAZQmp2faP9jZ5XdJ6J%2B7piCoFQCwUq0UYaxXrotLqJ83ToMwYmd%2BVNMw0zFLXQhz9iEYKweAuWxkGxNhbGNGB7A4GGyZk3Z2PCRQCKOJ7IWFsDxa0tqg%2BhmCnZAyEW4eBS1rrmxOhIjaUiSEsHdkOeRIi9zawnBzP2Ssv7IT0fhMRgtsah3mr/UGpNwZQShgA3BQDGYgg0Qw5GRiKJYyIZo7O1jfGr1ovRCuZ5q6004vbCUddgFM2fHw5S7N/FeI8ZnNYPMM7WyzmXYWzc0xi3Uo3TeUtcwyzAQFA%2BH8TKIj2AAdQaJgBAZ97J4PidfREt976eQaU0lpr9QFTVMYtF2Uo/6RRwXEq%2BCVmGDUgelC0sDhnBVGblQs%2BVPSNLsggZYShsHlUvrxGqmz0DbOaXsxqFMImUJrnTWq5zdkZl6npCpdY9jDXYW2Thk0P4K2RiY1ZgiRmqzCqI1RKjtZ9J2Zc2ROiQWbnkWMtReTLHQouc87Rq4kV2P0bOCcIl0LGINgihRuKLEQslIS4gAMw6IIjg4yCg9nFTKOfDNwjzYUgmpWnYmnLMXcu9CePJD4ikTOanbSJ1C6ZjOmccjec07bPn5UoZGPLBaESFfGIuCkV5ivXiU7AW9pZML3slapcIj4AEkFAAFlPDoCoF4WgnSqQQL2NqTAfIlQP2jAcAAbBoe1tB0AmEDTaHFiCDlKhtcGx1zqKZ7E7kSacAhySqESMQPYEQMEuoxGIIqmoqBiH2XLTkZq/lIsjWrFF85jzxgfMi984lBBQnLpM8qsaHVOtoIKhcfpMItoIHkshFgk2TxTWgBg6bM3ZtzXsfN3g34WDKg6MtlTjLWoUKSCEPbXW31Sp671QZfWegDRoHdDpw28mrc6aNQYbWXp7Ym5NyBU3Tr5BmrNObPALoLcu4ttBS36XLW8z%2BQLEWkvMdgNFiNTbKKDgvSE969iPqYLuhNCMMmLWDiO9t/lx29knWmz9s6f15v/ZqVdlTQPgMNFu%2BsqAmDxpdS5d1R6mwntOeexjzGw0aAjaSsZKGbW8ZYy%2Bidb6p0zu/fOxdhb/KAeA3qWj8sBGKxJRBhRt6QZ4vEZCy2Kr1aApHAgmtBn9NUq1RBKOLLO0KDE8%2Bo4Rm%2B31rXt8fDXJCNd3fTJudv75PLuo%2BuuZNSGM%2BloHutj7yOM%2Bu4/x%2BsEX%2BOCa08J9tMdRMRefRXbzxGP2YC/f5ijS6i0lrXSBjdKyZoAs06Z7TUHA56dRSdY%2BdDNGA3hVp6DljDHYaZSJhzWXMNuE8aQrDOS1h4aal519vnSOyYC5R/ywWKuhctaZbAZIPhspAdF8DdWm2SijOh5D6WXF7E2wobb7T3G3BAHsRIXgnopsKr5c%2BeIbvHMjPlE7I7wlrZvUJuxx2IRtoinZKyeA7JzggLuMw/rzD%2Bq7SGpzbgQenaNSAQL8w7NKku9dtxX20c/dB2Em493HvPbfaiQwrSL6ffZejv7sstQVpSwd4HJOMc/Ah14KHkI9iw5lPDxHommPie%2B%2B6X7ktse46DPjnbBCufM4p0994b7Hl04%2B4TxnyuyezLZ4D1LnOpeg9lLz/nMO4cI/h5lugqOmcy//Tj/%2BUyFcM%2BQkzsnquqetZftienOvPd6/FcmAHKUj746vntxRh2bjEGAGDn41co9OTpu7oPi14%2BJ4osa8pdGI%2BUiL0Xg9R9cSQmHfu9bxea%2B32r8iAAYlD4YF3VCsEFBSG%2ByfblCC8IkXInpGwKGdQQbuGha6nC3n3%2BgIJggEAfFQWgTH597EX8v%2BED50DLD%2Bh5gK1ch8j7H7XVP1UNN20n9pafi05/FzPBfggV%2BQRr97AvpfvZ4TpzvwQdAU%2BO8gi32rlck4gXq%2Bt3LONEAQBABfgoBKGAW2m4AfrQKPhoFjH3gPugIgcgZcDjgXrUsiOZFOugK3u3vQFXrcNXL3v3ikIPpCIflwBPt/lpHPpgBCMQN3EoBNtfoIA%2BCgXsG0HsGYA%2BLELvp2PvrQUgd3PQenltrdjVufowSAMwawewdhrPtwXsAJsTF/j/ooQwFgKoCoZwSCPwWYJ/vxBfsEPoYYdtCVEcMIfhpDCAZJnAUoI0FAQoTAWwHASCJgZIagVQUoBgeIaPlwNgWBngcqC0sQEQdgG3naJ3l0uzt/PVsbvShZszjHEZmPmBrHjpkBOCgYhMpkf0pcpITkVWkDmkQUfikUedlkaYQXrHuStHOdiWNkY0XkeMkLHLvOGUR0ZUeZt0a7uVG0Q0WpgMWCihm0fYXvj3mgdQUEcPhIWYLXFkZoShAIGPpqgwH4b0YIb0fYVcAXmIUsaPisdIVdrIUkmmGsX2u0ZRGeFkaEUcG0fwaMWYXbPUXcYcbZk4URj3OAW4dAbAWSD4cEd3PsZQegb4Q0dgDgQFBEQ3ssI0AgMQfEWQftskYot1pSihqNiwO0eMalroo1hSoUUMR2kqPiX0USQdiSQhk1mTjHNSWMdwg1gyWdlMt5ISWyV1qSS0VyZZDSbyXVtBj0dyayVVskWKcMVSUKTMaIXMQETQacd3LELXNSesdybwdyfwRKdkmqSIclCcYfuqRcR8FcQOPxJqekhZPcQ%2BGeNSc8SNkKXqUKbCR1qmCybaYaQ4UcQFKAYCZAcCV4aCUcL4RUGZPMYERGWETvBwIsLQJwAAKy8B%2BAcBaCkCoCcCCSWDWBJrIlMibA8CkAECaAJmLBuggDJlmCSgchmCSAAAcjZyZGgAAnDWRoP6o2RUEmRwJILwCwBIBoCgemZmdmRwLwAoCACgWWRmQmaQHALADAIgCAMsAQI9vPhQBAGgAKHQNEKEBKJwKoI2f6gALT%2BqSB7DADIBvpSCShmC8CeiEAkB4A/5tD8CCAiBiDsBSAyCCCKAqDqDzmkC6BtAADuYIiQnAPAiZKZaZ5ZWZnAwErwm5ewqAVAewJ555l515t5fBkgD5guHge59AWaxZ8wvAc5WgiwEASAu5hIZF5AlADF%2B5MQwAUgghNASBEElAEQiFEQwQDQHwMFvAglzAxAHwwEEQ2gnGolpAu52EwEDAtAIlIFWAEQXgwAFotAQG8lWALA4I4g6l/ODgY005IFBWbCfI8lzBfZmZ7wEQYIklHgWAiFUUeAQ53AvAbYxAOaSgnqhlRg7wRg5Ziwi%2B6GCgN0eAmA4FwEY48ln5wgxIv50gSVgFagiFYF%2Bg4IKA1g1g%2BgeAEQ05kAiwqAiQNQFlZ5pw%2BYpgeZlgZg45vlP0WAJVEAiwdgnG6QLgehYwrQpAgQvoMwAwbQuQaQAgfVOQKQ41DA0w/QMQEwVQXVAgXQowngLQegnVZlK1IwPQQ181m1u1k1Ewu1c1JQI1HVhZv5cFHAqZpAY5vAE5WFp5F5V5N5d5hFKxEAuAL55FfwXAlFpZYViw4EzGAw7VpAVZkgsQkobZsQHIkgGgkgDZgaGgyZ/qbZ%2BgnAA5pAQ5sQXAko/qXA3ZbZjZxNyZkgXAyZcN/q91iFE5U5M5QN85tFK5dFa5qFrwzFO5mCjFB5R5HADQLAGIHIZ5TAFsWYXAbZkoBNmZz5RALVegSV354gf56VSgmVIFugghkFTA0F3lN1d1D1SFHAKFG5rw6FmFQtItYtEtbEUtMtko4%2BEAJFfNf1sQZggN1FC57NrFTF25ftAw1totM4RgUtXAKB3FfItEfFAlQlkl8l4lwl0lslDg8lilX4ylqliFGlWlOlel3lpABlRl6wmZ%2BAdkZlbYFlctqg1l6wJZdliFjlzlHwrlpdVFP0XlJZvl/lmAgVRlrEYVfABgie0VsV8VjAiVsgKtqV/58gGtwFmZ2tOVoVdVVglghVxV8AZVFV6QVVNVnEa91gjVj1zVb5kI297Qy1fgEArgx1A1ehZ1swo101NQ99Y1NQT9I1V921tQR1614wP9NQq1e1RQB1J13Q99kwjQX9C1l1KwawEghtCFIFT1wdttod9t0tstguP1CtBw/1XtwNpAoNWAMQENfZONeN0tSNHI1NHIHIsQyNkgl5bQxtDNtgTN3trN8A7N65m53NgdxAh5bAnAQtuFLACgGIb6GIDt9owwT5%2BACtb5St09KVEgaVsgGVi9OgcQpAut%2BtsFWNt1KD45yFnNQYGFew4jV5kj0jC6cj64LeLtvNbFBD8QRDLNi59Frj/tLFvjAw0j/e3csjbZ3c8jo%2BNjfAdA0d05EA/FIFSdCdhdSTUlMlclhdGdggWdalZdmAml2lYgBdJZxdwV7dRdpljgVdiFVlzYNlhdjdIFzdwlbd7lnd8lPd1B/dwVg9XjEVo9MVcVCVhdyt6jatWjC9WVejBgq9%2BVG9jlbVO9lVnAsIk%2BR9DVTV0QLVF9pVQD3Vt9vVAD/Vg1YD51C1SQr96Q79lzBQ%2B1Zzm1S1v9IDUDjzwDp1dzz9tg/9WQ/V0DoDfQ9zANSwCD11xjRt9NnA1jxALAEjUjMjjjfIzjeDJA7jANVFxDpD4NN1VDIAZg0t8QyZrZlNI58QHI3ZdNqDnAjNs5xDUNHID5dDXAUgbZtDcNXAHIxjsQpjj1VLzNNFN1j5FLZjk5fLFZpAvlqQzgkgQAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/omennivore/easy_paste.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/easy_paste.type.test.hpp)
