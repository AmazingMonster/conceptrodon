<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Conceal`

## Description

`Raillivore::Conceal` accepts an operation and returns a metafunction such that when invoked by an argument list, the alias member `type` becomes the previously provided operation invoked by the argument list.
<pre><code>Operation&nbsp;->&nbsp;Rail&lt;&ast;&gt;{type=Operation&lt;&ast;&gt;}</code></pre>

## Type Signature

```Haskell
Conceal ::   template<template<auto...> class...> class... 
          -> template<auto...> class...
          -> typename
```

## Structure

```C++
template<template<template<auto...> class...> class...>
struct Conceal
{
    template<template<auto...> class...>
    alias Rail
    {
        using type = RESULT;
    };
};
```

## Example

We will conceal `Operation`.

```C++
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

template<template<auto...> class...>
struct Operation;

using SupposedResult = Operation<Seq_2, Seq_3, Seq_0, Seq_1>;

template<template<auto...> class...Args>
using Metafunction = Conceal<Operation>
::Rail<Args...>;

using Result = Metafunction<Seq_2, Seq_3, Seq_0, Seq_1>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Raillivore::Conceal`:

```C++
template<template<template<auto...> class...> class Operation>
struct Conceal
{
    template<template<auto...> class...Sequences>
    struct ProtoRail
    { using type = Operation<Sequences...>; };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJJcpAAOqAqETgwe3r566ZmOAuGRMSzxiVwAHLaY9sUMQgRMxAS5Pn5BdQ3Zza0EpdFxCUkpCi1tHfnjk4MRwxWjNQCUtqhexMjsHASYLKkGeyaBbnsHR5gnZ/uHTMenTF5EAHRvJ9gA1MgGCgpvLw%2B31%2BCk%2BAHlUgl7tkPiYNABBCbELwOT4eBjbMRw%2BEmADsVgRnyJn3OdweNwu9yuj2eqABQJ%2BTD%2BAKEmAAjl5GNsFLDCcSkSiCJ9lMRUEQAEpMOjY4mfPEWT5eTJGEkAT0hcsCABFwZDiNCBNdWRyuZh/u9AtgTgq8VrrdiZcTSZdrs6qdcnq8LV9Gcy3sbORizbz4bKlRFgJ9JXRNTqRWLUNHaEb2YHufTLfaEbasziEQB6ABUxZLpfz2KLxYAKtghFWS%2BWC6Xm4XG3mcWZAhEfl4sJq3Ggg6kCDzM9mEW7yZ66d7sQLUcaAPoaXPYyfUtzTjNWhHzoVLririe3F00r2AseIgjIhfsxdmI/w9ce2nbufXwWfJeBR/P05/zdX29YEmXNC8dyvG8hQhKFGkfcMVSELxUkKTB0HFM0vFoIUTh1GD9Tg04lzMUgvzvYIyLZZdSIPWFAgJdsAIArdgN9MD4WIYBRwghDIwAWUwFoqC8DFGljNEBExZNTnwg0GBDEAQCTa4OK4t96IdBFeKjTDsPEgShJEhwYSIu8SMoxcKKXDQaLvQ9LUUgh1WpBj32hZBF1AhICAgCZ0EUhRWEwTzRzcDCFCwggaOQ1D0N0ggPhWa0ODWWhOH8Xg/G4XhUE4NxrGsT4FA2LZMDlTseFIAhNBStYAGsAkkF4NGSXFAg0fwNDMAA2bqzGqWo0o4SReBYCQNBsrKtFIXKOF4BQQBs6qOC0NY4FgGBEBADYCFSZ5yEoNADjoBIoiCzhVGqbqAFpuskT5gGQZBPikF4zF4NDCBIPB/JSfhBBEMR2CkGRBEUFR1BWnQ9AAd31VJOB4VL0symqZs4MFnj2oVUCoT5Lpuu6Hqel6mrMT4IA8Y76GIcrAi4FZeGW1bSAgJAjtSE6yAoCAOa5kBgCkEiaGwhIFogWI0diCJWlVRHeGl5hiFVMFYm0TAHHl0gjrYQQwQYWg5ah0gsFiLxgE3WhaAW7KTf2QxgHEY38GIDXHAANzNNHMFUDXnh2SqIj2IbptoPBYn1ZWPCwNHrzwMbbc94hYgyTAtXtoww6MGq1ioAwuIANTwTAYZgrLKv%2B4RRHEEHK/BtQ0d0FIDGz0xLGsfRw4WyA1lQYdsht66/NwturEsMxptQJPiB%2Br2e56N3shcBh3E8To9DCBZykqAoMiyARpj8FJCn3hghm35YF%2BMgR%2BimNeZivxpb/mMoRiqWw5kPvQJgGc%2B34kNYxVNjbAAfoFGpApo5U4PjK6t17qPWeq9cmEBcBfVpuYemjMqo5zWAgTATAsCJAgPVJIgQXgAE5Ai4kkC1MwkhuoTX8N1chYDhqjRAPTF43UuDdWqOQ6oPD/DJH8JQ7qEC0azXmotbBUM1qbTZttLG%2B0eZ8xpmdNgnBWgsHdria6TAQIqi4OQl4XBmofXwEQGev1QZVyBhIaQdclAN2NroEicMmAI2ysjDgGVxHG1mpjXazxPi40%2BFonReiDGRiMSY5qFMqacxpnTMwWDmYpVZuzVA1MEgHV5lkxJoxwm6MZEYIxXAbIiz2MQcWktjaK1llrepytVbq01rbHWjACD60NmjU25tLbWy1lgFgDsnbTRdovT2Ntpo%2Bz9nsLWQd6hozDhHWW0cdjTTjgnSqScU5KHTiMzOEYc58HzgoIuJcy5a0roDGuDjZD10htNVx%2BgHYoAKpYTusRu7EJmv3AQg9h7alHtYCeOVp6zx%2BYA%2Boi9nAQFcF/FIm9X5LHfifRoiK0h70aH/VF38YXXyaJ/e%2BR9H59DmLineswBiYp/m0SlyxAElRAQzVhvjIHow4GE4g2jdH6JKdE4xpiNAU1QZYumDMmY4NIHgghoxflDRGqQMagRjEtVxCI3EbVJB0LuikDlkjbDSLSXI%2BACidrY1yao0650OBaKJiwBQ7tnruxiZcCY5i0E/T0Dc6uwN7lgycU86GwR3GeKRmy1G/iMZKJxnje191HXOs%2BK64x7qhSU3yVzOmgRUknIUda7mh0s00xAM6lCi5U2LnTZ5Hld0%2BB0CqTUqWMtlaNNbSrNWbstYdL1gbI24zMBmwtmIQZtthmjI2bwCZxkpne19sgf2CzBBLONisyOqp1mxxnts3guzU4HNGcc2RpymCF2LqXSE5deC%2BrsbXB5QbG4cNea3D5NgVlQr%2BY0G2%2BY/LvPbuPSeEKsCfrsLCvw8KV6YuRYsKlWKijZExei7IDL35gcJc/WlBKn4Uq3v/ald88ikrpS/WDjL1jAOBt49lEjoEJs%2BEml1bqqQTFFRYkgEq82yNwfgwhlBvFKrGmYYxgRAj%2BE6skCaoncS8L8ZPTgUilrSoapIfwFD/DVB6uQyQ5C2pUK4MEIagQo3ybmjI1a3j3pyagWZk1awk6ZGcJIIAA)

## Links

- [source code](../../../../conceptrodon/raillivore/conceal.hpp)
