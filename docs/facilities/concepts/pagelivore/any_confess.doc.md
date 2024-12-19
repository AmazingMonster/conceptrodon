<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AnyConfess`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-1">To Index</a></p>

## Description

`Pagelivore::AnyConfess` accepts a class template predicate and a list of elements.
It returns true if there exists an element whose value result satisfies the predicate and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...||Predicate&lt;Elements::value&gt;::value)</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept AnyConfess = REQUIREMENT;
```

## Examples

`AnyConfess` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||Pred_0<*>::value)` and `(...||Pred_0<*>::value) && (...||Pred_1<*>::value)` are both atomic:

```C++
template<auto...>
struct Pred_0
{
    static constexpr bool value {true};
};

template<auto...>
struct Pred_1
{
    static constexpr bool value {true};
};

template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (...||Pred_0<Args::value>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||Pred_0<Args::value>::value) && (...||Pred_1<Args::value>::value)
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEIGYA7KQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7Jv5uTF5EAHRXx9gmGgCCE8ReDgDUysSY6AD6Gnf3JmSVger1BrzmjmQrzQDAmmFUaWIr1iqE8rwAbmIvJhXoCLARnphAQARY7AgHJUn%2Bcn/Xb7Q5Ek5nS7Xfy3B5PF4Ed6fH5cf54/5g8EtSHQgRwhFIlFozHeHF4gnYklkgWU1UPWl7A5MI5M86oV4ASRu/05bwAsgJUEQGABPNXk4UQvBQmGSxGvZmGuXY3FAk3q6lqqk0h50nV6twEO1pRisTBXC73YjABSmh6fACOXjwnwUrwgScBbhLHy%2Bv2ObhTaZAIF9jOwdYby3%2B7t2UuRqNoryoXgYEFbQM%2BBA2DF7YiUqvVmvD2oZVZjceYbCTNfTbP%2B2dz%2BcLxeSpYP5Z%2BfxO6%2BbWMbF/ly1xZgAbOZ73vrgey7zvvyz6mFNflWy/0wVsHnbeFPRlHs%2BwHIcLBHMdXiVRkrBnAEOVFV1viYBQlDaah%2ByrK0GBtAQHROL9bjZQdW2pDhVloThAl4PwOC0UhUE4UtLGscF1k2BUzH8HhSAITRaNWABrEBAnvC4AA57ykQJknvSQAE5/GUgT9E4SReBYCQNA0UhmNY9iOF4X8jJEljaNIOBYBgRAQHWAg0nOchKDQfY6ASKIE04VR5IAWhU15gGQKEpAuMxeC%2BQgSDwdA9H4QQRDEdgpBkQRFBUdQbNIXQuFIAB3YgmDSTgeDohimNEtjOAAeXONzuVQKhXkC%2B8QskMKIteKKzELDxvPoJFzEE5ZeGsrRVggJAvLSHyyAoCAFqWkBgCkMw%2BDoXZiF/CBYjq2IIlaO1Kt4E7mGIO0GtibRMAcC7SC8thBAahhaHO/KsFiLxgFOWhaF/bheCwFhDGAcQfrzR7HHRTAQdY%2BFHvObYhIiXZ6Py2g8FiMqbo8LA6oJPB9NB0gEeIFElGJPZIdxoxRNWKgDDTAA1PBMGKhrl2elLhFEcRMoFnK1Dqwr9EhlBrGsfQ8d/SBVlQNJGhBoKJnQY5iVMLjLDMUyqeIRLEfgVY7DhnIXAYdxPE6PQwgiYYqlGIrimyARpj8N3Mg9hgFhGRIiothw%2Bkmdo7YKYP6ktgR%2BjaAOXaD2xw69vQ5gTp3Fld83eK2CRqo4RjjLqsyOuC0LwsiyRosLXB4rGgSuEm4TmdWBBMCYLBEkHUhJMkfwLnU5JJA0SQzEke9DOk1TtI4XTSH0wSLgU%2B9ZNU2SuHvQJJC4QJ1PvEv8rMiyQCs5m7McubnOa9yVrW0a/LYThWhYdFkiCphoQMIx%2BtUi4uAXGRvgIgxskpFQFmlYW0hRZKHFvlXQ21SrlQuoXYuJleBmSaq5c4rw2pemIG/D%2BX9kA/2AH/ABQChqoBGgkO8/gzAt2mrZa%2BD8EgeVWjQxao0QCv3fkFUhkMuCqS4EZGgtA9oHSOvlK6Z1nqyJundB6T0KavUYAQD6X06q/X%2BoDYGz1wYM22KxfAnxQ4IyRrFVQqNdjPUxvUOquN8ZnSJsYqaxtyZCSpjTTAdMIZGEZqAGyLM2YKE5tzXmjB%2BayCgRlGBsgxZ5VYogqWTNdZWEsPLWIite4qzVpwDWBAtb%2BB1rLfWhsEhgNNkrHosc/AQFcGnIqjsKiBz0O7RoTT0i%2B0aInJY0dehx1TpHb2tTQ5DPmFnNpwdhn5FGRnQYUyk4FzWBsfOzc57oNLpwAhRDP7f0hhQwBGg64gJIPQ5uU026kA7l3UYvdsYLyXv/MeyR97JGSP4cek9d5H1MpwU%2B59gmX3gNfFyLUOFsOIE/bYr9QosAUOiKE6JhEXAZBMWKZywHJRiULOJWV5BwKSToAIJUyoVVBmg2qx9Gq31au1OFPUEVIoxKi9F3IIDDW4XQ8a/gmEX1YVwpakKhU8KRWkNI3wUWqW%2BOyzChCVI7QkQkKRx1To3Xkeq26904bPTUe9T630TGYD%2BgDMQ%2BiKaGICW40gpjLYWLqijZAaM7GCAcTjPGBM7SuJJh4563jMi%2BPpgEiIQSZp8FCeEnmfMKaQLxRIeJ2UiUS1JWQmWesbBOJycrVWOQQYAHpNbpoyRYA2mCjYm2zWMxo1tbZzIdjbPprtuklByF0jpOQm3JxDo0eOEd60DLqX2rt6dZn2xmZM1pyyNkKDzhlKlfzME7MZa8ZlyK2W6kRhy%2BuoCLn8uCe3Tu3dKCFyeUkf%2B/ggiBDHqIjQl7lKyUXfVcytgz6twPX3EAA8AH%2BFkjvAS177wCWUnPfw1L/kvuYcsQuMUn0n3fTNVYVMsjOEkEAA%3D%3D)

