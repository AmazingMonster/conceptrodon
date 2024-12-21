<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreBoundedByOpenInterval`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-bounded-by-open-interval">To Index</a></p>

## Description

`Varybivore::AreBoundedByOpenInterval` accepts two variables, indicating an open interval, and returns a predicate.
When invoked, the predicate returns true if all the arguments are within the open interval;
otherwise, the predicate returns false.

<pre><code>   Min, Max
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Min &lt; V<sub>0</sub> &lt; Max) && (Min &lt; V<sub>1</sub> &lt; Max) && ... && (Min &lt; V<sub>n</sub> &lt; Max)</code></pre>

## Type Signature

```Haskell
AreBoundedByOpenInterval
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct AreBoundedByOpenInterval
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
// Create a open interval (1, 4).
template<auto...Args>
using Metafunction
= AreBoundedByOpenInterval<1, 4>
::Page<Args...>;

static_assert(Metafunction<2, 3>::value);
static_assert(! Metafunction<1, 2, 3>::value);
static_assert(! Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<2, 3, -1>::value);
```

## Implementation

We will implement `AreBoundedByOpenInterval` using only `<`, meaning <code>Variable &in; (Lower, Upper)</code> is expressed as:

```C++
(Lower < Variable) && (Variable < Upper)
```

Here's the entire implementation:

```C++
template<auto Lower, auto Upper>
struct AreBoundedByOpenInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(Lower < Variables && Variables < Upper)) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(Lower < Variables && Variables < Upper)) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQAcpK4AMngMmAByPgBGmMQgAMyJpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmiW5MXkQA1CGoAO7xpOenF3KpqfFH2CYaAILjxF4O5y%2BxEwFjWDCw6AsAE8APKvBgASUE8QAbmJPl8TAB2Kzfc74847PYHTBHE5nVAAOmpADUWngmDF6Ap3hiCedfv8COdlMRUERlExgKS8QTsbivuz2bNHMhzmgGONMKpUsRzjFUJ5zmjvCLJVL8eLzhBqZTzAA2C0QK63NVk8504gMpmYBTnC0Wh30xnM93Hc7PV7EJZLd1YgAiRwl7OxkcSErZBKJ%2ByYh2Ojyp1K%2BwGBu0YBBZiQ%2BovxXkyRh5QswfvDPL5AqrZOzubYggUptZ8YxifxyZJZIzpsdzuZrJLHOasvlAiVKrVGq1guFAH0Ue7x0aTdSPWZzdabvE/W4vU6fa73bvPcOz277YH4iGw3GExGo93vgB6ABUP9/f4/GLfj%2BAAq2BCMBv4AZ%2Bf4wV%2BUGYp%2BH7nG4wKptWTDnKg8LnOEOzEDqxpcPckhLGa3x9mhA4UqaQLAIWxZfGW4TAOcACymDNFQXgMA42TdoktZAiCYIQtCcKMEieE6mSRHnJIY5fCAIBLqSxy0e225Fm%2B3wYjKeDIMuTAKEorQQOxnHcbxAhkmY9yJO8Sk6l4mBLNpPyTvphnGfEBAQGAYBsRxTBcTxDQyfctnnPZRaOWIzmuV23x6QZRkmb5/mBRZoV8cckUpHJDkgE5LluclXlpX5AXmcFllhccsl5cRhXFQlEplalPmVZlNXZdZuV2fcAC0XDNXFJXxhwKy0JwACsvB%2BBwWikKgnBuNY1gcmsGzVuYiQ8KQBCaJNKwANYgDNZiUliZiBAEM0aAAnBdGjmgEKTTRwki8CwEgaBopALUtK0cLwCggP9h2LZNpBwLAMCICAawEKkZzkJQaB7HQ8SRKwWyqAE5qDeakjnMAyBylIlJmLwmD4EQTroHo/CCCIYjsFIMiCIoKjqFDpC6ER1zEEwqScDwU2zfNR3LZwMJnCj3KoFQ5z44TxOk%2BT5yU2YxoeJj9B2mYe1LLwkNaCsEBIBjqRY2QFAQNbtsgMAUi2TQtB4WDEAxNLMThC0UJi7wfvMMQsIxNomAOEHpAY62BAwgwtCB3zWAxF4wAnLQtBg9wvBYCwhjAOIqd4MCvEoq60vKlHZxbPtuF1NLtB4DEwthx4WDSwQTo/XnpCV8QGpKOGuxFy3RhHSsVAGHRNJ4Jg1ziQt%2B3M8IojiBza/c2o0sC/oRcoOtlj6K3YOQCsWENLng3jOgRzhqYljWGYQODwzVcX90UcNC44JTH4IioRwhDEqCMIiRQsgCAAXoSBDR5jDASEROwP9egTDaJ4DoegUFWUaOghBYCkG2HQTA5B%2BCQELHASsBQW1NgSAlhwOaANpbAxVgTImJMyYU0kFTY0uBCAkAvMbU2U8VgIEwEwLACQICnX8IkSkD1EhYkkBoSQN1zR/RmuaB6%2BhOBfVID9PalJzRcFeg9AIpiZqSC4DNRR5pmF82BqDcGB0p4w3hpbRG8tUb20dgbHGbBOAtBYCiLEg0MLIAMBWLgD1KRcEpEtWmAiGZM1kKzTe0ht5KF3nzXQtkhYiyDgwphgNeDAzlsjM4mFlbBNCeE%2BUUSWIxLiQk3WqB9aHl2mYE2rioYWytu0m2Bs0YO0GU7WpYTIlFxiVwf67tPaUB9nzEOAcY4rLDjCCOP8Y5x3zInZO0s04ZyzjnGOBdx5bCWvgcujhK650SaoWuOwY6Nw%2BktFubcA6d0uabXuMdB7D0wKPQuRgJ6gD6XwWeCh56L2XjHNe6T2aZNkDvXmS08kH0nk/KwJ8PnnxkctVI19OC3wIPfAS2KX5v3iB/fF1C6ioOcBAVwpDgjggIYsCBGQoE5EwfkLlxRsgcvAd/XBfRJh8sAaKho4qBgUMQdgkhkrFVzHlYQ%2Bhqx1h0K4MUqWjjOAPGICEsJETGla1ifEjQfC6aCN2jqkRfSxESKkZQBh%2BjDGxNUViWxWIsSJDUZIYmRFSkyxBrYFxZtoawwRkjBWIy/HY1xkEo16sWAKBRHKFEzSSTjBpjalJREEUbyRZzeQ2S0U6CSKQApos866ocUDWW3jFY1JTSTNNGbtTZrQuMNpHTDbJB6ZG/pKAxnDN8WOkYGaXirhicuHNBBDJtr4HQBZ3tfb%2BzDmszd4dI7R37rswQ%2ByU5XMwOnTOYhTn93OaCn5pBrmoLudXR5yA64vORG83gHz25Qm%2Bd3P5/cAUZCBWPUFzE3EzyFNCheS94TwrScWiQyKublr3lWxpR9n64rPvAS%2BRLsi5w/HfTDOKLCvzKe/PAWA6XSuyH/dwyqgHsrVZytI3KGisrgUKljIqcEyqVXkKVfG0GqvKAqsh/RWWzFaMKpB1DaHs3rSG1hwTU3pszd2nYvaID8PpkI%2B1vTzZOskSMAlH13UgDMLE5IM17rWL%2BskLEr0G1lM4M4iGojSBnUkFiKm3quBSAel6xRXAsS6I4IkPVjaw3DoYdTFzoaHVGYHvETIzhJBAA)

## Links

- [source code](../../../../conceptrodon/varybivore/are_bounded_by_open_interval.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/are_bounded_by_open_interval.test.hpp)
