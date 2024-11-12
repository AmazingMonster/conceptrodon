<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsEqual`

## Description

`Varybivore::IsEqual` accepts a target and a list of variables.
It returns true if all variables are equal to the target.
Otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> == Target) && (V<sub>1</sub> == Target) && ... && (V<sub>n</sub> == Target)</code></pre>

## Type Signature

```Haskell
IsEqual :: auto... -> auto
```

## Structure

```C++
template<auto, auto...>
struct IsEqual
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto...>
static constexpr bool IsEqual_v
{RESULT};
```

## Examples

```C++
static_assert(IsEqual<1, 1.0, 1>::value);
static_assert(! IsEqual<1, 2, 2>::value);
```

## Implementation

We will implement `IsEqual` using only `<`, meaning <code>Variable == Target</code> is expressed as:

```C++
(not (Target < Variable)) && (not (Variable < Target))
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsEqual
{
    static constexpr bool value
    { (...&&(not (Target < Variables) && not (Variables < Target))) };
};

template<auto Target, auto...Variables>
constexpr bool IsEqual_v
{ (...&&(not (Target < Variables) && not (Variables < Target))) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxBIA7KQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxXEl2mA6ZQgRMxATZPn4Btpj2RQwNTQQlkTFxibaNza25HQrjA2FD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbkxeRADUACpNwJgEpJfnRAB07wBqTXhM0fQKJ2wJg0AEEZsQvA5LgBJBTYACOXjEwJBJgSVlBlyxlxmTEcyEuaAYM0wqmSxEu0VQnkuADcxF5MCjsZc0RZLhB3q9zAA2XkQBioAgc27Ee7Ck5uS5fYg/P6YBTLVlmPkqy6C4UQGVy/6s043O4PZbG1kJAAiJwxqPNlpRKN2%2B0OTNOL1QBrFDyerq52t%2B/0BKKJJLJFKpNNhCKRtAA%2BrS7eiOVzefyNSLDRL9b75YrlaqeeqhRys7rJe7xcalWiLccrSiAPQAKibzZbdfrzeu2CE12bbdBjZbg77qNBuPx0aYCiUzQgEcRyNOXCeXFeGmXgJAIHp3kwy1to8a48n04IEDAYBhcPntElS8ugXvG63DN3lo4q1onAArLw/BwtKQqCcG41jWDi6ybJgyrHDwpAEJo76rAA1iAX5mK8CRmJIAAc2FfhoACcaEaDy2HHPonCSLwLASBoa5/gBQEcLwCggGu8H/u%2BpBwLAMCICA6wEMkFzkJQaD7HQcQRKw2yqNhPIALQ8pIlzAMgBJSK8Zi8Jg%2BBELK6B6PwggiGI7BSDIgiKCo6icaQuhLgA7sQTDJJwPAft%2Bv4IYBnAAPIXMJwqoFQlxyYpymqeplyaWYHIeBJ9AUuYMHLLwHFaKsEBIOJySSWQFAQLl%2BUgMAUiBDQtC7MQrEQNEPnRGETQAJ7ubwjXMMQzV%2BdE2i1BxsHiWwgh%2BQwtCtXZWDRF4wBnLQtCsdwvBYCwhjAOIk14MQ/V4LSCo%2BaStQXNssFhLsn52bQeDRC5XUeFgPkELKNFLaQe3EFSShmnsa1XUYCGrFQBjAAoHx4Jgjl%2BckjBtZZwiiOIFnGfIShqD5Dn6GtKCgZY%2BjXaxkCrKgyQ9ItCkzOgJxmqYljWGYjHvQZ%2B2E503SZC4DDuJ4bR6CE8xlBUegFBkAiTH4S7Cz0gwC0srM7QIfQTNzuRLjUdQK7M0vDJUYz9GLei4s0WuLJUqwKBBWwSJ5HA/qQDG8ExYXyUpKlqRpkhaRyuCECQ0FcGlcEA6sCCYEwWDxBAyH%2BMcrwEccCSSBoASSDydFfjyBEURwVGkDRMGvDyXCkQR2FF1%2BkhcF%2Bcc8nbPlMSxbGB5xWV8dlAmBSJhXFUl0lsJwTQsLSCQKUwhIGEYMUEa8K4AbpPsGUZsimYj0jI9ZaN2bogTOa5bXW7b9u%2BRwAVCRclwhc8xCD8Po/IOPwCT9Pq7xagiVxNBZgBxlXFt93cSiUVV%2BeUkogAHkPBSd81pcAIlwNclVqq1XqnZDqLVYYoK6j1PqDhYZDUYAQUa40fJTRmnNBasMVq/W2ABfA206h7UWrPVQR1diwzOl0HyV0botXulQ9Kz1YbvU%2Bpgb6q0jB/VAM3PgwNQbg0htDP8sFkbL3MqvWQ69bIAS3pjf6NMrC404QTSOgESaZDJhTKmui6YMziEzQxZsujyz8BAVw%2Bslx81KNrIWaQRZZGVuLFI3ipb808arBx6teizFcXLcJis5geJNgbSJfjEn9GNoLf2awNiWwyRdA%2BddOCX2viPMea1H4zy9npX2KV/bpSDqQEOYcRhGIujnPOU8k4JCrgkBIxxk7KSXIfeuthG7fxbvANugkgoAL/sQXu2wB6RRYAoWkBJaTQNeE6GYOlKkLyXEohGKi4bqPRiAciO83JLX3t5OyTET5BXPqFBZKklkrLpOszZmoErAPfilY4X8AbcRykA/K0zgUgJWckZIsZoHRg%2BROK%2Byk%2BB0AQZQJBAF0ETVghizB/UcGv2GvgsaE1qGYGmrNMQZDXoULEbw0gNCdr0IOkw5Ax1WGCHYZda6t1mo8Mevw16gi0jCJ%2BmIsIEjMpSKYCDMGEMoYw1evssyEhVFWVRhonQpztHGBxjYAx8AiYmIEItOsFNsa00sPTB2jM8BYDsdEnoHMuY5H8e4hY6SAmFEyFEyWmQ0myzVj0WJUSA31E1sEhJqsknOpSUbcN6SzYW3Mlc2uNyClPMuC81Z7y8QKk1N7fSft/nN2DqHcOlBratJAGYKexxjhfnwhXOitaEikRTYxTgDd2J1JQpIBIWlOlcCkARDpccqhZ2ONc9tzEm6ZWttpNtDsO0zsQm9OI6RnCSCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/is_equal.hpp)

- [unit test](../../../../tests/unit/varybivore/is_equal.test.hpp)