By turning `(...||Pred_0<*>::value)` and `(...||Pred_1<*>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AnyConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyConfess<Pred_0, Args...> && AnyConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept AnyConfess = (...||Predicate<Elements::value>::value);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEAdIADqgKhE4MHt6%2BAcGp6Y4C4ZExLPGJ/tJ2mA6ZQgRMxATZPn5Btpj2RQwNTQQl0XEJSbaNza25HQrjAxFD5SNVAJS2qF7EyOwcBJgsyQa7Jv5uu/uHmMduTF5EAHQPx9gA1MgGCgrPysSY%2BKK7pGeBAAnslGKxMA87th6GxBAoniYNABBNAMLbJAjPZEMYEeBhUTAfZ7HAAizwgUJMAHY3DS3N9fnh/pcTjC9owCAoQCAAG5iLys7A8/neTDLY5WFFI5EAegAVIqlcqVbKZQqlc8ACpErnPZVqlEalUmxWG5Eys4HJhHE43e6PfzYGUzYheBxfH7oAD6GhlNKlyOeweeMxtzNeAhmmFUyWIz1iqE8z1FgpJ1IsBDdl2ppMl/tz%2BelKKtFyu9tQVKdLqz7qxjJ9XALgZDocajmQkYY0dj8cTydTmHTmezNLz/kDY6LFpLe2ttuut1QzwAkoiUa6688ALICVBEXHNmWtsMdrs9uPPCspgVDgNrwsTgvjyez8421mnUHgthQ5HEYAEWrFEfgARy8PAfk%2BHE8QEQkPiuBtfUBf9AKrZ0UTRC8%2ByTWhnioLwGAgCUMx%2BAgNgYfCxCUfNC2LZFSw/K4QTBZhfweVCgIw/9MHAyCiWxXF8XgoCGS9ZDsQAhR0JJMwADZzDkwTYIJIlRKQrgUKk9CZSw3ZewTXD8MI4iAzIiigVHJ86JnZFT2Zb0mA%2BBICGoQirl3Bh9wEYEribasnWIiUnxRDhVloThAl4PwOC0UhUE4OlLGsUN1k2O8zH8HhSAITQwtWABrEBAkkO4NEkLhqX8DRAg0eS5LMAAORr9E4SReBYCQNA0UgYrihKOF4bkety2KwtIOBYBgRAQHWAhkluchKDQfY6ASKIIU4VRGrkgBaOTJGeYBkE7KQ7jMXgmSIYg8HQPR%2BEEEQxHYKQZEERQVHUMbSF0TSAHdiCYZJOB4cLIuivL4s4AB5W4FqxVAqGeba9oOo6TueM6zApDxVvoeNzCy5ZeFGrRVggJAVuSNayAoCAqZpkBgCkMw%2BDoXZiG5CBYkh2IIiaYEQd4PnmGIYFodibRalG7KVrhAhoYYWhBe%2BrBYi8YBrloWhuW4XgsBYQxgHEVX%2BLqXkiUhmNalubZsoiXYIu%2B2g8FiQGxY8LBIazPBOr10gLeIRMlFJPYjZdow8tWKgDEAgA1PBMD%2B6HWKFt7hFEcRXoe%2BQlDUSHfv0I2UGsax9Fd7lIFWVBMUyXXdpmdAyVMZLLDMfrA5urBK%2BIzpukyFwGHcTw2j0MJ5jKCo9AKDIBEmPxNJnnpBknkZNJqOoBD6CYR9ydeuml%2BpZhX4ZEnX2Z570MNmhPxYz9WBQ0q2CQwY4KLeshgbkZ2/bDuO07SrYwgLgQgJBZJExJlHVYCBMBMCwIkXuRVJD%2BDuAATn8NSSQ5UzCSDkt1QIclUGtQ4O1UgnUsp3DklwOSjVUGNWoSVLggR0FyQ/t9AaQ0QAjSjhNaaFNZpw0WnTBm%2BMNpsE4E0FgvJqS7SYK8AwRhMaoLuFwMql18DXVuvdWQT0s7SBzh9fO31dCswBkDIWr9359V4ANWG81bjPERleYgUiZFyLeEbJRKiyo41QHjBI4CzDExyjw/hIiEhLXpn46m%2BMQCSOkbtDxRguCoK4D1GgtAOZcx5t9EWAs055LFhLKWDg05y05IrZWkM1Yay1jrNOBtw7bDivgH45tLbfWtsgW2acHZdEhi7N2AtPbNJJjdP22VA7B0wKHQ2RgI6gDGtHWOCgE5JxTowNOOddEvX0bIQxX04omKLpHFuVhLDl1iD3autcoycAbgQJu/hSRnOsO3GxndbqWyrn3Q%2BzgICuEvppcepRT7TzSLPLIu8F6kCXpkW%2BU9979y3hfaFV8D6b16MfCeYLz79CBWMfoCK14Pyfi9SxEN2GcGca42R8jPEpO8RoCkIDrrgK4ME0m%2BVSAwLgSMXuTtSHkOUeVakzDqRVUkDgg6mlrFQ0GrYLhISlm8PgPwua8NInhOIGI7Yki0YsAULyTsvJGUXBmOo0BXdtGPUzrs9OByC4BFIGY4GesKVsP6jDQRCMkb6sOoa41KYzUfhmL4/xBNMr%2BE5aEym0SaZavjbE41yRkjelNag705qCCORcQdNmmSEjZN5vzMWBTS3i0ltLMpfj5aVJVi0zA6tNZiHqf7Rp8zRmkFaYfC2us4pdJ6f7PpTs4qDPdrBL230fYTN4FMtIMyw7zIiIssmfAVlrOTqnf22y7USD2e9POhydDOoUcYUuFzBnXPirc7snBZSNxLq3Cw7z4qfO7vAB%2BGKeiD2HjkGFIKFiIthRCnoBK4XFBxXfdFyKsX4rRUiv5cGb5QeA9fFoCHCUodBdBjlawNjPzw07Kxn9qX%2BueIGk1IbdhhuARosBhMOWQKWdA2B8DKCvyFSAMwyj/BBFqhVbqfHqQ0M9TYzgnDuEsdIEgwIaDAiNXkqgyQqCqoYK4P4Yh/hKVeoVVy5Yr8LpiflcxsmqxA7pGcJIIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/concepts/any_confess.hpp)
- [unit test](../../../../tests/unit/concepts/pagelivore/any_confess.test.hpp)
