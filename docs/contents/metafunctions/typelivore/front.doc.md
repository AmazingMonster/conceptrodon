<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Front`

## Description

`Typelivore::Front` accepts a list of elements.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function collects elements of the amount from the front of the list and instantiates the operation with the collection.

<pre><code>   Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>I</sub>, ..., Element<sub>n</sub>
-> I
-> Operation
-> Operation&lt;Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Front ::   typename...
        -> auto...
        -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Front
{
    template<auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
}；
```

## Examples

We will invoke the `Operation` with the first three elements from `int, int*, int**, int**`.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**>;

using Result = Front<int, int*, int**, int**>::Page<3>::Road<Operation>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Front` using concept expansion.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to enumerate `Targets`.
        Prefix<I>...Targets,
        typename...
    >
    static consteval auto idyl() -> Operation<Targets...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `Targets` satisfies `Prefix<Targets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<typename...Elements>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCBmZqQADqgKhE4MHt6%2BASlpGQKh4VEssfGJtpj2jgJCBEzEBNk%2BfoF2mA6Z9Y0ExZExcQlJCg1NLbntY31hA2VDiQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACex9gmGgCC27v7mEcnyKPoWFQ3d49mOwYey8h2ObgIl2SmAA%2BgRiExCApfg8/gRMCxkgY0WCIVDmGxSAcmGdUMj7mggZhkgQDspiJgaKo3gARA5wryYY5WFEPNEYrGck64xisQW3B6jYheBwHABiJFeJgA7FYlcyuX9UejMUxsSd0gAvGEEAB0ZoAkmTJdKafL6WDPiAQGEsKpoUoAI4cylg81mk2/fzix4qv4HcNs7UCsMRsExiMRvk6vXgyEitj%2Bm4HPZMBQKA4AeSh8NqDFI8YTBwA9FWDgB1V5eJRHABsGjpDLwql9N0zbbZqAOjB8cV1irbABVGsBMAQkW2Aw9KxGO4ye0H/VPiDO5%2BWl8u2Wn8ZhM/vw2SE6NdXhkNmBKNMAA3MREkkHPDoS60CCLA4AWizItR1LMEtx3BRMyDDUUTVaDHl5KMxxxI9RX9bB6DYQQkSgiV2RlWViFkTVQzPSN%2BSQ/U8CNWEDnuFhVkEC8I2tGU6VQIhlCYGcK2Vbl7gPMjk0FcFEJTYVj0g7BswMPN/XuYB6XRRg5yY5cmzCYADgAJVQJh0BZA4sD2YUKwTCBTIPO1hMdEAWCYABrGEXUwN1PW9DYwTohiCEDYMBITJ0kwFd9P1oTyFMwJSsP9Ql0KiudJJ/Czw0WOCE2VdV/D4isgootxiSIOSIvi7C/IjdSjFpLjFX8Vk2I46rwsUzCErNQNstgrLNQeKsACp%2BoGwaqz%2BPr%2BonbAhAnAbhp6wa5t6mb4P%2BQFgVBd4BA2alSu6%2B5crElCMzanD7hYmkgJLTI4L%2BCrNKELxklSJR0C0zAFC8WgaWOVlzuvAQwTCAhCQB3qgcEfr2p2m7tNe97PtquVCMYk4AdBggQffMH0eB3qbidTjuJOfxcZAHS9LBH6QKgrqeROhpHGQaFcyUJoIBshRRUZ7C3Duh60kwZ6YY%2BwkXrej6blSrKOGWWhOAAVl4PwOC0UhUE4NxrGsA4FFWdZFQBHhSAITQpeWeyQFlgAOE0W38SQzCVSRJEt/wNFlgBOC39E4SReBYCQNA0UhFeV1WOF4BQQEDo2lal0g4FgGBEBAVYCGSM5yEoNAMToOIIlFThVAtls/xbSQDmAZBbykE0zF4fnCBID89H4QQRDEdgpBkQRFBUdQY9IXQuFIAB3eFkk4HhpblhXjZVzgCzONOaVQKgDkL4vS/LyuDmrswDggDxs/oYgjn1xZeGjrRlggJAs%2BSHOyAoCA74fkBgCkJIaA%2BuII4gaJZ%2BiGERolwJ68EAcwYglwCzRG0J0aOBss4tQLAwWgID%2B5YGiF4YA%2BVaC0AjtwXgWA7JGHEOgvA9IuiPlerPFynQzibANgDaos8LjRHhJAjwWBZ5wjwH7AhpAqHEGiHzZk6JDDAAuEYY2ywqAGGAAoAAangTAw8gKKwNi3YQohxCd00T3NQs9B76HESgDWlh9B4GiBHSAyxUDUkyPgv8nwvqmEsNYMwIdBHEA/NQmxVQaiZBcAwdwnhWh6BCLMUo5Q9CPUKFkUJuQh6xNLP0KJQwh4dC6HUaYEw/AZOqHA7o0xUmDHiBknJCS8m2GKZE0pEhljazWBsepXsODyyDrPUOa8i4lzLhXKukga771wA3E%2B2wuDn0NtI5YCBMB6SGD%2BUgZtJD%2BBNG7fwDsNB20kG2V2LY3atJ9qQP2/guDWy4C2C2HsLmy0kFwd2/gWwdP7qHcOkcpkx2vonG%2BydF7pyfi/Y%2Bec2CcEaCwR8So/xMGkuInebsTRnOVvXIg3j0DN1kG3HR0g9FKAMf3XQSRR5MHHgQqebSZ4vPnn85eq8wUQqhTCyqXB4WIv3ofe%2Bx9T7%2BDMJMy%2BscfmAriBnZ%2BqAj5DDpZCnMRhmVcEDl/NExBf7/37uA4BoDSCqsgdA2BDh1WIOUsg1Bs8MFYJwXg9VRDxGkOVvgChjgqH4KRaoOhaJ1VMJlv3Vh7DLicM2MrHhfCDaCOEUoURxCJEaWkXwORijlGqLxOqzRmKO7YtkPovuysCXGKka4qw5jWHWMWXY0sjjnG1Vze4zxcRUW%2BMWZk0sQSQk5CqREkodSkkFFLLkmJnbMglPmGU/xhTsm9G7fkgJI6mj9uieU0dlS9BXinbUgdLTGm6xaR69pwdeBdIlQyqVmlmUIpNBoYZ%2BAUVcomRfaZpBZnzPiIsj1RyTnwq2Uqd2SolS2zMDsu5zyQ6cDeVHKN8ck4pyXsKwVxBgWbDBZvFgChHy3kfEegUow67nsbmioeSbtEpq7vIXFGadB5CJSSyerSt2dKpanM4BwV5EmICweDiHkOobHKMNloqOVxC5f4XlIHb7cYfpB4Tx8QBIYetCFDbtoRoYIIzJjpc%2BB0AVUqgBQDIHqs1VAmBcC9WiqQSgtBNrMCYOwWIc1/DLUkL9YQ8hhSHU0OdcgehbrBDMM9ZY71vruHeMDbwYNIixEkMjZ86NXFY0qLUYmjFeGJCpu7kRwxeQDA5rMTYAt8BbH2PvJwKsjoK2WA8TurxPjC0NIKVkvwEBXBjqCME6d6T8jpC7fOjtrW%2B3LpnUO6rPRxjtd66WfrMw20rtnQN5tC6aljZnQ0nWzSJmUYpQBjgjHmNlwQ0hg4MmTTybPaMy9AnPkzLmVgB9ZLn0JHhf4fwstZZbNlRoW7SpLn/p3YB2w7y%2BWLFNiAO5JpHmyyVGYe7dz9mSA0EkD1/gVsfbDh8q%2BZLa7vbngjn7yxBHpGcJIIAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/front.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/front.test.hpp)
