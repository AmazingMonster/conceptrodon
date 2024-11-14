<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Upend`

## Description

`Varybivore::Upend` accepts a list of variables and returns a function.
When invoked by an operation, the function instantiates the operation with the previously provided variables but in reversed order.

<pre><code>   Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>n</sub>
-> Operation
-> Operation&lt;Variable<sub>n</sub>, Variable<sub>n-1</sub>, ..., Variable<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
Upend ::   auto...
        -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Upend
{
    template<template<auto...> class>
    alias Rail = RESULT;
};
```

## Examples

We will flip `0, 1, 2, 2` and invoke `Operation` with the result.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<2, 2, 1, 0>;

using Result = Upend<0, 1, 2, 2>
::Rail<Operation>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Varybivore::Amid`.
We will label each variable by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding variable from the roster.

First, we need to create a label class.
We will pack each variable into a `Monotony` so that we can use it as a return type::

```C++
template<auto Variable>
struct Monotony
{ static constexpr auto value {Variable}; };

template<auto Variable, size_t I>
struct Stamp
{ 
    static constexpr auto idyl
    (std::integral_constant<size_t, I>) -> Monotony<Variable>;
};
```

We can pull out the variable of a given index by asking `decltype` the return type of `idyl` if invoked by `std::integral_constant<size_t, I>`.
Here, we convert an index into a type via `std::integral_constant` for argument-dependent lookup.

Now, we will assemble an overload set and instruct compilers to pull the variables out in reversed order. Here's the entire implementation:

```C++
template<auto...Variables>
struct Upend
{
    template<template<auto...> class, typename>
    struct Detail {};

