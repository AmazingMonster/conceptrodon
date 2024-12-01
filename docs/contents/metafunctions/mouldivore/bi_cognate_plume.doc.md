<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::BiCognatePlume`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-1">To Index</a></p>

## Description

`Mouldivore::BiCognatePlume` accepts an operation.
Its first layer accepts a list of containers and returns a function.
When invoked, the function places its arguments into the containers via a process similar to pack expansion;
then it invokes the operation with the packed containers.

Check out **Examples** for more information.

<pre><code>   Operation
-> ...Container<sub><i>i</i></sub>...
-> Element
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;::type...&gt;</code></pre>

<pre><code>   Operation
-> Container
-> ...Element<sub><i>i</i></sub>...
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>

<pre><code>   Operation
-> ...Container<sub><i>i</i></sub>...
-> ...Element<sub><i>i</i></sub>...
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>

<pre><code>   Operation
-> ...Container<sub><i>i</i></sub>...
-> Element
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;::type...&gt;</code></pre>

<pre><code>   Operation
-> Container
-> ...Element<sub><i>i</i></sub>...
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>

<pre><code>   Operation
-> ...Container<sub><i>i</i></sub>...
-> ...Element<sub><i>i</i></sub>...
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;::type...&gt;</code></pre>

## Type Signature

```Haskell
BiCognatePlume ::   template<typename...> class...
                 -> template<auto...> class...
                 -> template<auto...>

BiCognatePlume ::   template<typename...> class...
                 -> template<typename...> class...
                 -> template<typename...>
```

## Structure

```C++
// Plume `Rail`s
template<template<typename...> class>
struct BiCognatePlume
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto>
        alias Page = RESULT;
    };
};

template<template<typename...> class>
struct BiCognatePlume
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

template<template<typename...> class>
struct BiCognatePlume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

// Plume `Road`s
template<template<typename...> class>
struct BiCognatePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<typename>
        alias Mold = RESULT;
    };
};

template<template<typename...> class>
struct BiCognatePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};

template<template<typename...> class>
struct BiCognatePlume
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will see six examples that present different use cases of `Mouldivore::BiCognatePlume`:

- We will pack `0` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
template<auto>
struct Val;

template<auto I>
struct AddZeroHelper
{ 
    using type = Val<I>; 
};

template<auto...Args>
using AddZero = AddZeroHelper<Args...>::type;

template<auto I>
struct AddOneHelper
{ 
    using type = Val<I + 1>;
};

template<auto...Args>
using AddOne = AddOneHelper<Args...>::type;

template<auto I>
struct AddTwoHelper
{
    using type = Val<I + 2>;
};

template<auto...Args>
using AddTwo = AddTwoHelper<Args...>::type;

template<typename...>
struct Operation;

using SupposedResult = Operation<Val<0>, Val<1>, Val<2>>;

using Result 
= BiCognatePlume<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<Val<1>, Val<2>, Val<3>>;

using Result_1 = BiCognatePlume<Operation>
::Rail<AddOne>
::Page<0, 1, 2>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<Val<0>, Val<2>, Val<4>>;

using Result_2 = BiCognatePlume<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0, 1, 2>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We will pack `std::integral_constant<int, 0>` into `TypeAddZero`, `TypeAddOne` and `TypeAddTwo`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
template<typename Element>
struct TypeAddZeroHelper
{ 
    using type = Val<Element::value>; 
};

template<typename...Args>
using TypeAddZero = TypeAddZeroHelper<Args...>::type;

template<typename Element>
struct TypeAddOneHelper
{ 
    using type = Val<Element::value + 1>; 
};

template<typename...Args>
using TypeAddOne = TypeAddOneHelper<Args...>::type;

template<typename Element>
struct TypeAddTwoHelper
{ 
    using type = Val<Element::value + 2>; 
};

template<typename...Args>
using TypeAddTwo = TypeAddTwoHelper<Args...>::type;

using SupposedResult_3 = Operation<Val<0>, Val<1>, Val<2>>;

using Result_3 
= BiCognatePlume<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<std::integral_constant<int, 0>>;

static_assert(std::same_as<Result_3, SupposedResult_3>);
```

- We will use `TypeAddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_4 = Operation<Val<1>, Val<2>, Val<3>>;

using Result_4 = BiCognatePlume<Operation>
::Road<TypeAddOne>
::Mold<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

