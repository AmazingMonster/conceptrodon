<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::FoldLeftFirst`

## Description

`Typelivore::FoldLeftFirst` accepts a list of elements and returns a function.
When invoked by an operation, the function left-folds the list using the operation with the first element as the initiator.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>..., E<sub>n</sub>
-> Operation
-> Operation&lt;...
   Operation&lt;
   Operation&lt;
       E<sub>0</sub>, E<sub>1</sub>
   &gt;, E<sub>2</sub>
   &gt;
   ..., E<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
FoldLeftFirst ::  typename...
                  -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct FoldLeftFirst
{
    template<template<typename...> class>
    alias Road = RESULT;
        
    template<template<typename...> class>
    using UniRoad = RESULT;
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
= FoldLeftFirst<
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

We will implement `FoldLeftFirst` using recursion over the number of parameters.

- **Base Case:** Handles several numbers directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct FoldLeftFirst {};

// Base Case:

// Fold once.
template<typename Initiator, typename Element>
struct FoldLeftFirst<Initiator, Element>
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
struct FoldLeftFirst<Initiator, First, Second>
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
struct FoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = FoldLeftFirst<
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACc0gAOqAqETgwe3r4BwemZjgLhkTEs8Ykptpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJydIKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmgW4EAJ6pjKyYAHS32PRsggpH2CYaAILjxF4OANQAYp50KFMFQCP88MRxr8TAB2KywgAiRysHze7wA9BjfhYmEpfm48ex0eisQCgb8BJtruidnsDpgjidzpc2L8AJIMLJMIhkX5nC7MNn3XaMAgvdFfH4Ecm0YGg8GQ8ZMznc3mkX4ix7iwKvNHw9G/I383b7HmM450s2HS0soU3W4vX7IAwKBS/ADyF2IPOyEo%2Bxt%2BUr%2BiMwzTohuNcNR70Dga8mSM/JZMIDcaNR0Rnu9voEKq5jh5JA1WrFEsCMcDcORFZJaaNVoZTMb5ubdqutxpuudroUnfewGImFFT39seNCYiwF%2BACVUEx0DDAlnQ%2BHaEyB0ORwQ%2B47dSAQAKLTHqyi65jsYC5fyAO54am001N22Cq4cgt4It8o/2gFKggaj%2Bb5CJgaAMOgY7BjKV7ymCEJQjqbiqoW6p/ghGogWBEG6iSBr1ia9KtpaT5Ecyr5sJ2Touni7pegkuYMGOgZQb8q5MBG%2BHRpG6aTkmR6puO6aZtm9ENEy3HpiJPpiccEmSe%2BarFmhyr4UJuoYaBAgQapcblpWUZImeaL4S2NonCRZlARRe7YD2NH9oOw7as8OH4bx05zguS4rmG7Hrscm5OWKu5dtgB5HkZ7ynrWxkXrOoHrJkABumAEkSIDnmSMG3vemAagghjoPQ/IIKlNAISVW6/KkLRXDsUKkKS2KFb8Q7IIlqXuSVqVDuMNIfKZFpkayqXIZ%2BqFWal8HjIB7ZsphWmzeRDrXB6BClVCkEEN8fwwSCcH/vmil8tNAG/At4EamtG0hWOXEmRZQ2DW2y2Ud21FulJDFMcaLFsRxgkwnhgPxom078XJUbLrKsGKgh4k6emdHSX6smI3GyPfWjIPycaY1fhqp2Q2p2AaVhxO6epnrrQkt3oy84WPbO87YW4mMya8MWA9FJ4PYRlmPS9I1vbZH0hYF24uXqgNdZ5i7Cf9/luBLzki%2BFLKRTzmUAFS63r%2BsYqSesACrYEIxt64bHwYvrtva1bUVomYgQRC6XhYEubhgZsqQ7ndA2Cy%2BI2/O8S3B1YrmfNt0rnV4sTbUwDi4fpRpdRFnHQ%2BM6AHhEOyDmIAD6YGzIITK5xq7wHklYheJgAC0FhVzXFqcyehlc4%2B/NPXNK3vMQwBS%2BiXVCHHCcOAXMrCSP8c%2BknAX97d%2B6HhrHcB13zaB8N9oi3Zbr9gvY5dQAsr5VBeAwDjZAJwl7QqRPY8xBDZyAueYPntBFwIJeIeXvxcC8jV8JZxzoIN%2BPoP7F2aKXY4v9AgAIksAl%2BoD36fwYN/MuggNSSHgUAp%2BIC87gNQegmBmDfhwMjhmJecsNwLxFprD4w8vCpCKJgdAM5MAKC8LQcUaJM54KQQQwukDDA/1IXXJIelzyyw4Vwye0MT7NDPhfGSbhp5jwIBPSRsVZiOGQAXGiCQCAQEQQoK4%2BiXJuHYZw7hGEmEsLYTI7hLwlgog4CsWgnB/C8D8BwLQpBUCcDcNYawQY1gbFSuYQIPBSAEE0G4lYABrAIkhrgaEkFwWEgQND%2BA0GYAAbHkswAAOIp%2BhOCSF4CwCQGgNCkB8X4gJHBeAKBALU2Jvi3GkDgLAGAiAQBrAIKkLwAEKAQDQHsOgCQohXE4KoIpeS655MkL8YAyBkB/xSWYXgrDCAkDwNnLgMhBAiDEOwKQRz5BKDUHE0guhDk3h9KkTgPB3GeO8TcxpHphlDJlKgKgvw5kLKWSstZGzrhmF%2BBADwEz6DEBhM7LgSxeDtK0CsCASBxmpEmWQUZmLsUgGAFIMwfA6D1RaRAWINzYgRBaKcZ5vBqXMGIKcD0sRtCgXadE8Z2oPQMFoHSjppAsCxC8MAQktBaAtO4LwLALBDDAHEIK/AbVHApSlX4zAqgEo7HpeQUBHjBW0DwLEH0zKPBYBudtPAVTpWkBSsQWIGRMChjlUYI1Rg4krCoAYAeAA1PAmAbx0R8dE/gxzRDiHOWGy5Kh1CCrufoeVKBgmWH0MalpkAVioF9tkKVdcs6ZlMJYawZgGn2uIPsjh8AVh2A5dkFw4Eph%2BEOWECIQxKgjEOUULIAgm16G7Q0eYwxEiHNrZfAQfRJieA6HoMdDRJ0DDbQsTttgJhtGnfkUda6h0dpHTWsJmwJCvI4F4upHzOAAvmYs5Zqz1lSHBZC3Auy4WRMRciz1KxSoLhGBARJIBJCBGuEkQIsJJBpLMJIPJNT/B5KSGUjgFTSBVKidcPJXA8lFKSEU9D/h0n%2BGA3ks9grGnNNaTEz1XTenov6d84Z5BKB4thdMtgnAWgsCSrCOuTA7JJi4Eka4XBUnbPwLyfZeho0nMjdIaNihY03N0MSh5TAnnSuPae%2BpvBPm0d%2Bf8tjHGuM8enHxgTqTIXQqxbC%2BFgQzBIvIx0tFGLUAwoSPRsZTmLMjD05x6iRg%2BNcFqTQbhtNKCUsFYy2lurwvMtZeyhwuruVil5fym5wrRXislbq2V8rFV%2BOVXWtVNzNXaq2NE1%2BBq/FGpNbS81Ww/FWptdE%2B1jqlAuuy1OCj3qmB%2BoDUGwUuqJMRrOdJ2QsnrnxpAMSgwHqi1WFTZVjNv7/E5q/pwfNT9C0posKWzT5bK0LZrXUOtzgICuD7S28CO7FhdoyD2nIG7m2kAHdkS7K6529DXWd7oR3GjbqXcO2dH37sA7mH93dR7VjrEPYi%2BD6nz0cF%2BF5gzPmjP8cExoR9ImSBWbfXZ1Fn7MDfsSItg1iHkP8bSbCfDsJMmSAg0sw5Gn/GcFI20ij3S%2BkDJ%2Ba5xjUyZkcDY8ClgCgkrrKSsZhk4xhPPrE4cgbpyJDDcEKNuNfjdDBCUypl5MP3nEc4F8wZwzKS6eICwQXwvRfi/NNCKF7nsVWcCLZlFnTqM85xQx23sKQAi%2BYQXMXSQC4S40QL6TpLgsUqpTS5lkXI8srZRy%2BLTmeV8oFblzAIqxViAy7arLbrasyshPlqtgqivtR1basrNzKumtODVy1FaGu8Ca061rbr2v2b4D6hQ/rA3Bv67ISTQ2LnK/kyAYIU3jCbbTbEfbS2GhSoxMAmbJay0JArVgGfb3junaB%2Bd4EoOruPZuw0T7T3Sj79e4d8dP3%2Bifc39f1oL2R2rpvzv5/D/z97oh%2BE8HBrYe6/h8Hr8ELiLr8H7tcIHhjs%2Btjo7h%2BqQF%2BlgETseqThNvxoEIEP4DkukjUmgbCBhkRg0szrYGRk7ksH%2BpIP4EBv4EUvkikEkJkiBlwGPpwIEDrgQU0rjvEvBlsvgZpoQSQSsPapkM4JIEAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/fold_left_first.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/fold_left_first.test.hpp)
