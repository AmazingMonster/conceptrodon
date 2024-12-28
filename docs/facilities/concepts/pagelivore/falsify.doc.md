<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Falsify`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-falsify">To Index</a></p>

## Description

`Pagelivore::Falsify` accepts a class template predicate and a list of variables.
It returns true if the predicate invoked by the variables returns false and returns false if otherwise.

<pre><code>   Pred, Vs...
-> not Pred&lt;Vs...&gt;::value</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept Falsify = REQUIREMENT;
```

## Examples

`Falsify` turns a class template predicate into a concept so that it can be used for subsumption.

Since `(not Pred_0<***>::value)` and `(not Pred_0<***>::value) && (not Pred_1<***>::value)` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {false};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {false};
};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<auto...Args>
requires (not Pred_0<Args...>::value)
constexpr bool fun(){return false;}

template<auto...Args>
requires (not Pred_0<Args...>::value && not Pred_1<Args...>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQgAMyJpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAggSYLKkGzyaJbkxeRAB0AM%2B2HuD3GxC8DmOpwuGhBJgA7FZHocUYdZo5kIc0AxxphVKliIcYqhPIcAG5iLyYQ4IixUMRKBEAEU%2BSIezNZcMeewOULO5y41wOd0ez1e70wn2%2Bv1QAL%2BQJBYIhBD5Fy4cMRINRaOaGKxAlx%2BMJxNJFO81Np9NojPhLMSbI59q5Dx5%2B0OADUmABPIX7EVPF5vJgfL4/IiHACSCseSshnq9GrZ2vReEx2MNBMOYdQ5MpFsRUdtnMejod3JuhyoXgYvtuILFQZD0v%2BAIexGACmjbcwAEcvHhTgpDhAGKgVSd%2BbCvm2O3KgSAQGaqUsQennkaiSTaJXqxAV4jTgR1jWrYynUWS6LAxKpdm5TPO4lgY9Tn2B5ghyOx6rLlKH3OnwXJcLTMAA2cxQMOUdx2hAU/3bBQAOwIC8xXR41zxTMTW3KsGD3WlD2PQ4CHBSVzxZS8XQrAAVD8VRuf1tm2Q5sGIYgSEVXVU3OJgFCUVpqGrKV1SfPcV3tDgVloTgAl4PwOC0UhUE4NxrGsNE1g2EDEh4UgCE0SSVgAaxAAJQL%2BAAOUCpACeFQMkABORI7LMFJpI4SReBYCQNA0Uh5MU5SOF4BQQD8/SFMk0g4FgGBEBANYCFSX5yEoNBXjoeJIlYLZVCsgBaezDmAZBMSkP4zF4M5CBIPB0D0fhBBEMR2CkGRBEUFR1Ei0hdC4UgAHdiCYVJOB4KSZLkgylM4AB5X5kpVVAqEOPLQMKyRitKw5yrMYcPAy%2BhCXMHSll4CKtBWCAkHS1JMrICgIFu%2B6QGAKQzD4OhnmIUKIBiaaYnCFovTG3hAeYYgvVmmJtEwBxQdIdK2EEWaGFoEGeqwGIvGAb5aGtBGsBYQxgHETH3wcPAyQ/aa8Th34tl08JnncxTaDwGJhshjwsGmki8G87heGp4hiSUJkXhJ9mjAMlYqAMDt3TwTABtm1JGARxrhFEcQ2q1zq1Gmvr9BJlA1MsfQOdCyAVlQVIGlCjh8vGdBPiZUxLGsMxApF4g6ppm3ujhhoXAYdxPA6PRQnCIZKhGfqiiyAQpj8BOMiThh5mGBJ%2BrsYPegmNoI/yXO6nzgQ%2BlaLO45z2xC5TvRZirmOFnjlYFE0zYJAmjhZP86agtWgqipKsrJAq4dcBq47XK4M69NllYEEwJgsASPdSBMyREj%2BJz4UkDRJDMSRQN8syHP0ThPNIbzEjMP5ElA%2BELMSCyAgCLhnIciz%2B56oKQrCgvSKV04rXQSgtFKj1npHWymwTga0NpYgMEYHaDk/hcD%2BIpaqRA/b1X6lrZqutpD6yUIbHqugPpDRGqDHufcAq8CCvNJKvxDjLSHutIqyBkHAFQegzB%2B1UCHXiDSVyZh54XSimA6B8RUpPUEXdI6KBuFcAclwPyNBaDfV%2Bv9Hq4NgYIz0ZDaGsN4ZC0RoI5GBBUbo2mljHGeMCZmKJlLLYil8CnEptTR2WDVD02eAjZmdRprs05sDHmrjzp%2B0FrpEWYtMAS2JkYaWoBgF8AVgoJWKs1YazMQQnWrViGyANt1RSFCTYyw9lYC2ITrYbztg7TgzsCCu0SO7c2FhvYMN9v7Wp7cy6U2cBAVwDd%2BrR3KNnPQicGgjLSOnBo1dFilx6BXeuxdU5BwGY0QuCz45136DMpuAwW4TLnqsdYXdTnuToQPTg7DEFcJJrwjBVwIBTxwSI0651F6kGXqvEYG8TJqL8u5a%2Bt8Ah/EcgEByZhoVgQsp/eyv9AqcAAeFWW0VQFIESotWR0jiCwK2C0FgRUWAKDJJiMkKi/gSnGFVfAOC6oNVkIQgp7V5CkJKToJIg1hqjSFrQqaf85oQKWitVQJKyUUqpTSlUEADoKOESdRI4j0VSPkfdXF6rFHktSKkc4lKHLnBleccVxCvrxG0QDIGkMDHWqhjDYOCMkaMCsWjDGbjMDY1xmIRxulnFJIiaQdx%2BcvG018cgBmATBBBJ6iErmXpwl8yiQjWJGR4mSySeEFJl00lMEVsrVW6t5K6TyS1CQhSOocqNty7hZtPbVKtvAW29tsiO22C7OtVSOk%2B3iLggOG886bNDuHPI6yxmx0WbM4o2QZlTOyDs2ug6GiVyLqOxu/Tl3bOOTXRuqy125y3eMndpyO7nNagKpFDDbmmsOKS8l5JpXBjopPelJAPlzy%2BcApeK816UB7qCpI98EWiLMGYLgFkNCgShZemawVbCAIkUsYyIBt7oNfgEI%2BiQAiQdcnZS%2BHBEiCuRXBxDPdKowf/kAy6KwRaZGcJIIAA%3D%3D)

