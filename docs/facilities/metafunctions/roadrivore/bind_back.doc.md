<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::BindBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-bind-back">To Index</a></p>

## Description

`Roadrivore::BindBack` accepts an operation.
Its first layer accepts a list of containers and returns a function.
When invoked, the function adds the containers to the end of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Cons...
-> Args...
-> Oper&lt;Args..., Cons...&gt;</code></pre>

## Type Signature

```Haskell
BindBack
 :: template<template<typename...> class...> class... 
 -> template<typename...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct BindBack
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will bind `Con_0, Con_1` to the back of `Operation`.

```C++
/**** Dummy Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** Operation ****/
template<template<typename...> class...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Con_2, Con_3, Con_0, Con_1>;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = BindBack<Operation>
::Road<Con_0, Con_1>
::Road<Args...>;

/**** Result ****/
using Result = Metafunction<Con_2, Con_3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<template<typename...> class...> class Operation>
struct BindBack
{
    template<template<typename...> class...Endings>
    struct ProtoRoad
    {
        template<template<typename...> class...Containers>
        using Road = Operation<Containers..., Endings...>;
    };

    template<template<typename...> class...Endings>
    using Road = ProtoRoad<Endings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArADspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJgAzG4AUCnpgwRDAXdobCCABPJKMViYAB02LB2AuyAMCgU2MxuPxhIUFwA8mjiE8Mri/sNiF4HBcLMF0BYmMgANZ/EzxKynC6ii6QhEg8ES4Ew6Wo9FsElkglMIkk7AMfBGBSMkVi5msggXZTEVBEABKqCY6D%2BYouguFJ3t9pliOl8NlSIVzCVONBeNV6uxHkewWiuoDdpdoq8aSMFytNodoIAItTafSBLDQ/Vw8RidjSBdNdrgIXSVHQU77YLU2CndHRW6pXCoa2UWjfVj/YGKRqtcFy3rnWK40PE9b0Cn06bzagk7bwaWhxXGdWBfF6xvTn8Pl89j99yXVKw7pgXoc9wfvgLd2ZQcECV4sCm3GgGKskgRI9g72ddguVMfBYZELhOYhgB8Rgf0vbYfhbOUIR9DFlSjU5DTZUMAH0NAbf9EO9LtUN7JkCBZLCBGwrh8N3U5CPlYi/UrP8MPIo0LhwsxaN%2BejPXdZCmJ7FiyIo40cNBHjr0uGloizBg4M2BD%2BI7FSkM7RVhJVftSLYsSMzkmopPeQChC8JI8kwdALUwBQvFoY1Xj%2BccEzMizUismy7IcmcDLpIzwS44sJOCqiNFChhqPXRsTMuABZTB6ioLxP2eJy%2BPbdS1KIzS0L7NUKwg4d0JOFzgAuBKkpShwMl8jktW5PlYVk/yGRKkAQEXHMwoiqL2s6qdYSKtcqxigDLi8%2BzHKvU4ysTWypt8yqmGS1K2rcILOKoyTRv/Y8ABVbOm%2BCyPpZBsIK6ICAgYZ0A6hQMQuyM3EmhzizcyzrIWhzcTmYyTg4BZaE4WJeD8DgtFIVBODcaxrAuBQlhWC9zFBHhSAITRAYWXk4kkTENAADjMMwAE5Sa4WIicJrh4niaRgY4SReBYCQNHC8HIehjheAUEBwsxiHAdIOBYBgRAQCWAgki8AhyEoNBbjoaJQgxThVEJgA2ABaTXJAuYBkGQC4pExMxeCswgSDwO62n4QQRDEdgpBkQRFBUdQhdIXQ2gAdzpJJOB4IGQbBrGoc4KlZZl41UCoC4NZ1vWDaNk38bMC4IA8JX6GIB0Hy4OZeEFrQFggJBFaSZWyAoCBK%2BrkBgCkMw%2BDoAEC0oCJw4iYIGmRIPeB75hiGRKkIm0TAHAH0hFYeAgqQYWh%2B69rAIi8YA3DEWg%2Be4XgsBYQxgHEFe8GISfHAAN1s8PMFUSfZbWdHggBRnIdoPAIjpEePCwcPyLwVmu9SBX2IBEDyqZASH3fkYLGCwqAGHLAANTwJgX2slwbo3tsIUQ4gXZYPdmocOPt9CHxQHDSw%2BgP580gAsVA34Mg721rdMEqZTCWGsGYLmIDiA22vjQ9o58MguC1GMVopBAjhhmAMNoeR0gCFEbkVIciGDTH6DECYVRBECC6KMTwLQ9B2C0bUEYPRJFqIMSYhREwTGqNKNIhYiNlirAkCHDgoNSCc14NzBOWtdb60NsbU2GcIC4CtnnVGhdi6wIWAgTANoBgQBxiASQoJMSk1BPTDQkgzCSE1uzWImtSb6E4MzUgrM0aYk1lwTWhNSY001rESQlN0maw8eHbmvN%2BYY1gSLcW5dJbR1lvLOuqAc4qzVhwBoLAL7xG1kwckh8Tak0xFwAmFt8BEB4bbV22CnYSGkPgpQhCva6Bbv7Jggdd6uPcZ4iOHAo7S1lhcOOPik761VAmLgyzVkaEztnKuud86gjMEXbpQsy4V1GQC6Iwz665xQAYIwXyuDhRoA5CMndu69xHtPIefcx4TynkA2eMEF5L3Dqvdem9aDb2nvvKBaxIb4DPjVK%2BO9Ia33vgCaez8qjh3fp/PuP9GXFx4YA9GICwFKAgQfIw0DQDgr4AghQyDUHoOnlgx2uCDmyAIZ7SGpySEwLYVYChArqGJKhvQgQjDmFphNRwrh0Qtl8MtYYmqzgICuCseIrUtjZgyKUTUH1siaj%2BukQIj1xjug%2BvdTUHRpjijmOsTGvR4xbA2LMXY9RDikbOMLsUtxYcvbeMTn4hZnzvkE0zqEzZQLIlgtLjEuJWAYiWsZqU8pyysnxFiKTOmoJsm5KaW0ktnBOkCx6aLCWUsY6wqhdXVWbBOBTOTiwBQF9jYXy%2BZiWUwx1lhJtnoTVODnY6rdkc/VOgQCglIOcy5wdC03PaZHQZsd46qDXRurdO693GizguwFqNQSgpLsLfpcKYW10gzETdFlsLbtJthP92FP0HLbhiiAXcvZ4pxUA3Do9x7n2niSwQZLl5MswGvDeW8d7o3pXKkVpBmWCLZTfO%2ByAH48sEHyr2Aqv7ImFX/MV09JXgMgXKocPT4FMCQSgtBXYNWyC1WenZeqiE3qNcYchNhzXwFodahgO91i3TIewywnCvHcN4Rahxmio3CPcGmsREik3ZsUfkDIIag0ZHDeoyN8bLHOYMfZwLUws0Bozam7IYjJiND8y4xYTjnbXOLVzTgCcv2bouIh3d0Jhg1o2SQetoHomkFifEttrjO0gDJpiUEoJYhUyaezBr8QamjvSzzWwXSwNzCSZIWIaTabxHZoTSQFMuDEzMK0xmoI0tePHY27GhbzadcW91vrCwQFpGcJIIAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/bind_back/implementation.hpp)
- [Source code](../../../../conceptrodon/roadrivore/bind_back.hpp)
- [Unit test](../../../../tests/unit/metafunctions/roadrivore/bind_back.test.hpp)
