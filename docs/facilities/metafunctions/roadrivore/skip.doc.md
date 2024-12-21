<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Skip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-skip">To Index</a></p>

## Description

`Roadrivore::Skip` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer {...Last Layer {***}}}
-> <i>1</i>st Layer {...Last Layer { <i>0</i>th Layer {***}}}</code></pre>

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
template<template<template<typename...> class...> class>
struct Skip
{
    struct Commit
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
    alias Cool = RECURSION;

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

using Result = Metafunction<void>::Page<0>::Commit::Road<std::tuple>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Skip` relies on a helper function called `LoadSkip` to keep a record of user inputs.
The record will be passed to `Omennivore::Press` to invoke the previously provided operation.

We will implement `Skip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Page`.

```C++
template<typename...>
struct Capsule;

template<auto...>
struct Shuttle;

// We will use `Items` to keep track of user inputs.
template<template<template<typename...> class...> class Operation, typename...Items>
struct LoadSkip
{
// If `Mold` is selected, user inputs will be kept
// in a `Capsule` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkip`,
// waiting for more inputs.
    template<typename...Elements>
    using Mold = LoadSkip<Operation, Items..., Capsule<Elements...>>;

// If `Page` is selected, user inputs will be kept
// in a `Shuttle` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkip`,
// waiting for more inputs.
    template<auto...Variables>
    using Page = LoadSkip<Operation, Items..., Shuttle<Variables...>>;

