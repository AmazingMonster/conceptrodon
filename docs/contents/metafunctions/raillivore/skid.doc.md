<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Skid`

## Description

`Raillivore::Skid` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

The only difference between `Skip` and `Skid` is that `Skip` uses `R_il` for initiation and `Rail` for recursion, while `Skid` uses `Rail` for initiation and `R_il` for recursion.
<pre><code>   Operation{FirstLayer{...LastLayer}}
-> FirstLayer{...LastLayer{Operation}}</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
Skid ::   template<template<auto...> class...> class... 
       -> typename...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> auto...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skid ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class...>
struct Skid
{
    template<template<auto...> class...>
    alias Rail = INITIATION;

    template<typename...>
    alias Mold = RECURSION;

    template<auto...>
    alias Page = RECURSION;

    template<template<typename...> class...>
    alias Road = RECURSION;

    template<template<auto...> class...>
    alias R_il = RECURSION;

    template<template<template<typename...> class...> class...>
    alias Flow = RECURSION;

    template<template<template<auto...> class...> class...>
    alias Sail = RECURSION;

    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RECURSION;

    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RECURSION;

    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Lull = RECURSION;

    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RECURSION;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RECURSION;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RECURSION;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RECURSION;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RECURSION;
};
```

## Examples

We will move the *0*th layer of `Operation` to the end of its invocation order.

```C++
template<template<auto...> class...>
struct Operation
{ 
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage {};

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

using SupposedResult = Operation<std::index_sequence>
::Mold<void>
::Page<0>;

template<typename...Args>
using Metafunction = Skid<Operation>::Mold<Args...>;

using Result = Metafunction<void>::Page<0>::Rail<std::index_sequence>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Skid` relies on a helper function called `LoadSkid` to keep a record of user inputs.
The record will be passed to `Omennivore::Press` to invoke the previously provided operation.
We will implement a simplified version that only handles `Mold` and `Page` as a demonstration.

```C++
template<typename...>
struct Capsule;

template<auto...>
struct Shuttle;

// We will use `Items` to keep track of user inputs.
template<template<template<auto...> class...> class Operation, typename...Items>
struct LoadSkid
{
    template<typename...Elements>
// User inputs will be kept in `Capsule` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkid`, waiting for more inputs.
    using Mold = LoadSkid<Operation, Items..., Capsule<Elements...>>;

    template<auto...Variables>
    using Page = LoadSkid<Operation, Items..., Shuttle<Variables...>>;

    template<template<auto...> class...Sequences>
// When finally initiating the operation, we invoke the skidped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
    using Rail = Press<Operation<Sequences...>>::template Mold<Items...>;
};

