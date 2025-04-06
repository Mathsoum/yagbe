---
layout: single
title: Mise en place du projet CPP avec Google Tests
date: 2025-04-06 10:30 +0200
---

## Initialisation du projet

En se basant sur https://github.com/kigster/cmake-project-template, j'ai initialisé un projet construit comme ça :
```
- cpp
  - src
    - yagbe-lib
      > Implémentation de l'émulateur
    > main.cpp pour l'émulateur
  - test
    - src
      > Implémentation des tests
    > main.cpp pour exécuter les tests
```

Tout le projet est construit comme un projet CMake avec des sous-projets pour chaque composants.  
Ainsi, l'implémentation de l'émulateur ne sera compilée qu'une seule fois puis utilisée par l'application principale ainsi que par les tests.

## Les premiers tests
J'ai initialisé un fichier TODO.txt qui permettra de suivre les cas de tests à implémenter. Ce fichier sera rempli au fur et à mesure des développements.

Le fichier TODO.txt initiallement créé ressemble à ça :
```
This file will serve as a TODO list for test cases to implement

Decompiler to parse ROMs and convert them to CPU instructions
Empty binary must work
Basic CPU instructions are handled
```

J'ai implémenté en premier un test qui valide le parsing d'une ROM vide et ait implémenter le code en suivant. Une API basique à laquelle on peut donner un tableau d'octets et qui retourne un tableau d'instructions CPU.

L'étape suivante sera de s'attaquer aux instructions elles-mêmes.  
J'ai ajouté un test à la TODO pour valider la lecture des instructions NOOP. L'implémentation du test est directe et l'implémentation du code validant le test est minimale.  
Pour l'instant, il est évident que le code n'est pas "prêt" à génrer toutes les instructions mais c'est justement le principe du TDD, avancer par petits pas.

Fichier decompiler.h
```cpp
#include <vector>

namespace Decompiler {

enum class Instruction {
    NOOP
};

std::vector<Instruction> decompile(const std::vector<std::byte>& rom_bytes);

}
```

Fichier decompiler.cpp
```cpp
#include "decompiler.h"

std::vector<Decompiler::Instruction> Decompiler::decompile(const std::vector<std::byte>& rom_bytes)
{
    if (!rom_bytes.empty())
        return {Decompiler::Instruction::NOOP};
    return {};
}
```

## Fun fact

Après avoir poussé le code à ce stade, j'ai vu sur Github la proportion des langages dans les fichiers sources.  
![languages_ratio](/yagbe/assets/images/languages_ratio.png)

J'ai trouvé la proportion de code CMake très importante par rapport à la proportion de code cpp.  
Cependant, avec l'avancement du projet, le code CMake ne devrait pas grossir énormément par rapport au code CPP qui lui va augmenter considérablement.

Un ratio intéressant sera de comparer les tailles de code entre les tests et l'implémentation de l'émulateur lui-même.  
l'approche TDD devrait normalement m'amener à un ratio plus grand pour le code des tests que le code de l'émulateur.