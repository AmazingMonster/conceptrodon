<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsGreater`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-greater">To Index</a></p>

## Description

`Varybivore::IsGreater` accepts a target and a list of variables.
It returns true if the target is greater than all the variables;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target &gt; V<sub>0</sub>) && (Target &gt; V<sub>1</sub>) && ... && (Target &gt; V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsGreater :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct IsGreater
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsGreater_v
{RESULT};
```

## Examples

```C++
static_assert(IsGreater<5, 2, 3, 4>::value);
static_assert(! IsGreater<4, 2, 3, 4>::value);
```

## Implementation

We will implement `IsGreater` using only `<`, meaning <code>Target > Variable</code> is expressed as:

```C++
Variable < Target
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsGreater
{
    static constexpr bool value
    { (...&&(Variables < Target)) };
};

template<auto Target, auto...Variables>
constexpr bool IsGreater_v
{ (...&&(Variables < Target)) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQSQQAOqAqETgwe3r7%2ByanpAmER0SxxCVxBdpgOGUIETMQEWT5%2BgbaY9o4CdQ0ERVGx8Ym29Y3NOW0Ko33hA6VDFQCUtqhexMjsHASYLEkG2yYAzG5MXkQA1AAqDcCYBKTnp0QAdK8Aag14TDH0CkfYJg0AEEpsQvA5zgBJBQAcWImCY22IgKBJgCVmB5yx5ymiLwyHOaAYU0wqiSxHOMVQnnOADcxF5MCjsec0RZzhBXs9zAA2XkQD7EL4/TAKVnHK43O6LRasgIAESOGNRCqVKJR212%2ByZxyeqElxFu90eZ1QXMFwt%2B/xRRJJZIpVJp0LhCKRAH1aer0Ryubz%2BRbvr9xW4DUaZXLFYdlSiAPQAKgTiaTMdjicu2CEl0TKeB8aT%2BZzqOBuMcyDdTAUSkaEGd8MR8SObgArA8zA9Dg9JP8QCB6d5MIs1cX6qXy5X4gQIGAwFDYXWkY3pOc2%2BcO%2Bcu4dsD2%2B4zB1GOMtaJwm7w/BwtKRUJw3NZrDjVutMKyzIceKQCJoD8sANYgJtmZ4AjMSQAA4QKbDQAE5/w0HkQI7I8OEkXgWAkDQNFIM8LyvDheAUEAMI/c8D1IOBYBgRAQFWAgkjOchKDQXY6HiSJWE2VQQJ5ABaHlJHOYBkAJKRnjMXhMHwIghXQPR%2BEEEQxHYKQZEERQVHUYjSF0LhSAAd2IJgkk4HhD2PU9P0vTgAHkzloghzlQKhzg47jeP4wTzmEswOQ8Jj6ApcxX0WXgiK0ZYICQRikmYsgKAgSLopAYApDbGhaCRfCIBicyYnCBoAE8jN4HLmGIPLLJibRqiIt9GLYQRLIYWgCo0rAYi8YATloWh8O4XgsBYQxgHEFq8HhGpaVFczSWqM5NjfcJtkQi9aDwGJ9NKjwsHMgghVQ3rSAm4gqSUeUdkGlajE/ZYqAMYAFDePBMB0yykkYQrlOEURxCU2T5CUNRzK0/RBpQW9LH0Vb8MgZZUCSLpiU4LipnQI55VMSxrDMbDDqkybofaToMhcBh3E8Fo9FCWYSjKPQUjSeHxj8bS6YKBh%2BmphYCaq2ppkZvQqhqbppnZwZyhGXo%2Be03FGhF%2BZymWBQHw2CQTI4E9MPMnCnM4ni%2BIEoTJBEjlcEIEhn0C4KruWBAESwBIIB/fxDmeSDDgCSQNEkYCeXQpseUg/ROGQ0hUNfZ4eS4ODIJAyOm0kLgm1dnkNY0nC8II98rtIijwqomy6Ni%2BK/NYthOAaFhaQCLimEJAwjA8yDni4Z4L3E02pJk2R5O%2B6RftUgGNN0Ns9IMwrVfVrDeBw6yaLOezHPLyvq9rwaG6blvvNQXz4nNswgsz4iwoireor8%2Bi4pPhLF6r5A66SyCuAw1L0soLKNOK/L3o/0rysqhx3tqowAgDUmrmVau1Tq3V3r9XOpsC8%2BAxqOAmj1VuqgZrbHegtDo5kVprXyptOBwVdrvUOsdTAp0BpGAuqAQ%2BfBbr3Ues9V6Z43y/W7opXush%2B7qQvEPYGl10ZWHBrgqGDtLxwwyD1JGBAUaHDRmDCwWMp44zwFgURCsOjc2cBAVwktggk1ljTZm%2BQGZkxyMY%2BmGRDGcwFvDHoYwzFMy5oLBg9iZjFFFvzXmjivG9GsfLFYaxlZcHHmZVOnBHjEArlXGut9V5cEbs3DQxsJJmwCiEy2h9ra2yGGIxCwdQ6N09gEROAQAiHC9pIXi2lJ4WVwrYDOIUSJkUotRWy58i4sTYmXKJrkWAKFpASWkCTnjaimGJVJHdtJsK%2Bhwj63DAYgA7CPQyvVQkp2wlZfOdkHKRJYH0gZQyRljLshAHyp8d4BUOPvJpR8UCXzPoXB5QxBlJCSB6BJboTnll6b3OgL9MrZVyqVL%2BwKyoVSqgAredVgGNWavAzAbUOpiCgftGBVDCGkAQdzZBU00HIFmpgwQ2CNK4PWnlAh21iH7VIakchZ0qHhBoaFOhTA7oPSei9N6%2B0ZkKQkJwlS/0eE6CWfw4wCiIYxHUeI%2BGPUYzI1BhjSwSjLwqLUfADRhNtG6J8dpSmHi5a0xMRkPRLN4b%2BP5polxbi9G2J5n4qmnipbeOyE46W7i5hGIVkrRS6zala3LgcwZdJjn1imCk9u5sMkH1CtkpgdtKCqwKSAMwjdDiHCbBBeO6F00BDghsqenB06EStqQX8gQRIlK4FISCxTXYVEDhwQ4YTNn1NuarUSBa6mZNjQdeIaRnCSCAA)

## Links

- [source code](../../../../conceptrodon/varybivore/is_greater.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/is_greater.test.hpp)
