<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Plume`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-6">To Index</a></p>

## Description

`Typelivore::Plume` accepts a list of elements.
Its first layer accepts a list of containers and returns a function.
When invoked by an operation, the function places the elements into the containers via a process similar to pack expansion;
then, it collects every packed container and instantiates the operation with the collection.

Check out **Examples** for more information.

<pre><code>   Element
-> ...Container<sub><i>i</i></sub>...
-> Operation
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Container
-> Operation
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> ...Container<sub><i>i</i></sub>...
-> Operation
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;...&gt;</code></pre>

## Type Signature

```Haskell
Plume ::   typename... 
        -> template<typename...> class...
        -> template<template<typename...>class...>
```

## Structure

```C++
template<typename>
struct Plume
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;

        template<template<typename...> class>
        using UniRoad = RESULT;
    };
};
```

```C++
template<typename...>
struct Plume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;

        template<template<typename...> class>
        using UniRoad = RESULT;
    };
};
```

```C++
template<typename...>
struct Plume
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;

        template<template<typename...> class>
        using UniRoad = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::Plume`:

- We will pack `int` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will instantiate `Operation` with the results.

```C++
template<typename Element>
using ZeroStar  = Element;

template<typename Element>
using OneStar = Element*;

template<typename Element>
using TwoStars = Element**;

template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**>;

using Result = Plume<int>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<int*, float*, double*>;

using Result_1 = Plume<int, float, double>
::Road<OneStar>
::Road<Operation>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<int, float*, double**>;

using Result_2 = Plume<int, float, double>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::Plume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements>
struct Plume
{
    // Multiple Elements
    // Multiple Containers
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetics<Elements>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    // Multiple Elements
    // one Container
    template<template<typename...> class Cosmetic>
    struct ProtoRoad<Cosmetic>
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetic<Elements>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};

