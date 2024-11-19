<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ClassicPlume`

## Description

`Typelivore::ClassicPlume` accepts a list of elements.
Its first layer accepts a list of containers and returns a function.
When invoked by an operation, the function places the elements into containers via a process similar to pack expansion;
then, it collects the type result of each packed container and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   Element
-> ...Container<sub><i>i</i></sub>...
-> Operation
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;::type...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Container
-> Operation
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> ...Container<sub><i>i</i></sub>...
-> Operation
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>

## Type Signature

```Haskell
ClassicPlume ::   typename... 
               -> template<typename...> class...
               -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct ClassicPlume
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
struct ClassicPlume
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
struct ClassicPlume
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

We will see three examples that present different use cases of `Typelivore::ClassicPlume`:

- We will pack `int` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
template<typename Element>
struct ZeroStar { using type = Element; };

template<typename Element>
struct OneStar { using type = Element*; };

template<typename Element>
struct TwoStars { using type = Element**; };

template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**>;

using Result = ClassicPlume<int>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<int*, float*, double*>;

using Result_1 = ClassicPlume<int, float, double>
::Road<OneStar>
::Road<Operation>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<int, float*, double**>;

using Result_2 = ClassicPlume<int, float, double>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::ClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements>
struct ClassicPlume
{
    // Multiple Elements
    // Multiple Containers
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Elements>::type...>;
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
            using type = Operation<typename Cosmetic<Elements>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};

