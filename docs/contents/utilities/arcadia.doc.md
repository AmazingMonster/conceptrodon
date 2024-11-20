<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Arcadia`

## Description

`Arcadia` is a vessel for `Glow`.

It also contains a regular function, `size`, which returns the number of items it holds.

## Type Signature

```Haskell
Arcadia ::   template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...>
struct Arcadia
{
    static constexpr auto size() -> size_t;
};
```

## Examples

We glow create a `Arcadia` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we query its size.

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_3;

using PackedArcadia = Arcadia
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

static_assert(PackedArcadia::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...Items>
struct Arcadia
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAQBspAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfP3eTE%2Bp0BfwBryBIO%2BkPBoNhwP%2B8N%2BiIBAE9UoxWJgAHR4m6HfZMBQKPE4glEklkikGKn4gLYQm00n0xmUlnkhlM4kcmk8skASR%2BChuT3GxC8DkO9w2THwTCeJgA7FYHod1YdZo5kISBONMKpUsRNXgAF6YAD6BBN5ogSyeGuOKsOxEwBHWDBtmFQVDJECFrwU9oCFidABFFUqIyHFQ8APQAKiTyZTqbjT0TycOABVsEJs0JDin0/HU2Xi7HHmZdgx9l4jl80LXMKkCCKGZWwajkVCkTCUdCu4OEcOB32h%2BOMVi2NSuezZ2zmQvuXTOYv%2BayV7y50vWWKCBKpQGWBaNCdVY8HhOIWOb7273D%2B/ee4/r6Cp8wZ5v59/d2ut8uP7/kBfKrqKDzipK1rHhaXDnp2I7johD7dk%2Br7IS%2BqFvt8H7YoBf6gdu65gTuG7AQRpEkbcEEHlBhwwWY8EPE82GsRhaFYexbG3u%2BmKfriv5kYR%2BFCZRREAYJVH7oe0E/BaARMZe9xeJkRiHMoTDIAA1pg6AyqI8rHAEYbSrK8qKqcDoajBGikMcarWXJXB2VZ6oMS5DluXJCnMR2MbMTRwJ4MgFo8vEBAQBp2m6fpcp4EwIAgJktpLEZ0YmZIwYXhwKy0JwACsvB%2BBwWikKgnBuNY1iamsGyYMc1Y8KQBCaDlKxaSA%2BUaDiZhmAAnAAHBofX5QNSQBJIZhKpIKR5Rwki8CwEgaLZxWleVHC8AoIC2S1JU5aQcCwDAiAgGsBCpF4BDkJQaBvHQ8SRNinCqGNAC0SSSIcwDIDqUg9bwumECQeDoHo/CCCIYjsFIMiCIoKjqPtpC6M5ADuxBMKknA8LlBVFa1ZWcAA8ldl3Wj6hyvUkH1fT9f2SD1hwQB4930MaOxcEsvB7VoKwQEgd2pA9ZAUBAQsiyAwBSGYfB0C8xDbRAMSEzE4QtGiOO8GrzDEGixMxNomAOFrpB3WwgjEwwtCa8jWAxF4wBuGItDbdwvBYCwhjAOIdt4K6Dh4AAbpgbulQaxtXVsTXhC8c2lbQeAxJjeseFghMHngS3u6QIfEDEGSYGGrze4nRitSsVAGMACgAGp4JgaPE3xpsQ8IojiLDbcI2ohOo/o3soFVlj6En22QCsqCttkbtvRcJxhqYljWGY6158QoOh/AKx2MbDQuAw7ieB0eihOEQyVCMzlFFkAhTH418ZLfDDzMMCTObvgcCH0kzH/kH91D3r0CYAxz4LCvrYEB989CzFaK/S%2B78d61U2BIPGHBCqkDWrwDaVN3qfW%2Br9Q4/0zDM1wMDDmjVubNQrisBAmA5QjDtKQDqgQcR9QCNNDQk0ZorXykkPq%2BhOALVIEtAIXAcRJC4EkAag0pH5UkFwfK7CUhYKJptWwO1qH7X5idAWZ0yZXRuuLVAbNHrPQ4C0FgQclRvSYNyNSXA%2Bo4nEeHfARAN5g2cm3KGndpDdyUL3ZGuhZYYyxlrNBGDVEbVJhdK6hxKaWOsbY%2BxwAiFOJcczVmwt2YNQCGYKhvMDp6IluzIxJSRiJJsUSIwjiuC2RoLQBWSsVbIx1hrU2bS9YGyNibHO5tGAECtjbQm9tHbO1oK7U2ntS5bFKvgAOjgQ5h0BqoSOLxTaxzqITROycNZp1mTzDe2cmp5wLkoYuXsjBl1ANovg1c64Nybi3HO3iO4wz8bIHuSNSrBIHuXJeVgR47PHkwqeDRZ7z2MgClea94geK3hPboQDnAQFcNA5yZ9yhvz0DfBo6K0hPwaPAxYACejfygX/B%2BSKv6NBAcSiBsC2iUpgXSsB2KuarHWCgjlc1ImExwZU5J1TUmOOcTiDQpC3EkFyVzHmNDSB0IYQkJhc1hGiKcVwpUSilRKgmmYGaCjMH8s4FtTRhSdHwD0edcmZSTHZLMWwTglj8EsAUEHHUQdRV/HGIDKVHjwayB8e8uG8gAnfJ0IkUgoTsbuwiQTZG0SDEUyoIcZ1X1XXusOJ6px3rrQsztSLXJAQCkV0OoLAtpSxblISO61IqQLTZotLm0KxAWCfTlo0%2BIzTVbqz1h03t%2BtDZ71Nv0y21tbZzMwA7J2Ls3ZNWmVcg5pB5lAKWYTCOyAo4bMEFs5GOyU5on2RnI5ptTmFwuaXcINy%2BZ3KYDXeujdm6MFboGt5EgPnwzDX3SNBh/nDxsMC7eZVp56k4HGC4Q9l6WFXtg9em8QU70ATSg%2BR88hUsxRfElBLijZHxbi7I9L37UoaD/JlaGYFIZI6yrFCCWX9HxYywjqDOV1WY7y%2BN61OCptbS6t1HqvWInGJK8hMqS3aNofQrAyq0FqpAP1HEAQAj5S6golaimlTSKNQmk1GjdrypYU4nVGhHFcK4MkfKSozDyMERwAIHHsE6fNWgsw9m1FyvE7nLt2R/BAA)

## Links

- [source code](../../../conceptrodon/arcadia.hpp)
