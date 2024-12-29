<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Flip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-flip">To Index</a></p>

## Description

`Roadrivore::Flip` accepts an operation and flips its *0*th layer and the *1*th layer.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer }
-> <i>1</i>st Layer { <i>0</i>th Layer }</code></pre>

## Type Signature

```Haskell
-- flip with Mold
Flip
 :: template<template<typename...> class...> class... 
 -> typename...
 -> template<template<typename...> class...>

-- flip with Page
Flip
 :: template<template<typename...> class...> class... 
 -> auto...
 -> template<template<typename...> class...>

-- flip with Road
Flip
 :: template<template<typename...> class...> class... 
 -> template<typename...> class...
 -> template<template<typename...> class...>

-- flip with Rail
Flip
 :: template<template<typename...> class...> class... 
 -> template<auto...> class...
 -> template<template<typename...> class...>

-- flip with Flow
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<typename...> class...> class...
 -> template<template<typename...> class...>

-- flip with Sail
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<auto...> class...> class...
 -> template<template<typename...> class...>

-- flip with Snow
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<typename...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Hail
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<auto...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Cool
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Calm
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Grit
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Will
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Glow
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Dawn
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Flip
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };

    template<auto...>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };

    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<typename...> class...> class...>
    alias Flow
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<auto...> class...> class...>
    alias Sail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will flip `Operation` and its member `Mold`.

```C++
/**** Operation ****/
template<template<typename...> class...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

/**** SupposedResult ****/
using SupposedResult = Operation<std::tuple>
::Mold<int, int*>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*>::Road<std::tuple>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Although there are many cases to consider, the implementation for each case is straightforward.
We will implement the one where the function flips the operation and its member `Mold`.

