<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::BiCognatePlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-bi-cognate-plume">To Index</a></p>

## Description

`Mouldivore::BiCognateClassicPlume` accepts an operation.
Its first layer accepts a list of transformations and returns a function.
When invoked, the function instantiates the transformations using its arguments via a process similar to pack expansion and invokes the operation by the instantiated transformations.

Check out **Examples** for more information.

<pre><code>   Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg
-> Oper&lt;Transfs<sub>0</sub>&lt;Arg&gt;, Transfs<sub>1</sub>&lt;Arg&gt;, ..., Transfs<sub>n</sub>&lt;Arg&gt;&gt;</code></pre>

<pre><code>   Oper
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Transf&lt;Arg<sub>0</sub>&gt;, Transf&lt;Arg<sub>1</sub>&gt;, ..., Transf&lt;Arg<sub>n</sub>&gt;&gt;</code></pre>

<pre><code>   Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;Arg<sub>0</sub>&gt;, Transf<sub>1</sub>&lt;Arg<sub>1</sub>&gt;, ..., Transf<sub>n</sub>&lt;Arg<sub>n</sub>&gt;&gt;</code></pre>

## Type Signature

```Haskell
BiCognatePlume
 :: template<typename...> class...
 -> template<auto...> class...
 -> template<auto...>

BiCognatePlume
 :: template<typename...> class...
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
/**** Vay ****/
template<auto>
struct Vay;

/**** AddZero ****/
template<auto I>
struct AddZeroHelper
{ 
    using type = Vay<I>; 
};

template<auto...Args>
using AddZero = AddZeroHelper<Args...>::type;

/**** AddOne ****/
template<auto I>
struct AddOneHelper
{ 
    using type = Vay<I + 1>;
};

template<auto...Args>
using AddOne = AddOneHelper<Args...>::type;

/**** AddTwo ****/
template<auto I>
struct AddTwoHelper
{
    using type = Vay<I + 2>;
};

template<auto...Args>
using AddTwo = AddTwoHelper<Args...>::type;

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<0>, Vay<1>, Vay<2>>;

/**** Result ****/
using Result 
= BiCognatePlume<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Supposed Result */
using SupposedResult_1 = Operation<Vay<1>, Vay<2>, Vay<3>>;

/**** Result ****/
using Result_1 = BiCognatePlume<Operation>
::Rail<AddOne>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Supposed Result ****/
using SupposedResult_2 = Operation<Vay<0>, Vay<2>, Vay<4>>;

/**** Result ****/
using Result_2 = BiCognatePlume<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We will pack `std::integral_constant<int, 0>` into `TypeAddZero`, `TypeAddOne` and `TypeAddTwo`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** TypeAddZero ****/
template<typename Element>
struct TypeAddZeroHelper
{ 
    using type = Vay<Element::value>; 
};

template<typename...Args>
using TypeAddZero = TypeAddZeroHelper<Args...>::type;

/**** TypeAddOne ****/
template<typename Element>
struct TypeAddOneHelper
{ 
    using type = Vay<Element::value + 1>; 
};

template<typename...Args>
using TypeAddOne = TypeAddOneHelper<Args...>::type;

/**** TypeAddTwo ****/
template<typename Element>
struct TypeAddTwoHelper
{ 
    using type = Vay<Element::value + 2>; 
};

template<typename...Args>
using TypeAddTwo = TypeAddTwoHelper<Args...>::type;

/**** Supposed Result ****/
using SupposedResult_3 = Operation<Vay<0>, Vay<1>, Vay<2>>;

/**** Result ****/
using Result_3 
= BiCognatePlume<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<std::integral_constant<int, 0>>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
```