template<template<template<auto...> class...> class Operation>
struct Skid: public LoadSkid<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEmYAHKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHASYLGkGeyaBbgQAnmmMrJgA1ADyV8RMTSfYJhoAgpPEXg63ymImAUCg%2BnxMAHYrF9brDbnsDkdMCczpdrmwAHRYt5guG3H5/Ai3AAimFadFukKsEOJJ2h4K%2BAHpGbcLEwlLdREoQGDcXCEYcXsiYXCUXy8bCBUiURcrsxMdjAthOQYQbcPIImBEEqQwczbgAVBAJO54BS3AS0c4WyK3NJtG57Yh2pjIADWt3oVAIGPFEtl6MwWIxGr2glBIthOMj%2BIIv3%2BpPJtBRoa1kWIKdkjAICmDOKVfqpepZAHVTQwAG6oN13AjGzkkIEKDIMfBGeH7QV7W5sKoJC1UeH11BPF45Yu3ADuhAQQ7umFUcdde3QLvdvpjeK8WXbAcpgWJD1HTRAIClQtuAFlPOhM4Js7nFe9AhZKTHIbSX7yY%2Bfju/Tn6eK/sipxMF4RB5kqKrsuaQiYAAjl4jDbLqm5wmBEFYqGD6FgWMYEgmZJasmpxwYhyEgW42HhpBz7vO%2BUK3NuETAPCaL7oejwJGOzhnp2SIAkwwCUdROa0XSlI0nS36fPqABKmDIJsWQVncXLsDJQH8UKuFuIB/LaccpwBvKQZPtBaqptqZATmW%2BKYPazzdnWdw0MQkwus8bBOmuHpUMQqAsHOFoue5G6fBK/JoqZwaiQoqERZFbFyjcwb3KFEaJVGeFZbG8ZEomxF3uS6bFQ%2BtGkA8GXiQx9JJUxO6sXuJyHoCwKZfVYpMqW5ZVjWwVoMQTYtm2TWGXcvbVAOwUjtxrzdVOM7BQuS4OJgq72uuE5GowlWTnc9pqi5txNl4tBErEroekQAJNua/DOlQmyhbcERVqITS5vpkUmTcR5zTkp7AVeN5lTRT7ffu9GySycgMNu62%2BeabR3ECyDnMg9Crg9txPe0xrOm9qAfTkX1obCQPjSSRF0Ci6UE4%2BvpKkDaLSQxn70n6wG6ZD3OgeBqC0RZsEIUhDAoZDGGC1hWbhgl9W/QqGL0wkHWijleIEQVNMkW4ZFi9sYNiU%2BlUq2FEO1ZDzG7uxLW3e1MrRX9XFOYDfGIheyhCSJsvG0zdGQ5THvdoVtOnGbjNvCzVxs7lH6x3iXPjY7KVK58wBAvsOEa3C1usdetCrnboe6%2BnmdsOD/vRyBnNSV%2BXxgnzqKp2Z/tglr6pMGkChnTXMlN1LNXfHGhK3EICDgQQ9Cx7ZdzTrQtANXcJgAGwaAAkgioJr/CqC3DWDnws87rTQjhMMGk4Fk58Te38n/OYf7wtC5jMH/a7AiVYrreb/soI5R3UIqAmDoCEG6PAt4G5QiTsHSi39gzYHoBXHM0YYa3EUP2CIl8cyLQXrceI%2B8HJEgiJSNebgu492njvQwG0DDbFXC8ZarZpqrw3lvX0a9trGgYHtA6b9jorVcIjVhv8WDbw0Pgq6u9SEaCASAsBEDWF7S1I4dsOMWAkHLNg6%2BW5Gog0LhxW4cjQHgNvOHY8ORKqiMZpVch3de4okQVnSu%2BZnycx/PfchAtgwADU2h4CYLEeg/9oa6JYoJYShjjEKLMW4F2PEeG3GscGSq49J7T1OH44gASgnAnEgWeuDJcp31gSiQe5lX4gmDPrCiITbLcNxhEMQVpXoMGyGOXcw4LGfynL1astZ6wKFMVcVcBhzgJHCvqHaiT9ouiOvWCI8xBABJXBabpDBbg0KXufbRE4br3Arm0qsQJTxtTVDjPGL0iYkwEDo3Oei5LEUMWc/%2BcT1kohqeLPJENmbuy7HcAusTkk/NrhzfuniSn/LKd4ipqpI5QUqeaeJrwAEj3%2BDEkAdovBBLwMgIxwCTGKPMQDAQbxJLUjBQ3JkAAqWldL6WMj1HSg02AhAGjpYyml9LuWcqKeYQIERMZeCwPuNw4E6CEHOKgxuELPHlKfoioeHdkXjiga%2BGBULjJOyVqgzWaKiSAlQEQQFhZoHkw7KUh%2B0s27mo7oaogXtIlFjru43KWlLVeMfmXTAziUE50innCJy8Dy3SNagR1lFvW%2BvhW401lKinus1c3QMwYo3ILqTGQNgLnkBWNaDU4abyogt5C6mSgahBeDSMUdaClKFEjtiq0lpxJjoFPBELAqgAD6ShyJfNQaeE1pwqxEuhqc72KIND5ldbfbVrdPjEGABmz4WaiJPXFk0QxMS6bvN%2BYOtw87F35NdYG2tZ160hsvKurw67xxDtQCOsdwkJ1RxAI8sObgW1ttbAubtosKJTpkvMRwyBO0wQSAQCAn6QAKBuKB15p7zqpMrdW9ACGCBvBWHSDgaxaCcH8LwPw3BeCoE4HpSw1h8QbC2MvMwgQeCkAIJobDaw3QBEkBiDQkguAQkCBofwGgzArxXikVIuGOCSF4CwCQGgNCkEI1oUgJGOC8AUCAWTjGOBaDWHAWAMBEAgA2AQbB5BKBoAOHQBIUQbicFUMkFeABaFekhbjAGQHiqQGIzC8HWoQEgEC9D8EECIMQ7ApAyEEBgtQTHSC6C4KQSczw0icB4DhvDBHotKfuOBbB01bMOacy5tztwPNmFuBADw5n6DOn5VwFYvANNadIBAJAZm0gWbIBQCArX2sgGAFIMwfA6BOlUxAWI0XYhNOIOcZLvAJvMCm/cWI2hFIafo2Z5B9wGBWmi1gWIXhgDkIXqpojpAsAsEMMAcQmneD4DRo4VSx2FMLkUuBHY9GIh7DEwp2geBYjPCmx4LA0W4x4Ckyd1SxBYiZEwKSc7RgftGCY2sKgBhF0%2BLwJgScXFCP0cC8IUQ4gwt48i%2Boa7MW9AGER6Ycjlh9C/dU5ANYI5PqcHsy2lq1OrCWDMAp1AEPslYAZxANYdgVuAwgK4GYfg4thG1EsMYcXijZAEFLvQSumiLFGDUXoYuBADGmJ4LoehRcOH6FMIYcutfG/N6ruL8x2ia77DUEXVHtgSFSxwfDcmMucFuHlxzznXPufY6ViAuBfPVdo7V%2BrSO1jGhAWMYXpBWOSECBiAAnIECEkhONmEkGvPjK90/6E4BJ0gUm6MYhXlwFeyR0/JBr/4Lj/hM8r292TpTKm1MMaR01vTzWDPZfAiZrrgU2tVas2wTgbQWAVghPZpg0F2xcHTxiLgHHvP4CIALgLshguE%2BkMTpQUWye6AGwlruM2Pde/k8RzgWWjPgWmjPufC%2Bl%2BsRX2vjjZWKvj/7PyswOrHva7bTFrMfdrEfbrKrEAF/efV%2BIwFfLgWTGgc6VWSgMbMnObNoabE7LAhbJbFbGbUgdbbMTbbbMnXbfbQ7WgY7ejM7C7K7BTW7MXB7aLZ7JSPYIgj7BoaLH7P7bAwHHYBTEHMHejCHKHJQWHBgliXvFHISBQdHTHbHIgvHffULQ/WQEnaLM/fQC7FAawawOnWIIXJnNIFnDgNnAgMxYkTnawHnYjfnCBYEeAEXBoXXPwCXVsW3EIVsR3ZYRXTIZXXIQ3AoAIkoHIPwhXHXU3PXG3EI6XaIpofXC3CoK3O3OI/IBI%2B3FIkYJ3d3dYTYN3WrEvT3dLDvX3WAt/eAj/VfdfCRMPLfEgSkKPIAhrZjUgePLARIJPMTMvCvVfTjCEFvCEHjSQPPJzOLW/RTTgLvdTXvHTfTQzYzTrKAyzazDgGfArMRCsPFCsT/JESYTfCPfzOLVQgndQ8LeQY/UnBTXQYIC/JLIja/Mo3ne/IfIkVAQcTY5zbY3Y/YoUDycrcAqrZowIQIVo%2BYsAyrHUFY4EsYHYqtTtPY9PTtA4ggUDYgFgJzQbVA9ydA8bSbHA%2BjPA84RbZbBwIgkgwQMgnApgzAPbA7ZpWgm7fYBgoQm7PAO7PAVgsndg17Lg%2B8L7XgPg/7c4QQ4HbJUQ3gcQ6HKQ%2BHGQkAvgVHBQjHLHOUFQvfc4iQDQiLa47QkAYISnYwAw2nPgkwxTMw0mTgRkT9Ww7nXnRwwXFwxI8XSXeIvQWXVIvIsIoI7w9XCIy3b0l02IwYbwk3JI83SI7XbIsMyMwM/wl3Qo0LZ49vV4jgTZTErYhQHY24ZEjENEsrcPbfUE6PYArTOPTABPboj3PokAMwVfME/wfjLjGTMEiEWvVMu/ZTWwbvNolYFjEASQfwDPfwZIQTdPSQdPHjLPLgQ0zgQIF4rsmPEAj3LzTs6Y7svstYCHLIZwSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/raillivore/skid.hpp)
- [unit test](../../../../tests/unit/raillivore/skid.test.hpp)