static_assert(std::same_as<Result_4, SupposedResult_4>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `TypeAddZero`, `TypeAddOne`, and `TypeAddTwo` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_5 = Operation<Val<0>, Val<2>, Val<4>>;

using Result_5 = BiCognatePlume<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

static_assert(std::same_as<Result_5, SupposedResult_5>);
```

## Implementation

`Mouldivore::BiCognatePlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<template<typename...> class Operation>
struct BiCognatePlume
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    {
        // Multiple Sequences
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<Devices<Variables>...>;
        };

        // Multiple Sequences
        // One Variables
        template<auto Variable>
        struct Detail<Variable>
        {
            using type = Operation<Devices<Variable>...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class Device>
    struct ProtoRail<Device>
    {
        // One Sequence
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<Device<Variables>...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<typename...> class...Devices>
    struct ProtoRoad
    {
        // Multiple Containers
        // Multiple Elements
        template<typename...Elements>
        struct Detail
        {
            using type = Operation<Devices<Elements>...>;
        };

        // Multiple Containers
        // One Elements
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Devices<Element>...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class Device>
    struct ProtoRoad<Device>
    {
        // One Containers
        // Multiple Elements
        template<typename...Elements>
        struct Detail
        {
            using type = Operation<Device<Elements>...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISdKuADJ4DJgAcj4ARpjEEmZmpAAOqAqETgwe3r56KWmOAiFhkSwxcQCcAOy2mPYFDEIETMQEWT5%2BATV1GY3NBEUR0bHxiQpNLW05XLbj/aGDpcNVAJS2qF7EyOwcBJgsSQa7JgDMbrv7h5gnZwCeSYysmAB0LyfYANTIBgoK7wDy92ITHqbxMGgAgmNiF4HO8LHgPMBmLtlNkrhCTJUrBD3rj3ucDsCrqcCZdrkwvEQXk83p9vgpqQARTAANzwWwUoJxeKhMII72UxFQRAASkw6GDwXj3pjsVLpXiAPSK94AWS8tEcB0w7yEmAAjl5GBzJQqlSr1Zq8Nr3gA1Zp4JhReic7lm0lE8mU1DU%2B3ER3OzCc47YU1m9682HMpoSt0K2Vh8N4rxpIz4u46k6M/6A4EZa7Mtkm05%2BgMut7U0HHOVJzGMk5yxMK5VqjVa%2Bi6g1GhgmuPSlt/MJ2h1O8t9vEeo6nClEYf%2B0fE0Pj3GR/nR8W0a6lhdc%2BVmhPLhUp0LAdP3GXHbMA2J5gQF1nsoNbkeBiuvEMNpvSuufjGHyfEm4M4%2Bi84LAMQmB7IwBDBkue5Hqmp7KEwwCZpe7zrhKpxgRBUGCAy77YCAIAEBmv7wT%2B1aSk2AHXLR07epWIZ0kwPwYQ%2BWy7tKq4CkKoobveRaLk2B7wf2KqDjqeqGsa6JiearZWja26Bq68m4vRQGMS8Knlh%2Bh48Zhm6HqJSbSseaakeeWY5jeIKnIWj7PvOqlvjSH5USZlT1p54JfhOeyElOWlUqB4GQWw%2BFceGFlIShaHZkZ1w4RF0EEe5REkWRvnft55E0YFZIkoVnoMaFGUsT81IpXhMHRbisXvGKdAXtmgrCqgzWbth4W1elVaNnGmnDRmzBsExHxfKx6WOcWcHcQQ0Kwu1oqoEw6AiVi/m4i2lrtjqHiCOKYTEGpSa7W21odtg9CRXV/4lcFVkPONLw3X19UKoZmAxsZ6kylth7mYhZ4JbZQL2W4s1Pqc713bBE3kbWeW%2Bdt7wXUpHaHTGJ1neGA5DnDaVoyN9xjTqROCJ9C1LWuP0CbDt3QdTeKmWZDUg89rXg7eDCCY%2BwZuJTBBuQNaOUYN/2ky9zxhbh8MsxzJ5qp46Dc0lPXy2lE3Ec9SOsyjkvSsNj2Ac95MTZVvzQ59PErZ1a0bQ5HHCXGbNmgTB2yMdsR4x7FqXTawt%2Bwq0sW29TNRfp/3fb94uA/9wPK1zNnXhD%2BbO0J1zB6LHk1uGEvUQ9FylbcZOPNVvUK9HSaNaqqvq/TWFuDV8M61l9z67ihd/vBJsl09o0V4RVuV1rUfzcmIMio73P2zP63JVX2uEflhtF35EKKgAVLve/7wfiqSjve/vAAKkGMHvPvR9bwf983xv5jHKEXxeFgF5uGgPaYEkdXR5KTSwFdw8XtN1SWQDvTvAAJIgMWnyd44J0DoAAFqxFQAACVqICaiWIZRxkaindCYDriwLzvgvy69e6QPKuCYgwBYKSkakg1B6DuYsLQUKLBtAcHYXof1EMutsoQNNl6WcZC4I8RYZJbhOCMR4KbIQjM3MSGnGgTKSw7wuBi3kT5ERA9ALAWqvw3czDkGSXYeYsIsjYjJX4e3PWqMIQ0NQDAuBtNEHILPgAd0wdg2x8j85K0ssomyqi3DqOsO8MwOjKF6I3i44xDDTEgxYT41xNk0m%2BJscQOxDCHHCISaIkkQ82DvGFu4hBZ8MwcPQTk3BFgKFJxCdZYhYhs6RwIMRFkYgjQDQoT3Te4Iw7DyeHQ5J0dGrVPuLUoU3NpmYFmX4nhti%2BH5MIkIzuTjhnFLLjLcpnTKmwgWdI6x/jcmBKaVPZOoS2ndSFp07pvTMyaO0eQ3B8TqG7PNqM8ZjCIRTJqVYsGJzgX1LWQIzKjj9FBTNqUimhzo48VBegdJ9TLmKM5rc7M4ThZPO8C8xpMT3m6Pys4758Kkn/PBICmZXjfHzKBai7J5y8mQs2cSGFRU9nhwypKHiadeZkvBCfXe7wABieBTr8mwKoVgNpH690akILwSQ8iYHQCKIMbZuaCshuEjQbxSDDnuW87AxrwnEtDHnDejUtUKB1dRdC8JETIhUGia4eqM5wWIl1ZKyDOGoGNaczAwb6WoF3MRZCqFriGptb3MYeZkAAH1pqxAIBAMY6BiIKEeKmwW9q2zGpVWq1IGrC2ajeMsYVort6dm/mrWV8qOyKqGcq1V6rNXas1Mmrgurcz6vaacM1Fqh1uCtaO%2B5xwqzWslna7tBBe3cxdagJERJUQ%2BEAl6u80dfUMxbsCyNIBo2AQ0Ma6Y0TYn8qaI4FNaaWiZoINmkAua2D5uuBWxdF6S2ds/b2qtNb97nwQFKxtcqLg6lbUwkGP6y1dodT2sw/a7IZzcAao1JrrgTsw6cSQM7hXzoQ4upDNkV1rpRB60426%2Ba7pAH67CAb0FhvQJJZj6Sj0ntjee41VrhWJtvfmpQD6s05rzaxD9C7k2JF1B2uDf6rXVu2bWiV6wWgIHKeBhVe9b5tpg7JpQ8G2zJuOMh9OO60NjrjeanDbgR02d4/G3Tys/0maddmMjbqN1sE9QO71kpfWO2uCiwNxqUWsfPky9jtH660Cdm4ETIBQi7HAmIZN39E1U1OEl41Vmr0Qn4%2ByQT6bH3PtfZgd9pwXPFv0%2BWyT06QyKclspyVVACDqabRB6%2B2nbV6dLQZv9khTNCpLGOuzlqMPhPq9a2dPXnOScG6RhEq7POUbcNRo9C84thbCEemLcWmwJaS5gFLtA0sCAyyLLLggctGoO0%2B4iR2TtnYYBd642WtG3bjIdwQx2gSnfS00TLbh3u8YxI569SaivCfuy%2BsTBb5vVb67Vojya8MNcA6fIQeBVBtY082yD3WlW9d/ZJgArENwd9yrOTqwxNsdaPpsEenmT5dS3yPus3T5lDO6fV0cC6cYLTGIt0pY2EULkXfG7dVtcO7z7Ht/ee69q7BAbshlILLh7P2nsA8MJd4H12Ptq414lrXCuddA5B7uPLkIb2FfvRmhLZWKtuD/aTxHJOUek4A9WDgqxaCcFJ7wPwHAtCkFQJwNw1gokKFU1sDRxweCkC6SH33qwADWIBSeSCeBoSQXBKjHA0KTjQZgABspezAAA5K/6E4JIXgLAJAaDPcH0P4eOC8AUCAM9yetCrDgLAGAiAQDrAIEkSk5BKBoH2HQWI4RHicFUJX0vABaUvg3gDIGQFo7PZheAasICQPA2bpj8EECIMQ7ApAyEEIoFQ6gU%2BkF0NMbxQIkicB4H7gPQfNC8Hb38SkcffkVAKgd4JfVfdfd4TfbfKQJ4JDCADwGfegYgePLgZYXgXvX3UgCAJAafJIWfMgCgCAPAggkAYAKQRIGgTUX2SgKIX/UgKIUIZoG4D/XgRg5gYgG4P4KIbQTABwVg0gafO6QcWgFgx/LAKILwYAICWgWgLvbgXgLAFgQwYAcQcQqVPgxwFkIMegzAVQPgykbYRPI7f3R/WgPAKIIETgjwLAegxaPARvBQ0gbQ4gKIMtZkZQowcwowX/VYKgAwBhW0PATAbxa8YPRPM/YQUQcQa/SIu/NQeg5/fQFQlAKPSwfQCwrvSAVYVAP%2BDIeQlfLNLMUwSwawMwNvFw/0LALIiAVYOwTQjIFwBgdwTwdoPQYIeYEoMoXIVIdIAQSYPwaYPIPohgAYLo4YaYeohwHoWYAYvQKY%2BoXoFoMYoYOISY2Y1oqYGYPoFYxYNYuo2PK/L/DgQPUgVvP/TgMA5fNfDfLfHfOA94CAXAQ/FA5%2BNAjA3w1YBATAdaYYWo0gDPSQY4J4coY4SoSQXPMwSQUvZvUnUvcoWvDgevUgRvBPJ4UvLgUvSvcoSvTErPLgUnUE0vM4%2Bg9vTvbvJPXw7AofHAkfQAifIgkg5A%2BfNgTgZoFgFkSoFfJgFiNMLgcoJ4LgHPfffAIgKovQSIi/GI6QOIpQBIx/XQRIV/Jgd/BQ440484sPTgAAsfSkd4EA94dkzk7k3k08fkwUnPR4xA/A5A%2BPMwdAyklPfvXA1AJA2ISfYg10m04YI0rkqaIwfkrgM9Kg3YU6Wg%2Bg9g5ggQyMzg7g3g/gpwoQ6CEQsQ0PCQqQmQuQgQpQlQtQtMjQ6Y7Q%2BQ0PPQgw3YAQkw%2Bg8wyw5gmw7YUPewxwxPFwtwpQDw3Mk8Kk/wlCBQIIkIsIgQyU6Iq/GU2QeIh/UPRU5InwkoqwdI6smonIvI87TgQop9YotIiwcov/So4/HQ7IroBo5wCAVwOY6YDo4oVYno/IDIM85IXo%2BoXY7oyY2oI8hoDY7IQYw86YgQJYuYS8vY%2BYj8to9YnYzoq8tAtYDYLYCQdUn/R/dvQ04gDkrknk/0s0gUoUjQR454sU1Ah0zA5YL4n4rAOIf40w5E1EgU3PSoQkyoAvSQKE9faYTUsk2wCkwi6k%2BAWk0fIAj0pkufBfDgdkyAlgBQFkbfFkc0y4MYEUl44/CU2QKUkcm/eQOUicnQEAY4UgZU1Uz/REjU0k7U%2Bk4A0AkSwbMSiS94KSgUmS/kBAr0gg%2BPY4Aiqk2kgSwgqfRy5AkACStVZNGy5NOy1NZC9fPgOgUMrvCAOgx/GMsQxPOKuMzQgQpMwQFM%2Bg9M6QsQLMpwnMrw%2BsxQgsrQnQx/Us5AQwisn7Uw0Pasqwm4Osuw/0Js3gFs9wvYDsnwp0vgAI3s4I0IsmQcpS4ciQUc2/dSxIrS6c4wTcjIqIRcsPZcl7TgRUETWcsoio2IKo/c/4hYxok85ou8i8hYZ8%2B8m8/ozYr84Yx88CwCl87oX84CrY3ah6sCgCk6xNCYC6oC1646iYg46Co4gy%2BCtvS48y94SyyS6SokMYHC0UkgfCj4p04i34si44yikAMwAU44Y4UnYvPPZvbGyoLEkkhCzgcknvT4gE/wUnEE0nSvMvcoSQKoQmrgbS0w44YGi4jvR0vvY4vfEmkG7mwi1YFwtIZwSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/bi_cognate_plume.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/bi_cognate_plume.test.hpp)