- We will use `TypeAddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Supposed Result ****/
using SupposedResult_4 = Operation<Vay<1>, Vay<2>, Vay<3>>;

/**** Result ****/
using Result_4 = BiCognatePlume<Operation>
::Road<TypeAddOne>
::Mold
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_4, SupposedResult_4>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `TypeAddZero`, `TypeAddOne`, and `TypeAddTwo` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Supposed Result ****/
using SupposedResult_5 = Operation<Vay<0>, Vay<2>, Vay<4>>;

/**** Result ****/
using Result_5 = BiCognatePlume<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIGYAbFykAA6oCoRODB7evgHBmdmOAuGRMSzxiSlpdpgOuUIETMQE%2BT5%2BQbaY9mUMLW0EFdFxCUmptq3tnYU9CjMjEWPVE3UAlLaoXsTI7BwA9ABUp2fnF5dnhyYaAIInZwDUAJIs6fRsgkwDT%2Bc390eV2BVwBd1udwImHeBihJgAzG4oTCfpgEUiAJ7pRisTAAOgJCOwT2QBgUCieAHlscQfrkiRDFsQvA4nhY8B5gMwocoCmj7iZAlZ7k9RU9kR9UeiJbC0YimF4iAS8USSWSFMqACKYABueH2CgZIrFTJZBCeymIqCIACUmHQIWKnoLhXcnU7DocngBZLy0RwfTBPISYACOXkYBsd7tFnp9foD9CeADU2ngmLF6IbjTGZVL5YrUMrU8R05nMIb4dhozHTazta0HTn3S6azGxV5skZxVigwjNVSaXSBOjtXqo4iS2Ws0TlQz4a7287ApqEa62x6vb7/XhA8GwxGGFHm5uqZEU2mMzOT2K83CC0QL6Wr3LqzfRXXzQ37bR0VOX0abrtq277up2ETAD22LOvCA7Ugkw4MKOur6hWf6XuWs6ElWa4bmKgqrguEJ4aKd5ym4CpKgSdzAMQmDQowBCVm%2BQExuB3bKEwwB9rBTzfg6iI0XRDGCBq2HYCAIAEL2uHNgRsngs2ZHStCkr3hRhZzlWapMOSfEofsgFOp%2BFpWraP7IeOr5tiBrHunGlLniG4aRvydmntuiZBv%2B5bZu5t6qbK6KUUWBI%2BTOOGgSZ/G/qBtlLk67GQdJ0H9oOCEDJZqHoc%2BvlYSqOFEXFK4KSR4qBfmGlUXiQn0V8TFGe2SUWlxPEDjF6K1SJTFaRJUkyUVdnyYNbbKYiY1VaFBXEqSuliTVtF1YxzFts1dp0DBA6WtaqDrb%2BgmLd183zuuSkVepE0pTibC9Tp5JagZaGRXZJnbbaqBMOgNlCmVcaebuSYeN8KzEH5S5/QmANBtgnzLWVl29swN0EjDR2NbWBDMvWmCNrF/mivFCWis1V2beltKZYiY6oZWbio/VzG9QpS7Dad%2BNPBDO57kDjaRKDv1eo50Ow6J8PneRV1I8L3Xo%2B60U4xZiL04xstOoTRMk72ZPwRT9JU49tPK4I%2BUnWVrPEaBCPYlLypdQzqsdl2kHep46Bkx1B3CQzvWSVdzP4SVI1nSiF3i9KiO4rds16dThnPcZmNmqZO02h9X361Zsvq/Zgvnjz9p82D7ac15TxGw1lth%2BNEfI3i5crVFifY7jZs/aBiVO1BbXk4hWVx3TIsNVWTODSzgds0uVvXfi1GHfb8dNZ3Lu0G7aUe24dvLT7/XYv7BPjxbdmXVXmLW5H4l3fNm%2BiwvxOd6nn1k29u1p51c9b%2BJpUHwKgIgn//wQiBMcJ4AAxPAoNzTYFUKwPcADf7/3/mCYiZh4QRFJF4LAME3BoCPJgdIQ8WKAPOBeDEfxrgQgmiFQCJlUwYlKvA04Tw7joHQAALQSKgMhpwwSUMLK8ahTdzTMLYRwgAEn0GkxEhTOmbJrVKvFaHoheCdGR4Jv6KUhCfEKttiDAAbncZqwj2FWjJkYsREiEidV0cdKsvsBpsyAUwlhQsuHHB4VovhyjnomWEULcRtBJECmkatTupM0qKMRC8Z0lgnhcFNkEwibNeHVTuNYwChjnHnjSr4yI/jJGCWsdvP2QcHjEOEQAFQAO6cLgZokO5EQr8O8YIpx6AqmoDyZYoJi5HYQS7mTCJbgonWCeGYeJajEmH2SVNVJej0mdwqdU0xLD2mdOIFYvRRT7GH0cTrRCrj3H1PDmfWuAisbmj2ZTBxxChBeHSCUTA6AbQVgTAciEzVbn3KyI855ChXlpUuXrNwgyNBElICQ9EcSqzgsGWMwq1YSmON%2Ba82pa0Xn%2BlUWldknJuQqD5OiQFI5nqST2p1FhxjUDgpyZgKlKzqmAUkpxbi6JQWFWuc8cpFZzS1MWHSZAAB9OaCQCAQEWOgSSChcSCtpsi/04LPkPKeeiggRINj0NKQgxBRDnghhwW7KBMCky1KAZq0EOybl3MVU8WV3KwQfMtd8pVfz/T8q4NrIclNgVMDoYiKF2AYXevRHC/1ELETwnnAi9ljCbVvPuGi51BBXVk2xagLkqJeQ%2BHIoSpCxKQCksEpk6y9xGWtRZeCtIozxnasYZyxYsa7i8scAKoV7RRUEHFSASVbBpXohta6%2BVDqlBOoTK61V6qTWmuNcQ8pCBwH6ugTCIMU7J1mp/hqxhCrHXWuVfW%2B1Xyh19rMO6jKQKQVgtDW4YNAafVuEkBG8dxCY2ovvsq/lR6sUclTbijNbACUer1ixElisN7ko4bS9AQtwPtIZSAJl5ENDlvBcGh9HKuX1sbfqaVShW1iolVK3SvbX1mAHfun5RGx2IpXcCMEjiQE7HaAgMuC7YHkIYVR2p1bgHlN7GYkxtSp5SzLoPM5SduPYl4x0ix6zumqI7n0sJCjA1K0HpJHUYgIwqKkZMtdAnz41TSc9ZqYnMASbJsZiTayNk2L6sUqNXGeOFvrbptgQmZbNPOU8czhbLMyZCfJrW4SlMD26qp9TfYYl%2BrXJi9RFCT6Sz07M/RRmHMQaybxLzqXMCWYKZs8Sdjd6UY5Sl9pTm4s12lvVETrIMurKk1IiwsnendgUwOQZ5dQveHCw15DC5ovaY0c5me%2Bm5mGc7jVpZaVxuSYCZYnL1n8tyjs8GQdjzt0Jt3Z3TdB7X3wmPbrIlXqb2spDYMv116g33sK9Gndz6%2Bl9t28RXiKa008nxYibNMGH7pzcBlil4KMuQc88V%2Blubl7fdwyACIUJaJiH5Tg3lxtERQ/BcdqtbHPNoZ5a0JtWHhVto7V2zAPbET3ZI4q%2B7FG7PsbcZx0BeAqAEEYwaxd9aJ1UaQejrbq2n2sYMZtlbw6XWSD273ScQWzsXqvRe8N8KUPXfW7d7sfbhcfpxemt7bgPu5q%2B%2BiAHkQYNg8e24NsEOoeYBh7QOHAgEcqqR4IFHYKTftskmbi3VuGA2/RMj2Jjvmym8EOb2klv4etER24b3yGBRsvNahutWO%2BW45w87zt%2BGZWvukMt0jgvE13qrGqq71Oaec7wKoRnTHDVLt52zldHP13AK527Hn3D3n86z32/wIvPVnuhZL89gzc8IsjTH%2BXKLefxpHR31XX71eZr/SeolgG82v0RL9sDQPxOFv%2B8D1ABvXZG6dx213Qf3ee7twQB30KD8u4D27kPhhbfh/tz7y/fvk9H9h3fsPEfAJo7rxjuPvOGGza5IeOEOhOxObg7eZOjq7elOHAWwtAnA/gvAfgHAWgpAqAnAxulgIyCg9G%2Bw0S8IPApABAmg8BWwAA1gEJIHiBoJIFwIEPCBoP4BoCkMkGYAABwcH6CcCSC8AsASAaAIaoHoGYEcC8AKAgAIakFoHwGkBwCwAwCIAgA7AEDpCKjkCUBoDvB0AJBRC4icCqAcHJAAC0yQwuwAyAyAsSNBZgvAjyhAJAeA4qaQ/AggIgYg7AUgMgggigKg6gshpAugaQlStI6QnAPACBSBKBZBGBnAlIio6h5oqAVATwRhph5hTwlh1hUgeIR6EAHgOh9AxAhBXAGwvAMhWgWwEASA2h6QuhZAFAEAdRDRIAwAUgxGNA/oCQkhEAsQsRsQEQbQGIERvAgxzAxAGIlIsQ2gjQMhxB2h9UjktAIxgRWAsQXgwAFEtAtAkh3AvAWALAhgwA4gax4CcxeAOoFYsRmAqgjQioBwxBZuiBgRtAeAsQtIkxHgWAsRmMeAAh%2BxpAVxxAsQ3y2oRxRgbxRgZBWwVABgeiyYeAmAlS8EqBxBbhwgog4g3hGJfhagsRwR%2BgxxKA1g1g%2Bg7xkhkAWwqA%2BCuQexJhYq/YpgOBlgZgohwJpYWAlJEAWwDQTQzgEArgcwfgaQYQKwVQNQegJQOQAgwpUpWQMpDAowEpEw9QfQFxAgQwswngXQegfJAwWpywlQ4wiQ9QSwcpZpwwypJpEgvJ%2BBXhURHAyBpAIhvAYhaRxhZhFhVhNheRTwEAuAjhJR5gRB5RJBMJWwCAmAn0EwPJpAVBkg8IeIAAnPCIEJIHQWYJIMkEIf4MkMmTwRwHwaQAIUQXiKkMkBwcmRwVwMkP4PQf4KmckC6bEWIRIVIeGbIdUUoTUSoYkRoU0S0cUfoWwJwG0CwDqIECYUwDpN2FwMmXiFwLQfYfgEQJyXoBiR4didILiUoPiYEboMRqEUwOEfsY6c6a6XERwAkWoYqE8CkR6RkcLrNHOQuUuRoP6YUfUcUYQWYGGZUXIb2UOQkJoc0agEURMC%2Be0cmVwAhl0VCKDJQP0YEeMcMaMaQKhZMdMbMQ4OhYsYxMsasegesZsdsbsehYcccaccRecU0FcXsegbcfcVCOhc8bEW8R8cMd8QcOgX8QCcQcCaCUoOCVRRBDCXwPCQoIiciaiehZuViV4TubIHiQEegYeUSdCcyVYJYOSbENydSbSdbpwAye2kyaSayeyQkJydcVSb0P0LkC4AwO4DqYUKKU5daWsKaRkAqQMBad5aULkB5ZKWqfZZqeaS5SKXZRqYMEsEFaqdMMMH5byu0HFaaXabsPsLaYWRea2ZwI%2BV6bOZBPOYubQf6YGWuaUf%2BRGaQFGTGYkHGS8cWaWQuXQYEI2YEIwZIFmeYWkJeW2bYB2QBd2fAL2aoUkaBcBcQCOQcOOZkSwAoDqNYTqMVbKIsCuUGc4RubIFuYpT4fIHuapToCAPCKQMeaeZEdlTEYEWITeUkfeakaoHNQtUtStaiHWgUeBd%2BQkIQfCFVV2fIbUZ9Q0RNUDcUSAItfcvystcmfyqtYmo9TuXQAhb0chegZhascQejdhXMXheBUsQwCsbESRVsWIORYCZRZCTxQcbRY4PRTcXccgA8axQHi8egRxZ8RiNxb8aWPxbwIJWCdCKJdCf9XCVxFJUiSidbHJdtQpRIEpb4QdQScdRpcYOZTYBxfpRgYZR7pwIcLhlpdYGyW6Ryc4TZXGfqQ5YKU5X5WKcaZ5fKQFbKRFQ7YqalXqeqfyTFYlc7SFdFYaW7ZadqQUJFclUaasMFelXsA6ZdS2ddXlQjU8PNYtU8NDXiHDWVauSQJVRUdVbVVgPVY6U1UkAufCPCP4CwfQUIaXYEJWbHaIZwO2dIdVQmf4Cmf4BwSkMmZIMmYwWmVwCdS8fCFdfXeIZ2VUY6XYXXW6Q3WPeQUCT0Q5ZIEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/bi_cognate_plume.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/bi_cognate_plume.test.hpp)
