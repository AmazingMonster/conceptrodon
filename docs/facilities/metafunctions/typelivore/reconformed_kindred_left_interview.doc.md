<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ReconformedKindredLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-reconformed-kindred-left-interview">To Index</a></p>

## Description

`Typelivore::ReconformedKindredLeftInterview` accepts a list of elements.
Its first layer accepts another list of elements and returns a function.
When invoked by predicates, the function first binds the second list to the front of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

This function internally is the flattened version of `Typelivore::LeftInterview`.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Interviewers...
-> Preds...
-> (...&&Preds&lt;Interviewers..., E<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Interviewers..., E<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Interviewers..., E<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
ReconformedKindredLeftInterview
 :: typename...
 -> typename...
 -> template<typename...> class...
 -> auto
```

## Structure

```C++
template<typename...>
struct ReconformedKindredLeftInterview
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class...>
        alias Road = RESULT;

        template<template<typename...> class...>
        static constexpr std::make_signed_t<size_t>
        Road_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
template<typename...Args>
using Metafunction = ReconformedKindredLeftInterview<int, int*, int**, int**>
::Mold<Args...>;

static_assert
(Metafunction<int**>::Road<std::is_same>::value == 2);
static_assert
(Metafunction<void>::Road<std::is_same>::value == -1);
```

## Implementation

`Typelivore::ReconformedKindredLeftInterview` is implemented upon `Typella::UnconformedLeftInterview`.
The latter is a flattened version of `Typelivore::LeftInterview`.

Here's a simplified version of it:

```C++
template<
    template<typename...> class,
    typename,
    typename...
>
struct UnconformedLeftInterview
{ static constexpr auto value {-1}; };

template<
    template<typename...> class Predicate,
    typename Interviewer,
    typename First
>
struct UnconformedLeftInterview<Predicate, Interviewer, First>
{
    static constexpr auto value 
    {
        []() -> std::make_signed_t<size_t>
        {
            if constexpr 
            (Predicate<Interviewer, First>::value)
            { return 0; }

            else
            { return -1; }
        }()
    };
};


template<
    template<typename...> class Predicate,
    typename Interviewer,
    typename First, typename Second, typename...Others
>
struct UnconformedLeftInterview<
    Predicate,
    Interviewer,
    First, Second, Others...
>
{
    static constexpr auto value 
    {
        []() -> std::make_signed_t<size_t>
        {
            if constexpr 
            (Predicate<Interviewer, First>::value)
            { return 0; }

            else if constexpr 
            (Predicate<Interviewer, Second>::value)
            { return 1; }

            else if constexpr
            (
                UnconformedLeftInterview<
                    Predicate, 
                    Interviewer, 
                    Others...
                >::value != -1
            )
            { 
                return 2 + UnconformedLeftInterview<
                    Predicate, 
                    Interviewer, 
                    Others...
                >::value; 
            }

            else
            { return -1; }
        }()
    };
};

template<typename...Elements>
struct ReconformedKindredLeftInterview
{
    template<typename Interviewer>
    struct ProtoMold 
    {
        template<template<typename...> class Operation>
        using Road = UnconformedLeftInterview
        <Operation, Interviewer, Elements...>;

        template<template<typename...> class Operation>
        static constexpr auto Road_v 
        {
            UnconformedLeftInterview
            <Operation, Interviewer, Elements...>::value
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSUqQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJXEl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxidIKjc2tuR3j/YNlFaMAlLaoXsTI7BzmAMzhyN5YANQmO25ejrSEAJ6n2CYaAIK7%2B4eYJ2fI4%2BhYVHcPzyeBEwLGSBmBpzcAKOMKOwNB4MwkII12SjFYmAAdNi7kcDkwFApSNDYSi0cw2MSnrC4aj0WxsZiAf8nuNiF4HEc5Aw0Ax%2BMQ2OgQpgqAQAJKCeIANzwmAA7syAOwWI6zRzIPECcaYVTJYhHJgXVBHKViLzvEzKgC0XEtABFTir7Y7mUCQWCmBCziSYfCPV63GT6VicTtsHiDISjspiJh8KJgVTHjSgxT3hLgcQZfL4kmU3S00cAGJ4YjjZlhgFsjkELk8gT8wXC0UZ6WyhVnGNxvAJzCkI6trPt3PF0vlytPS1WamwtU9zUMbW6/WGogms0Wmcwqc%2BmknfxWfx2iBLI5W3HfEAgFhMADWmAA%2BulgBF0A%2BCJD0gAvR8fifJvdt2VXdAJhPAqAXJc9ROLdQJhCAu3jT0kTOQdszlEcSzLP9sCvU1vEwJYQNAqcjljAh1gYI4NEdE5FQdSdYLgrolGIwDSPIyiz1tHYnXoti6OPIjYOdXilQdMTGMBR4/URSFd1k5DkQLDFGVxfEo0QntkLzUkVLYAdJSHHMyAU/T3iw8Z%2B1TDEjiEWoBHQazzMZAB5AgEHiBQK3uVkCHZTluV5Rs42bcUjPQ%2BTYK03tdJhNDh1M2DLIIft7N5JyjnczyyzUyd/x3WC5w1XkoJXI11wImCAKA6car3EwD0aoSzwvAh0CvG97yfPAXzjd9PzwH8Bv/ODCvquDwMg4Fl2quCaQQ2MkIDBKTP7FK7jwjdhImkjlTIzAKOIKiaN4wTXV2wCWPeKbSpm6CBIWmKlNQiLErShyGHQTaQHw80dvm2EOMOrieL4hjpMBmFrqOW6tXu4hHthCAkcAoKGxIJsRXCzNIu9JioZpZ7EzmwnQNWjCyFJsm92yry8su%2Bafr%2B94wDAU47W41GjgBqHSO5mlOOOo4zBOSw62CzHQuximosZwnib7amadhCmRwF0C6dynECcB5mN1o7nnSkwnrqN/ahaom1Df43XBJPXdRLqp2LsUgMbIZbFsHoNhBG8/9q05AAlT6QvQABpcJ0CWsLZcnYDYLdlDA3MwzccSll6sD2sY1QIgAFlPHQZXxrgpPkXdOSzg9kMmTDCMCQULK0WIT1MkzuCvHSIwjiD1AmGLjmJYxgVpZbN75QEyFXJbtuBH7NWqe9kFGAIBQ1MrSTIdA8vq8rl6U/JVTQ3DDSm5n%2BI54YDvQOK6adWg1djT7geHylZWaVLqH0b5KWhRlieCo7afzOBfVuPQF6AJHMvX2a8N64V%2BgbO2LsRL8S3gpfe7sXLYkeMAWMK8/Y3xhF3cIwAjiF1oIPHYnNc4FyLpCXB%2BDYHrxPi6eOElnZPAAPQACo%2BH8IEYIrhAJeH8KOAAFUwOMJuAjhHcMEQo2RF0Xg8jeB8c4lwbiZwBLvQ%2BwZGSPGIMAf2vlHgkJ7vnQ6TAqBeB5D0D4nMQ6S1HhHKOMcAHp0nmccIqVYaCB4f2HxfDAn%2BJ4ZnK8FDvpnEMcY%2BBbDpLFQfI3eIH4ngQEsY0Gxdj27eNCT9F%2BUS3CXhAHgBQT4MT6yqhzIeZgiJb0Sck5oAJ0lWKyXUAQkIpSoDwFEhBBTPztSvKU8pbBKnmgcUPG0dSLAcBWLQTg/heB%2BA4FoUgqBOBQksNYVUawNgWjMDsHgpACCaFmSsW8ARFSYh2AADgAGyKh2A8jQtzHkAE4dj6E4JIXgLAJAaA0KQZZqz1kcF4AoEAgKTkrNmaQOAsAYCIBAGsAgyQLjkEoGgUEdB4iRAxJwVQ9yrR3MkEcYAyANRSExGYXg3YiDEB6XofgggRBiHYEkZl8glBqFOaQXQXBSBylbskTgPA5kLKWby0FrkLhotrKgCChK7nEtJeSylkhqVHAgB4bF9B9S7C4EsXg0KtArAgEgLFyQcVkAoBAS11qQDACkGYPgdBMwQogDEXlMRwhNGuKK3gPrmDEGuK5GI2hajQqOVi2BrkGC0H9TC0gWAYheGAG4MQtAIXcF4FgG8RhxBJvwLGOoUopG8p1LUC4Wwjk%2BK6Lyq4MRW4ho8FgXl/k8B/JzaQMtxAYhpEwHaEEhhgBXCMKclYVADDGIAGrtgvsso5nLWXiA5bIRQKh1BJv5foEdKBrDWH0HgGIELIArFQMkHo2arTfA5qYLZlgzAgt7QyrAp6TydG6JkFwX0ph%2BAFaEcIQxygjAFQUDIAg/16HAz0eYwxKifsjfUCYLRPBtD0DUdpvQUNwZAwh2Ykw0O5AFQRgYQGFigZWAoXZmwJDio4IsoFUrOBHCVSqslFKjhUtFhAXAhASBi0OUa45E6VieQHiMD9FzJA7ExB8xUkgNCSDMJIO5AL/B3LeV8jgPzSB/MOZiO5XA7k3LeTc4z/hJBcH8B8u5TGk2gvBZCkTMKzWIvNci2V6LbX2r1XitgnAmgsClIqK0TAG49y4G8zEXBMSrLpSQRlArl2iFXdITlG6eXbpAC6oVTARU5vo4x4FvBpVeflRBILIWwsRbIVFmLcWtU6qtXqwTtTjUTrhRa1Aurcw%2BZ6y1kYVXQv4iMFFrggKaC0HdZQL1Sag1%2BoDaQBbIaw0RocEtmNq840Jt5SmtNGbaBZqW3mkdhbVnFqQ2W7N8XVBVuBEtut8yk2NubdcVtWxVkdq7Uc3t/alBDvzaO0hnWp1MFnfO8kS2UtsokOl9d3Kt2rN0C6gw4771WEsEek98Bz2XsyNe291CMfWCfaVl9PTy1nsQ1hn97giP/uCF9XDiwwNpAg1kBn0H2ewfI/BjDXQkMCD6IRnIjPMM9BF2R0o/OSMoag3LuYfO8N0dWOsWjhrtPFeYxwA0ApqvhdG3V6LsWNBar4/SwThqOuubE5gCTCQP3Pd0/p6LSnFQ2cVI85TqmrP2ZBZwJzULOvwqRSiuVGK7UDetf5rYQWSVHBYAoKUGopT1cROMWl%2BB6VJZkCy1L7L4eCEy0jnQIBPl5YK2KrXkqHOcBlaii4RwFV65YAnpPKeTTp%2BQuMJr0fWu7B2MJk1sKPO%2Bb65i/vIwU/JGSG/KLD4M8ECSQKElrrpteVm9631IalsrdDeGyNm2euxvjYmi7mBU3pszdmo5p2C2fdzaWK75ak2VuQNWx7kpnurNe36j77aDKP2vAf2A6gOZ2IOrmfA06Cgc68oC60OsgK6heeeXKm6vKugnyaOxgB6WOja76eOV6nAXCl4JOj6z68Qr6VOH6Eu36EArgCuTOQoyurOKQPOmQjBMGmQLOoGNOku8uXOJGguWGUuPB%2BGAhYuGGOGLBlGaueyquz22udeuu8epKHeqe3ewIvevG2eAmBqw%2BompA4mWAju9GLuOW0WOwOwgQSmE2LyOwioJm/upWgetgzmI%2BSw5yIAymhmXAOwZgdy/hbyRmARGgio2mOwteAeYKLmpq9GNKzhayrhHhKwva6QzgkgQAA)

## Links

- [source code](../../../../conceptrodon/typelivore/reconformed_kindred_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/reconformed_kindred_left_interview.test.hpp)
