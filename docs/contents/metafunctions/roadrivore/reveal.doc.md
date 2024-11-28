<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Reveal`

## Description

`Roadrivore::Reveal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and becomes its type result.
Overall, `Reveal` turns a `Typical` operation into its non-prefixed counterpart.

<pre><code>Operation -> Road&lt;&ast;&gt;=Operation&lt;&ast;&gt;::type</code></pre>

## Type Signature

```Haskell
Reveal ::   template<template<typename...> class...> class... 
         -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Reveal
{
    template<template<typename...> class...>
    alias Road = RESULT;
};
```

## Examples

We will reveal `Operation`.

```C++
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

template<template<typename...> class...>
struct Vehicle;

template<template<typename...> class...Args>
struct Operation
{ using type = Vehicle<Args...>; };

using SupposedResult = Vehicle<Con_2, Con_3, Con_0, Con_1>;

template<template<typename...> class...Args>
using Metafunction = Reveal<Operation>
::Road<Args...>;

using Result = Metafunction<Con_2, Con_3, Con_0, Con_1>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Roadrivore::Reveal`:

```C++
template<template<template<typename...> class...> class Operation>
struct Reveal
{
    template<template<typename...> class...Containers>
    using Road = Operation<Containers...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJJcpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmgW47eweYRye7%2B0yHxwQAnqmMrJgAdB9H2ADUyAYKCg%2Bby%2Bv3%2BCm%2BAHlnsRbtkviYNABBcbELwOb4AJUwADdMGIEYiTAB2KxI77k76nG53K5nW4Xe5PF5sIEgv5MAFAjyCJgRBIKeFkileTJGTGoJjob5HAAikOhsIEl25zT5xEBn0C2BAIEezyOpMJRJlBoJBIA9AAqa0223mi02gAq2CEjpt9qRVtt3o9hKR5kCET%2BXiw0uOaAYm1SBAFWrNSKp50ueuZ7012AJKLRBG%2B3IA%2BhpTf6E9ck4znswWenMwRUej81wi37EYn6cmmZW08C40is/WBHmzE2Ca2aSnO6ye8ja9ncwPAsOS3Sx6W2%2BXU5OfuzOdXezP0VjccQ8AzDSPVyvlwyTh3XpvQRyNW9EcRgLGM3u6zmoQlFQwzSS3wihEwCUkyYZyoeCQnpcL5vpuBrSsai6IsBYpCF4qRFJg6BYgoXi0DmsqYji0HXvmZikHODB5sE1EFlRDbwoEZ5LtS16jhxt5Vt2W5gkCcHvgSaGgQAspgzRUF4kYNBBJG4vixw/jCDSCoiOoYhK6Cwa%2BT7MaxqGiqBeEEURgRyuJknSQ4cLHBRjHzg5NEaE5eaNnGLHxtOsLIHmj4JAQEDjOgOoKK8fmxm4JmEVRGFYRkOHRQQXxLAaHArLQnD%2BLwfjcLwqCcG41jWN8ChrBsmDSmYgQ8KQBCaOlKwANYBJIbwaMkRKBBo/gaGYABs/VmAAHMN%2BicJIvAsBIGgublWikAVHC8AoIAufVHBaCscCwDAiAgGsBCpF4BDkJQaB7HQCRRK8nCqMN/UALT9ZI3zAMgyDfFIbxmLwOGECQeAhSk/CCCIYjsFIMiCIoKjqJtOh6AA7jCqScDwGVZTlDWLZwEIncdOaoFQ3z3U9L1vR9X1tWY3wQB4l30MQVU1UsvAbVtpAQEgF2pFdZAUBAvP8yAwBSJRNCEfylCxDjsQRC0Dzo7w8vMMQDwQrE2iYA4yukBdbCCBCDC0ErCOkFgsReMAbhiLQq15RbuyGMA4jm/gxA644uIOwtmCqDrJ1bLVEQ7Jl5u0HgsQwurHhYDjtZ4NNjtHrECUys7RiR0YDUrFQBhvgAaieSM/rltWg8IojiFDlew2oOO6CkBg56YljWPoUerZAKyoNG2QO49wWym3ViWGYC2oEex5YN3EArHYXvZC4DDuJ4HR6GEfILCMKRFFkAhTH4e8ZAfDDzMMiRjHUS8CH0kzr/k189HfEwDNvl96LMD95MfthvxfSou8F7lU2BITGHBsqkHmvlTgpMHrPVeu9T631aYQFwADZmAYuBszqrnFYCA8RYESPPUgLVJCBDeAATkCESSQHUzCSH6rNfw/UqHjQ4JNUg00apvH6lwfqw0qHDQEf4ZI/gaH9WgTjJaK01p4IRttPa3MDoExOmdIWqBGbXVuhwFoLBsREkekwB8YouBULeFwdqf18BEBnnoSu4Ma7SDrkoBu5tdCURRkwNGeUIFQJgbjDg%2BMjonW%2BMTb4%2BjDHGNMaBcxlj2p0wZnzJmLMzC4I5ulLmPMtEpISBo4WTMQBRKMeyIw5iuAuUljsdUMs5YK3VnrVWitNba11o7A2jACDG1NjjS21tba0HtnrLALAXZuwWh7JePscb%2B0DjsPWoc6g40jtHRWcctgLUTsnWqqd06Z1diBXOfAC4KGLpgUuFY9aOOrpDFxsh67wwWp4/QLsUDFUsJ3WIc9e79wEIPYe5lR7WAnvlaeQNMA/O6LfPwEBXBH03qvQBiwT7FGyAi1FZ9kW72hTZV%2B/QMW4oaPfd%2B5RP5jDfoS7%2BpKhhAKviA9YYCcEcICTIuBJSYllLiRYqxGg6YYLsSzHB7N8GkEIZKEYpDw5cJ4RYjqRIJFEi6pIRhL0UiBNkbYeRmSlHwBUYdQmBTcn8xumwTg%2BiKYsAUNiT62J4nnHGDYzBQMHGyCcXc6G8g3FPMRsEbxviMYsuxubJaITCbhJJha16VqbXfDtRYh1OZ6bGtSQGQIGTjkqMKfkwW2bEg2qwnmeNeZE1%2BWICwF6fA6A1NWhAWW5tmmNMdo2jWWsvZ606UbE2ZtJmYCtjbO2DtaqjPGZs3gUybIzPNnM5AQdFmCGWRHKOMcHgbITseHZvA9lKAzmMrORzFEnKYEXEuZdrlutuRIe5MNvWNxAMEFuxgPk2FWVCvuDQHbmmCu89u49J7gtnvABeN88WwvhY/P%2BW8yV0r0PvBohK4PZGxVfIlvRKUQa/iB4lACP4wYpQSjD%2BHWjIfAasRlkN/HBsnuy8tlrrW2vtfScY/LbEkCFRmxRBCiGSogTKkAZgLGBECP4XqyRZpCaJII6RIbOByPWqK8h/hqH%2BGGgNKhkgqFdVoVwB9nBAhUdgctBRW0IG/Wk9RozOqVhHkyM4SQQA)

## Links

- [source code](../../../../conceptrodon/roadrivore/reveal.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/reveal.test.hpp)
