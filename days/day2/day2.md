# Day 2 — Bypass d'un Serial Check Basique

## Objectif
L'objectif de cet exercice est de bypasser la vérification d'un numéro de série (serial check) dans un exécutable. C'est presque la même chose que le day1 mais appliqué pour un cas un peu différent. 
Ainsi aujourd'hui nous allons analyser le programme, trouver l'endroit où il compare le serial entré par l'utilisateur avec la valeur attendue, et patcher le binaire pour qu'il accepte n'importe quelle valeur.

---

## Outils utilisés
- Ghidra (ou IDA Free) pour l'analyse statique
- x64dbg (ou OllyDbg) pour le débogage dynamique
- HxD (éditeur hexadécimal) pour appliquer le patch final

---

## Étapes de l'analyse et du patch

### 1. Localiser la vérification du serial
Ouvrir l'exécutable dans Ghidra et effectuer une recherche de chaînes de caractères (`Search -> For Strings`).  
Repérer le message affiché lorsque le serial est incorrect, par exemple "Invalid serial.".  
En double-cliquant sur cette chaîne, Ghidra affiche l'endroit du code où elle est utilisée. En remontant dans le flux d'exécution, on trouve la fonction qui effectue la comparaison du serial.

### 2. Comprendre la logique
La comparaison est souvent réalisée via la fonction `strcmp` ou équivalente.  
`strcmp` retourne :
- 0 si les chaînes sont identiques
- Une valeur différente de 0 si elles sont différentes

En assembleur, la vérification peut ressembler à ceci :

```asm
call strcmp
test eax, eax
jne invalid_label
```
Ici, `test eax, eax` met à jour les flags en fonction de la valeur de `eax`, puis `jne` (*jump if not equal*) saute vers la partie du code affichant **"Invalid serial."** si les chaînes sont différentes.

### 3. Modifier le flux de contrôle
Pour bypasser la vérification, il suffit d'empêcher le saut vers la partie **"Invalid serial."**.

Deux options courantes :

- **Inverser la condition** : remplacer `jne` par `je` (*jump if equal*).
- **Supprimer complètement le saut** : remplacer `jne` par deux instructions `NOP` (*No Operation*).

**En hexadécimal :**
- `jne` a souvent l'opcode `75` suivi d'un offset.
- `je` a l'opcode `74`.
- Un `NOP` est représenté par `90`.

---

### 4. Appliquer le patch
Ouvrir le binaire dans **HxD** :

1. Rechercher l'opcode `75` correspondant à la condition trouvée dans le debugger.
2. Remplacer :
   - Par `74` pour inverser le saut.
   - Ou par `90 90` pour supprimer le saut.
3. Sauvegarder le fichier modifié.


