<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# Vocabulary

When I choose a technical expression to use in the documentation, I first attempt to keep it close to the relevant C++ terminologies since they are well-documented and familiar to programmers.
However, C++ terms can be confusing. For example, it is unclear what the 'non-type' in the 'non-type template parameter' refers to, as it looks like the complement of all 'type template parameters'.
Moreover, the term 'template template parameter' not only repeats the same word twice like a typo but also erases the differences between the parameter lists within template template parameters.
The detection of the differences, however, is the key part of this library.

As a result, some vocabulary used in the documentation will have meanings unique to this library.
The goal is to maintain the usual flow of written English while providing insights through the selection of words.
Strict definitions for conventional programming terms have little practical use.
They are there for the convenience of authors who try to be as accurate as possible.
Understanding these terms shall not be a burden for the readers or users, as these terms shall be used intuitively and conventionally.
This is what I want to achieve.

## Template-head

The term 'template-head' is introduced by the standard.
It is easier to explain the word by an example.

<pre><code>template ---------------------------------------------------+
<                                                           |
    template&lt;typename...&gt; ------> template-head       template-head
    class ----------------------> type-parameter-key        |
    ...                                                     |
    Args -----------------------> identifier                |
> ----------------------------------------------------------+
struct Vehicle;</code></pre>

This library often uses the term without the hyphen.
This is to make my grammar checker happy.

## Metafunction && Function

In C++, the word 'metafunction' does not have a decisive definition and often acts as a synonym for 'template'.
In this library, the word represents a class template or an alias template, as these are the only kinds of templates acceptable as template arguments in C++20.

The goal is to define the kind of metafunctions this library focuses on.
To start with, we will categorize metafunctions by their primary signatures, where a primary signature is defined as follows:

> A primary signature is:
>
> - `typename` for a type;
> - `auto` for a value;
> - the template head for a template.

Namely, primary signatures extend the notion of template heads by two special cases.
Now, we will define the 'conformed signatures' using recursion.
The two cases added earlier will serve as the base cases for the definition.

> A primary signature is conformed if one of the following is true:
>
> - It is `typename` or `auto`.
> - It is a template head whose parameter list only consists of conformed primary signatures.

With all the preparations done, we can finally define the 'conformed metafunctions', which are the focal point of this library.

> A metafunction is conformed if its primary signature is conformed.

The word 'function' is a shorthand for 'conformed metafunction'.
Note that it differs from the ordinary use case of the word, which generally means a named block in C++.
I adopted this abbreviation for several reasons:

- Most metafunctions discussed in the documentation are conformed, which means repeating the quantifier is often redundant and distracting.
- The term 'metafunction' already indicates the function-like behavior of templates. It is more natural to relate the word 'function' to a template in a metaprogramming library rather than a named block in the usual sense.
- Only a few ordinary functions are mentioned in the documentation. When it appears, the term 'ordinary function' is used for differentiation.

> A Submetafunction of a metafunction is one of the following:
>
> - a class member template or
> - an alias member template or
> - a class member template of a submetafunction of the metafunction or
> - an alias template of a submetafunction of the metafunction.

The term 'thoroughly conformed metafunction' is used when every submetafunction of a conformed metafunction is required to be conformed.

## Operation && Vessel

Both words are synonyms for conformed metafunctions.
The term 'operation' is selected when the function's (often unspecified) functionality is the focus.
Meanwhile, the term 'vessel' is selected when the function is only used for holding its arguments from an instantiation.

The arguments held by a vessel are denoted as 'items'.

```C++
Vessel<Items...> // General representation of a vessel holding the items.
```

## Container && Sequence

'Containers' and 'sequences' are special vessels.
The term 'container' is selected when the template holds types exclusively, meaning its primary signature is `template<typename...>`.
The term 'sequence' is selected when the template holds values exclusively, meaning its primary signature is `template<auto...>`.

## Element && Variable

The term 'element' denotes a type in a container.
The term 'variable' denotes a value in a sequence.
Honestly, I would like to write 'type' instead of 'element' and 'value' instead of 'variable'.
However, 'type' and 'value' are conventional names for type traits.
To avoid possible confusion, I adopted the lengthier ones.

The word 'variable' is inaccurate as nothing varies for a non-type argument.
Other words like 'datum' and 'member' are considered.
'Datum' is rejected since its plural form is irregular, a significant setback as it prohibits Find-and-Relace.
I prefer 'member' over 'variable' since the former often denotes an element in math.
Yet again, the word 'member' already has an established meaning in programming.
It commonly refers to a component of a class.
Therefore, I rejected the word to avoid creating a mess.
While 'variable' is inaccurate, I doubt this inaccuracy will become the source of confusion, and its resemblance to the word 'value' also gives it an edge.

## Layer && Invocation Order

An illustration might help in understanding the term 'layer'.

