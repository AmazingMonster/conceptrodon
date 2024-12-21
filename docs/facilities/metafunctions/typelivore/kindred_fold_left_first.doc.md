<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredFoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-fold-left-first">To Index</a></p>

## Description

`Typelivore::KindredFoldLeftFirst` accepts a list of elements and returns a function.
When invoked by an operation, the function left-folds the list using the operation with the first element as the initiator.

<pre><code>   Init, E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
-> Oper
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, E<sub>0</sub>
   &gt;, E<sub>1</sub>
   &gt;, E<sub>2</sub>
      &vellip;
   &gt;, E<sub>n</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
KindredFoldLeftFirst
 :: typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredFoldLeftFirst
{
    template<template<typename...> class>
    alias Road = RESULT;
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
template<typename A, typename B>
struct Subtract
{
    using type
    = std::integral_constant<int, A::value-B::value>;
};

template<typename...Args>
using Subtract_t = Subtract<Args...>::type;

template<template<typename...> class...Args>
using Metafunction 
= KindredFoldLeftFirst<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Road<Args...>;

using SupposedResult
= std::integral_constant<int, -9>;

using Result = Metafunction<Subtract_t>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `KindredFoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct KindredFoldLeftFirst {};

// Base Case:

// Fold once.
template<typename Initiator, typename Element>
struct KindredFoldLeftFirst<Initiator, Element>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = Operation<Initiator, Element>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

// Fold twice.
template<typename Initiator, typename First, typename Second>
struct KindredFoldLeftFirst<Initiator, First, Second>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = Operation<
          Operation<
            Initiator, First
          >, Second
          >;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<typename Initiator, typename First, typename Second, typename...Others>
struct KindredFoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = KindredFoldLeftFirst<
            Operation<
            Operation<
                Initiator, First
            >, Second
            >, Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACc0gAOqAqETgwe3r4BwemZjgLhkTEs8Ykptpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJydIKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmgW4EAJ6pjKyYAHS32PRsggpH2CYaAILjxF4OANQA0hF0MRMOgAGKedChTBUAhgvDEca/EwAdisKIAIkcrB83u8APT434WJhKX5uUnsPF4wm/CG0dC/ASba54nZ7A6YI4nc6XNi/ACSDCyTCIZF%2BZwuzH5912jAILzxXx%2BBABQJB4Mh0Nh8MRCuOQpFYtIv1lj31r1xaLxv1tEt2%2B1FXOO7MdhxdvOlN1uL1%2ByAMCgUvwA8hdiKLsoqPnbfsq/hjMM06Da7aice8YzGvJkjBLecjo5nbUcMSGwxGBNzDY5RSQTWb5YrAumY6isc3qYXba7Odye06%2B56rrdWYFsH6AwoR%2B9gCC5U8oxm7dmIsBfgAlVBMRkl34JpO0bkzufmqc%2BscgECS53ptvYzsEon0xkEADueBZbIdvY9UquguFGtjTzP9%2BV1cYTWvL1fiETA0AYdBFzjVVAQQjVn21OEEXGKtALwWtxXAggTVg%2BDELHalrS7e0OQHF1vzonlQO9Udx39Ukg1DBIKwYRcY2QvdEyYZNqLTFMixXXNrwLJci13LjwwablxKLMtuKU44VNUgCjTrOlsIVai5LHEi4IERCjMzJsW1TTF71xaj%2B3dE4GOcqDh3PNjJ2nWdMHnAhngo6jJLXTdt2RQJS33YTD2OY8/NPEcXkva97PeO8Owcx8Nzg9ZMgAN0wclKRAB9aWfCV302E0EEMdB6AlBAipoPVGrnX5UhaK4dkRUgaSJOrfhBZA8qKkLGqKkFxlZD4nOdJi%2BSK6t8OA9ywIMyCh35UjzM25iR2DAgmsRJCCG%2BP5UOBUEMJhLC9Vw3TCI2mCzIQk1DuOs9WMomzu1c%2Ba5sHfbPInDi1MUyMgtk2MzpVQSDxUsTLNtcbpK01NIrVNDrq1W6iOU5HMwUniCeh7TiY0tx0e021loIk18cJ1sTJesjqaslmPoSL72eSq9/o3LdyLcCnIdeTLoYy29HP%2BvtZd/RakrHUHAx8k95UCy1ofGsKd0x6Lkzi3z/J5i8r15NKpbKgAqW27fth38Rpe3fgAFUwcYg3tp2PnxB3/e9h9zECCJ/S8LAIrceDNlSALFy/Wi3K2or3j2xbiVO87VSELxYjOpgHB%2BlTUYt0TMfGdBLwiHZZzEAB9eDZkEblq5Nd5L3ysQvEwABaCwO6751xdvOyJYTt0AeT6diGATW8XGnO8/DBw69VXdF/zwu4pn03sBSi2x9m%2BWXMTyfgdYlWvveHfF3GgBZISqC8BgHGyGTd0u9DcZ1AzSf4ghK4gGrpgWutAG4CCbvqNwrdfhcBeH1aiFcq6CBAeGMBjdmjN2ODAwI8CVJIKASg0B4CGCQJboIE0kg8GIIAcgmuaCSFkOwRQ34uCobFjNrrI8O8lbDwfAvLwqQiignXB7LwtBDLpXLrQwh9D64YMMFAmBPckjWX4TmUKYiJERVLA/ZoT8X6Uw3svAgq81FZVmI4ZAdcOIJAIBAAhCgrg2MCm4URChxHERgoI4R6B3GeJeEsbEHAVi0E4P4XgfgOBaFIKgTgVNLDWFjGsDYRVg48FIAQTQISVgAGsAiSGuBoSQXAUSBA0P4DQZgABs1SzAAA56n6E4JIXgLAJAaA0KQKJMS4kcF4AoEAXSsnRJCaQOAsAYCIBAGsAgqQvDEQoBANAew6AJCiFcTgqh6nVJ7tUyQvxgDIGQLAwpZheCgkICQPAlcuAyEECIMQ7ApD3PkEoNQ2TSC6Dua%2BcMqROA8FCeEyJny%2BnBgWfM1UqAqC/G2bs/ZhzjmnOuGYX4EAPCrPoMQZEZhAhcCWLwEZWgVgQCQCs1IayyBLPJZSkAwApBmD4HQHqgyICxE%2BbECILRTgAt4Jy5gxBTjBliNoOCIyMkrPNMGBgtAeWjNIFgWIXhgAUloLQQZ3BeBYBYIYYA4h5X4GGo4QqGqYmYFULlHYvLyAoLCfK2geBYjhkFR4LAnyzp4HaZq0ghViCxAyJgBMOqjAOqMNklYVADCzwAGp4EwK%2BLiUSMn8AeaIcQLyU1vJUOoeV3z9C6pQNYaw%2BhHWDMgCsVAsdsgap7hXEsphEmWDML031xAbke3gCsOwYrsguAQlMPwdywgRCGJUEYdyihZAEAOvQk6GjzGGIkO53bX4CD6JMTwHQ9AroaOugYI6FjjtsBMNom78jLpPQusdS6u0pM2BIIFHAIndNBZwWFOy9kHKOScqQKK0W4Cudi9JBLMnhpWE1bcIwIB5JAJIQI1wkiBBRJIYpZhJDVM6f4apSRmkcFaaQdpeLrjVK4NU%2BpSR6mkf8CU/wiHqkvvlX0gZQzQOjJJVM0lMyIULPIJQGlWKNlsE4C0Fg%2BUUQ9yYKDXMXAkjXC4EUi5%2BAxQ3L0Jmx56bpCZsUNmz5uhGW/KYP8zVj7n09N4GC7jUKYUibExJqTa4ZNyaKWijFFKsU4sCGYEDRKxmcf4wkXjyzUCYpGDZ8T7EjAya4F0mgEjuaUHZfK/l3LrXJcFcK0VDhrWSvlNK2VnzFXKtVeq612rdX6piYantJrPnmstVsDJwC7UxIdU67lrqtgxI9V6jJvr/VKCDeV1c4a%2BBRoULG%2BNibrVqbTc8zTshtMfNzSARlBgw0NqsJYEtsQy3QdiVWiBnBa0APrUWptLaEhtqwLtrtdQe3OAgK4GdQ6EJXsWBOjIU6chnsHaQOd2Q3tHp3b0E9z3uj3caJeg9i7t2g5%2B7DuY0Pr0PtWOse9%2BLcOmdfRwX4YW7MRYc7J%2BTGh/1KZIB5/FhKwOkAg1gRIe27X4cI7J4pKJaMojKZIND%2By7lmdiZwZjwyRsTOmbMyFgX/PEEE1sETCKWAKHyic/KjnOTjEU4BlTdyZtPIkPNwQi2c0xN0MEAzRnAWY5BYxzg4K5kLKZNZ4gLA5cK6Vyrp0SJ0XBbcwkDzgRvPC7JV7ylEug9YpAIroRddldJDrqr0xsvNPMvi2yjlXLBWpbT0KkVYrsvBalTKuVlXMBKpVWIEr3qyshs61qhE1WO3yrqyNK13qmufNa8604HX3Vtp67wPrAbBshuG2x0bTAY1xoTVKabsh1NzdeQb3TIBghreMGdmwrWbv7YaBq/ESCNvWGbeZ1t7bN/A4e09%2BHL2oRI/e39z7DQwf/dKDfoHd3V2Q/6GDs/H/WiA6Xcez/S/AA3/F/G9VHVJFHO1LHK3HHBPX4eXRXX4aPa4OPUnQDCnf3NjcDTASDenR9JnFbWTQIQIfwSpEpTpYglEMjBjXpAXWwFjHzJYGDSQfwBDfwepGpFIJIMpJDLgZfTgQIS3Wg/pVjYlR9c5Gg8zOgxglYX1TIZwSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/kindred_fold_left_first.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/kindred_fold_left_first.test.hpp)
