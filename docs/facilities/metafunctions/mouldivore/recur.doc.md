<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Recur`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-recur">To Index</a></p>

## Description

`Mouldivore::Recur` accepts an operation.
Its first layer accepts a list of predicates and returns a function.
When invoked, the function instantiates the operation with its arguments and uses the result to call the operation repeatedly until the result satisfies all the predicates.

<pre><code>   Oper
-> Preds...
-> Args...
-> (...&&Preds&lt;Oper&lt;Args...&gt;&gt;::value) ? Oper&lt;Args...&gt; : (
   (...&&Preds&lt;Oper&lt;Oper&lt;Args...&gt;&gt;&gt;::value) ? Oper&lt;Oper&lt;Args...&gt;&gt; : (
   (...&&Preds&lt;Oper&lt;Oper&lt;Oper&lt;Args...&gt;&gt;&gt;&gt;::value) ? Oper&lt;Oper&lt;Oper&lt;Args...&gt;&gt;&gt; : (
            &vellip;
   )))</code></pre>

## Type Signature

```Haskell
Recur
 :: template<typename...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Recur
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will increment `0` and `-1` until they are greater than `9`.

```C++
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename Vay>
struct AddOneHelper
{
    using type = Vay<Vay::value + 1>;
};

template<typename...Args>
using AddOne  = AddOneHelper<Args...>::type;

template<typename Vay>
struct IsGreaterThanNine
{
    static constexpr auto value
    {Vay::value > 9};
};

template<typename...Args>
using Metafunction = Recur<AddOne>
::Road<IsGreaterThanNine>
::Mold<Args...>;

using SupposedResult = Vay<10>;

using Result_0 = Metafunction<Vay<0>>;
using Result_1 = Metafunction<Vay<-1>>;

static_assert(std::same_as<Result_0, SupposedResult>);
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

We will implement `Recur` using a helper regular function, which utilizes `constexpr if` statements to decide whether the recursion should continue.

```C++
// `Sacrifices` are the arguments that will initiate `Operation`.
template<typename...Sacrifices>
static consteval auto idyl()
{
    if constexpr 
    (
        // `LessonsLearned...` are the predicates.
        (...&&LessonsLearned<
            // `History` is the operation that will recur.
            History<
                Sacrifices...
            >
        >::value)
    )
    {
        return std::type_identity<History<
                Sacrifices...
        >>{};
    }
    
    else if constexpr 
    (
        (...&&LessonsLearned<
            History<
            History<
                Sacrifices...
            >
            >
        >::value)
    )
    {
        return std::type_identity<History<
            History<
                Sacrifices...
            >
        >>{};
    }

    else
    {
        return idyl<
            History<
            History<
                Sacrifices...
            >
            >
        >();
    }
}
```

Note that we wrap around each result inside a `std::type_identity`.
This is to avoid creating an object of an instantiation of the operation, as it might be impossible.

Here is the entire implementation.

```C++
template<template<typename...> class History>
struct Recur
{
    template<template<typename...> class...LessonsLearned>
    struct ProtoRoad
    {
        template<typename...Sacrifices>
        static consteval auto idyl()
        {
            if constexpr 
            (
                // `LessonsLearned...` are the predicates.
                (...&&LessonsLearned<
                    // `History` is the operation that will recur.
                    History<
                        Sacrifices...
                    >
                >::value)
            )
            {
                return std::type_identity<History<
                        Sacrifices...
                >>{};
            }
            
            else if constexpr 
            (
                (...&&LessonsLearned<
                    History<
                    History<
                        Sacrifices...
                    >
                    >
                >::value)
            )
            {
                return std::type_identity<History<
                    History<
                        Sacrifices...
                    >
                >>{};
            }

            else
            {
                return idyl<
                    History<
                    History<
                        Sacrifices...
                    >
                    >
                >();
            }
        }

