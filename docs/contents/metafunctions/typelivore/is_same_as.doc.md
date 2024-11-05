<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsSameAs`

## Description

`Typelivore::IsSameAs` accepts an element and returns a function.
When invoked with an argument, the function will check whether the argument is the same as the previously provided element and return the result through member `value`.
<pre><code>Right -> Left -> Left == Right ? true : false</code></pre>

## Type Signature

```Haskell
IsSameAs ::   typename...
           -> typename...
           -> auto
```

## Structure

```C++
template<typename...>
struct IsSameAs
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Example

```C++
template<typename...Args>
using Metafunction = IsSameAs<int>
::Mold<Args...>;

static_assert(!Metafunction<int*>::value);
static_assert(Metafunction<int>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<typename RightSide>
struct IsSameAs
{
    template<typename LeftSide>
    struct ProtoMold
    { static constexpr bool value {false}; };

    template<typename LeftSide>
    requires std::same_as<LeftSide, RightSide>
    struct ProtoMold<LeftSide>
    { static constexpr bool value {true}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr auto Mold_v 
    {ProtoMold<Args...>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISVykrgAyeAyYAHI%2BAEaYxCAAzNIADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn4B1bWZDU0EJZExcYnSCo3Nrbkdo739ZRXDAJS2qF7EyOwc5glhyN5YANQmCW5oDOvJBApH2CYaAIK3dwSYLMkGz0duBACeyYysmH2ACU8MAEMI8Fhro9RsQvA59gBJBRCAF3K73EwAdis932%2BP2z1e70wnx%2Bf2YbH2wUwVAhUISNzxBNh8II%2B2UxFQRAAsp50I8CYccftpo5kPtTqNMKpksR9tFUJ59gA3MReQHYixUMRKbEAESOFmFhoSuIezPxRLeTA%2Bx3J/ypNLpQkhpMZgoJxEwAEcvHhvQpRQR0CAQAoAQB9JhXY7O%2BmYUjA0Hg10Mpl3IWshGc7moPm0AVx2kJ6GW4XGsV4CVS56y%2BWK5Vq7yanEEOGkrGm40Go2PT1Wl42u1fX6OzAAOind2A3pejEuZczBK86SM%2BwL6EOCX1HK5vP5nxnc7YggUU4n0LN/fL1pJZLHlMn0%2BIwFjGazjXFkoE0vr%2ByYLwiA3flIxVQ5yy1XMD0LI9X3PKdrjDZsNV7a9MS7PtMXuAB6AAqAjCKInDHnwgiABVsCEcjCJI3CiIYvC6ItB4zG2M49k1Y5TnORcPWwp4h3ve1HwBC87ngpdVzCYAN0wRoqC8M46m3XdkVRNh0U%2BMICCXMNNzgt8Lyvc0YS/atowUJRmggMAwB5eSmEU5TMm0wQ8KQkAUMwBYsPRczkEs6yCAgByFKUhxXOOHTPO83yzQ4JZaE4ABWXg/G4XhUE4NxrGsUUVjWTU2J4UgCE0RKlgAaxAFLJAnDQAixBINBSjQzAANg6swAA4ev0ThJF4FgJA0DRSAyrRSGyjheAUEBxvKjgtCWOBYBgRAQBWAhkiA8hKDQV46DiCIAU4VQeo6gBaDrJH2YBkAlKQJzMXhMHwIhiEhPR%2BEEEQxHYKQZEERQVHUZadD0AB3YgmGSTgeCS1L0oq6bOAAeSA3b2VQKh9gu67bvux79mesx9ggDwjvoeUti4BZeCWlbSAgJBDuSY6yAoCB2c5kBgCkMw%2BDoZ5iHmiBolR6Iwiab4Ed4aXmGIb50eibRMAceXSEO08CHRhhaDliHSCwaIvGANwxFoebMpNl5DGAcRjfwb1IpVTAbammUNaAjZSp0mpUdoPBolh5WPCwVH2zwEbbfd4hFSUfV7aMYOjAqpYqAMN8ADU8EwKH0YpLXfuEURxCB0vQbUVHdECAx09MSxrH0EP5sgJZUAuTIbau0Yi31JurEsMwptQeOvqwduICWOwNbqFwGHcTw2j0EIwgGcohnyNIMgECY/B3wpMlmQZ4kCOfIoEHpxhX3IL5qefujGPoN7mbfbBfg%2B9GmZpT638%2Bs9CrrAkEjDgaUJqoxmvjS6N07oPSevVcmEBcCEBIIcEqDMyoZyWAgTATAsDxBnqQGqkgEgTgAJwJCxJIRqZhJAdTGilDqFCBocCGqQEaCQuATg6lwDqPUKE9X4XVLgKUqEdUgcbGac0FrYIhqtDarMtpYz2tzXmNNTpsE4E0FgKosRXSYJKBuskuAUInDwr2H0SDfUCKXf6FdpBVyUDXY2ughYwzhvLMBEDJpZQxqonGeNdH6MMcYh2pNzGWIplTDmNMMEJDMFgpmiUWZs1QNTOI%2B0eYZLiUMEJBjdgOzMVwcaNBaCi3FpLY2itZZa1qcrVW6tNa2x1gufWhtUam3NpbWg1stZYBYA7J2U0XZP3dp7N6qgfbPC1gHZKxtg6h1lhHDYU1o6x1KvHROmBk5DNTjJDOfBs4KDzgXIujAS6yAcYDJxshq7gymu4/QDsUB5UsK3aI09O7d1/JwPuIYjiD3eRYUeWUJ5um%2BZ0J%2BzgICuG/oEdepQz56AKHvLId9D6kDRXUf%2B8wH5dGvl/TFP9H5X3qC/PFH9f4tBJRfSlb8UX02WKsEBzKFm%2BKgZwACxA9EGKMUU9cZiLENQpqgz6CT6aMxwaQPBBChjEIWRwrh5jGpYnEViZqkh6G3UCH4tGs1bByJSYo%2BAyjtrY2yRok6Z0OC6KJiwBQKoJQqmFSSUYb1rGTx%2Btc8utzgbyBcY8yGCRSCePhplHxKNpEBJ2kBfYuMeUsAdU6l1brbQe3ZJTXJnMEkJGSUc5R1quYHRzTTLyyBkjJDAmYyM7qCDRl5bdYWFS4hVKljLZW9TO0qzVvPLWbTBAdKNqMzAZsLZWxtqVQZwy1m8DGW7D2qNvbIF9nMwQgdFkhzDt8VZUcvqbN4NstIuyU6O0OQo45TBc750LsXW29i/USDuSDINtdEgvMbiCz5UKu51Btjhfubzm4jzHhCqe8BZ5koXnCpeCKghLypefbFu86jwZxSfRlADSWEopb0eDl86g31fsi7D9L8N0s/jMLD%2BKgGssBlGqRY9uX2ruo651qp03PFGGKr1kqC0KNwfgwhlAwHKpAGYcxCQEgpTagEMa0msQCKY/4w181FoytISlShKUeqdQoZIChzVqFcFDQshI0bmOGpNWA16KmDXSsE6QeO6RnCSCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/is_same_as.hpp)
- [unit test](../../../../tests/unit/typelivore/is_same_as.test.hpp)
