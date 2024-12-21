<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRotate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-rotate">To Index</a></p>

## Description

`Pagelivore::CognateRotate` accepts an operation.
Its first layer accepts an amount and returns a function.
When invoked, the function relocates arguments of the given amount from the front to the end of its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper
   &lt;
       Arg<sub>I</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>,
       Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
CognateRotate ::   template<auto...> class...
                -> auto...
                -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateRotate
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will rotate the first three variables from `0, 1, 2, 2` and instantiate `Operation` with the result.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<2, 0, 1, 2>;

template<auto...Args>
using Metafunction = CognateRotate<Operation>
::Page<3>
::Page<Args...>;

using Result = Metafunction<0, 1, 2, 2>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateRotate` using concept expansion.

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template<
        template<auto...> class Operation,
        Prefix<J>...FrontTargets,
        typename...BackTargets
    >
    static constexpr auto idyl()
    // Note the position change of `FrontTargets...` and `BackTargets.`
    // Note that `Operation` is invoked by values extracted from
    // the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<BackTargets::value..., FrontTargets::value...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateRotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        
        template<auto...Variables>
        using Page = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsGqQADqgKhE4MHt6%2BehlZjgLhkTEs8Yn%2BABy2mPYlDEIETMQEeT5%2BQfWNOS1tBGXRcQnJqQqt7Z0FXLZTQxEjlWO1AJS2qF7EyOwc5oERyN5YANQmgW5ejrSEAJ4X2CYaAIIHRyeY55fIk%2BhYVEezzerwA9AAqSHg04AWQEqCIDDupyh4NBwIImBYaQMmIubiY11QpwAam08ExYvQga9JsQvA5YfDEQ9XiYkhZTpMmI5kKc0AxJphVGliKdCURTgA3MReL7sixk4gUqmYdkAEQunI1WuBwIhUNOymImBoqhRUPRr0x2NxasuBDuaUYrEwpHFRJpLwFuzSBCNJrN33VpwI9PtVjZYNRpyEAHc8FKGhbIVaXjacTz7W5Hc7mGwvXSGf744nkwqdYFIyD01jM3jLlkAF6YAD6BAAdF2AFKFsPF2MJpO0fF/EAgCJYVStpQARzlDF2%2BO7XY7QMCTzZHOBp13obrdvxO73J4zh8uEtQq8e/IMCgUpwA8s7iDycqRjyfd8bTXhVMvHlXAAxYhZAAFTaYBMAIBQP1eL891zF02FXCwmGQABrCDiCgmDP2%2BTcXhPbleX5AQhRFMVL1OPB0DuWgIDWfDQVBU4ogRL4CAQL4imyAR%2BQQQwoNOVAqHOAA2DQQPAyDoIUa9JPFBh0AkjQ0Mw7DcPkkxJOY1j2MxUNBP9HSNGfBI3wEUyaIfCIpVQDDMBU2JkRlbxMAfYUw3QzEVKoUCWD0ozOIPLNTjSNpXUxYhtPgvcAFob3M18mnxdSsNkmDxzcuVV3daTBE0uTstlTBrw3XUt01Ks9WjQ0PGAZhMQAJQRMLUTTM8s3xLqGwJIlyuwW8mHvJ8X0shg%2B3pRkGqazBWtaPEt2rU9Qr65s239F4WC2QQvWI/tGWNBFUGUJgoPwis4oQ/DVttbqLwGrslRVegFH2hDTi8LIjCNc75UCEMsGOJDbr3CAwYQ0th1HAh0HHFgmEc1tJ2FGdMHnRgl0ubbdoIddCM%2Br9x16r5aPo/Fkom904QYE6kXxF7KTewCu0eRjIdOJiauu84kmq6t8NJ/FL1XF5gBNLFGDwiree%2BiJgD%2B4SLhDY6iDOi6cYlzApcEeS2Yqnm3n5yqawNVELY6/UYzAjyYJTNFrct53HajN4zEORdPm%2BK4bnuL0MTW7NRYNwii0ZKnUqN4F5d%2BoQvDSIonOajyvFoEzAbGiyo7cMx3VSU45lOMx10F60g5Fp6OxeHD3tll5Y8VmFoKYKgvEXJpg1OWaswWh63EjnIvXHDXs0CYeQFH/Ea%2BAfW10NsuG5%2BxWU4UNOM5DZvWjbjuh8uAui7z4vS9ql4SLwZBWxGpR2ggMcQAUV0r7rtxV/X9148TzJk9T9PHm5iwHANi0E4P4XgfgOBaFIKgTgbhrDWC5FsHY8oPY8FIAQTQQCNgYQCGYDsSQzCSBqDUfwGgACc/gzAaHEjUYIICOCSF4CwCQGhUgQKgTAjgvAFAgFSBgyBQDSBwFgDARAIAtgEDSNccglA0DYjoAkKIrpOCqBqOJeK4lJCnGAMgPkUgOxmF4E5QgJBaJ6H4IIEQYh2BSBkIIRQKh1ACNILoOYcZXxpE4DwYBoDwGYOgZwR81wpH%2BlEqcVR6jNHaN0YXSQBjTgQA8PI%2BgYoDhcDWLwfhWgNgQCQHItICiyAUAgPkwpIBgBSDzjQdOCQeEQFiP42IEQ2h3C8bwJpzBiB3EfLEbQmAHBtNIHItgghHwMFoK05xWBYheGAASWgtAeHcF4FgRGRhxBTLwCaBwZYllQOFP064ew0ERExPQqBtxYivi6R4LA/iwx4GYcs0gSZiCxG/uqLEQlbhGEwRsKgBhZ4kjwJgOM5kIFoIscIUQ4hbFQocWofxrj9BCRQPAyw%2Bg8CxB4ZADYqA/Q5CWfFP4KtTCWGsFQ3gqBXnKiwDixivR%2BlNBcMpGYfg5hhCWBUKohRMh8VyJ4LovLig5GGNysYcw7BMv6AsNlegpU7IEAMdoYrRiJElbKwVsx5iDFVSsdVGwFBIN2BIHxHAwGkHYVSzg4S1EaK0TovRcSzAJNwCY1JqCMnoL%2BRsbiTAsCJAZTgyQgQOxkMCEkSQGhJCEMkhofw4kyH6E4Iw0gzDAhcA7OJLgNCyE1Bzf4SQXB/DhvEpa/xnDuG8O9QInJojcniOCdI4ppSUlKLYJwNoLApRJHikwYav0uBkI7Jm/Z%2BAiC0vMbIKxsLpDwqUIi5xug87uKYJ45ZZqLVWoCRwIJkjrgiTEl2ntfaB2KyHSOjsGgElJIKSk84HszBeqyYIhtraEgyJKagZJYxj29uOEJIdXBUjVOinUhpziOktMGVBrpPS%2BkDOecM6WYyJn%2BOmbM%2BZizBmrO%2BXsKB%2BBtmOCTHsoxqhDmYkGacho/jLnXLuLc/DmTlRPLQa895ShPlrOAD80Ata%2BCAoUMC0F4LBlQpnTYudsgEVOKgculFvyyVWAxZc%2BleKCXkU4MSuGpL0UWEpdAmltEPLwENQ0aVzgICuDlRy5SeqeVzF4k0Gz6Q%2BVNHsxKxlirmiavyOyrzTRlWLHKGq%2BVvmhUat1Vy0L6TNjbBNbF%2BhW6K02r/aegDg7h2jtdeOkgD6M3Pp9aQP1AbKBmtTem4d0akglqSEkQIMbJCaLmNuytthq0vrrfABtEiQmfvfcQdtewu1RJYAoKUfIpQXrtJMIxuXJ1zHEzCyTdj5ALtkzoEAwRV3ru8cm81fjnGcL3SEw94piAsFG%2BNyb02syTBvd%2Bu9CR8uBEK/xt9j3Cn9c%2BykkAE3E6tim2Q1sM2CBXwu5ovgdAwOUAg1A2Dky0EI/g0ywZyHRnjMmQRzAMy5liGw883D6ymOkEI9Kkj/iDnICOVRwQNHnF0ZaYx%2B5LHBnsY%2BV89ZCs/kCfOkJkFYK8xienctiQUn7HraRVthTxg9OYuxaZ6BGnBScFBGOJTFKOFGbpYrhVzKrOsq1f5zlIX9XCv5S5pzorotm8leZ7zQWXN65lVF03DmdXTCN2F13ywHOGuNTYzdh2OGpYh1osbE3pS3cxPdiAbqJ35fSZkorJWxgMvoRVkAZhh2BECP4UhRbWG56SDQ8tR3OBVr4UV4NSQDE1a4FIMh1Xw1cCSPtwIwfrVcJrdks1hiy8h%2B751jYrysjOEkEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_rotate.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_rotate.test.hpp)