<pre><code>template<...> ---------------------------------------------+
Metafunction                                               |
{                                                      0th Layer
    template<...> -----------------------------------+     |
    NestedMetafunction                               |     |
    {                                            1st Layer |
        template<...> -------------------------+     |     |
        NestedMetafunction                     |     |     |
        {                                  2nd Layer |     |
                  ...                          |     |     |
            template<...> ---------------+     |     |     |
            NestedMetafunction      Last Layer |     |     |
            {}; -------------------------+     |     |     |
                  ...                          |     |     |
        }; ------------------------------------+     |     |
    }; ----------------------------------------------+     |
}; --------------------------------------------------------+</code></pre>

Essentially, each layer is a submetafunction, except the *0*th one.
A layer's number suggests its position in the outmost metafunction.
To invoke the (*n* + 1)th layer, the *n*th layer must be instantiated first.
Therefore, the *n*th layer is defined recursively, with the *0*th layer serving as the base case, which is directly invocable.

This is the explanation given to the `*n*th layer` when I first started working on the documentation.
Later, however, I realize it does not cover all the scenarios where I use this word.

In the description for `Flip` functions, I wrote:

> `Namespace::Flip` accepts an operation and flips its *0*th layer and *1*st layer.

How do we flip metafunctions?
The previous explanation won't make sense in this scenario.
To solve this, we need to abstract the notion further.
I introduce the term 'layer' to capture the sequential characteristic of submetafunctions.
But what has been sequenced?
The following illustration might help.

<pre><code><b>Metafunction</b>

template&lt;...Args<sub>0</sub>&gt; ------------------ Declare Args<sub>0</sub>...
Scope<sub>0</sub> { ---------------------------- Args<sub>0</sub>... are injected to the <i>0</i>th scope
    template&lt;...Args<sub>1</sub>&gt; -------------- Declare Args<sub>1</sub>...
    Scope<sub>1</sub> { ------------------------ Args<sub>1</sub>... are injected to the <i>1</i>st scope
        template&lt;...Args<sub>2</sub>&gt; ---------- Declare Args<sub>2</sub>...
        Scope<sub>2</sub> { -------------------- Args<sub>2</sub>... are injected to the <i>2</i>nd scope
                  ...
            template&lt;...Args<sub>Last</sub>&gt; ---- Declare Args<sub>Last</sub>...
            Scope<sub>Last</sub> { -------------- Args<sub>Last</sub>... are injected to the last scope
            };
        };
    };
};</code></pre>

After applying `Flip` to the metafunction, the illustration becomes the following.

<pre><code><b>Flip&lt;Metafunction&gt;::RESULT</b>

template&lt;...Args<sub>1</sub>&gt; ------------------ Declare Args<sub>1</sub>...
Scope<sub>0</sub> { ---------------------------- Args<sub>1</sub>... are injected to the <i>0</i>th scope
    template&lt;...Args<sub>0</sub>&gt; -------------- Declare Args<sub>0</sub>...
    Scope<sub>1</sub> { ------------------------ Args<sub>0</sub>... are injected to the <i>1</i>st scope
        template&lt;...Args<sub>2</sub>&gt; ---------- Declare Args<sub>2</sub>...
        Scope<sub>2</sub> { -------------------- Args<sub>2</sub>... are injected to the <i>2</i>nd scope
                  ...
            template&lt;...Args<sub>Last</sub>&gt; ---- Declare Args<sub>Last</sub>...
            Scope<sub>Last</sub> { -------------- Args<sub>Last</sub>... are injected to the last scope
            };
        };
    };
};</code></pre>

The order of scopes is defined naively.
It is an invariant for rearranged metafunctions.
What was flipped is the declaration order of the parameters.
Take `Plume`, `SensiblePlume`, and `CognatePlume` as examples:

<pre><code><b>Plume</b>

template&lt;typename...Elements&gt;
Scope<sub>0</sub> {
    template&lt;template&lt;typename...&gt; class...Cosmetics&gt;
    Scope<sub>1</sub> {
        template&lt;template&lt;typename...&gt; class Operation>&gt;
        Scope<sub>2</sub> {
        };
    };
};</code></pre>

<pre><code><b>SensiblePlume</b>

template&lt;typename...Elements&gt;
Scope<sub>0</sub> {
    template&lt;template&lt;typename...&gt; class Operation>&gt;
    Scope<sub>1</sub> {
        template&lt;template&lt;typename...&gt; class...Cosmetics&gt;
        Scope<sub>2</sub> {
        };
    };
};</code></pre>

<pre><code><b>CognatePlume</b>

template&lt;template&lt;typename...&gt; class Operation>&gt;
Scope<sub>0</sub> {
    template&lt;template&lt;typename...&gt; class...Cosmetics&gt;
    Scope<sub>1</sub> {
        template&lt;typename...Elements&gt;
        Scope<sub>2</sub> {
        };
    };
};</code></pre>