    template<template<auto...> class Operation, size_t...I>
    struct Detail<Operation, std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Stamp<Variables, I>...
    {
        using Stamp<Variables, I>::idyl...;
        using type = Operation<
            // Note that `sizeof...(I)` is the total number of I...,
            // which is a constant.
            // We are doing pack expansion over the second I.
            // The result is a list of form:
            // sizeof...(I) - 1, sizeof...(I) - 2, ..., 0. 
            decltype(
                idyl(
                    std::integral_constant
                    <size_t, sizeof...(I) - I - 1>{}
                )
            // We pull the value result out of `Monotony`.
            )::value...
        >;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements..., std::make_index_sequence<sizeof...(Variables)>>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQgAMwAHKQADqgKhE4MHt6%2BEqkZWY4CYRHRLHEJiQDstpj2pQxCBEzEBHk%2BfoENTTmt7QTlUbHxSakKbR1dBVyT08Pho1XjdQCUtqhexMjsHOaJ4cjeWADUJoluXo60hACel9gmGgCCh8enmBdXyFPoWCoTxe7zeBEwLDSBnBlzcTBuqDOADV2ngmDF6MC3lNiF4HGcALICVBEBiPN4mWoWM5TJiOZBnNAMKaYVRpYhneFEM4ANzEXm%2BlIsKOIaIxmEpABFLtSpTKQSDwZDoRKrlzESKxfRSDS8AAvTAAfQIZwAkljXji8SbBpCFVSLm8zs6aW16YyBCy2Rz1Wc8Oh7rQQS6zhB/iAQOFwcBiGJDUzaYJYVkDcadebEth1mcALRPQnE0mPK6a9GYzPyim1aWJKwUsEQqF01VwhEAOg7pfFCgtVvxcjSrntddeIaVTZhV3HKth6o7bfzJyYCgUOoI90HzDYFpDfZNkswbToFypctrCqdLunzdh18nraI88XBhXZwA8oPY80dSmjQR5xmzyXs6e5nAeR5BlcH7xHSOQ/gQ6ARuEWCqIaSgAI4CgweywqaT4VhWwFnAA9MRZwAOrfMgxCYM2nIMGcqA8vEtCoEw6A0oejFUBc/gaP6gYmHxZwEAgxDbMACB%2BgwCDxIQhh7AuREgGcaReBieAMraaSwl29CrmaTxPkRQrBiGLpeFkRhnNpumomWmAGYBSEBrQ%2BEjuZFlWcAIkboKiSSu%2Bn6wQIsJmZ5IakWckQkt8ol0rxGi/qgVDzhAprrEJGh%2BgoImySJJJiGcDBjByKVmvOpDhRFzpRQA7ggmlSXguVMB6zJtIISmjjVLpRZRnI0Wc6CoOEPlpEwyAANZnKyE3MjkjHMRyonfEoTIcXh1U1VFAAq%2BU0QoXi0CaLWcmcdxTNxZz8MQLAgNtEVRclqUdul2Y5mcQS6gaKVpRluZnGYOqVWcGhto6PW9cNmAnOug4QI90MCbQiNEdDnnhpGgiYDGcYJp1BBIxjzrJvqf4/uTf1vQDn2moDXDAqe1bEzVmXo09ZEDWptC0IxNx5d8fLeN8h3HSaVDiSwiVEgwJICI8fHdST6wRsLArGVD5nAueJks7roJa3eLbG7O7Yds%2By4KPOrwxpgEKMAQPaEVrlljWcABKTDHpcgXgd7kFuLbNEO4I1sdvBiEgCwTBTUayGsmhmCYYwOFXC9aV6Y5mUEdgEbw6qI5nkXbzEQAVBXldV8RILlxXu3YEIu2VzXpdV%2B3Zet4bHzYV8PxuEyexpE7FqKo2M5qubC4u6B0FfjklaG271lCF4aTFJg6Ae454s/IFc8hQwsLA0DOrfRoOsl68y8%2BdvR0nXvZwDkOVwaGfOon2YFoRl7dCwgfzRL4XktG6TShorbxAIGGBCEYFCsCNMuWEq916ZE3nfcWOp0EnSeDnCwHBNi0E4AAVl4H4DgWhSCoE4G4aw1gaTbF2IKMwiQeCkAIJofBmwpogCIZINsGhJBcFqIkDQRCNBmH8P4MwyRUiEI4JIXg90uAaDfmQihVCOC8AUCAN%2B7DyH4NIHAWAMBEAgG2AQNSBByCUDQJCOg8RIjwM4KoZI/gcz%2BEkGcYAyAGRSDbGYXgm9CAkH9HofgggRBiHYFIGQghFAqHUPo0guggh1VjGkTgPACHENIRwyhnA3w3EsddFxbiPFeJ8V9PhZhQweDsfQDkhwuDrF4HorQmwIBIFsWkexZAKAQG6b0kAwApDAxoCdeI2iIAxDyTEcI7R7iZN4HM5gxB7hvhiNoWGejWG2LYIIN8DBaCLKSVgGIXhgBwl5to7gvAsAxyMOIU5eAaIODwMxG5FDWSwxuPsVhUZGh5LuDEWMayPBYDyQQUU91bmkGWjEVBB4HnADuEYDhmwqAGGAAoJEeBMB1WgmQ1h4ThCiHEDEkl8S1B5JSfoQwxhaGWH0HgGI2jICbFQMPHINycz/F9qYSw1gzDqOWqKLAbKICbDsNsnILgGDuE8N0PQoRliVGqHoYo2QBCzD8EETVzQRhqvGEEaVbyBCDBmIquYfQZXmsWIa0qehaSWvyLq2w9rVWOuaVsHYewJDZI4CQ0gajeAaLOKU9xnjvG%2BOqaGXAwTGnMOaa09FmxZLsXGJK0g3DJCJDbAATjqJIARZhJB8VEf4fN%2BhOAKNIPdFhbZAj%2BGSPm5IXB/C8K4EQwt/hg15I0VonRbD0WGJMZ0sxRSbjWIGagepDinEcHaCwHktQcxtSXNZLg%2Ba2xcH4YE/ARAxVhNkJE8l0hKVKGpUk3QwM0lMAybcgNQaQ35I4IUixAtypLpXWuxkBhN3bt3dlCAdSekNIuMwswLTh36I6V02dYH4jTsGQ0kA37V0bpGfm5RfA6DgmIFMmZSSVkLKWaQEjayNlbIcGRvZjtDnHLyWci5VzaA3NYfc%2BlTyKH4FeY4D5eTvnIF%2BWRgFciKHAtBfccF%2BwKFQrwDC1h8LEUQi42NEdmKmDYtxfiwlZGSWnuiee2QVLEkUJvXStFAqrBMuBRKjlXLPScF5QhfljKLDCtDaK/0jl4BSsaLavwEBXA6uVfKh1qwEh6syFq3IVq3X6pyBF9VJqAtmpaIsULqX%2Bh2qGMl417qhhZcKx0fLUWpUML9d6uRz7%2B2cEGsu1d67/0%2BS3Tu/hcaD0kAgyw6DbTOGkHTVgBIWa5G1vrdugRtRu21GEZIUtHiggvoHbYId/WOljqQOYyxyGEO9McWwTgS7yksAUDyBkPI2sqimPuhNoSggGbJUZ2J8hL1mZ0EkUgd6H1ZOrYG3JSSNHvuKV%2Bu6J2zsXau82K6IG9vgcOIkPrI7x0oaQ/01HCRzvr0NJd/NhprsEHAWD89eHJmUCIxQijJzWFU6o9s2js79kEAYycnjmBzmXLEGxsjnHHmybuS8mVAmklCZE7CsTQKWVSZk5C6FZHlNKCRWptFsG%2BBYpxXiglm59MnqexIYzcS3s0s%2By1lA7nmWsr85QxzzJODEXDNZoVIr4hit8%2Bym16W5UKtdWF9AZWNUxeaMVxLZRPWRadWl5oFrOjxYjzljLeWw8pZKzHn3JqPUVC9RV310Sn0A/UfV47njTvnd5FD8EMP42Hp68mmD7S020WG5QAN42QBmG3YkRIRCxGCJUZ32oza%2B2A84IO3Rqbs0gEkEQgtRDkgSPzZIfNwi6hcESH9xI%2BfQ0j7rwNuRASh8F80Tv9YmxlpZGcJIIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/varybivore/upend.hpp)
- [unit test](../../../../tests/unit/varybivore/upend.test.hpp)
