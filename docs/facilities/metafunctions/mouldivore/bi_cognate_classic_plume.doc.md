<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::BiCognateClassicPlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-bi-cognate-classic-plume">To Index</a></p>

## Description

`Mouldivore::BiCognateClassicPlume` accepts an operation.
Its first layer accepts a list of containers and returns a function.
When invoked, the function places its arguments into the containers via a process similar to pack expansion;
then, it collects the type result of each packed container and invokes the operation with the collection.

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
BiCognateClassicPlume ::   template<typename...> class...
                 -> template<auto...> class...
                 -> template<auto...>

BiCognateClassicPlume ::   template<typename...> class...
                 -> template<typename...> class...
                 -> template<typename...>
```

## Structure

```C++
// Plume `Rail`s
template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto>
        alias Page = RESULT;
    };
};

template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

template<template<typename...> class>
struct BiCognateClassicPlume
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
struct BiCognateClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<typename>
        alias Mold = RESULT;
    };
};

template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};

template<template<typename...> class>
struct BiCognateClassicPlume
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

We will see six examples that present different use cases of `Mouldivore::BiCognateClassicPlume`:

- We will pack `0` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
template<auto>
struct Vay;

template<auto I>
struct AddZero 
{ 
    using type = Vay<I>; 
};

template<auto I>
struct AddOne
{ 
    using type = Vay<I + 1>;
};

template<auto I>
struct AddTwo
{
    using type = Vay<I + 2>;
};

template<typename...>
struct Operation;

using SupposedResult = Operation<Vay<0>, Vay<1>, Vay<2>>;

using Result 
= BiCognateClassicPlume<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<Vay<1>, Vay<2>, Vay<3>>;

using Result_1 = BiCognateClassicPlume<Operation>
::Rail<AddOne>
::Page<0, 1, 2>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<Vay<0>, Vay<2>, Vay<4>>;

using Result_2 = BiCognateClassicPlume<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0, 1, 2>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We will pack `std::integral_constant<int, 0>` into `TypeAddZero`, `TypeAddOne` and `TypeAddTwo`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
template<typename Element>
struct TypeAddZero 
{ 
    using type = Vay<Element::value>; 
};

template<typename Element>
struct TypeAddOne
{ 
    using type = Vay<Element::value + 1>; 
};

template<typename Element>
struct TypeAddTwo
{ 
    using type = Vay<Element::value + 2>; 
};

using SupposedResult_3 = Operation<Vay<0>, Vay<1>, Vay<2>>;

using Result_3 
= BiCognateClassicPlume<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<std::integral_constant<int, 0>>;

static_assert(std::same_as<Result_3, SupposedResult_3>);
```

- We will use `TypeAddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_4 = Operation<Vay<1>, Vay<2>, Vay<3>>;

using Result_4 = BiCognateClassicPlume<Operation>
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
using SupposedResult_5 = Operation<Vay<0>, Vay<2>, Vay<4>>;

using Result_5 = BiCognateClassicPlume<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

