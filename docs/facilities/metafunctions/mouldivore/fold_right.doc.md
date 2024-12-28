<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::FoldRight`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-fold-right">To Index</a></p>

## Description

`Mouldivore::FoldRight` accepts an operation. Its first layer accepts an initiator and returns a function.
When invoked, the function right-folds its argument list using the operation and the initiator.

<pre><code>   Oper
-> Init
-> Arg<sub>0</sub>, Arg<sub>1</sub>..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>,
        &vellip;
   Oper&lt;Arg<sub>n-1</sub>,
   Oper&lt;Arg<sub>n</sub>,
       Init
   &gt;::value
   &gt;::value
        &vellip;
   &gt;::value</code></pre>

## Type Signature

```Haskell
FoldRight
 :: template<typename...> class...
 -> typename...
 -> typename...
 -> typename
```

## Structure

```C++
template<template<typename...> class>
struct FoldLeft
{
    template<typename>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will right-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   1-(3-(4-3))
-> 1-(3-1)
-> 1-2
-> -1
```

```C++
/**** Subtract ****/
template<typename A, typename B>
struct SubtractHelper
{
    using type
    = std::integral_constant<int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= FoldRight<Subtract>
::Mold<std::integral_constant<int, 3>>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>
>;

/**** Test ****/
static_assert(Result::value == -1);
```

## Implementation

We will implement `FoldRight` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct FoldRight
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<typename...Elements >
        struct Detail {};

        // Base Case:

        // Fold once.
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Element, Initiator>;
        };

        // Fold twice.
        template<typename First, typename Second>
        struct Detail<First, Second>
        {
            using type
            =   Operation<First,
                Operation<Second,
                    Initiator
                >
                >;
        };

        // Recursive Case:

        // Write out the last two folds, handle the first two parameters,
        // and recurse using the rest to obtain the initiator.
        template<typename First, typename Second, typename...Others>
        struct Detail<First, Second, Others...>
        {
            using type
            =   Operation<First,
                Operation<Second,
                    typename Detail<Others...>
                    ::type
                >
                >;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };
        
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIACcZqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJM/jcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ADyqOI7xyOOBE2IXgctwAYp50AAlPDABAEYEmADsViut0Ft1hz3hiIIKLRbAeDGy7xIVIFQppdIIt2UxFQRAAsszgULbrz%2BZcDQaRRCEdCJajmGwsRjsC9GAQiYqTabBSr6QARTAtOiGvm871Q436j23HY7W4WJhKW5uOPsblKj1RxnM24CLYY8Me81iq2S22YW6OsHOt0R25etW%2B/20RHl15c/zYPOmo0d6teLJGYWSw3%2Bb0kskUgRNp2CUgyuVEYhU/zG6vB0Mp91p6NM2joYUAdzwOe7QoLkKLNvRjLwxAmM%2BtUtLQkwaAY6CrEdrt3rTDoiIZ19vW4nxfN822PQUu1Tatbl7CJgAHVFwM7YchVJBJxwYP8AIIUgkOrNDyUaRFgIEdBcKg6CI3uWVHHlBcKMood2wYyjF2XCNVyXddq3TFlnw2LIADdS0TJQQG4iN0wAdWIQhS3WNUCAQUsCUUvdUFufgdwUGcEEMdB6GFZTNOw/cNLSVp0VBG9yI3U103025iH4m9S1g/slNLZyJmFDTUFif0GCM0sIjnEhcxY4UwVFM9kQvaV/xvHCEIfIDn1Iu9i3Re1iU8m93w9T9v1/aFEsAkjXxnXLlJve0Cs7INIoNdz4PvPChShEdBQIjCsKS2zGNNHqiOhCqyPayj7xLL8/R/RtoWqhIFDqsCmsYkAQDataPXqwa2KQziw0i09LTih97UuYBnIrQQFF2oUWtuXUdyHEdivmtxLuultluxNsNrarioMOg6oJO8UsrtLEvswG6XXqx7nt3Tr1U1HU9WhGG4d%2B3MwKBoEeRDfHgV%2Bf5jkBUmy1UVhnlLL4SbJgF13MfwInxLwsCHM6AH0CHJQg7tWoEfiOICvAC8l6Xpq5wfPVLLky%2BLSysIXPyEcW%2BaYBwAAl6jJblGrsx6trslGJnQDaIlBK6xG5l85kERErZnS4NsEsQvFLABaGM3Y9y122Jwm1yuYFZbOksLuIYBBeYy5HvViWtbVFHE81nW9YSRFLmjnGcQByUQ%2BF65Re1WaqC8BgHByT4zjD6KLQhpWo5jt1EfLyvq4EQ1Q5Q7dWXZTliI1yXWzjjakcRc3LcETAbdoO2BAd1s3Gd25/EXceQEnzHc5WwOjpLu4%2BIULxaDVaX477eCT7PlOULLloK6roje7cDtp5AK25/JBf7ZaR20I15cBxANZUBALZf1nvPReDBl5O2nOvUBH8IEz2tr/WB8CgGIMkG6faocRZ3AACqYB8pfOYjhkDczjEoNoEBb7nz9t4UsnUUZey4MsUMHBVi0E4AAVl4H4DgWhSCoE4O/Sw1gazrE2Cwsw/geCkAIJobhqwADWIA%2BGSAxBoAAHGYMwSQkhcD4Xo3RXAeQ8mkLwjgkheAsAkBoDQpAhEiLERwXgCgQDOOUcI7hpA4CwBgIgEACk0heBwhQCAaAnh0ASFEdEnBVC6MCF7QIkhbjAGQMgW4UgMRmF4JgfA848AWy4DIQQIgxDsCkBU%2BQSg1AqNILocpe5yRpE4DwHh/DBFNPccSCJ4S1SoCoLcZJqT0mZOybk7RZhbgQA8LE%2BgxBDTyI4bwXxWhVgQCQDEtIcSyBRL2QckAwApCpBoOfJalBYhNNiBEVoSJOm8HucwYgSJiSxG0M%2BXxiiYktmJAwWgTy/GkCwLELwwBEy0FoF47gvAsAsEMMAcQoL8DOWrsJOFIjMCqH4qCZ55BZ42JEbQPAsRyTvI8FgJpfM8AOPhaQYSxBYiZEwL6JFRgyVGBUasKgBgY4ADU8CYD3GhIRij%2BCVNEOIWpUr6kqHUKClp%2BhkUoGsNYfQ5KvGQFWKgNIjQ4Ve3Np1UwkjLBmDccy2SWAdUQFWHYH5OQXCvmmH4cpYQIjDCqKMcpxRsgCDdXof1jQFgjESOUx1XcmiTHaJ4Toego2NH6G0MNPqI22FjUGyNsa01LA4WsDYWwJDdI4AIlxfTOBjJSWkjJWScl5LmRAXAhASCrIUcsDZvLVjKSYFgRI9rSAaMkP4DESR/BWI0JIMwkhAhOL4YEJI%2BhOB2NIA4hRGJAhcECLopI5jAhaJMeO4IrjeDuM8d4pRvKAnBJ2aEwZETyCUGOcshJbBOCtBYIJHkXsmB4gMP2LgSQMRcB0YU4pJBSl6HlVU2V0h5WKEVU03QqQ2lMA6fC0t5bT2iM4AMggQysyjPGbW/9yLcnAdAxoeZiz9nLPbWYTtV6/HbN2agJZCQn3RPY3R0Y%2BJkVAa4M4y51kvEQFuaC15jzCVSfeZ875DhCX/OdIC4FTTwWQuhbCwliLkWopEeip1WKmm4vxdsRR38SW8DJRSx51LtgiLpQyxRzLWVKA5XpuC17%2BVMCFSKsVNpCUwZlTU%2BDshEONOVSAVIAHjAassFq2Idq9UGpyEak1w4zVWAtVahINrSHwAdfUJ1zgICuGzSEV8ebfXpEyAG3I8aCh%2Brq6Gr1iwatJr6Fmxr7qeglZjfMNr4bE3dfyL1uYqahvppLYW2RM2bHYcrRwatEyMn8cA5RnR8yW3znbes5jWye2YD7aMQdNjV3ruA1OnkfCkiWP8NO2dkhyk4fPbYS9mz/GBJCWEx9RyeMHLfdsT9kyWAKEEjkwSQGMQWgmOB1tNroOyFg6FupEWlUiN0P4UgaGMNdOXWW3poL%2BkPuGcR0H4PIfQ9h2qBZAP6Ms38Exz7rGUD084/9jjiQIdpDSNzKHSRuY0%2B5qodJfA6CiZuXch57yZMy4%2BV8n5Sn2MAqBSCgzmAIVQrENpxlumuUOYRdeIzBXQWmeQBE8zvBLNNJs5SpE9naWyWc7wVzbKPNcq8yxvgAqFDCtFeKoLyOQsSDC4IdHyGAiqp5VlzVNnkuiNS0vTgOxp6x5y2e61pSCu6r69Gl17get6E9RUYbzWSg5AqyGnI1WM2dYECmuNY3E3FejY32vI2BgVYm4MKb%2BaHUyOLQWhbRO3FVtFxksHEPbgC5h/CHyzaIMrJZvtlnR2TsDtLRd6LwH/D%2BD4aY57Ti988h3RW4nnAL0%2BO7UOkAkg%2BFjosTyJxujJDGK4PoswwQbH%2BFH2ey/B2qiBOBS5%2BY%2BHigBywqwzKWQzgkgQAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/fold_right/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/fold_right.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/fold_right.test.hpp)
