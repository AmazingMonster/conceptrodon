<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Skip`

## Description

`Roadrivore::Skip` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.
The only difference between `Skip` and `Skid` is that `Skip` uses `R_ad` for initiation and `Road` for recursion, while `Skid` uses `Road` for initiation and `R_ad` for recursion.
<pre><code>   Operation{FirstLayer{...LastLayer}}
-> FirstLayer{...LastLayer{Operation}}</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
Skip ::   template<template<typename...> class...> class... 
       -> typename...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> auto...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class...>
struct Skip
{
    template<template<typename...> class...>
    alias R_ad = INITIATION;

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
using Metafunction = Skip<Operation>::Mold<Args...>;

using Result = Metafunction<void>::Page<0>::R_ad<std::tuple>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Skip` relies on a helper function called `LoadSkip` to keep a record of user inputs.
The record will be passed to `Omennivore::Press` to invoke the previously provided operation.
We will implement a simplified version that only handles `Mold` and `Page` as a demonstration.

```C++
template<typename...>
struct Capsule;

template<auto...>
struct Shuttle;

// We will use `Items` to keep track of user inputs.
template<template<template<typename...> class...> class Operation, typename...Items>
struct LoadSkip
{
    template<typename...Elements>
// User inputs will be kept in `Capsule` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkip`, waiting for more inputs.
    using Mold = LoadSkip<Operation, Items..., Capsule<Elements...>>;

    template<auto...Variables>
    using Page = LoadSkip<Operation, Items..., Shuttle<Variables...>>;

    template<template<typename...> class...Containers>
// When finally initiating the operation, we invoke the skipped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
    using R_ad = Press<Operation<Containers...>>::template Mold<Items...>;

};

