<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Sink`

## Description

`Roadrivore::Sink` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.
In contrast to `Skip` and `Skid,` `Sink` introduces a new scope to avoid name collision. Hence, it uses the name `Road` for both initiation and recursion.
<pre><code>   Operation{FirstLayer{...LastLayer}}
-> FirstLayer{...LastLayer{Operation}}</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
Sink ::   template<template<typename...> class...> class... 
       -> typename...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> auto...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Sink ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class...>
struct Sink
{
    struct Realm
    {
        template<template<typename...> class...>
        alias Road = INITIATION;
    };

    template<typename...>
    alias Mold = RECURSION;

    template<auto...>
    alias Page = RECURSION;

    template<template<typename...> class...>
    alias Road = RECURSION;

    template<template<auto...> class...>
    alias Rail = RECURSION;

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
template<template<typename...> class...>
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

using SupposedResult = Operation<std::tuple>
::Mold<void>
::Page<0>;

template<typename...Args>
using Metafunction = Sink<Operation>::Mold<Args...>;

using Result = Metafunction<void>::Page<0>::Realm::Road<std::tuple>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Sink` relies on a helper function called `LoadSink` to keep a record of user inputs.
The record will be passed to `Omennivore::Press` to invoke the previously provided operation.
We will implement a simplified version that only handles `Mold` and `Page` as a demonstration.

```C++
template<typename...>
struct Capsule;

template<auto...>
struct Shuttle;

// We will use `Items` to keep track of user inputs.
template<template<template<typename...> class...> class Operation, typename...Items>
struct LoadSink
{
    template<typename...Elements>
// User inputs will be kept in `Capsule` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSink`, waiting for more inputs.
    using Mold = LoadSink<Operation, Items..., Capsule<Elements...>>;

    template<auto...Variables>
    using Page = LoadSink<Operation, Items..., Shuttle<Variables...>>;

    struct Realm
    {
        template<template<typename...> class...Containers>
// When finally initiating the operation, we invoke the sinkped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
        using Road = Press<Operation<Containers...>>::template Mold<Items...>;
    };

};