    struct Commit
    {
        template<template<typename...> class...Containers>
// When finally initiating the operation, we invoke the skipped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
        using Road = Press<Operation<Containers...>>::template Mold<Items...>;
    };

};

template<template<template<typename...> class...> class Operation>
struct Skip: public LoadSkip<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEoEAHKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHASYLGkGeyaBbgQAnmmMrJgA1ADyV8RMTSfYJhoAgpPEXg63ymImAUCg%2BnxMAHYrF9brDbnsDkdMCczpdrmwAHRYt5guG3H5/Ai3AAimFadFukKsEOJJ2h4K%2BAHpGbcLEwlLdREoQGDcXCEYcXsiYXCUXy8bCBUiURcrsxMdjAthOQYQbcPIImBEEqQwczbgAVBAJO54BS3AS0c4WyK3NJtG57Yh2pjIADWt3oVAIGPFEtl6MwWIxGr2glBIthOMj%2BIIv3%2BpPJtBRoa1kWIKdkjAICmDOKVfqpepZAHVTQwAG6oN13AjGzkkIEKDIMfBGeH7QV7W5sKoJC1UeH11BPF45Yu3ADuhAQQ7umFUcdde3QLvdvpjeK8WXbAcpgWJD1HTRAIClQtuAFlPOhM4Js7nFe9AhZKTHIbSX7yY%2Bfju/Tn6eK/sipxMF4RB5kqKrsuaQiYAAjl4jDbLqm5wmBEFYqGD6FgWMYEgmZJasmpxwYhyEgW42HhpBz7vO%2BUK3NuETAPCaL7oejwJGOzhnp2SIAkwwCUdROa0XSlI0nS36fPqABKmDIJsWQVncXLsDJQH8UKuFuIB/LaccpwBvKQZPtBaqptqZATmW%2BKYPazzdnWdw0MQkwus8bBOmuHpUMQqAsHOFoue5G6fBK/JoqZwaiQoqERZFbFyjcwb3KFEaJVGeFZbG8ZEomxF3uS6bFQ%2BtGkA8GXiQx9JJUxO6sXuJyHoCwKZfVYpMqW5ZVjWwVoMQTYtm2TWGXcvbVAOwUjtxrzdVOM7BQuS4OJgq72uuE5GowlWTnc9pqi5txNl4tBErEroekQAJNua/DOlQmyhbcERVqITS5vpkUmTcR5zTkp7AVeN5lTRT7ffu9GySycgMNu62%2BeabR3ECyDnMg9Crg9txPe0xrOm9qAfTkX1obCQPjSSRF0Ci6UE4%2BvpKkDaLSQxn70n6wG6ZD3OgeBqC0RZsEIUhDAoZDGGC1hWbhgl9W/QqGL0wkHWijleIEQVNMkW4ZFi9sYNiU%2BlUq2FEO1ZDzG7uxLW3e1MrRX9XFOYDfGIheyhCSJsvG0zdGQ5THvdoVtOnGbjNvCzVxs7lH6x3iXPjY7KVK58wBAvsOEa3C1usdetCrnboe6%2BnmdsOD/vRyBnNSV%2BXxgnzqKp2Z/tglr6pMGkChnTXMlN1LNXfHGhK3EICDgQQ9Cx7ZdzTrQtANXcJgAGwaAAkgioJr/CqC3DWDnws87rTQjhMMGk4Fk58Te38nxlO0rbzC0LmMwf9rsCJViut5v%2BygjlDuoRUBMHQEIN0eA0i8ihBOdeg5V4aALreHeZp7KNHWpVM%2Br0L5X0WgvW48R94OQIBOCItwmCUjXm4LuPdp470MBtAw2xVwvGWq2aaCC/4sC%2BmvbaxoGB7QOu/Y6K1XCI04VvBBBCrq70oRoYBoDwGQIQQlfUk4tSOHbDjFgJByyXzEknYOlEf7BmwPQCuOZoy5TziDQuHFbgKLARAqB4djw5EqlwxmlVqHd17iiMxWdK75mfJzBacC5Fe2ElI1BdhFIrkwUoc%2B%2BjzTz0XoQmsaQSELTIRQhB49J50I0OQ9hgpmHkKJCI9hqB4Fr08b6XhC0doCKnEIo69ZRGtnEbUyRO9LonxuggxxSioFr1USydR2QtEkB7Lo7ByTwpaSMSiQeWIABqbQ8BMFiPQAB0MtyNUEsJexQznF0zcV/W4dSsSVXyQQKelF1nEE2ds4E4kCz1wZLlDuHgWAsEIIWGB5MOxLOMvfZugZX6qkZlZdMuzbL8NxhEMQVpsHZDHLuYc5zmn7WwX1Ws9YFDOKuKuAw5wEjhX1E0wRLo2nlnmIITZK4LRYuKauLBERkkThuvcCuDA8BViBKeNqaocZ4xekTEmAhr71RsXJEBRcDz2xBGcgGAhipplVm87AQcux3CQSiK5bcPmJzrqE8Epr%2B5grviC8FMVzJvxBJC9%2BLseIMCsR3YZIA7ReG2XgZADj5XDJVZ/N1UEiwWobkyAAVDG2NcbGR6ljQabAQgDSxoTdGuNWaM2fPMIECImMvBYH3G4cCdBCDnCsY3K1VrH6t2fg6yOgCR7/BdfNc1r5DG6pThCi2XyW1EkBKgIg%2BrLZAoHgLIe9UO5DqIJE5eMCI2fIVmClZGIy6YECZYnOkUbHzvsbO1A86UQbq3U2kJAKOaaQMjakxWJT0WLhTGGxSCD0BRHaDU4D7yoQw%2BfHP9XwbFCC8GkYo60FK0KJHbNt45TiTHQEDED08cqnn1acKseBbwoZAMe04Gh8xmtvnW4MnxiDACfZ8F9REnriyaPYoNrjVWhu1SANDbhSPkbeWa2VwIzpQcVZeajXhaOwbcBhrDLHcNuHw8zEAPy/kEFPHK0BKJ4OIcOCBC9kbh5jmQAAfRggkAgEA1MgAUDcAzAC3AQb4zckDYH0A2fOm8FYdIOBrFoJwfwvA/AcC0KQVAnA9KWGsPiDYWxl5mECDwUgim/PubWG6AIkgMQaEkFwCEgQND%2BA0GYFeK8zDJFSJ5jgkheAsAkBoDQpBfP%2BcCxwXgCgQDVbi1oNYcBYAwEQCADYBB9HkEoGgA4dAEhRBuJwVQyQV4AFoV6SFuMAZA/qpAYjMLwdahASCYb0PwQQIgxDsCkDIQQigVDqHi6QXQXBSCTmeGkTgPAPNeZ85oXg9X7jgX0dNSbM25sLaW7cFbZhbgQB%2BWkEbzo81cBWLwVr7nSAQCQEN8H9AyAUAgMjiHIBgBSDMHwOgTomsQFiK90gsQkXEHOA93g5PmCU/uLEbQcTqekCGxY%2B4DArSk6wLELwwBqELya9wXgWAWCGGAOIC7%2BA0aOFUkL/zC5FLgR2DFiIewSv%2BdoHgWIzxKceCwKTuMeAKvC9IKpYgsRMiYFJGLowWujCvbWFQAw5HVl4EwJOLivmYu7eEKIcQR3fenbUKTq7%2BhxcoGsNYfQ2umuQDWCOT6nBpvwZaqYELlgzB1fN08rAceIBrFiQ4QGEBXAzD8NdsI2olhjGu8UbIAhy96Hr00RYowai9Dif0KYHRPBdD0EXpoAx2ht77B3%2BY0w%2B8FGuxPoY1f28SEL%2BF7Yi/9DPZq6T%2Brtwfuzfm4t5bKXgcQFwJtyHUXoew8d2sY0oCxgF9IElyQgQMQAE5AgQkkGlswkg17ZZXi/tfUrcrEAaLDEFeLgFeZIF/ZICA/wdLfwN/FeDfC7erRrZrWLR3BHLrRHHrT7cCAbDHQKFHUbcbDgNoFgCsCEabChN%2BdsLgF/DELgVLdbfAIgXPHbWQfbAPaQIPJQEPC7XQPHW7LuanJ7DgbzZAurTgD7PrcCaacgyg6g6COghgpgopUHIgiHSkKLMwGHDA%2BLdrJHTQ1HAgzHVHEABQqg2gnHF/LgarGgc6VWSgEnC7WnNoKnU3Nw%2BnRnZnU3NnbMDnLnKXTAXnfnZFIXGLUXcXSXfzaXLvOXUnRXJSPYFnNXBoUnLXHXdw/XHYfzI3E3GLc3S3JQG3aIliTA53ISBQN3D3L3FnX3Lgw7Hg2QYPc7fzQQ8PB3dPKwSwGPWIfPBPTJUmZPVPA8bo6wLPN7HPTDYEeAQvBoLvZwUvVsJvSvVsUfZYOvTIBvXIKfCvdIbY1vefMfAfBY4vAQYfXvfIfYwfbvBYY4zY2wHvVYp4%2B4ioBfaHdYTYFfT4krCQ2rN7TgchYgCgqgmggwFQxg1LEHE/Ng7Q6LPQuHFYa/TAW/RIe/ErMrUgCrQIBgtLCEBAiETLSQb/Oba7AEgLTgNAlrTAjrbrXrfrdHMwkgtgTgcgv7bhCsf1CsegjEJESYFg0/bba7Bo/3Jo47eQPgtonQEAm7O7UQwA/4zfaQvAokapYElgDkhQLk24Hkhg/kokDQ4bVHeEwIRE2kow40nUJk4wsYLk0DPTPUvTA0gzEEubfHRw9yZw0nLwjwmLX0hnJnBwFnfwwQQIjw2IkIvnAXWgCIkXfYaI3IkXPAGXflWYi7JI5XVI%2B8DXXgTI3Xc4HIw3J5Ao3gIoq3Uou3cogwvgF3ao93T3OUeozgsUiQZok7KU0PWUiE4wKPXozIgYgLIYqVTgRkNTcYzPbPBIXPWY%2BPTvc4vwZY9wPYvQKvd4k4rYkoHIF4lvHIDY2vecofZ4lcmfM4o8t4kYDc14yfa4gfHvfcmoJfb4w7MQpUlAoE9k%2BbTk7k3kg0mE1g6ZKHc0gwlEtEygMQrEirMwBgwIQIfwHLdLKrWCiESAyQwEhrWwdApExLEASQfwV/fwZIPLF/SQF/TLd/WoQAwIF7d8jC7CwAtbNCykuiq/M3VWQGSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/roadrivore/skip.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/skip.test.hpp)
