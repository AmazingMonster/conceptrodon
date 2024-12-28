<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyDeceive`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-any-deceive">To Index</a></p>

## Description

`Varybivore::AnyDeceive` accepts a callable predicate and a list of elements.
It returns true if there exists an element whose value result fails the predicate and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...||(not Pred(Es::value)))</code></pre>

## Structure

```C++
template<auto, typename...>
concept AnyDeceive = REQUIREMENT;
```

## Examples

`AnyDeceive` turns a fold expression of a callable predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||(not Pred_0(***)))` and `(...||(not Pred_0(***))) && (...||(not Pred_1(***)))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return false;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return false;};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...||(not Pred_0(Args::value)))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...||(not Pred_0(Args::value))) && (...||(not Pred_1(Args::value)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAgmgM45iqqcSHTF5Ex6cXVxM/gAIocTEkrElgRBvkQAHQIpYmADsFlOBHWDEOVDESiBVmRwPx9weJL2Bz%2BZ3OXGuBzuj2er3en1hqEpFxpQNB4Mh0NZCLhSNR6Mx2NxmGJhOJjzJN0OADUmABPWn7ekPAiYFipAyaoFuVmHACSQOwJPGxC8DgVypJKKsj0OTsOs0cyEOjM1zK%2BPzZADcxF5MGDUSapf4HaTw5HZRSqF4sTd1ZrtbqJf43AQlalGKxMAKHsRgApTSTTgBHLx4U4KQ4QAUotyNiAMVAEdmXCCF4sgEAB7yYJZDkmet4fQ4xVCebEJiBCtGYDHELE42h4iMookyx4pnVMPUZrM55hsAtFkv%2BM2PCtVmv1hGN5ut9snKkaLvn3v9oNDpZgswAGzmABdYNsiTbgS2bYdlwH49n2gaDsODICEy46TtO8YMHO9oisuhwEJa6YElupKPOS%2ByHAAKpg4yqrcZLbIc2DEMQJDms0brnEwChKK01AJvqipKvqXClpec5IhGHArLQnBJLwfgcFopCoJwTaWNYLprBswbmP4PCkAQmgySsADWIBJABcIABwAVISTIgBkgAJz%2BE5Zj%2BPonCSLwLASBoQRKSpakcLwCggEExnKTJpBwLAMCICAawEKkPzkJQaDanQ8SRHmnCqHZAC0zmHMAyDulIcJmLwZyECQeDoHo/CCCIYjsFIMiCIoKjqDFpC6FwpAAO7EEwqScDwsnyYpJmqZwADyPxpe2qBUIchUASVkhlRVhxVWYdYeNl9CfPpXBLLw0VaCsEBIFlqQ5WQFAQA9T0gMAUhmHwdCasQEUQDEc0xOELRKpNvAg8wxBKgtMTaJgDgQ6QWVsIIC0MLQ4P9VgMReMABq0GuyNYCwhjAOIOPVojjh%2BrRc1vIjPxbIZ4SanJ/W0HgMRjTDHhYHNhF4P53C8HTxCTkowJauTXNGCZKxUAYxbyngmDDQtx7Iy1wiiOInU6z1ahzYN%2Bjkyg1jWPo3MRZAKyoKkDQRRwRXjOgXKmJplhmCF4vEI19N290NPZC4DDuJ4HR6KE4RDJUIxDUUWQCFMfiJxkycMPMwwJENdghwIfSTJH%2BR53UBeNBMAyxwsCe2FXqd6LMrTZ/HucrAoOmbBI00cAppDBbwoUbcVpXlZVkjVXWuD1WdnkXVdCsrAgmBMFgCRzqQFmSP4cJucikgaJIZiSABgVWS53kcL5pD%2Bf4Zhwv4AHIjZ/g2UkSRcO5Lk2QPc2heFSKRkFZxUSndZKy10ovTeqdPKbACqjx2sgAwRh9ouThFwOEKk6pEH9k1IaOs2r62kIbJQxt%2Bq6G%2BqNcaENe790HvNDgS1Uo/EOGtEeW1SrIPJmgjBWCjqoBOvEf899LrAJirde6gjHqnQyq9aR71uFGC4C5LgQQaC0D%2BgDIG/UoZg2RnomGcMEZI1FijQRaMCAYyxnNXG%2BNCbEzMaTWWWwVL4FOA4PAdNnbYNUEzTUyM2Z1DmlzHmYN%2BauKuv7EWhlxaS0wNLMmRg5agAkXwZWChVbq01owbWsgiEdRIbII2fUVKULNvLT2VhLDWxiLbTeDsnacFdgQd2IIqnWB9kPP2Ad6kd3Lp45wEBXCNyGjHcoOc9BJwaKMtIGcGit0WGXHohcG4lzTsHQZlc5g10mXnNZeQNnN2rhMtuPdVjrG7hdK%2B9D/6cA4dtD0KDgC8MwVcCAM9cEiIXuIm6y9V7r0oOZAKQQOY3zvkkOErkkguTMLCwCNkv7OT/v1ABtggHXVivFJKKUVpyJgblfKHAWgsFKiwBQfp3R%2BhUXCNM4xar4FwY1Zq%2BS9aFK6vIMhpSdABBGmNCaos6GzVRYtSBq11qqDJRSqlNK6XtggMdGRwj9L%2BDEZiyRKAFGyOgVqkYlLUipHONSly5w5XnElSQ368RtHA1BjDAxdrYbwxpsjVGjArGY2xm4zAeMCZiEcYZZxyTImkHcSHbxDM/HIGZoEwQwTObc15kqCJgtonIziRkBJMtknhFSTddJTAVZqw1lrMxhC2USCKd1LlJteXPItl7GwoS%2BmqUdtkZ22w3YNuqRYLpqkelYBbfnLZYcI6HOjuHRZddpnZFmTO0ouyznLIrkXNo6ym4DIaKuqdud679Fmccnd5zO6XI6kKlFIV7kWsOOSylhxjW0v3LReVnySDfLVUvUgK814jE3mCvyAQH5Is8mYUDXAbIaAAjCi9Q9OCAKip%2B7eu8v7v2Pv4JIkHPJOSvv4YVl6wq/NMlfGqMHGGLwkSscWmRnCSCAA)

By turning `(...||(not Pred_0(***)))` and `(...||(not Pred_1(***)))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AnyDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyDeceive<Pred_0, Args...> && AnyDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept AnyDeceive = (...||(not Predicate(Elements::value)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBAKykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJn8biYXiId2UxEw%2BFEYNIdwIAE8UoxWJgAHRE7CvRgEBTQ7AgtAMbYpAh3K4MLEAETqmDwADdMHdoSy7hAiQSTAB2NyitwQBioBlIlF4NGYCAk8FkhQgECcsReTArPXQqzXEF/AHnY3HO4AFUwswUXzNv1NJyB5vucvQAH0NPbDkCabNMKoUsQ7nCEe6vbz/PyTIkrIkWRAw6ghStRRZkQRNgw7lQxEoDaKWYWjY63cjPVwffs/QIA0GQ8nERWPVW%2Bby47HE8nU%2BnM9nc/nMIWRcX/IbgWXDncAGpMLHVoFgiEfYcwpsPSkg2bELwOWfzkHpkF3U93WYfBV3f1ghuh%2BGoO5a7w89Ob0cl4Ef8dHqf7XNeDm3wgsuLyrtCbjYrizBsEKVzEMAFL%2BFS1zIgAjl4eDInaTKsuyXJrm4EZBIyCEKEKW7XDegbBncMSoJ4AEMBAaYihmmBZsQOZ5rQBY/h%2BpaguCYFQjCUF4rBRLwYhlHwZgGFYTajLMmy2wERBxEYtJ5FEpSvJmAAbOYBnKXhanchpLZcFpZEUch1J1retH0YxVCASxfYcQOBC7muVgCZONwWtasyLtuTSOMgHpMAoSgtNQgEQXOWIQVwW7ISxabjhway0JwiS8H4HBaKQqCcOKljWOeGxbK%2BZj%2BDwpAEJoOVrAA1iAiQGQSAAcBlSIkIoGZIACc/hDfV%2BicJIvAsBIGhBEVJVlRwvDqkEzXFTlpBwLAMCICAGwECk8LkJQaDPHQ8SRPinCqH1AC0w13MAyDIHcUgEmYvDykQxB4Ogej8IIIhiOwUgyIIigqOoW2kLo1kAO7EEwKScDwuX5YVLWlZwADy8InQyqBUHc90GU9kgvW9H2SF9AoeJd9AhuYDUrLwm1aGsEBIBdKRXWQFAQHzAsgMAUhmHwdBgsQ6oQDEOMxOEzRYujvBK8wxBYnjMTaHUm2NRdbwEHjDC0KrcNYDEXjALCtC8WrpBYCwhjAOIluKfU3LqnDgZ1PCOyNeEYJ5XDtB4DEKNax4WA4z5eBzdwvDcsQ9FKGyLtGOHRgtWsVAGIhM54JgiN49BjvA8IojiBDlfQ2oOMI/orsoNY1j6BH6qQGsqD0lkPsPbM6B8qYlWWGYy0p/9WBdyxXQ9FkLgMO4njtHooQLOUlR6IUmQCFMfjWbvvRDFvozWbU9QCP0kyr3kF/dPrDRzKfIwJBfcwH3oF4tK/Szv2sBQNVtgSExhwAqpAlq8BWmTR6z1XrvU%2BmYAUuBCAkH0mzDmuc1gIEwEwLACQ54dUkP4AkY0RSSA0JIMwkgDILS6iNKaHAZqkDmv4MwBJ/AGRFD1fwPVEiJC4ONEaPVIE4xWmtEAG1c47X2jzQ6hNTpCxFszG6bA7pwKpsgAwRgPojQJFwAkJVfokABkDWQoMa7SDrkoBucNdCS2RqjNWYCIFQNxhwAmx14R3BJrAimz1tGuz0QYoxDNUBM3iBgsw7MmoyPkSo%2BIZ1hYRP5szFAOjxYjS4EEGgtAZZywVnDDWKtHYlK1jrPWDhHZGzJKbc2OMrY2ztg7JOTtwSu3diVfAyIvY2hxn7ZAAdHbB26DjcOkcVYxx2CVeOidGopzTpgDOnTwigC2nnAuCgi4lzLowCuFjq7g2sbIeusMSoOObjnUeVhLAdxiLPHufc6ycEHgQYe0YbnWAntAqeAN%2Bnd3nk/ZwEBXBf2shvMob8d7pD3tkO%2Bh9UiwpPpvaFD8F7X0/gi7%2Bj8r59Bfqi/%2B38sW5ERT/eYUKiVcEAcA8GrjsZwxgeTSm15MkhMMd6ZU%2BA/oYOpVgjZOC8EEMoO1eaQRQ4sLYYkAko1EgjTMPKwyPUhHDTEYyzgkjpEbNkfAeRR0ibJMScQNROxmgsGeiwBQnJ3qci4PoyENoCA/W5aYwG1lK6WOOZDeQtjzk6ACKQJxaMk70rVctfGijiak1UBaq1Nq7UEgdaFCAjM0lRNZv4WJnNtoJNSQLQ1eb0nWpSCkD0tqRoeiTQQD0MbrHS3iIUxWystZlObdrXW%2BsakRONvUi23TMDW1tmIVpjVnadJmbwHpT9vYDNUP7MEIzBBjLDhHKOWJplx3%2BvM5O8QlkrKzmsmR%2BcmCF2LqXcubSPVHIkCcqGvrG4Bsya3MeNgJmPNKs8hgPtdhD2fbciwPzSp/JnvAQBuLehLxXqS9ey8/7byPsirI4KkVFCyHB8%2BQK8U31aNi9FwL8UDHQ%2B/cYAxkPkqI6A9YmwQHUqYW48RnAyaxutU%2BBNVaUEupZvVPlcSBWkFwfg0Yc8JWzQCBwlV9UzBSa4D1DQBk5VhugRq2wUjeNc1FSQgxfDEjUOqHJ%2BqQ0mH%2BAZeG1aanWpMO%2Bopjx/L1OkBThkZwkggA)

## Links

- [Example](../../../code/facilities/concepts/varybivore/any_deceive/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/concepts/any_deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/any_deceive.test.hpp)