template<template<template<typename...> class...> class Operation>
struct Sink: public LoadSink<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAbKSuADJ4DJgAcj4ARpjEEgDMGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQnJqQqt7Z0FPZODw5XV4wCUtqhexMjsHASYLGkGeyZJbgQAnmmMrJgA1ADyV8RMTSfYJhoAgpPEXg63ymImAUCg%2BnxMAHYrF9brDbnsDkdMCczpdrmwAHRYt5guG3H5/Ai3AAimFadFukKsEOJJ2h4K%2BAHpGbcLEwlLdREoQGDcXCEYcXsiYXCUXy8bCBUiURcrsxMdikthOQYQbcPIImBEEqQwczbgAVBAJO54BS3AS0c4WyK3NJtG57Yh2pjIADWt3oVAIGPFEtl6MwWIxGr2glBIthOMj%2BIIv3%2BpPJtBRoa1kWIKdkjAICmDOKVfqpepZAHVTQwAG6oN13AjGzkkIEKDIMfBGeH7QV7W5sKoJC1UeH11BPF45Yu3ADuhAQQ7umFUcdde3QLvdvpjeK8WXbAcpSWJD1HTRAIClQtuAFlPOhM4Js7nFe8khZKTHIbSX7yY%2Bfju/Tn6eK/sipxMF4RB5kqKrsuaQiYAAjl4jDbLqm5wmBEFYqGD6FgWMYEgmZJasmpxwYhyEgW42HhpBz7vO%2BUK3NuETAPCaL7oejwJGOzhnp2SIAkwwCUdROa0XSlI0nS36fPqABKmDIJsWQVncXLsDJQH8UKuFuIB/LaccpwBvKQZPtBaqptqZATmW%2BKYPazzdnWdw0MQkwus8bBOmuHpUMQqAsHOFoue5G6fBK/JoqZwaiQoqERZFbFyjcwb3KFEaJVGeFZbG8ZEomxF3uS6bFQ%2BtGkA8GXiQx9JJUxO6sXuJyHoCwKZfVYpMqW5ZVjWwVoMQTYtm2TWGXcvbVAOwUjtxrzdVOM7BQuS4OJgq72uuE5GowlWTnc9pqi5txNl4tBErEroekQAJNua/DOlQmyhbcERVqITS5vpkUmTcR5zTkp7AVeN5lTRT7ffu9GySycgMNu62%2BeabR3ECyDnMg9Crg9txPe0xrOm9qAfTkX1obCQPjSSRF0Ci6UE4%2BvpKkDaLSQxn70n6wG6ZD3OgeBqC0RZsEIUhDAoZDGGC1hWbhgl9W/QqGL0wkHWijleIEQVNMkW4ZFi9sYNiU%2BlUq2FEO1ZDzG7uxLW3e1MrRX9XFOYDfGIheyhCSJsvG0zdGQ5THvdoVtOnGbjNvCzVxs7lH6x3iXPjY7KVK58wBAvsOEa3C1usdetCrnboe6%2BnmdsOD/vRyBnNSV%2BXxgnzqKp2Z/tglr6pMGkChnTXMlN1LNXfHGhK3EICDgQQ9Cx7ZdzTrQtANXcJiBBoACSCKgqv8KoLcNYOfCzzutNCOEwwaTgWTnxNzfyfGU7StvMLQuYzB/2uwIlWK63G/7KCOUd1CKgJg6AhARDdLyKESdg6UW/sGbA9AK45mjDDW4ih%2BwRAvjmRaC9bjxD3g5IkERKSrzcF3Hu09t6GA2gYbYq4XjLVbNNFe69N6%2BlXttY0DA9oHTfsdFarhEYsN/iwLeGg8FXR3iQjQQCQFgIYBA1ee0tSOHbDjFgJByxYKvluRqINC4cVuLI0B4C6bHhyJVERjNKpkO7r3FECCs6V3zM%2BTmP475kIFsGAAam0PATBYj0H/tDXRLFBLCUMcY%2BREDw7mM/rcKxwZKrj0ntPU4vjiD%2BMCcCcSBZ64Mlyh3BSYgWCFigeTDsMCZQeLgeZV%2BIJYqyDTKrFB%2BoSxcNxhEMQVpXoMGyGOXcw44ncKnL1astZ6w7jdFcVcBhzgJHCvqHaIz9ouiOvWCI8xBD%2BJXBaYZtxqFLzPtoicN17gVz6VWIEp42pqhxnjF6RMSYCB0UlPOtw5LAKLgee2IIzEAwEMVZp5s27M3dl2O4BdbynESRDfJic65uPBIi/uNS0VVPvi3F%2BqpI5QXqeaF2PEGAoI7tEkAdovCBLwMgIxXzon/I/sSqCRYUUNyZAAKk5Vy7ljI9RcoNNgIQBouW8o5dy8VoqCnmCSBETGXgsD7jcOBOghBzgoMbuiiFKdAzYpgkPDuhL5rItfNArVmKdUW0KSPf4gJUBEChWUuqSUB5eMtfVDutqiBewiSyjmmlnUeMHliMumAnHIJzpFd53rl4/M9agaNKIQ1htxa4spfq2W5Rvg/VuSakHBL9O8qFhi40OtOLm8qcLa7poKe8oQXg0jFHWgpChRI7aGvHKcSY6Agb1rSdDU8pa3BVjwNC/tIAE2nA0PmJFWasXBuIMAfNXxC1ESeuLJohj6WxIBUy7AA7QZloXSmmey69HNrOq2n5l5V1eHXR2odqAR1R3Hd7FEU6wXFNoCwU8nyQEoi7T2w4IFU0ZvmI4ZAAB9GCCQCAQAAyABQNwoP/zcOe86yT62NvQGhggbwVh0g4GsWgnB/C8D8NwXgqBOB6UsNYfEGwtjLzMEkHgpACCaEI2sN0ARJAYg0JILgEIUj%2BA0GYQIgQzAAA5JP6E4JIXg36uAaFSORrQpAqMcF4AoEAqR2McC0GsOAsAYCIBABsAgWDyCUDQAcOgCQog3E4KoSTgQAC0gRJC3GAMgGlUgMRmF4OtQgJAR16H4IIEQYh2BSBkIIdBagOOkF0FwUgk5nhpE4DwIjJGyOJY0/ccCWDprObcx5rzPnbh%2BbMLcCAHhbP0GdNKrgKxeB6YM6QCASAbNpDs2QCgEBuu9ZAMAKQZg%2BB0CdNpiAsREuxC6cQc4mXeBzeYAt%2B4sRtCKT06xmzSD7gMCtIlrAsQvDADIQvbTFHSBYBYIYYA4h9O8HwGjRwqlLtqYXIpcCOxWMRD2MRx7%2Bg8CxGeAtjwWBEtxjwN%2Bq7qliCxEyJgUkt2jC0BYhxtYVADCLu8XgTAk4uLkdY%2BF4QohxAxZJ/F9QgPkv6Duygaw1ggexG05ANYI5PqcFc12lqphaOWDMGp1AcPMlYFZxANYdgtuAwgK4GYfgUthG1EsMYKXijZAEPLvQ6umiLFGDUXo0uBADGmJ4LoegpcOH6FMIYyv9cW5t1rlL8x2h677DUSXDHtgSGyxwUjpBVOUc4LcEr7nPPed87x6rEBcDBca8x5rrWMdrGNCAsYEvSDcckEkDEABOJIEJJD8bMJIVeGggi59kxweTpBv0sYxIELggRJO58k03/wAn/D5%2BCIH9TnAtM6bYxjjrJnOtmcK%2BBKzA3Ao9Yaw5tgnA2gsArBCVzTBoLti4LnjEXA%2BOBfwEQUXYXZCRfJ9ISnSgEs05AGNtLXclu%2B/973/LE%2BiSoEHEvlfa%2BN%2BsS3zvvjNWdWs%2B/Y0qZgLWQ%2Bj2hmXWM%2BvWU%2Bg2DWIAn%2Bq%2Br8RgW%2BSm4250qslAM2gOK2bQi2V2eBa2G2W2S2pAu22Y%2B2h2gOx2p252tAl2rGN2d2D2amz20ub2iWn2SkewZBf2DQiWaOIO%2BB4OOwamUOMOrGcOCOSgyOLB6OkBfA2OCguO%2BOhOZBJOp%2B0W5%2BsgVOiWugY2BgRgDO/ONgQh4u7OaQnOHA3OBA0KxIfOVgAuQuIuI6wI8AkuDQRufgsurYTuIQrYbuywaumQGuuQZuBQIRJQOQQRquhuVuxujuERCu8RTQJutuFQ9uzuSR%2BQKRLuGRIw7uPu6wmw3uzWVeT%2BeWweSB3%2BKBv%2B2%2Bu%2B4iMeB%2BJAlICe4BbWnGpAqeWAiQGeAONede2%2B/GEIXeEIQmkgJeHmKWz%2B/etgg%2BnRhmo%2BSA5mlm/W8B9mjmHAS%2BZWoiFYNKFYf%2BSIkw%2B%2BceoWKWmhZO2hsW8gl%2B1OamugSQqW6WD%2BFRuWgOL%2BFm4E00OxnmexBxRxQoHktWMBDWbRSQSQHRw%2BY%2BGxfW1moJYw%2BxDaEGhxueEGxxBAUGxALAHmGBk22Bs282BBrGRB5w62m2DgZBFBggVBBBbBmAJ2Z23SjBT2%2BwLBYhT2eAL2eAnBgO3B32fB94AOamQhoO5wohkOmSkhvA0hiOchqOCh7WWOQkKheOBOcoGhJ%2BVxEgOhcWdx%2BhIATxRhxgjOlgzOFh6mVhpMnAjIAGjh1ggulGrhYuHhqRMucuyRegSumRRRURYR/hOuMRduvpbpiRgw/hluaRNusRBu%2BREZ0ZwZwRnupR0Wj%2B7xQu1R2JuxCg%2BxtwqJGIGJNWseh%2B4JieEBBmKemAaefRvugxN%2B2%2BEJ/gImAmymEJEIzeAeVRmm8xumyemeIAkg/gee/gkmYmuekgueQmBetQVeSQ6ZQe3ZixvuAWnZHxcxS5pAcOWQzgkgQAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/roadrivore/sink.hpp)
- [unit test](../../../../tests/unit/roadrivore/sink.test.hpp)
