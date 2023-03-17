# cmpe230p1
## BNF 
```
<stmt> => <assignment> <comment>| <expr> <comment>| 
assignment => <var> = <expr>
<expr> => <expr> + <term> | <expr> - <term> | <term>
<term> => <term> * <factor> | term / <factor> | <operator>(<term>)
<operator> => xor(<var>, <var>) | ls(<var>, <factor>) 
| rs(<var>, <factor>) | lr(<var>, <factor>) | rr(<var>, <factor>) | not(<var>)
<var> => ?
<comment> => % (str) | " "
```

===================================================malyasin============================================================