template<template<template<typename...> class...> class Operation>
struct Skip: public LoadSkip<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEmYAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHASYLGkGeyaBbgQAnmmMrJgA1ADyV8RMTSfYJhoAgpPEXg63ymImAUCg%2BnxMAHYrF9brDbnsDkdMCczpdrmwAHRYt5guG3H5/Ai3AAimFadFukKsEOJJ2h4K%2BAHpGbcLEwlLdREoQGDcXCEYcXsiYXCUXy8bCBUiURcrsxMdjAthOQYQbcPIImBEEqQwczbgAVBAJO54BS3AS0c4WyK3NJtG57Yh2pjIADWt3oVAIGPFEtl6MwWIxGr2glBIthOMj%2BIIv3%2BpPJtBRoa1kWIKdkjAICmDOKVfqpepZAHVTQwAG6oN13AjGzkkIEKDIMfBGeH7QV7W5sKoJC1UeH11BPF45Yu3ADuhAQQ7umFUcdde3QLvdvpjeK8WXbAcpgWJD1HTRAIClQtuAFlPOhM4Js7nFe9AhZKTHIbSX7yY%2Bfju/Tn6eK/sipxMF4RB5kqKrsuaQiYAAjl4jDbLqm5wmBEFYqGD6FgWMYEgmZJasmpxwYhyEgW42HhpBz7vO%2BUK3NuETAPCaL7oejwJGOzhnp2SIAkwwCUdROa0XSlI0nS36fPqABKmDIJsWQVncXLsDJQH8UKuFuIB/LaccpwBvKQZPtBaqptqZATmW%2BKYPazzdnWdw0MQkwus8bBOmuHpUMQqAsHOFoue5G6fBK/JoqZwaiQoqERZFbFyjcwb3KFEaJVGeFZbG8ZEomxF3uS6bFQ%2BtGkA8GXiQx9JJUxO6sXuJyHoCwKZfVYpMqW5ZVjWwVoMQTYtm2TWGXcvbVAOwUjtxrzdVOM7BQuS4OJgq72uuE5GowlWTnc9pqi5txNl4tBErEroekQAJNua/DOlQmyhbcERVqITS5vpkUmTcR5zTkp7AVeN5lTRT7ffu9GySycgMNu62%2BeabR3ECyDnMg9Crg9txPe0xrOm9qAfTkX1obCQPjSSRF0Ci6UE4%2BvpKkDaLSQxn70n6wG6ZD3OgeBqC0RZsEIUhDAoZDGGC1hWbhgl9W/QqGL0wkHWijleIEQVNMkW4ZFi9sYNiU%2BlUq2FEO1ZDzG7uxLW3e1MrRX9XFOYDfGIheyhCSJsvG0zdGQ5THvdoVtOnGbjNvCzVxs7lH6x3iXPjY7KVK58wBAvsOEa3C1usdetCrnboe6%2BnmdsOD/vRyBnNSV%2BXxgnzqKp2Z/tglr6pMGkChnTXMlN1LNXfHGhK3EICDgQQ9Cx7ZdzTrQtANXcJgAGwaAAkgioJr/CqC3DWDnws87rTQjhMMGk4Fk58Te38nxlO0rbzC0LmMwf9rsCJViut5v%2BygjlDuoRUBMHQEIN0eA0i8ihEnYOlEf7BmwPQCuOZoww1uIofsERL45kWgvW48R94OSJBESka83Bdx7tPHehgNoGG2KuF4y1WzTVXhvLevo17bWNAwPaB137HRWq4RGbC/4sG3hoAhV1d5kI0MA0B4DIFsL2lqRw7YcYsBIOWHB18tyNRBoXDitx5FgIgVA8Ox4ciVTEYzSqFDu69xREgrOld8zPk5j%2Be%2BFCBbBgAGptDwEwWI9AAHQz0SxQSwkjEmMUeYtwLseK8NuDY4MlVx6T2nqcfxxBAnBOBOJAs9cGS5TvnAlOgZX6qkZlZdMoTbI8NxhEMQVpXoMGyGOXcw5LFfynL1astZ6wKDMVcVcBhzgJHCvqHaST9ouiOvWCI8xBCBJXBabpDBbi0KXufHRE4br3Arm0qsQJTxtTVDjPGL0iYkwELo3O%2Bi5IAH1QFGLOQA%2BJ6zipplVgU7AQcux3ALreU4KSIZFOgRzfuXjSkAvKTFcyb8QSVPfgk14gCR7/FiSAO0Xhgl4GQMYkBpilEWIBgIZ%2BRY64eNkgAKjpfShljI9T0oNNgIQBp6VMqZAynlNKuXFPMIECImMvBYH3G4cCdBCDnDQY3aF0LH6t2foiyO6L8of0SdA18sDYUPxbkPTWGKiSAlQEQIFhYYHkw7GU/mmE25Wo7iaogXsomUshQ3K1A8fFYjLpgFxqCc6RTzpE5eB5bqmtQC6yivr/WqvcRa91xStI2ubhUn1Gc/UoLqTGYNQLXkBTNaDU4Mas0FNromsEwahBeDSMUdaCkqFEjtqi8cpxJjoCBjWzJ0NTzmtOFWPAwKe0gCjSiDQ%2BZqW30VcGT4xBgDZs%2BLmoiT1xZNCMbEumnzmYgD7W4Wd86y0yWDQ2s6Taw2XmXV4Vdra3ADqHac72Y6o4gCeaAlE7bO2HBAvGj1w8xzIGeSCBIBAIAfpAAoG4gGUQnvOmkmtdb0AwYIG8FYdIOBrFoJwfwvA/DcF4KgTgelLDWHxBsLYy8zCBB4KQAgmh0NrDdAESQGINCSC4BCQIGh/AaDMCvFeZgAAcAn9CcEkLwFgEgNAaFILhrQpACMcF4AoEA0naMcC0GsOAsAYCIBABsAgODyCUDQAcOgCQog3E4KoATK8AC0K9JC3GAMgAlUgMRmF4OtQgJBB16H4IIEQYh2BSBkIITBag6OkF0FwUgk5nhpE4DwDDWGcORYU/ccCODprWbsw5pzLnbhubMLcCAHhTP0GdIKrgKxeBqY06QCASATNpDM2QCgEBmutZAMAKQZg%2BB0CdMpiAsRIuxCacQc4iXeBjeYBN%2B4sRtCKTU9RkzKD7gMCtJFrAsQvDAAoQvZTeHSBYBYIYYA4h1O8HwGjRwqlDtyYXIpcCOxqMRD2Jhy7%2Bg8CxGeBNjwWBItxjwBJo7qliCxEyJgUkp2jC0BYnRtYVADDzt8XgTAk4uK4eo/54QohxAhZx%2BF9Qn3ov6DOygaw1gvuxGU5ANYI5PqcFs%2B2lqphiOWDMHJ1AYOclYFpxANYdgluAwgK4GYfgYthG1EsMYMXijZAEOLvQ8umiLFGDUXowuBADGmJ4LoeghcOH6FMIY0v1cG5N0rmL8x2hq77DUQXZHtgSGSxwbDMm0ucFuDl%2BzjnnOueY8ViAuBvOVco9V2rCO1jGlAWMAXpBGOSECBiZIgQISSFY2YSQa8uMr1SB9sTpAJNUYxCvLgK8BPJAE%2BX/wbH/Cp5Xh7z7CmlMqZowjhrOnGt6cy%2BBIzHXAotYqxZtgnA2gsArBCWzTBoLti4MkDEXAWOefwEQXnfnZCBfx9IQnSgIsk5AH1uLXcpuu/d7J/DnAMsGfAtNcfk/p%2Bz9YvPxfLGStlaH/2QVZgavt8u5pprQfVrfvTrCrEAe/KfN%2BIwefLgaTGgc6VWSgEbT7GbNoSbI7VAubBbJbKbUgVbbMdbTbT7bbXbfbWgQ7ajE7M7C7OTa7YXO7SLR7JSPYXAt7BoSLOHH7NA/7HYOTIHEHajMHCHJQaHag%2BHf/PgZHBQVHdHTHXAnHLfYLHfWQInSLXQPrAwIwCndnGwTg/nenNIRnDgZnAgYFYkNnKwDnLnHnQdYEeAQXBoLXPwUXVsK3EIVsO3ZYOXTIBXXIPXAobwkoHITw2XTXI3bXS3fwiXMIpoHXU3Coc3a3SI/IaIm3eIkYe3F3dYTYZ3arETN3VLZvL3CAx/KA5/BfJfSRYPVfEgSkcPX/OrejUgGPLARIePAvcTEAQIBfVjCEevCEDjSQLPBzGLC/eTTgVvVTDvLTXTfTQzdrUA8zSzDgcfPLcRCsAlCsF/JESYFfUPXzGLBQvHJQ0LeQPfYnOTXQYIY/BLPDM/QornK/XvIkVAQcVYxzdYzY7YoUDyUrIAirOowIQIBo6YwA8rHUBY/4sYDY2tR5LY5IR5HYggZ5YgFgBzfrBA9yJA0bcbdA6jTA84ebRbBwXA/AwQQg9A2gzAHbPbZpCgq7fYag3gq7PAG7PABgz7Jg57Vg%2B8D7OTTg37c4HgwHHJAQ3gIQyHUQ2HcQ%2BrJHISaQtHDHOUeQzfY4iQZQsLc4tQrosnLQiwqnPQ%2Bw%2BTQw0mTgRkD9fUqw/DGwvnI0w3E8Fw9wKIvQKXBIzIwI3wtwlXYIs3d0mI43QYNw%2B0gM23X0rw2wZI/XJIhYMM2XR3HI4Le4pvR4jgTZVEtYhQDY24eEjEJEkrEPNfQEiPP/DTaPTAWPNo13QvCTFIDEIE/wbjNjKTIEiECvZMy/RTWwNvRolYBjEASQfwFPfwATXjZISQZIDjNPLgYID7QIB4jsyPf/V3Dzds8YzsnstYMHLIZwSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/roadrivore/skip.hpp)
- [unit test](../../../../tests/unit/roadrivore/skip.test.hpp)
