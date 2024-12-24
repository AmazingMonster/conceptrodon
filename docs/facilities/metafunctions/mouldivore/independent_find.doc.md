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
IndependentFind
 :: template<typename...> class...
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
/**** IsIntDoubleStar */
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = IndependentFind<IsIntDoubleStar>
::Mold<Args...>;

/**** Tests ****/
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQgABz%2BpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzOFkN4sDcTKC3MhxugsFRYdhgeZwQxIV5obC3AQAJ5PAD6BGITEIClR6J%2B/zpAOBv12NwAkixUvQ2IImA1PgdAUz6f9AcCCJh2QYxXixRKeZhpUTGKxMAA6NWom6QpgKBRqlXKYiYfCiMVU0Foy7jYheByshhYJ72xgEABi4XQ6IA7FZLjc/TcZRy5QrHcq9dTff6rTaCDcDagiABZTweyN%2Bkzem6zRzITUCcaYVSpYhZgjoEAgFhMADWmGJmWAEXQpLxmQAXnWCBqAG5iLyYGHegC0XAzd1hFkH49BPqBaYD4qDUrhhNDbBubuI4wjF39pettvjSZTeM32/NwL3Gcn6fne%2BzeFzaAYBaLJaYXiIN173gHl73/rXv%2BAEASYACsVhgXcEBLDcQ4aoiFZVrW9Z4I2RotnC7adjuIEgUBd54XueBUHmL5im%2BNxQOGZj%2BOY/gGkaj5ymabhnl25oVj%2B/ZLEswFEaBmaGgQ6wMDcGgTlONK7gJIF1Eo/GyemQmYCJxBiSOkljopeFjjBOnKdOs5Xp6RnSXugaSvKK6Ksw67saQAa2cqNxCJgz7oI5q5KmweoAPIEAg8RmhaMl%2BtGh7EAmqDJrQHpwg5rnuQInk3AFQVbuGF7ztegGEeFzQ5mRr7FjcH5ftxf75YOxlKeBkHQbB8HmqW5aVjWdYNk2mFuNhmGhUpNUGQJJHFRRxbDUR1HqrR9GMcaLGnngW4cdgXF9pgvGTbpKlqWJEkzlJlzbXJtBKDco3PiVxAnQB00qvRc2Ggtpp4m5Hmoutv5bdVRG5cJok3KOh3acdv14fJA6Xfm403eDIEQLdRFHjFJ5wulwVZQNg14V9/Y3GAYCwnccGjvDAF8eTJmTkjeEA%2BpNxmDClhxlFx5xXiGOZeq2VhTje549ZNNU4BpnmfzNyQ7TymTvTGnAzTYvk3plN8yZZk5WLM7i36lnBjZa6qmqFzAIa4rOiF/FeJkRg3LF6AwqCJMo/beIm2bXIELqPNotrx1a7OjJCgytK3NgqisByA5fEHwf8tJTKsgoLKCHcawxPQfQlqcoqLlZIY%2BQO2Ccs6O4RbGLLJ6n6eZxMwIgDcqReBnj6tRWeAKPWyp4sX5uCI54QEPsGpAQHCeHHbqlMFQXhYryMeXHry74s5vnG8QwCW5c1vhMAk/NDPc/ZI7JMpw6zyCG69p4pXKcEGnze1y0O4Vq7cIXBv3sPReftzlcE8ABV3hez5PsQED5kDEm1EoVoEBExT0Pg4bIeJB4D0ELsNBQ8MEXXQcPTiIBKon2JozPiv8IFQJ1PEAgcCEGzyQQIFB/ccFD0wQcT6BCNpEKdqTUhFgOArFoJwMCvA/AcC0KQVAnA3DWGsFmNYGw/xgh4KQAgmh%2BErGrCAMCkgVQaESGYMwABOQxXAwJ6MSFwT0nppCCI4JIXgLAJAaA0KQUR4jJEcF4AoEALjVFiP4aQOAsAYCIBAGsAgTcCDkEoGgdkdB4iRGVJwVQyQhz%2BEkDcYAyBcxSBVGYXgTEiDEDwOWII/BBAiDEOwKQMhBCKBUOofxpBdBBAAO7klSJwHgAihEiLURIzgflPyRJuKgUiKT/BpIyVknJOimYQA8HE%2BgJYMRcCWLwPxWgVgQCQLE1I8SyAUAgHsg5IBgBSDMHwOgYotyUBiP0mI4QWgEi6bwR5zBiAEj8jEbQ7k/HKNiZ7PyDBaAvKaVgGIXhgBuDEGdV5pAsBViMOIcFy0/l4G7O8fphZ3Kfi2MowedR%2Bm0DwDEcknyPBYH6WSPAjjuC8ExcQGIGRMAPCRcAElRg1ErCoAYTeAA1N4rS/KOnheU4QohxA1PFfUtQ/SWn6EMMYGRlh9Cku8ZAFYqBUgNG8RwIciJiamEsNYMw7jGXFKwBqmC3R0XOAgK4KYfggihHCEMSoIxCgZCyAIJ1egig%2BoYPMYYCQgh2DtY0CYbRPAdD0OG%2Bhka5huoWJ62wUa/VhqjcGj1oaVgKHkZsCQPSODCNcf0jxNwJlTMydkoGcyqK4EICQZmoI1kbO5SsIKTAsAJBtZoyQoIVSGNBNYjQkgzCSH8M4sC/hDH6E4PY0gjjW0qkCP4RIhiLH%2BG0aY4dKQ3G8A8V4nxKjuWBJCTssJwzPzROOagJZCSkkcBaCwbsnohxME1AYW2XBDEqi4Logp%2BAiklL0OKypUrpAyqUHKppuhLntKYJ0%2BlxbS0HoGRwIZETPyjPGak9JX6lVAz/QBjQVFFn7OWS2sw6zT3%2BO2bs%2B9lH4i3pOcslA37zkmJcTQWgNzvEQHuU095zz4Uic%2Bd835Dh4WAudMC0F/SIVQphbQOF9KEXiiVSi8R%2BBDRIMxXq8ROLkB4vhYS2x4iSVkueZSrY4iaV0uUYy5lSg2Vad3me3lTABVCpFYwMVsgIPVKg7IWVjTxHwcVVy41VhVVWetVqnV2Q9UGrLEalVFgzWHotSUrFmrbUJpcPaDNwR7TZsWF64o2QSsBoaOV1N8aGhZ2jXkZ1BWmtZuTSGuN6aY35EzUm8o3W1mrHWIWkbti0Pls4JW/DGStQ/pI7ohtwHm2rNo5s9RpAu09soMWxdy6/1js9GBQxVjQTjsnZIII6Gj22BPZt7ZF6kDhMiaxpjBzElsE4C%2BgjLAFDdlzN2X9KorLjCA02y1YHAuSuC7U%2BQMHws6BAKCUgiHkPdPnSWvpTSPFYZGWMytf2AdA5B2D2MCyPtUYxKCDbZ7L1sZY0cxnCRAepFSMSYHhjiTk%2BJKodJVy%2BPBTuQ8p5nyxNi6%2BT8v5Mn71ApBWCnTmBIXQthXq5RiKtN2d4Lp9FBnsWqFxWKMzggiVNKs%2BSgktnqXFMcwy%2BILnWWaeRR5%2BjfA%2BUKEFZgYVor1PgdhxIELdTEfypR1F5VJq4vqvgIl3VnBtiIRi6a818RLV5ZtY17IRX3B9ba66obOb/XeoaDV4v2R6uhva70XrrW411Ajc1ivPX%2BgldmK0JvI381jeqahnH7iZv84yf9wH34ycsQp42opLa210a2Z2zA3aRg2tsQdkARiVSglBGBMx13nGb89OustuPODHt8R20g/awJDssZ6ZxiRJAmK4Po2iWPQR98PSf2fW3bH5KP/3zxX%2BvEpAjKmQzgkgQAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/independent_find.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/independent_find.test.hpp)
