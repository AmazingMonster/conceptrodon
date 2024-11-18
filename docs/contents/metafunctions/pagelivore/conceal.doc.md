<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Conceal`

## Description

`Pagelivore::Conceal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and returns the result using alias member `type`.
Overall, `Conceal` turns an operation into its `Typical` counterpart.

<pre><code>Operation -> Page&lt;&ast;&gt;{type=Operation&lt;&ast;&gt;}</code></pre>

## Type Signature

```Haskell
Conceal ::   template<auto...> class... 
          -> auto...
          -> typename
```

## Structure

```C++
template<template<auto...> class>
struct Conceal
{
    template<auto...>
    alias Page
    {
        using type = RESULT;
    };
};
```

## Examples

We will conceal `Operation`.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 1, 2, 3>;

template<auto...Args>
using Metafunction = Conceal<Operation>
::Page<Args...>;

using Result = Metafunction<0, 1, 2, 3>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Pagelivore::Conceal`:

```C++
template<template<auto...> class Operation>
struct Conceal
{
    template<auto...Variables>
    struct ProtoPage
    { using type = Operation<Variables...>; };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGYAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7JoFuu/uHmMduTF5EAHQPx9gA1MgGCgrPAPJpCUyNTxMGgAghNiF4HM8PAwtmIgcCTAB2Kwg55o55nA7/S4nG73B4ANVaeCYsXoCkBqPRYIhBGeymIqCIyiYwEuVLRSIszy8WSMGIAnr9nscACLfX7Ef45K5E4gksmYBQPO6AwLcpGi44ohEcjF7LFHXG3VAquUK8mU4Honl84D01mYEWBcUMpmoFls2XE0nklVqnWa7Xw%2BEAegAVJGo9HQ2GowAVbBCeNR2MgiPRzNp3UIsyBCJvLxYZ1uNAwzBpAgUwLYEMgzEXK5402PGvwmmQn5/AHquvA3kRe1CLxpYqYdAAJSVXlodLFEu7MpOGlIzy4q7Mq8CAb7DexTZNKuBxGA1drIIH/IAspgWlQvDDGs7xdDYbQrl2pT3z8CQCBPTibjHqe/ptr2ILwpe9pTgoM5zi6zw3neD4OEubgrmuG5bk8f4EEKOKBiCcyOMgAD6TAfAkBAQBM6B/gorCYOR1ZuDBcGrsOo6ZOObGzk8yzahwqy0Jw/i8H4HBaKQqCcG41jWM8CjrJsTrmIEPCkAQmhCasADWASSHcGiSFwiKBBo/gaGYABs1lmAAHPZ%2BicJIvAsBIGgrhJUkyRwvAKCAK5aZJQmkHAsAwIgIDrAQaS3OQlBoPsdAJFEjGcKo9nWQAtNZkjPMAyDIGuhlmLw46ECQeB0eu/CCCIYjsFIMiCIoKjqCFpC6OuADuUppJwPDCaJ4nadJnBfLccV0qgVDPJlOV5QVRUlXcZjPBAHjJfQxAinmXDLLwwVaKsEBIElaQpWQFAQBdV0gMAUibjQs4JAFECxGNsQRK0AqDbw33MMQApfLE2iYA4/2kElbCCF8DC0H9nVYLEXjANctC0AF3C8FgLCGMA4jI3gxAQ44ABuSpjZgqgQ7c2waREuwiZ1tB4LEUrAx4WBjQQ8ruTjpCU8QsTcaKewE2zRjaasVAGKeBJ4JgPVdhJGl1cIojiM1GttWoY3dfoBMoPJlj6OzAWQKsqCVjk2PZbRYqmJY1hmD5wvylglsQKsdhkzkLgMO4nidHoYQRMMVSjOuxTZAI0x%2BDHmRxwwCwjIk65%2B6hAj9FMIcFJn9T%2BznkyDBHizR7YpcJ3ocxtGnUcZ77ylbBIw0cGJpDebwvnzVluX5YVxVSGtG24JVu1qQdR0y6sCCYEwWCJD7pD6ZIgR3MkgSIpIxlmJI1mef41mpCzrmkO56l3NZXDWfZyT2bf/gmf4W/WV3Y2%2Bf5gWaTLYWRWdaKU14o3TujtNKbBOCtBYOTRE2UmCvAMPyLgyQ7hcCMuVfARBPZ6A1g1bW0hdZKH1p1XQm4%2BpMAGjjdundu7jQ4JNWKtxnizWeNA2B8DEEEzXKg9BGgNpbUujtPagQzCHV/iFU651UDbQSAlW6MihGjHYXAt4BMUFcBXC9XYxB3qfU6oDX6UNDHA1BuDSGgsYaMAIPDRGY0UZowxljKGeNJbbCkvgUmqFKbYykjTOmuwoZM3qGNNmHNfrc3cUdfmUNhaiyUOLfGRgpagEkXweWChFbK1VlDPBWsmqENkHrDqUkyFG2ls7KwZswne2trbAQ9tHYukqa7d2CRPZUytj0YufgICuBruucOFR056Fjo0AZ6Rk6NAbksQuvQS4DAmVnRoucy7DMbrXau%2BdE5V3mOXEZB01gbFboclmtDP6cDYcQGBcCEFqOQbwoyY8sEkBEdPCRJ054LyXpQdu59L6oOMoiV%2BiIzKSH3nldcdCv62B/sdUK4UooxWmvIsBqV0ocGgUtFgChybFXJigu4FwJiYIntVXBsh8EFJavIYhJSdAgGCBQqhQ1nId1Gp1XyjDposLmli/KOK8XPAJag4ldJNqKKuiIwI4j4VSJQJKnaqLFWjDxaOUiIrSJivItcvKfA6A6L0V9H6wNjEmpBmDMmUMrFwwRkjDxmBUbozEM4wWrjklRNIJ4/2Pjqa02QPTIJggQms3ZpzAUkTeYxMFnEsWEtkmDj/nLVkmSlYq1%2BGrXgeTGoSEKa1OlBtGXlOMKbGwNT4B1MaNjUMtETYu0sG7HuHtqqdJXssgOfSg4TKGZHWZkySg5AmWMnIMzK7toWXnfIOzx1NFLqOjOuzJ2h0znO/ZGzDlKWOU1GhHKfKXP5c8QV%2BLCViueRPN5srZ6kHnovUYK8z5uTGHcQIgR/CWRMp5F9iI74f05Zwb%2BQUr1r38Jvfw9kbLJEkMkMy28uDBBZoEXdPd/0fJ0mysqv691%2BVQ8sVYwssjOEkEAA)

## Links

- [source code](../../../../conceptrodon/pagelivore/conceal.hpp)
- [unit test](../../../../tests/unit/pagelivore/conceal.test.hpp)
