<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Plume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-plume">To Index</a></p>

## Description

`Typelivore::Plume` accepts a list of elements.
Its first layer accepts a list of transformations and returns a function.
When invoked by an operation, the function instantiates the transformations using its arguments via a process similar to pack expansion and invokes the operation by the instantiated transformations.

Check out **Examples** for more information.

<pre><code>   E
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;E&gt;, Transf<sub>1</sub>&lt;E&gt;, ..., Transf<sub>n</sub>&lt;E&gt;&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Transf
-> Oper
-> Oper&lt;Transf&lt;E<sub>0</sub>&gt;, Transf&lt;E<sub>1</sub>&gt;, ..., Transf&lt;E<sub>n</sub>&gt;&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;E<sub>0</sub>&gt;, Transf<sub>1</sub>&lt;E<sub>1</sub>&gt;, ..., Transf<sub>n</sub>&lt;E<sub>n</sub>&gt;&gt;</code></pre>

## Type Signature

```Haskell
Plume
 :: typename... 
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
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::Plume`:

- We will pack `int` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will instantiate `Operation` with the results.

```C++
/**** Transformations ****/
template<typename Element>
using ZeroStar  = Element;

template<typename Element>
using OneStar = Element*;

template<typename Element>
using TwoStars = Element**;

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = Plume<int>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int*, float*, double*>;

/**** Result ****/
using Result_1 = Plume<int, float, double>
::Road<OneStar>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<int, float*, double**>;

/**** Result ****/
using Result_2 = Plume<int, float, double>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEmYAzKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkixp9GyCTE13xxfXt2f/Zx%2BV0uVwImGeBjBJmSbgIAE80oxWJgAHRo7CvRgEBTQ7AgybELwOO7KfKYEEmQJWa53Wl3Xa7O4AWS8tEcL0wdwx4KxOJpdIZzNZ7Podw87wiCT5VzpdzBEI%2B5Jh8peiuhsIRSLYaJRuLuyAMCgUOo8CjYjmQOOSeP5tIJRIIJOIqCIACVUEx0HcQbLKRZvbbZXLwaqocqQ5ClRrEcxtWi9QamEa7gB5RHED45XE%2BoN2giE4kAEUwrToOdzfvLubpXiyRjlmu9yULqfTmYE6tN5rwlvV3Le2NxOuzyWpMurlML0LHVdlKsj6vnauVmtjqPj1v1huNaKuwGImB5gitNvHudrEWAd3dnqbLeLpdo6r3B6P2OH1pAIHhiOnVcnf7XFWgosmyeAclymLHsBjICJy4qlpExBVkuYawhGy7Rlq666puibJl2JY9tmgb2sSyjOm6HroJ2mTdqY1r/lSAZnkGqFRuxi6rsiH7YFuSYKK2CTtgwJGsbKZGOg%2BTBloGvpUrO1YXvWP6ctCLZpsJTS0WaREMW4/a8kOG54qOim0gBZlAXJdKceGCpoapa68fxRo6i%2Bh4Die5l3MpV43l66l3NJZYwh5b47rh2BfqpgGsZZM6BnZ6EORx3FxlFrmRYRFreYGfnXtRd5Oi6qABTp9GRSOM6BFOVnAtcyVOcikFvmJkkkmSfZQQQYmVoGgoppErUDjBQpgRBCEyUh0pzhhjnzWlMY8SZWUmnRel5axHUUaVAUsfJ/o%2BU1i1cctGUJtuQkZtpjE2XmBZSSWMlPvd3oKW9soFapxWaTdWYwjlPZWgZPXGVFcXVu9dWJeJtmnfZoZLdhLn4ZF4VeWJUMFftQUhU%2BYX7p5vK8TFmqQ3SCUUklCMpUjZ0o6taPrbpuVYzWdb%2BUVQW7VRnoVZtvFxVT1k3AC4vfCCfz7HcABieDEJMXKqKwEGS78Eua0CFIpBEBpeFgTZuGgDDbGkg53Q1Yv3AAKhmDAKPwxAsCJgnq6CtPNWwI1YmJBUAFoJKgAzEBZzY%2B4IwuNZ76WcoZkeWwVQ2YCHxXxwQ%2BxRx7qUM2uEe9YnnN3DbADuwdTIJQXp4cWfS9dIlfOcIJNbHQvXB1f0ibXxx3EIXhpMUmDoK6mAKMKjeHECBV9wPmRDyPY9sr9ba3W4EQEKQdzr/sm/b5njH1VLPcL%2BP7s46P48811MLr2JX7lTCgfOiHm/Jy/xdlyHW339R6qd7dplYZ1xtqPR07t5gWgAPoCQSAQCAkx0BfgUMiaBIMT5sk3jPQew8L5slxCsbumsJZAjrkITAJsvTYBVhCTk7tpZEMBNTa2hxe792wegsBTdrjTzYXPHBi8CCQK4MvLSAM16CB3ncKgtAPQZ03ugDYsR6D70AUwuuHCJ77CnkXDhQjiqkh8FGdem9pGyPkYo%2Bgd8QAPzcG/KYVibH/wBqo0WwDQGaKBBAnsqClDtHgQQRBIBkFsFQeqXRXBMG8KUPw4UQj8GEIYYwjWtsEAK0odQtWXDmGJJONrZJLCsF8I0WfIuhTom6LMCI/6HYb6CBMTIj4kiFFeCUZgGuB8gHH1wZwyeIJz4CMgZUq%2Bhj1TGKkQ0jedxmmtIcb/R%2BQd352LaJvUu5c2jf2sXM2xK9nEJJliApW4DWhQJgX4hBSCUFJjCd0wZkTZ7lJuWYeJo4OBrFoJwfwvA/AcC0KQVAnA3DWGsHcBQGwthqRSDwUgBBNCvLWAAawCJIFEGgAAcZgzAAE5MVcH8Gi1FXBAiBGkO8jgkheAsAkBoDQpBvm/P%2BRwXgCgQA0phT815pA4CwBgIgEAGwCBpC8BvCgEA0DPDoAkKIyJOCqFRQANgALRyskHcYAyBkB3CkCiMwvAh6EBIHgRBET%2BCCBEGIdgUgZCCEUCodQ7LSC6AiSXDMaROA8DeR8r5sK/mcBTEKwVjpUBUDuLKxVyrVXqs1ciypEAPDivoKHcwyQuArF4GyrQawIBIDFWkCVZARU5rzSAYAUgzB8DoGCRWlBYjetiBENocI3W8DrcwYgcIUyxG0OQtlUKxUDiGrQRt9qsCxC8MANwYhaDMu4LwLALsjDiGHQrbteAABuo9vWYFUOQoVOwoXrwaN62geBYgZjbR4LA3r8x4EpTO0g67iCxDnsWedwBj1GFhWsaRTBgAKAAGp4EwCXTS3yoUmuEKIcQlrwM2rUN6x1%2BhDDGCBZYfQJ7mWQDWKgc2ORp0KoQepUwlhrBmHpQ%2B4ghqN2Yd6Cu5wEBXAzD8BEsIkolhjAicUbIAhGN6E400RYowag0YcP0KYHRPBdD0HYWjzQxMCaqOx2wYmeMRPmO0eTywU3rE2NsCQHqOCfNpd6hlIb5VKpVWqjVWqY24H1YmyFqboWfrWAgTAnoxgQARSASQyQUSYuSMSjQkgzCSDldS/wcrMX6E4OS0glLk0ojlVwOVqLMUErlf4SQuL/NyqM/ahlTKWVOfZZmnlWa%2BX%2BqFeQSghaE1SrYJwNoLBV2BAVUwfi9YuCYpRFwFFur8BEAo0aq1EHzUSGkDBpQcH7W6DLc6pgrqZ36cM3S3gDK/UCqFXcINpmw0qsTJ17rvWNB3FjageNCRvQpDMI59NHLyu1YSNV0V53c0JpQAYIwXWuA0poGyKU1ba31rbU20gLaG0dq7Q4UHfasQDqHb8kdY6J20CnaDudSHF2I%2BXSJ9d07flbp3WCUHB7SW/OPaehtF6di/OvbeqFD6n1KBfZjy8n6%2BAGF/QBoDIHQfgbNVBibshYN2t%2BbNxDH6iNWFQxTjDnm/k4YEHhgjzYpckbIwkIbVH5fSZE3RhjEmCjMYYOgDTim%2BM5BU%2BkTIXGGBm6E7rpoIdxP5CY8Jp3cnWOCak8pw3bu1NDC9wpmoaxQU6Ytctr1%2BXOC7fMx1q8XWesotO7ZwbV3k23ec6QVz7nEjy9JbF%2BL3WguBH8JiolyRguhay3l%2BlnBCusvZ1y3l/KA3Pce8QerOwmvhpYAoVdGrV2J8jJMfrdnDV6H55Bi1QvrVTdFzoEAqR5uLfddFgzUe68cA2wG7bwbVC9/74P4fiolZnYu/Z5IyRM8lc5dm17eb28P/ewPgekCh%2BYsgSPwRB%2BJsVoBxADWvauDiDneiAe2p2t2jDudv2gwIOt6kjuOpOtOlChjgujTrOjjo4HjputusgLuiToIIevahTmenCNTlehRvTrwIzs%2BuCKzh%2Brft%2BlzoBsBjGHzrIALjPiNiLvBkvhLshsRjLuhvAFhorg7JwLsOcmrpYKRmtuRpRnLqHg0DJi4CblbixhUN7hxjbk0FbhbmUEHppu7qJoMFbo7qYepkYYpgHuYZ7locHnptpuCk4aSitsZjHr/ncH3gPncB/iiN/ingNiQOnimmmlnjnlgHnvpoXiAFiiiFfv4HilltSlfoEClrXmtvXrYEVndisF5pIP4H5oSoENSqipIDilwOimYLlqSskJvlkYysVhmvpjqpkT6k0XkWsA%2BlkM4JIEAA)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/plume/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/plume.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/plume.test.hpp)
