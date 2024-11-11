<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Has`

## Description

`Typelivore::Has` accepts a list of elements and returns a predicate.
When invoked, the predicate checks whether the previously provided elements contain all its arguments.
<pre><code>   Elements...
-> Arguments...
-> Arguments... &in; Elements... ?
   true : false</code></pre>

## Type Signature

```Haskell
Has ::   typename...
      -> typename...
      -> auto
```

## Structure

```C++
template<typename...>
struct Has
{
    template<typename...>
    alias Mold = RESULT;

    template<typename>
    static constexpr bool Mold_v = RESULT;
};
```

## Examples

We will check whether `int*, void`  is contained in `int, int*, int**`.
Then, we will check whether `int, int**`  is contained in `int, int*, int**`.

```C++
template<typename...Args>
using Metafunction = Has<int, int*, int**, int**>
::Mold<Args...>;

static_assert(! Metafunction<int*, void>::value);
static_assert(Metafunction<int, int**>::value);
```

## Implementation

We will use a technique called SFINAE, which stands for `substitution failure is not an error`.
It roughly means we are going to create an `if statement` for template instantiation, where the condition will be the legitimacy of an action.
In this case, the action we will be using is accessing a function in an overload set.
This action will fail if the requested function signature is ambiguous.
We will use this behavior to check whether one overload set contains the other.

We will use `Label` to create an overload set for `lark`.
We add a second parameter in the template head to distinguish identical elements.
It is essential since inheriting the same class multiple times is an error.
Unfortunately, using this error for SFINAE is impossible based on my testing.

Since arguments are not allowed to have the type `void`, we declare the parameter using `Element*`.

```C++
template<typename Element, size_t I>
struct Label
{ static constexpr void lark(Element); };
```

Here's the entire implementation:

```C++
template<typename...Elements>
struct Has
{
    template<typename...InspectingElements>
    struct ProtoMold
    {
        template<typename, typename>
        struct Detail {};

        template<size_t...I, size_t...J>
        struct Detail<
            std::index_sequence<I...>,
            std::index_sequence<J...>
        >
        // We create two overload sets and combine them through inheritance.
        : public Label<Elements*, I>...,
          public Label<InspectingElements*, sizeof...(Elements) + J>...
        {
            // We bring every `lark` from its base class to the current scope.
            using Label<Elements*, I>::lark...;
            using Label<
                InspectingElements*,
                sizeof...(Elements) + J
            >::lark...;

            // We will do SFINAE on the second parameter.
            // The default argument `void` ensures
            // the compiler checks the specialization
            // before the primary template.
            template<typename, typename=void>
            struct Hidden
            { static constexpr bool value {true}; };

            // We ask the compiler to access a `lark` that
            // declares a parameter of type `Element`.
            // If the compiler can access the `lark`,
            // this specialization will be used.
            // Otherwise, the primary template will be used.
            // This function checks if both overload sets
            // contain the same element.
            template<typename Element>
            struct Hidden<
                Element,
                std::void_t<decltype(lark(std::declval<Element*>()))>
            >
            { static constexpr bool value {false}; };

            // This function returns true if `Elements...`
            // contains every element from `InspectingElements...`
            static constexpr bool value {(...&&(Hidden<InspectingElements>::value))};
        };