template<typename Element>
struct Plume<Element>
{
    // One Element
    // Multiple Containers
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetics<Element>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArACcpAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHASYLEkGGyYAzG4EAJ5JjKyYAHRX2PRsggr72CYaAILDxF4OANTK2ZjPLxMAHYrK8vuCvgB6SFfACyXlojm2mC%2BN02jAIDzBEOhcIRSPoXw8giYwWiWJeEK%2BGy2O3%2BBxp2yYuwZJzObCuF0eX2QBgUCk5HgUbEcyAeeye2PB70%2BBB%2BxFQRAASqgmOgvgCqcCLBqpVTqZsmSzDoa6ftDmzmByrtzeUx%2BV8APKnYjMjKPTX66UED7fAAimHqdE9Xu1Ia9EK8aSM1LZGr2fqdLrdAnNQpFeDF5rRd0xj05Hr2oMpEeBfv2xfDVMZZoZpuZ9ItpytlxtEp5fIFVxewGImHR9w9eqpUeCwC%2BKrV8cTAaDtHNPb7A8xBYlIBAx1OFfDZe3r3DuPhiLwyNRtwxFKpuIEKOJQZCxHDNYb5ufxs37NbXPbdod6cDmZDiW3q%2BnKygKsqqroGmqQZqYEo7iCurAfqb6Nmhr6Wucq7YB29oKEm0QpgwQERl8Mr%2BoGpLzsOEJhrRXqjjGH7ToRro1DBwoAfBbg5he%2BZtk8RZVnRQLlsJ%2B4MQatIvnWMnvlh1rfrhv5dhci79rm4qSihI7RuOk7qvsM5UcGBwacuamPOuH57ihu4SYCeoYXJRroYpX62p2gqwdx2nhkxBlQax4GKqghmcXBVkIY5DmVq8LlNp%2BZ7LkBFFgX82bnoIQH0ShuKOiEKW5geMJHgSt6yKSD6XhCiX1R5OF4fyPlcaK/l6ul8phYZyFakhIngvV9YKc22GCc1BHOkRHEIVJXWztRg0aiCy16WOsanKx03se6Bz/u1WWpRKOF2WRcUAstw3ye5Y1KV5%2BGchZWmkRGgUTsFxlfItZluM9F44TZbJnaJ4nxSh11uZhd2eT%2B3lXAdmYdSh729V9oWQWqkV%2BadsViXZAKQgAVCTpNk5ChOkwAKtgQhU6TFOvMTZMs4zTmAmYezBLyXhYPGbhoAwqxJHmc3sw1MPFRiQHvQAWtEqBdMQ4JfXxOWxQlI23clasEDL%2BlOiESusbrRME5rN3Qzr2V62L71UwA7orIwEarNsk%2BbLwS5%2Bp2vF1O3EZ7uJU5gwxfBol2vO9QheEkeSYOgSqh/i23JrNbjBAQpBfJnRPZ7nZsxeDqPJ4iIWZQcmdAeuEUHPLCpK9nhWYI3XyO87DTIzXUHmgHs1CeDkyigA%2Bvh0QEBAwzoOuCjnKP4puEnCj4tnMdx6kCdL/ijxzEHMIh2HXCRy80ex/HielwQw9cKnM17Rngh518VC0KqBBP%2BgSwRPQhcD8fJfL0RNfcuPhGyZ2zi/N%2B2dP5eG/vSHS3csYHGbkrauIBa5uD7ntP%2Bkk3j1BHmPRok8CDTxALPNg89zRbyAW0L4a9z7UKvkfCUu8NYvGDqHOUZh/4G3oRvC%2BgCr5mFvrtVMldBAQNfsyD%2BX8f6/09gA/Ew9hHowrg/LOz8pEaJgXAtBGD64dzIIbFuIxs7tyVl3dBPdkFp2wZ7IemZ55KCIVPGec97RUMvso1eZ9%2BGMOUTvCsHAFi0E4LEXgfgOBaFIKgTgbhrDWHIksFYKJzB7B4KQAgmhgkLAANZxEkBcDQkguBAj2BoWIGgzAADZqlmAABz1P0JwSQvAWASA0BoUgkTomxI4LwBQIAulZKicE0gcBYAwEQCAJYBAkheCzhQCAaAth0GiKEc4nBVD1OqQAWmqZIL4wBkDIC%2BFIC4ZheAJ0ICQPA082j8EECIMQ7ApAyEEIoFQ6hRmkF0G0B2rokicB4CEsJETskxM4I6BZ8y5SoCoF8bZeyDlHJOWcwpwiIAeFWfQZWaSuBzF4CMrQCwIBIBWUkNZZAlkUqpSAYAUgzB8DoBsYggyIARAhREYIDQjjAt4Ny5gxAjiOgiNoTADh%2BWkBWbmQqtA%2BU/KwBELwwA3BiFoIM7gvAsAsEMMAcQiq8B9gcHgAAbqHCFmBVASoWWsDJmcqgQtoHgCIrphUeCwBCn0eB2latIOa4gEQN4Bl1UYZ1RhskLBfkwYACgABqeBMAO2mpEjJjzhCiHEG89Nny1AQr%2BfoPVKAEmWH0C6wZkAFioBFhkTVuyp7GVMJYawZhekBuIHci1lb2gSpqC4Bg7hPAtH8AO6Y/QYhtDyOkAQYxWjJFSNOhgY7SgDAmFUXtnQRhNCHeMHtJqBBKx6GSGYq7bBbtnXoSYjRl2zAJYsZYqwJCgo4OE7pEK%2BmIp2fsw5xzTnnMxbgG5eLOYEqJZGhYCBMBqgGBAPJIBJB7AuPEPYQJJDFLMJIapnTYjVMSKEjgrTSDtPSRcapXBqn1PiPU8jsQSkJD2NUt9Py%2BkDKGZkyN4yplkpmTChZ5BKC0txRstgnAGgsFNUCXZTA8Ixi4PEC4XAilXPwEQDt9z3kZpeRIaQOalB5p%2BboJlAKmBAq1c%2B19PTeB9OhXMhZXx4VfDExJqTMnxxyYU0Ur4WLUA4uiBqTmZhCXsdGaS8lPnKW4v48s8LdKnOSbtEYOTXAuk0EROSSgnKfmCt5VK7LwrRXislX6mVGI5UKuiUqlVaraAaqlTqvVBqKtGo3eazV0SrU2o2FKh1%2BHonOtdbyj1axonet9RkgNQalAhoa2ODj0bY0JqTSmqV6bnlZp07IXN3zomGcLRGptVhS39YrbBmJNaBB1obQmA7La23RDU1207dgN3OAgK4C9bRAjHvHbkBdNQPvzvyBkG9p7nv7tqOendc6wc1EPSDidZ7ugA6vUe4oP270KGSY%2Bu9%2BGLPvs4I54g4nJPSYS25%2BTimNBecA6p/z6SgvEpyaQSD0GYinfw4R4j8nilAgSECMpkgMMHLaJZyF/TbBscZ6SrjSBZmwqi4J9ZmyOBiZRSwBQprTmmvc3SYYymgN3L0KtzNryNsfL09tnQIA9ikGM6ZkFzSX3guY1C3jcKEWq8OerzXXxtfyd13KbzvngN7D2Azjj3HFfUoEzF3FIBNdx2Hn74eAfR5E4OcytLbKMtcp5cK3LeeRVit7VKkrggysQsq6q9VmqMn1bDcN7VzWTWtctda5AtruuCEdT8/rbqjhDa9R2sbvAJvBs2DNiNIW%2BAGAW4m5NzYVuyDW6bjTW383W728YEtNhjvwCredhgmrISuJu5YVtVn22dpOwsGHGR%2B2DuyHOr7aOV0I6nf9qHv2geFG%2B2/y9664Oh6yOgBsOW68Ol6kOT%2BkBUwf%2Bt6t%2BWOry5mzuvSBOnuXw3uWuOuDYYcEANOJAdOoGwWJKEGUGWAbOz6nOIAZg8moesQlSJSnSoeQIFGTGqB4ugywy4GpA%2BSkgsQSGsQ9SNS8Qkg8QZSKGXANu%2BGewKBVmnAYGIWz6lybBch4uUuCwAaaQzgkgQAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/plume.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/plume.test.hpp)
