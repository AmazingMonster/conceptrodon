<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Front`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-7">To Index</a></p>

## Description

`Varybivore::Front` accepts a list of variables.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function collects variables of the amount from the front of the list and instantiates the operation with the collection.

<pre><code>   Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>I</sub>, ..., Variable<sub>n</sub>
-> I
-> Operation
-> Operation&lt;Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Front ::   auto...
        -> auto...
        -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Front
{
    template<auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

## Examples

We will invoke the `Operation` with the first three variables from `0, 1, 2, 2`.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 1, 2>;

using Result = Front<0, 1, 2, 2>::Page<3>::Rail<Operation>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Front` using concept expansion.

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Monotony
{ static constexpr auto value {Variable}; };
```

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
        template<auto...> class Operation,
        // We use `Prefix<I>...` to enumerate `Targets`.
        Prefix<I>...Targets,
        typename...
    >
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Monotony`.
    static consteval auto idyl() -> Operation<Targets::value...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `Targets` satisfies `Prefix<Targets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Monotony<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM2akrgAyeAyYAHI%2BAEaYxP4apAAOqAqETgwe3r7%2BgSlpjgKh4VEssfFmiXaYDhlCBEzEBFk%2BfgG2mPaFDPWNBMWRMXEJtg1NLTntCmP9YYNlw5UAlLaoXsTI7BzmAMxhyN5YANQmO25ejrSEAJ6n2CYaAIK7%2B4eYJ2fI0%2BhYVHcPzzMewYBy8x1ObgI1ySmAA%2BgRiExCAp/k8AQRMCwkgYMRCmBdUEcAGqNPBMaL0VGPabELwOI4AWQEqCIDFuaIA7BYjtMmI5kEc0AxpphVEliEd8UQjgA3MRed4mLkk4hkimYJUAEVO3K1OoB6Mx2L5GrOUJhzDYpElBKpQs2SQIR2UxEwNFUH01RwRCv1aKeGKxONNkOhjFYpvuTxpdKdADESIquXqdlZ/Y9A8bcWc0gAvOEEAB0xYAklSY/SE66Id8QCAwlhVLClABHBUgkMl4uF/47KPPZNPI7D71G4MAkcfNwTycjzPjs5S1Ddu6CgwKBRHADyMMR3VIM9nRwA9MejgB1d5eJQnABsGhdbrwqghZb7K/v3sJjB8cRNd40AAVRpgEwAgUXvHshyPZ1XXdV87m7YDiFA8CD2go9zXDNgVwwj5%2B0nU8jgiFl3gIBA%2BQAnc/26ExPzwTcwhlVAAGtMHQI5omuWV5UwFE8KI0UESYBx2KOKhiFQFhvQQMix3/JJGgjDFiAUKDHknXl%2BUFAQRTlWgbWlPB0GuWgICWI4AFpV2ovcMghZDUIUOt9IVFc%2Bz9AdtVTA0A3k7M3CXbsVTVegUQ86MfUrSTBANQcNLnfyQzzAsjkeFg1liiKEuHCsnRdFlUGUJhQMPE54pg0cgxNCF5xqxcCXc7A1yYDdu0eYBXUxRhwKpSrrzCYAjgAJSRAzTi9LADiwsrJwgWaYKrZKCHQOsWCYNjYQbUVm0wNtGE2CF0syghewIyqRzrOqMSOYzTKOzrMG6wQ1OLa0mQYQq2QhELyTCxDizucyFuHJZPMnFM02ePDrpDILiw6rq2BevqRwGoxnRKxUdi9AqiGK0qzkRp7kfAprPMh3zHmPAAqOn6YZ48AVpunAOwIRAPppmnhZhnGapl4QTeKd7UwR1wv7Q1qoC%2BGe2yvLt13Pl7J89N0aGoQvCSfJ2OGvivFoJ0JsVmiVbcRIji4a0zF7KGAXVkb9cNz0jjjGLTrOC2raOQIfbuOsCZDHZ/ZAUa6AhWzlYEW2qa0vBkFhVqlCaCBaxABQI0T8K3E17XUl1p2CGtPWFANj3sDB1MOBWWhOAAVl4PwOC0UhUE4adLGsHk1g2RUgR4UgCE0auVhYkA64ADkLW8dkkMwOUkSRJ52DQ64ATgn/ROEkXgWAkDREiblu244XhnMSIfm%2Br0g4FgGBEBANYCCSC5yEoNAsToOIIgjThVAn28llbySCOMAZAAopCFjMLwdihASDGT0PwQQIgxDsCkDIQQigVDqCvqQXQVsADuiIkicB4DXeujdh6t04FuC4L8nSoCoEcf%2BgDgGgPAZbSQUCjgQA8J/egEpdhcCWLwS%2BWgVgQCQB/JIX8yAUAgNI2RIBgBSECDQQ2cRnIQGiFQ6IYRGjXFIbwPRzBiDXC3NEbQNRL4Dw/qTLcDBaCGNwVgaIXhgCBVoLQZy3BeBYHWkYcQLi8CulqDKPiVDRQ1AuFsAeYQMS11wVcaIiIzEeCwFQhEeA96%2BNIOE4g0R86akxIYYAVwjDDxWFQAwwAFBEjwJgAh1Em4DyQcIUQ4h0FtKwWoKh%2BD9ClJQNYaw%2Bg8DRGcpAFYqBHQZB8ZZb4E1TCd0sJUXgqB8mqiwBM8yHQugZBcAwdwnhWh6BCHMUo5Q9D5HSAICYfgrbXO6AMC5wwrbVFqAIXo4xjk5DeZ0axdQZjPKGPEN5Mw7l6F5E0YFCxQUrAUD3TYEhyEcAbqQI%2BazODMIAUAkBYCIFcLMDw3AcDBH9xEYPSpKxZJMCwPEHZY9JA7ELGvHYC8NBz0kPeVet415bw4DvUge8dhcGnlwW8E8N7irrpILg68di3nRVQk%2BZ8QAX0qTfe%2BkjH50NfvIxRAif5sE4I0FgMoOSWSYC1DGXA16FlFS3WBRBNmINkCgzp0hulKF6bg3QgQiFMBIb4lFaKMXUI4LQ5%2BFwjiMMlMQM1FqrUHFKZbO1DqeF8JkQIk4QIzAUrEdfbVBq4hvwUVJLNwxTXmsssmowtquCJHUSpLROjcEmIMUY0g7azEWKsQ4TtdieoOKcVQ1x7jPHeM7f40pQSW74FCY4cJPjHWqGiRiTt8TOhUOSak646StgtyyTkge%2BTClKGKQEspg0NXVJKnUhpTSLSdrae6tBnrZA9JwS3P1AyKlLKsJYUZ4z4BTJmbpTg8yVqLOGSs4%2BGzjIRMmbsgFzgICuAhVbM5JQQVXNSDczIPz7nJDw0885OG/l7M%2BeCwjkL/kfJ6ECsjsLIXUeyERqFsxsPMeEasdYSKeOJNDcqrFVbE3WqGra%2B1hYNDEvwM6nNIr81UtIDSullAUWCuFXajlHJ14cg5LPMwXLZVKtwSq2warKVXwkVqpAT96GluLcQI1WxTVsJYAoGUAoZSSeDNMGBcn4GrSti%2Bjpb6MHyG9V%2BnQIAdikADUGsh/KhNmZobqhhTC3MgI8152UvmTTTAzeW2RCmdhKeszfKRxWBGOeq8MLz2tYQ%2BbXrCPzBBE7xuAXwOgzbKCtpbt25xA9Bu9usQOqS9jHHOLnZgNxHixCTtydOwJB6/EhIBUuyJq7kAxI3YILdSSxm7v3Zk1Ux7eCnqKSUwJ16Ku3tqfUxpzTn1urCxId9mCot9Ni7%2B4wMGbDJO2aB7oPjjy1n/dYVZrd4NbJA8h%2BjByjlsdOYcmFlyHkkYyBh4jBQMho9efD7oXzmg0YoyhhjfR8egtGH0bHHGqfIt473RngnKGpY4HGlg7nPPefyxiQrEASXyaEeV8R1LMC0uGDsxJmn/B2p2DsOudcOUNo0ArjkErTPH04Kq9V1nR4gFlYWBVdcORmCV7K3lkgNCBESTsNn2vT5WbF/y6BWvMVO4LUsFY%2BS0jOEkEAA)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/front.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/front.test.hpp)