template<typename Element>
struct ClassicPlume<Element>
{
    // One Element
    // Multiple Containers
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Element>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIACcAOykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyb%2BbgQAnumMrJgAdPfY9GyCCifYJhoAgpPEXg4A1G4DApsshlAVMB9PiYUlYvv8Ef8APRI/4AWS8tEch0w/0e%2B0YBFe8MRKPRmOx9EBsiYEQSxM%2BiP%2BewOR0hpxZhyYxw5l2ubHutze/2QwIUgo8CjYjmQr387xJCJ%2BfwI/2UxFQRAASqgmOh/lCmTCLAbFUzmfsuTyzpa2ScznzmAL7sLRUwQf8APJXYjc3JvQ3mpUEX4AgAimFadEDQeNMaDiK82SMzL5Bv8Ya9Pr9AntFyuTtxkuleFl9vxzyJbxAIHzdxd8pOcMZCZhYabUPjTM5do5tu57IdBZugtdYsFn2AxEwBJeAbNTKTEWA/x1evTmYjUdo9sn09nRNH8prdY7ZrbZ%2BhZrJGKxeBxeKehIZTLJAiLNLpxHjPYHef71p1oWR7YCKYrUlKkalvOLbBqGqrqpqqBrug9rFlBpiNuesKmrB5q/oBAGDkBI4NqBboet6CQ5gwMEJv8yrhpGtI7guiJxmxQZLimdYblm1FNHmjo3BBJaYW4FbPtWtZ8iBl70Re/jNl2iIEcRRFCcOzpCvKYHuuK9x7jOlZygqeGLsmK4oXxW4sbuU7Gc%2BIEnny8nsSk7ZKZ2Zpqf%2BrJ/ryWn1jp5Hjvc6EyqZ8bcVZur6icmaIdqcVoVkYkGSFl6KcpXy%2BYF/K4pJggwYxqpAvppbgj4g5FQQMEcXhZKepEj4HvGN4UveVIeIItKRMQL6qRpfb%2BYBwnaWO%2BkSmlGFRWapVqhqyXrvGxq4fReU2qNxHjcFk2UdmglYeZiILbZ0acQasIqVxlmplcfFUb6R1DgVomzeWT7FceMlXHJXmXdl3knQim1g7tIF6SCE4OQec0g/8MWrnFNnMdGpxGXDzm/eyzZGh5WU%2BcNW1WjtQWQxRGURaW8MWcuyMrRmi1IShqWQZF/3KQTANXrzSIAFSC0LwtIlCAuCwAKtgQgS0LotfOLwsi8D5j%2BBEopeFg6ZuGgDDbOkVbHVC4NBa1lYlSGKr/AAWgkqADMQV0mkjvEJWbhJNldnk5Z8JtvbVFvwV6kQO07iN3a7TO1fzntA18xvEyRbDu99ZkLRLADu9tTAoYcu2mbvRzHSle4TvuJxDZFQgtT00WXZIS5gkz/BowNI0IXjpCUmDoFqTcUo9h3%2BqcEQEKQ/yj/z4%2BT8X7w81CSN9woA9u%2BVIKVRC9qjzBNas6ctsag74/NZgR//Jn2dtPDu8pactdHXPPvzDKAD6%2BkJAQECTOgNYKDcb9yjcEvCk48O5dyyD3YBWI3grHrqiRuzcuBtzumA7uvd%2B5YhflwQeAlh5uEnuPKgtBdQECnv8dAGxYj0FnmXReGCCBYL4mvUEVU2Bb0EIQ4h3Jx4UK8FQ9kZkb56ntCfB2O8QB7zcPfYej9gbP1LAApQ7Qv4EB/iAP%2BbAAH2igQwrgoDO5oJ0VgmBcDz5N1VGYZB9NUEQPQcvTBZgcHPTwaPThJCyG8P4YLAM88vh0PsQwxxq8xQb2quwse/wiEkJ4ZQ%2Bg4jJEH0vmQYOp8pjjwvg7a%2BEjb5SKHrmRsvjvitFfu/ZR39f7/3dNo%2BhL8zD6PAUoOxFJakmKUhwNYtBOAAFZeB%2BA4FoUgqBOBuGsNYBiGwti4lVjwUgBBNDtLWAAaxAF0yQtwNCSC4CkfwGgukaDMIEQIZgAAcxz9CcEkLwFgEgNAaFIH0gZQyOC8AUCAO5cz%2BntNIHAWAMBEAgA2AQdIXgx4UAgGgA4dAEhRBuJwVQxzAgAFpAiSH%2BMAZAyB/hSFuGYXgPdCAkDwD/PR/BBAiDEOwKQMhBCKBUOoT5pBdB6Izr6dInAeAdO6b0%2BZgzOCehBcC1UqAqD/HhUilFaKMVYrWY4iAHhIX0EdtMlYvAPlaDWBAJAEL0hQrIGC7VuqQDACkHUmgWJ6SUFiDy2IEQ2jnHZbwG1zBiDnE9LEbQmAHAOtIBCyszVaD2oZVgWIXhgBuDELQV53BeBYBYIYYA4gg14GnA4PAAA3JuPLMCqE9SCnYMzR4NB5bQPAsRfQuo8FgHlIY8DXOjaQDNxBYgQIjHGowJajDzLWEQpgwAFAADU8CYAzlRPpMzSXCFEOIKlE7aVqB5Uy/Q8aUCjMsPoUtrzIBrFQAbXIUbEXfwSqYSw1gzCPMbcQIlmat29E9U0FwDB3CeC6HoMIdIlhjD0SUHIAgZh%2BC/VkH9DBFijESHouwd7%2BhTA6M%2Bwo4GGiQYEA7IY77QN6HmNMWD/7bDQZA9UT9awFATO2BITlHAen3J5U80VCLkWovRZi7FsrcAEqVWYfwXAVWzK7WsBAmA9RjAgEskAkh/C3CSP4FIkgNlmEkIEW5XTAhJHORwS5pBrkcduIELggRjlJGOTp1ZXAukSeCA83gTyXlvO458jVfzNUAoFSC8glADWKphWwTgbQWBppSIipgekUxcCSLcLg6y8X4CIJe4l1LJ0UokNIWdSh50Mt0HUllTA2XRrIxR8zvKOD8qBSC/4wr/jed8/5wLK5guhfWf8OVqAFUJANOxswXG1VfIc25hILnwWNZ1YqkA5W/NuiMMFrgdyzV7AGpa61tqXXeqdXat1HqvX1t9YSf1gaBnBtDeG2gkbvWxvjYmnbybIMZqjQM7Nua9jesLZ0hlJay12srTsAZNa60zMbc2pQraTvLi7XwAwfbB3DtHd6id5Lp2JdkHO%2BlAy0tLs7ceqwa7nubqE4M3dAh92HozKj0956EjRevVjiDqbnAQFcH%2B19j68PLAA6UXItOmdAYZ5%2B29lPmjQdZ1zpoyGOdgZw4MPnGGUOVDQ5x9YmwSPS8e7lqjnAyvEB835gLo3qshbCxoerLGostY4%2B1njpA%2BMCcSFjx7amNMhY2SkEzKRtmSFkyivReXLO2Gsx1uz8AHOAsFb17rxAPM7G8xKlgCg02YrTTVtkkwIusaJXoKHU7KWw5pclhHOgAikAy1ljlKnFcMqeYVwVJWRVh9RRHqP/wY8hbj6qBrTW2P%2BH8Mb2z3ytX9d1YH7vg2o9dxfnXl%2BDe36q5RXwOg03XkQCtQypbC360L9de6u93qNuCC2zy3bYaI1Rpmcd9t72Y3ndTZdrNObkB5vu4IItT3S3lvOG96tl6vu8B%2By2/YAPO0d57aDodI6BYkOsg0OaesW8OC6OeBgKOq6NgGO8A26OODAUaSI5ShOlgZ6FmF6V6mOhGCG3OD6T6BQ2Gb6ku%2BGwu36TQfOlBuQQu6G%2BBAuvOWG9BfQSGuGqG5B6GTBxBXBCwHBjOhGxGlKOW3Kxeyule/w1e0eseA4zcEA%2BuJAhunGqqJuZuWAFuZG1uIAZgIWreXSeymytyreKQumlGYhzynu7yJuyykgXS4mXSxyBySQkgqQxhXA/gKm/gohjynAKhtmZGuKZhPhFh3uawja2QzgkgQAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/classic_plume.hpp)
- [unit test](../../../../tests/unit/typelivore/classic_plume.test.hpp)
