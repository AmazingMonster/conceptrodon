<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::IndependentFind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-independent-find">To Index</a></p>

## Description

`Mouldivore::IndependentFind` accepts a list of predicates and returns a function.
When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
IndependentFind ::   template<typename...> class...
                  -> typename...
                  -> typename
```

## Structure

```C++
template<template<typename...> class...>
struct IndependentFind
{
    template<typename...>
    alias Mold
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<typename...>
    static constexpr std::make_signed_t<size_t> Mold_v
    {RESULT};
};
```

## Examples

We will find the indices of `int**` in list `int, int*, int**, int***` and `int, int*, int***`.

```C++
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

template<typename...Args>
using Metafunction = IndependentFind<IsIntDoubleStar>
::Mold<Args...>;

static_assert(Metafunction<int, int*, int**, int***>::value == 2);
static_assert(Metafunction<int, int*, int***>::value == -1);
```

## Implementation

We will implement `IndependentFind` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class...Predicates>
struct IndependentFind
{
    template<typename...>
    struct ProtoMold
    { static constexpr std::make_signed_t<size_t> value {-1}; };

    template<typename First>
    struct ProtoMold<First>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<typename First, typename Second, typename...Others>
    struct ProtoMold<First, Second, Others...>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    ProtoMold<Others...>
                    ::value != -1
                )
                { 
                    return 2 + ProtoMold<Others...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQgAOyJpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAMzhyN5YANQmO24EAJ6pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fI43QWCoLzenw%2BBEwLFSBkhp3OUJhTDhZ0u12YbAAdNiXkcDkwFApsZjlMRMPhRJDnjtXh9xsQvA4jgBJBhYdFYQQAMXC6DBJkSVg%2BRxFR0h0NhmHhaMYrEwxNBwtF9MZBCOpNQRAAsp4%2BUqRQKLEdZo5kHiBONMKpUsRjQR0CAQCwmABrW6ZYARdB3eGZABetwIuIAbmIvL9DQBaLgCgAipyNcYT/P1YsRkulV1lbCOPOI40V71FdoZTI12t18LzBZpYOLhtFdeLyuapvNDEt1ttTC8RCOoe8EdT9cFTebzZMAFYrJPYxAlkdI7jAY7nW6bh6vT6zv7A4Xx%2BPDWOD%2BO8FR252bUcoAqzP5zP5SeS8JTMNS3NWgzTHQPw0slseJ4jkaZIEOsDBHBoCYnIk8YfIBQEinUSgIYhDageBi4xjsiawahE6wfO%2BFJjhx4kUK4JFqK4pIii5xZhivyfqQYoMXKRxCJgaBsixMqMcSADyBAIPE1K0lRIoqmWxCaqgOq0HyZzMRxXECOgLFCSJ%2BYKrWqYNgaw4tsiL4XpCXZHD2fa/kOEkERRiEGtOU5zguS40naDpOq67p4J65Lbm4u7buJDkwfZoWimeplWja%2BEnjeOJ3g%2BT4Usib5Vng%2BZftgP5hpg/5xQe6GYGBxAQVBOEwXBlERaKyG/FF3GXsQhXjglmIPslZKpVS8Kcdxik5SA1kFYZaGCkcGFlUc2G4dVrXNvVRyNRaZmxWNQEQAtJ7lnJlZnJpok6SFtXNrlg5HGAYCnLGWHbaKAEbSeDb3eOU0QWYJyWOqMkVgp8KHdpOK6bZp1HOd4bQa9VUpqDDn1dDxWlRB0ZQ3hT2NoRj1wwaeGkXpeMUceNEZqibFYti7zAGSUKMAQYnHl4mRGEc8noH8t27Wz8JUzTbCCESwOvPjnyE7DAD0ABU0sy7Lcvi2CUsy0cAAqb700cssKx8Sty3r0va5RXwMAcXjHPC3GbKk9OFmCJNpZm6Lsdg9D89lYJSWqzIKKyBCxmsMT0H0LUfCARypF4gcmSuIB4AoG5yvCLu04ILHhAQ0u4keYvwRC6YO2TTsU5i7zEMADMfEz4TAKzJVMFQXgmw0HMsmymAcnTPJsvC3u%2B/7kdBxMhaOtzZyl%2BXx3Jrn7wmi%2BNwEkorQQFqdcN032TwunaeCJL28Z7vy075n37DXlHM3UcZgASLs/IPPhLxAQy%2Br43Dgb2cW%2BHxne8yy8EMRjseMgCsLXwohwFYtBOCTl4H4DgWhSCoE4G4aw1hjRrA2BGMwOweCkAIJocBKwXQgEnJITEGhJBcESDsDQk4NB3n8GYAAHIw/QnBJC8BYBIDQGhSCwPgYgjgvAFAgB4XguB4DSBwFgDARAIA1gEAjgQcglA0DQjoPESIcpOCqEYf4SM/hJBHGAMgM0UhMRmF4M%2BIgxA8AOiCPwQQIgxDsCkDIQQigVDqHEaQXQQQADuDxUicB4BAqBMD8EIM4AJXsiijioHPDovRBijEmJmqQz6EAPBqPoLaXYXAli8DEVoFYEAkCqNSOosgFAIDlMqSAYAUgzB8DoJCfMlAYgRJiOEFoFxgm8C6cwYgFwBIxG0FxMRODVFuwEgwWgvTvFYBiF4YAbgxC0GEdwXgWBnRGHEAszK4y8DBjfBEq0XFexbBwenOoETaB4BiA8IZHgsARPuHgThmzSDHOIDEDImBYxQkMMAO5Rh8ErCoAYcuAA1PAmA/ECXRH0txwhRDiFcQ4%2BQSg1ARN8foIFKAUGWH0Pc4RkAVioGttkDZkZAQ3VMJYawZh%2BHfJsVgUl85uiHOcBAVwUw/BBFCOEIYlQRiFAyFkAQfK9BFAlQweYwwEhBDsFyxoEw2ieA6HoZVb8BDBwGEKhYorbBqqlUqtV8qRWKpWAodBmwJChI4NA3hESBFHESfowxxjTHpOvLgQgJAvrYIKbgsFKwRJMCwAkDlRDJA7ExAATh2IkSQ5CzCSH8Nwyc/h42sI4Ow0gnDsGYkCP4Rh8bGFcH8CQrgk5E3%2BGdd4gRQiREhvESUmRpS5ExN7MompqBskaK0RwFoLBgyJEjEwPEBgWZcHjZiLgZDLH4GsbYvQGKnFoukBijx2LvG6CaQEpgQTNkOqdXw3gAjokKN7HE88I6x0TqnUCmac6F0aGvFkipOTA1X0KWCyRZT%2B1fviL22pOSQD3vHfiIws6uA8JoLQVpwiIAdO8QMnpSL0NDJGWMhwSKpl0xmXMiJizlmrNoOspF2ygV7PgfgMkb9jkbPgWc5AFykXXMgd4u5DyenPK2PAt5HycHfN%2BUoAFOzgXV3/RCpg0LYXwsRZ89dqKXFbtkDurx8D914tBfSqwRKePsvJZSi0nAaX2jpYSiwTKL0stsScslnKdV%2BB5WyU1wQ2QWsWGK4o2QPMyoaN5o12qGh6o86F3o5qDUKq1SajV%2BQzVzBi5a%2B1qx1h2vybms9LrOAWWIKO8dk7oM11nfOshvrl0BrycGopBDSDhsjZQB1%2BbC1zvIYkWtyQdiSDTQYoI57ImCNsC2ur7b4CdvkYo0DQHKmaLYJwEdySWAKGDGaYMZXJTjCXf61la7ZAbrU8izTOKQA7FIIe49ITsvhMbVE7tap4n5ZYMt1b63NtpXGB%2B2b37dg7Fq/%2BztYGQPVOBwkNbqRUg3A2/Gm4W2CDzwKwY5piHRLtM6d0oZmHMfDNGeM/D/bpmzPmXRzASyVlrI2Tg6juyBNbIOYxk53jWPsc%2BZx259zHkXH468mxwneCib%2BRJmj0m218EhQoGFcKEWMCRSp5xEh1PuKxVpnQZ3dPGGs8SmIxmEGmY7JwcWK59OMuZfEVljmOWRe5byhL/LPPoGC4qtI4qGgBdd9kJ3Wq6gqvC3b73PRdXRfKLFpLkx/dh/1SH1LWWbUZZcae27/C8tLcMSttb/YPtUjVBAP11jA35L/W2sNmAI0jA5Vx1rIAzBzp2DsSctCKHcLr4kUtDbk/DeEaI0NpAY2TgTZORhd542SHjVQpNXBztcZ2Eni9nAi/FIdRY9vc/htjZWN8zIzhJBAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/independent_find.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/independent_find.test.hpp)
