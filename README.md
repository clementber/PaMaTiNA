# PaMaTiNA
Pattern Matching with Timed Nu-Automata.

In this repository you could fine different version of the project with different automata's model. This *read me* will explain how to dp the pattern matching with the currently most advanced model of the project.

## Description of the project


## Specification Langage

The patterns can be describe with the timed nu-expressions, wich is an extension of the regular expressions with primitives for describe time constraint and manage memory.
The timed nu-expressions are converted to timed nu-automate to perform the pattern mathing. So you have also the possibility to modelise your pattern directly with a corresponding automata.

### Timed nu-expression

Expression        | Description
------------------|------------
Alpha & num       | The words represents the constant and variables. The constants means that the same word should be gotten in input to be accepted. The varriable are associate with domain. The domains are initially empty. The variable accept an input only when it's present in his domain. But if the variable is allocated instead it add the input in it's domain, if it isn't already present in his domain, or an other variable's domain. The difference between a variable and a constant is that the variable is used with the symboles "\#" or "\!" but never the constant. We recommend to fully writte the variable in uppercase.
@                 | **(Not yet implemented)** The universal character. It mean that any character is accpeted in input.
( Expr )          | The parenthesys are used to precise the priority.
Expr . Expr       | The dot is de concatenation of two expressions. When the sub exoression on the left of the dot is matched you strart the search of the sub-expression on the right of the dot.
Expr \+           | The same plus as as the one used in regular expressions. He meant that the sub-expression on it left can be matched multiple time consecutively but should be found at least once
Expr \*           | As in the regular exprssion, the asterisk mean that the sub-expression preceding it can be match as many time as neeeded. 0 time if it doesn't appear.
Expr ?            | The question mark symbolise the optionality of the sub-expression preceding it. The expression may be match once or pass.
Expr \| Expr      | The *or* symbol, one of the two sub-expression should be match.
Expr & Expr       | The *and* symbol, both the sub-expression should be matched.
< Expr >\[x,y\]   | The delay constraint. The duration of the sub-expression should be included in \[x,y\].
\# c              | The *\#* is the symbol of the allocation. If it precede a *variable* c then c is allocated before the treatment of the input. When you treat an input with an allocated variable, the value in input should be added in the variable's domain. **Important** An input can't be put in a variable if any variable already contain it.
c \!              | The *\!* is the symbol of free. Writted after a *variable* c, it clear all the value contained in c after the input's treatment.
\# c \!           | This is a combination of the two precedent symboles. The *variable* c is allocated and after it's treatment c is cleared.
\#\{Vars\} Expr   | Right before the treatment of the sub-expression, all the variables contained in *Vars* are allocated.
Expr\{Vars\}\!    | Right after the sub-expression is matched, all the variables of *Vars* are cleared.
Expr % Expr       | The shuffle's symbole % is used to symbolize the recognition of two sub-expression simultaneously.
Expr \- Expr      | **(Not yet implemented)** The "-" is te symbole of the unbreakable concatenation. Associate with the symbole %, it break the parallelism when the first sub-expression is matched until the second sub-expression is matched.


**Vars** = c \| c, Vars 

### Create your own timed nu-automata

## Pattern Matching

To compile the application you need flex, bison and g++.

The application to do the pattern matching is compilable by calling successively the two makefile :
* ./hybride_no_interval/parser_regex2auto/Makefile
* ./hybride_no_interval/reconnaissance/Makefile

It will create two applications:
* RegexRecognizer expression_file input_file : Do the pattern matching with in verbose mode.
* RegexChecker expression_file input_file : Do the pattern matching printing only the finded instance and the progression.

If you want to see the automata generated by your expression you could call the makefile of ./hybride_no_interval/parser_regex2auto/Makefile with the target *test*. It'll create the application test.
This application need at least on parameter, the expression file. An optional second parameter could be put to redircet the output. The output is a dot file which can be use with graphviz to obtain a png of your automata.
The graphviz command ton convert the dot to a png is :

```
dot -Tpng -o <your_automata>.png <your_automata>.dot
```
