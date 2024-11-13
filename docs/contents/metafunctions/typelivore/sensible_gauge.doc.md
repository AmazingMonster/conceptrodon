<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensibleGauge`

## Description

`Typelivore::SensibleGauge` accepts a list of elements.
Its first layer accepts an operation and returns a function.
When invoked by containers, the function places the elements into the containers via a process similar to pack expansion;
then, it collects the value result of each packed container and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   Element
-> Operation
-> ...Container<sub><i>i</i></sub>...
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;::value...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Operation
-> Container
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Operation
-> ...Container<sub><i>i</i></sub>...
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>

## Type Signature

```Haskell
SensibleGauge ::   typename... 
                -> template<auto...> class...
                -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::SensibleGauge`:

- We will pack `std::integral_constant<int, 0>` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
template<typename Element>
struct AddZero 
{ 
    static constexpr auto value
    {Element::value}; 
};

template<typename Element>
struct AddOne
{ 
    static constexpr auto value
    {Element::value + 1}; 
};

template<typename Element>
struct AddTwo
{ 
    static constexpr auto value
    {Element::value + 2}; 
};

template<auto...>
struct Operation;

using SupposedResult = Operation<0, 1, 2>;

using Result 
= SensibleGauge<std::integral_constant<int, 0>>
::Rail<Operation>
::Road<AddZero, AddOne, AddTwo>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<1, 2, 3>;

using Result_1 = SensibleGauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>
::Rail<Operation>
::Road<AddOne>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<0, 2, 4>;

using Result_2 = SensibleGauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>
::Rail<Operation>
::Road<AddZero, AddOne, AddTwo>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::SensibleGauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements>
struct SensibleGauge
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        // Multiple Elements
        // Multiple Containers
        template<template<typename...> class...Devices>
        struct Detail
        {
            using type = Operation
            <Devices<Elements>::value...>;
        };
        
        // Multiple Elements
        // One Container
        template<template<typename...> class Device>
        struct Detail<Device>
        {
            using type = Operation
            <Device<Elements>::value...>;
        };

        template<template<typename...> class...Devices>
        using Road = Detail<Devices...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<typename Element>
struct SensibleGauge<Element>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        // One Element
        // Multiple Containers
        template<template<typename...> class...Devices>
        using Road = Operation
        <Devices<Element>::value...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCCSABykAA6oCoRODB7evnppGY4CoeFRLLHxXLaY9kUMQgRMxAQ5Pn6BdpgOWQ1NBCWRMXEJyQqNza15VWN9A2UVEgCUtqhexMjsHASYLCkG2yb%2BbgQAnimMrJgAdDfY9GyCCofYJhoAgmPEXg4A1EKMGWi9AA4kwvMBMK83iYAOxWd4/RE/ba7faQo4ovZMA5HMFEG5XZ4/ZAGBQKH4AeXOxGxWWeUKRP0%2B3wIP2UxFQRAASkw6AykbD4W9GYyAPSin4AWS8tEce0wPzuO0YBCeCJFiPFUplcvoPw8gl54WIauFGuROyxOOOlrRh2OZwubAJRJJTDJBIAIpgAG54DZPfwvdUa5m/b2NPkhkWC/nmpFeDJGZGOn6HT2U6m0gRx%2BNpo7ev0B%2B1Kh6q54gEA%2BsRea43en%2BIXx2Gew5N825sUS6WyvDyxX3FWm%2BNainhfWyI1xTtIzF2jG27Hoh3nZjO%2BtB4mk8mF/3o4Nm0MEL7hzCR2j23cbenRxmx2/mxNhYAp875jNUuLZhgzjWX317iWg6PBWVY1nWhJBm2v5pjCraNlCMFzku9rIdapyrpcLqbm6Ho3FemCBge8ZPsmXKoEw6Dvj8Ea8heBYAQG2HYJWGHou2iIttB7y5mhy58faeKoMxW7ugoBJvMAxCYMqIFQdGpEvjydDUeynKoMp9FuJJ0myaqzHcdCcGGVCAkYo6a4KqWKo3h8x4sn8AJ4ECmCguCy7WYItn3oeFqoihC7%2BdaQkibh5KfjSdS2YyYasmp3J0bmPkjhKY5WcBBAwVqPa6gqBqRsaw7mmZNpBfxFlYRu2CiXhVwEURMGKT85GUdREXfjB/5FoRQF6aB1beBBDYcbB8FCrxi7oZNy4hVVNXiTcOkyWWDUKUmSl0apHIJXyRxLXpC2QS8CE8cZJ3Qu8ooAFQ3bdd2ilC103QAKtgQjPbdD2XXdP1XV9F3QmY/hhCSXhYPmbhoAwGwpOW8kAyVbGWQOfXw7FPxvOg6AAFpxKgaanRYBO%2BTMjjIMSAhjJgqgpMQPxCT8A21klcKeQQlZM5CZ1E4h3OIe8iMVWwKNlrZ6OY%2BgaW8zz0ak/6FMMFTNN0wznMsxYbMc%2BBaaWD8XBcY2xMG%2BNAvTahQvpajB7i1jz0AO6oNLxMxY0ZMK0rtP014RCM%2BB6ua2Bg060TZjG0bfM8abZWCd7wlVVC6PtVF52PRKz2EayGj828TVCF4KQFJg6BcoROptVmyduBopB6zXodQSn7xNSXChl4h/gZv8ivOSCYIQvaYzoJWYTbFJYgAPpQzMXlHCPNdZw3B6Vpp9pJ3S8PLxR6D2hLuMcjXEtpQftsO8N2dy8g49iXEBAQIPlYKJcV%2BBm4Lc6jXecF%2BkRdv7KzyLCZS6acM562zrnfOhdi6l1lOPLg5cvyVyqD8MwNd/Bn0jjndazVoEEFgdRLugJe7uXtLme%2BIAR6YDHrQSelNGgzzcHPH4C9sCkFIQQIe5DBCUJpNQqedDMqz0EDXfWQZWGy3YcPLhVCaGK34faRh9cDy2WXolI4a8cwbxAC1bee0sZSwbibOytJL7X2aHfCRIBH5sGfvaX%2BuCkGf0gXY2B/9AFvC1OnMYyCwFYMcd/KBrcYFmHgZFdeVc6410kOggGzccHj2CemRy3cXJuX7kcNhHCKHSL4YYARDChFMOeGIkmFisk8JkdPPJjCREsIyZI0e5Scn0IUd5TRK81EV3XkvLRW8d5Yz3qgY%2BktwhDPto7Ax59Xb%2BmfkoMxZCrGYBsUcZxKC/gQP8Ss1xjYODLFoJwAArLwPwHAtCkFQJwNw1hrBMlWOsBU5h/A8FIOzE5OzlgAGsQD7MkFcDQkguAwn8BofZGgzAADYwVmESMkPZHBJC8BYBIDQ1djmnPORwXgCgQDVxeVoZYcBYAwEQCAVYBAUje3IJQNAuw6BxAiJcTgqhEhgoALRgskD8YAyByZSCuGYXgRdCAkDwEPKo/BBAiDEOwKQMhBCKBUOoV5pBdBVDtjSFInAeC7IOUczQvB0UUm9uS1kqAqA/CZay9lnLuV6x%2BcEiAHgaX0Dpg8rgixeC4p2aQCASBqUpFpWQCgEA/UBpAMAKQKCaCyjiFiiA0Q9WkGiGEJoJxNW8CTcwYgJwKTRG0F0F5TzqVljHLQVNSqsDRHBG4MQtAsXcF4FgFghhgDiHLXgaS3QfSEQTdTLo3tNhPIobC05tBnI0izR4LACbjx4ERfW0gXbiDRG/t6JtRhR1GD1csKgBhgAKAAGp4EwHbT8xynniuEKIcQMqL3yrUAmlV%2Bhm0oCuZYfQzksWQGWKgWGWQ60ssHumUwlhrBmDRYu4gIru1fuqLULILgGDuE8G0PQIQwiDHKMMKoBRMgCEmH4bD6RcMMDmEMSosH809HGC0ZDUwKPdAEL0ZopHMPkZmBMWjBHbDUZYwsN1Kw1gbCWPoHVpBUX6s4Oa5lbKOVcp5Xan4EBcBCpdUDN1Hqt3LAQJgSiwwIAfISP4K4ABOfwMJJB/LMJIMFyL9lguMyJuFCKAhcCuGCrgYLEjGcSB575XB9mmbBWJhN6LMXYueVu71RKfUkqNRSoNIbnX0rYJwJoLAfQwhZUwUSyYuDGauK505gqiCQdFbKy9UqJDSFvUoe9SrdAoLVUwDV9btUcEOcFpVBq4smrNWljLWWcsvjywV35inHX%2BudTrfwZh3URdefi31qAnVxEpcG5bk3hj9cy26IweWuDVyjdsE0lB41KozSmtNibk1ZpzXmhwV2i0qhLWW05Faq01rrU8xtzbW1vfbZRrtdaiuqD7dsK7Q6E2juiOOk4k7NinJnXOp5i7l1KFXb958kWd1MD3Ye49p6rsXslde6rsg72KtOQ1p9m7gNWDfdDz9%2Bmzm/sppwAD7CgOvosGB/VEGoNM%2BWJ0BjfgICuHw6hxDvGsOpCI3UCXhHChZGl2xmolHGPUYV/RuoTH%2BjofmDL9jNHchcaNyr4TChblCf47Cjr4mzmSe24N3bw38uFcU8pkr031PzbxVpnTWB4jM9hfC0giL/D5b%2BTCALMJAWSCs%2Byqo9vQu2HC56/F0WkCkuNWtxLdKGUcDS1algCgfTkx9CNtEYwBX4BKyKvQxOr3SrJ3K2rlOdABFIE1lrWrHN25C5wQ1ZLvY/FNfTYgLBi%2Bl/L5XpcXiHUbYDdN/wc30/eqWytwNVLF/OqrMgAu48K/GfHlX3BRfqt0GO7Gs7pyLtZqu3f7Nub82PeW8WhgpaE3veANW2gtars/broI4NoA6drdpKq9rID9oQ5cLDq8DQ6w7w7TqQbI68Co4ro7CY6boLZ8C7oHpHonqrhE6yAk7N7lYU4Pqd4GC07c7vrRCC4s51B1qij3x06gbgZxClbQbM7C51AIZIYm6S7oDm6K7EZa44Z1AiHa5UZ9Ba68EyHMb65kZ6BG5yE8ZKGsYW5W7Sptb95daO4T5T5l6Myz7bDz6e4kDe6r6aakDaa6ZB5tah6IpmD5b%2BD%2BD7Igr/LIpuEwieadZoqcBhY4o2GfKSD7Imb7KJDgrGaSDGaApmZcCBCwr%2BC6r6EYq%2B5vKOb8r%2BESbpHp7LCLoZDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/sensible_gauge.hpp)
- [unit test](../../../../tests/unit/typelivore/sensible_gauge.test.hpp)
