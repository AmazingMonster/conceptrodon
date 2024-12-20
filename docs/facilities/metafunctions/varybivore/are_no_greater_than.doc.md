<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreNoGreaterThan`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-no-greater-than">To Index</a></p>

## Description

`Varybivore::AreNoGreaterThan` accepts a variable and returns a predicate.
When invoked, the predicate returns true if all the arguments are less or equal to the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> &le; Target) && (V<sub>1</sub> &le; Target) && ... && (V<sub>n</sub> &le; Target)</code></pre>

## Type Signature

```Haskell
AreNoGreaterThan ::   auto...
                   -> auto...
                   -> auto
```

## Structure

```C++
template<auto>
struct AreNoGreaterThan
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
template<auto...Args>
using Metafunction
= AreNoGreaterThan<5>
::Page<Args...>;

static_assert(Metafunction<2, 3, 4, 5>::value);
static_assert(! Metafunction<6, 2, 3>::value);
```

## Implementation

We will implement `AreNoGreaterThan` using only `<`, meaning <code>Variable &le; Target</code> is expressed as:

```C++
not (Target < Variable)
```

```C++
template<auto Target>
struct AreNoGreaterThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Target < Variables))) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Target < Variables))) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQgZgCcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmAMxuTF5EANQAKi3AmATH2CYaAILjxF4OFy/EUagA4r8mDtiFcEIZni8TAErK8LvCLjs9gdMMdTudUAA6bEANRaeCYMXoCkekIRF3enwIF2UxFQRGUTDuZIR0NhL3J5NmjmQFzQDHGmFUqWIFxiqE8FwAbmIvKi4Zz4WyLhBsZjzAA2TUQBj0lU3Yh3aloi544gEomYBRLG0XaEAEWO7PJDqdLKVCvhSP2wNRJzORDVL2Av12jAIJKOT09Fy8mSMNKZmDtR3tNLpDKTaODobYggUatJR3Z7sRux9h39GLVZotxNJMe5eF5/MFwtF4sljLuAH0pXaY8rVdjNdrddSIAajSm3Kb8YTiTalnaAo7i5DXevXpCAPQAKgPh6PO93h6u2CEV0PJ9e%2B6P95vUNe3pRaIDWOxP2AkejLzj4WAC4AFl7iYKgvAYBxsg3VNvl%2BSIASBEEwQhE4AFYGxeEAQG7P03C/AsRyjN1t1eJtkB7JgFCUVoIBA5pwMgho0TMUgLiONjpAuDCo2wmVvEwJYSLeZoeUo6j4gICAwDAYDQMYqCBDRDU2NY9jHj42VBKdDgVloTg0N4PwOC0UhUE4NxrGsCk1g2ZNzCOHhSAITRdJWABrEA0LMTEAjMSQAA4ArQjQkm8jQNQCjj9I4SReBYCQNA0UhjNM8yOF4BQQGSlyTN00g4FgGBEBANYCFSc5yEoNA9joeJIlYLZVACjUAFoNUkC5gGQXkpExMxeEwfAiHNdA9H4QQRDEdgpBkQRFBUdQ8tIXQuFIAB3YgmFSTgeD0gyjNcszOAAeXOCrqVQKgLmatqOq6nqLj6swVQ8Wr6FFByuCWXhcq0FYICQGrUjqsgKAgYHQZAYApFYmhaBBLKIBiI6YnCFoAE9dt4NHmGIDGTpibRMAcbHSBqvMCBOhhaCx5asBiLxgFOWhaCy7heCwFhDGAcR6bwX4oKlK0jqFEnzi2Jzwh2GLTNoPAYi2/GPCwI6CHNBKOdIYXiHFJR7V2Hn5aMVyVioAxvxxPBMHWk7UkYMmJuEURxFmp2FrUI7Vv0HmUCsyx9AVrLIBWVBUgadnWvGdBjntUxLGsMw0p10aRZD7oSYaFwGHcTwOj0UJwiGSoRjWoosgEKY/DLjIK4YeZhgSNa7Ez3oJjaPP8mbupW4EPpWgbkum9sduq70WYB6LhZS5WBRbM2CR9o4QyUqO9Kbpa9rOu63rJH6lVcEIEg7TMRyfuc02VgQTAmCwBIIA8/wjkxJIjgCSQNEkfyNSStCNRSGKcVSAJUcpiDUXBIpJAChAtCkguBoVfipVKvB0qZWyhfPKANiqA1KudSq4NIYfQamwTgLQWBSgCK1JgfIDAJi4EkTEXBMSmSGkfUa41ZBTVdtId2ShPbLV0KxTa21sZLxXsg46HAzrlXOBcK6FwyEUKoTQnmT0GFMI0K9VA714gnyOGYc%2Bf18o4MIfEKqENtEgw%2BiARRlDkC0JhkkLgyV4aI0oCjZauNMZky8fjQmxNSZawpuGamtMjoMyZizNmZMuZGy2KZfAgtHDC3Ziw1Q4sdhk2lnUI68tFaYxVvE36GsyY6z1pgA23MjDG1AJgvgFsFBWxtnbB2WsnZcJmjw2QHslqmUET7E28crABzycHB%2BZlw7ZEjtHWOQzE7J3iKnMZs8e6KT8BAVwY81qF3KI3PQ5cGhbLSLXBog9Fjdx6H3Uendq4ZzWf3AYU89nN2uXkW5E9Hm7KHovVY6wF7fX0AdVey1162OUfY1R9DGHMIPsNY%2BX1DGX1INfW%2BIxxmAPiiAI4DDP4BAQQEAIRwv6SA6mtCRqDbDoKMVg%2BAOCyoXXMaY4gxCthkPuiwBQUpeRSihSicYg04XsLWu0l2nS5ryD4b0nQWKNpbR2hzMRh0QWnTwZda6bLOocq5dKXlvpxhaJ0Z9U%2BRxEV1JMZY0GjKLXWK5akVIfZ6E9j5QQSixAWAdT4HQNxyNUbo3xj4v1BMiaZzJsEwQoS6YJMwIzZmYhola1idUoppBEmtxSaLdJyAJZZMEDk5aeSlYY0KWrEpWsykZAqYbapAFTb1KZI062tt7bGSciK6aEgunzUlV7GVDi/YJxGUHeAodJkCHZjuaO/bhkWCTiglOeAsDLLuVnDZOcjk7OLuc45xRshHIOdkM5pdl1t36Eclu9z26HuHh8s9l6nnfIBXPP5M1FXArSpwBRbr2Wcu5bqnY%2BqICHxGno76v0kUorvpQJeQCErJExEcI4aEQpwKSghgIkU30oM4GgnKSLPKBH6nirgUgki4tflwIIMUjhKvfRlDB/0l4DUw5IsDmCVg60yM4SQQA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/are_no_greater_than.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/are_no_greater_than.test.hpp)