By turning `(not Pred_0<***>::value)` and `(not Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires Falsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires Falsify<Pred_0, Args...> && Falsify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept Falsify = not Predicate<Variables...>::value;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQgkgDMpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJiSbhBYLemEhbiYXiIADo0ZDsDdkAYFAobspiJh8KIQaQbkjUWiAGotPBMGL0BQYoFoBibVIEG4AMTEmSoAE8bpCACI3BioTkEol4EnwqE04h0hmYBRolEYkAgABuYi8cqslyBPz%2BpyNhxuABUVQQ8Z8zSa7YbvuapegAPoaD6my4wp5whEU1Bq5mXcbELwOfGE90aIEmADsBouNxTN1mjmQWIE40wqlSxBuMVQnhuOu8mCFiaovPh8eFkKTCfrSUbzturrdXC9%2BwBvvBcsRyKD6KS2CBYYjkujnbjiaBqbTzQzWYYObzBaLJbLesrFmrtCUTYbs%2Bbrau5ppgsdwNBfohUMD9xDFwnkcvs6TC/TMpXa/z5KHUtdQrBMLDuI8WxPY8nXPW4qC8Bhu12Xtb37AMhzVC5iGAJlRyBQkAEcvDwQk8R5A88AFBEOw0MksJw4M8MuVk/w3YtaBueCGAgJZQMJAh1kQ/dD0gus4x9VD/QfDC0Xo3Cx0uQjiNI7leUo/lqOnWibjkxjMXMAA2QzVIoqioQ7Lg6Ow1URwUi4WJBddC3YziEJ4vjMAE4hEIIcN9SPGDjUta0kIBb9kDdJhcXiAhqAQhEuAxHjeJbDgVloTgAl4PwOC0UhUE4NxrGsNM1g2ECzCSHhSAITQ0pWABrEAAgMlEAA4DKkAJ4wMyQAE4kh6yr9E4SReBYCQNFonK8oKjheAUEBaNq3K0tIOBYBgRAQDWAhUmRchKDQR46HiSJWC2VQOoAWl6m5gGQTMpBRMxeGlIhFXQPR%2BEEEQxHYKQZEERQVHUVbSF0SyAHdiCYVJOB4dLMuyur8s4AB5ZF9s5VAqBuK6DNuyR7sem5nrMG4IA8E76ALcwqqWXgVq0FYICQY7UlOsgKAgDmuZAYApDMPg6BBYhFogGJUZicIWn5BHeBl5hiH5dGYm0TAHAV0hjpeAh0YYWh5fBrAYi8YBEVoA9tawFhDGAcQTZIzXHC1FVUdzTXkS2arwhBDLwdoPAYlhlWPCwVHfLwCbuF4N3iCLJRhVBe2g6MOqVioAwcKpPBMCh9HUkYbWfuEURxEB0uQbUVHIf0e2UGKyx9GDxbIBWVAOWyRaOGu8Z0BFUxLGsMxZvjz73fb7oXeyFwGHcTwOj0UJwiGSoRksoosgEKY/E3jJt4YeZhgSSy7BngQ%2BkmRf8jPuoL8aCYBlXhYN9sJ/d70WZWmP9fT5WBQZVNgSCRhwLKpAZq8DmvjG6d0HpPUkC9SmuBCAkCFJVLgjMaoZxWAgTATAsAJB4qQJqyQUQDXjJIDQkgzCSAMlNFqfURocDGqQCaSQzAoiSAZeMbUkhtQCAELgg0%2BptQgajOaC0lrYNWqzLabMdpYwOjzPmtNzpsE4ATImWIDBGDJn1FEXAUR5XeiQPAX1LKlz%2BhXaQVclA13BroYWMM4YK1AeAyBaMOCYz2siG4uMYGEzutie2%2BjDHGMptTTmtN0EcKwczNaCjVHxEOrzVANMRghKMFwPqXBaI0FoGLCWUtwZKzltrMpKs1Yay1rHHW6S9YGyNqjU25tLbWzqbbVOWw8r4EJA4PAbse4mNUF7EE2s/Z1FRkHEOctw49KZoqGO1V46J0wMnO2Rg06gFkXwbOChc750LsXOpVjy4A1sbIauYM8pOPrunIeVhm4zLbsQzuDQe59wIAPJIwpHkjzHvECeryAH3wGc4CArhP6WRXuUE%2Begt4NGhWkA%2BDRf6LDvj0S%2BH8b572nuCx%2BcwX7wrPjivIeLv7PzhX/EBqx1jAMwcwjxEjOCBO0Vk4AYSjGeggCgj6sTMFMxwaQPBBCRjEKank2iAdWHsICCifqAQ%2BpmGVWYAybVhG9XEeDSRthpEJLkfABRu1sapOScQdRWwWgsDuiwBQWpMxahySifs4w3r4A%2BuY76shrEXKBvIexNydAgBSC4%2BGsd3Eox1RjJROM8aqFtfax1zrXWcipuk6J8RYlJHiRnda7MM1czNYW2m2pkCpFSG6J1fU3SprdAm2xot4jFOlrLFWFS22q3Vi7bWutGD60NsbXpmAzYWzEB06qXStkLNIH0meQyPajOQN7CZggpmB2DqHfk8zI5LO1qsjI6yU5bPCDslmeymA5zzgXIuOVqpnP%2BhIS5wNA21xDfc4wTcbAvPgB3Lu2ZODbH7o3YelhR5QPHuYyexDz4Erngvcly957orfoi7IyK0OlGJTSzFD8r5tFxV/MFDR8ModPu/foyLKVkdpYA%2BlANI3atmqyhtNw7UOtLCmuE4xkEerQfTQVMiWa4PwYQygoDZUhs4ZqyqZg5NcDahoAySqmNQM4FI5awrSFJEMfwgINCkgBCU5VHqzCkhRuY/NIT9VmGvVU14oVsiVjx0yM4SQQA%3D)

## Links

- [Example](../../../code/facilities/concepts/pagelivore/falsify/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/concepts/falsify.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/falsify.test.hpp)
