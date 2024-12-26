<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::TerseIndependentRightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-terse-independent-right-interview">To Index</a></p>

## Description

`Pagelivore::TerseIndependentRightInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

`Pagelivore::TerseIndependentRightInterview` prepares fewer base cases than `Pagelivore::IndependentRightInterview`.

<pre><code>   Preds...
-> Vs...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>, Vs...&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>, Vs...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>, Vs...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
TerseIndependentRightInterview
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct TerseIndependentRightInterview
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Page_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = TerseIndependentRightInterview<Equal>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

We will implement `TerseIndependentRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct TerseIndependentRightInterview
{
    template<auto...RightSides>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...>
            struct ProtoPage
            { static constexpr auto value {-1}; };

            template<auto First>
            struct ProtoPage<First>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<First, RightSides...>::value))
                        { return 0; }

                        else
                        { return -1; }
                    }()
                };
            };

            template<auto First, auto Second, auto...Others>
            struct ProtoPage<First, Second, Others...>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<First, RightSides...>::value))
                        { return 0; }

                        else if constexpr 
                        ((...&&Predicates<Second, RightSides...>::value))
                        { return 1; }

                        else if constexpr
                        (
                            ProtoPage<Others...>
                            ::value != -1
                        )
                        { 
                            return 2 + ProtoPage<Others...>
                            ::value; 
                        }

                        else
                        { return -1; }
                    }()
                };
            };
        };

        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQSGmakAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzOFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GB5nBDEhXmhsLcyHG6CwVGxuJ%2B/zpAOBv12NwAkiwUvQ2IImA1PgdAUz6f9AcCCJh2QYxSSxRKeZgSUwvEQAHSq7E3SFMBQKVXK5TETD4URirGgnGXcbELwOG4AFXiShZDCwT2djAIACU8MAEAQnWLiAA3N4Ad1xAHYrJcbjGbjKOXKFUrULqvT7hHgsKbzRdYzdLdaCDd9agiMomMB5dHYyZI8C83mCzahAYFAh6w2Y7Wo7nOw345L5XDFSq1WaO33Y02iyWyxWq73J13I/nmo5kBqBONMKoUsQbiPUDdA2IvJgYZGALRcWt3WEWC930E9idLgeJ4fJm4AMTwxHG1LVkuq5Wjas6oOWlYkr%2B/4EIBi5Lt2NZAcBU5rngG5oAw267vuh7Hqe56vqhF49iRk4mP4Vj%2BHcEBLDcl7quSIAgCwTAANaYMiGTABE6CoiSGQAF5cXB44oeRNZ1hJkkNngVCbthYq4TCMmybGUC6uYABsOn6oaGFyqabgweMpA3GmvpCJm7xaWaLEnt4mBLEsxHqVJD4GgQ6wMDcGj3o%2BNIIe5sZ1EobkhUhXk%2BQxN7PoFankbedERYh4ZPmRqG3veQUke%2BUqfkQP5/mZB5fkImBYeg5mHrqADyBAIA68EkdOxbEKWEHztBJUEOZFVVeZDVNf%2Bdk5iRSFdolk6zOuik4XuZVFY5Z6qcFWXSetkmUdRtH0YxZqrugLFsZx3HenxAlwsJoktSFpGpep8nzcpi2PbJmlqmYunffpRpGT1sHmZZGZZmNDmES573bSu0XEL5/nxdllzQ%2BRYXns9WELfuqMkZ9yo6XpBr/SaJIDQI1UWd6Vk2TqY7YBDTlQ9NslRZg3nwzccUPsjQIs5J6M3JjW6vcQuOoRA4uSeBkFDm4w0OmNUvkYzq1gGAsJ3LFyuTq5/NJSuOuoXDvlmDCljtZ1sskgro300bwGq0OPP6xN6W5fdebow7DZsxzvnXgFvOe8letbWlGWo9lz6pdHL6Jflcu1aqFzAAa4rutmqVeBkRjFvOMKglrLZakgICJ5bc5QXCqfp1yBB0wT44xyhccezGidJqOyoXMQwBZyhOfhMA%2BeVoXWsy91Nd9431It0C7vz4yQoMrStzYKorAcueXzLyv/JBUyNzYAAjl4Yh8vsgKd4VR4sjVX4AFLwW1p/n7QEaZTGs0YS9O6LTEVAngCJOVfN2Fk49NY3GfovF8sDD6HBuAAWXZkwKgXgCS8l3pcG%2Bbhk49xnvBIeecUHNHQZgrI487QOkwE6F0zxBAg39PEYMmAwxwjfmIeCLFrbT37krJea99jUPGB8bBFwf7IGRFqJQrRgQQFIWgjBDgsgkjMNiHhU83AaHMkEG4yR9EaJACtIiRcoFmFcvPSR0jtTxDgpcBRqDyEqIECSQO9kQC8O0bo8yBj1EeJMZAousVLEWA4CsWgnB/C8D8BwLQpBUCcDcNYaw%2BY1gbCImCHgpACCaHCSsdiARJDKg0AADjMGYAAnJUrg/gymlK4OGcM0hIkcEkLwFgiQdGxPiYkjgvAFAgB0bkuJ4TSBwFgDARAIA1gEBSEqcglA0DsjoPESIrAtiqFKdpS82lJA3GAMgDcUhlRmF4AZIgxBMx6H4IIEQYh2BSBkIIRQKh1CjNILoIIIZ0QpE4DwCJUSYl5ISZwOqSp5lFlQApLZOy9kHKOVzYpZsIAeBWfQHGWSli8BGVoFYEAkDLJSKssgFAIBEpJSAYAUhkg0FoAGQZEAYggpiOEFoCJ/m8FZcwYgCI6oxG0JVEZ2Tln1zqgwWgHKPlYBiF4YAeDaC0EGdwXgWA2JGHENKv8Qq8CBneCCnclUlRbGyeEMUrT4m0DwDEdEvKPBYBBWiPAnSVWkD1cQQBSgHjquAFaoweSVhUAMP3AAaqGOqrpOXPOEKIcQTzbnyCUGoEFXz9CGGMCkyw%2BhrWDMgCsVAKQGjKsvOSTWphLDWDML091VyszwBWHYHVzgICuCmH4IIoRwhDAqCMAo6RMgCDbXoQoA6GDzGGFUboTbGgTDaJ4DoehG0uJnXMLtCxe22FnUOoIsxWjjp7VUBt6TNgSEBRwaJpAem8D6TcWFuz9mHOOcim4EBcCEBIObUEXBsU5IDSsJqTAsAJDoqQQpkhQTKkqaCZpGhJBmEkNpDQGh/DaUqfoTg7TSCdK/cqbSXBtKlMqQ07S/hJC1Kg9pS9IK%2BkDKGb%2B0Z%2BKpkEpmRChZZKKUYvWWwTgLQWCBnDJeJgGoDB5y4JU5UXASnnPwJc65QQE33LjdIBNrzk0fN0MkH5TA/kqrPReq9oKODgrmUqG40Lb3bPvcJ9NXNxOSY0C%2BtFxKMWfosTigN4zCWoHRfERZ5LvPOZGJqIwYnqh8DoAyygzKPncvZVG2LvL%2BWCocFG0V7pxWSpBTKuVCqlVRrVemzV8T8AGhUXq5V8TDXIGNVGs1dQQVWptey%2B1Wx4lOpddk91nrMDesK8PDzQaKwKDDWwiNjAo0KdjY85TshVPvPiRptN/ry1WCzY13NIGC1Fs4CWgg6Ay2ZosFW69Nbab1qnculwzpt3BGdPuxYfaihZBuyOho92N1LoaH0SY868g7rqNO77Aw10TsXVu377bN2rrKKD79qx1gnrh60/T1HOAWbhfs4LI8xMSZKS%2Bt9lzP3fvcwx/9mBAMjBA60zD2HxOwfDP4SpTTQRwYQ2RqjHyaO2Do7isZEzpmzMhX5jjayNk8eICweFLAFCBg3IGHHg5xjSffbWm5shFPTejXNlNIBQSkC0zpgF6Hz3As52C1jUKYVS5l3LhXRkiyooCySz9oIf28/xV5nzpKllO4xcY5AKQUjInl5U5EiuCDIlUHs8L9KHRRZZWy3l8XE98oFUK1L3mxUSqlcVzAsr5ViDy66grGrWuqu1WV/VHyqs1ddXVi1vBGu2oRC1x1VyOu8C6%2BkHr4o%2Bv%2BoY3wYNw3w2RtdZNh5EgZsvKTfNnQuulsZorWtnN52ttZGVdsZiK3K3VviLW/VeaLsNCu%2B4CHehO0w4PcO/tDQXs36yO9ydn3ejg9yJD5/AggeP7B/0G7u7geX4PZHoI6PJ6am69Jo5R77LS6y7Hh24mgO4E4fp4jE70Z4pk4U7AZno04gBVLKigigj%2BB1JkZIYEHhgEYc4QH9Lc7DJ/qgYgCSD%2BCQaNLhhIalKSA1JcDlLfTG6gjgHXqcAk7oHG5nKUECHUHu4rDuoZDOCSBAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/pagelivore/terse_independent_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/terse_independent_right_interview.test.hpp)
