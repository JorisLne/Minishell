<p align="center">
  <img 
    src="https://github.com/JorisLne/42-project-badges/blob/main/covers/cover-minishell-bonus.png?raw=true" 
    alt="Bannière minishell" 
    width="80%">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Score-125%2F100-brightgreen?style=flat-square" alt="Score du projet 125/100" />
  <img src="https://img.shields.io/badge/Langage-C-blue.svg?style=flat-square&logo=c" alt="Langage C" />
</p>

<p align="center">
  <img src="https://github.com/JorisLne/42-project-badges/blob/main/badges/minishellm.png?raw=true" alt="Badge minishell">
</p>


## 🧩 Overview

**Minishell** est un projet qui consiste à recréer un **shell UNIX minimaliste** en C.  
Le but est de comprendre le fonctionnement interne d’un interpréteur de commandes, 
en manipulant les processus, la mémoire, les signaux, et les variables d’environnement.

> - Gestion de processus (`fork`, `execve`, `pipe`, `wait`)
> - Parsing lexical & syntaxique
> - Gestion de la mémoire
> - Signaux (CTRL+C, CTRL+D…)
> - Redirections et pipes
> - Implémentation d'un environnement interactif

-- 

## 🎯 Objectif

Créer un shell fonctionnel capable d'exécuter des commandes avec :
- Redirections (`>`, `<`, `>>`, `<<`)
- Pipes (`|`)
- Variables d’environnement (`$PATH`, `$USER`, etc.)
- Signaux (`SIGINT`, `SIGQUIT`)
- Builtins (cd, echo, env…)

---

## 🚀 Features

✅ Lecture de commandes avec `readline`  
✅ Parsing avec gestion des quotes `"`, `'`  
✅ Redirections : `>`, `>>`, `<`, `<<`  
✅ Pipes multiples : `ls | grep txt | wc -l`  
✅ Variables d’environnement : `echo $HOME`  
✅ Exécution de commandes binaires et builtins  
✅ Gestion fine des signaux et erreurs
✅ Gestion du heredoc

---

## 🛠️ Installation

### Prérequis :
- Système UNIX/Linux
- `make` et compilateur `gcc`
- Bibliothèque `readline` installée

### Compilation :

```bash
git clone https://github.com/votre-repo/minishell.git
cd minishell
make
```

---


## 🧠 Architecture du Shell

```text
+------------------+
|  Saisie utilisateur
+------------------+
         ↓
+------------------+
|      Parsing      | <-- Gestion quotes, tokens, expansions
+------------------+
         ↓
+------------------+
|   Execution Tree  |
| (redirections, pipes)
+------------------+
         ↓
+------------------+
|   Exécution (fork/exec)
+------------------+
```

---

## 🔧 Builtins Implémentés

| Commande | Description                  |
|----------|------------------------------|
| `echo`   | Affiche du texte             |
| `cd`     | Change de répertoire         |
| `pwd`    | Affiche le répertoire courant|
| `export` | Définit une variable env     |
| `unset`  | Supprime une variable env    |
| `env`    | Affiche les variables env    |
| `exit`   | Quitte le shell              |

---



## 🌳 Parsing en AST (Arbre Syntaxique Abstrait)

L'un des composants les plus complexes du projet est le **parser**, qui transforme une ligne de commande en une structure exploitable par le shell : l'**AST** (*Abstract Syntax Tree*).

### 🧠 Qu'est-ce qu'un AST ?

Un **arbre syntaxique abstrait** représente la hiérarchie logique d’une commande.  
Chaque **nœud** contient un opérateur (`|`, `>`, `>>`, `<<`, `&&`, `||`, etc.) ou une commande, et les **branches** représentent les sous-commandes à exécuter.

---

### 🧱 Exemple : Commande simple

Commande utilisateur :

```bash
echo Hello | grep H > out.txt
```

Représentation sous forme d’AST :

```
           [>]
          /   \
      [|]     "out.txt"
     /   \
"echo"  "grep H"
```

---

### 🏗️ Étapes du parsing

1. **Tokenisation** :
   - Découper l’entrée (`readline`) en **tokens** : mots, opérateurs, redirections.
   - Gérer les **quotes**, les **espaces**, les **variables** (`$VAR`).

2. **Construction de l’arbre (AST)** :
   - Prioriser les opérateurs (pipes > redirections)
   - Créer récursivement un **nœud parent** pour chaque opérateur trouvé
   - Attacher les **commandes** à gauche et/ou à droite

3. **Exécution récursive** :
   - L’exécuteur visite l’AST de façon **postfixée**
   - Chaque nœud est évalué en respectant les règles des redirections et des pipes

---

### 🔄 Avantages de l’AST

✅ Représente fidèlement la logique des commandes complexes  
✅ Permet une exécution ordonnée, même avec des pipelines imbriqués  
✅ Simplifie l’implémentation des redirections et des opérateurs logiques  

---

### 📂 Fichiers concernés

- `parser.c`, `parser_bis.c` – Analyse lexicale et gestion des priorités
- `ast_builder.c` – Création des nœuds et liaison récursive
