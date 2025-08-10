# DAY 1 : Patching simple - Remplacement de JE par JNE

## Introduction

Le **patching** est une technique permettant de modifier directement le code machine d’un programme binaire afin de changer son comportement. Cela peut permettre, par exemple, de contourner une vérification de licence ou un contrôle d’accès.

L’objectif de cet exercice est de démontrer un patching simple consistant à remplacer une instruction assembleur `JE` (Jump if Equal) par son inverse `JNE` (Jump if Not Equal). Cette modification inverse la condition d’un saut conditionnel, ce qui peut permettre de contourner un contrôle dans un programme.

---

## Contexte

Dans un programme compilé, un saut conditionnel `JE` permet au processeur de sauter à une autre partie du code uniquement si la condition "égalité" est vraie. En modifiant ce saut en `JNE`, le programme sautera si la condition "égalité" est fausse, modifiant ainsi la logique du programme.

---

## Exemple concret

Supposons un programme simple qui vérifie si un mot de passe est correct en comparant une valeur :

```asm
; Extrait en assembleur x86 (simplifié)
cmp eax, 0x1234      ; Comparaison de eax avec la valeur 0x1234
je valid_password    ; Saut vers valid_password si égal
jmp exit             ; Sinon, quitter


Instruction JE (opcode 0x74)

Signifie : "si égal, sauter à `valid_password`".

En remplaçant `JE` par `JNE` (opcode `0x75`), on inverse la condition.

---

Étapes du patching

1. Identifier l’adresse de l’instruction `JE` dans le binaire.  
2. Ouvrir le binaire dans un éditeur hexadécimal.  
3. Remplacer l’opcode `0x74` par `0x75` à l’adresse identifiée.  
4. Sauvegarder et exécuter le binaire patché.

---

Effet du patch

Après modification, le programme sautera vers la section `valid_password` uniquement si la comparaison est fausse, ce qui inverse la logique et permet d’outrepasser la vérification initiale.

---

Remarques

- Cette méthode est simple et efficace sur des programmes avec une logique linéaire.  
- Sur des programmes plus complexes, il peut être nécessaire d’analyser plus en profondeur et de patcher plusieurs endroits.  
- Le patching doit être effectué avec précaution pour éviter de corrompre le binaire.

---

Outils recommandés

- `hexedit`, `ht` ou tout autre éditeur hexadécimal.  
- `objdump` ou `BinaryNinja`  pour analyser les binaires.  

---

Conclusion

Le patching par remplacement d’un saut conditionnel est une des techniques fondamentales du cracking. Ce premier exemple illustre comment un simple changement d’opcode peut modifier significativement le comportement d’un programme.