Each function contains three scopes.
The order of the scopes is invariant since it is defined by induction and only relies on the total number of scopes.
What separates these functions is the arrangement of `Elements...`, `Cosmetics...`, and `Operation`.

We will define the 'invocation order' first.

> The invocation order of a thoroughly conformed metafunction is a map from the function's canonically defined scopes to a set of parameter lists.

Finally, we will define the '*n*th layer'.

> The *n*th layer is the projection from the *n*th scope to the parameter list it maps to according to the invocation order.

Now, we can understand flipping the *0*th layer and the *1*st layer as an exchange of the projections' destinations.

## Summary

<dl>
  <dt>Conform metafunction</dt>
  <dd>
    A metafunction is conformed if its primary signature is conformed.
  </dd>

  <dt>Conform primary signature</dt>
  <dd>
    A primary signature is conformed if one of the following is true:
    <ul>
      <li>It is <code>typename</code> or <code>auto</code>.</li>
      <li>It is a template head whose parameter list only consists of conformed primary signatures.</li>
    </ul>
  </dd>

  <dt>Container</dt>
  <dd>A container is a vessel that holds types.</dd>

  <dt>Element</dt>
  <dd>Elements denote the arguments held by a container.</dd>

  <dt>Finally-returned function</dt>
  <dd>The finally-returned function of a thoroughly conformed metafunction is the submetafunction corresponding to the last layer.</dd>

  <dt>Function</dt>
  <dd>A function is a conformed metafunction.</dd>

  <dt>Item</dt>
  <dd>
    Items denote the arguments held by a vessel.
  </dd>

  <dt>Invocation order</dt>
  <dd>
    The invocation order of a thoroughly conformed metafunction is a map from the function's canonically defined scopes to a set of parameter lists.
  </dd>

  <dt>Layer</dt>
  <dd>
    The <i>n</i>th layer is the projection from the <i>n</i>th scope to the parameter list it maps to according to the invocation order.
  </dd>

  <dt>Metafunction</dt>
  <dd>A metafunction is a class template or an alias template.</dd>

  <dt>Operation</dt>
  <dd>An operation is a conformed metafunction. The term is used when the focus is on the functionality of the metafunction.</dd>

  <dt>Packed container</dt>
  <dd>A packed container is an instantiation of a container.</dd>

  <dt>Packed sequence</dt>
  <dd>A packed sequence is an instantiation of a sequence.</dd>

  <dt>Packed stockroom</dt>
  <dd>A packed stockroom is an instantiation of a stockroom.</dd>

  <dt>Packed warehouse</dt>
  <dd>A packed warehouse is an instantiation of a warehouse.</dd>

  <dt>Packed vessel</dt>
  <dd>A packed vessel is an instantiation of a vessel.</dd>

  <dt>Primary signature</dt>
  <dd>
    A primary signature is:
    <ul>
      <li><code>typename</code> for a type;</li>
      <li><code>auto</code> for a value;</li>
      <li>the template head for a template.</li>
    </ul>
  </dd>

  <dt>Primary signature category</dt>
  <dd>
    Let M be the set of all primary signatures, define &sim; as follows: &forall; (x, y) &isin; M, x &sim; y &iff; x and y have the same signature. Then a category is an equivalence class in M under &sim;.
  </dd>

  <dt>Thoroughly conformed metafunction</dt>
  <dd>A metafunction is thoroughly conformed if all of its submetafunctions are conformed.</dd>

  <dt>Type result</dt>
  <dd>The alias member <code>type</code> of an instantiated function.</dd>

  <dt>Sequence</dt>
  <dd>A sequence is a vessel that holds values.</dd>

  <dt>Stockroom</dt>
  <dd>A stockroom is a vessel that holds functions with the primary signature <code>template&lt;auto...&gt;</code>.</dd>

  <dt>Submetafunction</dt>
  <dd>A submetafunction of a metafunction is one of the following:
    <ul>
      <li>a class member template or</li>
      <li>an alias member template or</li>
      <li>a class member template of a submetafunction of the metafunction or</li>
      <li>an alias template of a submetafunction of the metafunction.</li>
    </ul>
  </dd>

  <dt>Value result</dt>
  <dd>The static constexpr data member <code>value</code> of an instantiated function.</dd>

  <dt>Variable</dt>
  <dd>Variables denote the arguments held by a sequence.</dd>

  <dt>Vessel</dt>
  <dd>
    A vessel is a conformed metafunction that is used for holding its arguments from an instantiation.
  </dd>

  <dt>Warehouse</dt>
  <dd>A warehouse is a vessel that holds functions with the primary signature <code>template&lt;typename...&gt;</code>.</dd>
</dl>