        template<typename...Sacrifices>
        using Mold = decltype(idyl<Sacrifices...>())::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM9KuADJ4DJgAcj4ARpjEIAAcAOykAA6oCoRODB7evv7SaRmOAiFhkSwxcUm2mPbFDEIETMQEOT5%2BATV1WY3NBKUR0bEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHOYAzKHI3lgA1Cbbbl6OtIQAnifYJhoAgvcPBJgsKQavJ26v75%2BY3wIVxSjFYmAAdJDbod9kwFApDgAJPBjEg3bZ3R5jYheByHABKmGQa2eJkSVkehyph1%2BHyYX1OtP%2BgOBoLYkPB0Nh8I5QUw8IECj5zTC6Fuz2ph2xuIIh2UxFQRHxqCYYsp1LJFIekslTPpAMZrOY7MhQiYyGIeBoGwU4vVOqlTUcyBhgteADcxIcmOdUIc8OgrrQIIsJQ7juSw%2BHqVbXQwxphVCliMd7dHDhAo%2BnJQB6HPHABsGj5AvjwuIoo5JiL3uImBpCHrycw%2BFErwUnLT2apECrZgL5gLJYUgvLou%2BWe7OrzhY0yNRxBuNZRDfrqBBxHpWQb9MOAHc6LRDnXicRO9qp%2BH50RFxOu5eHWaLVa8Daq/eH3aL5%2BMSAQJ7vEwUMPx1YDv3TTVJ27OsCDWBhHXQP8gRBAB9ANGEcIFvmvNE73Ah9H3NS1rX5d98O7cUMUgxIABETi1KcyTokDJSgh1aiUf0qDjBMkxTNidUzFjw17KF%2B0HYdR0wEUWzwgidRw29TgEqdFPRNwVIIp9iNfUioWE7Mv3k1iqIMnVbj/ACvCAzSqTAxjIzMyUYLghCkNZNCsEEa5sJRG91Ns9M1Lk4zCOfEiO308if0xaKIKoqjI1o%2BjAqY0kzI4gEzMgpzqRcit/UDWgQtC4LlNyh0yo0ir020l83yi0KqSMpqWpikMUuy5KQLSx4BL1BkfiNMEOTqiK2p1LwMiMQ4AFlPHQY5thow4sH2ZDMAgAMg2%2BMbdMizkMRDRZ3JBTrwLS7YtSzAaDR%2BN46UGjbjQhKEMRhAweUhB5gDrN4MNtUzwKm0JgAJFVFpOFb5UVVBlVVb4fr%2BthBAOyjruSq70oeHMACp8YJwmiZzZ48YJw4ABV%2BQIBFCZJx4yaJpn8fpp4%2BrMXYGH2Lwjm%2Bc46B8oHScJuaBFhhgrkOOnnlu74fSIQ4AEkv2lPF5oYcWbj68lHS3F00HjV4%2BO9X1Dis%2BtNWVzGLAjOisb6hmRYedB0AAeTCKWCdZ2XDRBF7DgANTEFWCBxPFnbdsJEVqDdSUc4HprBjalpW9XNe%2BIPaEssRrOOSxDi4dG47t67Hh9oa/ZG77iGAQHYpBmaI/d%2BsU8OJuo5j2JEZrtHfxADbzuF8nFYUABxOt9WICmEEMcJQnraWy4e5lfbZetM5DsPZRH8fpNeKeZ4YOewjjhjqRmZ0eKN5MTYV82s01TPs8ApbsEOABOS6MZL7Hy%2BeqvwQPB7l%2BBuYNZqYCaFQLwXN6it0JKeRGLtm5fj/PDMUpwd4T33tPWe88UEgHmrQdBbggG1yrAlUuDxQGHCEF4FIhQWyEgUF4Wgsooaiw1kQCW3wuAaCLg7KhicCT8hYQQFCGhW7gMgdAhwWRvhpy4epPhCU7j20EaDYRzDWEoS4JIiBTAoEwLkacBRAh1IAFpC4qMHliJ0r4UJwiUC0CAYxEIgAUGCBxgM3BMNEeI0gNC6EMPQL41htxQxqIvvYxxsQCAuIIG4jxbAvHfFCWIrgATaH0PSIwkRYSMQRIsBwZYWcOAAFZeB%2BA4FoUgqBOAaUsNYKUqx1gWw5jwUgBBNDFOWAAaxAGUsw4JEgBHiPEMpGh36DI0AWeI2x9CcEkLwFgEgNAaFIFUmpdSOC8AUCAdZXTqnFNIHAWAMBEAgFWAQFI5xyCUDQO8OgsRwhgk4KoeIBZzEFkkIcYAyAXRSHBGYXgLZCAkADHofgggRBiHYFIGQghFAqHUEc0gugMl7k3CkTgPASmcAqRs7ptTOCu3ODc2UqBuLvM%2Bd835/yC6SCBRmDwjz6D8XaYsXghytDLAgEgB5KQnlkAoBAAVQqQDACkGYPgdB957IgFEIlURQjNCuDi3gyrmCLldlEbQRJDkdIeSjAg7taBqtRVgKIXhgBuDELQPZ3BeBYBYIYYA4gLV4BPI4d0/IiWJiJOcTYHTQivFKTUy4URNyLg8FgIloc8ArMdaQH1xAog5Jom8V1lwjDdOWFQAwtcA54EwHuV2ft1UIuEKIcQ8KoXyCUGoIl6L9CupQNYaw%2Bg8BRD2ZAZY656gOvMa4qGphGmWDMFslNlosA9pDF0fVWQXAMHcJ4doehgjz3mMMDJhRMgCEmH4Hd6Q90MDmEMOIGS7ALoEL0CYq68iXtqNeho4x%2BibvPXoGYd7ciHtsK%2Bs9FRt3LBHGsDYEg8XlMqUS7ZhxqVfJ%2BX8gFjKzAZlwGC9l2wuCcs6bm5YjZVTDDnf0yQ2xwTv22IkSQGhJABCLBoMpBZ34LI4Es0gKzMPggLFwWZ794jcbKZILgZTyMFkJai7Zuz9k4aOby85fLLlktuSKsVbKXlsE4M0Fg7pEjmKYB9V1Bd37gi4OCGpoKbwQoyXWmFNbpB1qRY21FuhpWYqYNix1EGCWbN4Ns0l1zziHEpbWLTOm9OwhmlwIzJmJEQBZYKtledthmGw9y458mVOxDuaK1ArLhiae0%2BY8Lkr368Jlaw2I8rFWos1aqitNXtW6v1RWo1GFTXmpqZa61traD2orc6rNmwOueoXT6h1ZnVABteBWkNtQiURqjVcGNg2uWWkTR0lNaalAZpdUYbNoAZN8ALQoItJay2MArdZ6tcK7OyAcyimpzmW05tHVYSwnbu3wD7SkAdnAh0JJHe28dk7YjTt9b2%2BdsjnAQFcAe9dy6AMLCPUULIsOkcnoR9uiH9Rb2tHvb%2Bq9kOX2zHfYBi9f6%2Bio/Jy0DHF7gMtLA1h5jXnoOcGCwVsLBgItRdM6h/AN5EtYa5bh0g%2BGsBxDnaU1j7GjPUcSMJxIiRtg0ckN8jJ3niU7NsFJ1Lsn4DyaueSrLGXiBqc2Jp2lLAFDuhdO6SL4J/hjBBXz8FiErOyBs9dytd2m0gHma59zuKmdQfEySxTFLuLm5%2BZb63Zs7cO9lLFnL8XYiJe2Cl3NJz%2BVJ6FUb7PbL/zIHoShW378ULx4ccQFg3yytysoFVmp9XzUdMbzqvVDhms5eNW1olnWbV2odR0/ru3lukHwF6vAo2/UTeJFNpNM2w28Hm6qpbcbVsVo2%2BmzNu3QYZ/zUwQtxbS3lqTZd2FEgbuIobfdnQvunvGEBzYCNs6vs/Y4DmVxbax0WAnT5qd6Fn9Y6LrQ7LqU4bplAfpo71CU67r1A06fpPqE446U4E7Y7/ok6I5U644/qfpoHgGk7gYrCgZwqebB5bKs6R6HDR425x76hjC87oYC7p4yZ4bSRi6UAQZS7%2BBGbbDbBlITKCZrI8GJCzJiZkGa57IHLC7EaJBApy5cBSDvyy7kZcDJClLbCkE%2BacBC7MHMbAqiGaGa467LApoZDOCSBAA)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/recur.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/recur.test.hpp)
