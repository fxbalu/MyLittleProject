# My Little Project

My Little Project is game developped by five engineering students from __INSA de Rennes__ in France. It's a 2D sprite based platformer.

## Todo

- [ ] Add screenshots
- [ ] Create a simple Makefile
- [ ] Rewrite the project with SDL2
- [x] Stop deleting useful files (hopefully)

## Getting started

### Ubuntu

1. Install ```libsdl1.2-dev```, ```libsdl-image1.2-dev```, ```libsdl-mixer1.2-dev``` and ```libsdl-ttf2.0-dev``` on your system.
```
sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
```
2. Clone the repository.
```
git clone https://github.com/fxbalu/MyLittleProject
```
3. Create a new SDL project with Code::Blocks.
4. Add the ```src``` folder to your Code::Blocks project.
5. Add ```SDL```, ```SDLmain```, ```SDL_image```, ```SDL_mixer``` and ```SDL_ttf``` in __Project > Build options... > Linker settings > Link libraries__
6. Build and run the project (```F9```).

## How to contribute

### Syntax
- Indent your code with three space, and no tab
- No trailing whitespace. Blank lines should not have any space.

### Documentation
Use Doxygen syntax to comment your files, structures and functions.

Example:
```c
/**
 *  \brief Print arguments in standard output
 *  \param arg1       First argument
 *  \param bar        Second argument
 *  \param character  Starting character
void foo(int arg1, int bar, char character){
  // some code
}
```

## Authors

- Vincent Werner
- Gwendal Henry
- Martin Parisot
- ~~Adrian Dufac~~ (still need to commit something)
- François-Xavier Balu