```C++
template<template<template<typename...> class...> class Operation>
struct Flip
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>
        ::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArGakAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0XEJCnUNTdmtQ109xaUDAJS2qF7EyOwcAPQAVFvbO7t722smGgCCm9sA1ACSLIn0bIJM1ec7hydn%2Bx/7r8dHxwSYNwM/xMAGY3P9AY9MKDwQDblCYQQAJ6JRisTAAOixoOw52QBgUCixGJxeIJCnOAHlUcRHukcb8hsQvA5zgAxWh4RK/EwAdisJ3OQvOEPhwLByNRzDYxOwd0YBAUDMFwqZLII52UxFQRAAsp50OdfsKjfzjSbhaKgdCJXDrYiUWiZdiQbj8UxCcTjsBiJgAQqla7zRbzl5UkZzgAlVBMQ2ggAiVJpdIEMO9vv9giJLuwwYtIBAVqh531tHQMLlmcVxIZIIFxxNfPjoPreaL4vBjulmKxlfuiuVDeFYeCwBLBqNIMTWp1qFL5bBfYDNaDdZ5vOba5Ov3en1231352wqlYt0wzwOO73Xx527MIOC%2BK8WEn4K8Z8HV4u1OiKYYF62b52xtWFIQ7SUnR7ElXTJD1s2g3MTjVVkf1pap13rE1gIdKV0RXRChyFZCNRnPUJz5KwNxbW9CJFO0EQlLs8KxY5iGAQMCJNEcI3nSdp21MiyzTNj4NrVsqK3H43h2c4hHfXJMHQSNMAULxaA1F5fm4sc5MSBSlJUtSNQTJNf3QsEhnQAsCHfehBwLecYWCAhSHOZyNjEmjD11TA6ioLwGAcdIAI2ID6PApjnQxVj2MHbSS18ph/MCp4TI5LkYVQv97JARywRi0TV1baSLmU1T1JC754rKoy%2BISvyAqC1MwWc1z3JxAto1jGFLOs2ybVzSSvy2c4ABUVI0y8kLqRxkAAfTg6ICAgXqQAUdEFsDNwavU1zdP0naCBxWZqO3E4OHmWhOFiXg/A4LRSFQTg3GsaxzgURZlnPcwQR4UgCE0C75gAaziSQMQ0AAOMwzAATlhrhYihyGuF5XlpCujhJF4FgJA0DRSDuh6no4XgFBAAmAfui7SDgWAYEQEBFgIRIvBcigIDQG46GiUJ0U4VRIYANgAWiFyRzmAZBkHOKQMTMXhFMIEg8Cs1p%2BEEEQxHYKQZEERQVHUanSF0VoAHdaUSTgeEu67bsBx7OEpNnWY1VAqHOQXRfFyXpdl8GzHOCAPG5%2BhiCNe8uFmXgqa0eYICQLnEh5sgOaTlOQGAKQEhodTonJiAIgdiJgnqJFrd4EvmGIJFKQibRMAcCvSC5/tKQYWhy%2BNrAIi8YA3DEWhye4XgsBYQxgHEbu8F9IKADcVIdzBVEbtnVj%2B5zKgdzkIlpGuPCwB2CGIPBcZH0gF%2BICIUkweMAQnzkjEB%2BYqAMdiADU8EwM2fzuv6NeEKIcQusAEGzUA7U2%2BgJ4oFepYfQeAIjk0gPMVAiRqjDxFpZBMphLDWDMMTS%2BJ8sBIIgPMOwjdqguAYO4TwzR/DUKmH0GIrRchpAEKMFoSQUhsIYIwko/RxiVAoR0YYjRaFjDaMIgQnQGh8JmOMURHC9ATFkcEXo/DmFkM%2BisCQtsOA3UJg7EmnthZiwllLGWctA4QFwMrcOP0o4x2fvMBAmBYz9FIaQUGkgQQYlhiCdGGhJBmEkELfGsQhaw30JwbGpBca/QxELLgQtIawxRkLWIkhEb%2BKFoY42JMyYU3%2Bs/WmDME5MxdmzcglB05hz5mwTg9QWBz15CLJgsEIxcFhhiLgENFb4CIEQvQACtbAOkKApQ4Dja6ASBbJgVsR56IMUTXgJNnYszZucd2JjvYS3dJ07pvSNBBxDsnMOEcQRmGjsU6m8dE6oFDtEapnMHlnP6PsrOCMCa53%2BMQAuRdjZVzLs3IFNc64NybufVuCp26dwdj3PuA9aBD2bmPB%2BqwHr4Fno4Bew8HrL1Xv8Zum9MYPR3nvJEB8MUxxPmfP6l9r5KDvuPIwj9QC3L4G/BQn9v6/2biMoBOtxmyDAUbB6MyoFPxwVYOBO8SEoLQekDBWCpzSrwQQ6IRDF7IMkU1PwEBXBKNaIENR0wBFcLyOkI1FqeFyPNeQvVMixFZE4Q66oTq7XMNsIo8RrrRGet0QsJYOio7RP0fbfJnAdlmI6WOLpPSIZB1sYMi5jiblxxcW4rAMRPGY1ifE7pQTeSxFhmjEEwTQlZLycTTghTKYlLpozZmrtnm1N5vzDgTSfYsAUHPGWc943WiGP0uxqthmyFGUKvW8hJlip0CAEEpA5kLJtmG5ZRinaVLdh7VQ3be39sHVCIYJzXkpwuSCa5scablLbanGpp6w4gD7XpOaA7YZzSHQQOau7xl0F%2Bf84upca4gqA7XeuFDm7QsELCrumLMC937oPYef00WsupaQLFwjcVLxXsgNexLBBb2NuSsuVKj60ubgym%2BzKH6jhKa/JgH8v4/ylPyidgqJDCv1rOiBC7JXGFgTYOV8AFXoM4GsXqarLD4NWYQ1W2rPFuvSFQmhLr6HoADSw7h1RrWsOqJp3V7qfVqcEe0aR/rTVMOUcZuhCjJiWY0YGj6wadZLIjTWjgns919vOG%2BjEn6k0DJIKmy9zjSCuPcTmvR%2BaQBwwxCCEEsQkZZPxgl3kKTq2rNrbYIpV7ZggxAJIWIfjUa8nxpDSQCMuDQzMLkzGIJ3NZdJumoGYaFaZcds1vL8xL6pGcJIIAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/flip/implementation.hpp)
- [Source code](../../../../conceptrodon/roadrivore/flip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/roadrivore/flip.test.hpp)
