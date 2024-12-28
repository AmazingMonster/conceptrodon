<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Pop`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-pop">To Index</a></p>

## Description

`Varybivore::Pop` accepts a list of variables and pops the last one. The result is stored in `Shuttle`.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n-1</sub>, V<sub>n</sub>
-> Capsule&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Pop
 :: template<auto...>
```

## Structure

```C++
template<auto...>
alias Pop = RESULT;
```

## Examples

We will pop the last variable from `0, 1, 2, 2`.

```C++
template<auto...>
struct Shuttle;

using SupposedResult = Shuttle<0, 1, 2>;

using Result = Pop<0, 1, 2, 2>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Pop` is implemented as a shortcut to `TypicalPop<*>::type`:

```C++
template<auto...Variables>
using Pop = TypicalPop<Variables...>::type;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2Blwu1yOtyECC8BAI9C%2BhyBBEwLDSBkRJkCbiYUNQADo8ejsCCJsQvA5wZDofR0VYriC/ntbthVIiGOgAGLEWRwg5AnY7W4AdUwtwA7nRaLcvEpbgQEHhPlQvAwHDkZag6fy0MqmCydcLZcK0sQPgkAG6YdC3QyW43IDZKS1pAYKHEgxHI1GYdFuAgAT2ezDYBKJBBJZKZLPZnMEtxMSSsSXu1JBbqRKL13vd6bRGKxRDxrsC2FuyAMCk%2BQkwAEcvK9MKQrdiCwA1Vp4JixegKYNXYmkgiM5muDmyb2Vmt172t4jtzsfAvBosp%2BMg25rmVpz3evO4vEWTDACIMCLAbtLq7ryVZIy3ZRMYDC9H3cHV2vKr0Y/eHhjHowuvENtOs5dguS6BDSwKJsmtK/GCAAq/p4KItDKKgaTcmcqYehmuZNvi56XH2ZIIWkSFiKh6FxgmSbgSmVxZluuFELcbJ4MQEw9oRob9rcJFkShaHeqx7EEJxVGruuUonjK/qPoEz4QlCMIfm4i4QXGNHqfRm44Zi2IsWxEwNjuL5augnFEQOfHIRRQmGQQDaVmZYkrheknXsAMnPLG8nkkpVIYsJHFgepUG0TBlwMbpJlBQ5jbMU5AjoMZeE4gA8ga7EWdxxGITZgmBfZjmYGZDYZQgCT/oWhK0q5lyXlJN5%2Bs8Elrk%2Bg6RiOgiZrJgbCtZ5EFW45WVaB2AgCAzUfjV9XrhNUWIre94qbFxXOSFy6aXRoIArt3x0mCACSHpIowLSNBhvJ7ddmERQtKk7i2bYdl2nGNZ5FE%2Bc%2BA0CWkU7PXOVUEvNsnQcCsE3fCB13EyrAosK%2B0Q5Dt3g8CZiBBEpZeFgPluFqWxpAQZ4zdDBx%2BZSCNQ9p2E5np%2Bb4TNlnk8pYOkwyQheGkxQWgASh8Xi0AOiOXO94Kc9z6B8woAsDu1ikU96qS3FwDZmGp230rcUsy5dIKi9rgtfbxeWDX9GJKyrtxmKrwOTaD4Wo5rcEfELVNcTqSEAPpMOWCQEBAEzoBNCisJg3tnm4BtxRzXOZLz/OCwSyzUhwqy0Jw/i8H4HBaKQqCcKpljWLcCjrJsj7ozwpAEJoqerAA1gEkg4hoAAcZhmAAnJ3XD%2BG3rdcEkSTSOnHCSLwLASBoqTZ7n%2BccLwCggKkNc56npBwLAMCICA6wEGkULkJQaDInQCRRKHnCqK3ABsAC0N%2BSLcwDIMgyvN2YvAWoQJB4EHKv8EECIMQ7ApAyEEIoFQ6g16kF0CrEUxAmBpE4DwNOGcs61zzpwNKUID4DlQFQW41976P2fq/d%2BOIzC3AgB4U%2B9BiCxkrssXgq8tCrAgEgE%2BpF6FHwgFws%2BiRgBSGtjQQWlVKCxEwbECIrRfQoN4NI5gxBfRpViNoEqq8q4nzYIINKDBaByJgVgWIXhgCYloLQJe3BeBYBYIYYA4gjFsQ0Xgc0Vjc6YFUCVKE2wq4RERKPXOtA8CxEQcojwWBMGhjwJPaxpBzTEFiHHR4dijDBKMLXVYVADCnmbO8EUaUAzyPAcIZCoDpCAPkEoNQmC4H6HsSgaw1h9AhKXpAVYaFGhWLvoHJ8pgi6WDMHPBJM4sBtIgKsOwLjnAQFcNMPwKswgRGGFUUYKtijZAEPMvQGzGgLBGIkFWUyVQCH6FMTwnQ9DHMaGcwYyzFhrNsJMdoFyChHOefs1ZhzJlly2BINBHBM6kFnrweeRDb4Pyfi/N%2BUhKHUNwD/Bh5hAhcGYdXTJqwKpMCwIkCZpBG6SECDiTugRh4aEkGYSQN9p7%2BBvp3fQnBx6kEniinEN8uA31bp3AeN9/CSF7iSm%2BwLMHz0XsvdFa92Hbw4bvXBh8KB8NQHQ8%2Bl8OCtBYKaJId8mAlgMDeLgnccRcBbl/fARBRl6EqcA8QYDKmQJqTA3Q1sEFIPkQCoFIKsEcBwfvKEtwCHgpIU/Us9jlaGuNRoahtDuEJEYYEMwaLWHrxlfwnhCrU2jBDUYA1XBUiiMROxCRUiZHKOKYo2Rqj1EOGKdos6eiDGYOMaY8xljim2PsY43O%2BBbSODcZgzx3jETFP8fUTBwTQmyIidsXO0TYlVwSUkpQKSO0nkyXwHJCg8mYAKUUuJVqykSAqbIe10Dc5OvqRk/pVhLAtNiOMjphMcjdN6fJK91ghmgpGX/D48BJn1GmX4WZrJtmLNZJ8pY6zMibNyK8hZ6QoN7PuQcq5/6TlNGeSBnoAHbngceXMc5%2BQ4P4buRUZDqK1gbD%2BeR0eHqRWcEDZC3VoaDVGpbvCs1JA42opYRi0gWKcWUABUyllhryVJH8J3IegQKVUv5cKmBorbDiqTVK%2BAMq954N4Rm4gF82CcHVaQlgChTRv1NCxz0ExTWIr/pa2Q1ryklJPbUkAwQXXIOse6jBCnsFyvwYQ1QhnjOmfM3qCYUalUxqRejQIia10poiwIrTCX6EgBM1zT2ZnO6ewswQT2AWKl0ALUvCAkiYHltLXE8rKi1EaJrUqnRBB62GK7ZgExZixCtrie2tJ06bHOJVH2mBA67RDriSOwJvBx1hN9FOqJM4528AXckpEK6MmSvXfeTd%2BTCmMGKfukBh7HPVNPToFzF7jBNJveO%2B9edH0CCsTsQOjSBkWA/XnL9Yzf1YbQy4YDsG9BLNI18nZCGciYd2TkXDhzvs3Iw/9o5qHYfzCQ8D95AxMPEah/8ij5dsc0a83Pej%2BXbhGZM7cTLOIcvscRVx2LkrMWYGxaMPFo9hMgC7jiQIgR/B935dPLnSROXycJwvJTK9eMEv8MSweKQ26SB7lwduZghWj0CAT0FnAeP04ZRwT%2BwuNei5U6sBJWRnCSCAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/pop/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/pop.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/pop.test.hpp)
