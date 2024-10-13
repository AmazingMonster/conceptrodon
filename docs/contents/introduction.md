<table>
    <thead>
        <tr>
            <th>Vocabulary</th>
            <th>Meaning</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>metafunction</td>
            <td>A template is a metafunction if it is a class template or an alias template</td>
        </tr>
        <tr>
            <td>signature</td>
            <td>
                A signature is:
                <ul>
                    <li><code>typename</code> for a type;
                    <li><code>auto</code> for a value;
                    <li>the template-head for a template
                </ul>
        </tr>
        <tr>
            <td>conformed</td>
            <td>
                A metafunction is conformed if one of the following is true
                <ul>
                    <li>It is a class template whose parameter list only consists of type template parameters(<code>typename</code>);
                    <li>It is a class template whose parameter list only consists of non-type template parameters(<code>auto</code>);
                    <li>It is a class template whose parameter list only consists of conformed metafunctions
                </ul>
            </td>
        </tr>
        <tr>
            <td>function</td>
            <td>conformed metafunction</td>
        </tr>
        <tr>
            <td>category</td>
            <td>Let M be the set of all functions, define &sim; as follows: &forall; (x, y) &isin; M, x &sim; y &iff; x and y have the same signature. Then a category is an equivalence class in M under &sim;</td>
        </tr>
    </tbody>
</table>
