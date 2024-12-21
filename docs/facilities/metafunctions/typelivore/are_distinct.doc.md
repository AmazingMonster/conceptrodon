<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AreDistinct`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-are-distinct">To Index</a></p>

## Description

`Typelivore::AreDistinct` accepts a list of elements. It returns true if no two elements in the list are the same and returns false if otherwise.

## Type Signature

```Haskell
AreDistinct :: typename... -> auto
```

## Structure

```C++
template<typename...>
struct AreDistinct
{
    static constexpr bool value 
    {RESULT};
};
```

## Examples

We will check if `int, int*, int**, void` are distinct. Then, we will append `int*` and check again.

```C++
static_assert(AreDistinct<int, int*, int**, void>::value);
static_assert(! AreDistinct<int, int*, int**, void, int*>::value);
```

## Implementation

We will use a technique called SFINAE, which stands for 'substitution failure is not an error.'
It roughly means we will create an 'if statement' for template instantiation, where the condition will be the legitimacy of an action.

In this case, the action we will be using is accessing a function in an overload set.
The compiler will select different partial template specializations depending on if it can find the requested function.

We will use `Label` to create an overload set for `lark`.
We add a second parameter in the template head to distinguish identical elements.
This is essential since inheriting the same class multiple times is an error.
Unfortunately, using this error for SFINAE is impossible based on my testing.

```C++
template<typename Element, size_t I>
struct Label
{ static constexpr void lark(Element); };
```

Here's the entire implementation:

```C++
template<typename...Elements>
struct AreDistinct
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set through inheritance.
    // Since arguments are not allowed to have the type `void`,
    // which shall be a valid argument for `AreDistinct`,
    // we declare the parameters using `Elements*`.
    : public Label<Elements*, I>...
    {
        // We bring every `lark` from its base class
        // to the current scope.
        using Label<Elements*, I>::lark...;

        // We will do SFINAE on the second parameter.
        // The default argument `void` ensures
        // the compiler checks the specialization
        // before the primary template.
        template<typename, typename=void>
        struct Hidden
        { static constexpr bool value {false}; };

        // This function checks if an element
        // is in the previously provided list.
        // We ask the compiler to find a `lark` that
        // declares a parameter of type `Element*`.
        // If the compiler finds the `lark,`
        // this specialization will be used.
        // Otherwise, the primary template will be used.
        template<typename Element>
        struct Hidden<Element, decltype(lark(std::declval<Element*>()))>
        { static constexpr bool value {true}; };

        // We check every element using a fold expression.
        // It returns true if and only if each element
        // appears only once in the list.
        static constexpr bool value
        {(...&&Hidden<Elements>::value)};
    };

    static constexpr bool value
    {Detail<std::index_sequence_for<Elements...>>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwA7KSuADJ4DJgAcj4ARpjEAQDMpAAOqAqETgwe3r4BwemZjgLhkTEs8Yn%2BKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BzmSRHI3lgA1CZJbl6OtIQAnufYJhoAgvuHx5hnF8hz6FhUDyerxeBEwLFSBlB5zcBFuqUYrE%2B2HobEEpBOmQAXpgAPoEE4ASUBLzmxC8DhOoSY8VoQJMgQsGOajmQJzQDDmmFUqWIJwAbqg8OgTgZiABrCDIsGMAirc6M%2BkAEXldJBYIhTChF1h8OYbAAdIapaiCApic9SeT8c9iJhFXg5ocCHSGUCTu6TqDwZDMNCdQi2OaPUyyRTFZhmnQzq7AsqklYXm6PV6NVq3FjcQRDfqiUlHi9g5awxGmHRob8QCAIlhVDilABHLyMHbQgnZwF5pPugD03ZOAHVPshbZrPoYTqg%2BQlaKgmMKlPiCAhiJtgAgThEEAlCIYdvquydeychIcx8RgD4ZQoTi1PgxUPixDOAO6YYVEE4IJhTz1bz1wz4TH8DQBSFICNFIA8j2fBA8GQdcFC/WhaBOeIb35MQhRvc9L0EE5%2BF5cCbTtB1HAYBxwMggsPWgz4sCOW9f0%2BVIWkRUFiGvLxMiMM5gONK8ACpwP3aj3RAE5Ui8WIblZKkaWhfjBAUAT0VzbB21E6ME2eYNgyPQdUOICJgBOTAp2IW5eI0UUxXA/CVxYDdTVQpglDZAwFDNTS9L7D8lyHLZbTwhQ0HhESdN090uOMylqR6BSUUE1SHkrGz23jVUIsi/TPmfOgUPQVBjwAMQJKJnmwCcGCYjF6gEYUWOINiEnCyKez7AAVP9/iYLxaEfHCTSs0D0DsxgFC2TAvKy3Sj38tlUHBOgEjZLdkDFa95oUeFkDwTDMU1bIDx81DMAIz55p5PAWBaSyUx9Vq2vu0c/QAvVMHRf13vORURqDNqi3xAAJIUsAYY6PXpRk5kO1l2U5bleViVBPAw7xAIZKgxCUJV5WjONtIh9qTi6h18K8ci%2BlW%2BoNo3Kgb2qnppUEInDz7MmIhqnkzKcLjaEsnlJyFN8RVIx7sr7AzXLFGq0CW%2BheQ/GgGGFJgrJsuyl01Vmj3o0UpvQxrmt5VB6f9KzFIIITgPF2a%2BwJM2/zl1Jlt5ZX0E2v9wJsyDgJ13zYOvbb6j2m4DqpvLkNOk4uLfW2ToAeX84g8qUT6/yum6LM9dUfROSOULQ2P0Hj5Nc5e7U3sRE5Lf%2ByLAZOEG/kYBLmYIdE9f9CAbIgCsQD1vkxFbk0hLzCBVgnuvdKhplYYWjlQUR1CUZQwf0a0ggyV9WM8dxjLE28mjJaHNaZbMhJLKZobop4tX%2BFoYUuW5zzslL4mCXxW0CC2DlPS3umGbCgEPzABmAmDwVMolFmh9iZMFSPCFo15gGWQEDsDc1V5o3DmG/WeLJ54Ix5MvVGa8mysyhhAdsZh/DmH8E3MGw8rwpRACQzAcod77xmnvQmmkYZ4PhovQhyNiFiFIZpKG4ZIy0guH3asXI6yYEbM2XEBEGFKXSo8PMlYWFcJdATTK3YBKGKMcY7sQIDGGI6tgIQHUjGmJeOY4xJjMpvHIh8L4bh2Q7FSKac0QJeFwRxK5JQrQIDEXtI6Sm0IIjt3QVbdE0TDHoj%2Bpo5hIjWEqhJMyAJQSEgEAgGAMAJwwmkSdFEtEsSVIVMqSNeJghR7YC0WkuU8YODrFoJwAArLwPwHAtCkFQJwNw1hrAYk2NsQCZgkg8FIAQTQrT1himSPqAAHMswIGh/AdI0BoJIZhllmAAJwHP0JwSQvAWASG2aQHpfSBkcF4AoEAEFZm9NaaQOAsAYCIBAJsAgkl24UAgM7V2UREScFUMs/wABafwkgTjAGQKyKQ%2BozC8DfIQEgQo9D8EECIMQ7ApAyEEIoFQ6hXmkF0FwUgz4mqpE4DwNpnTulzP6ZwBOVx/kTnphC6FsL4WIpOMiswJwIAeHlitfYXBVi8BeVodYEAkDAoVuQSgSqxjACkGYPgdB2KPIgLEFlsQIi3XpbwI1zALIJ1iNoeoLzplyxNAnBg/MWVYFiF4YAbgnyPO4LwLAN0jDiHJfgW0DQpw%2Br6VyeoVxdjTOiT0FlNxYhNQsh4LALLN7XVNaQcyyMlDhgDcAG4Rg5nrCoAYYACgABqeBMDPgTrqbNOLhCiHEIS5tJK1AsspfoQwxhhmWH0HgWIjzIDrFQN47IPqoW/B%2BqYSw1gzC3PMkZLAo7x7dF6NkFwKtph%2BCpWERYFQqh6CKFkAQe7T0ZHPQwYYx6xhUrqA0AQAwpieA6HoJ9fRX0LHKKMRIj75iXsA4MO9/6JDrAUGMnYEGTkcC6dclldyTg8phXChFSLJAopFbgDFhFJlSplaW9YW45xjA3YsyQSR9QHKSIESQGhJBmEkMBDQHT/DHPaRwM5pALlTP1P4Lg/hlkHOWUJjpkguAdNo/4RD5K7kPKeTM0t7yvkKp%2BRyq4KqgWLRdgrUFbBOAtBYHyQIUK1YMR4lwA5%2BouD6kjfgIgq7sWyDxW26QHalBdvJboLVNK4GmsZfB5l8m2WafxKbbCJmzMWYMFZmzdmNAirFXpiVkyzDSuU68%2BVirdOu202qxIxnTNQssxqg5XAII0H6gkPVBryXmpNb60gjXLXWttdmh1MonUuuDZgd1nrvXZv9X2oNfSQ22rwOGllUbkAxuzfGrjfSk0ptuGm3YfTM0XOa7mjIdowSjeMip8tTBK01rrQ2xgTbXOtoJR52QnayV9N872kt86rCDqTeu8dk6BDTtnUkRU73F3LoSKuqa8BINM2fX4CArhgMhBVmB5YAG0jXr6Ajs9fRkcnsfdD79QH335Dx1ul98wccPomIMBHMNWgU4A5B6DBKgsIZubwZDxWYvuT7YKhL9mcOOZIGcAjmXZXzNIKRrAiQN1cZ43xmzjHAjScCIEJITGWOSbk7czginnkqY%2Bd835/yCt5f02Cjgxm%2BUsAUHyVkfJrP6h9HMNFgvnNUubW5u7RL5BeaezoEAKR/N0t9SzkL2uODsr%2BVcLlUWrc27tw7p3%2BJRWm7S0kJIov9e5fFWQQFhXmHIHgTie3BycRJ8CcQFgsLtU1Y4pQerfTWu3GzU3q1NqHCdcWo651ze%2BsDa9chH10yRuBo236vAobHDTfJbN%2BbzXFuJuHat9bGajLbembt/NB3A1Hey3wCt1ba31sbc1j3t2JD3eJb77tAfXv9oXZ94d33%2Bm/Y5JwbsFZgeWCXezldwtn9frbpw67pE77qI7oD05XrFDZCY7o7ZCQEk6TZk7U6gGfr46NDk5HrgYgZvp5BgG06/pLC46M5bAwZSpwas5IacCx5wrW6278iJ6jhzAC54bC5TKZ7ZYkZgJS6UBBZy4gCHL6jp4dJbKSbbLp6BDCZa7s4662BKZi4TykCLJJD%2BC2ZcCHJq5HJBBcDrJUpcZJBh4yH3JZZypBaorSGsrGEKHrDmSZDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/are_distinct.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/are_distinct.test.hpp)
