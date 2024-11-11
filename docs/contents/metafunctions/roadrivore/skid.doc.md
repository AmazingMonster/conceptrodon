<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Skid`

## Description

`Roadrivore::Skid` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

The only difference between `Skip` and `Skid` is that `Skip` uses `R_ad` for initiation and `Road` for recursion, while `Skid` uses `Road` for initiation and `R_ad` for recursion.
<pre><code>   Operation{FirstLayer{...LastLayer}}
-> FirstLayer{...LastLayer{Operation}}</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
Skid ::   template<template<typename...> class...> class... 
       -> typename...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> auto...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Skid ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class...>
struct Skid
{
    template<template<typename...> class...>
    alias Road = INITIATION;

    template<typename...>
    alias Mold = RECURSION;

    template<auto...>
    alias Page = RECURSION;

    template<template<typename...> class...>
    alias R_ad = RECURSION;

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
using Metafunction = Skid<Operation>::Mold<Args...>;

using Result = Metafunction<void>::Page<0>::Road<std::tuple>;

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
template<template<template<typename...> class...> class Operation, typename...Items>
struct LoadSkid
{
    template<typename...Elements>
// User inputs will be kept in `Capsule` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkid`, waiting for more inputs.
    using Mold = LoadSkid<Operation, Items..., Capsule<Elements...>>;

    template<auto...Variables>
    using Page = LoadSkid<Operation, Items..., Shuttle<Variables...>>;

    template<template<typename...> class...Containers>
// When finally initiating the operation, we invoke the skidped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
    using Road = Press<Operation<Containers...>>::template Mold<Items...>;

};

