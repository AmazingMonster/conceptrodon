<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreDistinct`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-distinct">To Index</a></p>

## Description

`Varybivore::AreDistinct` accepts a list of variables. It returns true if no two variables in the list are the same and returns false if otherwise.

<pre><code>Variables... -> AreDistinct ? true : false</code></pre>

## Type Signature

```Haskell
AreDistinct :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct AreDistinct
{
    static constexpr bool value 
    {RESULT};
};
```

## Examples

We will check if `0, 1, 2, 3` are distinct. Then, we will append `1` and check again.

```C++
static_assert(AreDistinct<0, 1, 2, 3>::value);
static_assert(! AreDistinct<0, 1, 2, 3, 1>::value);
```

## Implementation

We will use a technique called SFINAE, which stands for 'substitution failure is not an error.'
It roughly means we will create an 'if statement' for template instantiation, where the condition will be the legitimacy of an action.

In this case, the action we will be using is accessing a function in an overload set.
The compiler will select different partial template specializations depending on if it can find the requested function.

We will use `Label` to create an overload set for `lark`.
We add a second parameter in the template head to distinguish identical elements.
This is essential since inheriting the same class multiple times is an error.
Unfortunately, using this error for SFINAE is impossible based on my testing.

```C++
template<typename Treasure, size_t I>
struct Label
{ static constexpr void lark(Treasure); };
```

To instantiate `Label` with variables, we need a helper class that transforms variables into types.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Then, given a `Variable` and an index `I`, we will instantiate `Label` as follows:

```C++
Label<Vay<Variable>, I>
```

Here's the entire implementation:

```C++
template<auto...Variables>
struct AreDistinct
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set through inheritance.
    : public Label<Vay<Variables>, I>...
    {
        // We bring every `lark` from its base class
        // to the current scope.
        using Label<Vay<Variables>, I>::lark...;

        // We will do SFINAE on the second parameter.
        // The default argument `void` ensures
        // the compiler checks the specialization
        // before the primary template.
        template<auto, typename=void>
        struct Hidden
        { static constexpr bool value {false}; };

        // This function checks if a variable
        // is in the previously provided list.
        // We ask the compiler to find a `lark` that
        // declares a parameter of type `Vay<Variable>`.
        // If the compiler finds the `lark,`
        // this specialization will be used.
        // Otherwise, the primary template will be used.
        template<auto Variable>
        struct Hidden<Variable, decltype(lark(std::declval<Vay<Variable>>()))>
        { static constexpr bool value {true}; };

        // We check every variable using a fold expression.
        // It returns true if and only if each variable
        // appears only once in the list.
        static constexpr bool value
        {(...&&Hidden<Variables>::value)};
    };

    static constexpr bool value
    {Detail<std::make_index_sequence<sizeof...(Variables)>>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAArAmkAA6oCoRODB7evnppGY4CoeFRLLHxXGa2mPZFDEIETMQEOT5%2BgXaYDlmNzQQlkTFxickKTS1teVy2EwNhQ%2BUjVQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACeZ9gmGgCCewdHmKfnyOPoWFT3jxezwImBYKQMILObgINxSjFYH2w9DYglIxwyAC9MAB9AjHACSAOe42IXgcx2CTFitEBJgA7BZ0U1HMhjmgGONMKoUsRjgA3VB4dDHAzEADWECRoMYBBWZ0Z9IAIvLacDQeCmJDzkxLqhjgA1Zp4Kn0IlPElkvEAWQEqCIDDuz3pjPGmrwrPZnO5vJ1RH5Yi8H2dhuIxuiprpyv8CsjKqdarBEMwUN9qAAdBmQ2H6AozRbyU9iJhFXhxgcCLSGYDjjXjiDE5rk%2BcYXDmGwzbWmaTyYrME06Kcq7Ho6qnp36xqtW5MTiCBm04T/A9np383je/2aecfiAQGEsKpsUoAI6BhjbKH4%2BcApfV2sAenvxwA6h9kEXG8dDMdUHy4rRUCYYUlDxAgEGIDZgAQY4wgQOJCEMbY0zvGsQGOFIvHDd0KSpWooRtBg7QEO5zizE1MFzJc0UXbBrxXWtnRQztjkfF8PmiUMjGOTA/2IG5TgANg0UUxRMITjioCCWBgggFGOaImCUNkDAUXN6OYlinz9MC302ItBHRNA4WQ9TmK8DIuMpal8Nte0SLcMjwwo%2B5qPuXcROvEd4zHDTNLY44AHc6FoY50D1IQADF8QiJ5sB/Bg6zg9FugEYUUmaBEQWIEyfI01iABUkr%2BHVaDxZpgB8GVBI0AUhTEjRuI5TZnNMztWJ0tlUDBOg4jZODkDFOSOoUOFkGNa4MTdAQmLap9Yn4ItEo%2BHk8BYZp%2BInJMct8ut1STFNdTRFt4XbfxFVq9AO18tdjgACSFLAGBmhiGSZN0PQEL0eXk1BPH9bwgwZKgxCUJV5UHKMrG8naCoQUsJK8c96j67pBpgqgv39UNyOemtWPhsIlvQos%2BScczaH4nlfyFTBhWucZtt81jXy/BQxSJtBuvoXk/RoBhhSYaqRPqxLNVxvysEOZoKMx9LiEy3rUAx47qoIoiHShRzTVvITGbyp98WVpLOZSHreT59AhqS%2BqRNIerxfauG5JG7pxrwSbkaC2gQtiY5zNpvXmNYgB5HTiCCpQjqSla1r43aGxBQLgvkj5/fQQPxz2xsDr9LWm2XXLmJu%2B7fkYTWjXItFJdK2FMAgESIB3EBq75MQbMIuzy%2Bxpyb2wCAVgHq6NOdN6WU6jkQW9H6/tbgHBwsAhSWTYcY0h0cYafFnkH69meLifjW%2B7%2Bg/Ys4BMf4WhhS5HkKIyAQM4fA28SLAhNg5Osl/Rr9%2Bfiimv8wJg28sbZmTK1R%2BX4UhwmaHJAQf8BDbBgglDq9M5zi1dGPT0k9vrRF%2BiFWegZxbOggNeMwAlzACRLo9LuIDKLYF3PgzAcoV5MTBl5IEhd0HYUwdfXkOCZ4BlAYXZ0G4mB0ChE3NaYocT7i5EeTAp5GAXm3O7TASt5wQDzgoOUt4lz0IEawqGLxmHeXvAAKnMRYyx95ARmPMflbAQh8oWOsc8WxlirGjleOed4nw3Dsm2CkWSZpAScOQNiRSSgWgQELMWUsjgkZQg0GiGYxxqjHH8G5EADDtGGNCeE1ScQCAQDAGAY4MSSxlgSecJJxwUlpMCLUzJ2T5QcDWLQTgCReB%2BA4FoUgqBOBuGsNYdEGwthBjMP4HgpACCaFaWsMUIABL%2BDTAADhWXSDQAkEgaA0P4MwKyzAAE5Dn6E4JIXgLAJA7NIN03p/SOC8AUCAJJMyemtNIHAWAMBEAgA2AQDCBByCUBNmbCICJOCqBWQJAAtAJSQxxgDIFZFINMZheC00ICQIUeh%2BCCBEGIdgUgZCCEUCodQbzSC6BmAFeWKROA8DaR0rpsy%2BmcGDpcAFP4MaQphXChFSLamSFRccCAHgua9T2FwFYvBXlaDWBAJAILuZAogEqkYwApDVBoKVOITyIDRBZdEMI616W8CNcwPiwdojaG6K8qZnMUQEGDgwCmLKsDRC8MANwYhaBPO4LwLAa0jDiApfgIsPQ/x%2Bt6VybolwdhTLCCCdpFLrgcXWh4LALLF6rVNaQXiOClC9iDcAa4RhZlrCoAYYACh9R4EwAFYOrZc24uEKIcQRKW2krUCyql%2BhDDGCGZYfQeBohPMgGsVAgSsh%2BuhT8M4ipTCWGsGYO5vFQxYDHf3GodQsguH5lMPwMwQgLDKBUfI6RMgCAPeewoWRBinuWNu21vQ5jXpmF0HoAg%2BgtHvcMSosx%2BhvoAz%2Bk9f6JBrAUKM7Y4HTkcE6Tcll9zjg8thfCxFyKhVmBFbgTFvJJXSumeWtYcEgIjC3QsyQyzDn%2BDpJIDQkgzCSCEhoBIAkTnJvOaQS5ky0wCS4AJFZhyVn8YSJILgCRqMCQQxS%2B5jznmEbefK75CrfkcsuCqtVxAwVsE4M0FgfI6TQsFlLLiXBDlpi4GmaN%2BAiDrpxbIfF7bpCdqUN2iluhqg0qYHS/1jK4PMpk2ytTeIlZfmIPpwzxmDCmfM5Zhqoquqm25qcCZZgCOyveSpzTGnEtmxAHpgz0KTMasOVwJJ2qsp6oNRS81Jr/WkFq5a61trc0OplM611obMAeq9T6v1UzA39pDb0sNz7I0spjcgONubE21BZam%2BWfEM07F6dmy59X83pGLKCIbYRQCKb4FWmtdaG1Nvqy2xzhLnOyC7eS3pHm%2B1lsXVYIdqbN0TqnZ9Tgs6CCXTOs95dq64jroovACDtRn3OAgK4IDx7ShgZmAUS92RPDtBvcj39Sx/0fvqN%2B1oqPphPs/Q0OYmOz3vtfQTw9wH5jw6xzByDmxoNStg/B25vAkMFci8pfttTYtWewzZkgKXJnpaI6QEjWB4hbo4xcgI5n6N0gk3SOk/gGNMbE9Ju5nA5MvPLR85TSA/kApy%2BKrT4KOB6b5SwBQfJWR8jM2mJM4x0VC7szMC7barvEvkK5u7OgAikC8z5hlrOAva44Oy/5lwuVhZYNb239vHfO7xAls3Iv/Bi4O1l3LyqKCqtzyMO3kDsQO8OdiFP4Twtwr4HQSrlBqu9MazcXNzerU2ocK1rqjqOst66z1713t%2BsBp28GlbAa8DhscONilk3pv1dm8m3pC300YHH9M0M62pmbcLaPkte39eVqYNW2t9bG2MGbQ5r3Ehrskr9z2wP0WB1LteyO97fTPsck4PeHcAPLAro5zXRpnfxx13Wh33Spz0Dh0WHJ1SAvXqCAyR3qDJ0fVAK/Up1yGpzQJJ36BQOxwwLRwp1wNA3pxZ0ZzGRg2TTZ0Q04DjwTzt35GT0bHGEF1wxFylRlXF0lzIz8040uSOTTH8H8CSHozK12RowEy1w5x11sHkwywHlIAWX8AEgsyqGo0kGOQEjpC4A2RmGTX8HD2kIeQUzlT8zRSkNZWMPkLWF4jvj8EkCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/are_distinct.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/are_distinct.test.hpp)
