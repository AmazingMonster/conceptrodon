<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Inject`

## Description

`Typelivore::Inject` accepts a list of elements.
Its first layer accepts an index, which indicates a location in the list.
Its second layer accepts a list of new elements and returns a function.
When invoked by an operation, the function injects new elements into the location and instantiates the operation with the result.

<pre><code>   Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>I</sub>, ..., Element<sub>n</sub>
-> I
-> NewElements...
-> Operation
-> Operation&lt;Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>I-1</sub>, NewElements..., Element<sub>I</sub>, ..., Element<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Inject ::   typename...
         -> auto...
         -> typename...
         -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Inject
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold
        {
            template<template<typename...> class>
            alias Road = RESULT;
        };
        
    };
}；
```

## Examples

We will inject `double, double*` into one of `int, int*, int**, int**`. Then, we will instantiate `Operation` with the resulting list.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int, double, double*, int*, int**>;

using Result = Inject<int, int*, int**>
::Page<1>
::Mold<double, double*>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Inject` using concept expansion.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<typename...NewElements>
    struct ProtoMold
    { 
        template
        <
            template<typename...> class Operation,
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl() ->
        // `NewVariables...` are injected in the return type.
        Operation<FrontTargets..., NewElements..., BackTargets...>;
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<typename...Elements>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        template<typename...NewElements>
        struct ProtoMold
        {
            // Note that we use a parameter pack in the template head
            // even though the function only allows one operation.
            template<template<typename...> class...Agreements>
            using Road = decltype
            (
                Enrich<std::make_index_sequence<Index>>
                ::template ProtoMold<NewElements...>
                ::template idyl<Agreements..., Elements...>()
            );
        };

        template<typename...NewElements>
        using Mold = ProtoMold<NewElements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxAFcpAAOqAqETgwe3r4ByanpAqHhUSyx8f6JdpgOGUIETMQEWT5%2BgVU1AnUNBEWRMXEJtvWNzTltwz1hfaUDFQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACeB9gmGgCCG1s7mPuHyAoE6FhUl9d3ZpsM2y8ewObgIZySmAA%2BgRiExCApvrcfgRMCwkgYUSCwRDmGxSLsmMdUIibmgAZgkgRdspiJgaKpngARXYwryYA5WJG3FFojHsw7YxisflXW5vYheBy7bAMYh4ZAIfYAdisSsZHJ%2ByNR6KYmMOaQAXlCCAA6M0ASRJ4slVJlcoVILe6BAIDCWFUkKUAEc2eSQeazSbvv5RXcVT9dpGWdq%2BVjwUK2IGIpgAO7YehsQQIkMRqPWqU01BEACynnQucjJhV%2B1uUbr0d5uvZtfrlcOFdbUZ5Or1oPjuMwgcuu22TAUCl2AHkIbDHAJSB3O7sAPTL3YAdSeXiU%2BwAbBoaXS8Kp/Zch/uWahdowfHEm3uNAAxYiyAAqDWAmAICP3QZbS8jQ96VPENA2fN8Py/BQF3/ADBQHQMLCYZAAGt32IT9v0XKMSSXN5dXlEcBDeTAADcxAJIldjwdAzloCA5l2ABaXDO1XB9kxTAA1Bo8CYaJ6AUc8NAJWlqIYbRqhRdBxJZBAnlpAhlgYFl4z/G4l2nO85wYEFwMEdDMKEs18U49NUUYb9A3xJDUMMqChxzfxOQ0nC1Q1LlXMjbtYwFfthSTVNzMzLCc1g7cwmAXZS1oGSDmZQsSzLEEzIzSzjKDJyXKrdVnM1bkYybOMcQCs1gvSq1WSlc0JKkzVw1gnyiv1PAjWhXYavdVjI3zKlEtQZQmE/DsqwsHDYLrJre3g0qTVSiys26%2BteupF8kti7DKwaryAM2%2Bt2IiIsngIBBdV2FMtx3JhdiSBphRRYgbuQlDZJO47CpRXZ5KYcsJrYtcyMYOSlmARU3t2KgvABHTdgEWgzgJWhaFQFMJwEJ5UBnAiBHUgCuw%2B/lQQJ4qE0HM1h1HcdAxuYBaQW0LQzxyMIqMXYACVUB%2BpldiwbZBT2usIAFzs7XlBBHXeF0WCYFCoTdTAPW9X1Vn9BguqcxmmbrF0pqefqYvLQ55pCjKlq1nWCeo2jaBBGm6ZN6zpTSrNHOwBjhcjOYPJ2uscu9vbdZJhCzWNiqwp9qMWaig3uf15KjaC52rPJrKRvcvLPMm4nDkJIhqdpzB6ezTXmbSVnBs/WO1oGobCbtwuHZTq4M7DXLstuZcACpu573vlx%2BLvu9fbAhFfHv%2B473up87ie7iRP4HiBJ4QTJVZKWL/KbkDvySsTJufhWrTZwyf3bij3YhC8JIUiUdA2cwBQvFoKl4qnLGdJBMICHxdAlgEzAf5/3oJ3fEX8QHiQIN3YM7cbjn3vo/Z%2B3MaqSQcJ/QQoDBDgLAZ3EkLoK6Ey4LgkABsQS/y8P/QB5DgFEI5j9EER9sa6VTp5fCjhkCQjHEoRoEAnQugUMKDh2Y3DwKft/C%2BV8b6YDvg/URlwvbOQ4AsWgnAACsvA/AcC0KQVAnA3DWGsLsBQSwVjLz%2BDwUgBBNCKIWChEAKiAAcJpdz%2BEkGYJUkhJAOP8BoFRABOex%2BhOCSF4CwCQGgNCkA0VonRHBeAKBABEyxmjFGkDgLAGAiAQBLAIEkY45BKBoDRHQOIERhScFUPY3cTFdySF2MAZAyBdhSBNGYXgUjCAkBonofgggRBiHYFIGQghFAqHUMk0guhEgplhEkTgPAlGqPUVY7RnBJzHFyVSVAVBdgVKqTUupDSmmSBabsCAHgin0EehsLgcxeBJK0AsCASBClJGKWQCgEAXlvJAMAKQZg%2BB0AevEiA0RlnRDCA0M4czeDguYMQM4k5ogoKSeYwpIVJwMHhssrA0QvDADcGIWg8TuC8CwNLIw4hxn4FpDUUiD9lkK2qMcNY5iv6YGUeM040RYTwo8FgZZMI8ChJJaQOlxBoipEwIyVEhhgCnCMFYhYVADDAAUFxPAqYtIaPMT04QohxCDN1SMtQyzJn6FlSgfRlh9B4GiPEyACxMY6WJUxJ08VTCWGsGYaJYq5RYHtQxWw7KpIZBcGrUYfhEghCmCUMoegb4FEyJ4Fo8b8g6V6LGgYlRg0dAYF0EYyacjZvsDpfNkxij9HiJUCYEa9D4UaBmytEgFhGOWKsZtgSOBqMicsmJOzKnVNqfUxpzSzCnNwB0q5ZjbkWMVQsb6WB4iBtsZIfwJpfH%2BHcRoVxkh9w%2BN3L4ztwTSChIqE4rgu57H%2BIvSoyQXA/H%2BF3D28ZMS4kJNnckx5GSnlZPWXkj5XzLmlLYJwBoLBSJKiYtdUcrMuC%2BJNFwE0Wj2lED9d02QfSDXSCNUoE14zdD/OmUwWZJKFldqWS%2B1Zf7NnbLAxBqDI4DCwfg4hkSZzUAXLiPsP4ZgZ33JST%2BwDcR8mfI468y5IA6OQZg783xXAIk0GfnEYFoLxmwshdC0g6n4WIuRZptFlkMVYqpZgXF%2BLCXEvMWS2VlKtHUpDXS4lyHVBMpRJptlHKtFcp5WcPlawtGCuFeYsVEqlDSvJXKyKiq%2BAqrVRqlMWrNO6swwM7DshjVjK0QR81CqPVWGtVygNjrKQZBdW6/wjI8tep9XEP19KHVBpLaGiArha1RrVo2mYVa8hpB0m1nribOtxuLSGzoNbC2Rsa6NvNEwhtZqGN0fr9by3TGGy24x7abmdu7VE3gfapMMZk00ljSHx34FQ9x%2BYdy52kAXQMQNHLj2nvg9upUfilRKhcWYXdd7n3RM4G%2BxJ0W0mZOyRskTQniDAbWGB/ZLAFCkUaaRODJo%2BRvDaedzpzpEjJf1aloZ8hcOZZ0LkIjJH5nbYo/9jgaycnHFhrR4gLA4cI6RyjtHVJ2Ocanf4fwfHgfPLE28iHQuJOI%2BvpCZHvjIQc44UzmpAKlPEBU2CiF8LNPaYRUiqS%2BmOPosxVCkzZmCVI0s6SmVFL/OkrwDSxwjmGUueQMy9zgh2XLO85CvzAq5RBd4CFyV4WbNRc/TFoacXNU4iSxhvHEg0vDKJ6a3ITHjBWpsIV%2BAxXnWcGXLwqrlhvV7d9TRergb2g6TDe4Cbeho0Vq66m3rGR%2BsJvTTGptI3c1lqWzm0ts3W91%2BrYtqvA%2BG197W4sNtAyyM7d7ZwUSzPanw8R7sKXqOmxvDO5Oy7NzrufvnZgH692yNPZAGYeDvOVEqO3fJjQvOlSXr%2B3tgHth338bmDYkAd6TSPpUUqMwF%2B70HqSAaD/Icr%2BBU6P6xIfoPJkatIP4rKQGv4LBippDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/inject.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/inject.test.hpp)
