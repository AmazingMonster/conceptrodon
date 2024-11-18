<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Among`

## Description

`Varybivore::Among` accepts a list of variables and returns a function.
When invoked by an index, the function returns the variable at the index from the list.

<pre><code>...Variable<sub><i>i</i></sub>... -> I -> Variable<sub><i>i</i></sub></code></pre>

## Type Signature

```Haskell
Among :: typename... -> auto... -> auto
```

## Structure

```C++
template<typename...>
struct Among
{
    template<auto>
    alias Page
    {
        static constexpr auto value 
        {RESULT};
    };

    template<auto>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will pick the variable at index `3` out of the list `0, 1, 2, 3`.

```C++
static_assert(Among<0, 1, 2, 3>::Page<3>::value == 3);
```

## Implementation

We will implement `Among` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the variable at the index is returned. Otherwise:
  1. Drop several variables from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `Among` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<auto...Variables>
struct Among {};

template<auto First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { static constexpr auto value {First}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    { 
        static constexpr auto value 
        {Among<Others...>::template ProtoPage<I - 2>::value};
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { static constexpr auto value {First}; };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    { static constexpr auto value {Second}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxBIAHKQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxXEl2mA6ZQgRMxATZPn4Btpj2RQwNTQQlkTFxibaNza25HQrjA2FD5SNVAJS2qF7EyOwc5gDMYcjeWADUJrtuyDPoWFRn2CYaAIIPjwSYLMkGb2duTF5EADogQA1Jp4JjRegKO4vGbELwOY6PFgCYCnADsVnRABEzlYni83h8vpgfn8iMcAGJ4YgzGFPOEIghIlFGH7U2kEenPTEvY7845Ez5Mb7ndIAL0wAH1mQBJbkC46MxHKYioIjKJjATAYrG43b455PRVCkk/CXSuUKgXETAARy8NMwCmOEHlu312I0yz5AuVzNV6tQmu1P3d92NApMmKVjUcyGOaAYM0wqmSxGO5NQxwAbmIvDroxYOXScXiMfrDb7%2BaaRaTzlmgQDHsBbe9GARobsI49FV50kZjiHCx6h2qNVr624W222IIFE2YQaXtHKyunrXRb9/tmSwRSJmd8chLUBOgD42gQB5AgIOJdnv%2Blmo9k0mYHk9J8/HG932mL7sV15SMa3eYUtwtGVjnDatY3hFVx2DSdThA3UUN7RU/TjPAEyTFM0wzLNc3zQtUMVItkRfc5f3vADsBAEBNx1QMJ1Dc5ZWOABaY4zDuBi828Uky2XVDVzxdcMNA4k63NPBJSgmDUNtB0nRdN0zk9b1YKfFikLYtxFMktCZhFHDEwEfD00PCkBILXU9zEg0K3EglUKY2T5KtQClPtR1bTU91PS4H1UJ0xDhzDa1%2BSLWNTNwiy3gI6zs1swtMU/M9HIsZyRKNIz3IbHcmxnTB23nKLjn7MI0WHU5R10iLzhKsrOzolyeTXVzHgAegAKn6gbBu6l4%2Bv6gAVbAhDGgbhqeUbBqGiS9gOI4RwuAQtmSTtuVhbDkClJgFCUZoIEotlzg0A8uAPQJjl2PiQEatx7u7fiSLqz07p9XKOFWWhOAAVl4PwOC0UhUE4NxrGsJV1k2QszF2HhSAITRftWABrEAAckAENEkLh0V2DQAY0MwADZybMBIkn%2BjhJF4FgJA0S6QbBiGOF4BQQEu1HQd%2B0g4FgGBEBAdYCGSf5yEoNAPjoOIIlYbZVAScnOPJyRjmAZAEykAEzF4TB8CIYg8HQPR%2BEEEQxHYKQZEERQVHUfnSF0a6AHdiCYZJOB4P7AeBtHwc4K9/kl5lUCoY4VbVjWtZ1449bMV0PDl%2BgMz2YLeD5rRVggJBZeSeWyAoCBC%2BLkBgCkQIaFoN5aUoaIg%2BiMImgAT193gW%2BYYg26vaJtFqPnkdlucCCvBhaA7l2sGiLxgF%2BWhaG57heCwFhDGAcQZ6dOoc2dIPU1qf5tmRsI3jpsHaDwaIvd7jwsCDghTaZ1fSH34hojSTBsXeTfr6MGjVYVADDAAUMCPAmB3ZXmSIwTu9thCiHEHbS28glBqCDm7fQm8UDQ0sPoG%2B3NICrFQFtTIK9OJXA0qYSw1gzDsw/qbLARCICrBqHUZwEBXCTD8NdEI8wygVD0AUDIAgeHCLSKIhggxBFLE6N0eosxxHXXYT0PozQZHDEqGMfoyidEaIEVoiQbC4ZbGMfoAOpA2a8A5tHVW6tNba11rjZOEBcCEBIKcRGWcUZANWHeJgWB4isNIFjSQuwAQAE5djokkPjMwkhyYswBuTSJFj6aMxAEjAE5MuDkwSJEhIeScZcABtE8mVig4cy5jzXx/M84i3zmLMOUtS7l3TorNgnAmgsBzOiTiTBEwGEHFwSJAIuB40NsbEgZsLayGtsg6QqDHYYJdroQIntvad39hwIGlSXYc1DhLf4xxI6ZmIL0/pgzDib0TmMiZGgU6oDTnELxuwzDLGzkAwWBdnlF3TtLMufyK49L6ZxG5RhRlcEurXeu3MIBNxdt3du8DkW937oPBw8DR4dgnlPIOs956L2XvA9e/9thg3wLaPeB8XZH2QCfeB58uhB2vrfduD8KXZxfvAj%2BX8lC/w3kYABoB6l8FAeAyB0DYEg2RqghZtslmyBWc7MG6zsGAJoVYfBbKWEkLIRZTglCCDoGoXgiw9CbGMLNgfYh8ih6ZBcAwdwng2h6H4aUIx10RE9D0T6zImjFjaNUYo3RrrcgqK6A6gQ6i5ieqDXoEyExw28P0XGhYQjgprA2GYrNdM9nWODhwc5lyBlDNuaM8ZeNXTuJNm8nxOd0akACUEygOyGakCZrsMZ%2BN0RlPRETAIiSCb7PZpwGpvNvlC1FuLcOgL2kKyVt0i5ccWAKBzAmHMlaSQzCmR4phcyrZIMVQglVmCsmkE2T7VeOyC1VJDi0iOUcemrvXZu7ddYZhPJeRnRGuxPl1Nzj8lAwKAVtNAyMDdyRkhSi3ZEqUO6CAHRXUsugcLG7N1br3VFWG%2B4DyHti55Y88XT0pZgOeC8xAkrfmS4VXLSBUodfvFeYN6WMrfsyy%2BvA2V3zbpyp%2BPK358u/oK/%2B1VvkgK1JKqBMC4Fv3lceiQSqHboNVToC9wzjDmoIdEPV4MDXJk4N1K4uDaGWEteDa1zD4BsKjRwvwXDnV6I9RmuR/qxEpokYUANhiE2RoUTGpRnn/PRt6LMQNma016KTem2RlQTE5ttrewOBzOAltfRu3MH63hfrcdM39SMAONuWP4zAgSRghLph2pmZgxm7F2ADUmBMWb1fRPk0dNjx22FqcVzG/gAZRIBgkCmkTJCRKJjErgux0m7BS2OzmgGm10wNh1otXz6mrA/ukZwkggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/among.hpp)
- [unit test](../../../../tests/unit/varybivore/among.test.hpp)
