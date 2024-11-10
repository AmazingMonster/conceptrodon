<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Cotanivore::TypicalPaste`

## Description

`Cotanivore::TypicalPaste` concatenates a list of packed containers. The first container will be used to hold the result. The result will be returned via the type alias member `type`.
<pre><code>   ...Container<sub><i>i</i></sub>&lt;Elements<sub><i>i</i></sub>...&gt;...
-> Container<sub><i>0</i></sub>&lt;Elements<sub><i>0</i></sub>..., Elements<sub><i>1</i></sub>..., ...></code></pre>

## Type Signature

```Haskell
TypicalPaste :: typename... -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Examples

Here, we paste `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>` together:

```C++
using SupposedResult = std::tuple<int, float, float*, double>;

using Result = TypicalPaste
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Cotanivore::TypicalPaste` first reduces the number of parameters via recursion.
When the number of parameters reaches one of the base cases, the function utilizes partial template specialization to extract elements from packed containers and place them into the first container.

A simplified version will be as follows:

```C++
template<typename...>
struct TypicalPaste {};

// Base Step:

template<typename PackedContainer>
struct TypicalPaste<PackedContainer>
{
    using type = PackedContainer;
};

// Recursive Step:

template
<
    template<typename...> class ContainerA,
    template<typename...> class ContainerB,
    typename...ElementAs, 
    typename...ElementBs,
    typename...Others
>
struct TypicalPaste<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
{
    using type = TypicalPaste
    <
        ContainerA<ElementAs..., ElementBs...>,
        Others...
    >::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzNIADqgKhE4MHt6%2BekkpjgJBIeEsUTHxtpj2eQxCBEzEBBk%2BflzllWk1dQQFYZHRcdIKtfWNWS2Dnd1FJf0AlLaoXsTI7BwEmCwJBmsmsW4EAJ4JjKyYAHTnO9gmGgCCg8ReDgDUACqHeKK0ykyDmE8mAHYrACACI7Ky3a43AD00KeFh%2BfxqmASIChULWGy2mB2e0OxzYT2%2ByAA1ph3LImMFopcofdHgRXu9Pt9frjiWSKYIqSFiLTIUCoU9hU8vCkjE8Dkd/rEQUSmKTyR5udS%2BbEITdAWD1ejbrCngAlTDIRYpABuSLWqN1N0xmyY20huyFIrt2NxUoJZwusWwT2QBgUCieytqqpupBdwrdDpxu09zDY51Ol39geDoZ50RsUcl%2BMT3tO2HobEEd1I/1uIrzRwLyeL60YBAsCkjVdd%2BZOyYA8gQENEFOjfXSCA9nm8Eh8xKztrtM%2BHcQ3SwQ7snLhX57yrLsl02W2vfRXe/3iAoD1cBRrq2LgsAa38dnKEycmZOWT9HTdq7jc9XN9FNR3Esm1Xc4K13QR9x9bA2y/asRWPAc13bYVLhAEBPXBdFQSwyE9QAKkIojiOhKFoSIl5sCEF4iNIgjiIYujNUhMxYmCAMvCwGU9i8TY4wvZibhvCUhF4nJySNBQvFoRlHyeQZ0HQghePoXFggICsqFoVAHU07SHXwit0AWCJVOHHU8KE8U70k6TZNlV8py%2BD8cSdNxcwUpSVLjNx1PXSs4OFTyMO83EtJ0jSnnCgz1w8ghFJCvjcWMrxTP4odsCU/FcME8ZHGQAB9H4lHqCBgoUE4isHXZbJkitRIScT0FqghLhmHKODmWhOAAVl4PxuF4VBOHcyxrHkhYlgfVieFIAhNE6uYSRAHrJFODRJC4AFYg0HqNDMAA2A6zAADhO/ROEkXgWAkDQNFIAatFIYaOF4BQQHu%2BaOC0OY4FgGBEBABYCASLwNIoCA0A2OholCE5OFUE6DoAWgOyQnmAZBkCeKRTjMXhyUIEg8EUlp%2BEEEQxHYKQZEERQVHUb6dD0AB3YgmFRQaut6/qFuezhuzB0HGVQKgnkRlG0YxrGcbWswnggDxofoYh/hmmZeC%2Bn7SAgJAocnFXyEofWYZiYApDMPg6DWU9KAiPmImCOp9k4WbHeYYh9m7CJtGNL7Zqh5duwYWgXaZ0gsAiLxgDcMRaHewaI/WQxgHEcP8GIP28AtBOnswVRjTBlZZvUio%2BdoPAInZz2PCwPnRzwG7E4tYgImSTAQWTowK6MBa5i0phgAUAA1PBMBZ7ta1d3hyeET5qekWf6bUPndBaAxe9MMbLH0Sv3sgOZUASKoE%2BRhTHy3qxLDMJ7UBb4gScwfeIDmOws%2BcCBXBGZpSECakpj6C0HIqQBDf2yMkEBDBJi9BiGMCo79qhDAaJ4Joeg34OHaEg6BxRAG2CQWAsYWD/4wIkK/SayxSEXQ4H1B6fMXriyRqjdGmNsa43lhAXARNVbmFiFwDWc0%2B5zH7EwLAMQX6kGWpIWIpwACcsQASSA2mYSQB07o9QOjIqhV1SA3V4acA6XADonRkSdQxq0uA9TkQdWh4cXpvQ%2BgIpmv0Aa6yBkLMGRtIaoGVrDeGHA6gsDNACZGTA0wpxxjI04XB1oE3wEQB%2BpNaZzyphIReshl6MyeroS2bMObT25tQ3mtiBbuJFmLAJQSQlhIlFwSJ0SNAKyVgbaIatYhmH4VrTqOs9beOaWQCGJsVYgAqcEgMKdalcHujQGSA47YOydp7aepB3bO29r7BwSzA5NmDqHPmkdo6x1oPHJZWAWApzTk9DOWcc583zoXNYSzS7dXDhXKuzta4rCeg3Jus0W5tyUJ3M53dbx9z4AYIeo9x6T0YEs2elNxA0yXkoFe4dsn6BTigaw1hd4RGfofY%2BaRT7n1lJfawN8hr30fni1oCCXAMApJkH%2Bf9CgkKARAqoBDSDAKqNg6YcC2gCA6MMFBowaUYMFUQllODYF4M6Jy8Y9ReWALIYsChfCqE0MekNTgTwRlVLGTUup60FacPia0vhmtBGkGEaIygBTtG6MiRtAEliATbUkMotGLQtX81erYBxnTnHwFccDYWnjBm%2BLYJwAJUsWAKDNNjM0tTTjYkGLErhJM9BwvnqkpJGTV5xFILkzmPACmaroSUkGYMnii11cQFgsb42JuTamxkitemm1abEDpoLXERv6cbDtQyE2NQKkmmRBVW1FXrWjK2MzbYQHtuHFZizE4rq9j7P2mzvFBxDmHS5mAo4xzjgnWapzzmfN4FcjBNzw53JNA8xOTzy6V2rvsD59cH4/N4H89ugLzkgqcWCweI8x4TynonbNKTEXpORZk5msR0WbyxTvV51Kj4n04NCTypLr630pVgal6Cqh0oZaglozKejSvAbkNInLuVpCVTK4jmC5Uip/ixiVExiHUcIWxxlaDJVUb5SqqalDnnluKRwOtDb0ZxoTU8cdKbYyDBNXEkg5qe1OKEZgERfRxHPIdSAMwkTYixB6ntTad0zMAiMTY2%2BnB7GfStZInqsieonUOjIyQMjtryK4Ih55sQikOb9YGgp%2BN7ParC1aluKRnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/cotanivore/paste.hpp)
- [unit test](../../../../tests/unit/cotanivore/typical_paste.test.hpp)
