<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredFoldLeftFirst`

## Description

`Varybivore::KindredFoldLeftFirst` accepts a list of variables and returns a function.
When invoked by an operation, the function left-folds the list using the operation with the first variable as the initiator.

<pre><code>   Initiator, V<sub>0</sub>, V<sub>1</sub>, V<sub>2</sub>, ..., V<sub>n</sub>
-> Operation
-> Operation&lt;
   Operation&lt;
        &vellip;
   Operation&lt;
   Operation&lt;
       Initiator, V<sub>0</sub>
   &gt;::value, V<sub>1</sub>
   &gt;::value, V<sub>2</sub>
        &vellip;
   &gt;::value, V<sub>n</sub>
   &gt;::value</code></pre>

## Type Signature

```Haskell
KindredFoldLeftFirst ::   auto...
                -> template<auto...> class...
                -> auto
```

## Structure

```C++
template<auto...>
struct KindredFoldLeftFirst
{
    template<template<auto...> class...>
    alias Rail
    {
        static constexpr auto value
        {RESULT};
    };
        
    template<template<auto...> class>
    static constexpr auto Rail_v 
    {RESULT};
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

template<template<auto...> class...Args>
using Metafunction 
= KindredFoldLeftFirst<1, 3, 4, 3>::Rail<Args...>;

static_assert(Metafunction<Subtract>::value == -9);
```

## Implementation

We will implement `KindredFoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<auto...Variables>
struct KindredFoldLeftFirst {};

// Base Case:

// Fold once.
template<auto Initiator, auto Variable>
struct KindredFoldLeftFirst<Initiator, Variable>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value 
        { Operation<Initiator, Variable>::value };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

// Fold twice.
template<auto Initiator, auto First, auto Second>
struct KindredFoldLeftFirst<Initiator, First, Second>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value {
            Operation<
            Operation<
                Initiator, First
            >::value, Second
            >::value
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<auto Initiator, auto First, auto Second, auto...Others>
struct KindredFoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value {
            KindredFoldLeftFirst<
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value, Others...
            >::template Rail<Operation>
            ::value
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxmpK4AMngMmAByPgBGmMQgABzSAA6oCoRODB7evgFBaRmOAmER0SxxCcm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfFJ0gpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG5MXkQAdJcAas14TDH0CkfYJhoAgmPEXg4A1ADS4XQxEw6AAYp50CFMFQCKC8MQxj8TAB2KzIgAiRys71ebwA9HifhYmEoficlCBcbiCT9wbR0D8BBtzrjtrt9pgjiczqgfgBJBiZJhEMg/U5EH43Yh3B6cw4vd6fb4Ef6A4FgiFQmFwhEELkCoUi0iS273ejPKmo3E/G0/Nl7YVytz2jlc8WoS4s%2BU/ZAGBQKH4AeRS8WFWQt71tPyVv2UxFQRAASkw6NbbSjsW8o1GZo5kD6BGNMKoUsQxTyfgA3MReTBIyPZm0ZoMh4hhgT6wWOYUkY1SmXm%2BUgEDV7x1lGYw6ZqMTrFUhs2l2OrlLg7Hd2e54%2Bv0KT1vYDAnaMAhPeVpm1eDJGH7JuhIw7on5xhOoW%2B0Ln7w9sQS7y4WqeWpOmbUoSdIMgQADueDMqyOwOmu3ISga3ZGuWEo6mMxruj8QiYGgDDoBGHwEF8vwAgR6pgVqsLwmMnaGr2tK0QQxq4fhhFnjiVoLnacGuscq5Ohuf7er6JIBsGob1EROYkcqT7xkmKbvjxGbntmubQQWDBFiWZbYaOtZItxWaNtmklttJxzqWZLZSeG1k8bZUbIXcqEYXqTlmc8w6GZgrF4QIhFeY2PkjjWnIhcZQHqbOAE4jxgkrnxy7rjym6iTue4HpgR4/jJtqXuEwA3sp96Ps%2BSmpscn65d%2BJ4ZS88VvHFwHvDSiZ4WsGSVnW5LsPO%2BKgRCdpQRsxoIIY6D0HaCB1jQuqzYePwpM0rCYNsCKkCBYoET8wLIN1dZFdeBBzftmBjCy7xJWlSFdm5jHYR5WEVmxQWvRclyBmd8SngqxGkSq5FAiCVHQjRur0ShjEvThgUEcaP1zQijWWtOtq3c6KUIcJXrYNu4l2ZZDkA7JQMKS%2Bb6xSZtmafm%2BG6aWaG8n5xkY85qoUWDmoQx5XI2ZzxPtgwAtRbZFki2LplC2Zrk9qK/Pi95Q7hWOAXsYLnNhX5SO/ajf7K02quCaV1VuJLVlk0LvkRVr0VzqpGKOy1iU406WN41uYn%2BtlX7Hv96knSVb7lZTVXvjVOV5Q1IlNcBzvNdSABUqdp%2BnGd4inac/AAKpdJ4/OnWftRnZfF4N5iHOEvpeFg95uPhGwpCeRGweyqWIbybyfbyVicYD8lCF4MQkUwDjo%2Bp9PaUz%2BkVn5NMWD8bwALRL61gEu%2B38Ee%2B7brpXHhO%2B5cbzEMAgfvMHPwALIbUwVBeAwDhZPWLUPlzoMavS1H88cXDGocY00gfiHDCtTGqZ9fz4y3oqJoeYAD64l4gEAgLfJoD8n5WTcMPUebYJ6qzZkcScj4V4AE5FhYg4MsWgnB/C8D8BwLQpBUCcDcNYaw0ZVjrHHGYQ4PBSAEE0FQ5YABrAIkhzgaEkFwZEhwND%2BA0GYAAbEoswiREj6E4JIXgLAJAaA0KQBhTCWEcF4AoEABjBGMKoaQOAsAYCIBAKsAgKQzjkEoGgXYdB4iRHWpwVQiQlEryUZIH4wBkD5ikOcMwvAQSEBIHgdAeh%2BCCBEGIdgUgZCCEUCodQ1jSC6H/hBNsKROA8GobQ%2BhQjmGcEDGcVxKpUBUB%2BAEoJISwkRJ%2BFEswPwIAeC8fQMsVcuCLF4FYrQywIBIE8SkbxZAKAQBmXMkAwApBBBoLQTa5iIAxGqTEcIzQACeZTeD7OYMQQ5gYYjaDwlY/hnj6qBgYLQY5%2BSsAxC8MAE4tBaDmO4LwLALBDDAHEG8%2BEty8C9T%2BUw4sXVtgnPIIIWo1TaB4BiG2C5HgsDVJIngXR/zSC9WIDEdImB0Q7GBaiowQjlhUAMOfK4eBMAQUkgw/hKThCiHEJkjlOS1DVMKfoYFKB2GWH0Gi8xkBlioBblkP5K8xgcXRKYSw1gzDGKJdKLAkqIDLDsBC5wEBXCTD8P/UI4RBgVGGP/QomQBAmr0La%2BocwhgJH/vq5%2BAhegTE8O0PQHr6jev6Ba%2BY1rbDjFaL6vI7qI0uqtW6vVXCNgSAqRwOhhjqkmJaYE4JoTwmRIkT0iAuB4lDN4SMsZNLlhzSYFgBIurSBiMkIcc4pDDjIkkFIswkglH6P8Eo0hmiODaNILovh5wlFcCUYkUhiQp3%2BGkf4NtSiM35JMWYixAiaW2IcVMpx9S3ELKWYM3xbBODNBYJWZEK8mCE2vFwUh5wuCSNifgEUiTkmyDSdy6QvKlD8vyboIIxSmClP%2Bam9NRjeAmLqS4s4jJmkXqvTeu9JUH1Pskb0/pszBlIl4WYUZW7rGTOmagAZ8R3GLLIzh4YSHr1iSMA%2BrgBiNlbMoLs/JZyjkIq4xcq5NyHAIoeceJ5LzqnvM%2Bd835CLAWUs2Ew/AB1HBQuqbCw68KCXhG2DQ/JqL0VHKxfJsZ0p8X8KJSSpQ5KgVGCpaAYjfB6UKEZcy1lCKOXfoyb%2B2QfK8lMKA0K6lKqrBir0zq6VsrCycAVQQJVQW1UaviFqy68A9W1ANX4I1BEHVmoInGhYNr0h2uyFG01pAnVZDy2GgNPQI3Za6OloNlW3Xhr6HVmYLQmsppWGsZNIyh2QczZwMUxBL3XtvQxtDj7n0aF6SWkUeG%2BGEfGcI0gNa62UFTSOsdj6pHIiXciWRkhu0hP/lBmppjbCbuW5M3dSBnENMo8enxfiOAXvaSwBQlZ8yVnQxyMYr7S0fv/u5rlnmsnyH/b5nQIBAEgbA%2BU/rVS121IPY0xDI33ufe%2B79x0iI%2BnUbmQtw4S3t17qe/MjxBPBkjmQCkFI8CfukPgX9ggiCMe/roGxnZeyDkXJ47zy51zblCbI4855ryFOYA%2BV8sQ0mCWyZs0Z0gimIUqfyWps4mx%2BFaeRbptFGLDmGZxSZhF5nSVWcpcVbddKmAMqZSykMbLeAg/SRILz2TIcCphwF4woqbChZS8wiLOlOB4kVSK1Vlh1XQc1Yk5LUr6ueoy8akrehzVlFdY6wr9Q6vlZKCGzP7q0tJ6DW14vgbY0F/jf62rqeY2zCr/lxNPWMkQaR8Yobb3Qkfa%2B1WHH2w8dzZIAtitRGJnVswLW4YDadNbZAGYR9hxDj%2BAUdI/RS/kTTtXR3i75jLFVsbSASQ/hW3%2BESMo0hkhSGyPbVwQBOnDjt%2Bg5wStxHU0xO38/i713lhEoyM4SQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/kindred_fold_left_first.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/kindred_fold_left_first.test.hpp)
