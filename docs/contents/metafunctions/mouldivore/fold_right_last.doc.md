<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::FoldRightLast`

## Description

`Mouldivore::FoldRightLast` accepts an operation and returns a function.
When invoked, the function right-folds its argument list using the operation with the last argument as the initiator.

<pre><code>   Operation
-> Initiator, E<sub>0</sub>, E<sub>1</sub>..., E<sub>n</sub>
-> Operation&lt;E<sub>0</sub>,
        &vellip;
   Operation&lt;E<sub>n-1</sub>,
   Operation&lt;E<sub>n</sub>,
       Initiator
   &gt;::value
   &gt;::value
        &vellip;
   &gt;::value</code></pre>

## Type Signature

```Haskell
FoldRightLast ::   template<typename...> class...
                -> typename...
                -> typename
```

## Structure

```C++
template<template<typename...> class>
struct FoldRightLast
{
    template<typename...>
    alias Mold = RESULT;
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
template<typename A, typename B>
struct SubtractHelper
{
    using type
    = std::integral_constant<int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

template<typename...Args>
using Metafunction 
= FoldRightLast<Subtract>
::Mold<Args...>;

using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

static_assert(Result::value == -1);
```

## Implementation

We will implement `FoldRightLast` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct FoldRightLast
{
    template<typename...Elements >
    struct Detail {};

    // Base Case:

    // Fold once.
    template<typename Element, typename Initiator>
    struct Detail<Element, Initiator>
    {
        using type = Operation<Element, Initiator>;
    };

    // Fold twice.
    template<typename First, typename Second, typename Initiator>
    struct Detail<First, Second, Initiator>
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
                typename FoldRightLast<Operation>
                ::template Detail<Others...>
                ::type
            >
            >;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQSGqQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJXEl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbrv7h5gnZwCeyYysmAB0LyfYANTIBgoK7wDy92ITB6bxMGgAgjNiF4HO8AGKedAAJTwwAQAyYMzB4JMAHYrBD3kT3ucDsCrqcCHcHmwXk9sPQ2IJfqDCcSoTCCO8ACKYRp0d54qy47knAk4tlEgD0UveFkxmHebgVIGx2OJ7xl8MR7wEWye6uJpMu1yp92YbHeDL2jAIpBJ1ItioAkgwMsCSKzwRqObDefzaNdrUy7e9Xe6iMQvRqhYaNUSvOkjA77oLjtz/oDgZkg4zbfbw44PVHjtgxXHBSLyxCK1qEbR0CSAO54fUV43k02Ox7wvDEGb2s00xVCWoCdCD7uWwt4YvR9kEaF%2BvlMOjXOF9gfvUdoBgTsNuouR%2BdE2OS%2BOJ8LAFNXc8x9PEgHxbMCdebu0V%2BOPrMg0478ekJ%2BX7xjOc53sBJ7AaepbVt6xJ4qKxzirWspIrUGzpAAboqypKKqNbnlqADqxCEIq6xcgQCCKt8lFNqg7z8A2Cj2gghjoPQJLUYx77NgxyRNI8uz9oBhGyux7zEOh/aKpeyZUYqUkzCSDGoDE/IMFxirhBGJAGueHZHJSU6Khu/ahkOTrbmOe6Tuajx0n8Cn9pBvpcv6q6BqcZlbv%2Btn/M5Ch0pBZ5wV%2BcnXkOQHQRmRJPkCv5uD5H7gV%2B8Uvgw1x%2BRO0VQTeVn1siqLoiEmIENc6W/mWqV5SAICGYqHlrqcTnUf2wUwTVUF1VFXXwZ1YV5aCSEVghsHtnsZJGbc9m0i84LAFJNrMpBEXvAAsjqJwZk1XluAtS0hkFrylj11LjVWI0EeCUoAFT3Q9j1PVK2J3Q97wACqYDMvyPS9EJvU9QP3f9Eo4mYxzhF8XhYGmbheI4tCEDcXrYg1XazYq4J2cOcpem525eOpQIOAAEl0gJqviFZrb1g3be8MzoHV4S7ItYgAPq7jMhjlacrP2uCdWYWIXiKgAtHKwuixSZZXTil3IRC6PGZjdLgsQwAKF6a1CETi5MLCDN68ThsEOTtCU6cGtax12Bnfc43K5NJqq8O6ua9rA1retK5UF4DB1AIgo1g%2BhUomiGJYn%2B%2Bsk3z1VCyAm0NtcNvHQaMHy9ia1oQoXi0FyDO%2B40/uByCoduBWTMs4ImDs7QXMCDzgjXAL7xcG8omDdXICs3XQIN9zjQt/zgj2scndVwQzO97X9eNwwzd824beSJP5493389D7zrdj%2B8E8DcNSuQo0jjIBzmJKM0EC5/nBDS94irbQz4tcMsYocKstCcP4vB%2BBwLQpBUCcErpYawjN1ibGfhDHgpAH6AK/qsAA1gESQTwNCSC4LiY4Gh/AaDMAANkIWYAAHKQ/QnBJC8BYIkJIACgEgI4LwBQIAkgIK0KsOAsAYCIBABRZICNyCUDQPsOg8RIiPE4KoUhhDxaEMkO8YAyBkDt3QWYXgmB8CRjwMzII/BBAiDEOwKQMhBCKBUOoRBpBdBBCbECZInAeDf1/v/TQvAmF/ARoIrkqAqDvBkXIhRSiVFqKeGYd4EAPBiPoMQQUsDli8A4V/UgEAkCiOSOIsgFAIAZKySAYAUgzB8DoMJVhEAYjuNIDEcITQbhON4DU5gxAbh/BiNoWoCC4GiJDH8BgtB6nWKwDELwwBlS0FoKw7gvAsAsEMMAcQQy%2BydLwNhKZQDMCqHQrsBp5Ba4/2sUjGIQIWkeCwFUxceBaHTNINhYgMQ0iYF5HMowSMjDuNWFQAwWsABqeBMBNifAAuBBjhCiHEKY0FFi1BVNsfoeZKBrDWH0HgGIrDICrFQMkHoUzxZM22qYcBlgzCMLuaRLA6KICrBqEHPwEBXCTD8EEUI8wygVD0AUDIAhGUcrSFyhggw2VLE6N0eosweVBBpT0PozRBXDEqGMfoErFWytZfKiQ1KoFbA1ZQjgf9SAMI8ZwAJsj5GKOUaoqQ4TIm4EICQeJxx35JI%2BasaiTAsAJCpaQVBkhjhPAAJzHFxJITBZhJCEI0Hgwh/rdXUNILQx1TxCFcEIaQ/1pCU3%2BCwf4QNhCDVVKYSwth8CPmpN4Wk/h3ihE5LybEyRbBOBNBYJhXE4smCfAMMmLg/qnhcAwZo7RJBdF6FBUYiF0goVKBhdY3QxT7FMEcdMlxeq3HWM8VW3x/im0trbR2%2BZ7ce19o0JE6JmTYkOrMIkktiCuHpNQDE%2BIwjcn3rPSMbdravjzO7VUEpBd4jlMqdYppdTdnAZaW0jpDhdk9NtH0gZVThmjPGZM3Zsz5mLKAfgKSdQ1lVM2ds7YcC%2B4HKAUck5NwznbCAZc65cC7kPKUM89DV5S1fKYL8/5gLzS7NHeCkxE7ZDQqsUA2d8L3mEqsJYFFaL4CYuxZkXF%2BL0wSesCSjxZLdHfVkyKlZzh6V7mVSy0o6r8h8p6MqzlPQ5WLAVVKsVSrPBtD0HZgQMq5jGZs858VjnciStmNZ9l781gbG1UFg5%2BrDXAONe%2B3dn6u2HowTawdcTzCOqvck5YrrMDupGF6g5caE09swbiHNuIcGSDDQooIkXC22GLRlst8AK0COrSIl9WT63bCbcElgChMKqMwt2p4lwZgDrteSkdsgx38bMfIKdwmdAgGOKQedi7nG6oiwWzgXiCA%2BN1Fu4gLAet9YG0NkbXIontfPal446XS0VtrY%2BmtV2Rj9eSMkDmg3/Uc3O5fQ7Cjf1lMoIBoBYHBlwLBxBzp0H729P6YMzDmARljLEChm5aHXlUZmcsnDWnrH4eQAjQjvBiNVLI3UyjFzSK0d4PRx5THXksZvXwb5Cg/kAqBTxqbfGJACfMfN2FS2xPGCRVJo5lK5M4s4FKauKniWkviOSrTGKdO0pcAZnzTLgh7gC8KyzmQLNmcyLr2zXRdO9G8zkLXLmLf9BN15hzVuHeqo84FzVIWTHLs22u6L/3FG9f6%2B8L7w3yTKQgLayMDqnXXs4VlnLnrl0FZAGYHtxxjj%2BHwVgyNafcSpvzT75hdX2Euu9SASQ/gA3%2BFIUQ/1kh/U4KDVwZbBzjirsYZwZ1N7l0aPz%2B3wvGXVh3PSM4SQQA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/fold_right_last.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/fold_right_last.test.hpp)
