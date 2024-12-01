<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SensibleGauge`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-7">To Index</a></p>

## Description

`Varybivore::SensibleGauge` accepts a list of variables.
Its first layer accepts an operation and returns a function.
When invoked by sequences, the function places the variables into the sequences via a process similar to pack expansion;
then, it collects the value result of each packed sequence and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   Variable
-> Operation
-> ...Sequence<sub><i>i</i></sub>...
-> Operation&lt;...Sequence<sub><i>i</i></sub>&lt;Variable&gt;::value...&gt;</code></pre>
<pre><code>   ...Variable<sub><i>i</i></sub>...
-> Operation
-> Sequence
-> Operation&lt;...Sequence&lt;Variable<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>
<pre><code>   ...Variable<sub><i>i</i></sub>...
-> Operation
-> ...Sequence<sub><i>i</i></sub>...
-> Operation<...Sequence<sub><i>i</i></sub>&lt;Variable<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>

## Type Signature

```Haskell
SensibleGauge ::   auto... 
                -> template<auto...> class...
                -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::SensibleGauge`:

- We will pack `0` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
template<auto I>
struct AddZero 
{ 
    static constexpr auto value
    {I}; 
};

template<auto I>
struct AddOne
{ 
    static constexpr auto value
    {I + 1}; 
};

template<auto I>
struct AddTwo
{ 
    static constexpr auto value
    {I + 2}; 
};

template<auto...>
struct Operation;

using SupposedResult = Operation<0, 1, 2>;

using Result = SensibleGauge<0>
::Rail<Operation>
::Rail<AddZero, AddOne, AddTwo>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<1, 2, 3>;

using Result_1 = SensibleGauge<0, 1, 2>
::Rail<Operation>
::Rail<AddOne>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<0, 2, 4>;

using Result_2 = SensibleGauge<0, 1, 2>
::Rail<Operation>
::Rail<AddZero, AddOne, AddTwo>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::SensibleGauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables> 
struct SensibleClassicPlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // Multiple Variables
        // Multiple Sequences
        template<template<auto...> class...Cosmetics>
        struct Detail
        {
            using type = Operation
            <typename Cosmetics<Variables>::type...>;
        };

        // Multiple Variables
        // One Sequence
        template<template<auto...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation
            <typename Cosmetic<Variables>::type...>;
        };

        template<template<auto...> class...Cosmetics>
        using Rail = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};


template<auto Variable>
struct SensibleClassicPlume<Variable>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // One Variable
        // Multiple Sequences
        template<template<auto...> class...Cosmetics>
        using Rail = Operation
        <typename Cosmetics<Variable>::type...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCCSAJykAA6oCoRODB7evnppGY4CoeFRLLHxXLaY9kUMQgRMxAQ5Pn6BdpgOWQ1NBCWRMXEJyQqNza15VWN9A2UVEgCUtqhexMjsHASYLCkG2yb%2BbkxeRAB0FwBqTXhM0fQKh9gA1CYaAIJjxF4Oz0KMGXumDcBgUGWQylymDe7xMAHYrB9nsjnttdvtoUc0XsmAcsQBPFKMViYC5nJ7PZCghTPADyROIuKyTxhKOeXx%2BBGeymIqCIACVUEx0KyUfDEe82WyAPTS54AWS8tEce0wz2uxFuQMeSKlyNlCqVKvof0wAEcvIwNjrJXrUTscXi3NiMYdjqdUGSKVSmGCyR4FGxHMhHv5sKK9RzfgARTCNOgRqXixN255eDJGVGEtWHaN0hlMgQpu1ugjZ5hsZ4BoN4ENujVah5PEAgMtEr1hw4S1Pw6NdmHF/VyxXKvCq9U3O5N3V6g208Kmi1W6EzqUu3GY50O11HE7nC7e6lV9I10yd1dsqNc2Px2hu6tx2ssi9ihGDqXpsLALNE17%2BPP0nEhYMO%2BbKluWJLHoGj5nm4DZTpgobYC2bakgenb%2BN2JZwn2mEDi%2ByLrk6RGbnunroS8Pp%2BhcD7Bkh76fpm/JMHQf55jeLF3kctG1goHbIa22b9quvbCbCq4kaW24buBRIVmh5JhpS1Jku8wDEJgOyMAQ9Grox36CsKbHcryApCiKRxqRpWmCHxFFiaJeEfPh7ySbuHoTpqCHPp8BDfL8/wMIC9Agr64KQj4m7wUCPnJhJ0nEQlm6ofJ/HKWF%2BZAXUPmXn5nImXyqCGSKIlvgRzxzgu0X0O%2BBojsaar/EuDDWu%2BblbuiMnufuimUSpNEnjBum2nq%2BnPMxrG5pljLZeVsnEpWPF1kc1WYgJqH8WJYE4Q58WdYl%2B3JRBbBpVRdlnFZmlsLZOUomNxXGTyhXFW6l02Tpm1ObCO1fTC0oAFSA0DwPSn9QMACrYEI4NA6DHwA8DiNw%2BJsJmP4YRUl4WB/m4aAtZgKQ6bFHztWRzwAJI%2BVezwAFpxKgvTEAOCJphm36ocZYzoC2YTbOpYgAPp4zMghurzpAUyymGvD9EowqTHmU%2Bevn%2BVy86YIzzMWKzX4/jm/7sgQ3MgLzmD87QQsCCLBBi4IEtK9g/1djLuFyyTSVumTDswtT4MAO4M%2BMNrijrmYc1NXM84IZuMhbwuNKLRzi5LYaA87jlu65HsEnJJKbR81OATNzK/fDcrg4hXIaC5Y1CF4KQFJg6D8ohRrGUXwEDkciaRyb0fm5bQUJzbSd2881dhqQPdG1HfOx4P1u2wQEsT47U%2Brr3psD/Hhgj24yer2nzkYZn92t8qxmBcFwLUrWEVsG6q8wi2L1HB32XKy/nFunTvKMxL6t/7PH9oHJo9FS6%2BSZMgAWYU4gEAgL3BQJIYGhjcC3BQRoJZ1wbukJu6CjRPEWLtd4BoK5jGeFwGubM/j10bs3c%2BBABZcHbgWWasJu4bxnn3Oegsd6J33mPQ%2B68RqG2NlveefC97J0oanYRuUxH9wkVbYeS8JZmCeE7Y%2B4YIFnwwcqJhl8AR4CBKFMEd8oSPwllUZ46jP4gFfm4d%2BJdwwfC/gmN%2B4RNYnxcjMYMKClDNAQVwpBbAUFunwfo6x2C6ERMYTI7ARCIGkMrjYqhutom4PoXoxhZgWFZWZMfNw08FE8Ljso3eqjx5PDkSiTeijeHlP4dIjRNTkR1NKQvFRo9l6pNTpo9h2jT7UNiQLXJU0r7GJCrfCEFijgaCsWonyL9zJuicUWOxE0uJuF/qAsgdJPHjAliAxm4DM6%2BNrP4uBQTjYhMwGEo4IyzBYNoZkx5hCuwcGWLQTgABWXgfgOBaFIKgTgRTLDWHZKsdYOY0Y8FIAQTQnzlgAGsQA/MkGcDQkguBwn8BoH5GgzAADYiVmAABxkv0JwSQvAWASA0PMgFQKQUcF4AoEA8yEWAs%2BaQOAsAYCIBAKsAgKRTjkEoGgXYdA4gRBJJwVQZKiUAFoiWSGeMAZAyAKEYrMLwJuhASB4G5lUfgggRBiHYFIGQghFAqHUNy0gugqh%2B0ZCkTgPAvm/P%2BYi4FnBaSnFFVyVAVBngKuVaq9VmrtVnFyRADwUr6DEFeLCxYvAuVaGWBAJAkqUjSrIBQCAOa80gGAFIJ5NBlRxHZRAaIProhhCaPid1vB63MGIPiWk0RtBdC5XCyV10CDzloE2h1WBoheGAMcWgtB2XcF4FgFghhgDiFHXgDS3QABuiEfWYFUF0U4mw4Wm2%2BQ62gxjGTto8FgH1fk8B0rnaQLdxBoi4NjIuowZ6jCIuWFQAwwAFCXDwJgP2gEAVwtNcIUQ4grUQdtWoH1Tr9BLpQNYaw%2BhjHssgMsVAhMsizqVVzXMphwWWDMMyp9mosCYYgMsTo3RnAQFcJMPwVQQhhEGOUYYVQCiZAEMx/I6ReMMDmEMSo1Rag9HGC0TwbQ9B0bqIzfo7H5hcdsFJ/j0wpMic45UWjUKNhLCpRwP5pAmW8BZaGxVKq1Uaq1VIGNzwIC4ANUm8w/guCpvhd%2B5YCBMDCmGDR0gqLJD%2BDOIkfwcJJBYrMJIIlDKflEuSCemlpA6XubOESrgRKyWJDJVl9FXAfnhaJaZn1LK2Ucq89yzNAqs1CoDWKgtRbE2yrYJwJoLAN1wiVUwdKmYuCJDOFwTFer8BEEo3oCD5roPSFg0oeDDrdBPJdUwN1c7PXGe9Q6ll/qRWnGeMG54HWus9b69%2BAbQ3MWOfjbmxNyb/BmE8%2BmnldXmtxHFYW1ACbhjHe6z6IwA2uDzIrdsYg1ba0OtbY25tpAofts7d2hwMP%2B3aSHSOoFY6J1TpnTDhdS6V0Y7XT2vAW7Z1At3fu7YMPj0%2BrPdEC9%2BIr2bCBbe%2B9cKn0vqUG%2B/HX5v18D/QBoDIG5Iw6m1By1s3ZBwftUCpbSGv3EasJYdD0RqPYdw1bTgBGjZEdQ6R8jcRKPbqw%2BJ4nDGmMyamEEBg6BtMLG44JuoGnUiO6yHb1T8nJN9Gd57gQin3diZmBMS3LG1OzGU6JwzCh9OWo2yZszvqOBHeIJ17rvX/vncG8NjQjnnPjfux5tN3nSC%2Bf8/EQLyXaUBEG1iuERW4S4skDF1VVQE/ldsJV57NX4B1eFYGj7b3iCtc2B1iNLAFAbq1Rui7GIxijZc0aybshpsS%2BtfIebMudABFICttbHqjPx7K36hrQaQ2j7VePyfzxp%2BDdn1yONX3btxHu/4J7fPXuP7zQPz/iaQCT4bgLDfgLHfjAinqqnwHQKDuDnWg2u2jDnDh2l2j2sjl9gOmjj6pjpOmIDjg%2Bnjh%2BszvOkTputug6hTsgAetTtHCekCnTgzkzjepqGzrwBzq%2BjsDzl%2BtVvzkwP%2BoBsBqBqLsvuLhIJLjahvghtvgYArnrjYHTmrsChrkFJwNKJHIrtYGRuZhRkasboFr7n4Ixjbs7mxqUJHg7oUFkM7jxnUAHnJjUGbvUOpiHjYRJn7lphHjpnJg4bkKHkHkpsYe4R5isGsAZgESeofttpwMniwGPhPlPjPhuOQk5mNiQAXm/tVj5n5lgOXhtilnSmYINv4P4D8gStigygUXCNlqVuEayh3pysXsFj8mFj8mSsSokEkLihFlwIECev4FtsypwEXmkUZrqpUX0dUV3ssE%2BhkM4JIEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/sensible_gauge.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/sensible_gauge.test.hpp)
