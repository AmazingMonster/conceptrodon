<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Reiterate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-reiterate">To Index</a></p>

## Description

`Typelivore::Reiterate` accepts a list of elements and returns a function. When invoked by the times of repetitions, the function repeats the list the given number of times and stores the result inside `Capsule`.

<pre><code>   Es...
-> N
-> Capsule&lt;Es...<sub>1</sub>, Es...<sub>2</sub>, ..., Es...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
Reiterate
 :: typename...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Reiterate
{
    template<auto>
    alias Page = RESULT;
};
```

## Examples

We will repeat `int, int*` four times:

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<
    int, int*,
    int, int*,
    int, int*,
    int, int*
>;

/**** Result ****/
using Result = Reiterate<int, int*>
::Page<4>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Reiterate<*>::Page` is implemented as a shortcut to `TypicaReiterate<*>::Page<*>::type`:

```C++
template<typename...Elements>
struct Reiterate
{
    template<auto...Agreements>
    using Page = TypicalReiterate<Elements...>
    ::template Page<Agreements...>
    ::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACc0gAOqAqETgwe3r4BwemZjgLhkTEs8Ykptpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJydIKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yuhxu2FUBFcFiYyAA1p8DoDISxUgZISZAm4CABPJ7MNgAOiJGOwwPGxC8DjBEKhMPhJgA7FYGXcMVZLsDkaimOjMcCbgKbly0ZgMVjcYxWJgiQSSTdkAYFB8PIImBEEqR%2BYKcXipTLsPQ2IIFMCSWSCBSqeDIQx0NC4WKVc11cQxQbMEaCAoZWbAqSOUytQLhTzRZidZLCUSLsBiJgPYwvWbLoKbl5MkYbgBZTzoG4Yu43J1qyKuzHuz3eomkG4xuMJ40%2Bv1s00slscn6gtxMVIKLz0BH7JEe7m88W6qOy5uXcmUghFnt9%2BjtoGd24AFVxeFEtAASphCAlQ4PTpyRyKxRH8dKiRXEybpxdZ1TN6lt2J94fiKHW%2ByLqmQzHJgvCIJt/X/QVn3nZRiFQIhlCYYBMHzQM20CP9gW2bYbmhJQFyUEAgyFc8f0xYCiBuABJZMIIFOMAEcvDwOMPggSj80CVlOJuDQliIqCbhguDUAQpCxWox9U0ZP9U1TdMImAIUJQ4wtu17fswzcX0ZMFRkuIwlNtRIoCQNQKiaNTBimJYm42JUgsbi4PjDIFAShPgxDNIk8CpMDFzZPkzMIxUhd1OXctDXvMCV18/TTR%2BbD92QdZMgAN2Q7sCKIwDNPIszvKIqzmPeWyzA4rTuMo5zaJuNzYI8sTMQK/zpKIuSM0U4KHOtWkHXDCVr0E%2BqRM88SbgAWhuMwSRAEAIws2SBVmnLs1zN1IsbaswQ2r1ovQoi9JXbLjNy0yZTreNKwWgVAsU0TkIc9yRsatwLobXbiWbfaAzijsQX%2BAGvkw0FKJRHaeWyE9AV%2BQGAcBM8wdI8dIxvAk72NGiBM/SFv3RAMdODE6xTy87Y0u%2B9rrTDrBM8kLX3fPcDxxpH0Y%2BqcfMFZaTppl63sraL/OWiUjrQgz/thxFgducFWFRZCgbXCWh3ioEzECCIFS8LByrQBhNlSJNHyl/ZQqXeXJcuHLLwGvVPvAgS1LNo7Fd2G4hC8VIikwdB9yXecFYuW63Y9r2ffeft5wcx2NLFIiIgIGt492TV/PjxPBGTuPBHTghM9T7ObiT00vrFmGbl9iOoeBIOK9oSPuOxo8xzTwuM5o2b7rFSRtJVsv13ef2LafZpHGQAB9JglQSAgIHGdBZoUKUJ4fNxa4T4PPYyb215JPj0I4FZaE4fxeD8DgtFIVBOC0yxrFqtYNgetWeFIAhNAPlZYQCSQCQ0AAOMwZgkhJC4P4f%2Bf8uAMgZNII%2BHBJC8BYBIDQGhSBnwvlfDgvAFAgBQW/c%2BB9SBwFgDARAIA1gEFSCBcglA0AojoAkKIUpOCqD/gANnGqwyQNxgDIGQI5H%2BZheDe0ICQPA88uAyEECIMQ7ApCSPkEoNQ79SC6AkQAd2/KkTgPBD7H1PsojBAB5EClD5yoCoDcFh7DOHcN4fwgkZUIAeDofQYg%2BZn5LF4HgrQKwIBIFoW%2BVx1CIABPoYkYAUgzB8DoDjbBEBYjKNiBEFo2JtG8CScwYg2JDGxG0JgBwaTSC0M9IYhgtBUn4NIFgWIXhgDdloLQbB3BeBYBYIYYA4hKn4DjA4PA6UmkX0wKofJIEtgv3jnUZRtA8CxG/FkjwWBlEWjwIg5ppB0rEFiFvB4bSjDTKMO/FYVADDAAUAANTeGowxeJCn8CkTuWR0g7kKJUOoSpqj9DtJQNYaw%2BgZnYMgCsVABtshNPGnPAsphb6WDMOgjZxAxHvHgCsOw%2BSGguFtFMPwEiwjqgWCMCRRQsgCCxXoIlDR5jDESBI1FvSBB9EmJ4DoehaUNAZQMPFVKWUTDaEy/INKeWUsqASlFD9NgSF0RwE%2BqCDGcEsWwjhXCeF8KkA42yuARFuPMIEJyXjDkrAQJgJgWBEgQE/iASQgQCRJECNAjQkgzCSFYcg/wrCkj6E4PA0giCdUElYVwVhf8kgQNYf4SQoCbWsJlZUjBWCcGv0OYQkhfiyEmKoRQEJqAXEMKYRwFoLBUoMnGkweUBhMxcCSASLgv8hH4CIAi8R8jpHiDkc8xQrzlG6CiRonsaTJXSrQbwIxaazEWKsYq0t7THKVurRoWyzjAkJHcYEMwniE34N8f4rNi6yAZtCa4lAZaIkgJQTQOuCQ4kJMqRklJhSb1ZJyXkgpazimJlKeU5R1Tan1MaYU1p7TOkX26WivpSLKlDJGZCQpEzYEX2mbMlJCytgX2Wasl%2BGytlKB2QBhSibjmIXOZc65jBbmyGbY8%2BR7alHvJAFEo93zoU2HgwCs1l8QUCDBRCziUKrAwrhQkBtSLAXdBA84CArhSU4ttEKxYhKMjEpyHy7FpByXZBkwSkTdLGg8sk5ptlgrOXCupbYHTSnuVzEM7J0V6xxVOQ9VK/RMa5XjpsQqKdFaq2/3VXWkgy7dXrp8Qao1JrKCSq9T6yt9qGT%2BCSFAwIDqnXhujegzgcbcGJqIaQ8hpjgn7pzWwTg%2BabEsAUKlPhqUPMinGLWzVYi9DPPIxIJ5sgqNvIvroYIPatHNP7Y5lLHBjEUJAjccxljiulfK5V0M4x53brCcuwIa7vEEJTXl3dNC5sHrK57MeFWkhjyqwQMeqhOHRPPcQS9iTklZLvdd7JuS0WFNfYId9FSgOYBqXUsQv61n/r2chlpxVen9OURB5KUG1kwamTMuZ2IkNLIRWh3gGHtkehwwcjdfATmEcwFcm5ayGsPKa5RxRbWdAgGCPRnjvzmPIrYw0Jp2w54Md4xYWFQ74WIpYyiuoom/DicxWZqT6B1PGdUySoXKn5MUssxp1lvRTN5GU/L%2BlBnyhcoFf0XTsxWii4lasGzsjevJaHc58bZWbh7YJId7zmq/NLf1aQQ1xqRisdgeF2jlbAiBH8GA8NyDvcMkDSby%2BqXbDxuW0sc1kh/DWsgQyZBf9JAgK4AAswUbYGBD66bzBAWP72cESH2Neeo/rIvdkC1QA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/reiterate/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/reiterate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/reiterate.test.hpp)
