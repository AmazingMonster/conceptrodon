<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Among`

## Description

`Varybivore::Among` picks out the variable at a given index from a list.
<pre><code>...Variable<sub><i>i</i></sub>... -> I -> Variable<sub><i>i</i></sub></code></pre>

## Type Signature

```Haskell
Among :: typename... -> auto... -> auto
```

## Structure

```C++
template<typename...>
struct Among
{
    template<auto...>
    alias Page
    {
        using type = RESULT;
    };
};
```

## Examples

We will pick the variable at index `3` out of the list `0, 1, 2, 3`.

```C++
static_assert(Among<0, 1, 2, 3>::Page<3>::value == 3);
```

## Implementation

We will implement `Among` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the variable at the index is returned. Otherwise:
  1. Drop several variables from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `Among` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<auto...Variables>
struct Among {};

template<auto First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { static constexpr auto value {First}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>::type;
};

template<auto First, auto Second, auto...Others>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    { 
        static constexpr auto value 
        {Among<Others...>::template ProtoPage<I - 2>::value};
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { static constexpr auto value {First}; };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    { static constexpr auto value {Second}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQBXKQADqgKhE4MHt6%2BIADMKWkZAmER0SxxCf5JdpgOmUIETMQE2T5%2BgbaY9o4Cjc0EpVGx8Ym2TS1tuQUKE4PhwxWj1QCUtqhexMjsHOZ54cjeWADUJnluyLPoWFRn2CYaAIIPjwSYLMkGb2duTF5EADogQA1Zp4JgxegKO4vWbELwOY6PFgCYCnADsVnRABEzlYni83h8vpgfn8iMcAGJ4YizGFPOEIghIlFGH7U2kEenPTEvY7845Ez5Mb7ndIAL0wAH1mQBJbkC46MxHKYioIjKJjATAYrG4vL455PRVCkk/CXSuUKgXETAARy8NMwCmOEHleX12I0Kz5AuVzNV6tQmu1P3d92NApMmKVTUcyGOaAYs0wqmSxGO5NQxwAbmIvDroxYOXScXiMfrDb7%2BaaRaTzlmgQDHsBbe9GARoXkI49FV50kZjiHCx6h2qNVr624W222IIFE27iAQAQAJ7JetVssGl6E97C0W/f7ZksEUiZ4/HIR1AToc%2BNoEAeQICHiXZ7/pZqPZNNm5%2BvSZ3scz6vrSi7druvKRjW%2B5mmKeCSjKxzhtWsbwiq47BpOpzQbqOG9oqfpxngCZJimaYZlmub5oWuGKkWyLfucIFvuB2DLrWbxjkGw5hscAC0xxmEuIB5t4pLboa9GSbuuGcVOFpIShuG2g6Toum6Zyet6qGfoGE6hucykEfyRaxiKJGJgI5HpheFJiQWuqntGlYVniskmYKsF1uaCGWsh1r8qpjq2hp7qelwPq4XpmG8UZgV4bMFmkdZbwUXZ2YOYWmIAbeLnlvlO4EnJ3mHg%2Bzatpg7bzgl/bhGiw6nKO%2BlYYZ06VdVnZse5BIycVjwAPQAFQjaNY0DS8w0jQAKtgQjTaNE1PFNY3jR5ewHEcI4XAI2zJJ23KwsRyBSkwChKC0ECMWy5waOeSRCeeeQiXFbjPd2y5ZU1nrHHkPpFY8HBrLQnD%2BLwfgcFopCoJwbjWNYSobFshZmHkPCkAQmhA2sADWASSACGiSFw6J5Bo/gaGYABsVNmAAHHT%2BicJIvAsBIGh3RDUMwxwvAKCAd2Y5DQOkHAsAwIgIAbAQyT/OQlBoB8dDxJErA7KodNU/xVOSMcwDIAmUgAmYvCYPgRDEHg6B6PwggiGI7BSDIgiKCo6jC6QuhJAA7sQTDJJwPDA6D4NY9DnCPv8svMqgVDHBrWs63rBvHEbZiuh4Sv0BmeyRbwQtaGsEBIIryTK2QFAQKX5cgMAUhmHwdBvLSlAxGHMThM0q6B7wHfMMQq6PjE2h1EL6OK3OBCPgwtDdx7WAxF4wC/LQtD89wvBYCwhjAOI89OvUObOmHqZ1P8Ozo%2BEbwgx7tB4DEfsDx4WBhwQltsxvpBH8QMRpJg2LvB3nfIwWM1hUAMMABQwI8CYG9o%2BDcEN0a22EKIcQTtkGuzUGHL2%2Bgd4oHhpYfQ99%2BaQDWKgfamR178SuFpUwlhrBmG5t/S2WASEQDWLUeozgICuCmH4JIoQFjlEqHoVI6RehZE8O0URRQJFDGEaMGo3RR4NDmHwvQnCJH9BaPIkYCQahqKkbkAxAxdFLH0RwpG2wJDBw4GDUgXNeA83jprbWut9aGwJunCAuBCAkFOKjPOGNQFrFfEwLACR2GkDxpIPIAIACceR0SSCJmYSQVMOb%2BCpvEpmHAWakDZmjAEVMuBUzpvEumpT/DE38IkqmDiw48z5gLYJwsi4S2LlLKOctK7V2zqrNgnBmgsBzOifiTBEwGEHFweJAIuCE1NubEgVsbayHtmg6QGClBYI9roBuvt/Y91sfYxx4cOCRxlv8Y4sdMzEBGWMiZhwd6p1mfMjQGdUBZ3iAEvIZgVj51AaLEunyy7Z3llXEFNdhmjP4k8owMyuB3RoLQZu/MIBtw9n3LuPdSBYoHkPEeDgcUTw7NPWeYcF5LxXmvHFW8gE7ChvgW0h9j4e1Psgc%2BOKr7dDDnfB%2BXdn4Mvzu/HF39f5KAAdvIwwDQBtL4BAqBMC4EIJxcg9ZjtNmyEwe7KGezcEgLoVYQhfK2FkIodZTg1CCDoFoQQiwjCnHMKtsfUhXQeiZBcAwdwRj%2BHBC9WYkRSQxHFEkTkX1wa5FCL0Ro5RXCGDaNaD6mN7q%2BhzADYo8YAx1EmJ0VG8xNj1ibGsZFXJJzGmcFufc8ZkznkzLmYTV0viLY/KCQXbGpAwkRMoLY/JhTZlE3RLU9EpNJBpJ1kkU5TTbAtLbe0%2BAnTpbR3BX0lWashl3KTiwBQOYEw5jrSSWYiy/EsNWXbVBGrnbyG2TqnQ%2BRSAHIDhvY5ocPY8wudHa5cdhmbu3bu/ddZZgfK%2BTnVGf0AVys6SuiuCtIXZ1EsgZIyQpR7viVKA9BBTobs2U3N8rd26dwHjivFg9h6j2JZ8yeZK56MswIvZeYgaWfzpdKoVpAmUqKPuvKG7LOWf25TfKGfLH6rkFa/EVn8xV/0lUA%2BqgLwFakVbA%2BBjBVVrPPRITVLtr3YLvVM4wdqiExFNdDc1yZOADSuPg%2BhlgHXQydaw%2BAHDY0SM9d6sNehBFlGjUG2RmRs2FHEZkdN%2Bi3UqNTVmpNSiU3xrTXmwNmbJiRYS/MLz%2BaS0KCsY7Z9DTX0Vu/brLdO7cz/reIBnxSyQNo3%2Ba0wuoTMDhNGFEm%2BvaQBmFmXkPIgQiaIo0B19EZScvc04M0wWITokgEkP4BJ/g6bU3iZIeJpMklcAKDfPIL6hu8xq%2B2m%2BJtBtOOG9tlYaxv7pGcJIIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/among.hpp)
- [unit test](../../../../tests/unit/varybivore/among.test.hpp)
