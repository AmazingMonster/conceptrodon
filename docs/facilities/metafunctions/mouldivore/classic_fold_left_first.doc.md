<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicFoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-classic-fold-left-first">To Index</a></p>

## Description

`Mouldivore::ClassicFoldLeftFirst` accepts an operation and returns a function.
When invoked, the function left-folds its argument list using the operation with the first argument as the initiator.

<pre><code>   Oper
-> Init, Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, Arg<sub>0</sub>
   &gt;::type, Arg<sub>1</sub>
   &gt;::type, Arg<sub>2</sub>
      &vellip;
   &gt;::type, Arg<sub>n</sub>
   &gt;::type</code></pre>

## Type Signature

```Haskell
ClassicFoldLeftFirst
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct ClassicFoldLeftFirst
{
    template<typename...>
    alias Mold = RESULT;
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
/**** Subtract ****/
template<typename A, typename B>
struct Subtract
{
    using type = std::integral_constant
    <int, A::value - B::value>;
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= ClassicFoldLeftFirst<Subtract>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

/**** Test ****/
static_assert(Result::value == -9);
```

## Implementation

We will implement `ClassicFoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct ClassicFoldLeftFirst
{
    template<typename...Elements>
    struct Detail {};

    // Base Case:

    // Fold once.
    template<typename Initiator, typename Element>
    struct Detail<Initiator, Element>
    {
        using type = Operation<Initiator, Element>::type;
    };

    // Fold twice.
    template<typename Initiator, typename First, typename Second>
    struct Detail<Initiator, First, Second>
    {
        using type
        =   Operation<
            typename Operation<
                Initiator, First
            >::type, Second
            >::type;
    };

    // Recursive Case:

    // Fold twice, handle the first three parameters,
    // and recurse using the rest.
    template<typename Initiator, typename First, typename Second, typename...Others>
    struct Detail<Initiator, First, Second, Others...>
    {
        using type
        = Detail<
            typename Operation<
            typename Operation<
                Initiator, First
            >::type, Second
            >::type, Others...
        >::type;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIAAcZqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJM/jcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ADyqOI7xyOOBE2IXgctzcBKyyAAYp50KFMFQCCy8MQJsCTAB2KxXW7i26w57wxEEFFothYjHYF6MAgKKliiU0ukEW4AEUwLTot2FViF%2BqhoqBWvFOx2twsTCUDOd7EFttu9tubNo6FuAi2GOBEslYOlkOhctRzDYDwY2XeJFIkvlscwtxVYLVmsuoZ19MNxtoiPuCccSbImdVglzobNIdDEq8WSMqdRpv8%2BpJZIpAlL5bwlZTWdeBBxIBA0YR/mt9YtVo9eYl3t9/oIAHc8EHG%2BKpRCZ8iY%2Bj44miFXp%2BmfXyJinLyehJg0Ax0HXtQRaYWjUw6AOz8nr35AgU0fZ9X38bBd1NEUoNDFsImAdsEU9esuwlUkEj7BhEVgps9zTE8MPJRocJQvCmzLf8q15IDcLwicp3lECnwEV8yPoiDJ2nRdPWFS1ZyXUNvQAJSfDYsgANwzNw3RAQSVwdNdJS3LYUwQQx0HoSUEAzGggO04hMAzNJWnRUF%2BVIKDvQ025DOQcSM3gtsCB02zMAmYNPX3GUowIuNKIrc87z8jMaNvJCr1A1jguPRUsWJFyEg1CCoILPUix/EtoQCocgsA8KopfFMEp0/klTfcUG3Y24nMQ7jqqhbsMt/aE6Kbe84yIrDSOXciJQ6jMupI1rqr6nLh3y8dRolBjp2YsC2tQ7AuKYklErK7EGs4xjUR43roP460oO8yMjwVTEsUuYBDOzQRksgz1atuABZdlOya78WrcK6brHBRyu27iBKuPi9uBX5/mOQEIczVRWGeDMvnByGASXcx/AifEvCwTszoAfQ/H91VzZG7iELxYkJ%2BkkauE7DwG25Lhi87HVzNLbnJynyQcQUYMe1s6vld7bgmdBJwiUFrrEPHnzmWteOhCWU0uScJLELwMwAWkdVX1ZnSDgaBBdDdJg4Xu/KgvAYBwck%2BM5gTp2UQqVS5iGAe7gSe56Latm2BFNEG0MZZ1mTXTluTC8doU5qmo%2BWkBXr9RFXfdgGDaOn4jluUSFC8Wg9Rpy4npzvO9Ua82Wkt62SMDtxUoIMWQAlzApdoGWBDlqO3CV24uBxSzPVF8XBBb8k29llpa0VwQU38fv68b5vW/bhhO8RHvJHnweG%2BHyWx5Xtfp%2BA2455SwP06XGGABV3IL%2B2rjmRxkDxkOEgICAS/z3XvAzRry81gAnMsK0HBVi0E4AAVl4H4DgWhSCoE4HXSw1gRbrE2L/Mw/geCkAIJoUBqwADWIAIGSAxBoFIZgAEAK4BA8hSQuBCiFNIcBHBJC8BYBIDQGhSAwLgQgjgvAFAgG4bg2BoDSBwFgDARAIB1gEDSF4YCFAIBoCeHQBIUR0ScFUEkQImtAiSFuMAZAyBe6kLMLwTA%2BBzx4DFlwGQggRBiHYFIBx8glBqDwaQXQ9iNzkjSJwHgYDIHQK8fw4kiiFF6lQFQW4Oi9EGKMSYsxGIzC3AgB4NR9BiCmkwVwZYvBRFaFWBAJAqi0jqLIMo8plSQDACkKkGg%2BckqUFiF42IERWhIkCbwDpzBiBImJLEbQT5RHYNUWOYkDBaDdLEaQLAsQvDABkrQWgQjuC8CwCwQwwBxBzPwHZRwUl1lwMwKoMSoIenkBHiwuBtA8CxHJAMjwWAvEfjwBwjZpApLEFiJkTAhptlGHuUYPBqwqAGHdgANTwJgDcGEYHYP4I40Q4hXHIvcSodQcyfH6B2Sgaw1h9APKEZAVYqA0iNHWZrUWjVTDIMsGYPhPziC2PcvAVYdhRk5BcC%2BaYfh7FhAiMMKoox7HFGyAIflegJWNAWCMRI9iuV%2ByaJMdonhOh6GVY0fobR5WisVbYNV0qlVqv1UsfJawNhbAkMEjgUCeFhM4HE3R%2BjDHGNMVIVJ6TcCEBILkrBBScFgtWDpJgWBEgQEISASQ/gMQAP8EwjQkgzCSECFwiBgQAH6E4Gw0gHCsEYkCFwQISQAH0MCCQmhCbgi8N4PwwRwjg1iJKdI0psjImKPIJQGp2TNFsE4K0FgEkhSayYHiAwbYuAAIxFwMhljrEkFsXoDFTi0XSAxYoLFXjdCpD8UwAJGy7UOrrfAzgET5GKIDLE%2BJbqJ07N7jOudGh0mZIqdkgNZgg1FPEe23tCRu0qNQFk0Y%2BIdnTq4Nwpp5khEQDaXMvpXSrmIYGUMkZDgrkTLVFMmZXiFlLJWWsq5Wydl7LgQc7lxyvFnIudsbBzdbm8HuY8rpLzthwPeZ87BPy/lKEBaRhCYK%2BCQoUDCuFCKrmrtRS4jdsgt2eJxSAVIk7jCEssMS2IpKo3wMpTkaltKuz0qsIy5lCRWVYC05y%2Bo3LnAQFcCakIL5zVivSJkSVuQNUFHFW5uVwrFgue1X0Y1nmBU9Bs6q%2BYfmFVauC/kULcw9VRYNbaq16CUssJPU6jgLqEmGLA1Op9ZCfWLpyejfJhSQ2kDDRGygdq80FpncmoUECAGMP8CmtNkh7GnobbYJtP7W3wHbXIqJgH/3EH7dsIdiSWAKAkqYiS06MQHgmAuv15mV2yDXTJtx8nsVwN0P4Ug%2B7D1BJzfa0JczwmduiTembc2FtLZW3qDJwH30JADf4b9Qm/1vcqWNv72SQDzbSGkPGi2AF42e3jVQBi%2BB0Bg609pnSBnIZR4M4ZozMPAcmdM2Z5HMCLOWWIIjXySPAvY5svklH2VzJo/ZS5XyGNeOY08pEbG3msq47wHj/z%2BPAsEy24TTBoWwvhTGSTW3pMSFk4IPbO6Ah4tBUZolzHLM6apZwHYQ8VcmfrSytl6vAu2fsyFvQQqKjRe8yUHIDnZU5Gc4a43EWphm6VdZlVurBhJYtUagYDmEve8t8ly1Cg0E2stRly7fDnWw8MbN%2BbtwIfLfhBMYr62A3lebcU0NmBw2jG0yw%2BrSmZ3%2BH8BA2hXWuFl6FKWx1V3OCNpEZVohkgIHxoYUKLhSRJDUK4BQ4ILD/DR/rY37P%2BDzsWPrzHgR4/lirB%2BVkZwkggA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/classic_fold_left_first/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/classic_fold_left_first.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/classic_fold_left_first.test.hpp)