        static constexpr bool value 
        {
            Detail<std::index_sequence_for<Elements...>,
            std::index_sequence_for<InspectingElements...>>::value
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr bool Mold_v {ProtoMold<Args...>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCAAHACspAAOqAqETgwe3r7%2BgemZjgKh4VEssfHJtpj2JQxCBEzEBLk%2BfgG19dlNLQRlkTFxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAMxhyN5YANQmO25ejrSEAJ6n2CYaAIK7%2B4eYJ2fI4%2BhYVHcPzzMewYBy8x1ObgI11SmAA%2BgRiExCAp/k8AQRMCxUgYMRCoTDmGwjth6GxBKQjpkAF5wghHACSqMe42IXgcR2CTFitABJgA7BZKc1HMgjmgGONMKpUsQjgA3VB4dBHAzEADWEBJmMYBCWp0F/IAIvreU8MVicZg8dDGKxMAA6R1askEFE7e5PFlsukACSYKLRAoBRxDR3N2KYuLO%2BNtbEd9vpEphDjCwGdOrdHseoaFrPZymIqCIAFlPOhg6H%2BVYnjmc%2BHLdaCXaKTHCVb3RXa7nvUdDZhmnQTkG%2BcadtXnjWu2HMRGo25qbT4/SKQv4fGAFJMqfd9l9gc8s6d7dC9AgEBhLCqWFKACOXkYmwh9Pjd1IR%2B33zPF6l18wd4f7ZuOuL4dpOXZblOAD0kFHAA6u8yDEJgkbvAQADuqBHKgcpxLQqBMMqSiukchjKmglRhKhCCYmGCCFl4wAIEcYTUcQhCGJs9rvqGIBHKkXjRFcoqctyELpoICgAFQUoy7rxm%2BYFTvxgl4MJXJ1E%2BSaYCmRjia60mUngNKoFQ8aaqSGZLCclhHJucmOtxIZVo5tbQXB7zRGxRhHJgOHENcJwAGwaKqaomMFRxUIWLDMcR0T%2BghBgKAoYaYQQ1FiusSGCJSaAwlxinbl4mTeSJGlnHpUkyXcZ6hSB47HqGxWphy6kHm4LnbomCjJo4ukWRJ0mdVOC4mWZlVWdYtnDU57q1S0ar1aa2aNUcbnwUcaF0LQRzoJhQgAGL0hEjzYFhDC0e8SjisqqQtHaGLEAVK2NW5AAqGW/EwXi0HSLTAD4OpBRoCpKuFGg%2BRK6yYAGL3Hm56UIagWJ0HEYrUcgaopYjlLJngYhGZG2QzWtMGxPwSGXXxbEsC0AX1ihz2rdOFooY2saYC2Nptqchqg%2BWoFwx%2BCI9j6SpYAwJNVkKROiuKkrSrK0SoJ48piPeQ4WCLVojvqQ6juOJPre8/pqlT5GpKjspECRyCbMlJHA6F4O0ZGRswVgBwtDDjt3YibCPVhVBhjawN6eDTOrW59LBzjFtW2Khi2/b2MZeDzvBQpQtQTB6V4ClPXafjVxUkTAibdtRyxEcxWYOgkevTBADyiPEFtSgthlMp4LT/ks7O7xbbQO3V7X9fu0cH355FXggg06PaVjzHB8r6VYX5eEEZS/aw8zbnigOF04wodo%2BQNBAN8eDNzq2p/h4LzNeuyYs/IwEIkzmelZ8zOafiA/PwghJ7X6NoIChQgH/YBcoxBiXPpJO4EAlhIIgo1FBx5pazBFGKAQCsZRVxVjtaB3h3hVioGIJQRo9aULHMtPeMEp4pSoLPFM5ckIEHWBKMMrJ3h4GDuDSqL5goTwPkiThvk4gBTqNqHKUVkbA26r1VMAiHJCMKiNYUqlsESgxIrfBqsiEayrBAF8ZhArmEChAF%2BEtNKFx0mmc%2BmYzwGMwMg3WNC1FOTcYbDxMssHyx0Xg5W%2Bj1YkJ8c5HxOY9xInan/b8V5bz3hBHCCmsDpGuhAtgb%2Bq1YkMEvL%2Bf8STYQpLOAo7SfV7FpIUBkmq/8QkuWoQ1SsXjaGhmvoBW%2BcZHSPGAEhSpaDmreVLLQZUvMjgFiLKgIZAs3DdN6S6KpDkOzuInHDNp7M2zxkeMQYAmYjyYM0f4qUgSCFHCmbCOUmtxkljLBCLZOyMlOLqc0wMBtlqQUkh8z5XzIIAneR8t62AhBvU%2BT8p4fyvnfOWi8EEbwPhuHFJsVIromTohnA2aM3M7SbO2bsp4AzgCnP7EwJhc9sgfENEcP0bo3BhAIBSWlBkGWMsEB8pkZ4pm3JxdU5ZAJ9nIFhP6JQrQIBgDAIS5oJKWGSzOAyik/ManOL1MsvlArkpxAIBAYsRLJUNAhLS%2BlLL4FzVqcQpVFgOArFoJwJIvA/AcC0KQVAnAOqWCmgoNYGwSFAh4KQAgmgLUrDVCAJICR7SBR2JIMwfJJCSBDTsDQSQACcCR9CcEkLwFgEgNCBDtQ6p1HBeAKBAIEP19qLWkDgLAGAiAQBrAIPxOlFAIDx3oMQCIdpOCqASIFAAtIFSQRxgB2yOFIe0ZheB10ICQJUeh%2BCCBEGIdgUgZCCEUCodQZbSC6C4KQNCiJUicB4Ja61tr/WOs4E3C4Dag5HC7b2/tg7h2jrMEcCAHgUatusjsLgSxeClq0CsCASAW1xHIJQED8RgBSDMHwOgj0i0QGiGe6IYQ6aHt4Ch5g/km7RG0GU9DpByIuibgwWg1wz1YGiAxNwYhaBFu4LwLAtMjDiE3fgJCKYcL0YdVKbSFwtg%2BtpXUM9VxPJ0w8FgM9CIe4Eb8srJQfZmPACuEYf1KwqAGB2QANTwJgNCTcCQEbncIUQ4hl3GbXWoM9279CGGMNYaw%2Bg8DRCLZAFYqAkXZHoz274vNTCussGYPNfk2JYFc4g7oZTsguFyVMPwO6QiUQWCMHdRQsgCDi3oNLDR5jDHiDuuwUWBB9EmJ4DoehCtSpKwMJLeWKsTDaGV/IBWGu5cqCllY7r1ibAkMejgNrSC5t4Pm293a%2B0DqHaKZ9r7cBTtlLsH9f61MrGogREYEWg2SB2PaRNOxo0aEjZIYKCbAqJtTRwdNpBM3frDVwQKCRk13aSJILgSadiBUG2e/Nhbi2%2BrUxW6tQHa1XouGB5tyNLatvbWwTgLQWByj5D2pgYoDDeS4Im%2B0XB7Q8fwEQULs7ZALrM9ICzSgrObt0DBvdTAD0Mb6wNob56OCXvrRcG9cOEdI5R3ZkdGOscQzfRDhOuwzC/r%2B2WwDwGhetrBxBkAHPEdeyMOjrggQaC/TiAhpDm7MNoYY6QXX2HcP4f10RnUJGyMUcwFR4ANHh70Z9UxuzrGHXsai1xs9vHkD8YI0Jq1m7ROIn8hJrYDrpOZv13JjImBFPO9TP9jTTBtO6f04Z/XxmidLpJ7ISzG6HWU9s6p/zVhLBOZc/AdznmcGcB8wQAWhpi/WCC8NkLSoYYV8i1KmL7gmvxaCLktrixUsZHSzkXvWWR85dq%2B1/LneGjVcywVqRVXWvT6H7YBri%2BN9zDXx11Y3Wl309PZukbCuudK4JejzH2OZu45IF%2Bxb4uAMreQlgeIEX/eXeuxjg7fIk18j5AjTMCOxe0%2BxP04B%2BxLX%2B0rRrTrQbVl2lziGhy2DhwfRYAUDlFFDlCv0tHGAnTv3xx3Qz1MyzxXXkDJzzx0BAB2F3X3XQyPzALzQvRBzpBMhImIBYDQIwKwJwJQnGFfXfUhzRl2B2DF3/XLSBwgwQI/RGEwNSFSHOXR1hFwIIAFQ4P7Vgw12IC12Q1Q38gI0N2uBwzwwcAIzN0EAt3IzY2t2o1owd0Y0xGd1D0YzwA40cA903S9x931z9xE2cyD2uBDykxplkziHkxj0cJY3jwlz4E0wUB0z0wM0YCM0JxIIkGz1XQoOs2oML3swCxsFE3C0rwaHo0gk/Eb0C2CziFC3bzczn2iwgFcC30S3KDq2H2KGyC32y2yEHxS3qOK033HyXx6AGJ31aJn3q36C31mFaF6Py06w9R6x/XOwZy%2B04HYM4IHXQMwPlF4IxH4M1AIIfzEOW1IFWzf0oD6y/xADMAxx2B2CSCSAO1Vw0HuL5Hu0YOGwgNsF%2B3EKQVIE2yx3eySD5DMEeJe1OwCBg39x2GPyYILSfwDXO3HU%2BKZyWwlxWD8kyGcEkCAA)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/has.hpp)
- [unit test](../../../../tests/unit/typelivore/has.test.hpp)