template<template<template<typename...> class...> class Operation>
struct Skid: public LoadSkid<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEmYAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHASYLGkGeyaBbgQAnmmMrJgA1ADyV8RMTSfYJhoAgpPEXg63ymImAUCg%2BnxMAHYrF9brDbnsDkdMCczpdrmwAHRYt5guG3H5/Ai3AAimFadFukKsEOJJ2h4K%2BAHpGbcLEwlLdREoQGDcXCEYcXsiYXCUXy8bCBUiURcrsxMdjAthOQYQbcPIImBEEqQwczbgAVBAJO54BS3AS0c4WyK3NJtG57Yh2pjIADWt3oVAIGPFEtl6MwWIxGr2glBIthOMj%2BIIv3%2BpPJtBRoa1kWIKdkjAICmDOKVfqpepZAHVTQwAG6oN13AjGzkkIEKDIMfBGeH7QV7W5sKoJC1UeH11BPF45Yu3ADuhAQQ7umFUcdde3QLvdvpjeK8WXbAcpgWJD1HTRAIClQtuAFlPOhM4Js7nFe9AhZKTHIbSX7yY%2Bfju/Tn6eK/sipxMF4RB5kqKrsuaQiYAAjl4jDbLqm5wmBEFYqGD6FgWMYEgmZJasmpxwYhyEgW42HhpBz7vO%2BUK3NuETAPCaL7oejwJGOzhnp2SIAkwwCUdROa0XSlI0nS36fPqABKmDIJsWQVncXLsDJQH8UKuFuIB/LaccpwBvKQZPtBaqptqZATmW%2BKYPazzdnWdw0MQkwus8bBOmuHpUMQqAsHOFoue5G6fBK/JoqZwaiQoqERZFbFyjcwb3KFEaJVGeFZbG8ZEomxF3uS6bFQ%2BtGkA8GXiQx9JJUxO6sXuJyHoCwKZfVYpMqW5ZVjWwVoMQTYtm2TWGXcvbVAOwUjtxrzdVOM7BQuS4OJgq72uuE5GowlWTnc9pqi5txNl4tBErEroekQAJNua/DOlQmyhbcERVqITS5vpkUmTcR5zTkp7AVeN5lTRT7ffu9GySycgMNu62%2BeabR3ECyDnMg9Crg9txPe0xrOm9qAfTkX1obCQPjSSRF0Ci6UE4%2BvpKkDaLSQxn70n6wG6ZD3OgeBqC0RZsEIUhDAoZDGGC1hWbhgl9W/QqGL0wkHWijleIEQVNMkW4ZFi9sYNiU%2BlUq2FEO1ZDzG7uxLW3e1MrRX9XFOYDfGIheyhCSJsvG0zdGQ5THvdoVtOnGbjNvCzVxs7lH6x3iXPjY7KVK58wBAvsOEa3C1usdetCrnboe6%2BnmdsOD/vRyBnNSV%2BXxgnzqKp2Z/tglr6pMGkChnTXMlN1LNXfHGhK3EICDgQQ9Cx7ZdzTrQtANXcJgAGwaAAkgioJr/CqC3DWDnws87rTQjhMMGk4Fk58Te38nxlO0rbzC0LmMwf9rsCJViut5v%2BygjlDuoRUBMHQEIN0eBbwNyhEnYOlEf7BmwPQCuOZoww1uIofsERL45kWgvW48R94OSJBESka83Bdx7tPHehgNoGG2KuF4y1WzTVXhvLevo17bWNAwPaB137HRWq4RGbC/4sG3hoAhV1d5kI0MA0B4DIFsL2lqRw7YcYsBIOWHB18tyNRBoXDitx5FgIgbecOx4ciVTEYzSqFDu69xREgrOld8zPk5j%2Be%2BFCBbBgAGptDwEwWI9AAHQz0SxQSwkjEmMUeYtwLseK8NuDY4MlVx6T2nqcfxxBAnBOBOJAs9cGS5TvnAlOgZX6qkZlZdMoTbI8NxhEMQVpXoMGyGOXcw5LFfynL1astZ6wKDMVcVcBhzgJHCvqHaST9ouiOvWCI8xBCBJXBabpDBbi0KXufHRE4br3Arm0qsQJTxtTVDjPGL0iYkwELo3O%2Bi5IgKLgee2II6brOKmmVWBTsBBy7HcAucSUkQyKbyOuHib5eNKf88pMVzJvxBJU9%2BCTXiAJHv8WJIA7ReGCXgZAxinmxPeQDAQz8izgpkoyAAVDS2ldLGR6lpQabAQgDS0oZUyOlXKqUcuKeYQIERMZeCwPuNw4E6CEHOGgxuUKoWP1bs/BFkc0X5Q/oksFr5YEwofi3Iemt0VEkBKgIggLCwwPJh2Mp/NMJtwtR3I1RAvZRPJRzTSSUB4%2BKxGXTALjUE50innSJy8XkOtQE6yi3rfXKvcWa11DdPFWubhUr1GcfUoLqTGQNgKjGhtNacSN6aCm1zjcUwNQgvBpGKOtBSVCiR2xReOU4kx0BAwrZk6Gp481uCrEonKpzvYog0PmCFt95XBk%2BMQYAGbPhZqIk9cWTQjFEosSShgUcQBdonVOotMlA01rOnWl5l451eAXY27tqBe2/JAOGwd67HmgJRM21thwQIxvjcPMcyAAD6MEEgEAgM%2BkACgbi/oAW4fd500kVqregSDBA3grDpBwNYtBOD%2BF4H4bgvBUCcD0pYaw%2BINhbGXmYQIPBSAEE0ChtYboAiSAxBoSQXAISBA0P4DQZgV4rzMAADl4/oTgkheAsAkBoDQpAsNaFILhjgvAFAgAk1RjgWg1hwFgDARAIANgEBweQSgaADh0ASFEG4nBVC8ZXgAWhXpIW4wBkD4qkBiMwvB1qEBIJAvQ/BBAiDEOwKQMhBCYLUNR0guguCkEnM8NInAeCofQ5hsLsn7jgRwdNCz1nbP2cc7cZzZhbgQA8EZ%2Bgzp%2BVcBWLwZTqnSAQCQIZtIxmyAUAgA1prIBgBSDMHwOgToFMQFiGF2ITTiDnDi7wYbzBRv3FiNoRSymKOGZQfcBgVowtYFiF4YAFCF4Kew6QLALBDDAHECp3g%2BA0aOFUnt6TC5FLgR2BRiIew0Nnf0HgWIzxRseCwGFuMeBRP7dUsQWImRMCkiO0YWgLFqNrCoAYKdvi8CYEnFxLDFGfPCFEOIQLmOQvqDexF/Qx2UDWGsO92ICnIBrBHJ9TgVnm0tVMARywZhpOoGBzkrAVOIBrDsPNwGEBXAzD8JFsI2olhjEi8UbIAgRd6Bl00RYowai9AFwIAY0xPBdD0Pzhw/QphDAlyr3Xhv5eRfmO0ZXfYah8%2BI9sCQCWOAYck8lzgtxMs2bsw5pzDGCsQFwB5srZGKtVdh2sY0oCxi89IHRyQgQMTJECBCSQTGzCSDXuxleqRXvCdIKJ8jGIV5cBXrx5IvGS/%2BGY/4JPK9Xdvdk/JxTlHYe1c03V7TaXwL6da4FRrpXTNsE4G0FgFYIRWaYNBdsXBkgYi4Ixtz%2BAiBc%2B87IPzOPpB46UKFwnIBuvRa7uNp3LupM4c4Kl3T4Fpoj7HxPqfrEZ9z8Y4V4r/f%2Bz8rMJVlvZ21P1b701nvNrUrEAG/cfN%2BIwGfLgCTGgc6VWSgQbN7SbNoMbfbJA6bWbebcbUgJbbMFbNbN7DbLbHbWgPbCjQ7Y7U7aTC7AXa7MLO7JSPYLA57BoMLaHT7ZAn7HYaTf7QHCjYHUHJQCHCgmHH/PgBHBQJHFHNHLAzHdfALTfWQfHMLXQbrAwIwUnFnGwNgnnGnNIOnDgBnAgcxYkZnKwVndnTnSBYEeAPnBodXPwIXVsc3EIVsa3ZYaXTIWXXIbXAoDwkoHINwqXNXfXDXM3Hw0XYIpoTXI3CoE3C3MI/ICIy3GIkYG3R3dYTYB3CrQTZ3JLBvd3UAu/cAh/WfefSRAPJfEgSkEPL/arGjUgSPLARIGPXPETEAQIWfJjCEGvCEVjSQdPWzSLU/GTTgJvJTVvdTLTHTPTFrIAkzMzDgEfbLcRCsfFCsR/JESYRfIPLzSLWQ7HeQoLeQbfAnaTXQYIA/WLbDY/PI9nc/LvIkVAQcJYuzFYtYjYoUDyIrf/UraowIQIWoiYv/ErHUWYn4sYVYytb9dY5Ib9TYggX9YgFgWzHrWA9yeAobEbFAijNA84GbObBwLAnAwQPAlAqgzATbbbZpUg87fYCgrg87PAS7PAWgt7egh7Jg%2B8V7aTNgr7c4Tgv7HJXg3gfgsHIQqHEQmreHISCQ5HVHOUGQtfA4iQBQ4LE45Q9o4ndQ0w8nbQmwmTPQ0mTgRkZ9HU8wnDSw7nfUvXE8Rw9wcIvQcXWItIvwrw5wxXAI43F0yIg3QYZwm030q3L09w2wBInXeIhYYMqXO3TIgLG4%2BvO4jgTZJE5YhQVY24GEjEeEwrQPZfP40Pb/VTCPTAKPZop3PPUTFIDEf4/wDjZjcTf4iEUvBMs/OTWwZvOolYWjEASQfwRPfwXjLjZISQZIVjZPLgYIV7QIW41ssPH/J3VzFskYtszstYYHLIZwSQIAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/roadrivore/skid.hpp)
- [unit test](../../../../tests/unit/roadrivore/skid.test.hpp)