static_assert(std::same_as<Result_5, SupposedResult_5>);
```

## Implementation

`Mouldivore::BiCognateClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<template<typename...> class Operation>
struct BiCognateClassicPlume
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    {
        // Multiple Sequences
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<typename Devices<Variables>::type...>;
        };

        // Multiple Sequences
        // One Variables
        template<auto Variable>
        struct Detail<Variable>
        {
            using type = Operation<typename Devices<Variable>::type...>;
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
            using type = Operation<typename Device<Variables>::type...>;
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
            using type = Operation<typename Devices<Elements>::type...>;
        };

        // Multiple Containers
        // One Elements
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<typename Devices<Element>::type...>;
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
            using type = Operation<typename Device<Elements>::type...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIGYa0gAOqAqETgwe3r4BwemZjgLhkTEs8YnJ0naYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQlJKbbNre35XQpTQxEjlWM1AJS2qF7EyOwcBJgsqQYHJgDMbgdHJ5jnlwCeqYysmAB07%2BfYANTIBgoKXwA8k9iEw%2Bp8TBoAILzYheBxfCx4DzAZgHNx/TLIZR5W7QkyBKzQr4kr5XY5g24Xck3O5MLxEd6vT4/TFMgAimAAbnhdgoIcTSbD4QQvspiKgiAAlJh0SFQ0lfAlEhWK0kAenVXwAsl5aI5jpgvkJMABHLyMPnytUarW6/V4Q1fABqLTwTFi9H5gptNMpdIZqCZruI7s9mH5Z2w1ptX2FCM5zTlPrVypjsdJXkyRjJjyN53ZQJBYOydwIeeYbC%2BnJ5VouIbDXs%2BIBA5aeTIhZxVGYJ7POKvTas1Or1BvoxrNFoYVpTiuHgMiLrdHqbs9JftOF3pRCXoZXVOja5J8dFidltDuDf3AtVNrTR7VWYiwFzTyVZ0LwISJYEZYrL2rbleQjS9l3DZtWzzDso37QdFV7WD8QfDcqTcbcg3eKFgGITBDkYAhI0PW9H2zF9lCYYB8w/QCkwvC4sJwvDBAUaDsBbNsqW7UkEK7eVBxQstDgpTc0MDVjWSYf5ANrA9BxPMUJWlc87hrYCb3gwk4NtIFFxNc1LTxYi5ztUdHXHK9w29Iz1yE2ktzE94LKbGCH3ks9k2skl708kjn1fKjP2LcFqX/KtVN2UC90siCONYxCfJ4gdkNs/17MZTDsNwthmPU2MnxzcjKPfQt3LotwGKy/CWI%2BKN2LzeKNL7XikOIgTqRSkT0PE35JOq14KqYgjcpJfKXxlOhioUyVUHGsqBuygi4uaqF%2BI61C2oeJ5KzeGrvh6/4OSAusiMVeTxWmqVUCYdBB28jNh3tMcjQ8QRZUiYgrPukyHSdbB6AWz7Yw2jjtqZP7BsIrTjwIOEE0wWioaVTSH0VUb/Mmr9QWCzbnjCo6QIucGAZiqDdoa2NEr4h8HtMp0XqTd7AZtedFyJqrEeB0KjTZwRhrVNz4eUwn/vwvmNK4jMRtI9GCyLb9sZBgDwoJtweYIEn2zJ5ae0CJqkp8zmtpeJl5vZlyfLR7VPHQSbSruU3mNYuqnnJrzdfi1brlSy41r/I22G6zFpLU83TphkUpulK6bouZW%2Bbu2MWee2Q3oSJmh2%2Bp6vjV9PFUN3GdteHOxaFcO4YRh8E8lr40Y4jGgtLEL/aNOPhYhjXC87CXU3d5aOd9puC5NzL29DvLpat2gbdlu36JHgGncgl3te43v9bzgefa9kTFYD3aJIOjLGOJsepb8y7rsm86o%2Bu%2B356qpaBzXqmVuhdUACpP6/7%2Bf/VeUP6/l8AAKhGAiXxv5/zfj/aBECX7mDOBEX4XgsDvjcGgacmBUhDXNvKDa6EbzyVdHRfWeDAxfAAJIELLqKKE6B0AAC0EioCVPiQkLDiK1zzJNIhdxKEwS7OwymLVSE7j4UReStD0ALkMsqdhqNpZ11ljwi45ClSWC%2BFwLufFn7CM3uhChVDYY0LoUAgA7qgbR3dOFviUWIXhaiLBfDMFo1hesX7522tnEWvNzbySAXmSRjCJSCLYYOaxAUlxlTVi2LkYgLRdxCW43R291pcy8YNQxEd/FPEkdIyxcjMwKK4bYqJ3iCAxLifmdRmj%2BGOO0Uk1%2BUIPEATVpkhE2TMCSLMRY1hdSUzhO4XYtuC0KneCqY45xtTEke2hM0vezJfHULlljRu%2BsAGfy%2BAAMTwB9UU2BVCsCdLAlqaMhBeFSEUTA6ApQRlHPXeWjc3DKLcBoT4pBIl3Bqdgd5zzJnRlqS/NGNyFB3L4tRJEKI0SYAxL1XkOIfCoUxj%2BBgN4WyzXtnQoJqB3m5MiDikx5jUUgEKqhV5AKWrzBLMgAA%2Br1BIBAIDzHQC2BQLxaWRjcMC0c7yzkXIyFcrl%2BpPhrBmVCdZ78JzoJtvsw545jmNNOecy51zbn6mpVwe5Kzfz1iGW4L5PzdV/INWVM4nZ/n6yBaqgg6rJoQtQKiSkML/hwtxHcJFwUiJoqFuVOheTzYthJXcDQ7yuDvL%2BaKyljgaV0taIyggzKQCsrYOyu4grrWhuNEq/lKqQVqq%2BSKvuUDAFAIQDs6VBzrhGnlfKRVfKlA5tHNSswmrkWgTKmS75HyLhGq7W4SQZrRWWtzda5tss7UOvRJiF1CK3UN21Z6kA6L6KYqYfiqReKvhdMJf64lFFSUhrDS4xpkbeTsqULGplLK2WSVTVaptPKs31rTU24VorxVbK2K0BA2cK1HK/pAhV0teXKufWcFt2NnkduNZ8t5vbw3ksA%2BfO9YGwWFnHVCp1WJ4VsFnQ8%2Bd8o0XRzuB0wJq7gEBN9RukjBKLE7snjHNwl6QARAONhMQ1L0GUp8W4Fj7yO1HvlCe6N/x6VxoTUmzAKaLigYfXWgVyHX2FrFd/LZeAqAEG/TKyt4D/2AqA4%2B%2BTw7qWSHA4855%2Bq4Oweeaa/h5q9NIaMyZsdyJ7UYandiV1Fx3WNwXRfBj1H12yWhC2ejdw5LxpbCxzAbHaAcYEFx9WFxeNfCg%2BFhNUWYtxYYAlu4yX9Vpci4IaLoJYuceaNx5L4b8QIcE80KNZ7RNMYk1Jzld7pCZrkw2tV/aowFrWSpoQeBVAaZ/bKqtumTn6c68%2B/wpntVPN1VByzUZoMXB6/8uzk2HONtm85yFjr3PYcRXOlFO6/PEYowwsjAXpHvIC90oloWLgFeY0VzLZXDCJZ44IPjbyXsZZK1lnLSWfsaL%2BymJjAP2MfYq6DqrK0avQiEw1i9EXE3Xo5TN2TIG73%2BEUxYDgGxaCcH8LwPwHAtCkFQJwNw1hrBxk/bsNRZweCkHKRTwnGwADWARJCvBSFwQIZwND%2BA0GYAAbOLswAAOaX%2BhOCSF4CwCQGhg3k8p9TjgvAFAgGDezrQGw4CwBgIgEAWwCCpAZOQSgaAjh0ASFEF4nBVDS/FwAWnFyZ4AyBkAaL52YXgVzCAkDwMy0N/BBAiDEOwKQMhBCKBUOoDnpBdChtMaCVInAeBE5J2TzQvBNeAgZJb0UqAqBfBd%2B7z3Xxve%2B6kK8ZtEAPB2/oMQZnXA1i8H14T0gEAkC29SPbsgFAIAD6HyAYAUgzB8DoAcD6lBYj59ILECILR7hZ94Cv5gxB7iAliNoeo7PWe24WguWg6/k9YFiF4YAaFaC0B19wXgWAWCGGAOIS/OzD94C5BGJfmBVB6gGQ9hWcotidk9aA8BYhQQd8PAsAl8YY8Blcn9SBf9iBYh%2BVORX8jBICjB88NgqADBgAFBnQ8BMBTEvxydWcI9hBRBxBY8aCE81Al9U99A38UA6dLB9AoCddIANhUAsFshH83cmUCxTBLBrBkgC80DQwsBeCIANg6gGhnAIBXAZg/BQ0wglgKgqg9AigsgBB1C9CMgDCGBhgdCxhQ0lC%2BgBhphPAOg9BrDGgFhzDRhEgrCFgjCPDBhXCVh3DFDGcY8c8OBSdSB1cC9OAK9XcPcvcfc/cG8vgIBcBg8294EO8u98CNgEBMBroxgFDSAedJAzhXgABOM4QISQFIMwSQcXVXfwcXEo%2BXDgRXUgZXFnV4cXLgcXaXEo6XLo/wSQLgfwMo8XMIpfTXbXXXNnfA3vE3PvM3YvK3EfMfVvR3NgTgFoFgLkQIN3JgCSHMLgEo14LgfnQPfAIgWQvQGgqPeg6QRgpQZg5PXQafdPJgTPJ/YI0I8IqnTgIvC3BkL4MvL4TY7Y3Y/Yl8Q444/nRI5vQfVvZnMwTvaYjnQ3fvVAFvBIa3UfdEuEsYEEnYnqIwQ4rgYNGgfUNOBfJfLfNfDfZfVfHfPfA/BwWkk/fCM/C/SnK/G/O/B/Wkl/N/D/Tkr/BoX/R/SnAAoAg4WksApfSA6AtfOAvYSnRA5A1nNAjApQLAgU58GYwgiiEgsgigraWk64ugmPO42QJgpPSnZ4tgvA8QqwLguU%2BQ/gwQ%2BLTgEQ%2BNMQzgiwKQqnGQ0PP/Pg7oXobIFwBgdwew/ITQiM3w3Q0NfQvoLw0gRM7IOMywkM7/AQWwtoKMjQzM5Q/oFw7QtwxwzwvMssnwksvwiQAI7YXYWspor48YyI/EsEwkiEo4k4jQRI5Ii49vJE7vNYLInIrARIfI8Alotoo4lIQIYYwIIXSQaoz3UNb4iY2wKYoc2Y%2BAeY83EvLElYh3J3DgTY6vFgBQLkX3LkSEm4eYM4lI0PK42QG480uPeQB460nQEAM4UgV4947PJsvPZPQvRY0vcvU8kzc8y8r4a8o4280UJvHEofZnM4QcmY%2BYw84fG3JC1vEAS8i5alWC6leC2lYgFgT3Gfck%2BfCARfZPaknfWk%2Bi3fffQ/Fk9E0/Bgc/JfLk2/MQXklA/knApU5/YUxwUU//QA5AYA6UorcAynOUmA%2B4RUhA0MVU3gdUzAw4bUvAlEvgIgg08gygk058s0iQC0%2BPD8lg78u04wH07g2IF0qnN07LTgdUS9B0yQjXAMuQ%2BARQnoLMvwVQiM5MrQ8oUshMkwpMisiK4oNM6s%2BMgsmw8svIfMpw7M4ssKms7wuwlKys1odM/wzYesoIwCsY4C1ssis8i8q8m8ykeYXs84kgAcjIlEkc3I8c4IqcpII4s4M4fwUXQY1XXqwIbosqjXTgSYvXTIgokASQfwUo/waXCXEoyQEooXcorgH88As4IC8arXZEg3YIgPMaiI/aocjYNAzIZwSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/bi_cognate_classic_plume.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/bi_cognate_classic_plume.test.hpp)
