<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsDifferent`

## Description

`Varybivore::IsDifferent` accepts two variables.
It returns true if they are different and returns false otherwise.

<pre><code>Left, Right -> Left != Right ? true : false</code></pre>

## Type Signature

```Haskell
IsDifferent :: auto... -> auto
```

## Structure

```C++
template<auto, auto>
struct IsDifferent
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto>
constexpr bool IsDifferent_v
{RESULT};
```

## Examples

```C++
static_assert(IsDifferent<1, 1.0>::value);
static_assert(!IsDifferent<1, 1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto, auto>
struct IsDifferent
{ static constexpr bool value {true}; };

template<auto Variable>
struct IsDifferent<Variable, Variable>
{ static constexpr bool value {false}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxBLSAA6oCoRODB7evv6ByamOAqHhUSyx8VK2mPYFDEIETMQEmT5%2BAZXV6XUNBEWRMXEJtvWNzdltCsM9YX2lA1IAlLaoXsTI7BwEmCyJBpsmAMxuTF5EpADUx0QH2CYaAIITxF4OZwCSCgAieFRUcYwEtzuJgA7BYzhMmI5kGc0AwJphVIliGdoqhPGcAG5iLyYM4giwEJ6YEEfA5gklkwGAzbbXbEw6XVBnABqDTwTGi9GugMezwIb0%2B31%2BxH%2BBzcrOI7M5mHOEqlXP2N3u%2BPB9ShMIE8MRyNR6Kx3lx%2BKoYiUFP25OBpPNVPuAHoAFSOp3O22Ah2OgAq2CEHqdrrtzsD9v9QPuEKhAH0mAolI0IO8vj8/oIxVxzlwAHQaa4gED6nHzSlhtV4ZBRmNxAgQMBgBNC5MAw5ps5cHN57GYQvmjiLWicACsvD8HC0pFQnDc1ms4OWq0NZn2PFIBE0PcWAGsQP3JFnJFxgfsNP2NGYAGynswADkv%2Bk4kl4LAkGg0pGHo/HHF4ChAL5XI57pBwLAMCICAywEIkJzkJQaDbHQcQRKw6yqJep4ALSnpIZzAMg0JSBmZi8Jg%2BBEJK6B6PwggiGI7AVJR8hKGoq6kLoaYAO7EEwiScDwvYDkOzEfgA8ickH8qgVBnCh6GYdhuEtjuZhnBAHhwfQyLmIu8y8H%2BWiLBASCwYk8FkBQEBGSZIDAFIgQ0LQmzEN%2BEDRMx0RhA0ACePG8G5zDEB5QnRNomAON5pCwWwghCQwtBef%2BpBYNEXjAEctC0N%2B3C8FgLCGMA4jxfgIoOHgGKYBlo4IiFJzrEuYSbH28W0Hg0Scf5HhYMxhJ4I%2BmWkKVxCokoHxbLlTVGKuixUAYwAKMyeCYGxQmJIwYX0dR4h0bIigqOo8WsfouUoFOlj6M136QIsqCJDUGVoRM6AHB8piWNYZjvv1ZFlfAix2CFNQuAw7ieC0eghNMJRlHoeRpAIox%2BGm0M1L0ENzO0f2dJMcN6L9xUCF0jTI/05RDN0WNphCBPg0TEg/bOaw07eHCDq%2BgmcFJqEYVhOF4Ypym4IQJB4guXDacuE2LAgmBMFg8QQBu/j7BmACc%2BzApIGgBJIp7Pv2p5K4z96kI%2Bi4ZqeXCnpeSuXub25cP2Kuniz8Ufl%2BP5i/%2B%2BkgQZYGiVBZkWepiFsJwDQsBiwJoUwMIGEYLZKxmmYVSRJB4ORaZraIG3SPR21MXtICBBxXHeXxTMCc7nAiRBJxnBJFzEGHEdR8gMfAHHCdZspqnGepQv7GYou6QB3sB3E0HmagakDKH4doS3uVcErXAvnZDlOS58W%2BZ5YVb/5gXBaFvURf80WxcxiXJal6Vhdlo3rKOhXo6V5VEaoVWbGFdVVMxTUtZ57X3x0pKHqS5%2BqDUwMNHKRgxqgA9nwaas15qLWWsOJcGcaKDBzoxXao5dCBFbkdF6J1f7nTlmOa66Rbr3Ues9Kwlg3q8FQB9VOX0Lpo1xn4CArgyZBEBoTWYxNEbpB4UIwoVMBHYyqOjPGmNgbZHJlIjh%2BMpjFGpuTWRWR4Yk0pqoiRIslgrHpvohqzM3yMLZjPJu0dcrt0TnzZOGlhaD3FqQSW0sBhkIaobY28cNbAntsCA8mtMJpjMWOTgrtfwTUAl7JA4ExLj1HsQIO6xQ6yRYAoDE0IMSLwzHSCYREHGpworIdatFs5bWwcxXQ%2BxSBF24plUupjWYcCrmJWukk0lYQyVkzEuT8n8hUpPHucQ%2B77GcXAkewyTKJOmepPMyBEiJAjDkpWEYBlRgbphPgdA16UA3qOXecUlxHP3n9MKx8ooxTig/TASUUpiGvr1W%2B0DAEJTwEVRwz9mKVWQNVT%2Bghv6NWaq1DyADOrALCmAlIECRrQLCLAvS8CmAzTmgtJaK1eroKzjIQQuccE6BALUghtDrCnWiKQy6FDNScFtPdQhdCLAMLHMwrAlL2H/S4YDHhYNdGQwRikGGGQ5FaNEQwfh/KOUY1JiKyRHQZHdAlajCmTRZXqMVeI/ltNDG0SaeXd8FitndMydk/pkIyqDP5qRPuIsdIuLcTLSgpdvEF3jvsfY/Zjx7mfO64EFsnYGs/LYN2Q95jy0kP2ZW/ZLxniVpIJWB5VZcGJZwfY%2BrzFBtDaXQiAaM12o9osfqqRnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/is_different.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/is_different.test.hpp)
