<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateFilter`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-filter">To Index</a></p>

## Description

`Pagelivore::CognateFilter` accepts an operation. Its first layer accepts a list of predicates and returns a function.
When invoked, the function removes every argument that satisfies all of the predicates from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? (nothing) : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? (nothing) : Arg<sub>1</sub>,
                            &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? (nothing) : Arg<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateFilter ::   template<auto...> class...
                -> template<auto...> class...
                -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateFilter
{
    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will remove every variable divisible by two and three from the list `1, 12, 2, 6, 15` and instiate `Operation` with the variables left.

```C++
template<auto I>
struct DivisibleByTwo
{
    static constexpr bool value
    {I % 2 == 0};
};

template<auto I>
struct DivisibleByThree
{
    static constexpr bool value
    {I % 3 == 0};
};

template<auto...>
struct Operation;

template<auto...Args>
using Metafunction = CognateFilter<Operation>
::Rail<DivisibleByTwo, DivisibleByThree>
::Page<Args...>;

using SupposedResult = Operation<1, 2, 15>;

using Result = Metafunction<1, 12, 2, 6, 15>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`CognateFilter` is implemented based on `Pagelivore::Sieve`.
It transfers the result of `Pagelivore::Sieve` to the given operation.
We will use the following function to send the result.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
```

Here is the entire implementation:

```C++
template<template<auto...> class Operation>
struct CognateFilter
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Send
        <
            typename Sieve<Predicates...>
            ::template Page<Variables...>
        >
        ::template Rail<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgGykrgAyeAyYAHI%2BAEaYxBIAzIEADqgKhE4MHt6%2BAaSp6Y4CoeFRLLHxXEm2mPZFDEIETMQE2T5%2BXIF2mA6Zjc0EJZExcYldTS1tuZ22E4Nhw%2BWjVf4AlLaoXsTI7BzmCWHI3lgA1CYJbl6OtIQAnufYJhoAgvuHx5hnF8gKBOhYVAeT1eZgODCOXlO5zcBFuyUwAH0CMQmIQFECXsCAPQAKjxOJOQkwAEcvAw8AA3EjsEAAFTheFEtGUTF%2Bn3xOKxwIImBYyQMPOhsPhzDYADoJRjnr9iF4HCd6clGWIWWyzgB2KzqgAi5ysmJeWKxJwsrM%2BbjNIGB3N5/KYgouwsYrE%2BLOQAGtMOgiaTGDspTK5QQFQymaqHW43Z7vSSvH7MFKTJrgSdUycvOkjCcnV9tSco16fXHwQmEvrXjq9dbDcaAEo9LbpCnmy3V548vkChOYi4ptMdu0RphXVASsUPE5HVkKQmx%2BPPUh91MDrvQ4dEMcTqcKGdF%2BM2JcndejiUANWaeCY0Xo0tIZxeaaPI7H5%2BIl%2BvmAsCkXD/7cOd4oSgA8gQCBxOiPaPC8gbyoqyrMqyEZ7iWrwXK%2B743gom4JNgd7ITsVhoReV70F%2B2G4ScIFgcQWGSjh1rJr%2BqYZmEwDZv%2BuYhkqYaId2zyPtCh6PvhmCoW46EkaJtFineEkfmRdG4UJaZUeBm5MV82AgCATpVpilZlm2K72nxgkacZEZOqKmB3se5GTgYO6zr6KE/vx/a2qujr/tZtnPopDnTs5xYEW5j5WS6CoLoeEVsAqB4aXZZ7ER%2Bt73u5qZJWKcmkd%2BMU%2BS6Y6qTR1r0dByJBlx8HhqWbgiWJtILicOVSeReFziWhFuLSNjNSluVtZRoFqYpDHlo%2BLFZjm5x5nBPFsoeZkZY%2BwXztCjV3r89qMgioi/OtqHYBALXSqsY6bU0jjILtiEHQ8x39Z%2BChnYpYUramxXSYtOHabphn6bq/2vIaHKEggVwEPQJwclyLwWbVWUBhV8pCODBCQ6W5bYqDQh4JgzbQ/isPtp5JlCqTQ7%2BeOOGBTuY7KMQXrKjy6JldKyPBrj%2BOmYxy3w2uI59W%2BklSo%2BMHBtqmBNHQ6UCZq6aZmx00JHmqMQ/Qgn0WWGqA1j5kUwjgstaLaaM6SeCMzOEAMKgwYQJuZj%2BOY/gM0zogs9Cxs/SAFJiHGqyrIe4snJL0u0J7j0m6mSYWArrHsfCnFq%2BjGtEcLH5AtrSa6224UGwLG7Jen9Cs1By2TWxLLAJ8M1VfNgoaUKBVxaHqLh2nGGYKXv3/uRPfwnpFY5wazy4vis4MOghN4sT/PeSKhWjeVsoo64GpasPwMk52ZOOvnFyIzT267h1Ox%2BYX2WPaXwLB0Sk/QiJEfF135GJrzec75Z%2B8WlTW6OTOQF4QonqFHE4wdW50EWu/d6ccpocVroAuI20BBP07l9LW400zZ0HjFb%2Bc8f4Xz/tOMczxgCM15IwAg18NIVxOLWNunEIHtzcKQ8hbBBDoK0jpf8OCDJ61HqDDwwBmA8gAGJ0B5MQaenIbSf1qvgw%2B2BaYAKAcghgSMV7BiESIzA4jaCSLGrguR5NjEH1/kff%2B9NGb4Hdl3UBwcGa21QPQyBjdoHvQUVTFq1DloTUVvmJg1ck6uGUtHXsGkYEJwAp8LmzZoSuxsSZThoSVq/QNgE6uqDJLJIiVgtmkS0lyLoW3aEiDgGZEzpg6OfDc4eVMTCb%2BijlEkLIZgChHDQG0JcbQTijiiDdOhKwtp7CqGvyBtg8ZIMOTTOmcTMeeIFRdyodIuZMy1kzzbG8cEHwviXGuHcRMUyFnakpHgdI8lbi0gAO6oBWbIwchsiAnAAJIaMqicikZy8AXOuagQxGktpXUnAINkqhkhSOiKgTwJxfbeD4nLCwzyzhmAAKwnDMLmWuGgJlYxqSPeZBIPlfJ%2BQgchdy4aNMFq8tm4DTnnNIpc0lbT/nLUBYyYFDBQXgpOJC6FsK4xQMRcitFCRMUqxONivFQ8cFHIJGUtR5Lt4PILieamZdg7ypAZMgR49sCqFYPydkRMjKUovs8YgwAfG0IALJSyYFQMkvQBCcW0SZPRBiLiaoqWzbSAyLhEvpZ%2BS5Ny7wBu%2BQy2kTLSxl20lXWq5rLVjP4bQoQXhkgFC9PWBQXh9GcS9Sgi4XA7xmDvFwFFlS2xdK7jm4MtdbVNAdeCLVbgi0nC4CW9Fd5AhtvLRgtsbLrrTjiAQCAvx0DaQUC6BErJoRZprXhNNGb0Bzv0Q8QOZYODrFoJwFFvA/AcC0KQVAnA3DWGsGAzY2wa6gh4KQAgmhN3rHdCAFFZgxTqjMJIAAHF%2BlFGgACcr6ND%2BC/QkfQnBJC8BYBIDQGhSD7sPcejgvAFAgDg/eg9m7SBwFgDARAIBNgEGSFccglA0B8joHECILpOCqC/f4AAtP4SQJxgDIGQG2yQYozC8CZkQN846i38EECIMQ7ApAyEEIoFQ6hMOkF0EWq5KJkicB4Funde6H1Hs4EBK4xHgyoCoCcOjjHmOsfY5x7jJwIAeAo/QKR%2BwuCrF4BhrQ6wIBIHI0qezpGIBeco/EYAUgS00H0eBSg0QtPRDCM0W4qneDReYMQW4QFojaB6Bh295GRlAQYLQOLcmsDRC8MAC0tBaCoe4LwLALBDDAHEIVi2GXKRdy05gVQDYeTxfIIIWoWmbjRBRMljwWAtPIjwNBqrpBmzEEhUoSWtWjA3CMA%2B9YVADCWtPHjK5iD923uE8IJk4npAHek2oLTCn9B1ZQGeyw%2BhvmocgOsVAyR6iVYY2OmaphLDWDMIhmbAnWtPZqHUTILhJ5TA6EESeQwygVD0AUDIAhIcI7SEjhgsORiVBB81gQ/RJieHaHoboTqGhzEx0sbHW0Cc5Ch9T%2BYpQscSHWAoS9OxmfgY4Lu%2BDWmkPGfo0xljbGONSCsxAXAhASDIoSE5lzq31hgSYFgeIEAn0gEkAkMU/6EjqkkBoSQn7/CwZRf4f9nPIOkGgzLsU/hOhfv/V%2BzoKLJBlu14EBDvAkMobQ3e1b2G8MeYI3pkjFA/OoDs1RmjHBmgsApOqBjTBApZi4P%2BsUXAxSHr4yQPAgnJOHbExIE7sgzuycPboEtSmmAqaq%2Bprnmm5NId00Rq4JxDNHmILH%2BPiepzJ9T%2BnjQ1nbPebiNLswznfeYfc558Pw%2ByCh/8/ZkAMe48MZ70F/9XA4OhckahiAkW5OJdi91w/yXUvpYcN17LlDcv5a00VkrZWKvdZq3Vhrh78CM16M2SrmeOvICuLsLemEDyNunJgNkNrcCNrsIeuNpNrejNnNpgAtq/qxH7utoEgoFtpgDtiKN1gdqJuIBJqdkoOdnJuXlditt9lYHdgNo9qrkeq9pkO9p9irFQb9v9nEIDnQSzrULjn4BAK4CjkWiEAsHDssPkGjvUEIRIYUJkBTvDkWiTvUPjq0ITtMDjqTiofIeIfTtIfTtoZUCzmzuJrXtzh7tphwO3p3gnknmxCnmnhntZhLvxtLrLhPm5grpgErqMPQaARblbqnvruqCiv%2BuqOqAkAbpIMxkWuYV7rYD7q5lhjhvhoRvpr5gvpHmwJwDHmZiwAoBSBxhSPYV2L8LxvgPxjnnoPgUdoXnniXhdiAGBpXtXmppzmYbzjpsHgZkZjkSxnkQUTCsUUknbEPgFtLgkOPokVPigDPgFukbMYvgUemgiEUf%2BgiCUQQNOh3sxnwBIuFnvlFjFslsfkcSlmlhlpfuHjlnlgVu/pgMVqVmIE/lNi/kttAdVk1l/q1nJu1p1oAbwMAX1mAd8hAVAWNm%2BHAbwAgWkEgbyCgStpPnwBtpgdtrtngbIAQcdnUSQaXjoI0RQcYLdjYLQfAM9owSCpwFiGOjdj9pYH9p7gDjnkDvQUoWDgIRDmoVDiIYzpTqjrIcjpyXyejgYcTrwZoXMHoWKcoeTqIUzooRKYKfKQMCKU5hsFsOzqqaAe0Q3pwFYbkfkYUUMSzHbM4VLo5pMfLqQIrsrpQLXv4SAGYKngkAkCin%2Bi7rBs6eqCBjzjqchvEehpac%2BpIOqNxsEVwFIP%2BkEdrlwOqJzgkPXohpwHLpPrXjxj6YmX6VMesDNukM4JIEAA)

## Links

- [source code](../../../../conceptrodon/descend/descend/pagelivore/cognate_filter.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_filter.test.hpp)
